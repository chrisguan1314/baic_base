#pragma once

namespace structure
{
class Timestamp
{
public:
    Timestamp() = default;
    Timestamp(const Timestamp&) = default;
    Timestamp& operator=(const Timestamp&) = default;
    Timestamp(Timestamp&&) = default;
    Timestamp& operator=(Timestamp&&) = default;
    ~Timestamp() = default;
};

};
