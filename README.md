# Student Grade Book Management System

A C++17 console application developed for the PPOIS team project. The system allows a teacher or administrator to manage students, courses, enrolments, assessment scores, grading scales, and academic results through an interactive numbered menu.

The project demonstrates object-oriented programming, the Standard Template Library (STL), C++ templates, modular design, file persistence, and automated testing.

**GitHub repository:** [Student-Gradebook](https://github.com/jesseptakwi-max/Student-Gradebook)

## Main Features

- Add, list, search, rename, and remove students using unique student IDs.
- Add and list courses using unique course codes.
- Enrol students in courses.
- Prevent duplicate student enrolments in the same course.
- Record multiple assessments for each student-course enrolment.
- Validate assessment scores against their maximum possible values.
- Calculate aggregate percentages using total points earned divided by total points possible.
- Convert percentages into letter grades using a configurable grading scale.
- View an individual student's course result.
- View assessment results for a course.
- Save records to and load records from `gradebook.dat`.
- Run automated unit tests independently of the interactive application.

## Default Grading Scale

| Percentage | Letter |
|---|:---:|
| 90–100 | A |
| 80–89.99 | B |
| 70–79.99 | C |
| 60–69.99 | D |
| 0–59.99 | F |

The grading scale can be configured through menu option 12.

The default scale is the group's chosen starting scale and can be changed if the lecturer specifies different grading boundaries.

## Technologies and PPOIS Requirements

- **Programming language:** C++17.
- **Object-oriented programming:** Classes including `Student`, `Course`, `Assessment`, `GradeScale`, and `GradeBook`.
- **STL:** Standard containers, strings, streams, and algorithms.
- **Templates:** `Repository<T>` provides reusable typed record storage.
- **Build system:** CMake.
- **Testing:** A separate unit-test executable registered with CTest.
- **Version control:** Git and GitHub.
- **Documentation:** Markdown documentation files.

The application implementation uses C++ and does not require third-party C++ libraries.

## Requirements

- A C++17-compatible compiler.
- CMake 3.16 or newer.
- macOS with Xcode Command Line Tools, or Windows with Visual Studio 2022 and the **Desktop development with C++** workload.
- Git to clone and manage the repository.

## Build and Run on macOS

### 1. Install the compiler tools

Open Terminal and run:

```bash
xcode-select --install
```

If the tools are already installed, macOS will indicate that no installation is necessary.

### 2. Install CMake

If CMake is not installed, use Homebrew:

```bash
brew install cmake
```

### 3. Configure and build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

### 4. Run the application

```bash
./build/student_gradebook
```

## Build and Run on Windows

### 1. Install the required software

Install Visual Studio 2022 Community Edition or another supported edition.

Select the **Desktop development with C++** workload, including MSVC and the Windows SDK.

### 2. Open Developer PowerShell

Open **Developer PowerShell for Visual Studio 2022**.

### 3. Configure and build

Navigate to the project root and run:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

### 4. Run the application

For the Visual Studio generator:

```powershell
.\build\Release\student_gradebook.exe
```

For a single-configuration generator such as Ninja or MinGW Makefiles, the executable may instead be located at:

```powershell
.\build\student_gradebook.exe
```

## Running Unit Tests

The unit tests are separate from the interactive menu application.

After configuring and building the project, run:

### macOS and Linux

```bash
ctest --test-dir build --output-on-failure
```

You can also run the test executable directly:

```bash
./build/gradebook_tests
```

### Windows

For the Visual Studio generator:

```powershell
ctest --test-dir build -C Release --output-on-failure
```

Run the executable directly if needed:

```powershell
.\build\Release\gradebook_tests.exe
```

### Automated Test Coverage

The automated test suite checks:

- Student creation, validation, renaming, and removal.
- Course creation and validation.
- Assessment validation and percentage calculations.
- Default and custom grading scales.
- Repository template operations.
- Student enrolment and duplicate-enrolment rejection.
- GradeBook result calculations.
- Course result generation.
- Saving and loading application data.
- Floating-point precision during persistence.
- Handling invalid and corrupted save files.
- Preserving existing in-memory data after a failed load.

Run the tests after making changes to verify that existing functionality continues to work.

## First-Time Usage

1. Choose **1 — Add student** and enter a unique student ID and full name.
2. Choose **6 — Add course** and enter a unique course code and course name.
3. Choose **8 — Enrol student in course**.
4. Choose **9 — Enter assessment score** and enter the assessment name, maximum possible score, and student's raw score.
5. Choose **10 — Show student's course result** to view an individual result.
6. Choose **11 — Show all results for a course** to view course results.
7. Choose **12 — Configure grading scale** if a different grading system is required.
8. Choose **13 — Save data** before exiting.

The application uses the numbered menu to guide the user through each operation.

### Saving and Loading

The application stores its data in:

`gradebook.dat`

The file is created in the application's current working directory.

- Menu option 13 saves the current grade book.
- Menu option 14 loads saved data.
- At startup, an existing valid save file is loaded automatically.
- If no save file exists, the application starts with an empty grade book.
- If an existing save file cannot be loaded, the application reports an error and exits without silently replacing the file.

Keep backups of `gradebook.dat` because it contains the locally stored application data.

## Project Structure

```text
Student-Gradebook/
├── include/
│   ├── Student.h
│   ├── Course.h
│   ├── Assessment.h
│   ├── GradeScale.h
│   ├── GradeBook.h
│   └── Repository.h
├── src/
│   ├── Student.cpp
│   ├── Course.cpp
│   ├── Assessment.cpp
│   ├── GradeScale.cpp
│   ├── GradeBook.cpp
│   └── main.cpp
├── tests/
│   └── test_main.cpp
├── docs/
│   ├── ARCHITECTURE.md
│   ├── TEAM_PLAN.md
│   ├── TEST_PLAN.md
│   └── FINAL_REPORT_OUTLINE.md
├── .github/
│   └── PULL_REQUEST_TEMPLATE.md
├── CMakeLists.txt
├── README.md
├── LICENSE
└── .gitignore
```

## GitHub Repository and Collaboration

Repository: [https://github.com/jesseptakwi-max/Student-Gradebook](https://github.com/jesseptakwi-max/Student-Gradebook)

The project uses Git and GitHub for version control and collaboration.

The development workflow includes:

1. Creating feature branches for assigned development tasks.
2. Making small, meaningful commits.
3. Pushing development branches to GitHub.
4. Submitting pull requests for review.
5. Reviewing and testing changes before integration.
6. Maintaining a stable version in the `main` branch.
7. Updating the GitHub Projects task board to reflect actual task progress.

The target branch for a pull request must follow the team's agreed integration workflow.

Team assignments and development responsibilities are described in `docs/TEAM_PLAN.md`.

## Team Contributions

The project work is organised around the following responsibilities:

### Jesse

- Student class and student management.
- Course class and course management.
- Student enrolment functionality.
- Command-line interface integration.
- Project integration and testing.

### Jonathan

- Assessment and grading functionality.
- GradeScale implementation.
- GradeBook functionality.
- Repository template.
- Grading and assessment tests.

### Tavana

Tavana was initially included in the team plan, but does not currently have a GitHub account. Any contribution should be documented only if the corresponding work was actually completed.

Actual contributions, reviews, testing, and documentation work should be recorded honestly in the final project report.

## Testing and Platform Verification

The project should be built and tested independently on macOS and Windows.

The current development build and automated unit tests have been successfully executed on macOS.

Windows verification must be recorded separately after the application has been built and tested on a Windows environment.

See `docs/TEST_PLAN.md` for the manual test scenarios, automated testing procedures, and evidence-recording template.

## Known Scope and Limitations

This is a coursework-scale local console application rather than a networked multi-user service.

- Data is stored in a local file.
- Course results use aggregate points rather than individually configured assessment-category weights.
- The application does not provide a graphical user interface.
- Data is not synchronised between computers.
- Users should maintain backups of their saved grade book.
