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
#include "Menu.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <iomanip>  


namespace seneca {

    void MenuItem::setEmpty()
    {
        m_content = nullptr;
    }
    MenuItem::MenuItem(const char* content)
    {
        if (content)
        {
            m_content = new char[strlen(content) + 1];
            std::strcpy(m_content, content);
        }
        else
        {
            setEmpty();
        }
    }



    MenuItem::operator const char* () const {
        return m_content;
    }

    MenuItem::operator bool() const
    {
        return !(m_content == NULL);
    }

    std::ostream& MenuItem::display(std::ostream& os) const
    {
        if (m_content != nullptr && m_content[0] != '\0')
        {
            os << m_content;
        }
        return os;
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }


    // Menu class

    Menu::Menu(const char* title) : m_title(title) {
        m_noOfItems = 0;
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
            m_items[i] = nullptr;
        }
    }
    std::ostream& Menu::displayTitle(std::ostream& os) const
    {
        m_title.display(os);
        return os;
    }

    Menu& Menu::operator<<(const char* menuitem) {
        if (m_noOfItems < MAX_MENU_ITEMS) {
            m_items[m_noOfItems++] = new MenuItem(menuitem);
        }
        return *this;
    }

    Menu::operator bool() const {
        return m_noOfItems > 0;
    }
    std::ostream& Menu::display(std::ostream& os) const
    {
        displayTitle(os);
        if (m_title) os << "\n";
        for (int i = 0; i < (int)m_noOfItems; i++)
        {
            os << " " << i + 1 << "- ";
            m_items[i]->display(os);
            os << std::endl;
        }
        os << " 0- Exit\n";
        os << "> ";
        return os;
    }
  

    unsigned int Menu::run() const {
        display(std::cout);
        int option = -1;
        bool valid = false;
        do {
            std::cin >> option;
            if (std::cin.fail() || option < 0 || option > int(m_noOfItems)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid Selection, try again: ";
            }
            else {
                valid = true;
            }
        } while (!valid);
        return option;

    }
    Menu::operator int() const {
        return m_noOfItems;
    }

    unsigned int Menu::operator~() const {
        return run();
    }

    Menu::operator unsigned int() const {
        return m_noOfItems;
    }

    std::ostream& operator<<(std::ostream& os, const Menu& m) {
        return m.displayTitle(os);
    }

    const char* Menu::operator[](unsigned int index) const {
        if (index >= 0 && index < (m_noOfItems))
        {
            return m_items[index]->m_content;
        }
        else {
            int validIndex = (index % m_noOfItems + m_noOfItems) % m_noOfItems;
            return m_items[validIndex]->m_content;
        }
    }
    Menu::~Menu() {
        for (unsigned int i = 0; i < m_noOfItems; i++) {
            delete m_items[i];
        }
    }

} // namespace seneca