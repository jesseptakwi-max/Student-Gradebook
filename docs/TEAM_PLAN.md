# Team Plan and Division of Responsibilities

## 1. Confirmed Team and Equipment

| Member | Role | Computer / Environment |
|---|---|---|
| **Jesse** | C++ Developer 1 | MacBook running macOS |
| **Jonathan** | C++ Developer 2 | Windows laptop |
| **Tavana** | Documentation, Requirements and QA Coordinator | No dedicated project laptop; contributes through available access and shared sessions |

Jesse and Jonathan are responsible for implementing and running the C++ application on their respective computers. Tavana contributes to documentation, requirements, planning, manual testing and quality assurance.

Tavana does not currently have a GitHub account. GitHub activities requiring an account must therefore be handled by Jesse or Jonathan, while Tavana's actual contributions should still be recorded.

## 2. Jesse — Developer 1 (macOS)

**Main ownership:** Student and course management, menu integration, project coordination and macOS verification.

Responsibilities:

- Implement and maintain the `Student` and `Course` classes.
- Implement student operations: add, list, search, rename and remove.
- Implement course operations: add and list courses.
- Coordinate changes to `src/main.cpp` and the interactive menu with Jonathan.
- Write and run tests for student and course functionality.
- Build and run the complete project on macOS using Clang and CMake.
- Maintain the `feature/jesse-student-course` branch.
- Commit changes in small, meaningful increments.
- Open Pull Requests into `integration/student-gradebook` when work is ready for review.
- Record actual macOS build and test results for the final report.

## 3. Jonathan — Developer 2 (Windows)

**Main ownership:** Enrolment, assessments, grading, persistence and Windows verification.

Responsibilities:

- Implement and maintain `Assessment`, `GradeScale` and `GradeBook` functionality.
- Implement student enrolment, assessment entry and result calculation.
- Implement course result reports.
- Maintain saving and loading of grade-book data.
- Maintain and explain the reusable `Repository<T>` class template and its use of the STL.
- Write and run tests for enrolment, assessments, grading, results and persistence.
- Build and run the complete project on Windows using MSVC, CMake and CTest.
- Coordinate changes to `src/main.cpp` with Jesse.
- Use a feature branch for development, such as `feature/jonathan-grading-assessments`.
- Commit changes in small, meaningful increments.
- Open Pull Requests into `integration/student-gradebook` when work is ready for review.
- Record actual Windows build and test results for the final report.

## 4. Tavana — Documentation, Requirements and QA Coordinator

**Main ownership:** Non-code deliverables, task planning, manual testing and contribution evidence.

Responsibilities:

- Convert the lecturer's PPOIS requirements into a checklist.
- Help track evidence for each project requirement.
- Help maintain the GitHub Projects task board through coordination with Jesse or Jonathan.
- Prepare and maintain Markdown documentation, including the user guide and architecture explanation.
- Coordinate README updates.
- Prepare manual test scenarios and expected outcomes using `docs/TEST_PLAN.md`.
- Review project changes and provide feedback through the available communication channels.
- Check that changes match their assigned tasks and that appropriate documentation and test evidence are provided.
- Maintain a contribution log with dates, tasks, decisions and evidence.
- Coordinate the final report and presentation/demo script.
- Help ensure the final report accurately describes completed work and actual test results.

Since Tavana does not currently have a GitHub account, Jesse or Jonathan must publish any documentation or QA changes that Tavana prepares. Contributions should be attributed accurately.

## 5. Shared Responsibilities

- Agree on project scope, user requirements and the default A–F grading scale.
- Participate in planning and contribute to the final report.
- Jesse demonstrates the macOS build.
- Jonathan demonstrates the Windows build.
- Tavana coordinates the user-workflow review and documentation.
- All members should understand the project's purpose and be able to explain their own contributions.
- Individual contributions must be supported by available evidence, such as commits, Pull Requests, task-board items, review comments, test records or documentation.

## 6. Git Branching and Collaboration Workflow

The project currently uses the following branch structure:

| Branch | Purpose |
|---|---|
| `feature/jesse-student-course` | Jesse's student and course management development |
| `feature/jonathan-grading-assessments` | Planned feature branch for Jonathan's development |
| `integration/student-gradebook` | Integration branch for combining and reviewing development work |

The confirmed remote branches currently include Jesse's feature branch and the integration branch. Jonathan's feature branch should be created or verified when his development work is ready.

### Workflow

1. Developers work on their own feature branches.
2. Changes are committed in small, meaningful increments.
3. Completed feature work is submitted through Pull Requests.
4. Pull Requests are reviewed before merging into `integration/student-gradebook`.
5. The integrated project is built and tested.
6. Once the project is ready for final release, the team can prepare the final integration into the repository's designated release branch.

Avoid committing directly to the integration branch for normal feature development.

Tavana's documentation and QA contributions can be prepared separately and committed by a team member with GitHub access.

## 7. GitHub Task Board

The GitHub Projects task board should track the following work:

| Task | Responsible Member(s) |
|---|---|
| Confirm project requirements and acceptance checklist | Tavana, with team input |
| Establish CMake build and C++17 conventions | Jesse and Jonathan |
| Implement student management and tests | Jesse |
| Implement course management and tests | Jesse |
| Implement enrolment and assessment entry | Jonathan |
| Implement grading scale and result calculations | Jonathan |
| Implement saving, loading and persistence tests | Jonathan |
| Integrate the menu and validate the complete user workflow | Jesse and Jonathan |
| Build and test on macOS | Jesse |
| Build and test on Windows | Jonathan |
| Prepare manual test cases and review evidence | Tavana |
| Maintain README and architecture/user documentation | Tavana, coordinated through Jesse or Jonathan |
| Review Pull Requests and maintain contribution evidence | Jesse and Jonathan, with Tavana providing review feedback |
| Prepare the final report and presentation | Tavana, with input from all members |

Suggested board columns:

- Planned
- In Progress
- Under Review
- Completed

Task statuses must reflect actual progress rather than the original plan. Only mark work as completed when there is supporting evidence.

## 8. Project Milestones

1. Confirm project requirements, team responsibilities and the initial project structure.
2. Establish the CMake build system and agree on class interfaces.
3. Complete student and course management.
4. Complete enrolment, assessments, grading and persistence.
5. Integrate the application menu and validate the complete workflow.
6. Complete automated unit tests and manual testing.
7. Verify clean builds on macOS and Windows.
8. Complete documentation, contribution evidence, final report and presentation.

## 9. Contribution