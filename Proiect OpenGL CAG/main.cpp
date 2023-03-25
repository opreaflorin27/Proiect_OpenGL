#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359; //Valoarea lui PI pt calcule

//Initializarea functiilor
void display(void);
void reshape(int, int);
void timer(int);
void Circle(int, float, float, float, float);
void menu(int);
void Border(void);

//Valori globale (by default)
float speedx = 2;
float speedy = 4;
float posx = 0.0;
float posy = 10.0;
float posz = -220.0;
float angle = 0.0;
int statex = 1;
int statey = 1;
int statez = 1;
int angle_time = 9;
int gamble = 0;

void init() //Initializeaza ecranul
{
	glClearColor(0.5, 0.3, 0.9, 1.0); //Culoarea Background-ului
	glEnable(GL_DEPTH_TEST); //permite lucrarea in 3D
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);//Initializare glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); // Pt culori RGB | Pt 3D | Pt animatii
	glutInitWindowPosition(600, 0); //Unde se va afisa ecranul
	glutInitWindowSize(1000, 1000);// Resolutia ecranului
	glutCreateWindow("Zar"); //Face ecranul si il numeste "Zar"
	glutDisplayFunc(display); //Functia de display
	glutReshapeFunc(reshape); //Functia de reshape
	glutTimerFunc(0, timer, 0); //Functia de timp
	init(); //Apeleaza init
	glutCreateMenu(menu);//Adauga un meniu pr program
	glutAddMenuEntry("Increase the horizontal speed", 1); //Creste viteza pe axa Ox
	glutAddMenuEntry("Increase the vertical speed", 2); //Creste viteza pe axa Oy
	glutAddMenuEntry("Decrease the horizontal speed", 3); //Scade viteza pe axa Ox
	glutAddMenuEntry("Decrease the vertical speed", 4); //Scade viteza pe axa Oy
	glutAddMenuEntry("Gamble", 5); //Seteaza viteza zarului la o valoare ft mare
	glutAddMenuEntry("Reset", 6); //Reseteaza vitezele zarului
	glutAddMenuEntry("Stop the Dice", 7); //Opreste zarul in centrul ecranului
	glutAddMenuEntry("Quit", 0); //Se iese din program
	glutAttachMenu(GLUT_RIGHT_BUTTON); //Meniul se deschide apasand "Click Dreapta"

	glutMainLoop(); //Functia de loop (pt a nu se inchide ecranul instant)

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Frame buffer, curata pixelii de pe ecran (curata ecranul)
	glLoadIdentity();

	glTranslatef(posx, posy, posz); //Pozitia zarului in ecran

	//Rotirea zarului
	glRotatef(angle, 0, 0, 1);
	glRotatef(angle, 0, 1, 0);
	glRotatef(angle, 1, 0, 0);
	
	Border();//Aplica bordurile pt zar

	//Fata de valoare 1
	Circle(3, 0, 0, 10.01, 2.5);

	//Spate de valoare 6
	Circle(3, -5, 5, -10.01, 2.5);
	Circle(3, -5, 0, -10.01, 2.5);
	Circle(3, -5, -5, -10.01, 2.5);
	Circle(3, 5, 5, -10.01, 2.5);
	Circle(3, 5, 0, -10.01, 2.5);
	Circle(3, 5, -5, -10.01, 2.5);

	//Dreapta de valoare 2
	Circle(1, 10.01, 5, -5, 2.5);
	Circle(1, 10.01, -5, 5, 2.5);

	//Stanga de valoare 5
	Circle(1, -10.01, 0, 0, 2.5);
	Circle(1, -10.01, 5, 5, 2.5);
	Circle(1, -10.01, 5, -5, 2.5);
	Circle(1, -10.01, -5, -5, 2.5);
	Circle(1, -10.01, -5, 5, 2.5);

	//Sus de valoare 3
	Circle(2, 5, 10.01, 5, 2.5);
	Circle(2, 0, 10.01, 0, 2.5);
	Circle(2, -5, 10.01, -5, 2.5);

	//Jos de valoare 4
	Circle(2, 5, -10.01, 5, 2.5);
	Circle(2, 5, -10.01, -5, 2.5);
	Circle(2, -5, -10.01, -5, 2.5);
	Circle(2, -5, -10.01, 5, 2.5);

	//Fetele cubului//
	glBegin(GL_QUADS); 

	//Fata (Axa Oz nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(-10, 10, 10);
	glVertex3f(-10, -10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, 10, 10);

	//Spate (Axa Oz nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(10, 10, -10);
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, 10, -10);

	//Dreapta (Axa Ox nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(10, 10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, -10, -10);
	glVertex3f(10, 10, -10);

	//Stanga (Axa Ox nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(-10, 10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glVertex3f(-10, 10, 10);

	//Sus (Axa Oy nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(-10, 10, -10);
	glVertex3f(-10, 10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, -10);

	//Jos (Axa Oy nu se modifica)
	glColor3f(1, 1, 1);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, -10, -10);

	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 20, 500);
	glMatrixMode(GL_MODELVIEW);

}

void Circle(int a, float x, float y, float z, float radius) //Deseenaza un cerc plin (folosind triunghiuri)
{
	int i;
	int triangleAmount = 16; //Numarul de triunghiuri folosite pt a desena cercul

	float twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.0, 0.0); //Cercurile vor fi negre
	glVertex3f(x, y, z); // Centrul cercului
	if (a == 1) //Verifica pe ce axa sa genereze cercul (Ox, Oy sau Oz)
	{
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex3f
			(
				x,
				y + (radius * sin(i * twicePi / triangleAmount)),
				z + (radius * cos(i * twicePi / triangleAmount))
			);
		};
	}
	else if (a == 2)
	{
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex3f
			(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y,
				z + (radius * sin(i * twicePi / triangleAmount))
			);
		};
	}
	else if (a == 3)
	{
		for (i = 0; i <= triangleAmount; i++)
		{
			glVertex3f
			(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount)),
				z
			);
		}
	}
	glEnd();
}

void Border(void) //Functia pt borduri
{
	glBegin(GL_LINE_LOOP); //Bordura fata
	glColor3f(0, 0, 0);
	glVertex3f(-10, 10, 10);
	glVertex3f(-10, -10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, 10, 10);
	glEnd();

	glBegin(GL_LINE_LOOP); //Bordura spate
	glColor3f(0, 0, 0);
	glVertex3f(10, 10, -10);
	glVertex3f(10, -10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, 10, -10);
	glEnd();

	glBegin(GL_LINE_LOOP); //Bordura dreapta
	glColor3f(0, 0, 0);
	glVertex3f(10, 10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, -10, -10);
	glVertex3f(10, 10, -10);
	glEnd();

	glBegin(GL_LINE_LOOP);  //Bordura stanga
	glColor3f(0, 0, 0);
	glVertex3f(-10, 10, -10);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glVertex3f(-10, 10, 10);
	glEnd();

	glBegin(GL_LINE_LOOP); //Bordura sus
	glColor3f(0, 0, 0);
	glVertex3f(-10, 10, -10);
	glVertex3f(-10, 10, 10);
	glVertex3f(10, 10, 10);
	glVertex3f(10, 10, -10);
	glEnd();

	glBegin(GL_LINE_LOOP); //Bordura jos
	glColor3f(0, 0, 0);
	glVertex3f(-10, -10, -10);
	glVertex3f(-10, -10, 10);
	glVertex3f(10, -10, 10);
	glVertex3f(10, -10, -10);
	glEnd();
}

void timer(int) //Functia pt timp (seteaza FPS-ul si modifica unele valori in timp real)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0); //Seteaza sa ruleze programul la 60FPS

		switch (statex) //Adauga limitele si viteza pe care se misca zarul pe axa Ox
		{
		case 1:
			if (posx <= 95)
				posx += speedx;
			else
				statex = -1;
			break;
		case -1:
			if (posx >= -95)
				posx -= speedx;
			else
				statex = 1;
			break;
		}

		switch (statey) //Adauga limitele si viteza pe care se misca zarul pe axa Oy
		{
		case 1:
			if (posy <= 95)
				posy += speedy;
			else
				statey = -1;
			break;
		case -1:
			if (posy >= -95)
				posy -= speedy;
			else
				statey = 1;
			break;
		}

		if (gamble == 1)
		{
			switch (statez)
			{
			case 1:
				if (posz <= -200)
					posz += 30;
				else
					statez = -1;
				break;
			case -1:
				if (posz >= -300)
					posz -= 30;
				else
					statez = 1;
				break;
			}
		
		}
		else posz = -220;
		angle += angle_time; //Unghiul de rotire al zarului
		if (angle >= 360.0)
			angle -= 360.0;
}

void menu(int value) //Functia pt meniu
{
	switch (value) 
	{
	case 1: //Viteza Oy
	{
		speedx += 2;
		angle_time += 3;
	}
		break;
	case 2: //Viteza Oy
	{
		speedy += 2;
		angle_time += 3;
	}
		break;
	case 3: //Frana Ox
		if(speedx > 0)
			speedx -= 2, angle_time -= 3;
		break;
	case 4: //Frana Oy
		if (speedy > 0)
			speedy -= 2, angle_time -= 3;
		break;
	case 5: //Gamble
	{
		speedx = 30;
		speedy = 38;
		angle_time = 102;
		gamble = 1;
		glClearColor(0, 0, 0.3, 1.0);
	}
		break;
	case 6: //Reset
	{
		speedx = 2;
		speedy = 4;
		angle_time = 9;
		gamble = 0;
		glClearColor(0.5, 0.3, 0.9, 1.0);
	}
	break;
	case 7: //Stop
	{
		speedx = 0;
		speedy = 0;
		angle_time = 0;
		gamble = 0;
		posx = 0;
		posy = 0;
		glClearColor(1, 0.5, 1, 1.0);
	}
		break;
	case 0: //Quit
		exit(0);
	}
}