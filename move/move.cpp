#include <math.h>
#include <cstdlib>
#include <GL/glut.h>
#include<vector>



typedef struct _Vector {
	double x, y, z;
}; _Vector;

const int	SCREEN_WIDTH = 800;
const int	SCREEN_HEIGHT = 600;
const double PI = 3.14;

double radian;
double speed = 10;
double rot;

_Vector pos;
_Vector vel;
_Vector dir;
_Vector dis;
_Vector mouseCoords;
//vector<double> vel;
//vector<double> dir;
//vector<double> dis;
//vector<double> mouseCoords;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -100, 100);
	glColor3f(1, 0, 0);
	glTranslated(pos.x, pos.y, 0);
	glRotatef(rot, 0, 0, 1);
	glutSolidTeapot(10);
	glFlush();
	glutSwapBuffers();

}
void mouse(int btn, int state, int x, int y) {
	mouseCoords.x = x - SCREEN_WIDTH / 2;
	mouseCoords.y= -y + SCREEN_HEIGHT / 2;
}
void move() {
	dis.x = mouseCoords.x - pos.x;
	dis.y = mouseCoords.y - pos.y;
	if (sqrt(dis.y * dis.y + dis.x * dis.x) < speed) {
		pos.x = mouseCoords.x;
		pos.y = mouseCoords.y;
	}
	else {
		radian = atan2(dis.y, dis.x);
		pos.x += cos(radian) * speed;
		pos.y += sin(radian) * speed;
		rot = radian * 100 / PI;

	}
}

void update(int value) {
	move();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}
void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("click to move");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutTimerFunc(25, update, 0);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return(0);
}

