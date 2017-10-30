#include <GLFW/glfw3.h>
#include <stdlib.h>
void DrawRect(int x, int y, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void DrawNumber(int x, int y, int n);
void Reset();
void Collisions();
bool Between(int target, int min, int max);


#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 450
const int RacketWidth = 10, RacketHeight = 100;
const int BallWidth = 10, BallHeight = 10;

double time;

int LeftY = 0;
int RightY = 0;
int Racketspeed = 5;

int ballX, ballY;
int ballVelocityX = 1;
float ballVelocityY = 0.0f;
float StoredVelocity = 0.0f;

//Ball Speed
double TimeSpeed = 0.2;

int LeftScore = 0;
int RightScore = 0;

int main(void)
{

	GLFWwindow *window;

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "sierpinski", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment
					  //Ball Starting position
	ballX = SCREEN_WIDTH / 2 - 5;
	ballY = SCREEN_HEIGHT / 2 - 5;

	//Racket Starting Y Position
	LeftY = SCREEN_HEIGHT / 2 - 50;
	RightY = SCREEN_HEIGHT / 2 - 50;

	time = glfwGetTime()*TimeSpeed;


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render OpenGL here
		
		processInput(window);
		Collisions();
		DrawRect(0, LeftY, RacketWidth, RacketHeight);
		//Right Racket
		DrawRect(SCREEN_WIDTH - 10, RightY, RacketWidth, RacketHeight);
		//Ball
		DrawRect(ballX, ballY, BallWidth, BallHeight);
		DrawNumber(SCREEN_WIDTH / 2 - 40, 350, LeftScore);
		//Right Score
		DrawNumber(SCREEN_WIDTH / 2 + 10, 350, RightScore);

		DrawRect(SCREEN_WIDTH / 2 - 2, 390, 5, 5);
		DrawRect(SCREEN_WIDTH / 2 - 2, 360, 5, 5);






		// Swap front and back buffers
		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		// Poll for and process events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void DrawRect(int x, int y, int width, int height)
{


	glBegin(GL_QUADS);

	//Buttom Left
	glVertex2f(x, y);
	//Buttom Right
	glVertex2f(x + width, y);
	//Top Right
	glVertex2f(x + width, y + height);

	glVertex2f(x, y + height);

	glEnd();


}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Left Control down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

		RightY -= Racketspeed;
	}
	//Left Control up
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		RightY += Racketspeed;
	}
	//Right Control down
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		LeftY -= Racketspeed;
	}
	//Right Control up
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		LeftY += Racketspeed;
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void DrawNumber(int x, int y, int n)
{



	switch (n) {

	case 0:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;

	case 1:
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		break;
	case 2:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 3:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 4:
		
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		
		break;
	case 5:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);

		break;
	case 6:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 7:
		
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);

		break;
	case 8:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 9:
		
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);

		break;

	}
}

void Collisions() {

	if (glfwGetTime() - time > 1.0) {

		time = glfwGetTime()*TimeSpeed;

		ballX += ballVelocityX;

		StoredVelocity += ballVelocityY;

		if (StoredVelocity > 1.0f) {
			ballY += 1;
			StoredVelocity -= 1;
		}
		else if (StoredVelocity < -1.0f) {
			ballY -= 1;
			StoredVelocity += 1;

		}
	}


	//Ball at Right Edge
	if (ballX > SCREEN_WIDTH - RacketWidth * 2) {

		if (Between(ballY, RightY + RacketHeight, RightY)) {

			ballVelocityX = -ballVelocityX;

			if (Between(ballY, RightY, RightY + RacketHeight*0.3)) {

				ballVelocityY -= 0.3;

			}
			else if (Between(ballY, RightY + RacketHeight - RacketHeight*0.3, RightY + RacketHeight)) {

				ballVelocityY += 0.3;

			}


		}
		else {

			LeftScore++;
			Reset();

		}

		//Ball at Left Edge
	}
	else if (ballX < RacketWidth) {

		if (Between(ballY, LeftY + RacketHeight, LeftY)) {

			ballVelocityX = -ballVelocityX;

			if (Between(ballY, LeftY, LeftY + RacketHeight*0.3)) {

				ballVelocityY -= 0.3;

			}
			else if (Between(ballY, LeftY + RacketHeight - RacketHeight*0.3, RightY + RacketHeight)) {

				ballVelocityY += 0.3;
			}

		}
		else {

			RightScore++;
			Reset();

		}

		//Ball at Buttom Edge
	}
	else if (ballY < 0) {

		ballY = 0;
		ballVelocityY = -ballVelocityY;

		//Ball at Top Edge
	}
	else if (ballY > SCREEN_HEIGHT - BallHeight) {

		ballY = SCREEN_HEIGHT - BallHeight;
		ballVelocityY = -ballVelocityY;

	}

}


bool Between(int target, int a, int b) {

	int max;
	int min;

	if (a > b) {

		max = a;
		min = b;

	}
	else {
		max = b;
		min = a;
	}

	if (target < max && target > min)
		return true;

	return false;

}

void Reset() {

	ballX = SCREEN_WIDTH / 2 - BallWidth / 2;
	ballY = SCREEN_HEIGHT / 2 - BallHeight / 2;
	glfwSetTime(0.0);
	time = 0.0;
	ballVelocityX = 1;
	ballVelocityY = 0;
	StoredVelocity = 0;

	if (LeftScore > 9 || RightScore > 9) {

		LeftScore = 0;
		RightScore = 0;
	}
}
