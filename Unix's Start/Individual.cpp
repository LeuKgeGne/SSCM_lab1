#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <Windows.h>
#include <time.h>

#elif(defined(__linux__) || defined(__unix__))
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <ncurses.h>
#endif

#include "Individual.h"


unsigned int Individual::inputMoney()
{
	int someMoney = 0;
	cout << "Put your money in:" << endl;
	cin >> someMoney;
	return someMoney;
}

void Individual::runChild(std::string & par) const
{
	int changer;
#ifdef _WIN32
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;

	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));

	if (!CreateProcess(NULL,
		(LPSTR)(std::string("Z:\\SSCM\\Start\\Debug\\sleep.exe ") + par).c_str(),
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&startupInfo,
		&processInfo)) {
		cout << "We're not able to create any process :(" << endl;
		cout << "Enter a key.." << endl;
		getchar();
		return;
	}

	while (WaitForSingleObject(processInfo.hProcess, 800)) {
		system("cls");
		time_t t = time(0);
		tm * now = localtime(&t);

		cout << "Time: " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << endl;
	}

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

#elif (__linux__)
	pid_t pid = fork();
	char *tempStr;
	int st;

	if (pid < 0)
	{
		cout << "No chances to turn on this machine" << endl;
		return;
	}
	else if (pid == 0) {
		// if (execlp("./run.sh", "./", (std::string("./child.out ") + par).c_str(), NULL) == -1)
		// // if (execlp("./child_e", "./",(std::string("./child_e ") + str).c_str(), NULL) == -1)
		// printw("Error.");
		// getchar(); getchar();
		if(par.size() > 4) {
			tempStr = workWithMoney(par, tempStr);
			execlp("./child.out", par.c_str(), tempStr, NULL);
		}  
		else {
			execlp("./child.out", par.c_str(), NULL);
		}
	}

	bool flag = true;
	
	if(par[3] == 'r' || par[3] == 'l') {
		while (flag)
		{
			std::system("clear");
			time_t t = time(0);
			cout << ctime(&t) << endl;
			//cout << "Talking.." << endl;

			if (waitpid(pid, &st, WNOHANG) > 0)
			flag = false;

			napms(50);
		}
		if(st == 0) {
			cout << "Time's up!" << endl;
			//cout << "left in machine: " << money << endl;
			cout << "Enter a key..." << endl;
			getchar();
		}
	} else {
		while(true) {
			if (waitpid(pid, &st, WNOHANG) > 0)
			break;

			napms(50);
		}
	}
	// while(true) {
	// 	if(waitpid(pid, &st, WNOHANG) > 0) {
	// 		break;
	// 	}
	// 	napms(50);
	// }
	#ifdef _WIN32
	GetExitCodeProcess(processInfo.hProcess, (LPDWORD)&changer);
	#elif (__linux__)
	changer = WEXITSTATUS(st);
	#endif
	analyseOfResult((int)changer);
	system("clear");
#else 
	cout << "Recompile it in Unix" << endl;
#endif
}

void Individual::analyseOfResult(int number)  const {
	#ifdef __linux__
	if(number != 0) {
		number -= 256;
	}
	#endif
	switch (number) {
	case 0: {
		cout << "Child's returned correctly" << endl;
		napms(2000);
		//getchar();
	} break;
	case -1: {
		cout << "Not enough money(parent)" << endl;
		//getchar();
		napms(2000);
	} break;
	case -2: {
		cout << "Was wrong input(parent)" << endl;
		//getchar();
		napms(2000);
	} break;
		case -3: {
		cout << "Was wrong smth in sleep's start!" << endl;
		//getchar();
		napms(2000);
	} break;
	}
}

char* Individual::workWithMoney(std::string par, char* tempStr) const {
	tempStr = new char[par.size() - 4];
	int j = 0;
	for(int i = 5; par[i] != '\0'; i++, j++) {
	tempStr[j] = par[i];
	}
	tempStr[j] = '\0';
	return tempStr;
}
