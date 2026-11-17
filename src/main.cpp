#include "GradeBook.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {
std::string ask(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}
double askNumber(const std::string& prompt) {
    while (true) {
        std::string value = ask(prompt);
        try {
            std::size_t used = 0;
            double number = std::stod(value, &used);
            if (used == value.size()) return number;
        } catch (...) {}
        std::cout << "Please enter a valid number.\n";
    }
}
void showMenu() {
    std::cout << "\n========== STUDENT GRADE BOOK ==========\n"
              << "1. Add student\n2. List students\n3. Search student\n4. Rename student\n5. Remove student\n"
              << "6. Add course\n7. List courses\n8. Enrol student in course\n9. Enter assessment score\n"
              << "10. Show student's course result\n11. Show all results for a course\n12. Configure grading scale\n"
              << "13. Save data\n14. Load data\n0. Exit\n";
}
void printScale(const GradeScale& scale) {
    std::cout << "Grading scale (minimum percentage -> letter):\n";
    for (const auto& band : scale.bands()) std::cout << "  " << band.minimum << "% -> " << band.letter << '\n';
}
}
int main() {
    GradeBook book;
    try { book.load("gradebook.dat"); std::cout << "Loaded gradebook.dat\n"; }
    catch (const std::exception&) { std::cout << "Starting a new grade book. (No saved file was loaded.)\n"; }
    while (true) {
        showMenu();
        const std::string choice = ask("Choose an option: ");
        try {
            if (choice == "0") { std::cout << "Goodbye. Use option 13 before exiting to save your latest changes.\n"; break; }
            if (choice == "1") { const auto id = ask("Student ID: "); const auto name = ask("Full name: "); book.addStudent(id, name); }
            else if (choice == "2") {
                if (book.students().empty()) std::cout << "No students registered.\n";
                for (const auto& s : book.students()) std::cout << s.id() << " | " << s.name() << '\n';
            } else if (choice == "3") {
                const auto* s = book.findStudent(ask("Student ID: "));
                if (s) std::cout << s->id() << " | " << s->name() << '\n'; else std::cout << "Student not found.\n";
            } else if (choice == "4") { const auto id = ask("Student ID: "); const auto name = ask("New full name: "); book.renameStudent(id, name); }
            else if (choice == "5") { if (!book.removeStudent(ask("Student ID: "))) std::cout << "Student not found.\n"; }
            else if (choice == "6") { const auto code = ask("Course code: "); const auto name = ask("Course name: "); book.addCourse(code, name); }
            else if (choice == "7") {
                if (book.courses().empty()) std::cout << "No courses registered.\n";
                for (const auto& c : book.courses()) std::cout << c.code() << " | " << c.name() << '\n';
            } else if (choice == "8") { const auto id = ask("Student ID: "); const auto code = ask("Course code: "); book.enrol(id, code); }
            else if (choice == "9") {
                const auto id = ask("Student ID: "); const auto code = ask("Course code: ");
                const auto name = ask("Assessment name: "); const double maximum = askNumber("Maximum possible score: ");
                const double score = askNumber("Student's raw score: ");
                book.addAssessment(id, code, name, score, maximum);
            } else if (choice == "10") {
                const auto id = ask("Student ID: "); const auto code = ask("Course code: ");
                const auto r = book.result(id, code);
                std::cout << std::fixed << std::setprecision(2) << r.percentage << "% | Grade " << r.letter << '\n';
            } else if (choice == "11") {
                const auto code = ask("Course code: ");
                for (const auto& [id, r] : book.courseResults(code))
                    std::cout << id << " | " << std::fixed << std::setprecision(2) << r.percentage << "% | " << r.letter << '\n';
            } else if (choice == "12") {
                printScale(book.gradingScale());
                std::cout << "Enter the number of grade bands (including a 0% band):\n";
                const int n = static_cast<int>(askNumber("Number of bands: "));
                if (n < 1 || n > 20) throw std::invalid_argument("Choose between 1 and 20 bands.");
                std::vector<GradeBand> bands;
                for (int i = 0; i < n; ++i) {
                    const double minimum = askNumber("Minimum percentage for band " + std::to_string(i + 1) + ": ");
                    const auto letter = ask("Grade label (e.g. A, B, Pass): ");
                    bands.push_back({minimum, letter});
                }
                book.gradingScale().setBands(std::move(bands));
                std::cout << "Grading scale updated.\n";
            } else if (choice == "13") { book.save("gradebook.dat"); std::cout << "Saved to gradebook.dat\n"; }
            else if (choice == "14") { book.load("gradebook.dat"); std::cout << "Loaded gradebook.dat\n"; }
            else std::cout << "Unknown option. Please choose from the menu.\n";
        } catch (const std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }
    }
    return 0;
}
