#include <stdlib.h>
#include <GL/glut.h>  
#include <math.h>


GLfloat PI = 3.14159;
GLfloat gridSize = 40;
//door 
GLfloat door = 0.0;
//Animation
GLfloat animStart = 0.0;
GLfloat frameNumber = 0.0;
GLfloat animYRot = 0.0;

int firsttime = 0;
float x = 0, y = 0, z = 0.0;
GLfloat oldy = 0, oldz = 0, tempz, dy = 0, dz = 0;
int triggered = 0;

//basketball animation
GLfloat ballY = 0.0;
GLfloat speedY = 0.0;
static int flag = 0;
static int flag1 = 0;
GLfloat shooty = 0.0;
GLfloat shootz = 0.0;

//Man4 moves
GLfloat lefthandRotX = 0.0;

//Man2 moves
GLfloat handRotZ = 0.0;
GLfloat legRotZ = 0.0;

//Man moves
GLfloat righthandRotY = 0.0;
GLfloat lefthandRotY = 0.0;
GLfloat rightlegRotX = 0.0;
GLfloat leftlegRotX = 0.0;
GLfloat walkX = 0.0;
GLfloat walkY = 0.0;
GLfloat walkZ = 0.0;
//variables to move the camera
GLfloat camX = 0.0;
GLfloat camY = 10;
GLfloat camZ = 20;

//variables to move the scene
GLfloat sceX = 0.0;
GLfloat sceY = 0.0;
GLfloat sceZ = 0.0;

void init() {
    glClearColor(0.70f, 0.70f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); //do depth comparisons and update the depth buffer
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    /*glLineWidth(0.5);*/

}


void lines(float a, float b, float c, float d)
{

    //a = -2.5, b = -0.05 c = 0.05 d = 2.5

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(a, 0, b);
    glVertex3f(d, 0, b);
    glVertex3f(d, 0, c);
    glVertex3f(a, 0, c);
    glEnd();


}
void semicircle(float r)
{
    int i;

    glPointSize(1.45);
    glBegin(GL_POINTS);
    for (i = 0; i < 1000; i++)
    {
        glVertex3f((r * cos(1 * PI * i / 1000)), 0, 4.05 - (r * sin(1 * PI * i / 1000)));
        glVertex3f((r * cos(1 * PI * i / 1000)), 0, -4.05 + (r * sin(1 * PI * i / 1000)));
    }
    glEnd();
}
void circle(float r, GLfloat pointsize)
{
    int i;

    glPointSize(pointsize);
    glBegin(GL_POINTS);
    for (i = 0; i < 1000; i++)
    {
        //x and y defines the radius
        glVertex3f((r * cos(2 * PI * i / 1000)), 0, (r * sin(2 * PI * i / 1000)));
    }
    glEnd();
}

//void circlePolygn(float r)
//{
//    int i;
//    glColor3f(1.0, 1.0, 1.0);
//    glPointSize(1.5);
//    glBegin(GL_POLYGON);
//    for (i = 0; i < 1000; i++)
//    {
//        //x and y defines the radius
//        glVertex3f((r * cos(2 * PI * i / 1000.0)), 0, (r * sin(2 * PI * i / 1000.0)));
//    }
//    glEnd();
//}
void pole1() {
    glTranslatef(0, 0.1, 0);
    glutSolidCube(0.2);
}

void pole2() {
    glTranslatef(0, 0.1, -0.1);
    glColor3f(0.21, 0.2, 0.19);
    glScalef(1, 6, 1);
    glutSolidCube(0.2);
}
void onBoardLines(float a, float b, float c, float d)
{
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(a, b, 0);
    glVertex3f(d, b, 0);
    glVertex3f(d, c, 0);
    glVertex3f(a, c, 0);
    glEnd();

}
void boxBoard() {
    glPushMatrix();
    glColor3f(0.21, 0.2, 0.6);
    glTranslatef(0, 0.05, 0);
    glScalef(20, 25, 1);
    glutSolidCube(0.05);
    glPopMatrix();
}
void cylinder(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */

    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */

    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

}
void NetVetical(GLfloat x, GLfloat y, GLfloat increment) {
    glBegin(GL_LINES);
    /* glLineWidth(2);*/
    int i;
    for (i = 0;i < 14;i++) {
        glVertex3f(x, y, 0);
        glVertex3f(x, y - 3, 0);
        x -= increment;
    }
    glEnd();



}
void NetHorizontal(GLfloat x, GLfloat y, GLfloat increment) {
    glBegin(GL_LINES);
    /* glLineWidth(2);*/
    int i;
    for (i = 0;i < 8;i++) {
        glVertex3f(x, y, 0);
        glVertex3f(-x, y, 0);
        y -= increment;
    }
    glEnd();

}


void basketBall()
{
    glPushMatrix();
    glColor3f(0.9, 0.3, 0.0);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();


}
void man() {
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glColor3f(0.6, 0.3, 0);
    glScalef(1.4, 1, 0.8);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    //body
    glPushMatrix();
    glScaled(1, 1, 0.2);
    glTranslatef(0, 2.3, 0);
    glColor3f(0.2, 0.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    //Legs
    glPushMatrix();
    glTranslatef(-0.2, 2, 0);
    glRotatef(leftlegRotX, 1, 0, 0);
    glPushMatrix();
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0.2);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //leg1
    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glRotatef(rightlegRotX, 1, 0, 0);
    glPushMatrix();
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0.2);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //Hands
    glPushMatrix();
    glRotatef(-lefthandRotY, 0, 1, 0);

    glPushMatrix();
    glTranslatef(0.45, 2.7, 0);
    glRotated(30, 0, 0, 1);

    glPushMatrix();
    glScaled(0.2, 1, 0.05);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(righthandRotY, 0, 1, 0);
    glPushMatrix();
    glTranslatef(-0.45, 2.7, 0);
    glRotated(-30, 0, 0, 1);
    glPushMatrix();
    glScaled(0.2, 1, 0.05);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    //eyes
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //mouth
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0, 2.9f, 0.16f);
    glScalef(0.18, 0.05, 0.05);
    glutSolidCube(1);
    glPopMatrix();
}
//shoot basketball
void man5(GLfloat Rot1, GLfloat Rot2, GLfloat x, GLfloat y, GLfloat z, GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glColor3f(0.6, 0.3, 0);
    glScalef(1.4, 1, 0.8);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    //body
    glPushMatrix();
    glScaled(1, 1, 0.2);
    glTranslatef(0, 2.3, 0);
    glColor3f(R, G, B);
    glutSolidCube(1);
    glPopMatrix();

    //Leg1
    glPushMatrix();
    glTranslatef(-0.2, 2, 0);
    glPushMatrix();
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //leg2
    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glPushMatrix();
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //Hands 1

    glPushMatrix();
    glTranslatef(0.45, 2.7, 0);
    glRotated(Rot1, x, y, z);

    glPushMatrix();
    glScaled(0.2, 1, 0.05);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //hand2
    glPushMatrix();
    glTranslatef(-0.45, 2.7, 0);
    glRotated(Rot2, x, y, z);
    glPushMatrix();
    glScaled(0.2, 1, 0.05);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //eyes
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //mouth
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0, 2.9f, 0.16f);
    glScalef(0.18, 0.05, 0.05);
    glutSolidCube(1);
    glPopMatrix();
}
//man exercising
void man2(GLfloat R, GLfloat G, GLfloat B) {
    //body
    glPushMatrix();
    glScaled(1, 1, 0.3);
    glTranslatef(0, 2.3, 0);
    glColor3f(R, G, B);
    glutSolidCube(1);
    glPopMatrix();

    //Buttons
    glPushMatrix();
    glTranslatef(0, 2.7, 0.15);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.3, 0.15);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.9, 0.15);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();


    //head
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glScalef(1.4, 1, 0.8);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    //Legs
    glPushMatrix();
    glTranslatef(-0.2, 2, 0);
    glRotatef(-legRotZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(R + 1, G, B);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //leg 2
    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glRotatef(legRotZ, 0, 0, 1);
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glScaled(0.2, 1.4, 0.1);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(R + 1, G, B);
    glTranslatef(0, -0.1, 0);
    glScaled(1.2, 1, 0.5);
    glRotatef(90, 1, 0, 0);
    cylinder(0.25, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.4, 0);
    glScaled(1.3, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //Hands
    glPushMatrix();
    glTranslatef(0.45, 2.7, 0);
    glRotatef(-handRotZ, 0, 0, 1);
    glPushMatrix();
    glScaled(1, 0.2, 0.05);
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0.5, 0, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45, 2.7, 0);
    glRotatef(handRotZ, 0, 0, 1);
    glPushMatrix();
    glScaled(1, 0.2, 0.05);
    glTranslatef(-0.5, 0, 0);
    glColor3f(0.2, 0.2, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glScaled(1.2, 1, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.08, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    //eyes
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //mouth
    glPushMatrix();
    glTranslatef(0, 2.9f, 0.16f);
    glScalef(0.18, 0.05, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}
void smallFenceOnCompound() {
    glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(-20, 0, 0);
    glRotatef(-90, 1, 0, 0);
    cylinder(0.15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 0, 0);
    glRotatef(-90, 1, 0, 0);
    cylinder(0.15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 1, 0);
    glRotatef(90, 0, 1, 0);
    cylinder(0.2, 40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 2, 0);
    glRotatef(90, 0, 1, 0);
    cylinder(0.2, 40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 3, 0);
    glRotatef(90, 0, 1, 0);
    cylinder(0.2, 40);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 4, 0);
    glRotatef(90, 0, 1, 0);
    cylinder(0.2, 40);
    glPopMatrix();
}

void compound(void)
{
    //Entrance 
    //left door
    glPushMatrix();
    glTranslatef(-8, -1, 60);
    glRotatef(-door, 0, 1, 0);

    glPushMatrix();
    glPushMatrix();
    glTranslatef(4, 5, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.4, 10);
    glColor3f(0.5, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 5, 0.5);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    //right door
    glPushMatrix();
    glTranslatef(8, -1, 60);
    glRotatef(door, 0, 1, 0);

    glPushMatrix();
    glPushMatrix();
    glTranslatef(-4, 5, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.4, 10);
    glColor3f(0.5, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 5, 0.5);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();



    glPushMatrix();
    glColor3f(0.1, 0, 0);
    //back wall of compound
    glPushMatrix();
    glTranslatef(0, 4, -60);
    glRotatef(-90, 1, 0, 0);
    glScalef(80, 0.4, 10);
    glutSolidCube(1.0);
    glPopMatrix();


    //front left wall of compound                
    glPushMatrix();
    glTranslatef(-24, 4, 60);
    glRotatef(-90, 1, 0, 0);
    glScalef(32, 0.4, 10);
    glutSolidCube(1.0);
    glPopMatrix();
    //front right wall of compound
    glPushMatrix();
    glTranslatef(24, 4, 60);
    glRotatef(-90, 1, 0, 0);
    glScalef(32, 0.4, 10);
    glutSolidCube(1.0);
    glPopMatrix();



    //middle left wall of compound                
    glPushMatrix();
    glTranslatef(40, 4, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(120, 0.4, 10);
    glutSolidCube(1.0);
    glPopMatrix();
    //middle right wall of compound
    glPushMatrix();
    glTranslatef(-40, 4, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(120, 0.4, 10);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    //floor
    glPushMatrix();
    glColor3f(0.5, 0.2, 0);
    glTranslatef(0, -0.8, 0);
    glScalef(80, 0, 120);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //fence
    //back fence
    glPushMatrix();
    glTranslatef(0, 8.5, -80);
    glScalef(2, 1, 1);
    smallFenceOnCompound();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 3);
    glTranslatef(-40, 8.4, -6.7);
    glRotatef(90, 0, 1, 0);
    smallFenceOnCompound();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 3);
    glTranslatef(40, 8.4, -6.7);
    glRotatef(90, 0, 1, 0);
    smallFenceOnCompound();
    glPopMatrix();
}
void BasketBallSideBench() {
    //sitting area(horizontal)
    glPushMatrix();
    glColor3f(0.2f, 0.0f, 0.0f);
    glTranslatef(0, 1.5, 0);
    glScalef(8, 0.3, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    //vertical

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(0, 2.2, -0.6);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.2, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(0, 2.7, -0.6);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.2, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(0, 3.2, -0.6);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.2, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(0, 3.7, -0.6);
    glRotatef(-90, 1, 0, 0);
    glScalef(8, 0.2, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(-3.5, 1.5, -0.6);
    glScalef(1, 13, 1);
    pole1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    glTranslatef(3.5, 1.5, -0.6);
    glScalef(1, 13, 1);
    pole1();
    glPopMatrix();

    //chair legs
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(3.8, 0, 0.6);
    glScalef(1, 8, 1);
    pole1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-3.8, 0, 0.6);
    glScalef(1, 8, 1);
    pole1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(3.8, 0, -0.6);
    glScalef(1, 8, 1);
    pole1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-3.8, 0, -0.6);
    glScalef(1, 8, 1);
    pole1();
    glPopMatrix();
}


void BasketBallCourt() {
    //base
    glPushMatrix();
    glColor3f(0.3, 0.2, 0.2);
    glScalef(7, 0.5, 11);
    glutSolidCube(1);
    glPopMatrix();

    //lines
    glPushMatrix();
    glTranslatef(0, 0.3, 0);
    //center line
    lines(-2.5, -0.05, 0.05, 2.5);

    //side lines
    lines(-2.50, 4.7, -4.7, -2.55);
    lines(2.50, 4.7, -4.7, 2.55);

    //base lines
    lines(-2.55, 4.70, 4.75, 2.55);
    lines(-2.55, -4.70, -4.75, 2.55);


    //three pointer lines
    lines(-2.2, 4.7, 4.05, -2.27);
    lines(2.2, 4.7, 4.05, 2.27);

    lines(-2.2, -4.7, -4.05, -2.27);
    lines(2.2, -4.7, -4.05, 2.27);

    //two pointer lines
    lines(-0.6, 4.7, 2.8, -0.64);
    lines(0.6, 4.7, 2.8, 0.64);

    lines(-0.6, -4.7, -2.8, -0.64);
    lines(0.6, -4.7, -2.8, 0.64);

    //lines joining the above two lines
    lines(-0.6, 2.8, 2.84, 0.6);
    lines(-0.6, -2.8, -2.84, 0.6);

    //curves in court
    glColor3f(1.0, 1.0, 1.0);
    circle(0.6, 1.45);
    semicircle(2.22);
    glPopMatrix();

    //poles
    glPushMatrix();
    glColor3f(0.21, 0.2, 0.19);
    glTranslatef(0, 0, -5);
    glScalef(1, 30, 1);
    pole1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.21, 0.2, 0.19);
    glTranslatef(0, 0, 5);
    glScalef(1, 30, 1);
    pole1();
    glPopMatrix();

    //angle poles
    glPushMatrix();
    glTranslatef(0, 6, 4.7);
    glRotatef(-35, 1, 0, 0);
    pole2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6, -4.6);
    glRotatef(35, 1, 0, 0);
    pole2();
    glPopMatrix();

    //boxBoard
    glPushMatrix();
    glScalef(2, 2, 1);

    glPushMatrix();
    glTranslatef(0, 3.5, -4.2);
    boxBoard();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3.5, 4.1);
    boxBoard();
    glPopMatrix();

    //vertical lines on the board
    glPushMatrix();
    glTranslatef(0, 2, 4.0);
    onBoardLines(-0.15, 1.2, 1.24, 0.15); //bottom
    onBoardLines(-0.15, 1.5, 1.54, 0.15); //down
    onBoardLines(-0.15, 1.2, 1.5, -0.10);
    onBoardLines(0.15, 1.2, 1.5, 0.10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, -4.1);
    onBoardLines(-0.15, 1.2, 1.24, 0.15); //bottom
    onBoardLines(-0.15, 1.5, 1.54, 0.15); //down
    onBoardLines(-0.15, 1.2, 1.5, -0.10);
    onBoardLines(0.15, 1.2, 1.5, 0.10);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.2, -3.9);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 1, 1);
    glutSolidTorus(0.03, 0.2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.2, 3.8);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 1, 1);
    glutSolidTorus(0.03, 0.2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.2, 3.8);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 1, 1);
    glutWireCone(0.2, 0.8, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.2, -3.9);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 1, 1);
    glutWireCone(0.2, 0.8, 20, 20);
    glPopMatrix();

    //balls
    glPushMatrix();
    glTranslatef(0, ballY, 0);
    glPushMatrix();
    glTranslatef(-2, 0.5, 3);
    glScalef(1, 2, 1);
    basketBall();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1, 0.5, 2);
    glScalef(1, 2, 1);
    basketBall();
    glPopMatrix();




}
void badmintonCourt() {
    //base
    glPushMatrix();
    glColor3f(0.2, 0.2, 0);
    glScalef(15, 1, 25);
    glutSolidCube(0.5);
    glPopMatrix();

    //lines
    glPushMatrix();
    glTranslatef(0, 0.3, 0);
    //center line
    lines(-2.5, -0.05, 0.05, 2.5);
    lines(-0.025, -4.7, 4.7, 0.025);

    //side lines
    lines(-2.50, 4.7, -4.7, -2.55);
    lines(2.50, 4.7, -4.7, 2.55);

    //base lines
    lines(-2.55, 4.70, 4.75, 2.55);
    lines(-2.55, -4.70, -4.75, 2.55);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.6, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 0);
    cylinder(0.15, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.6, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 0);
    cylinder(0.15, 6);
    glPopMatrix();

   /* glPushMatrix();
    glColor3f(1, 1, 1);
    NetHorizontal(2.6, 6, 0.4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    NetVetical(2.5, 6, 0.4);
    glPopMatrix();*/


}


void shuttlecock() {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glutWireCone(0.2, 0.3, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0.28);
    glColor3f(1, 0, 0);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();

}
void badmintonRacketLines() {
    //Horizontal
    GLfloat x = 0.5;
    GLfloat y = 0;
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    int i;
    for (i = 0; i < 5; i++) {
        glVertex3f(-x, y, 0);
        glVertex3f(x, y, 0);

        x = x - 0.05;
        y = y + 0.1;
    }
    glEnd();

    GLfloat x1 = 0.45;
    GLfloat y1 = -0.1;
    glBegin(GL_LINES);
    int j;
    for (j = 0; j < 5; j++) {
        glVertex3f(-x1, y1, 0);
        glVertex3f(x1, y1, 0);

        x1 = x1 - 0.05;
        y1 = y1 - 0.1;
    }

    glEnd();

    //Vertical
    GLfloat w = 0;
    GLfloat z = 0.5;
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    int k;
    for (k = 0; k < 5; k++) {
        glVertex3f(w, z, 0);
        glVertex3f(w, -z, 0);

        w = w - 0.1;
        z = z - 0.05;
    }
    glEnd();

    //Vertical
    GLfloat w1 = 0;
    GLfloat z1 = 0.5;
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    int l;
    for (l = 0; l < 5; l++) {
        glVertex3f(w1, z1, 0);
        glVertex3f(w1, -z1, 0);

        w1 = w1 + 0.1;
        z1 = z1 - 0.05;
    }
    glEnd();


}

void badmintonRacket() {
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glRotatef(90, 1, 0, 0);
    cylinder(0.05, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glutSolidTorus(0.05, 0.5, 50, 50);
    badmintonRacketLines();
    glPopMatrix();



}
void badmintonRacketBucket() {

    glPushMatrix();
    glTranslatef(0, 1, 0);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.3, 0.3);
    cylinder(0.5, 2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0.5, 0.5);
    glTranslatef(0, 0, -0.3);
    badmintonRacket();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.1, 0.5);
    glRotatef(30, 0, 1, 0);
    glTranslatef(0.3, 0, 0);
    badmintonRacket();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glRotatef(20, 0, 1, 0);
    glTranslatef(-0.3, 0, 0.2);
    badmintonRacket();
    glPopMatrix();

}
void tableTennis() {
    //base
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glColor3f(0, 1, 0);
    glScalef(25, 1, 30);
    glutSolidCube(0.2);
    glPopMatrix();

    //lines
    glPushMatrix();
    glTranslatef(0, 0.3, 0);
    //center line
    lines(-2.0, -0.05, 0.05, 2.0);

    //side lines
    lines(-2.0, 2.3, -2.3, -2.05);
    lines(2.0, 2.3, -2.3, 2.05);

    //base lines
    lines(-2.05, 2.3, 2.35, 2.05);
    lines(-2.05, -2.3, -2.35, 2.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.06, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 0);
    cylinder(0.15, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.06, 0, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 0);
    cylinder(0.15, 2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    NetHorizontal(2.06, 2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 1, 0);
    glScalef(1, 0.5, 1);
    NetVetical(2.08, 2, 0.3);
    glPopMatrix();
    glPopMatrix();

    //table legs
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(2.35, 0, 2.05);
    glScalef(1, 15, 1);
    pole1();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-2.35, 0, -2.05);
    glScalef(1, 15, 1);
    pole1();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-2.35, 0, 2.05);
    glScalef(1, 15, 1);
    pole1();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(2.35, 0, -2.05);
    glScalef(1, 15, 1);
    pole1();
    glPopMatrix();

}
//weight lifting equipments
void barbell(GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(0.21, 0.2, 0.19);
    cylinder(0.3, 14);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 0, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(R, G, B);
    glutSolidTorus(0.9, 1, 10, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(11, 0, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(R, G, B);
    glutSolidTorus(0.9, 1, 10, 100);
    glPopMatrix();
}

void smallbarbell(GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(0.21, 0.2, 0.19);
    cylinder(0.1, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(R, G, B);
    glutSolidTorus(0.2, 0.3, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, 0, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(R, G, B);
    glutSolidTorus(0.2, 0.3, 10, 10);
    glPopMatrix();
}
void weightLiftingItems() {
    //big barbells
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    barbell(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, -5);
    barbell(0.5, 0.1, 0.1);
    glPopMatrix();

    //small barbells
    glPushMatrix();
    glTranslatef(2, 0, 5);
    smallbarbell(0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0, 5);
    smallbarbell(0.5, 0.5, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 7);
    smallbarbell(0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0, 7);
    smallbarbell(0.5, 0.5, 0.1);
    glPopMatrix();


}
void man3() {
    //head
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glColor3f(0.6, 0.3, 0);
    glScalef(1.4, 1, 0.8);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    //body
    glPushMatrix();
    glScaled(1, 1, 0.2);
    glTranslatef(0, 2.3, 0);
    glColor3f(0.2, 0.5, 0.6);
    glutSolidCube(1);
    glPopMatrix();

    //Legs
    glPushMatrix();
    glTranslatef(-0.2, 2, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //legs lower part
    glPushMatrix();
    glTranslatef(-0.2, 1.25, 0);
    glRotatef(30, 1, 0, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 1.25, 0);
    glRotatef(30, 1, 0, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //Hands

    glPushMatrix();
    glTranslatef(0.45, 2.7, 0);
    glRotated(-90, 1, 0, 0);
    glScaled(0.1, 1, 0.1);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.45, 2.7, 0);
    glRotated(-90, 1, 0, 0);
    glScaled(0.1, 1, 0.1);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();


    //eyes
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //mouth
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0, 2.9f, 0.16f);
    glScalef(0.18, 0.05, 0.05);
    glutSolidCube(1);
    glPopMatrix();

}
void manLiftbarbells() {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(4, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(-25, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glScalef(2, 0.1, 1);
    glColor3f(1, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.4, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glScalef(1, 0.1, 1);
    glColor3f(1, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5, 0.3, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(1, 2, 2);
    man3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 2.3, 1.4);
    glRotatef(90, 0, 1, 0);
    glScalef(0.2, 0.4, 0.4);
    barbell(0.5, 0.5, 0.1);
    glPopMatrix();

}
void man4(GLfloat R, GLfloat G, GLfloat B) {
    //head

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -1.8, 0);
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glColor3f(0.6, 0.3, 0);
    glScalef(1.4, 1, 0.8);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    //body
    glPushMatrix();
    glScaled(1, 1, 0.2);
    glTranslatef(0, 2.3, 0);
    glColor3f(R, G, B);
    glutSolidCube(1);
    glPopMatrix();

    //Hands

    glPushMatrix();
    glTranslatef(0.45, 2.7, 0);
    glRotated(-10, 1, 0, 0);
    glScaled(0.1, 1, 0.1);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.45, 2.7, 0);
    glRotated(-lefthandRotX, 1, 0, 0);
    glPushMatrix();
    glTranslatef(-0.3, -1, 0);
    glScaled(0.2, 0.4, 0.3);
    smallbarbell(1, 0, 0);
    glPopMatrix();
    glScaled(0.1, 1, 0.1);
    glColor3f(0.6, 0.3, 0);
    glTranslatef(0, -0.5, 0);
    glutSolidCube(1);
    glPopMatrix();


    //eyes
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.12f, 3.0f, 0.15f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //mouth
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0, 2.9f, 0.16f);
    glScalef(0.18, 0.05, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    //Legs
    glPushMatrix();
    glTranslatef(-0.2, 2, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 2, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    //legs lower part
    glPushMatrix();
    glTranslatef(-0.2, 1.25, 0);
    glRotatef(30, 1, 0, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 1.25, 0);
    glRotatef(30, 1, 0, 0);
    glPushMatrix();
    glScaled(0.1, 0.75, 0.1);
    glTranslatef(0, -0.5, 0);
    glColor3f(0.6, 0.3, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}

void manLiftsmallbarbells(GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(4, 0.1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(-25, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glScalef(2, 0.1, 1);
    glColor3f(1, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.4, 0);
    glRotatef(-90, 0, 0, 1);
    glTranslatef(1, 0, 0);
    glScalef(1, 0.1, 1);
    glColor3f(1, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5, 0.3, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(1, 2, 2);
    man4(R, G, B);
    glPopMatrix();



}

void wrestlingField() {

    //base
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glColor3f(0, 0.3, 0.3);
    cylinder(15, 0.01);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    circle(15, 2);
    glColor3f(0.0, 0.0, 0.0);
    circle(12, 2);
    glPopMatrix();

}
void draw_cylinder(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;
    /** Draw the tube */
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

//exercising men
void exercisingmen() {

    //men
    glPushMatrix();
    glScalef(1, 2, 1);
    glPushMatrix();
    glTranslatef(15, -1, 22);
    man2(1, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23, -1, 22);
    man2(0.5, 0.2, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31, -1, 22);
    man2(0.1, 0.6, 0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19, -1, 17);
    man2(0, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23, -1, 17);
    man2(0, 0, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(27, -1, 17);
    man2(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, -1, 12);
    man2(1, 1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23, -1, 12);
    man2(0.1, 0.6, 0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31, -1, 12);
    man2(0.5, 0.6, 0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23, -1, 25);
    man2(1, 1, 0);
    glPopMatrix();
    glPopMatrix();
}

void badmintonPlayer(GLfloat R, GLfloat G, GLfloat B, GLfloat R1, GLfloat G1, GLfloat B1) {
    glPushMatrix();
    man5(-20, -140, 1, 0, 0, R1, G1, B1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 3.7, 0.7);
    glScalef(1, 0.5, 0.8);
    glColor3f(R, G, B);
    badmintonRacket();
    glPopMatrix();

}
void Gym() {
    glPushMatrix();
    glTranslatef(0, 0, -20);
    compound();

    //BasketBallCourt
    glPushMatrix();
    glTranslatef(-5, -0.2, 18);
    glScalef(4, 1.5, 3);
    BasketBallCourt();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1.5, 1);
    glTranslatef(-10, -0.4, 18);
    glPushMatrix();
    glTranslated(0, 0, walkZ);
    man();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1.5, 1);
    glTranslatef(-5, -0.4, 15);
    glRotatef(180, 0, 1, 0);
    glPushMatrix();
    man5(-140, -140, 1, 0, 0, 1, 0, 0);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-5, 4.8, 14.3);
    glScalef(2.5, 2.5, 2.5);
    glPushMatrix();
    glTranslatef(0, shooty, shootz);
    basketBall();
    glPopMatrix();
    glPopMatrix();


    // 3 badmintonCourts
    glPushMatrix();
    glTranslatef(-25, 0, -14);
    glScalef(2.5, 1, 1.5);
    badmintonCourt();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -14);
    glScalef(2.5, 1, 1.5);
    badmintonCourt();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 0, -14);
    glScalef(2.5, 1, 1.5);
    badmintonCourt();
    glPopMatrix();

    //badminton player
    glPushMatrix();
    glTranslatef(-walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(0, -0.5, -9);
    glScalef(1.2, 1.5, 1.2);
    glRotatef(180, 0, 1, 0);
    badmintonPlayer(0, 0, 1, 1, 0, 0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(0, -0.5, -18);
    glScalef(1.2, 1.5, 1.2);
    badmintonPlayer(0, 1, 0, 0, 0, 1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(-25, -0.5, -9);
    glScalef(1.2, 1.5, 1.2);
    glRotatef(180, 0, 1, 0);
    badmintonPlayer(1, 0, 1, 1, 0.5, 0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(-25, -0.5, -18);
    glScalef(1.2, 1.5, 1.2);
    badmintonPlayer(0, 1, 0, 1, 0, 0.5);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(25, -0.5, -9);
    glScalef(1.2, 1.5, 1.2);
    glRotatef(180, 0, 1, 0);
    badmintonPlayer(1, 0, 1, 0.5, 0.5, 0.5);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-walkZ, 0, 0);
    glPushMatrix();
    glTranslatef(25, -0.5, -18);
    glScalef(1.2, 1.5, 1.2);
    badmintonPlayer(0, 1, 0, 1, 0, 0);
    glPopMatrix();
    glPopMatrix();

    //badminton bench
    glPushMatrix();
    glTranslatef(36, 0.2, -15);
    glScalef(1.5, 1, 0.5);
    glRotatef(-90, 0, 1, 0);
    BasketBallSideBench();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-36, 0.2, -15);
    glScalef(1.5, 1, 0.5);
    glRotatef(90, 0, 1, 0);
    BasketBallSideBench();
    glPopMatrix();

    //Shuttlecocks
    glPushMatrix();
    glTranslatef(-2, 0.5, -12);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8, 0.5, -18);
    glRotatef(30, 0, 1, 0);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 0.5, -8);
    glRotatef(30, 0, 1, 0);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 0.5, -16);
    glRotatef(90, 0, 1, 0);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 0.5, -8);
    glRotatef(-20, 0, 1, 0);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.5, -8);
    shuttlecock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28, 0.5, -17);
    glRotatef(-50, 0, 1, 0);
    shuttlecock();
    glPopMatrix();


    //Badminton Rackets
    glPushMatrix();
    glTranslatef(36, 3, -14);
    badmintonRacketBucket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-36, 3, -14);
    badmintonRacketBucket();
    glPopMatrix();

    //3 Table tennis courts
    glPushMatrix();
    glTranslatef(-25, 0, -30);
    glScalef(2, 1, 1.7);
    tableTennis();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 0, -40);
    glScalef(2, 1, 1.7);
    tableTennis();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 0, -50);
    glScalef(2, 1, 1.7);
    tableTennis();
    glPopMatrix();

    //wrestlingField
    glPushMatrix();
    glTranslatef(0, 0, -40);
    wrestlingField();
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2, 2, 2);
    man();
    glPopMatrix();
    glPopMatrix();

    //weight lifting area
    glPushMatrix();
    glTranslatef(0, 0, -70);
    weightLiftingItems();
    glPopMatrix();

    //cover arround weight lifting area 
    glPushMatrix();
    glTranslatef(-2, 1.5, -70);
    /*glRotatef(90, 1, 0, 0);*/
    glScalef(0.2, 5, 20);
    glColor3f(0.2, 0, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22, 1.5, -60);
    glRotatef(90, 0, 1, 0);
    glScalef(0.2, 5, 35);
    glColor3f(0.2, 0, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    //basketballbench

    glPushMatrix();
    glTranslatef(-30, -0.5, 10);
    glScalef(2, 1.5, 1);
    glRotatef(90, 0, 1, 0);
    BasketBallSideBench();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, -0.5, 25);
    glScalef(2, 1.5, 1);
    glRotatef(90, 0, 1, 0);
    BasketBallSideBench();
    glPopMatrix();

    //men exercising
    glPushMatrix();
    exercisingmen();
    glPopMatrix();

    //man lifting big barbell
    glPushMatrix();
    glTranslatef(20, 1, -70);
    glScalef(1.5, 1.5, 1.5);
    manLiftbarbells();
    glPopMatrix();

    //man lifting small barbell
    glPushMatrix();
    glTranslatef(20, 1, -65);
    glScalef(1.5, 1.5, 1.5);
    manLiftsmallbarbells(1, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 1, -70);
    glScalef(1.5, 1.5, 1.5);
    glRotatef(-90, 0, 1, 0);
    manLiftsmallbarbells(0, 1, 1);
    glPopMatrix();

    glPopMatrix();
}

void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;
 
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    for (line = -gridSize; line <= gridSize; line += step) {
        glVertex3f(line, -0.4, gridSize);
        glVertex3f(line, -0.4, -gridSize);

        glVertex3f(gridSize, -0.4, line);
        glVertex3f(-gridSize, -0.4, line);
    }
    glEnd();
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);

    glEnd();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    /* set material parameters */
 /*   const GLfloat blue[4] = { 0.5, 0.5, 0.5, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);*/

    /* positioned the light source */
    GLfloat position[] = { 100.0,100.0,100.0,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    /* set light intensities */
    GLfloat paleYellow[] = { 1,1,1,1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, paleYellow);
    GLfloat white[] = { 0.75,0.75,0.75,1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    GLfloat position1[] = { -100.0,-100.0,-100.0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, position1);

    /* set light intensities */
    GLfloat paleYellow1[] = { 1,1,1,1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, paleYellow1);
    GLfloat white1[] = { 0.75,0.75,0.75,1.0 };
    glLightfv(GL_LIGHT1, GL_SPECULAR, white1);

    GLfloat position2[] = { -50.0,50.0,50.0,1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, position2);

   
    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0.0, 1.0, 0.0);

    glRotatef(sceY, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, sceZ);
    glTranslatef(sceX, 0.0, 0.0);


    /*drawGrid();*/
    /*drawAxes();*/

    glPushMatrix();
    glTranslatef(0, 0, -40);
    Gym();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();

}

//Animation timer function
void updateBall(int x) {
    if (animStart) {

        speedY = 0.1;
        if (!flag) {
            ballY += speedY;
            if (ballY > 3)
                flag = 1;
        }

        if (flag) {
            ballY -= speedY;
            if (ballY < 0)
                flag = 0;
        }

        glutPostRedisplay();
        glutTimerFunc(40.0, updateBall, 1);
    }
    else {
        glutTimerFunc(40.0, updateBall, 1);
    }
}
void shootBall(int x) {
    speedY = 0.4;
    if (!flag1) {
        shooty += speedY;

        shootz -= 0.2;
        if (shooty > 5)
            flag1 = 1;

    }

    if (flag1) {
        shooty -= speedY;

        if (shooty <= 0.4) {
            shooty = -1.6;
            shootz = shootz;
        }


    }
    glutPostRedisplay();
    glutTimerFunc(40.0, shootBall, 1);


}
void timer(int x) {

    if (animStart) {
        frameNumber++;
        if (frameNumber < 20) {
            lefthandRotX += 5;
            righthandRotY += 2;
            rightlegRotX -= 2;
            lefthandRotY -= 2;
            leftlegRotX += 2;
            handRotZ += 5;
            legRotZ += 3;

            walkZ += 0.3;
        }

        if (frameNumber >= 20) {
            lefthandRotX -= 5;
            righthandRotY -= 2;
            rightlegRotX += 2;
            lefthandRotY += 2;
            leftlegRotX -= 2;
            handRotZ -= 5;
            legRotZ -= 3;
            walkZ -= 0.3;
        }

        if (righthandRotY == -10) {
            legRotZ = 0;
            frameNumber = 0;
            lefthandRotX = 0;

        }


        glutPostRedisplay();
        glutTimerFunc(40.0, timer, 1);
    }
    else {
        glutTimerFunc(40.0, timer, 1);
    }
}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += .5;

    if (key == GLUT_KEY_DOWN)
        camY -= .5;

    if (key == GLUT_KEY_RIGHT)
        camX += .5;

    if (key == GLUT_KEY_LEFT)
        camX -= .5;


    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    //Top view
    if (key == 't') {
        camX = 0;
        camY = 50;
        camZ = 20;
    }

    //Side view
    if (key == 's') {
        camX = 50;
        camY = 30;
        camZ = -20;
    }
    //front view
    if (key == 'f') {
        camX = 0;
        camY = 20;
        camZ = 20;
    }

    //light on
    if (key == 'l')
        glEnable(GL_LIGHTING);

    if (key == 'L')
        glDisable(GL_LIGHTING);

    if (key == '1')
        glEnable(GL_LIGHT0);

    if (key == '!')
        glDisable(GL_LIGHT0);

    if (key == '2')
        glEnable(GL_LIGHT1);

    if (key == '@')
        glDisable(GL_LIGHT1);

    if (key == 'z')
        sceZ += 0.5;

    if (key == 'Z')
        sceZ -= 0.5;

    if (key == 'x')
        sceX += 0.5;

    if (key == 'X')
        sceX -= 0.5;
    //wireframe
    if (key == 'w')
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == 'q')
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (key == 'a') {
        animStart = 1;
    }
    if (key == 'A') {
        animStart = 0;
    }
    if (key == 'b') {
        glutTimerFunc(1, shootBall, 0);
    }
    if (key == 'o') {
        door = 90;
    }
    if (key == 'c') {
        door = 0;
    }



    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum 
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 500);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Gymnasium");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutTimerFunc(1, timer, 0);
    glutTimerFunc(1, updateBall, 0);

    init();
    glutMainLoop();


    return 0;
}