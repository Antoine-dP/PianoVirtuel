#include "Key.h"


Key::Key(int keyType, float x, float y, float z, char letter) {
	position = { x,y,z };
    isPressed = false;
    if (keyType == 0 || keyType == 1)
    {
        type = keyType;
    }
    else {
        type = 0;
    }
    keyboardLetter = letter;
}

Key::Key() {
    position = { 0,0,0 };
    isPressed = false;
    type = 0;
    keyboardLetter = ' ';
}

void Key::press(bool isDown) {
	isPressed = isDown;
}
