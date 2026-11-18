
#include "GradeBook.h"

#include <cmath>
#include <exception>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

namespace {

std::string ask(const std::string& prompt) {
    std::cout << prompt;

    std::string value;

    if (!std::getline(std::cin, value)) {
        throw std::runtime_error("Input stream closed.");
    }

    return value;
}

double askNumber(const std::string& prompt) {
    while (true) {
        const std::string value = ask(prompt);

        try {
            std::size_t used = 0;
            const double number = std::stod(value, &used);

            if (used == value.size() && std::isfinite(number)) {
                return number;
            }
        } catch (const std::exception&) {
            // Invalid input: ask again.
        }

        std::cout << "Please enter a valid finite number.\n";
    }
}

int askInteger(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        const double number = askNumber(prompt);

        if (std::floor(number) == number &&
            number >= minimum &&
            number <= maximum) {
            return static_cast<int>(number);
        }

        std::cout << "Please enter a whole number between "
                  << minimum << " and " << maximum << ".\n";
    }
}

void showMenu() {
    std::cout
        << "\n========== STUDENT GRADE BOOK ==========\n"
        << "1. Add student\n"
        << "2. List students\n"
        << "3. Search student\n"
        << "4. Rename student\n"
        << "5. Remove student\n"
        << "6. Add course\n"
        << "7. List courses\n"
        << "8. Enrol student in course\n"
        << "9. Enter assessment score\n"
        << "10. Show student's course result\n"
        << "11. Show all results for a course\n"
        << "12. Configure grading scale\n"
        << "13. Save data\n"
        << "14. Load data\n"
        << "0. Exit\n";
}

void printScale(const GradeScale& scale) {
    std::cout
        << "Grading scale (minimum percentage -> letter):\n";

    for (const auto& band : scale.bands()) {
        std::cout << "  "
                  << band.minimum << "% -> "
                  << band.letter << '\n';
    }
}

}

int main() {
    GradeBook book;

    const std::filesystem::path saveFile("gradebook.dat");
    std::error_code fileError;

    const bool saveFileExists =
        std::filesystem::exists(saveFile, fileError);

    if (fileError) {
        std::cerr
            << "Error: Could not check gradebook.dat: "
            << fileError.message() << '\n';

        return 1;
    }

    if (saveFileExists) {
        try {
            book.load(saveFile.string());
            std::cout << "Loaded gradebook.dat\n";
        } catch (const std::exception& e) {
            std::cerr
                << "ERROR: An existing gradebook.dat file "
                << "could not be loaded.\n"
                << "Reason: " << e.what() << '\n'
                << "The application will close without "
                << "overwriting the file.\n";

            return 1;
        }
    } else {
        std::cout
            << "No saved grade book found. "
            << "Starting a new grade book.\n";
    }

    while (true) {
        showMenu();

        std::string choice;

        try {
            choice = ask("Choose an option: ");
        } catch (const std::exception& e) {
            std::cout << "\n" << e.what() << "\n";
            break;
        }

        try {
            if (choice == "0") {
                std::cout
                    << "Goodbye. Use option 13 before exiting "
                    << "to save your latest changes.\n";
                break;
            }

            if (choice == "1") {
                const auto id = ask("Student ID: ");
                const auto name = ask("Full name: ");

                book.addStudent(id, name);
                std::cout << "Student added successfully.\n";
            }

            else if (choice == "2") {
                if (book.students().empty()) {
                    std::cout << "No students registered.\n";
                }

                for (const auto& student : book.students()) {
                    std::cout << student.id()
                              << " | "
                              << student.name()
                              << '\n';
                }
            }

            else if (choice == "3") {
                const auto* student =
                    book.findStudent(ask("Student ID: "));

                if (student) {
                    std::cout << student->id()
                              << " | "
                              << student->name()
                              << '\n';
                } else {
                    std::cout << "Student not found.\n";
                }
            }

            else if (choice == "4") {
                const auto id = ask("Student ID: ");
                const auto name = ask("New full name: ");

                book.renameStudent(id, name);
                std::cout << "Student renamed successfully.\n";
            }

            else if (choice == "5") {
                if (book.removeStudent(ask("Student ID: "))) {
                    std::cout << "Student removed successfully.\n";
                } else {
                    std::cout << "Student not found.\n";
                }
            }

            else if (choice == "6") {
                const auto code = ask("Course code: ");
                const auto name = ask("Course name: ");

                book.addCourse(code, name);
                std::cout << "Course added successfully.\n";
            }

            else if (choice == "7") {
                if (book.courses().empty()) {
                    std::cout << "No courses registered.\n";
                }

                for (const auto& course : book.courses()) {
                    std::cout << course.code()
                              << " | "
                              << course.name()
                              << '\n';
                }
            }

            else if (choice == "8") {
                const auto id = ask("Student ID: ");
                const auto code = ask("Course code: ");

                book.enrol(id, code);
                std::cout << "Student enrolled successfully.\n";
            }

            else if (choice == "9") {
                const auto id = ask("Student ID: ");
                const auto code = ask("Course code: ");
                const auto name = ask("Assessment name: ");

                const double maximum =
                    askNumber("Maximum possible score: ");

                const double score =
                    askNumber("Student's raw score: ");

                book.addAssessment(id, code, name, score, maximum);

                std::cout << "Assessment added successfully.\n";
            }

            else if (choice == "10") {
                const auto id = ask("Student ID: ");
                const auto code = ask("Course code: ");

                const auto result = book.result(id, code);

                std::cout
                    << std::fixed << std::setprecision(2)
                    << result.percentage
                    << "% | Grade "
                    << result.letter
                    << '\n';
            }

            else if (choice == "11") {
                const auto code = ask("Course code: ");

                const auto results = book.courseResults(code);

                if (results.empty()) {
                    std::cout
                        << "No assessment results available for this course.\n";
                }

                for (const auto& [id, result] : results) {
                    std::cout
                        << id << " | "
                        << std::fixed << std::setprecision(2)
                        << result.percentage
                        << "% | "
                        << result.letter
                        << '\n';
                }
            }

            else if (choice == "12") {
                printScale(book.gradingScale());

                std::cout
                    << "Enter the number of grade bands "
                    << "(including a 0% band):\n";

                const int n = askInteger(
                    "Number of bands: ", 1, 20
                );

                std::vector<GradeBand> bands;

                for (int i = 0; i < n; ++i) {
                    const double minimum = askNumber(
                        "Minimum percentage for band " +
                        std::to_string(i + 1) + ": "
                    );

                    const auto letter =
                        ask("Grade label (e.g. A, B, Pass): ");

                    bands.push_back({minimum, letter});
                }

                book.gradingScale().setBands(std::move(bands));

                std::cout << "Grading scale updated.\n";
            }

            else if (choice == "13") {
                book.save("gradebook.dat");
                std::cout << "Saved to gradebook.dat\n";
            }

            else if (choice == "14") {
                book.load("gradebook.dat");
                std::cout << "Loaded gradebook.dat\n";
            }

            else {
                std::cout
                    << "Unknown option. Please choose from the menu.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}
