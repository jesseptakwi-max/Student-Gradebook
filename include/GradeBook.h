#pragma once
#include "Assessment.h"
#include "Course.h"
#include "GradeScale.h"
#include "Repository.h"
#include "Student.h"
#include <map>
#include <string>
#include <vector>

struct ResultSummary {
    double percentage;
    std::string letter;
};

class GradeBook {
public:
    void addStudent(const std::string& id, const std::string& name);
    void renameStudent(const std::string& id, const std::string& newName);
    bool removeStudent(const std::string& id);
    const Student* findStudent(const std::string& id) const;
    const std::vector<Student>& students() const noexcept;

    void addCourse(const std::string& code, const std::string& name);
    const Course* findCourse(const std::string& code) const;
    const std::vector<Course>& courses() const noexcept;
    void enrol(const std::string& studentId, const std::string& courseCode);
    void addAssessment(const std::string& studentId, const std::string& courseCode,
                       const std::string& assessmentName, double score, double maximum);
    ResultSummary result(const std::string& studentId, const std::string& courseCode) const;
    std::vector<std::pair<std::string, ResultSummary>> courseResults(const std::string& courseCode) const;

    GradeScale& gradingScale() noexcept;
    const GradeScale& gradingScale() const noexcept;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
private:
    using AssessmentList = std::vector<Assessment>;
    using CourseAssessments = std::map<std::string, AssessmentList>;
    Repository<Student> students_;
    Repository<Course> courses_;
    std::map<std::string, CourseAssessments> records_;
    GradeScale scale_;
};
