# Manual test plan

Run these scenarios using the interactive application on both macOS and Windows. Record the tester, date, operating system, actual result and pass/fail outcome. Do not mark a scenario passed until it has actually been performed.

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
| M10 | Record several assessments and view a result | Percentage is total earned points / total possible points |
| M11 | Check grade boundaries at 90, 80, 70, 60 and below 60 | Default A/B/C/D/F bands are applied correctly |
| M12 | Configure a valid custom grading scale | New boundaries are used for later results |
| M13 | Save, close, restart and load the grade book | Previously saved students, courses, enrolments and assessments are restored |
| M14 | View results for a course | Enrolled students with recorded results are displayed |
| M15 | Enter invalid menu choices or malformed values | Program handles input without crashing or corrupting records |

## Build and automated test evidence

On both computers, from the repository root:

```bash
cmake -S . -B build
cmake --build build --config Release
```

macOS:

```bash
ctest --test-dir build --output-on-failure
```

Windows with Visual Studio generator:

```powershell
ctest --test-dir build -C Release --output-on-failure
```

For each platform, record compiler version, CMake version, build output, CTest output and any issues fixed. A successful build on one platform is not evidence that the other platform works.
