// 控制台输出文字颜色类
#pragma once

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

const int FATAL = 12;
const int ERR= 13;
const int WARN = 10;
const int INFO = 11;
const int DEBUG = 14;

class Colorful
{
public:
	static void Color(int);

private:

};

void Colorful::Color(int k)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}