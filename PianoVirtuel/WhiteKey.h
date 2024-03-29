#pragma once
#include "Key.h"


class WhiteKey : public Key {
protected:
	float L = 2.0f;				// Key length
	float W = 0.5f;				// Key width
	float H = 0.4f;				// Key height
	char testText[];

public:
	WhiteKey(float x, float y, float z, char letter, int id_num);
	void show();
	void displayText(char text, float x, float y, float z, bool black);
};