
#include "Assessment.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

namespace {
bool isBlank(const std::string& value) {
    return value.empty() ||
           std::all_of(value.begin(), value.end(), [](unsigned char ch) {
               return std::isspace(ch) != 0;
           });
}
}

double Assessment::percentage() const {
    if (isBlank(name)) {
        throw std::invalid_argument(
            "Assessment name cannot be empty."
        );
    }

    if (!std::isfinite(score) || !std::isfinite(maximum) ||
        maximum <= 0 || score < 0 || score > maximum) {
        throw std::invalid_argument(
            "Score must be between zero and a positive maximum score."
        );
    }

    return score / maximum * 100.0;
}
