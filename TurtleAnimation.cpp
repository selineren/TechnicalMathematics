#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

// defining variables
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.1415

double turtleX = -0.65; // initial position of the turtle
double turtleSpeed = 0.005; // speed of the turtle movement
int isMoving = 1; // to check if the turtle is moving or not
int isClosed = 0; // to track whether the curtain is close or not

//mouse callback function
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//converting mouse coordinates to OpenGL coordinates
		double mouseX = (2.0*x) / WINDOW_WIDTH - 1.0;
		double mouseY = 1.0 - (2.0*y) / WINDOW_HEIGHT;

		//check if the click is inside the inner outlines
		if (mouseX >= -0.65&&mouseX <= 0.65&&mouseY >= -0.65&&mouseY <= 0.65) {
			isClosed = !isClosed; //changing the state
			glutPostRedisplay(); //requesting a redraw
		}
	}
}
//to draw circle, center at (x,y) radius r (will be used as handle)
void circle(double x, double y, double r) {
	float angle;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

//to draw half circle, turtle's body
void halfCircle(double x, double y, double r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 180; i++) {
		double angle = i * PI / 180.0;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

//for text
void stringprint(double x, double y, const char *string) {
	const char *str;
	glRasterPos2f(x, y);

	for (str = string; *str != '\0'; str++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
	}

}

//turtle drawing
void drawTurtle(double x, double y, double size) {
	
	//tail
	glColor3ub(139, 69, 19);
	glBegin(GL_TRIANGLES);
	glVertex2f(x+0.1, y+0.01);
	glVertex2f(x , y+0.03);
	glVertex2f(x +0.1, y+0.05);
	glEnd();

	//body
	glColor3f(0,1,0);
	halfCircle(x+0.15, y, size);

	//head
	glColor3f(0, 1, 0);
	circle(x + size + 0.2 , y + size, size*0.5);

	//neck
	glColor3f(0, 1, 0);
	glRectf(x+size+0.15, y+size, x + size + 0.2, y+0.05);

	//legs
	glColor3f(0.6, 0.3, 0.1);
	glBegin(GL_LINES);
	glVertex2f(x+0.12, y);
	glVertex2f(x +0.07, y - 0.05);

	glVertex2f(x + 0.18, y);
	glVertex2f(x + 0.23, y - 0.05);
	glEnd();

	//eyes
	glColor3ub(0, 0, 0);
	circle(x + size + 0.2, y + size , size*0.1);

	//baby turtle
	glColor3f(0, 1.5, 0);
	halfCircle(x+0.15, y+size, size*0.5);
	glColor3f(0, 1, 0);
	circle(x + 0.2, y + size +0.02 , size*0.2);
	glColor3ub(0, 0, 0);
	circle(x +0.2, y + size+0.02, size*0.05);

	
}

//hourse drawing
void house(void) {
	//house roof
	glBegin(GL_POLYGON);
	glColor3f(.990, 0, 0);
	glVertex2f(0.3, 0.15);
	glVertex2f(0.3, 0.2);
	glVertex2f(0.6, 0.18);
	glVertex2f(0.6, 0.15);
	glEnd();
	//house fence
	glBegin(GL_POLYGON);
	glColor3f(.555, 1.0, 1.0);
	glVertex2f(0.35, -0.37);
	glVertex2f(0.35, 0.16);
	glVertex2f(0.55, 0.16);
	glVertex2f(0.55, -0.37);
	glEnd();
	//house door
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.41, 0.36);
	glVertex2f(0.4, -0.37);
	glVertex2f(0.4, 0.04);
	glVertex2f(0.5, 0.04);
	glVertex2f(0.5, -0.37);
	glEnd();
	//house window
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.21, 0.26);
	glVertex2f(0.37, 0.07);
	glVertex2f(0.37, 0.1);
	glVertex2f(0.4, 0.1);
	glVertex2f(0.4, 0.07);
	glEnd();
	//house window2
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.21, 0.26);
	glVertex2f(0.53, 0.07);
	glVertex2f(0.53, 0.1);
	glVertex2f(0.5, 0.1);
	glVertex2f(0.5, 0.07);
	glEnd();
}


// to display onto window using OpenGL commands
void display(void) {
	glClearColor(0.4, 0, 0, 0); //clear color
	glClear(GL_COLOR_BUFFER_BIT);
	
	//wall pattern
	glPointSize(10);
	glColor3ub(122, 0,0 );
	for (double x = -0.9; x <= 0.9; x += 0.09) {
		for (double y = -0.9; y <= 0.9; y += 0.09) {
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
		}
	}

	//for window outlines 
	glLineWidth(10); // setting line width
	glColor3ub(0, 0, 0); 
	glBegin(GL_LINES);

	glVertex2f(-0.75, -0.75);
	glVertex2f(-0.75, 0.75);
	glVertex2f(-0.75, -0.75);
	glVertex2f(0.75, -0.75);
	glVertex2f(0.75, -0.75);
	glVertex2f(0.75, 0.75);
	glVertex2f(0.75, 0.75);
	glVertex2f(-0.75, 0.75);

	glEnd(); 
	
	//window as a rectangle
	glColor3ub(254, 238, 232); 
	glRectf(-0.75,-0.75,0.75,0.75);

	//sky
	glColor3ub(0, 0, 255);
	glRectf(-0.65, -0.65, 0.65, 0.65);

	//house
	house();
	
	//road
	glColor3ub(0, 0, 0);
	glRectf(-0.65, -0.65, 0.65, -0.1);

	//road line
	glColor3f(1, 1, 1);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2f(-0.65, -0.37);
	glVertex2f(0.65, -0.37);
	glEnd();

	//setting inner outlines 
	glLineWidth(5); // setting line width
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);

	glVertex2f(-0.65, -0.65);
	glVertex2f(-0.65, 0.65);
	glVertex2f(-0.65, -0.65);
	glVertex2f(0.65, -0.65);
	glVertex2f(0.65, -0.65);
	glVertex2f(0.65, 0.65);
	glVertex2f(0.65, 0.65);
	glVertex2f(-0.65, 0.65);

	glEnd();

	//handle part
	glColor3ub(153, 102, 51);
	circle(-0.7, 0.1, 0.02);
	circle(-0.7, -0.1, 0.02);
	glBegin(GL_LINES);
	glVertex2f(-0.7, 0.1);
	glVertex2f(-0.7, -0.1);
	glEnd();

	//writing my name and surname on a label
	glColor3ub(254, 238, 232);
	glRectf(0.41, 0.83, 0.75, 0.91); //label
	glColor3ub(0, 0, 0);
	stringprint(0.45, 0.85, "SELIN EREN");

	//turtle
	drawTurtle(turtleX, -0.30, 0.1);

	//the curtain function, drawing black rectangle if isClosed is true 
	if (isClosed) {
		glColor3ub(0, 0, 0);
		glRectf(-0.65, -0.65, 0.65, 0.65);
	}
	
	glutSwapBuffers();
}

//keyboard event handler
void keyboard(unsigned char key, int x, int y) {
	if (key == ' ') {
		isMoving = !isMoving; 
	}
}

//timer function for turtle movement
void update(int value) {
	if (isMoving) {
		turtleX += turtleSpeed; //moving the turtle
		if (turtleX > 0.3) {
			turtleX = -0.65; // reseting the position if it reaches the end
		}
	}

	glutPostRedisplay();
	glutTimerFunc(16, update, 0);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv); // initializing GLUT

	// window initialization
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Technical-Mathematics-Project");

	// event handler registration
	glutDisplayFunc(display); // event=display, call display
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, update, 0);
	glutMouseFunc(mouse);

	// main event loop
	glutMainLoop();

	return 0;
}