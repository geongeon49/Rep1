#include "OBJ.h"
#include <GL/glut.h>


#define WINDOW_X 200
#define WINDOW_Y 200

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

OBJ cube;
float angle = 0.0f;

void idle() {
	angle += 0.1f;
	glutPostRedisplay();
}

void drawCube() {
	/* Implement: Draw cube after applying rotation, translation, and scale */
	glTranslatef(0.5f, 0.5f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.5f);
	glScalef(2.0f, 2.0f, 2.0f);
	cube.draw();
}

void renderScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the correct perspective.
	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	gluLookAt(10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	/* Implement: Enable depth testing and call drawCube function */
	glEnable(GL_DEPTH_TEST);
	drawCube();

	glutSwapBuffers();
}

void main(int argc, char** argv) {
	cube.ReadOBJFile("cube.obj");

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Draw a rotating cube");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
}