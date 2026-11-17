#include "Course.h"
#include <stdexcept>
#include <utility>

Course::Course(std::string code, std::string name) : code_(std::move(code)), name_(std::move(name)) {
    if (code_.empty() || name_.empty()) throw std::invalid_argument("Course code and name cannot be empty.");
}
const std::string& Course::code() const noexcept { return code_; }
const std::string& Course::name() const noexcept { return name_; }
