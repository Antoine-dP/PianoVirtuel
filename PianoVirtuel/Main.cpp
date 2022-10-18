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

// Fichiers d'en-têtes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
//#include <glut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#define GL_GLEXT_PROTOTYPES

#endif



// Structure de données simpliste
// pour stocker un sommet 3D et 
// ses informations de couleur

typedef struct {
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    //float a;
} vertex;


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

vertex cubeBlanc[8] = {
   {-0.5f,-0.5f, 0.5f,1.0f,1.0f,1.0f},
   {-0.5f, 0.5f, 0.5f,1.0f,1.0f,1.0f},
   { 0.5f, 0.5f, 0.5f,1.0f,1.0f,1.0f},
   { 0.5f,-0.5f, 0.5f,1.0f,1.0f,1.0f},
   {-0.5f,-0.5f,-0.5f,1.0f,1.0f,1.0f},
   {-0.5f, 0.5f,-0.5f,1.0f,1.0f,1.0f},
   { 0.5f, 0.5f,-0.5f,1.0f,1.0f,1.0f},
   { 0.5f,-0.5f,-0.5f,1.0f,1.0f,1.0f}
};

// Création des faces du cube
int face[6][4] = {
   {0,1,2,3},
   {3,2,6,7},
   {4,5,6,7},
   {0,1,5,4},
   {1,5,6,2},
   {0,4,7,3}
};

// Indice des coordonnees de texture
typedef struct {
    float s;
    float t;
} textureCoord;

textureCoord faceTexcoord[6][4] = {
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // premiere face
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // seconde face
   { {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f} }, // troisieme face
   { {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f} }, // quatrieme face
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // cinquieme face
   { {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f} } // sixieme face
};


// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 1.0f;

// Rotations autour de X et Y
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLint oldX = 0;
GLint oldY = 0;
GLboolean boutonClick = false;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float _near = 0.1f;
float _far = 100.0f;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);

// Texture
GLuint textureID = 0;

// TEXTURE
unsigned long x;
unsigned long y;
unsigned short int bpp; //bits per pixels   unsigned short int
GLbyte* texData;             //the data of the image
GLuint ID;                //the id ogl gives it
unsigned long size;     //length of the file
int channels;      //the channels of the image 3 = RGA 4 = RGBA
GLuint type;

GLboolean colorCube = false;
GLint texEnvMode = 1;
GLboolean alpha = false;



// Definition de la fonction d'affichage
GLvoid affichage() {

    // Effacement du frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);


    // Combinaison avec le fragment
    switch (texEnvMode) {
    case 0:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
        break;
    case 1:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        break;
    case 2:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        break;

    default:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
        break;
    }


    // Animation du cube!
    glLoadIdentity();
    glRotatef(-angleY, 1.0f, 0.0f, 0.0f);
    glRotatef(-angleX, 0.0f, 1.0f, 0.0f);

    // Dessin d'un cube colore
    // face par face
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
            // Couleur
            if (!alpha) {
                glDisable(GL_BLEND);
                if (colorCube) {
                    glColor3f(cube[face[i][j]].r, cube[face[i][j]].g, cube[face[i][j]].b);
                }
                else {
                    glColor3f(cubeBlanc[face[i][j]].r, cubeBlanc[face[i][j]].g, cubeBlanc[face[i][j]].b);
                }
            }
            else {
                // enabling blend
                glEnable(GL_BLEND);

                if (colorCube) {
                    glColor4f(cube[face[i][j]].r, cube[face[i][j]].g, cube[face[i][j]].b, 0.5f);
                }
                else {
                    glColor4f(cubeBlanc[face[i][j]].r, cubeBlanc[face[i][j]].g, cubeBlanc[face[i][j]].b, 0.5f);
                }
            }
            // Tex
            glTexCoord2d(faceTexcoord[i][j].s, faceTexcoord[i][j].t);
            glVertex3f(cube[face[i][j]].x, cube[face[i][j]].y, cube[face[i][j]].z);
        }
        glEnd();
    }

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
    case 'p': // carre plein
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case 'f': // fil de fer
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 's': // sommets du carre
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;

        // Gestion du tampon de profondeur
    case 'd':
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    case 'D':
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
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

        // Couleur ou non
    case 'c':
        colorCube = !colorCube;
        break;


    case 't':
        texEnvMode = (texEnvMode + 1) % 3;
        printf("texEnvMode : %d\n", texEnvMode);
        break;

    case 'a':
        alpha = !alpha;
        break;

    case 'q': // quitter
    case 27:
        exit(0);
        break;
    }

    // Demande a GLUT de reafficher la scene
    glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y) {
    // Test pour voir si le bouton gauche de la souris est appuyé
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
        boutonClick = true;
        oldX = x;
        oldY = y;
    }

    // si on relache le bouton gauche
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
        boutonClick = false;
    }
}

GLvoid deplacementSouris(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace
    // alors on doit modifier les angles de rotations du cube
    // en fonction de la derniere position de la souris 
    // et de sa position actuelle
    if (boutonClick) {
        angleX += (x - oldX);
        angleY += (y - oldY);
        // Appeler le re-affichage de la scene OpenGL
        glutPostRedisplay();
    }

    // Mise a jour des anciennes positions de la souris en X et Y
    oldX = x;
    oldY = y;
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
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

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
    glutInitWindowPosition(200, 200);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("Cube3D");

    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialement on desactive le Z-buffer
    glEnable(GL_DEPTH_TEST);


    // Correction de la perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    // Nouveaux callbacks
    glutMouseFunc(souris);
    glutMotionFunc(deplacementSouris);
    glutReshapeFunc(redimensionner);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    return 0;
}








