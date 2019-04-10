#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include "Individual.h"

//#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	Individual indiv;

	int amount = 0;
	int changer = -1;
	bool checkSuccess;

	while (true) {
		string parametrs = "-m";
		checkSuccess = true;

		switch (menu(changer)) {
		case 1: {
			parametrs += " s";
		} break;
		case 2: {	
			switch (subMenu(changer)) {
			case 1: {
				parametrs += " l " + std::to_string(amountOfSecondsToTalk(amount));
			} break; //long distance call
			case 2: {
				parametrs += " r " + std::to_string(amountOfSecondsToTalk(amount));
			} break; //local call
			case 0: {
				//return;
			} break;
			default: {
				cout << "What's the hell, dude? Return you back -_-" << endl;
				checkSuccess = false;
				getchar(); getchar();
			} break;
			}
		} break;
		case 3: {
			parametrs += " a " + std::to_string(indiv.inputMoney());
		} break;
		case 0: {
			return 0;
		} break;
		default: {
			cout << "Help yourself!" << endl;
			getchar(); getchar();
			checkSuccess = false;
		}
		}
#ifdef _WIN32
		system("cls");
#elif (__linux__) 
		system("clear");
#endif
		//start daughters' process
		if (checkSuccess) {
			indiv.runChild(parametrs);
		}
	}
}