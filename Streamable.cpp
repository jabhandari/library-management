/*/////////////////////////////////////////////////////////////////////////
Full Name  : Juhi Abhay Bhandari
Student ID#: 106758238
Email      : jabhandari@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS
#include "Streamable.h"
#include "Lib.h"
#include "Date.h"
#include "Streamable.h"




Streamable::~Streamable() {

}

//extraction operator overload
std::ostream& operator<<(std::ostream& os, const Streamable& s)
{
    if (s)
    {
        s.write(os);
    }
    return os;
}

//insertion operator overload
std::istream& operator>>(std::istream& is, Streamable& s)
{
    return s.read(is);
}

