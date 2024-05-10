#ifndef _MAIN_H_
#define _MAIN_H_
#include <Windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "Object.h"
#include "Rect.h"
#include "GameManager.h"

void setColor(int color = 7);

void setMap();

void outputMap();

void outputInformation();

void keyUpdate(bool key[]);

void update(bool key[]);

void informationShow(vector<string> information);

// Define input command
enum class VALIDINPUT
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	EI = 4,
	EESC = 5,
	INVALID,
};

const double_t GTIMELOG = 0.33;

bool gKeyState[int(VALIDINPUT::INVALID) + 1] = { false };

#endif // _MAIN_H_