#pragma once

#include <regex/regex.hpp>
#include <string>

namespace GR {

class Terminal {
public:
    explicit Terminal(std::string name, Regex regex)
        : m_name(name)
        , m_regex(std::move(regex)) {}

    std::string const& name() const { return m_name; }
    Regex const& regex() const { return m_regex; }

private:
    std::string m_name;
    Regex m_regex;
};

} // namespace GR
