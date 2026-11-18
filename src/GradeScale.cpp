
#include "GradeScale.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <utility>

namespace {
bool isBlank(const std::string& value) {
    return value.empty() ||
           std::all_of(value.begin(), value.end(), [](unsigned char ch) {
               return std::isspace(ch) != 0;
           });
}
}

GradeScale::GradeScale()
    : bands_{{90, "A"}, {80, "B"}, {70, "C"}, {60, "D"}, {0, "F"}} {
}

GradeScale::GradeScale(std::vector<GradeBand> bands) {
    setBands(std::move(bands));
}

void GradeScale::setBands(std::vector<GradeBand> bands) {
    if (bands.empty()) {
        throw std::invalid_argument(
            "A grading scale needs at least one grade band."
        );
    }

    for (const auto& band : bands) {
        if (!std::isfinite(band.minimum) ||
            band.minimum < 0 ||
            band.minimum > 100 ||
            isBlank(band.letter)) {
            throw std::invalid_argument(
                "Grade boundaries must be between 0 and 100 "
                "and labels cannot be empty."
            );
        }
    }

    std::sort(
        bands.begin(),
        bands.end(),
        [](const GradeBand& a, const GradeBand& b) {
            return a.minimum > b.minimum;
        }
    );

    if (bands.back().minimum != 0) {
        throw std::invalid_argument(
            "The grading scale must include a 0 percent boundary."
        );
    }

    for (std::size_t i = 1; i < bands.size(); ++i) {
        if (bands[i - 1].minimum == bands[i].minimum) {
            throw std::invalid_argument(
                "Grade boundaries must be unique."
            );
        }
    }

    bands_ = std::move(bands);
}

std::string GradeScale::gradeFor(double percentage) const {
    if (!std::isfinite(percentage) ||
        percentage < 0 ||
        percentage > 100) {
        throw std::out_of_range(
            "Percentage must be between 0 and 100."
        );
    }

    for (const auto& band : bands_) {
        if (percentage >= band.minimum) {
            return band.letter;
        }
    }

    return bands_.back().letter;
}

const std::vector<GradeBand>& GradeScale::bands() const noexcept {
    return bands_;
}
