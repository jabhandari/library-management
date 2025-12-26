#pragma once
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
#ifndef MENU_H
#define MENU_H

#include <iostream>

#define MAX_MENU_ITEMS 20

namespace seneca {

    class Menu;

    class MenuItem 
    {

        char* m_content;

        void setEmpty();

        MenuItem(const char* content = nullptr);

        ~MenuItem();

        operator bool() const;

        operator const char* () const;

        std::ostream& display(std::ostream& os) const;

        friend class Menu;

    };


    class Menu {
        MenuItem m_title;
        MenuItem* m_items[MAX_MENU_ITEMS];
        unsigned int m_noOfItems;

    public:

        Menu(const char* title = nullptr);

        ~Menu();

        Menu(const Menu&) = delete;

        Menu& operator=(const Menu&) = delete;

        std::ostream& displayTitle(std::ostream& os) const;
        std::ostream& display(std::ostream& os) const;


        unsigned int operator~() const;
        const char* operator[](unsigned int index) const;
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        unsigned int run() const;

        Menu& operator<<(const char* menuItemContent);

        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);


    };


    std::ostream& operator<<(std::ostream& os, const Menu& menu);


} // namespace seneca
#endif // MENU_H