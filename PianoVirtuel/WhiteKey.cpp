#include "WhiteKey.h"

float toucheBlanche[8][3]{
    {-1.0,  0.0, -1.0},
    { 1.0,  0.0, -1.0},
    { 1.0,  0.0,  1.0},
    {-1.0,  0.0,  1.0},
    {-1.0, -1.0, -1.0},
    { 1.0, -1.0, -1.0},
    { 1.0, -1.0,  1.0},
    {-1.0, -1.0,  1.0}
};

int face[6][7] = {
   {0,1,2,3},
   {3,2,6,7},
   {4,7,6,5},
   {0,4,5,1},
   {1,5,6,2},
   {0,3,7,4}
};

float couleurBlanche[6][3]{
    {1.0, 1.0, 1.0},
    {0.8, 0.8, 0.8},
    {1.0, 1.0, 1.0},
    {0.8, 0.8, 0.8},
    {0.6, 0.6, 0.6},
    {0.6, 0.6, 0.6}
};

float rotateAngle = 5;

WhiteKey::WhiteKey(float x, float y, float z, char letter) {
    position = { x,y,z };
    isPressed = false;
    type = 0;
    keyboardLetter = letter;
    char testText[] = { '*' };
}


void WhiteKey::show() {

    // SINGLE SQUARE FOR TOP OF KEY
    //glBegin(GL_QUADS);
    //// If key is down, change color
    //if (isPressed)
    //{
    //    glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
    //}
    //else
    //{
    //    glColor3f(1.0f, 1.0f, 1.0f);
    //}
    //glVertex3f(-W / 2 + position.x, position.y, -L / 2 + position.z);
    //glVertex3f( W / 2 + position.x, position.y, -L / 2 + position.z);
    //glVertex3f( W / 2 + position.x, position.y,  L / 2 + position.z);
    //glVertex3f(-W / 2 + position.x, position.y,  L / 2 + position.z);
    //glEnd();

    if (isPressed)
    {
        for (int i = 0; i < 6; i++)
        {
            // Draw face
            // Rotate key if it's pressed
            glTranslatef(-position.x, -position.y, -position.z - L / 2);
            glRotatef(rotateAngle, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L / 2);

            // Draw faces
            glBegin(GL_QUADS);
            // Make blue
            glColor3f(couleurBlanche[i][0] * 79.0f / 255.0, couleurBlanche[i][1] * 194.0f / 255.0, couleurBlanche[i][2] * 170.0f / 255.0);
            //glColor3f(couleurBlanche[i][0], couleurBlanche[i][1], couleurBlanche[i][2]);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheBlanche[face[i][j]][0] * W / 2 + position.x,
                    toucheBlanche[face[i][j]][1] * H + position.y,
                    toucheBlanche[face[i][j]][2] * L / 2 + position.z);
            }
            glEnd();

            // Undo rotation for others
            glTranslatef(-position.x, -position.y, -position.z - L / 2);
            glRotatef(-rotateAngle, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L / 2);
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            // if not pressed, just draw in white
            glBegin(GL_QUADS);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glColor3f(couleurBlanche[i][0], couleurBlanche[i][1], couleurBlanche[i][2]);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheBlanche[face[i][j]][0] * W / 2 + position.x,
                    toucheBlanche[face[i][j]][1] * H + position.y,
                    toucheBlanche[face[i][j]][2] * L / 2 + position.z);
            }
            glEnd();  
        }
    }

    displayText(keyboardLetter, position.x, position.y + 0.001, position.z + L/4, true);
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
    for (char* c = tempText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
        break;
    }

}





