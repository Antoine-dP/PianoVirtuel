#pragma once
#include "Key.h"


class BlackKey : public Key {
protected:
	float L = 1.2f;				// Key length
	float W = 0.29f;				// Key width
	float H = 0.4f;				// Key height
	char testText[];

public:
	BlackKey(float x, float y, float z, char letter, int id_num);
	//WhiteKey(int keyType, float x, float y, float z, char letter);
	void show();
	void displayText(char text, float x, float y, float z, bool black);
};