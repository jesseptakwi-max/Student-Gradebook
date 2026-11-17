#pragma once
#include <string>

class Course {
public:
    Course(std::string code, std::string name);
    const std::string& code() const noexcept;
    const std::string& name() const noexcept;
private:
    std::string code_;
    std::string name_;
};
