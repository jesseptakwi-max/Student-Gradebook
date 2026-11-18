
#include "Course.h"

#include <algorithm>
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

Course::Course(std::string code, std::string name)
    : code_(std::move(code)), name_(std::move(name)) {
    if (isBlank(code_) || isBlank(name_)) {
        throw std::invalid_argument(
            "Course code and name cannot be empty."
        );
    }
}

const std::string& Course::code() const noexcept {
    return code_;
}

const std::string& Course::name() const noexcept {
    return name_;
}
