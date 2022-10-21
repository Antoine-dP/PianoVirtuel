#pragma once

#include "Windows.h"
#include "Vertex.h"
#include <iostream>
#include <stdio.h>
#include <vector>

#include <mmsystem.h>
#include <conio.h>
#pragma comment (lib,"Winmm.lib")

// Fichiers d'en-t�tes pour OpenGL et GLUT
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

using namespace std;

class Key {
	int type;
	vertex position;
	bool isPressed;
public:
	Key(int keyType, float x, float y, float z);
	void press(bool isDown);
	void show();
};