#include "BlackKey.h"

float toucheNoire[8][3]{
    {-1.0,  0.0, -1.0},
    { 1.0,  0.0, -1.0},
    { 1.0,  0.0,  1.0},
    {-1.0,  0.0,  1.0},
    {-1.0, -1.0, -1.0},
    { 1.0, -1.0, -1.0},
    { 1.0, -1.0,  1.0},
    {-1.0, -1.0,  1.0}
};

int faceNoire[6][4] = {
   {0,1,2,3},
   {3,2,6,7},
   {4,5,6,7},
   {0,1,5,4},
   {1,5,6,2},
   {0,3,4,7}
};

float rotateAngleBlack = 7;



BlackKey::BlackKey(float x, float y, float z, char letter) {
    position = { x,y,z };
    isPressed = false;
    type = 0;
    keyboardLetter = letter;
    char testText[] = { '*' };
}

void BlackKey::show() {
    
    // DRAW SINGLE FACE 
    //glBegin(GL_QUADS);
    //// If key is down, change color
    //if (isPressed)
    //{
    //    glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
    //}
    //else
    //{
    //    glColor3f(0.0f, 0.0f, 0.0f);
    //}
    //// Draw key
    //glVertex3f(-W / 2 + position.x, position.y, -L / 2 + position.z);
    //glVertex3f(W / 2 + position.x, position.y, -L / 2 + position.z);
    //glVertex3f(W / 2 + position.x, position.y, L / 2 + position.z);
    //glVertex3f(-W / 2 + position.x, position.y, L / 2 + position.z);
    //glEnd();


    /////////////////////////////////////

        // FULL CUBE (6 SIDES)
    for (int i = 0; i < 6; i++)
    {
        // Draw face

        if (isPressed)
        {
            // Rotate key if it's pressed
            glTranslatef(-position.x, -position.y, -position.z - L);
            glRotatef(rotateAngleBlack, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L);

            // Draw faces
            glBegin(GL_QUADS);
            // Make blue
            glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheNoire[faceNoire[i][j]][0] * W / 2 + position.x,
                    toucheNoire[faceNoire[i][j]][1] * H + position.y,
                    toucheNoire[faceNoire[i][j]][2] * L / 2 + position.z);
            }
            glEnd();

            // Undo rotation for others
            glTranslatef(-position.x, -position.y, -position.z - L);
            glRotatef(-rotateAngleBlack, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L);
        }
        else
        {
            // if not pressed, just draw in white
            glBegin(GL_QUADS);
            glColor3f(0.0f, 0.0f, 0.0f);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheNoire[faceNoire[i][j]][0] * W / 2 + position.x,
                    toucheNoire[faceNoire[i][j]][1] * H + position.y,
                    toucheNoire[faceNoire[i][j]][2] * L / 2 + position.z);
            }
            glEnd();
        }

    }

    displayText(keyboardLetter, position.x, position.y + 0.001, position.z, false);
}

void BlackKey::displayText(char text, float x, float y, float z, bool black) {

    if (black) {
        glColor3f(0.0, 0.0, 0.0);
    }
    else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glRasterPos3f(x, y, z);
    char tempText[] = { text};

    for (char* c = tempText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
        break;
    }

}
