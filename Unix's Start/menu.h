#pragma once
#include <iostream>
using std::cin;

int menu(int changer) {
	printf("1. Check balance\n");
	printf("2. Have a call\n");
	printf("3. Add some money\n");
	printf("0. Just get out");
	printf("\nYour choice:\n");
	cin >> changer;
	return changer;
}

int subMenu(int changer) {
	printf("\n1. Long distance call (10 $ for second)\n");
	printf("2. local call (5 $ for second)\n");
	printf("0. go back\n");
	cin >> changer;
	return changer;
}

int amountOfSecondsToTalk(int amount) {
	printf("\nEnter quantity of seconds you'd like to talk:\n");
	cin >> amount;
	return amount;
}