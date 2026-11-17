# Team plan and division of responsibilities

## Confirmed team and equipment

| Member | Role | Computer / environment |
|---|---|---|
| **Jesse** | C++ Developer 1 | MacBook running macOS |
| **Jonathan** | C++ Developer 2 | Windows laptop |
| **Tavana** | Documentation, requirements and QA coordinator | No dedicated project laptop; can work on documentation, planning and reviews using available access/shared sessions |

There are two laptops, so Jesse and Jonathan are the two developers who implement and run the C++ project. Tavana has a substantial, defined contribution that does not require independently compiling the project.

## Jesse — Developer 1 (macOS)

**Main ownership:** student and course management, menu integration and macOS verification.

- Implement and maintain `Student` and `Course` classes.
- Implement student operations: add, list, search, rename and remove.
- Implement course operations: add and list courses.
- Coordinate changes to `src/main.cpp` and the interactive menu with Jonathan so both developers do not edit the same area independently.
- Write and run tests for student and course behaviour.
- Build and run the full project on macOS using Clang and CMake.
- Commit work in small increments on `feature/jesse-student-course` and open Pull Requests.
- Record macOS build/test commands and actual outcomes for the final report.

## Jonathan — Developer 2 (Windows)

**Main ownership:** enrolment, assessments, grading, persistence and Windows verification.

- Implement and maintain `Assessment`, `GradeScale` and `GradeBook` functionality.
- Implement enrolment, score entry, result calculation and course reports.
- Maintain saving and loading of the grade-book data file.
- Maintain and explain the reusable `Repository<T>` class template and its use of STL.
- Write and run tests for enrolment, assessments, grading, results and persistence.
- Build and run the full project on Windows using MSVC, CMake and CTest.
- Coordinate changes to `src/main.cpp` with Jesse.
- Commit work in small increments on `feature/jonathan-grading-assessments` and open Pull Requests.
- Record Windows build/test commands and actual outcomes for the final report.

## Tavana — Documentation, requirements and QA coordinator

**Main ownership:** non-code project deliverables, task board, manual test planning and contribution evidence.

- Convert the lecturer's PPOIS task requirements into a checklist and track evidence for each requirement.
- Create and maintain the GitHub Projects task board with **Planned**, **In Progress**, **Under Review** and **Completed** columns.
- Maintain project documentation in Markdown, including the user guide and architecture explanation; coordinate updates to the README.
- Prepare manual test scenarios and expected outcomes using `docs/TEST_PLAN.md`.
- Review Pull Requests: check that the change matches its task, documentation is updated where needed, and developers have supplied build/test evidence. Record actual review comments; do not claim reviews that did not happen.
- Maintain a contribution log with dates, task links, decisions and evidence.
- Coordinate the final report and presentation/demo script.
- Help check that the final report accurately describes the work and actual test results.

## Shared responsibilities

- All three members agree on project scope, user needs and the default A–F grading scale.
- All three participate in planning and contribute content to the final report.
- Jesse demonstrates the macOS build; Jonathan demonstrates the Windows build; Tavana coordinates the user-workflow review and documentation.
- All members should understand the project's purpose and be able to explain their own contributions.
- Individual contributions must be truthful and visible through commits, Pull Requests, task-board items, review comments, test records or documentation.

## Suggested branches

- Jesse: `feature/jesse-student-course`
- Jonathan: `feature/jonathan-grading-assessments`
- Tavana: `docs/tavana-documentation-qa`

Use Pull Requests into `main`. Avoid committing directly to `main` for normal development. Tavana's branch is for documentation and QA artefacts, not C++ implementation.

## GitHub task board seed

Create a GitHub Projects board for this repository with these columns: **Planned**, **In Progress**, **Under Review**, **Completed**. Add the following tasks and assign the named owner:

| Task | Owner | Suggested initial status |
|---|---|---|
| Confirm project requirements and acceptance checklist | Tavana | Planned |
| Set up CMake build and shared C++17 conventions | Jesse + Jonathan | Planned |
| Implement student management and tests | Jesse | Planned |
| Implement course management and tests | Jesse | Planned |
| Implement enrolment and assessment entry | Jonathan | Planned |
| Implement grade scale and result calculations | Jonathan | Planned |
| Implement save/load and persistence tests | Jonathan | Planned |
| Integrate menu and validate full user workflow | Jesse + Jonathan | Planned |
| Build and test on macOS | Jesse | Planned |
| Build and test on Windows | Jonathan | Planned |
| Prepare manual test cases and review evidence | Tavana | Planned |
| Maintain README and architecture/user documentation | Tavana | Planned |
| Review Pull Requests and maintain contribution log | Tavana + other reviewer | Planned |
| Prepare final report and presentation | Tavana, with input from all | Planned |

Move cards only when work actually changes status. This table is a starting plan; the GitHub board should reflect real progress.

## Milestones

1. Create the GitHub board, agree interfaces and confirm both computers can configure the starter project.
2. Complete student/course management and the menu foundation.
3. Complete enrolment, assessments, grading and persistence.
4. Complete independent unit tests and manual workflow testing.
5. Verify clean builds on macOS and Windows.
6. Finish documentation, contribution evidence, final report and presentation.
