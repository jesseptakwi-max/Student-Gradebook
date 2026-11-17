#include "Assessment.h"
#include "GradeBook.h"
#include "GradeScale.h"
#include "Repository.h"
#include "Student.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int passed = 0, failed = 0;
void test(const std::string& name, const std::function<void()>& fn) {
    try { fn(); ++passed; std::cout << "[PASS] " << name << '\n'; }
    catch (const std::exception& e) { ++failed; std::cout << "[FAIL] " << name << ": " << e.what() << '\n'; }
}
void require(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }
template <typename F> void requireThrows(F fn) { bool thrown = false; try { fn(); } catch (...) { thrown = true; } require(thrown, "Expected an exception."); }
}
int main() {
    test("Student rejects empty ID", [] { requireThrows([] { Student s("", "Alex"); }); });
    test("Student can be renamed", [] { Student s("S1", "Alex"); s.setName("Sam"); require(s.name() == "Sam", "Name did not change."); });
    test("Course stores code and name", [] { Course c("CS101", "Programming"); require(c.code() == "CS101", "Wrong course code."); });
    test("Assessment calculates percentage", [] { Assessment a{"Exam", 45, 50}; require(a.percentage() == 90.0, "Expected 90 percent."); });
    test("Assessment rejects score above maximum", [] { requireThrows([] { Assessment a{"Exam", 51, 50}; a.percentage(); }); });
    test("Default grading scale maps boundaries", [] { GradeScale s; require(s.gradeFor(90) == "A" && s.gradeFor(89.9) == "B" && s.gradeFor(59.9) == "F", "Incorrect grade boundary."); });
    test("Custom grading scale sorts bands", [] { GradeScale s({{0,"Fail"},{50,"Pass"},{75,"Merit"}}); require(s.gradeFor(80) == "Merit" && s.gradeFor(60) == "Pass", "Custom scale incorrect."); });
    test("Grading scale requires zero boundary", [] { requireThrows([] { GradeScale s({{50,"Pass"}}); }); });
    test("Template repository adds, finds and erases", [] { Repository<Student> r; r.add(Student("S1","Alex"), std::string("S1"), [](const Student& s) -> const std::string& { return s.id(); }); require(r.find(std::string("S1"), [](const Student& s) -> const std::string& { return s.id(); }) != nullptr, "Find failed."); require(r.erase(std::string("S1"), [](const Student& s) -> const std::string& { return s.id(); }), "Erase failed."); });
    test("Grade book enrolment and weighted-by-points result", [] { GradeBook b; b.addStudent("S1","Alex"); b.addCourse("CS101","Programming"); b.enrol("S1","CS101"); b.addAssessment("S1","CS101","Quiz",8,10); b.addAssessment("S1","CS101","Exam",45,50); auto r=b.result("S1","CS101"); require(r.percentage > 88.3 && r.percentage < 88.4 && r.letter == "B", "Incorrect aggregate result."); });
    test("Grade book rejects duplicate student ID", [] { GradeBook b; b.addStudent("S1","Alex"); requireThrows([&] { b.addStudent("S1","Sam"); }); });
    test("Grade book rejects enrolment for unknown student", [] { GradeBook b; b.addCourse("CS101","Programming"); requireThrows([&] { b.enrol("missing","CS101"); }); });
    test("Grade book saves and reloads data", [] { const std::string path="test_gradebook.dat"; GradeBook b; b.addStudent("S2","Taylor Lee"); b.addCourse("MA101","Maths"); b.enrol("S2","MA101"); b.addAssessment("S2","MA101","Test 1",18,20); b.save(path); GradeBook loaded; loaded.load(path); require(loaded.findStudent("S2") && loaded.findStudent("S2")->name()=="Taylor Lee", "Student did not persist."); require(loaded.result("S2","MA101").percentage == 90.0, "Result did not persist."); std::remove(path.c_str()); });
    std::cout << "\n" << passed << " passed, " << failed << " failed.\n";
    return failed == 0 ? 0 : 1;
}
