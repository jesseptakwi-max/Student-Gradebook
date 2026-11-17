#include "GradeBook.h"
#include <fstream>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <utility>

void GradeBook::addStudent(const std::string& id, const std::string& name) {
    students_.add(Student{id, name}, id, [](const Student& s) -> const std::string& { return s.id(); });
}
void GradeBook::renameStudent(const std::string& id, const std::string& name) {
    auto* student = students_.find(id, [](const Student& s) -> const std::string& { return s.id(); });
    if (!student) throw std::out_of_range("Student not found.");
    student->setName(name);
}
bool GradeBook::removeStudent(const std::string& id) {
    if (!students_.erase(id, [](const Student& s) -> const std::string& { return s.id(); })) return false;
    records_.erase(id);
    return true;
}
const Student* GradeBook::findStudent(const std::string& id) const { return students_.find(id, [](const Student& s) -> const std::string& { return s.id(); }); }
const std::vector<Student>& GradeBook::students() const noexcept { return students_.all(); }
void GradeBook::addCourse(const std::string& code, const std::string& name) {
    courses_.add(Course{code, name}, code, [](const Course& c) -> const std::string& { return c.code(); });
}
const Course* GradeBook::findCourse(const std::string& code) const { return courses_.find(code, [](const Course& c) -> const std::string& { return c.code(); }); }
const std::vector<Course>& GradeBook::courses() const noexcept { return courses_.all(); }
void GradeBook::enrol(const std::string& id, const std::string& code) {
    if (!findStudent(id)) throw std::out_of_range("Student not found.");
    if (!findCourse(code)) throw std::out_of_range("Course not found.");
    records_[id].try_emplace(code);
}
void GradeBook::addAssessment(const std::string& id, const std::string& code, const std::string& name, double score, double maximum) {
    auto student = records_.find(id);
    if (student == records_.end() || student->second.find(code) == student->second.end()) throw std::out_of_range("Student is not enrolled in that course.");
    Assessment assessment{name, score, maximum};
    assessment.percentage();
    student->second[code].push_back(std::move(assessment));
}
ResultSummary GradeBook::result(const std::string& id, const std::string& code) const {
    auto student = records_.find(id);
    if (student == records_.end() || student->second.find(code) == student->second.end()) throw std::out_of_range("No enrolment found for that student and course.");
    const auto& assessments = student->second.at(code);
    if (assessments.empty()) throw std::logic_error("No assessments have been entered for this enrolment.");
    double earned = 0, possible = 0;
    for (const auto& a : assessments) { earned += a.score; possible += a.maximum; }
    const double percentage = earned / possible * 100.0;
    return {percentage, scale_.gradeFor(percentage)};
}
std::vector<std::pair<std::string, ResultSummary>> GradeBook::courseResults(const std::string& code) const {
    if (!findCourse(code)) throw std::out_of_range("Course not found.");
    std::vector<std::pair<std::string, ResultSummary>> output;
    for (const auto& [id, courses] : records_) {
        auto it = courses.find(code);
        if (it != courses.end() && !it->second.empty()) output.emplace_back(id, result(id, code));
    }
    return output;
}
GradeScale& GradeBook::gradingScale() noexcept { return scale_; }
const GradeScale& GradeBook::gradingScale() const noexcept { return scale_; }
void GradeBook::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Could not open file for saving: " + filename);
    out << "STUDENT_GRADE_BOOK_1\n" << students_.all().size() << '\n';
    for (const auto& s : students_.all()) out << std::quoted(s.id()) << ' ' << std::quoted(s.name()) << '\n';
    out << courses_.all().size() << '\n';
    for (const auto& c : courses_.all()) out << std::quoted(c.code()) << ' ' << std::quoted(c.name()) << '\n';
    out << scale_.bands().size() << '\n';
    for (const auto& b : scale_.bands()) out << b.minimum << ' ' << std::quoted(b.letter) << '\n';
    std::size_t count = 0;
    for (const auto& entry : records_) count += entry.second.size();
    out << count << '\n';
    for (const auto& [id, cs] : records_) for (const auto& [code, as] : cs) {
        out << std::quoted(id) << ' ' << std::quoted(code) << ' ' << as.size() << '\n';
        for (const auto& a : as) out << std::quoted(a.name) << ' ' << a.score << ' ' << a.maximum << '\n';
    }
    if (!out) throw std::runtime_error("An error occurred while saving the grade book.");
}
void GradeBook::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Could not open file for loading: " + filename);
    std::string magic; std::getline(in, magic);
    if (magic != "STUDENT_GRADE_BOOK_1") throw std::runtime_error("Unsupported or invalid grade-book file.");
    GradeBook temp;
    std::size_t count{};
    if (!(in >> count)) throw std::runtime_error("Invalid student section.");
    for (std::size_t i = 0; i < count; ++i) { std::string id, name; if (!(in >> std::quoted(id) >> std::quoted(name))) throw std::runtime_error("Invalid student record."); temp.addStudent(id, name); }
    if (!(in >> count)) throw std::runtime_error("Invalid course section.");
    for (std::size_t i = 0; i < count; ++i) { std::string code, name; if (!(in >> std::quoted(code) >> std::quoted(name))) throw std::runtime_error("Invalid course record."); temp.addCourse(code, name); }
    if (!(in >> count)) throw std::runtime_error("Invalid grading-scale section.");
    std::vector<GradeBand> bands;
    for (std::size_t i = 0; i < count; ++i) { GradeBand b{}; if (!(in >> b.minimum >> std::quoted(b.letter))) throw std::runtime_error("Invalid grade band."); bands.push_back(std::move(b)); }
    temp.scale_.setBands(std::move(bands));
    if (!(in >> count)) throw std::runtime_error("Invalid enrolment section.");
    for (std::size_t i = 0; i < count; ++i) {
        std::string id, code; std::size_t n{};
        if (!(in >> std::quoted(id) >> std::quoted(code) >> n)) throw std::runtime_error("Invalid enrolment record.");
        temp.enrol(id, code);
        for (std::size_t j = 0; j < n; ++j) { Assessment a; if (!(in >> std::quoted(a.name) >> a.score >> a.maximum)) throw std::runtime_error("Invalid assessment record."); a.percentage(); temp.records_[id][code].push_back(std::move(a)); }
    }
    *this = std::move(temp);
}
