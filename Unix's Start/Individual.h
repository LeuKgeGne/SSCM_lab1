#ifndef INDIVIDUAL_CLASS
#define INDIVIDUAL_CLASS
#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Individual
{
public:
	Individual() {}
	~Individual() {}
	unsigned int inputMoney();
	void runChild(std::string &par) const;
	char* workWithMoney(std::string par, char* tempStr) const;
	void analyseOfResult(int number) const;
};

#endif