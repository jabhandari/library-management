#pragma once
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "Publication.h"

namespace seneca {

    class Book : public Publication {
        char* authorName;

    public:
        Book();

        Book(const Book& other);
        Book& operator=(const Book& other);
        ~Book();

        char type() const;

        std::ostream& write(std::ostream& os) const;

        std::istream& read(std::istream& is);

        void set(int member_id);

        operator bool() const;
    };
}
#endif