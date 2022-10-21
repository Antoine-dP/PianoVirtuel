#include "Key.h"

Key::Key(int keyType, float x, float y, float z) {
	position = { x,y,z };
	type = keyType;
}

void Key::press(bool isDown) {
	isPressed = isDown;
}
void Key::show() {

}