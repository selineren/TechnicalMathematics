#include <time.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdarg.h> 
#include <stdlib.h>

//defining variables
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int elapsedTimeSeconds = 0;
int elapsedTimeMilliseconds = 0;

//variables to store cannon position
double cannonX = -0.9;
double cannonY = -0.8;

double bulletX = 0;
double bulletY = 0;
int bulletFired = 0; //0: not fired, 1: fired

typedef struct {
	float x;
	float y;
	float velocity;
} Target;

#define MAX_TARGETS 5
#define TARGET_DELAY 500 //milliseconds between generating new targets
#define TARGET_WIDTH 0.2 
Target targets[MAX_TARGETS];
int numTargets = 0;
int lastTargetTime = 0;
int score = 0;
int gameOver = 0;
int gameRunning = 0; //0: game stopped, 1: game running


void generateTarget() {
	//if the maximum limit of targets is reached
	if (numTargets >= MAX_TARGETS) {
		return;
	}

	//new target if it's time
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - lastTargetTime < TARGET_DELAY) {
		return;
	}
	lastTargetTime = currentTime;

	//new target
	float velocity = ((float)rand() / RAND_MAX) * 0.01 + 0.005; //random velocity  
	//before doing this homework I did not know about RAND_MAX and using float with rand but 
	//to be able to generate random double numbers I learned :)
	int side = rand() % 2; //0: left to right, 1: right to left
	switch (side) {
	case 0: //left to right
		targets[numTargets].x = -1.0;
		targets[numTargets].velocity = velocity;
		break;
	case 1: //right to left
		targets[numTargets].x = 0.75 - TARGET_WIDTH;
		targets[numTargets].velocity = -velocity;
		break;
	default:
		break;
	}
	targets[numTargets].y = ((float)rand() / RAND_MAX) * 0.90; //random y position between 0 and 0.9
	numTargets++;
}


void moveTargets() {
	for (int i = 0; i < numTargets; i++) {
		targets[i].x += targets[i].velocity;

		//if the target is completely out of the gaming area
		if (targets[i].x > 0.75 || targets[i].x + TARGET_WIDTH < -1) {
			//remove the target 
			numTargets--;
			for (int j = i; j < numTargets; j++) {
				targets[j] = targets[j + 1];
			}
			i--; 
		}
	}
}

void drawTargets() {
	glColor3ub(255, 0, 0); //red

	for (int i = 0; i < numTargets; i++) {
		float x_left = targets[i].x;
		float x_right = targets[i].x + TARGET_WIDTH;

		//adjust x_left if target is moving from right to left and is outside the left boundary
		if (targets[i].velocity < 0 && x_left < -1.0) {
			x_left = -1.0;
		}

		//adjust x_right if target is moving from left to right and is outside the right boundary
		if (targets[i].velocity > 0 && x_right > 0.75) {
			x_right = 0.75;
		}

		glBegin(GL_POLYGON);
		glVertex2f(x_left, targets[i].y); //bottom-left vertex
		glVertex2f(x_right, targets[i].y); //bottom-right vertex
		glVertex2f(x_right, targets[i].y + 0.05); //top-right vertex
		glVertex2f(x_left, targets[i].y + 0.05); //top-left vertex
		glEnd();
	}
	
}

//drawing the cannon
void drawCannon() {
	//cannon base vertices
	double baseVertices[8] = {
		-0.05, 0.0,   // bottom left
		 0.05, 0.0,   // bottom right
		 0.05, 0.2,   // top right
		-0.05, 0.2    // top left
	};

	//cannon barrel vertices
	double barrelVertices[8] = {
		-0.02, 0.2,   // bottom left
		 0.02, 0.2,   // bottom right
		 0.02, 0.3,   // top right
		-0.02, 0.3    // top left
	};

	//draw cannon base
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(cannonX + baseVertices[0], cannonY + baseVertices[1]);
	glVertex2f(cannonX + baseVertices[2], cannonY + baseVertices[3]);
	glVertex2f(cannonX + baseVertices[4], cannonY + baseVertices[5]);
	glVertex2f(cannonX + baseVertices[6], cannonY + baseVertices[7]);
	glEnd();

	//draw cannon barrel
	glColor3f(0.9, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(cannonX + barrelVertices[0], cannonY + barrelVertices[1]);
	glVertex2f(cannonX + barrelVertices[2], cannonY + barrelVertices[3]);
	glVertex2f(cannonX + barrelVertices[4], cannonY + barrelVertices[5]);
	glVertex2f(cannonX + barrelVertices[6], cannonY + barrelVertices[7]);
	glEnd();
}

void drawBullet() {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2f(bulletX, bulletY);
	glEnd();
}

//keyboard input for moving the cannon
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A': //move cannon left
		if (cannonX > -0.9) {
			cannonX -= 0.05; //decrease cannon x-coordinate
		}
		break;
	case 'd':
	case 'D': //move cannon right
		if (cannonX + 0.15 < 0.75) {
			cannonX += 0.05; //increase cannon x-coordinate
		}
		break;
	case ' ': //fire bullet (SpaceBar)
		if (!bulletFired) {
			bulletX = cannonX ;
			bulletY = cannonY + 0.3;
			bulletFired = 1;
		}
		break;
	case 27: //ESC key to exit
		exit(0);
	default:
		break;
	}
	glutPostRedisplay(); 
}

void specialKeypress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1: //start or stop the game when F1 is pressed
		if (gameOver) { //if the game is over, start a new game
			gameOver = 0;
			gameRunning = 1;
			score = 0;
			elapsedTimeSeconds = 0;
			elapsedTimeMilliseconds = 0;
			numTargets = 0;
			bulletFired = 0;
			bulletY = 0;
		}
		else {
			gameRunning = !gameRunning;
			if (!gameRunning) {
				//reset game state when stopped
				elapsedTimeSeconds = 0;
				elapsedTimeMilliseconds = 0;
				numTargets = 0;
				bulletFired = 0;
				bulletY = 0;
			}
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//for texts
void stringprint(double x, double y, const char *string) {
	const char* str;
	glRasterPos2f(x, y);

	for (str = string; *str != '\0'; str++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *str);
	}

}

// to display onto window using OpenGL commands
void display(void) {
	glClearColor(0, 0, 0, 0); //clear color
	glClear(GL_COLOR_BUFFER_BIT);

	//gaming area
	glColor3ub(0, 119, 190);
	glRectf(-1, -0.9, 0.75, 1);

	glColor3ub(255, 255, 255);
	stringprint(0.8, 0.75, "REMAINING");
	stringprint(0.8, 0.70, "TIME:");
    stringprint(0.8, 0.50, "SCORE");

	if (!gameRunning && !gameOver) {
		//keyboard directions for when game is not running
		glColor3ub(128, 128, 128);
		stringprint(-0.3, -0.96, "Press F1 to Start");
		stringprint(0.8, 0.65, "20 SECONDS");
	}
	else if (gameOver) {
		//display game over message and score
		glColor3ub(255, 255, 255);
		stringprint(-0.3, 0.5, "Game Over!");
		char scoreText[20];
		sprintf(scoreText, "Score: %d", score);
		stringprint(-0.3, 0.4, scoreText);
		stringprint(-0.3, 0.3, "Please Press F1 to Start a New Game");

		
	}
	else {
		//keyboard directions for when game is running
		stringprint(-0.7, -0.96, "<a> Move Left, <d> Move Right, <SpaceBar> to Shoot, ESC to Leave The Game, F1 to Reset");

		//if the bullet hits any target
		for (int i = 0; i < numTargets; i++) {
			if (bulletFired && bulletX >= targets[i].x && bulletX <= targets[i].x + TARGET_WIDTH &&
				bulletY >= targets[i].y && bulletY <= targets[i].y + 0.05) {
				//bullet hits target
				bulletFired = 0;
				bulletY = 0;
				//remove the target
				for (int j = i; j < numTargets - 1; j++) {
					targets[j] = targets[j + 1];
				}
				numTargets--;
				//increment the score
				score++;
				break; //exit loop after hitting one target
			}
		}

		//draw targets
		generateTarget();
		moveTargets();
		drawTargets();

		//draw bullet if fired
		if (bulletFired) {
			drawBullet();
			bulletY += 0.02; //move bullet upwards
			if (bulletY > 1) { //if bullet goes out of the screen, reset
				bulletFired = 0;
				bulletY = 0;
			}
		}

		//update and display the timer
		elapsedTimeMilliseconds += 16; //increment elapsed time by approximately 16 milliseconds (to simulate 60 FPS). I had to learn this part from Internet.
		if (elapsedTimeMilliseconds >= 1000) {
			elapsedTimeSeconds++; //increment elapsed time by 1 second
			elapsedTimeMilliseconds -= 1000; //adjusting milliseconds
		}

		if (elapsedTimeSeconds >= 20) {
			// Game over
			gameRunning = 0;
			gameOver = 1;
		}

		int remainingSeconds = 20 - elapsedTimeSeconds;
		int remainingMilliseconds = 1000 - elapsedTimeMilliseconds;

		if (remainingSeconds <= 5) {
			//change color to yellow when 5 seconds or less are left
			//warning seconds
			glColor3f(1.0, 1.0, 0.0);
		}
		else {
			//the default color
			glColor3ub(128, 128, 128);
		}

		char timerText[30];
		sprintf(timerText, "%02d:%02d:%03d", remainingSeconds, remainingMilliseconds / 100, remainingMilliseconds % 100);
		stringprint(0.8, 0.65, timerText);

		//keeping the score
		glColor3ub(255, 255, 255);
		char scoreText[20];
		sprintf(scoreText, "%d", score);
		stringprint(0.8, 0.45, scoreText);
	}

	//draw the cannon
	drawCannon();

	glutSwapBuffers();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0); //update every 16 milliseconds (about 60 FPS)
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv); //initializing GLUT
	

	//window initialization
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("SelinEren HW2 Target Game");

	
	//event handler registration
	glutDisplayFunc(display); //event=display, call display
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(specialKeypress); 


	//main event loop
	glutMainLoop();

	return 0;
}
