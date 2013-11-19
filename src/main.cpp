#include "freeglut.h"
#include "FreeImage.h"

using namespace std;

GLuint _weedTexId;
GLuint _ballTexId;

GLfloat pX, pY;
GLfloat pvX, pvY;

bool keyDown = false;

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x20:
		pvY += (pvY == 0) ? 0.5f : 0.0f;
		break;
	case 27: // Escape
		exit(0);
	case 'a':
		pvX -= (pvX > -0.1f) ? 0.05f : 0.0f;
		keyDown = true;
		break;
	case 'd':
		pvX += (pvX < 0.1f) ? 0.05f : 0.0f;
		keyDown = true;
		break;
	default:
		break;
	}
}

GLuint loadTexture(const char* path)
{
	if (!path)
		return 0;

	char fullPath[80] = "../res/";
	strcat_s(fullPath, path);

	FIBITMAP *bitmap = FreeImage_Load(FIF_PNG, fullPath, 0);
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	BYTE* bitmapBits = FreeImage_GetBits(bitmap);


	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 64,
				 64,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bitmapBits);

	return textureId;

	FreeImage_Unload(bitmap);
}

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	_weedTexId = loadTexture("weed.png");
	_ballTexId = loadTexture("bounce.png");

	pX = 0.0f;
	pY = 1.0f;

	pvX = 0.0f;
	pvY = 0.0f;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

	glTranslatef(-5.0f, -2.1f, -15.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _weedTexId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(10.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(10.0f, 1.0f, 0.0f);

	glEnd();


	// Draw player
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _ballTexId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTranslatef(pX, pY, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();

	glutSwapBuffers();
}

void Update(int i)
{
	if (!keyDown)
		pvX += (pvX > 0) ? -0.005f : 0.005f;

	if (pvY != 0.0f || pY != 1.0f)
		pvY -= 0.05f;

	keyDown = false;

	pX += pvX;

	if (pY + pvY < 1.0f)
	{
		pY = 1.0f;
		pvY = 0.0f;
	}
	else
		pY += pvY;

	drawScene();
	glutTimerFunc(1000 / 60, Update, 0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Yolouswaag");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(1000 / 60, Update, 0);

	glutMainLoop();
	return 0;
}

