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

int face[6][4] = {
   {0,1,2,3},
   {3,2,6,7},
   {4,5,6,7},
   {0,1,5,4},
   {1,5,6,2},
   {0,3,4,7}
};

float rotateAngle = 7;

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


    // FULL CUBE (6 SIDES)
    for (int i = 0; i < 6; i++)
    {
        // Draw face
        
        if (isPressed)
        {
            // Rotate key if it's pressed
            glTranslatef(-position.x, -position.y, -position.z - L/2);
            glRotatef(rotateAngle, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L/2);

            // Draw faces
            glBegin(GL_QUADS);
            glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheBlanche[face[i][j]][0] * W / 2 + position.x,
                    toucheBlanche[face[i][j]][1] * H + position.y,
                    toucheBlanche[face[i][j]][2] * L / 2 + position.z);
            }
            glEnd();
            // Undo rotation for others
            glTranslatef(-position.x, -position.y, -position.z - L/2);
            glRotatef(-rotateAngle, 1, 0, 0);
            glTranslatef(position.x, position.y, position.z + L/2);
        }
        else
        {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            for (int j = 0; j < 4; j++)
            {
                glVertex3f(toucheBlanche[face[i][j]][0] * W / 2 + position.x,
                    toucheBlanche[face[i][j]][1] * H + position.y,
                    toucheBlanche[face[i][j]][2] * L / 2 + position.z);
            }
            glEnd();
        }
        
        // Draw edges
        //for (int j = 0; j < 4; j++)
        //{
        //    glLineWidth(2.0f);
        //    glBegin(GL_LINES);
        //    glColor3f(0.0f, 0.0f, 0.0f);
        //    glVertex3f(toucheBlanche[face[i][j]][0] * W / 2 + position.x,
        //        toucheBlanche[face[i][j]][1] * H + position.y,
        //        toucheBlanche[face[i][j]][2] * L / 2 + position.z);
        //    glVertex3f(toucheBlanche[face[i][(j+1)%4]][0] * W / 2 + position.x,
        //        toucheBlanche[face[i][j]][1] * H + position.y,
        //        toucheBlanche[face[i][j]][2] * L / 2 + position.z);
        //    glEnd();
        //}
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





