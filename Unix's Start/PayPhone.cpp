#define _CRT_SECURE_NO_WARNINGS
#include "PayPhone.h"
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <time.h>

#elif(defined(__linux__) || defined(__unix__))
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <ncurses.h>
#endif

#define LDC_PRICE 10
#define LC_PRICE 5
using std::string;
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;

PayPhone::PayPhone(int argc, char * argv[])
{
	initField();
	int amount = 0;
	char* str = new char[sizeof(argv[1]) + sizeof(argv[2])];
	str[0] = '\0';
	makeUpStr(str, argv, &amount);
	if (argv <= 0) {
		cout << "Everything is bad ;(" << endl;
		return;
	}
	//add money into payphone
	else if (str[3] == 'a') {
		this->setMoney(amount);
		cout << "\n_____I've got: " << amount << endl;
		getchar();
	}
	//show money that we've got into payphone
	else if (str[3] == 's') {
		this->showMoney();
		getchar();
	}
	//make a long distance call
	else if (str[3] == 'l') {
		if (this->myTinyCounter(amount, LDC_PRICE) == 3) {
			return;
		}
		else {
			//cout << "Talking..\n(long distance call)" << endl;
			#ifdef _WIN32
			Sleep(amount*1000);
			#elif (__linux__)
			napms(amount*1000);
			#endif
			// cout << "Time's up!" << endl;
			// cout << "left in machine: " << money << endl;
			// cout << "Enter a key..." << endl;
			// getchar();
		}
	}
	//make a local call
	else if (str[3] == 'r') {
		if (this->myTinyCounter(amount, LC_PRICE) == 3) {
			return;
		}
		else {
			// cout << "Talking..\n(local call)" << endl;
			#ifdef _WIN32
			Sleep(amount*1000);
			#elif (__linux__)
			napms(amount*1000);
			#endif
			// cout << "Time's up!" << endl;
			// cout << "left in machine: " << money << endl;
			// cout << "Enter a key..." << endl;
			// getchar();
		}
	}
	//if we've got wrong command
	else {
		cout << "\nWrong command!" << endl;
		this->ret = -2;
		getchar();
	}
	free(str);
}

void PayPhone::setMoney(int _money)
{	
		this->money += _money;
		writeToFile();
}

void PayPhone::showMoney()
{
	cout << "You've got " << this->money << " , dear friend!" << endl;
}

void PayPhone::makeUpStr(char* str, char* argv[], int* amount)
{
#ifdef _WIN32
	strcat(str, argv[1]);
	strcat(str, " ");
	strcat(str, argv[2]);
	if (argv[3] != nullptr) {
		*amount = atoi(argv[3]);
	}
#elif (__linux__)
	int i = 0;
	while(i < sizeof(argv[0])) {
		str[i] = argv[0][i];
		i++;
	}
	if (argv[1] != nullptr) {
		*amount = atoi(argv[1]);
	}
#endif
}

short PayPhone::myTinyCounter(int _amount, int price)
{
	int value;
	value = price * _amount;
	if (value > this->money) {
		// cout << "Add " << value - this->money << " $ to make the call" << endl;
		// getchar();
		this->ret = -1;
		return 3;
	} 
	this->money -= value;
	writeToFile();
	return 2;
}

void PayPhone::initField()
{
	std::ifstream f_ptr("information.txt");

	if(!f_ptr) {
		cout << "Wrong pointer!" << endl;
		getchar();
		return; //for a while
	}
	else {
		f_ptr >> this->money;
	}
}

void PayPhone::writeToFile()
{
	string path = "information.txt";
	fstream f_ptr;

	f_ptr.open(path, fstream::out);

	if (!f_ptr.is_open()) {
		cout << "File doesn't open" << endl;
		getchar();
		return;
	}
	else {
		f_ptr << this->money;		
	}
	f_ptr.close();
}
