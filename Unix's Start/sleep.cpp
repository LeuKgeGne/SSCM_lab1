#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

#include "PayPhone.h"

int main(int argc, char* argv[]) {
	if (argv[0] == nullptr) {
		cout << "Helpy yourself[1]" << endl;
	}
	else {
		PayPhone payPh(argc, argv);

		return payPh.getRet();
	}
	
	return -3;
}