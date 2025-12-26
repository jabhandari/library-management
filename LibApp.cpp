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
#define _CET_SECURE_NO_WARNINGS
#include "LibApp.h"
#include<limits>
#include<fstream>
#include<iostream>
#include<iomanip>
#include <string.h>
#include"Book.h"
using namespace std;

namespace seneca {

	LibApp::LibApp(const char* file)
		:m_changed(),
		mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_pubTypeMenu("Choose the type of publication:")
	{
		m_changed = false;
		strcpy(m_filename, file);
		m_nolp = 0;
		m_llrn = -1;
		mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_pubTypeMenu << "Book" << "Publication";
		load();


	}



	void seneca::LibApp::load()
	{
		cout << "Loading Data" << endl;
		ifstream infile(m_filename);
		char type;

		while (infile >> type) {
			infile.ignore();
			Publication* pub = NULL;
			if (type == 'B') {
				pub = new Book();

			}
			else {
				pub = new Publication();
			}
			infile >> *pub;
			infile.ignore();
			m_ppa[m_nolp++] = pub;
			if (pub->getRef() > m_llrn) {
				m_llrn = pub->getRef();
			}
		}
	}


	void LibApp::save()
	{
		cout << "Saving Data" << endl;
		ofstream outfile(m_filename);
		if (outfile) {
			for (int i = 0; i < m_nolp; ++i) {
				if (m_ppa[i]->getRef() != 0)
				{
					outfile << *m_ppa[i];
				}
			}
		}
	}


	//utility function
	int LibApp::searchAndDisplay(char pubType, bool checkLoanStatus, bool onLoan) {
		int result = 0;
		PublicationSelector ps("Select one of the following found matches:", 15);
		std::cout << "Publication Title: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		char filename[256];
		std::cin.getline(filename, 256);

		char type{};
		std::ifstream infile(m_filename);

		for (int i = 0; i < m_nolp; i++) {
			infile >> type;
			infile.ignore();
			if (infile) {
				bool match = m_ppa[i]->type() == pubType && strstr(*m_ppa[i], filename) && m_ppa[i]->getRef() != 0;
				if (checkLoanStatus) {
					match = match && (m_ppa[i]->onLoan() == onLoan);
				}
				if (match) {
					ps << m_ppa[i];
				}
			}
		}

		if (ps) {
			ps.sort();
			int ref = ps.run();
			if (ref) {
				std::cout << *getPub(ref) << std::endl;
				result = ref;
			}
			else {
				std::cout << "Aborted!" << std::endl;
			}
		}
		else {
			std::cout << "No matches found!" << std::endl;
		}
		return result;
	}

	int LibApp::search(int n)
	{
		int res = 0;
		int selection = -1;

		if (n == 1 || n == 2 || n == 3) {
			selection = m_pubTypeMenu.run();
			switch (selection) {
			case 1: // Books
				res = searchAndDisplay('B', n > 1, n == 2);
				break;
			case 2: // Periodicals
				res = searchAndDisplay('P', n > 1, n == 2);
				break;
			case 0: // Aborted
			default:
				std::cout << "Aborted!" << std::endl;
				break;
			}
		}

		return res;
	}


	void LibApp::newPublication()
	{
		if (m_nolp >= SENECA_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			return;
		}

		cout << "Adding new publication to the library" << endl;
		int selection = m_pubTypeMenu.run();
		if (selection == 0) {
			cout << "Aborted!" << endl;
			return;
		}
		Publication* pub = nullptr;
		if (selection == 1) {
			pub = new Book;
		}
		else if (selection == 2) {
			pub = new Publication;
		}
		if (pub) {
			cin >> *pub;
			if (&pub==NULL) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Aborted!" << endl;
				delete pub;
				return;
			}
			if (confirm("Add this publication to the library?"))
			{
				m_ppa[m_nolp] = pub;
				pub->setRef(m_llrn + 1);
				m_llrn++;
				m_nolp++;
				m_changed = true;
				cout << "Publication added" << endl;
			}
		}
	}
	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		int ref = 0;
		ref = search(1);

		if (ref) {
			if (confirm("Remove this publication from the library?")) {
				m_changed = true;
				cout << "Publication removed" << endl;
				Publication* pub = getPub(ref);
				pub->setRef(0);

			}
		}


	}
	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;
		int ref = 0;
		ref = search(3);
		if (ref) {
			if (confirm("Check out publication?")) {
				int memID;
				cout << "Enter Membership number: ";
				cin >> memID;
				while (memID < 10000 || memID > 99999) {
					cout << "Invalid membership number, try again: ";
					cin >> memID;
				}
				if (memID) {
					getPub(ref)->set(memID);
					m_changed = true;
					cout << "Publication checked out" << endl;

				}
			}

		}

	}
	void LibApp::returnPub()
	{
		cout << "Return publication to the library" << endl;
		int ref = 0;
		ref = search(2);
		if (ref) {
			if (confirm("Return Publication?")) {

				Date today;
				int daysOnLoan = today - getPub(ref)->checkoutDate();
				if (daysOnLoan > 15) {
					double penalty = ((daysOnLoan)-15) * 0.50;
					cout << std::fixed << setprecision(2);
					cout << "Please pay $" << penalty << " penalty for being " << ((daysOnLoan)-15) << " days late!" << endl;
				}

				getPub(ref)->set(0);
				m_changed = true;
				cout << "Publication returned" << endl;
			}
		}

	}

	


void LibApp::printPublication(Publication* pub[], int size, int referenceNumber)
{
	for (int i = 0; i < size; i++)
	{
		if (referenceNumber == pub[i]->getRef()) {
			cout << *pub[i] << endl;
			break;
		}
	}
}


Publication* LibApp::getPub(int libRef) {
	for (int i = 0; i < m_nolp; i++) {
		if (m_ppa[i]->getRef() == libRef) {
			return m_ppa[i];
		}
	}
	return nullptr;
}

void LibApp::run()
{
	bool done = true;
	int selection = -1;
	do {
		selection = mainMenu.run();
		if (selection == 1) {
			newPublication();
			std::cout << std::endl;
		}
		else if (selection == 2) {
			removePublication();
			std::cout << std::endl;
		}
		else if (selection == 3) {
			checkOutPub();
			std::cout << std::endl;
		}
		else if (selection == 4) {
			returnPub();
			std::cout << std::endl;
		}
		else {
			if (m_changed) {
				int i = m_exitMenu.run();
				switch (i) {
				case 1:
					save();
					done = false;
					break;
				case 2:
					continue;
				case 0:					
					if (confirm("This will discard all the changes are you sure?")) {
							done = false;
					}
					break;
				}
			}
			else {
				done = false;
			}
			break;
		}
	} while (done);
	std::cout << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Thanks for using Seneca Library Application" << std::endl;
}
bool LibApp::confirm(const char* message) {
	char response;
	
	cout << message << endl;
	cout << " 1- Yes" << endl;
	cout << " 0- Exit" << endl;
	cout << "> ";
	std::cin >> response;
	return response;
}

LibApp::~LibApp()
{
	for (int i = 0; i < m_nolp; i++)
	{
		delete m_ppa[i];
	}
}

}


