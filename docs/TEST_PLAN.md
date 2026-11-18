# Student Grade Book Management System — Test Plan

## 1. Purpose

This document describes the manual and automated testing procedures for the Student Grade Book Management System.

Testing is intended to verify that the application operates correctly, validates user input, enforces business rules, calculates academic results accurately, and preserves data through file persistence.

Manual testing should be performed on macOS and Windows where possible.

Each test must be marked as passed or failed only after it has actually been executed.

## 2. Manual Test Scenarios

Run the following scenarios using the interactive application.

| ID | Scenario | Expected result |
|---|---|---|
| M01 | Add a student with a new ID and name | Student is stored and appears in the student list |
| M02 | Add another student using an existing ID | Duplicate ID is rejected with a clear message |
| M03 | Search for an existing and a missing student ID | Existing student is shown; missing ID is handled safely |
| M04 | Rename a student | Updated name appears in later views |
| M05 | Add a course with a new course code | Course is stored and appears in the course list |
| M06 | Enrol an existing student in an existing course | Enrolment succeeds |
| M07 | Enrol an unknown student or course | Invalid enrolment is rejected safely |
| M08 | Enter an assessment with a valid raw score and maximum | Assessment is stored |
| M09 | Enter a negative score or a score above the maximum | Invalid score is rejected |
| M10 | Record several assessments and view a result | Percentage is total earned points divided by total possible points, multiplied by 100 |
| M11 | Check grade boundaries at 90, 80, 70, 60 and below 60 | Default A/B/C/D/F bands are applied correctly |
| M12 | Configure a valid custom grading scale | New boundaries are used for later results |
| M13 | Save, close, restart and load the grade book | Previously saved students, courses, enrolments and assessments are restored |
| M14 | View results for a course | Enrolled students with recorded results are displayed |
| M15 | Enter invalid menu choices or malformed values | Program handles input without crashing or corrupting records |
| M16 | Enrol the same student in the same course twice | Second enrolment is rejected with a clear duplicate-enrolment error |
| M17 | Attempt to load a corrupted or invalid save file | Loading fails safely and existing in-memory data is preserved |
| M18 | Start the application when no save file exists | Application starts with a new empty grade book |
| M19 | Start the application with a valid existing save file | Saved data is loaded successfully |

## 3. Automated Unit Testing

Automated unit tests are implemented in:

`tests/test_main.cpp`

The tests cover the following areas:

### 3.1 Student Tests
- Student creation.
- Empty and blank student IDs.
- Empty and blank student names.
- Renaming students.
- Invalid rename attempts.

### 3.2 Course Tests
- Course creation.
- Course code validation.
- Course name validation.

### 3.3 Assessment Tests
- Assessment percentage calculation.
- Empty assessment names.
- Negative scores.
- Scores exceeding the maximum.
- Zero maximum scores.
- Invalid floating-point values.

### 3.4 GradeScale Tests
- Default grade boundaries.
- Custom grading scales.
- Missing zero boundary.
- Duplicate boundaries.
- Invalid percentages.
- Invalid grade labels.

### 3.5 Repository Tests
- Adding records.
- Finding records.
- Removing records.
- Rejecting duplicate identifiers.

### 3.6 GradeBook Tests
- Adding, finding, renaming and removing students.
- Rejecting duplicate student IDs.
- Rejecting enrolments for unknown students or courses.
- Rejecting duplicate enrolments.
- Rejecting assessments for unenrolled students.
- Calculating aggregate results.
- Generating course results.
- Handling invalid course reports.

### 3.7 Persistence Tests
- Saving and loading data.
- Preserving floating-point precision.
- Handling failed loading.
- Rejecting invalid saved data.
- Preserving existing data after failed loading.

## 4. Build and Automated Test Procedures

Perform the following procedures from the repository root.

### 4.1 Configure the project

```bash
cmake -S . -B build
```

### 4.2 Build the project

macOS and Linux:

```bash
cmake --build build
```

Windows:

```powershell
cmake --build build --config Release
```

### 4.3 Run automated tests

macOS and Linux:

```bash
ctest --test-dir build --output-on-failure
```

Windows:

```powershell
ctest --test-dir build -C Release --output-on-failure
```

A successful test run should report that all registered tests passed.

## 5. Test Evidence and Results Recording

For each platform, record:

- Tester name.
- Test date.
- Operating system and version.
- C++ compiler and version.
- CMake version.
- Build result.
- CTest result.
- Manual test results.
- Problems encountered and corrections made.

Use the following template:

| Test ID | Operating system | Actual result | Status | Notes |
|---|---|---|---|---|
| M01 |  |  | Not tested |  |
| M02 |  |  | Not tested |  |
| M03 |  |  | Not tested |  |
| M04 |  |  | Not tested |  |
| M05 |  |  | Not tested |  |
| M06 |  |  | Not tested |  |
| M07 |  |  | Not tested |  |
| M08 |  |  | Not tested |  |
| M09 |  |  | Not tested |  |
| M10 |  |  | Not tested |  |
| M11 |  |  | Not tested |  |
| M12 |  |  | Not tested |  |
| M13 |  |  | Not tested |  |
| M14 |  |  | Not tested |  |
| M15 |  |  | Not tested |  |
| M16 |  |  | Not tested |  |
| M17 |  |  | Not tested |  |
| M18 |  |  | Not tested |  |
| M19 |  |  | Not tested |  |

Use only these status values:

- **Passed** — the actual result matches the expected result.
- **Failed** — the actual result does not match the expected result.
- **Not tested** — the scenario has not yet been executed.

## 6. Platform Verification

### macOS

Record the results of:
- CMake configuration.
- Compilation.
- Automated unit testing.
- Manual application testing.
- Data saving and loading.

### Windows

Record the results of:
- CMake configuration.
- Compilation using the selected Windows generator.
- Automated unit testing.
- Manual application testing.
- Data saving and loading.

A successful build on macOS does not establish that the application works on Windows. Both platforms must be tested independently.

## 7. Final Testing Assessment

The project is considered ready for submission when:

- The application builds successfully.
- Automated unit tests pass.
- Core manual scenarios have been executed.
- Invalid inputs are handled safely.
- Duplicate enrolments are rejected.
- Results and grade calculations are correct.
- Saving and loading work correctly.
- Test evidence is recorded accurately for each verified platform.

Any untested platform or scenario must be identified clearly in the final report.
