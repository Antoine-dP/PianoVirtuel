#include "WhiteKey.h"


WhiteKey::WhiteKey(float x, float y, float z, char letter) {
    position = { x,y,z };
    isPressed = false;
    type = 0;
    keyboardLetter = letter;
    char testText[] = { '*' };
}

//WhiteKey::WhiteKey(int keyType, float x, float y, float z, char letter) {
//    position = { x,y,z };
//    isPressed = false;
//    type = 0;
//    keyboardLetter = letter;
//}


void WhiteKey::show() {

    glBegin(GL_QUADS);
    // If key is down, change color
    if (isPressed)
    {
        glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    // Draw key

    glVertex3f(-W / 2 + position.x, H + position.y, -L / 2 + position.z);
    glVertex3f( W / 2 + position.x, H + position.y, -L / 2 + position.z);
    glVertex3f( W / 2 + position.x, H + position.y,  L / 2 + position.z);
    glVertex3f(-W / 2 + position.x, H + position.y,  L / 2 + position.z);


    glEnd();



    //char tempText[] = { keyboardLetter };
    //char tempText[] = { ' ' };
    //displayText(tempText, position.x, position.y + 0.2, position.z, true);
    //displayText(keyboardLetter, position.x, position.y + 0.2, position.z, true);
    //displayText(' ', position.x, position.y + 0.2, position.z, true);
}

void WhiteKey::displayText(char text, float x, float y, float z, bool black) {

    if (black) {
        glColor3f(0.0, 0.0, 0.0);
    }
    else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glRasterPos3f(x, y, z);
    char tempText[] = { text };
    //char tempText[] = { ' '};
    for (char* c = tempText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
    }

}
void WhiteKey::displayText(char text[], float x, float y, float z, bool black) {

    if (black) {
        glColor3f(0.0, 0.0, 0.0);
    }
    else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glRasterPos3f(x, y, z);
    for (char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
    }

}