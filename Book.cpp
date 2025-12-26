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
#include "Book.h"
#include "Streamable.h"
#include<iostream>
#include<iomanip>
#include<cstring>
#include<string>
using namespace std;
namespace seneca {
    Book::Book() {
        authorName = NULL;
    }

    Book::~Book() {
        delete[] authorName;
    }

    char Book::type() const
    {
        return 'B';
    }

    std::ostream& Book::write(std::ostream& os) const
    {
        Publication::write(os);
        if (conIO(os))
        {
            os << ' ';
            if (strlen(authorName) > SENECA_AUTHOR_WIDTH)
            {
                char temp[SENECA_AUTHOR_WIDTH + 1];
                strncpy(temp, authorName, 15);
                temp[SENECA_AUTHOR_WIDTH] = '\0';
                os << setw(SENECA_AUTHOR_WIDTH) << temp << " |";
            }
            else
            {
                os << setw(SENECA_AUTHOR_WIDTH) << authorName << " |";
            }
        }
        else
        {
            os << '\t' << authorName << std::endl;
        }
        
        return os;
    }

    std::istream& Book::read(std::istream& is)
    {
        char author[256];
        Publication::read(is);
        delete authorName;
        authorName = nullptr;
        if (conIO(is))
        {
            is.ignore();
            cout << "Author: ";
            is.getline(author, 256, '\n');
        }
        else
        {
            is.ignore();
            is.get(author, 256, '\n');
        }
        if (strlen(author) > 256)
        {
            is.setstate(ios::failbit);
        }
        if (is)
        {
            authorName = new char[strlen(author) + 1];
            strcpy(authorName, author);
        }
        return is;
    }

    void Book::set(int member_id)
    {

        Publication::resetDate();
        Publication::set(member_id);
    }

    Book::operator bool() const
    {
        return authorName && strlen(authorName) > 0 && Publication::operator bool();
    }

    Book::Book(const Book& other) : Publication(other) {

        authorName = NULL;
        if (other.authorName) {
            authorName = new char[strlen(other.authorName) + 1];
            strcpy(authorName, other.authorName);
        }
    }


    Book& Book::operator=(const Book& other) {
        if (this != &other) {
            Publication::operator=(other);

            delete[] authorName;
            authorName = nullptr;

            if (other.authorName) {
                authorName = new char[strlen(other.authorName) + 1];
                strcpy(authorName, other.authorName);
            }
        }
        return *this;
    }
}