#pragma once
#include <string>
#include <vector>

struct GradeBand {
    double minimum;
    std::string letter;
};

class GradeScale {
public:
    GradeScale();
    explicit GradeScale(std::vector<GradeBand> bands);
    std::string gradeFor(double percentage) const;
    void setBands(std::vector<GradeBand> bands);
    const std::vector<GradeBand>& bands() const noexcept;
private:
    std::vector<GradeBand> bands_;
};
