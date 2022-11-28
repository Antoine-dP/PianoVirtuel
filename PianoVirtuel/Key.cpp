#include "Key.h"


Key::Key(int keyType, float x, float y, float z, char letter, int id_num) {
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
    id = id_num;
}

Key::Key() {
    position = { 0,0,0 };
    isPressed = false;
    type = 0;
    keyboardLetter = ' ';
    id = -1;
}

void Key::press(bool isDown) {
	isPressed = isDown;
}
