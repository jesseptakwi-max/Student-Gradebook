# Student Grade Book Management System

A beginner-friendly **C++17 console application** developed by **Jesse, Jonathan and Tavana** for the PPOIS team project. The system lets a teacher or administrator manage students, courses, enrolments, assessment scores and calculated grades through an interactive numbered menu.

The project is designed to build on both **macOS (Jesse)** and **Windows (Jonathan)**. **Tavana** coordinates requirements, documentation, manual testing, the GitHub task board and the final report. See [`docs/TEAM_PLAN.md`](docs/TEAM_PLAN.md).

## Main features

- Add, list, search, rename and remove students using unique student IDs.
- Add and list courses using unique course codes.
- Enrol students in courses.
- Record multiple assessments per student/course, including raw score and maximum possible score.
- Calculate the overall percentage as total points earned divided by total points possible (assessments are weighted by their maximum points).
- Convert percentages into letter grades using an editable grading scale.
- View an individual student's result and course results.
- Save records to and load records from `gradebook.dat`.
- Run unit tests independently from the interactive application.

### Default grading scale

| Percentage | Letter |
|---:|:---:|
| 90–100 | A |
| 80–89.99 | B |
| 70–79.99 | C |
| 60–69.99 | D |
| 0–59.99 | F |

The scale is configurable from the menu. The defaults are the group's chosen starting scale and should be changed only if the lecturer requires a different one.

## Technologies and PPOIS requirements

- **Language:** C++17 only for the application implementation.
- **OOP:** `Student`, `Course`, `Assessment`, `GradeScale` and `GradeBook` classes encapsulate domain data and behaviour.
- **STL:** standard containers, strings, streams and algorithms are used in the implementation.
- **Templates:** `Repository<T>` is a reusable class template used to manage typed records.
- **Build system:** CMake.
- **Testing:** a separate unit-test executable registered with CTest.
- **Collaboration:** Git, GitHub feature branches, small commits and Pull Requests.
- **Documentation:** Markdown files in this repository.

## Requirements

- C++17 compiler.
- CMake 3.16 or newer.
- macOS with Xcode Command Line Tools, or Windows with Visual Studio 2022 and the **Desktop development with C++** workload (including MSVC and the Windows SDK).

The application has no third-party C++ library dependencies.

## Build and run on macOS

1. Install Apple's command-line compiler tools:

   ```bash
   xcode-select --install
   ```

2. Install CMake if needed (Homebrew):

   ```bash
   brew install cmake
   ```

3. From the project root, configure and compile:

   ```bash
   cmake -S . -B build
   cmake --build build --config Release
   ```

4. Run the application:

   ```bash
   ./build/student_gradebook
   ```

## Build and run on Windows

1. Install Visual Studio 2022 (Community edition is sufficient) and select **Desktop development with C++**. Ensure the MSVC compiler and Windows SDK are selected. Install CMake if it is not included with the setup.
2. Open **Developer PowerShell for Visual Studio 2022**.
3. Change directory to the project root, then configure and compile:

   ```powershell
   cmake -S . -B build
   cmake --build build --config Release
   ```

4. Run the application:

   ```powershell
   .\build\Release\student_gradebook.exe
   ```

If CMake uses a single-configuration generator such as MinGW Makefiles or Ninja, the executable may instead be at `build\student_gradebook.exe`.

## Run unit tests (both operating systems)

After configuring and building:

macOS:

```bash
ctest --test-dir build --output-on-failure
./build/gradebook_tests
```

Windows PowerShell (Visual Studio multi-configuration generator):

```powershell
ctest --test-dir build -C Release --output-on-failure
.\build\Release\gradebook_tests.exe
```

The test executable is separate from the menu application. The developers must run these commands on their own computers and record the actual results; do not copy another machine's test result as local evidence.

## First-time usage

1. Choose **Add student** and enter a unique student ID and full name.
2. Choose **Add course** and enter a unique course code and course name.
3. Enrol the student in the course.
4. Add one or more assessments, entering the assessment name, raw score and maximum score.
5. View the student's result or the course results.
6. Review or configure the grading scale if necessary.
7. Save the grade book before exiting. The data file is `gradebook.dat` in the program's current working directory.

The menu displays the available options and prompts for the required values. Enter scores between zero and the maximum possible score.

## Project structure

```text
StudentGradeBook/
├── include/       # Public class and template declarations
├── src/           # C++ implementation and menu entry point
├── tests/         # Independent unit tests
├── docs/          # Team plan, test plan, task board seed and report outline
├── .github/       # Pull Request template
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## GitHub repository and collaboration

Repository: <https://github.com/jesseptakwi-max/TEAMWORK>

The team must use the repository's actual history to show iterative work:

1. Keep `main` as the stable integration branch.
2. Each developer creates a feature branch for their assigned work.
3. Make small, meaningful commits as work progresses.
4. Push the branch and open a Pull Request into `main`.
5. A teammate reviews the changes and checks the build/tests before merge.
6. Update the GitHub Projects task board to reflect the real status of work.

Suggested branch names and work allocation are in [`docs/TEAM_PLAN.md`](docs/TEAM_PLAN.md). Create the GitHub Projects board with the columns **Planned**, **In Progress**, **Under Review** and **Completed**.

## Known scope and limitations

This is a coursework-scale, local console application, not a networked multi-user service. Data is stored in a local file; keep backups of `gradebook.dat`. Course percentages use aggregate points (earned points divided by possible points), not individually configured category weights.
