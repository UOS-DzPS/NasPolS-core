#include <iostream>
#include <clocale>
#include <cstdlib>

#include <inc/polish.h>
#include <inc/unit_test.h>

void SetLocale(void)
{
	// Do not touch this code. This part sets the locale.
	std::setlocale(LC_ALL, "pl_PL.UTF-8");
	system("chcp 65001 > nul");
	// Do not touch this code. This part sets the locale.
}

int main(void)
{
	SetLocale();
	//AnalyzerUnitTest();
	
	SplitterUnitTest();
	
	return 0;
}