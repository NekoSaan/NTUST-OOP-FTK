#pragma once
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
	EESC = 4,
	INVALID,
};

const double_t GTIMELOG = 0.33;