#pragma once
#include <string>

class Student {
public:
    Student(std::string id, std::string name);
    const std::string& id() const noexcept;
    const std::string& name() const noexcept;
    void setName(const std::string& name);
private:
    std::string id_;
    std::string name_;
};
