#include "Assessment.h"
#include <stdexcept>

double Assessment::percentage() const {
    if (name.empty()) throw std::invalid_argument("Assessment name cannot be empty.");
    if (maximum <= 0 || score < 0 || score > maximum) throw std::invalid_argument("Score must be between zero and the positive maximum score.");
    return score / maximum * 100.0;
}
