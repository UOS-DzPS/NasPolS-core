#include <iostream>
#include <clocale>
#include <cstdlib>

#include <inc/polish.h>
#include <inc/unit_test.h>

int main(void)
{
	// Do not touch this code. This part sets the locale.
	std::setlocale(LC_ALL, "pl_PL.UTF-8");
	system("chcp 65001 > nul");
	// Do not touch this code. This part sets the locale.

	AnalyzerUnitTest();
	
	return 0;
}