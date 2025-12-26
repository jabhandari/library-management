/*******************************************************************

 Name        : Juhi Abhay Bhandari
 Email       : jabhandari@myseneca.ca
 Student ID  : 106758238
 Date        : 07-1-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

#include "Streamable.h"
#include "Publication.h"

using namespace std;

namespace seneca
{

	Publication::Publication()
	{
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		m_date = Date();
	}

	Publication::Publication(const Publication& pub)
	{
		m_title = nullptr;
		*this = pub;
	}

	Publication& Publication::operator=(const Publication& pub)
	{
		if (this != &pub)
		{
			delete[] m_title;
			m_title = nullptr;

			if (pub.m_title)
			{
				m_title = new char[strlen(pub.m_title) + 1];
				strcpy(m_title, pub.m_title);

			}
			strcpy(m_shelfId, pub.m_shelfId);
			set(pub.m_membership);
			setRef(pub.m_libRef);
			m_date = pub.m_date;

		}
		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
	}

	//methods
	void Publication::set(int member_id)
	{
		m_membership = member_id;
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date = Date();
	}

	//Queries
	char Publication::type()const
	{
		return 'P';
	}

	bool Publication::onLoan()const
	{

		return m_membership;
	}

	Date Publication::checkoutDate()const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title)const
	{

		return strstr(m_title, title) != nullptr;
	}

	Publication::operator const char* ()const
	{
		return m_title;
	}

	int Publication::getRef()const
	{
		return m_libRef;
	}

	bool Publication::conIO(std::ios& io)const
	{
		return &io == &cin || &io == &cout;
	}

	std::ostream& Publication::write(std::ostream& os) const
	{

		/*if (*this)
		{*/
		if (conIO(os))
		{
			os << "| " << setw(4) << m_shelfId;
			os << " | ";
			if (strlen(m_title) > SENECA_TITLE_WIDTH)
			{
				char temp[SENECA_TITLE_WIDTH + 1];
				strncpy(temp, m_title, 30);
				temp[SENECA_TITLE_WIDTH] = '\0';
				os << setfill('.') << setw(30) << left << temp;
			}
			else
			{
				os << setfill('.') << setw(30) << left << m_title;
			}
			os << " | " << setfill(' ');
			if (onLoan())
			{
				os << setw(5) << m_membership << " | ";
			}
			else
			{
				os << setw(5) << " N/A " << " | ";
			}
			os << m_date;
			cout << " |";
		}
		else
		{
			os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t';
			os << m_date;
			if (type() == 'P')
			{
				os << endl;
			}
		}
		//}
		return os;


	}
	std::istream& Publication::read(std::istream& istr)
	{

		delete m_title;
		string ShelfId;
		string Title;
		int LibRef = -1;
		int Membership = 0;
		Date date;

		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr >> ShelfId;
			if (ShelfId.length() != 4)
			{
				istr.setstate(ios::failbit);
			}
			cout << "Title: ";
			istr.ignore();
			getline(istr, Title, '\n');
			cout << "Date: ";
			istr >> date;
			if (date.errCode() != 0)
			{
				istr.setstate(ios::failbit);
			}
		}
		else
		{
			istr >> LibRef;
			istr.ignore();
			getline(istr, ShelfId, '\t');
			getline(istr, Title, '\t');
			istr >> Membership;
			istr >> date;
			if (date.errCode() != 0)
			{
				istr.setstate(ios::failbit);
			}
		}
		if (istr)
		{
			m_libRef = LibRef;
			strcpy(m_shelfId, ShelfId.c_str());
			m_title = new char[Title.length() + 1];
			strcpy(m_title, Title.c_str());
			m_membership = Membership;
			m_date = date;
		}
		else
		{
			m_title = nullptr;
			m_shelfId[0] = '\0';
			m_membership = 0;
			m_libRef = -1;
			m_date = Date();
		}
		return istr;
	}


	Publication::operator bool() const
	{
		return m_title != nullptr && m_shelfId[0] != '\0';
	}

}