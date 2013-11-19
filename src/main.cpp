// 2D Test.cpp : Defines the entry point for the console application.
//

#include "freeglut.h"
#include "FreeImagePlus.h"

using namespace std;

GLuint textureId;

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // Escape
		exit(0);
	default:
		break;
	}
}

GLuint loadTexture(const char* path)
{
	if (!path)
		return 0;

	FIBITMAP *bitmap = FreeImage_Load(FIF_PNG, "..\res\\", 0);
}

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	// Load images
}

void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) w / (float) h, 1.0f, 200.0f);
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	// TODO

	glutSwapBuffers();
}

int _tmain(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Yolouswaag");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}

