# Student Grade Book Management System — Architecture

## 1. Project Overview

The Student Grade Book Management System is a C++17 console application designed to manage students, courses, enrolments, assessment scores, grading scales, and academic results.

The application demonstrates object-oriented programming, the Standard Template Library (STL), C++ templates, modular software design, file persistence, and unit testing.

## 2. System Architecture

The system is organised into three main layers.

### 2.1 User Interface Layer

**Main component:** `src/main.cpp`

Responsibilities:
- Display the command-line menu.
- Collect and validate user input.
- Call the appropriate GradeBook operations.
- Display student information, courses, assessment results, and reports.
- Handle errors and communicate results to the user.

### 2.2 Application Logic Layer

**Main component:** `GradeBook`

Responsibilities:
- Coordinate student and course management.
- Manage student enrolments.
- Associate assessments with student-course enrolments.
- Calculate aggregate percentages and letter grades.
- Generate student and course results.
- Save and load application data.
- Enforce the application's business rules.

### 2.3 Data Model and Storage Layer

Main components:
- `Student`
- `Course`
- `Assessment`
- `GradeScale`
- `Repository<T>`

These components represent the application's data and provide reusable functionality for storing, validating, and processing records.

## 3. Class Responsibilities

### 3.1 Student

Represents an individual student.

Responsibilities:
- Store a unique student ID.
- Store the student's name.
- Validate student information.
- Provide access to student information through getters.
- Allow the student's name to be changed through the rename functionality.

### 3.2 Course

Represents an academic course.

Responsibilities:
- Store a unique course code.
- Store the course name.
- Validate course information.
- Provide getters for accessing course information.

### 3.3 Assessment

Represents an assessment associated with a student's enrolment in a course.

Responsibilities:
- Store the assessment name.
- Store the earned score.
- Store the maximum possible score.
- Validate assessment information and score limits.
- Calculate the assessment percentage.

### 3.4 GradeScale

Represents the grading boundaries used to convert percentages into letter grades.

Responsibilities:
- Define minimum percentage boundaries.
- Convert a percentage into its corresponding grade.
- Support configurable grading boundaries.
- Validate grading-scale configuration.

Default grading scale:

| Grade | Percentage |
|---|---:|
| A | 90–100 |
| B | 80–89.99 |
| C | 70–79.99 |
| D | 60–69.99 |
| F | 0–59.99 |

The grading scale can be configured through the application menu.

### 3.5 GradeBook

The central application logic component.

Responsibilities:
- Add, list, search, rename, and remove students.
- Add and list courses.
- Enrol students in courses.
- Prevent duplicate enrolments