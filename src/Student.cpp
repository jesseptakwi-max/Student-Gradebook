#include "Student.h"
#include <stdexcept>
#include <utility>

Student::Student(std::string id, std::string name) : id_(std::move(id)), name_(std::move(name)) {
    if (id_.empty()) throw std::invalid_argument("Student ID cannot be empty.");
    if (name_.empty()) throw std::invalid_argument("Student name cannot be empty.");
}
const std::string& Student::id() const noexcept { return id_; }
const std::string& Student::name() const noexcept { return name_; }
void Student::setName(const std::string& name) {
    if (name.empty()) throw std::invalid_argument("Student name cannot be empty.");
    name_ = name;
}
