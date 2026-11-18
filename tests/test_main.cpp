
#include "Assessment.h"
#include "Course.h"
#include "GradeBook.h"
#include "GradeScale.h"
#include "Repository.h"
#include "Student.h"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

namespace {

int passed = 0;
int failed = 0;

void test(const std::string& name, const std::function<void()>& fn) {
    try {
        fn();
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    } catch (const std::exception& e) {
        ++failed;
        std::cout << "[FAIL] " << name << ": " << e.what() << '\n';
    } catch (...) {
        ++failed;
        std::cout << "[FAIL] " << name << ": Unknown exception.\n";
    }
}

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

template <typename F>
void requireThrows(F fn) {
    bool thrown = false;

    try {
        fn();
    } catch (...) {
        thrown = true;
    }

    require(thrown, "Expected an exception.");
}

struct TemporaryFile {
    std::string path;

    explicit TemporaryFile(std::string filename)
        : path(std::move(filename)) {
    }

    ~TemporaryFile() {
        std::remove(path.c_str());
    }
};

}

int main() {

    // Student tests

    test("Student rejects empty ID", [] {
        requireThrows([] {
            Student s("", "Alex");
        });
    });

    test("Student rejects blank ID", [] {
        requireThrows([] {
            Student s("   ", "Alex");
        });
    });

    test("Student rejects empty name", [] {
        requireThrows([] {
            Student s("S1", "");
        });
    });

    test("Student rejects blank name", [] {
        requireThrows([] {
            Student s("S1", "   ");
        });
    });

    test("Student can be renamed", [] {
        Student s("S1", "Alex");
        s.setName("Sam");

        require(s.name() == "Sam", "Name did not change.");
    });

    test("Student rejects blank renamed name", [] {
        Student s("S1", "Alex");

        requireThrows([&] {
            s.setName("   ");
        });

        require(s.name() == "Alex",
                "Invalid rename changed the original name.");
    });


    // Course tests

    test("Course stores code and name", [] {
        Course c("CS101", "Programming");

        require(c.code() == "CS101", "Wrong course code.");
        require(c.name() == "Programming", "Wrong course name.");
    });

    test("Course rejects empty code", [] {
        requireThrows([] {
            Course c("", "Programming");
        });
    });

    test("Course rejects blank name", [] {
        requireThrows([] {
            Course c("CS101", "   ");
        });
    });


    // Assessment tests

    test("Assessment calculates percentage", [] {
        Assessment a{"Exam", 45, 50};

        require(a.percentage() == 90.0,
                "Expected 90 percent.");
    });

    test("Assessment rejects empty name", [] {
        requireThrows([] {
            Assessment a{"", 45, 50};
            a.percentage();
        });
    });

    test("Assessment rejects score above maximum", [] {
        requireThrows([] {
            Assessment a{"Exam", 51, 50};
            a.percentage();
        });
    });

    test("Assessment rejects negative score", [] {
        requireThrows([] {
            Assessment a{"Exam", -1, 50};
            a.percentage();
        });
    });

    test("Assessment rejects zero maximum", [] {
        requireThrows([] {
            Assessment a{"Exam", 0, 0};
            a.percentage();
        });
    });

    test("Assessment rejects NaN score", [] {
        requireThrows([] {
            Assessment a{
                "Exam",
                std::numeric_limits<double>::quiet_NaN(),
                50
            };

            a.percentage();
        });
    });

    test("Assessment rejects infinite maximum", [] {
        requireThrows([] {
            Assessment a{
                "Exam",
                10,
                std::numeric_limits<double>::infinity()
            };

            a.percentage();
        });
    });


    // GradeScale tests

    test("Default grading scale maps boundaries", [] {
        GradeScale s;

        require(
            s.gradeFor(90) == "A" &&
            s.gradeFor(89.9) == "B" &&
            s.gradeFor(59.9) == "F",
            "Incorrect grade boundary."
        );
    });

    test("Custom grading scale sorts bands", [] {
        GradeScale s({
            {0, "Fail"},
            {50, "Pass"},
            {75, "Merit"}
        });

        require(
            s.gradeFor(80) == "Merit" &&
            s.gradeFor(60) == "Pass",
            "Custom scale incorrect."
        );
    });

    test("Grading scale requires zero boundary", [] {
        requireThrows([] {
            GradeScale s({{50, "Pass"}});
        });
    });

    test("Grading scale rejects duplicate boundaries", [] {
        requireThrows([] {
            GradeScale s({
                {0, "Fail"},
                {50, "Pass"},
                {50, "Merit"}
            });
        });
    });

    test("Grading scale rejects invalid percentage", [] {
        GradeScale s;

        requireThrows([&] {
            s.gradeFor(101);
        });
    });

    test("Grading scale rejects NaN percentage", [] {
        GradeScale s;

        requireThrows([&] {
            s.gradeFor(
                std::numeric_limits<double>::quiet_NaN()
            );
        });
    });

    test("Grading scale rejects blank label", [] {
        requireThrows([] {
            GradeScale s({
                {0, "   "}
            });
        });
    });


    // Repository tests

    test("Template repository adds, finds and erases", [] {
        Repository<Student> r;

        r.add(
            Student("S1", "Alex"),
            std::string("S1"),
            [](const Student& s) -> const std::string& {
                return s.id();
            }
        );

        require(
            r.find(
                std::string("S1"),
                [](const Student& s) -> const std::string& {
                    return s.id();
                }
            ) != nullptr,
            "Find failed."
        );

        require(
            r.erase(
                std::string("S1"),
                [](const Student& s) -> const std::string& {
                    return s.id();
                }
            ),
            "Erase failed."
        );

        require(r.all().empty(), "Repository should be empty.");
    });

    test("Repository rejects duplicate identifiers", [] {
        Repository<Student> r;

        auto getter = [](const Student& s) -> const std::string& {
            return s.id();
        };

        r.add(Student("S1", "Alex"), std::string("S1"), getter);

        requireThrows([&] {
            r.add(Student("S1", "Sam"), std::string("S1"), getter);
        });
    });


    // GradeBook tests

    test("Grade book adds and finds student", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");

        require(
            b.findStudent("S1") != nullptr,
            "Student was not found."
        );
    });

    test("Grade book rejects duplicate student ID", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");

        requireThrows([&] {
            b.addStudent("S1", "Sam");
        });
    });

    test("Grade book renames student", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.renameStudent("S1", "Sam");

        require(
            b.findStudent("S1")->name() == "Sam",
            "Student was not renamed."
        );
    });

    test("Grade book removes student", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");

        require(b.removeStudent("S1"),
                "Student was not removed.");

        require(b.findStudent("S1") == nullptr,
                "Student still exists.");
    });

    test("Grade book rejects enrolment for unknown student", [] {
        GradeBook b;

        b.addCourse("CS101", "Programming");

        requireThrows([&] {
            b.enrol("missing", "CS101");
        });
    });

    test("Grade book rejects enrolment for unknown course", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");

        requireThrows([&] {
            b.enrol("S1", "missing");
        });
    });

    test("Grade book rejects duplicate enrolment", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");

        b.enrol("S1", "CS101");

        requireThrows([&] {
            b.enrol("S1", "CS101");
        });
    });

    test("Grade book rejects assessment for unenrolled student", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");

        requireThrows([&] {
            b.addAssessment("S1", "CS101", "Quiz", 8, 10);
        });
    });

    test("Grade book rejects result without assessments", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");
        b.enrol("S1", "CS101");

        requireThrows([&] {
            b.result("S1", "CS101");
        });
    });

    test("Grade book calculates weighted-by-points result", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");
        b.enrol("S1", "CS101");

        b.addAssessment("S1", "CS101", "Quiz", 8, 10);
        b.addAssessment("S1", "CS101", "Exam", 45, 50);

        const auto r = b.result("S1", "CS101");

        require(
            r.percentage > 88.3 &&
            r.percentage < 88.4 &&
            r.letter == "B",
            "Incorrect aggregate result."
        );
    });

    test("Grade book removes associated student records", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");
        b.enrol("S1", "CS101");
        b.addAssessment("S1", "CS101", "Quiz", 8, 10);

        require(b.removeStudent("S1"),
                "Student was not removed.");

        b.addStudent("S1", "Sam");

        requireThrows([&] {
            b.result("S1", "CS101");
        });
    });

    test("Grade book generates course results", [] {
        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addStudent("S2", "Taylor");

        b.addCourse("CS101", "Programming");

        b.enrol("S1", "CS101");
        b.enrol("S2", "CS101");

        b.addAssessment("S1", "CS101", "Exam", 90, 100);
        b.addAssessment("S2", "CS101", "Exam", 75, 100);

        const auto results = b.courseResults("CS101");

        require(results.size() == 2,
                "Expected two course results.");
    });

    test("Grade book rejects report for unknown course", [] {
        GradeBook b;

        requireThrows([&] {
            b.courseResults("missing");
        });
    });


    // Persistence tests

    test("Grade book saves and reloads data", [] {
        TemporaryFile file("test_gradebook.dat");

        GradeBook b;

        b.addStudent("S2", "Taylor Lee");
        b.addCourse("MA101", "Maths");
        b.enrol("S2", "MA101");

        b.addAssessment("S2", "MA101", "Test 1", 18, 20);

        b.save(file.path);

        GradeBook loaded;
        loaded.load(file.path);

        require(
            loaded.findStudent("S2") != nullptr &&
            loaded.findStudent("S2")->name() == "Taylor Lee",
            "Student did not persist."
        );

        require(
            loaded.result("S2", "MA101").percentage == 90.0,
            "Result did not persist."
        );
    });

    test("Grade book preserves floating-point precision", [] {
        TemporaryFile file("test_precision.dat");

        GradeBook b;

        b.addStudent("S1", "Alex");
        b.addCourse("CS101", "Programming");
        b.enrol("S1", "CS101");

        b.addAssessment("S1", "CS101", "Quiz", 1, 3);

        const double original =
            b.result("S1", "CS101").percentage;

        b.save(file.path);

        GradeBook loaded;
        loaded.load(file.path);

        const double restored =
            loaded.result("S1", "CS101").percentage;

        require(
            original == restored,
            "Floating-point precision was not preserved."
        );
    });

    test("Failed load preserves existing grade book", [] {
        TemporaryFile file("test_invalid_gradebook.dat");

        {
            std::ofstream out(file.path);
            out << "INVALID_FILE_FORMAT\n";
        }

        GradeBook b;
        b.addStudent("S1", "Alex");

        requireThrows([&] {
            b.load(file.path);
        });

        require(
            b.findStudent("S1") != nullptr,
            "Existing data was lost after failed loading."
        );
    });

    test("Grade book rejects invalid saved data", [] {
        TemporaryFile file("test_corrupt_gradebook.dat");

        {
            std::ofstream out(file.path);

            out << "STUDENT_GRADE_BOOK_1\n";
            out << "1\n";
            out << "\"S1\" \"Alex\"\n";
            out << "0\n";
            out << "1\n";
            out << "0 \"F\"\n";
            out << "1\n";
            out << "\"S1\" \"UNKNOWN\" 0\n";
        }

        GradeBook b;

        requireThrows([&] {
            b.load(file.path);
        });
    });

    std::cout
        << "\n====================================\n"
        << passed << " passed, "
        << failed << " failed.\n"
        << "====================================\n";

    return failed == 0 ? 0 : 1;
}
