#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Publication.h"
#include "PublicationSelector.h"
#include "Menu.h"
#include <iostream>

namespace seneca {

	class LibApp {


		bool m_changed = false;
		Menu mainMenu;
		Menu m_exitMenu;
		Menu m_pubTypeMenu; 
	
		char m_filename[256];
	
	Publication* m_ppa[SENECA_LIBRARY_CAPACITY];
	
	int m_nolp;
	int m_llrn;

	bool confirm(const char* message);
	void load();
	void save();
	int search(int n);



	Publication* getPub(int libRef);
	void newPublication();
	void removePublication();
	void checkOutPub();
	void returnPub();
	void printPublication(Publication* pub[], int size, int referenceNumber);
	
	//utility
	int searchAndDisplay(char pubType, bool checkLoanStatus, bool onLoan);
	public:
	LibApp(const char* filename);
	~LibApp();


	void run();




	
	};

}





#endif
