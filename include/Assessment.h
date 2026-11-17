#pragma once
#include <string>

struct Assessment {
    std::string name;
    double score{};
    double maximum{};
    double percentage() const;
};
