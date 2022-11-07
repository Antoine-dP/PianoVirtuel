//
//  main.cpp
//  ANREC_OGL_CubeTexture
//
//  Created by Jean-Marie Normand on 21/09/15.
//  Copyright (c) 2015 Centrale Innovation. All rights reserved.
//

#include "Windows.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Vertex.h"
#include "Key.h"
#include "WhiteKey.h"
#include "BlackKey.h"

#include <mmsystem.h>
#include <conio.h>
#pragma comment (lib,"Winmm.lib")

// Fichiers d'en-têtes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
//#define GLFW_INCLUDE_NONE
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

//#include <GLFW/glfw3.h>
//#include <glad.h>
#define GL_GLEXT_PROTOTYPES

#endif

// For GLM (click detection)
//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
//#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
////#include <glm/ext/constants.hpp> // glm::pi
//#include <glm/ext/matrix_projection.hpp> // glm::pi


using namespace std;

// Structure de données simpliste
// pour stocker un sommet 3D et 
// ses informations de couleur


// Création des sommets du cube
vertex cube[8] = {
   {-0.5f,-0.5f, 0.5f,1.0f,0.0f,0.0f},
   {-0.5f, 0.5f, 0.5f,0.0f,1.0f,0.0f},
   { 0.5f, 0.5f, 0.5f,0.0f,0.0f,1.0f},
   { 0.5f,-0.5f, 0.5f,1.0f,1.0f,1.0f},
   {-0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f},
   {-0.5f, 0.5f,-0.5f,0.0f,1.0f,0.0f},
   { 0.5f, 0.5f,-0.5f,0.0f,0.0f,1.0f},
   { 0.5f,-0.5f,-0.5f,1.0f,1.0f,1.0f}
};

GLfloat halfWidthW = 0.25f;
GLfloat halfLengthW = 1.0f;
GLfloat halfWidthB = 0.58f * halfWidthW;
GLfloat halfLengthB = 0.6f * halfLengthW;

// 10% gap between keys :
GLfloat gap = 0.1;


vertex toucheBlanche[4] = {
   {-halfWidthW, 0.0f,-halfLengthW,1.0f,1.0f,1.0f},
   { halfWidthW, 0.0f,-halfLengthW,1.0f,1.0f,1.0f},
   { halfWidthW, 0.0f, halfLengthW,1.0f,1.0f,1.0f},
   {-halfWidthW, 0.0f, halfLengthW,1.0f,1.0f,1.0f}
};

vertex toucheNoire[4] = {
   {-halfWidthB, 0.1f,-halfLengthB,1.0f,1.0f,1.0f},
   { halfWidthB, 0.1f,-halfLengthB,1.0f,1.0f,1.0f},
   { halfWidthB, 0.1f, halfLengthB,1.0f,1.0f,1.0f},
   {-halfWidthB, 0.1f, halfLengthB,1.0f,1.0f,1.0f}
};

vertex touchesBlanches[8] = {
   {(-4 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {(-3 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {(-2 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {(-1 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {( 0 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {( 1 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {( 2 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f},
   {( 3 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap), 0.0f, 0.0f}
};
vertex touchesNoires[5] = {
   {-3 * (2 * halfWidthW) * (1 + gap), 0.2f, (halfLengthB - halfLengthW)},
   {-2 * (2 * halfWidthW) * (1 + gap), 0.2f, (halfLengthB - halfLengthW)},
   { 0 * (2 * halfWidthW) * (1 + gap), 0.2f, (halfLengthB - halfLengthW)},
   { 1 * (2 * halfWidthW) * (1 + gap), 0.2f, (halfLengthB - halfLengthW)},
   { 2 * (2 * halfWidthW) * (1 + gap), 0.2f, (halfLengthB - halfLengthW)}
};

char textVect[] = "QSDFJKLMZEUIO";


// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 1.0f;
GLint downKey = 0;
bool leftMouseDown = false;
bool rightMouseDown = false;


// Taille de la fenêtre
int windowW = 640*2;
int windowH = 480*2;
float focale = 65.0f;
float _near = 0.1f;
float _far = 100.0f;
float rat = 1;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid clavierUP(unsigned char touche, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);

// Déclaration d'autres fonctions
void drawKeys();
void playKey(int key);
void displayText(char text[], float x, float y, float z, bool black);
void displayText(char text, float x, float y, float z, bool black);
void initOctaveVect();
void pressKey(char letter, bool down);
void pressKey(bool down);
char keyFromID(int r);

vector<Key*> octaveVect;

// Shader stuff
//UCreateShaders

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


// Definition de la fonction d'affichage
GLvoid affichage() {

    // Effacement du frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    // Draw octave 
    drawKeys();


    glFlush();
    glutSwapBuffers();
}

// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) {

    // Suivant les touches pressees, nous aurons un comportement different de l'application
    // ESCAPE ou 'q' : fermera l'application
    // 'p' : affichage du carre plein
    // 'f' : affichage du carre en fil de fer
    // 's' : affichage des sommets du carre

    switch (touche) {
    //case 'p': // carre plein
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    break;
    //case 'f': // fil de fer
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    break;
    //case 's': // sommets du carre
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    //    break;
    //    // Gestion du tampon de profondeur
    //case 'd':
    //    glEnable(GL_DEPTH_TEST);
    //    glutPostRedisplay();
    //    break;
    //case 'D':
    //    glDisable(GL_DEPTH_TEST);
    //    glutPostRedisplay();
    //    break;
        
    case 'q':
    case 'Q':
        pressKey('Q', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\C.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 's':
    case'S':
        pressKey('S', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\D.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'd':
    case 'D':
        pressKey('D', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\E.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'f':
    case 'F':
        pressKey('F', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\F.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'j':
    case 'J':
        pressKey('J', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\G.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'k':
    case 'K':
        pressKey('K', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\A.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'l':
    case 'L':
        pressKey('L', true);
        PlaySound(TEXT("E:\\P1RV\\PianoVirtuel\\PianoSounds\\B.wav"), NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'm':
    case 'M':
        pressKey('M', true);
        break;
    case 'z':
    case 'Z':
        pressKey('Z', true);
        break;
    case 'e':
    case 'E':
        pressKey('E', true);
        break;
    case 'u':
    case 'U':
        pressKey('U', true);
        break;
    case 'i':
    case 'I':
        pressKey('I', true);
        break;
    case 'o':
    case 'O':
        pressKey('O', true);
        break;

    case '+':
        // Augmenter la taille des sommets affiches
        pointSize += 1.0f;
        glPointSize(pointSize);
        break;
    case '-':
        // Augmenter la taille des sommets affiches
        pointSize -= 1.0f;
        if (pointSize <= 0.0f)
            pointSize = 1.0f;
        glPointSize(pointSize);
        break;

    //case 'q': // quitter
    case 27:
        exit(0);
        break;
    }

    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();
}

GLvoid clavierUP(unsigned char touche, int x, int y) {
    switch (touche) {

    case 'q':
    case 'Q':
        pressKey('Q', false);
        break;
    case 's':
    case 'S':
        pressKey('S', false);
        break;
    case 'd':
    case 'D':
        pressKey('D', false);
        break;
    case 'f':
    case 'F':
        pressKey('F', false);
        break;
    case 'j':
    case 'J':
        pressKey('J', false);
        break;
    case 'k':
    case 'K':
        pressKey('K', false);
        break;
    case 'l':
    case 'L':
        pressKey('L', false);
        break;
    case 'm':
    case 'M':
        pressKey('M', false);
        break;
    case 'z':
    case 'Z':
        pressKey('Z', false);
        break;
    case 'e':
    case 'E':
        pressKey('E', false);
        break;
    case 'u':
    case 'U':
        pressKey('U', false);
        break;
    case 'i':
    case 'I':
        pressKey('I', false);
        break;
    case 'o':
    case 'O':
        pressKey('O', false);
        break;
    }
    glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y) {
    windowW = glutGet(GLUT_WINDOW_WIDTH);
    windowH = glutGet(GLUT_WINDOW_HEIGHT);

    GLbyte color[4];
    //GLfloat color[3];
    //GLfloat depth;
    //GLuint index;

    //glReadPixels(x, windowH - y - 1, 1, 1, GL_RGB, GL_FLOAT, color);
    glReadPixels(x, windowH - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    //glReadPixels(x, windowH - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    //glReadPixels(x, windowH - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);


    float r = -color[0]-1;
    cout << "r = " << (float)color[0] << endl;
    //printf("Color : %x%x%x \n", color[0], color[1], color[2]);

    //cout << "x: " << x << ", y: " << y << endl;

    // si on relache le bouton gauche
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
        leftMouseDown = false;
        pressKey(false);
    }
    //// si on relache le bouton droit
    //else if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_UP) {
    //    rightMouseDown = false;
    //    pressKey(false);
    //}
    // si on appuie le bouton gauche
    else if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
        leftMouseDown = true;
        pressKey(keyFromID(r), true);
    }
    //// si on appuie le bouton droit
    //else if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_DOWN) {
    //    rightMouseDown = true;
    //    pressKey(keyFromID(r), true);
    //}
    
    glutPostRedisplay();
}

GLvoid deplacementSouris(int x, int y) {

}

// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;
    // eviter une division par 0
    if (windowH == 0)
        windowH = 1;

    float ratio = (float)windowW / (float)windowH;
    std::cout << "Ratio : " << ratio << std::endl;

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, windowW, windowH);

    // Mise en place de la perspective
    gluPerspective(focale, ratio, _near, _far);

    // Placement de la caméra
    //gluLookAt(0, 5, 0.0001f, 0, 0, 0, 0, 1, 0);
    gluLookAt(0, 5, 2.0f, 0, 0, 0, 0, 1, 0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char* argv[])
{
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    // Position initiale de la fenetre GLUT
    glutInitWindowPosition(300, 50);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("Piano3D");

    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.300f, 0.300f, 0.300f, 1.0f);

    // Initialement on desactive le Z-buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);


    // Correction de la perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUP);
    // Nouveaux callbacks
    glutMouseFunc(souris);
    glutMotionFunc(deplacementSouris);
    glutReshapeFunc(redimensionner);

    initOctaveVect();

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void initOctaveVect() {
    Key* keyPtr = nullptr;

    // White keys
    for (int i = 0; i < 8; i++)
    {
        keyPtr = new WhiteKey(touchesBlanches[i].x, touchesBlanches[i].y, touchesBlanches[i].z, textVect[i], i+1);
        octaveVect.push_back(keyPtr);
    }
    for (int i = 0; i < 5; i++)
    {
        keyPtr = new BlackKey(touchesNoires[i].x, touchesNoires[i].y, touchesNoires[i].z, textVect[i+8], i+10);
        octaveVect.push_back(keyPtr);
    }
}

void drawKeys(){
    for (int i = 0; i < octaveVect.size(); i++)
    {
        (*octaveVect[i]).show();
    }
}

// Old versions
//void drawOctave_White() {
//
//    // 8 keys in an octave
//    GLint octaveSize = 8;
//    
//    // If even number of keys (always used for drawing octave)
//    if (octaveSize % 2 == 0) {
//        // Draw 8 keys in octave
//        for (int j = 0; j < octaveSize; j++)
//        {
//            glBegin(GL_QUADS);
//            // If key is down, change color
//            if (downKey == j + 1)
//            {
//                glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
//            }
//            else
//            {
//                glColor3f(1.0f, 1.0f, 1.0f);
//            }
//            // Draw key
//            for (int i = 0; i < 4; i++)
//            {
//                glVertex3f(toucheBlanche[i].x + (j - octaveSize / 2 + (2 * halfWidthW)) * (2*halfWidthW) * (1+gap), toucheBlanche[i].y, toucheBlanche[i].z);
//            }
//            glEnd();
//
//            // Display keyboard letter on key
//            char tempText[] = { textVect[j] };
//            displayText(tempText, (j - octaveSize / 2 + (2 * halfWidthW)) * (2 * halfWidthW) * (1 + gap/2), 0.2, -toucheBlanche[0].z / 2, true);
//            
//            //displayText(tempText, 0, 1, 0, true);
//        }
//    }
//    // If odd number of keys (not used for drawing octave)
//    else {
//        for (int j = 0; j < octaveSize; j++)
//        {
//            glBegin(GL_QUADS);
//            for (int i = 0; i < 4; i++)
//            {
//                glVertex3f(toucheBlanche[i].x + (j + (1 - octaveSize) / 2) * (2*halfWidthW) * (1+gap), toucheBlanche[i].y, toucheBlanche[i].z);
//            }
//            glEnd();
//        }
//    }
//}
//void drawOctave_Black() {
//    // 8 keys in an octave
//    GLint octaveSizeB = 5;
//
//    vertex posTouchesNoires[5] = { {-3}, {-2}, {0}, {1}, {2} };
//    
//    for (int j = 0; j < octaveSizeB; j++)
//    {
//        glBegin(GL_QUADS);
//        // If key is down, change color
//        if (downKey == j + 9)
//        {
//            glColor3f(79.0f / 255.0, 194.0f / 255.0, 170.0f / 255.0);
//        }
//        else
//        {
//            // Default color : black
//            glColor3f(0.0f, 0.0f, 0.0f);
//        }
//        // Draw key
//        for (int i = 0; i < 4; i++)
//        {
//            glVertex3f(toucheNoire[i].x + posTouchesNoires[j].x * (2 * halfWidthW ) * (1 + gap), toucheNoire[i].y, toucheNoire[i].z + halfLengthB - halfLengthW);
//        }
//        glEnd();
//
//        char tempText[] = { textVect[j+8] };
//        displayText(tempText, posTouchesNoires[j].x * (2 * halfWidthW) * (1 + gap/2), toucheNoire[0].y + 0.2, halfLengthB - halfLengthW, false);
//    }
//
//        
//    
//
//}

void playKey(int key) {
    //PlaySound(TEXT("E:\P1RV\PianoVirtuel\PianoSounds\C.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //LPCSTR const Sound_File_Open = "open C:\\Users\\xxx\\Desktop\\nyan-clipped.mp3 type mpegvideo alias Current_Sound_Command";
    //LPCSTR const Sound_File_Open = "open E:\\P1RV\\PianoVirtuel\\PianoSounds\\G.wav";

    //MCIERROR open = mciSendString(Sound_File_Open, NULL, 0, NULL);

    //MCIERROR play = mciSendString("play Current_Sound_Command repeat", NULL, 0, NULL);

    //system("pause");
}

void displayText(char text[], float x, float y, float z, bool black) {
    
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
void displayText(char text, float x, float y, float z, bool black) {

    if (black) {
        glColor3f(0.0, 0.0, 0.0);
    }
    else {
        glColor3f(1.0, 1.0, 1.0);
    }
    glRasterPos3f(x, y, z);
    char tempText[] = {text};
    for (char* c = tempText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Updates the position
    }

}

void pressKey(char letter, bool down) {

    char c = (char)toupper(letter);

    for (int i = 0; i < octaveVect.size(); i++)
    {
        if ((*octaveVect[i]).getLetter() == c) {
            (*octaveVect[i]).press(down);
            return;
        }
    }
}

void pressKey(bool down) {

    for (int i = 0; i < octaveVect.size(); i++)
    {
        (*octaveVect[i]).press(down);
    }
    return;
}

char keyFromID(int r) {
    switch (r) {
    case 1:
    case 52:
    case 103:
        return 'Q';
        break;
    case 2:
    case 53:
    case 104:
        return 'S';
        break;
    case 3:
    case 54:
    case 105:
        return 'D';
        break;
    case 4:
    case 55:
    case 106:
        return 'F';
        break;
    case 5:
    case 56:
    case 107:
        return 'J';
        break;
    case 6:
    case 57:
    case 108:
        return 'K';
        break;
    case 7:
    case 58:
    case 109:
        return 'L';
        break;
    case 8:
    case 59:
    case 110:
        return 'M';
        break;
    case -42:
    case -16:
        return 'Z';
        break;
    case -41:
    case -15:
        return 'E';
        break;
    case -40:
    case -14:
        return 'U';
        break;
    case -39:
    case -13:
        return 'I';
        break;
    case -38:
    case -12:
        return 'O';
        break;
    }
    return ' ';
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////



