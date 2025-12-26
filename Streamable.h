#pragma once
#pragma once
#ifndef STREAMABLE_H
#define STREAMABLE_H

#include <iostream>

class Streamable
{
    //create interface streamable 
public:
    virtual ~Streamable() = 0; // Pure virtual destructor

    virtual std::ostream& write(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual bool conIO(std::ios& io) const = 0;
    virtual operator bool() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Streamable& s);
std::istream& operator>>(std::istream& is, Streamable& s);

#endif // STREAMABLE_H
