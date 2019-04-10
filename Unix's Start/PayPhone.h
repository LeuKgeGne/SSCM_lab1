#ifndef PayPhone_CLASS
#define PayPhone_CLASS
#pragma once
#include <iostream>

class PayPhone
{
public:
	PayPhone(int argc, char* argv[]);
	~PayPhone() {}

	void setMoney(int _money);
	void showMoney();
	inline int getRet() {
		return ret;
	}
private:
	short myTinyCounter(int _amount, int price);
	void makeUpStr(char* str, char* argv[], int* amount);
	void initField();
	//work with file
	void writeToFile();

	int money;
	int ret = 0;
};

#endif