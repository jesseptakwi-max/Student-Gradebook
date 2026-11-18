
#include "GradeBook.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

// ------------------------------------------------------------
// Student management
// ------------------------------------------------------------

void GradeBook::addStudent(
    const std::string& id,
    const std::string& name
) {
    students_.add(
        Student{id, name},
        id,
        [](const Student& student) -> const std::string& {
            return student.id();
        }
    );
}

void GradeBook::renameStudent(
    const std::string& id,
    const std::string& name
) {
    auto* student = students_.find(
        id,
        [](const Student& item) -> const std::string& {
            return item.id();
        }
    );

    if (!student) {
        throw std::out_of_range("Student not found.");
    }

    student->setName(name);
}

bool GradeBook::removeStudent(const std::string& id) {
    if (!students_.erase(
        id,
        [](const Student& student) -> const std::string& {
            return student.id();
        }
    )) {
        return false;
    }

    records_.erase(id);
    return true;
}

const Student* GradeBook::findStudent(
    const std::string& id
) const {
    return students_.find(
        id,
        [](const Student& student) -> const std::string& {
            return student.id();
        }
    );
}

const std::vector<Student>& GradeBook::students() const noexcept {
    return students_.all();
}

// ------------------------------------------------------------
// Course management
// ------------------------------------------------------------

void GradeBook::addCourse(
    const std::string& code,
    const std::string& name
) {
    courses_.add(
        Course{code, name},
        code,
        [](const Course& course) -> const std::string& {
            return course.code();
        }
    );
}

const Course* GradeBook::findCourse(
    const std::string& code
) const {
    return courses_.find(
        code,
        [](const Course& course) -> const std::string& {
            return course.code();
        }
    );
}

const std::vector<Course>& GradeBook::courses() const noexcept {
    return courses_.all();
}

// ------------------------------------------------------------
// Student enrolment
// ------------------------------------------------------------

void GradeBook::enrol(
    const std::string& id,
    const std::string& code
) {
    if (!findStudent(id)) {
        throw std::out_of_range("Student not found.");
    }

    if (!findCourse(code)) {
        throw std::out_of_range("Course not found.");
    }

    auto& studentCourses = records_[id];

    const bool inserted =
        studentCourses.emplace(code, AssessmentList{}).second;

    if (!inserted) {
        throw std::invalid_argument(
            "Student is already enrolled in this course."
        );
    }
}

// ------------------------------------------------------------
// Assessment management
// ------------------------------------------------------------

void GradeBook::addAssessment(
    const std::string& id,
    const std::string& code,
    const std::string& name,
    double score,
    double maximum
) {
    auto student = records_.find(id);

    if (student == records_.end() ||
        student->second.find(code) == student->second.end()) {
        throw std::out_of_range(
            "Student is not enrolled in that course."
        );
    }

    Assessment assessment{name, score, maximum};

    // Validate before storing the assessment.
    assessment.percentage();

    student->second.at(code).push_back(std::move(assessment));
}

// ------------------------------------------------------------
// Result calculation
// ------------------------------------------------------------

ResultSummary GradeBook::result(
    const std::string& id,
    const std::string& code
) const {
    auto student = records_.find(id);

    if (student == records_.end() ||
        student->second.find(code) == student->second.end()) {
        throw std::out_of_range(
            "No enrolment found for that student and course."
        );
    }

    const auto& assessments = student->second.at(code);

    if (assessments.empty()) {
        throw std::logic_error(
            "No assessments have been entered for this enrolment."
        );
    }

    long double earned = 0.0L;
    long double possible = 0.0L;

    for (const auto& assessment : assessments) {
        earned += static_cast<long double>(assessment.score);
        possible += static_cast<long double>(assessment.maximum);
    }

    if (!std::isfinite(earned) ||
        !std::isfinite(possible) ||
        possible <= 0.0L) {
        throw std::overflow_error(
            "Could not calculate a valid course result."
        );
    }

    const double percentage =
        static_cast<double>((earned / possible) * 100.0L);

    if (!std::isfinite(percentage)) {
        throw std::overflow_error(
            "Calculated percentage is not finite."
        );
    }

    return {
        percentage,
        scale_.gradeFor(percentage)
    };
}

std::vector<std::pair<std::string, ResultSummary>>
GradeBook::courseResults(const std::string& code) const {
    if (!findCourse(code)) {
        throw std::out_of_range("Course not found.");
    }

    std::vector<std::pair<std::string, ResultSummary>> output;

    for (const auto& [id, courses] : records_) {
        auto it = courses.find(code);

        if (it != courses.end() && !it->second.empty()) {
            output.emplace_back(id, result(id, code));
        }
    }

    return output;
}

// ------------------------------------------------------------
// Grading scale
// ------------------------------------------------------------

GradeScale& GradeBook::gradingScale() noexcept {
    return scale_;
}

const GradeScale& GradeBook::gradingScale() const noexcept {
    return scale_;
}

// ------------------------------------------------------------
// Save gradebook data
// ------------------------------------------------------------

void GradeBook::save(const std::string& filename) const {
    std::ofstream out(filename);

    if (!out) {
        throw std::runtime_error(
            "Could not open file for saving: " + filename
        );
    }

    // Preserve enough precision to reconstruct double values.
    out << std::setprecision(
        std::numeric_limits<double>::max_digits10
    );

    out << "STUDENT_GRADE_BOOK_1\n";

    // Save students.
    out << students_.all().size() << '\n';

    for (const auto& student : students_.all()) {
        out << std::quoted(student.id()) << ' '
            << std::quoted(student.name()) << '\n';
    }

    // Save courses.
    out << courses_.all().size() << '\n';

    for (const auto& course : courses_.all()) {
        out << std::quoted(course.code()) << ' '
            << std::quoted(course.name()) << '\n';
    }

    // Save grading scale.
    out << scale_.bands().size() << '\n';

    for (const auto& band : scale_.bands()) {
        out << band.minimum << ' '
            << std::quoted(band.letter) << '\n';
    }

    // Count enrolments.
    std::size_t count = 0;

    for (const auto& entry : records_) {
        count += entry.second.size();
    }

    out << count << '\n';

    // Save enrolments and assessments.
    for (const auto& [id, courses] : records_) {
        for (const auto& [code, assessments] : courses) {
            out << std::quoted(id) << ' '
                << std::quoted(code) << ' '
                << assessments.size() << '\n';

            for (const auto& assessment : assessments) {
                out << std::quoted(assessment.name) << ' '
                    << assessment.score << ' '
                    << assessment.maximum << '\n';
            }
        }
    }

    if (!out) {
        throw std::runtime_error(
            "An error occurred while saving the grade book."
        );
    }
}

// ------------------------------------------------------------
// Load gradebook data
// ------------------------------------------------------------

void GradeBook::load(const std::string& filename) {
    std::ifstream in(filename);

    if (!in) {
        throw std::runtime_error(
            "Could not open file for loading: " + filename
        );
    }

    std::string magic;

    if (!std::getline(in, magic) ||
        magic != "STUDENT_GRADE_BOOK_1") {
        throw std::runtime_error(
            "Unsupported or invalid grade-book file."
        );
    }

    // Build a temporary grade book so existing data is not
    // changed unless the entire file is valid.
    GradeBook temp;

    std::size_t count{};

    // Load students.
    if (!(in >> count)) {
        throw std::runtime_error("Invalid student section.");
    }

    for (std::size_t i = 0; i < count; ++i) {
        std::string id;
        std::string name;

        if (!(in >> std::quoted(id) >> std::quoted(name))) {
            throw std::runtime_error("Invalid student record.");
        }

        temp.addStudent(id, name);
    }

    // Load courses.
    if (!(in >> count)) {
        throw std::runtime_error("Invalid course section.");
    }

    for (std::size_t i = 0; i < count; ++i) {
        std::string code;
        std::string name;

        if (!(in >> std::quoted(code) >> std::quoted(name))) {
            throw std::runtime_error("Invalid course record.");
        }

        temp.addCourse(code, name);
    }

    // Load grading scale.
    if (!(in >> count)) {
        throw std::runtime_error("Invalid grading-scale section.");
    }

    std::vector<GradeBand> bands;

    for (std::size_t i = 0; i < count; ++i) {
        GradeBand band{};

        if (!(in >> band.minimum >> std::quoted(band.letter))) {
            throw std::runtime_error("Invalid grade band.");
        }

        bands.push_back(std::move(band));
    }

    temp.scale_.setBands(std::move(bands));

    // Load enrolments and their assessments.
    if (!(in >> count)) {
        throw std::runtime_error("Invalid enrolment section.");
    }

    for (std::size_t i = 0; i < count; ++i) {
        std::string id;
        std::string code;
        std::size_t assessmentCount{};

        if (!(in >> std::quoted(id)
                 >> std::quoted(code)
                 >> assessmentCount)) {
            throw std::runtime_error("Invalid enrolment record.");
        }

        // Reject duplicate enrolment records in the saved file.
        auto existingStudent = temp.records_.find(id);

        if (existingStudent != temp.records_.end() &&
            existingStudent->second.find(code) !=
                existingStudent->second.end()) {
            throw std::runtime_error(
                "Duplicate enrolment record in saved file."
            );
        }

        temp.enrol(id, code);

        for (std::size_t j = 0; j < assessmentCount; ++j) {
            Assessment assessment;

            if (!(in >> std::quoted(assessment.name)
                     >> assessment.score
                     >> assessment.maximum)) {
                throw std::runtime_error("Invalid assessment record.");
            }

            // Validate each loaded assessment.
            assessment.percentage();

            temp.records_[id][code].push_back(
                std::move(assessment)
            );
        }
    }

    // Reject unexpected non-whitespace data at the end.
    in >> std::ws;

    if (!in.eof()) {
        throw std::runtime_error(
            "Unexpected data at the end of the grade-book file."
        );
    }

    // Replace existing data only after successful validation.
    *this = std::move(temp);
}
