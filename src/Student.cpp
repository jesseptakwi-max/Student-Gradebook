
#include "Student.h"

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

Student::Student(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
    if (isBlank(id_)) {
        throw std::invalid_argument("Student ID cannot be empty.");
    }

    if (isBlank(name_)) {
        throw std::invalid_argument("Student name cannot be empty.");
    }
}

const std::string& Student::id() const noexcept {
    return id_;
}

const std::string& Student::name() const noexcept {
    return name_;
}

void Student::setName(const std::string& name) {
    if (isBlank(name)) {
        throw std::invalid_argument("Student name cannot be empty.");
    }

    name_ = name;
}
