#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<iostream>
using namespace std;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=900, windowWidth=1200,eyeX=22, eyeY=12, eyeZ=80, refX = 20 , refY=10,refZ=0, objX=0,objY=1,objZ=0,c1=0,c2=0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
double radius = 4;
double PI=3.14159;

int yFlag = 1, xFlag = 1,AniFlag=1;
GLfloat ya = 50,xa = 10;
static GLfloat v_pyramid[8][3] =
{
    {0.0, 0.0, 0.0},//0
    {1.0, 0.0, 0.0},//1
    {1.0, 0.0, 1.0},//2
    {0.0, 0.0, 1.0},//3
    {0.0, 1.0, 0.0},//4
    {1.0, 1.0, 0.0},//5
    {1.0, 1.0, 1.0},//6
    {0.0, 1.0, 1.0} //7
};
static GLubyte quadIndices[2][8] =
{
    {0,3,1,2,5,6,4,7},
    {1,5,0,4,3,7,2,6}
};

static GLfloat colors[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {1.0, 0.5, 0.0}
};

void drawCube(GLfloat c1,GLfloat c2,GLfloat c3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.9, c2*0.9, c3*0.9, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.9, c2*0.9, c3*0.9, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][4]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][5]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][6]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][7]][0]);
    }
    glEnd();


}




//
void draw_sphere(GLfloat c1, GLfloat c2, GLfloat c3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.3, c2*0.3, c3*0.3, 1.0 };
    GLfloat mat_diffuse[] = { c1, c2, c3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glutSolidSphere(5, 50, 50);
    //glutSolidTeapot(1);

}


void draw_triangle()
{
     glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(5,-8);
    glVertex2f(5,8);
    glEnd();

}










void draw_fan()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,0);
    glRotatef(-90,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();
//
     glPushMatrix();
    // glTranslatef(24,44,0);
    glRotatef(180,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();
//
//
     glPushMatrix();

     // glTranslatef(6,18,0);
    glRotatef(90,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();

     glPushMatrix();

    glTranslatef(-2,-2,0);
    //glRotatef(90,0,0,1);
    glScalef(2, 2, 1);
    drawCube(1, 0, 0);
    glPopMatrix();


}


void draw_khacha(GLfloat c1, GLfloat c2, GLfloat c3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.3, c2*0.3, c3*0.4, 0.0 };
    GLfloat mat_diffuse[] = { c1*.3, c2*.2, c3*.4, 0.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_POINTS);
    double r = 31;
    //glColor3f(0,1,0);
    //printf("afasd ");
    for(int i=0; i<1000; i++)
    {
        //glVertex2f(0,0);
        glVertex2f(r*cos(2*3.14159*i/1000.0),r*sin(2*3.14159*i/1000.0));
        r-=0.2;
        glVertex2f(r*cos(2*3.14159*i/1000.0),r*sin(2*3.14159*i/1000.0));
        r-=0.2;
        glVertex2f(r*cos(2*3.14159*i/1000.0),r*sin(2*3.14159*i/1000.0));
        r+=0.4;
    }
    glEnd();


}












void it_park_func()
{
    //IT PARK1
    glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(1,-.8,-20);
    glScalef(8,10,16);
    drawCube(1, 1, 1);
    glPopMatrix();

    //IT PARK2
    glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(16,.5,-20);
    glScalef(8,10,16);
    drawCube(1, 1, 1);
    glPopMatrix();
    glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(23.5,-.6,-10);
    glScalef(2,.4,5);
    drawCube(1, 1, 1);
    glPopMatrix();

    glTranslatef(23.5,-.2,-10);
    glScalef(1.5,.4,5);
    drawCube(1, 1, 1);
    glPopMatrix();


      glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(18,5,-24);
    glScalef(14,2,16);
    drawCube(1, 1, 1);
    glPopMatrix();



      glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(18,0,0);
    glScalef(14,1,1);
    drawCube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(18,1,-1);
    glScalef(14,1,1);
    drawCube(1, 1, 1);
    glPopMatrix();

     glPushMatrix();
   // glColor3f(.7f, 0.5f, 0.3f);
    glTranslatef(18,2,-2);
    glScalef(14,1,1);
    drawCube(1, 1, 1);
    glPopMatrix();




}



void wall()
{
    //front wall
    //glColor3f(0.7f, .7f, 0.6f);
//    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glScalef(24, 1, .5);
    glTranslatef(-0.01,-.4,20);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    drawCube(0.30,0.30,0.3);
    glPopMatrix();

    // left side_wall
   // glColor3f(0.7f, .7f, 0.6f);
    glPushMatrix();

    glScalef(.5, 1, 27);
    glTranslatef(-1.5,-.4,-.615);
    //glRotatef( 30,0.0, 0.0, 1.0 );
       drawCube(0.30,0.30,0.3);
    glPopMatrix();

    //right side_wall
    //glColor3f(0.7f, .7f, 0.6f);
    glPushMatrix();
    glScalef(.5, 1, 27);
    glTranslatef(47,-.4,-.61);
    //glRotatef( 30,0.0, 0.0, 1.0 );
     drawCube(0.30,0.30,0.3);
    glPopMatrix();

    //floor
   // glColor3f(.3f, .3f, .3f);
    glPushMatrix();
    glScalef(30, .1, 35);
    glTranslatef(-.1,-8.5,-.615);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    //drawCube();
    drawCube(0.70,0.40,0.5);
    glPopMatrix();
}











double roll=0;

double aY = 90, aP = 90, aR = 90;

double di=5.0;







int bv = 0;








// We need to store the mouse coordinate to find the relative mouse movement (new position - last position = relative position)
// So that we can use that value to rotate our camera
int mouseLastX = 0;
int mouseLastY = 0;

// Current camera rotation value along X and Y (Z is not needed since it rolls the camera which is not needed here)
double cameraYRotation = 0.0;       // also called yaw
double cameraXRotation = 0.0;       // also called pitch

// These are temporary variables to store calculate new rotation value (new rotation = old rotation + relative rotation)
double newCameraYRotation = 0.0;
double newCameraXRotation = 0.0;

// Fixed camera rotation speed done by mouse,
double cameraRotationSpeed = 0.1;

// To store camera forward/backward, left/right speed for internal use.
double cameraForwardSpeed = 0.0;
double cameraLeftRightSpeed = 0.0;

// Some other internal use variables
// Forward vector = eye vector + 1.0 distance forward
double forwardX = eyeX;
double forwardY = eyeY;
double forwardZ = eyeZ + 1.0;

// Right vector = eye vector + 1.0 distance to the right side
double rightX = eyeX + 1.0;
double rightY = eyeY;
double rightZ = eyeZ;

// Field of view angle (you can change it using keyboard + and -, this works as a zoom for camera)
double fovAngle = 70.0;

// Function : Update the camera direction based on the rotation (yaw, pitch) given
void updateCameraLookAt(double xRotation, double yRotation)
{
    double pitch = xRotation * PI / 180.0;
    double yaw = yRotation * PI / 180.0;

    if (pitch < -1.5) pitch = -1.5;
    if (pitch > 1.5) pitch = 1.5;

    // Find the forward vector
    forwardX = -sin(yaw) * cos(pitch);
    forwardY = -sin(pitch);
    forwardZ = -cos(yaw) * cos(pitch);

    // Find the right vector
    rightX = -cos(yaw);
    rightY = 0.0;
    rightZ = sin(yaw);

    // Find the up vector using cross product of forward and right vector
    double upX = forwardY * rightZ - forwardZ * rightY;
    double upY = forwardX * rightZ - forwardZ * rightX;
    double upZ = forwardX * rightY - forwardY * rightX;

    // Find magnitude of each vectors
    double forwardLength = sqrt( forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ );
    double rightLength = sqrt( rightX * rightX + rightY * rightY + rightZ * rightZ );
    double upLength = sqrt( upX * upX + upY * upY + upZ * upZ );

    // Normalize forward vector
    forwardX = forwardX / forwardLength;
    forwardY = forwardY / forwardLength;
    forwardZ = forwardZ / forwardLength;

    // Normalize right vector
    rightX = rightX / rightLength;
    rightY = rightY / rightLength;
    rightZ = rightZ / rightLength;

    // Normalize up vector
    upX = upX / upLength;
    upY = upY / upLength;
    upZ = upZ / upLength;

    // Set camera direction
    refX = eyeX + forwardX;
    refY = eyeY + forwardY;
    refZ = eyeZ + forwardZ;

    // Store the rotation value
    cameraXRotation = xRotation;
    cameraYRotation = yRotation;

    // The purpose of this function is too take angles and convert them to directions
}

// This is a glut build in function to give you mouse position when you tap hold + drag on the mouse
void myMotionFunc(int x, int y)
{
    // Find the relative movement
    int relX = x - mouseLastX;
    int relY = y - mouseLastY;

    // Store the value
    mouseLastX = x;
    mouseLastY = y;

    // Calculate horizontal and vertical rotation for camera
    double relHorizontal = relX * cameraRotationSpeed;
    newCameraYRotation = cameraYRotation + relHorizontal;

    double relVertical = relY * cameraRotationSpeed;
    newCameraXRotation = cameraXRotation - relVertical;

    // Update the direction by these rotations
    updateCameraLookAt(newCameraXRotation, newCameraYRotation);
}

// Glut build in function, gives position when you tap on the mouse. State == 0 means when you just clicked (MouseDown event)
void myMouseFunc(int button, int state, int x, int y)
{
    if (state == 0)
    {
        mouseLastX = x;
        mouseLastY = y;
    }
}

// Update camera perspective projection
void setPerspectiveProjection()
{
    double fov = fovAngle;
    double aspect = glutGet(GLUT_SCREEN_WIDTH) / glutGet(GLUT_SCREEN_HEIGHT);
    double near_dist = 0.1;
    double far_dist = 1000.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near_dist, far_dist);
    glMatrixMode(GL_MODELVIEW);
}


void cameraMoveForward()
{
    cameraForwardSpeed = cameraForwardSpeed + 0.1;
    if (cameraForwardSpeed > 1.0) cameraForwardSpeed = 1.0;
}

void cameraMoveBackward()
{
    cameraForwardSpeed = cameraForwardSpeed - 0.1;
    if (cameraForwardSpeed < -1.0) cameraForwardSpeed = -1.0;
}

void cameraMoveRight()
{
    cameraLeftRightSpeed = cameraLeftRightSpeed - 0.1;
    if (cameraLeftRightSpeed < -1.0) cameraLeftRightSpeed = -1.0;
}

void cameraMoveLeft()
{
    cameraLeftRightSpeed = cameraLeftRightSpeed + 0.1;
    if (cameraLeftRightSpeed > 1.0) cameraLeftRightSpeed = 1.0;
}

// Move the camera forward/backward based on the current speed
void cameraUpdateForwardSpeed()
{
    double directionX;
    double directionY;
    double directionZ;

    directionX = refX - eyeX;
    directionY = refY - eyeY;
    directionZ = refZ - eyeZ;

    double mag = sqrt( directionX * directionX + directionY * directionY + directionZ * directionZ);
    directionX = directionX / mag;
    directionY = directionY / mag;
    directionZ = directionZ / mag;

    eyeX = eyeX + directionX * cameraForwardSpeed;
    refX = refX + directionX * cameraForwardSpeed;

    eyeY = eyeY + directionY * cameraForwardSpeed;
    refY = refY + directionY * cameraForwardSpeed;

    eyeZ = eyeZ + directionZ * cameraForwardSpeed;
    refZ = refZ + directionZ * cameraForwardSpeed;


    cameraForwardSpeed = cameraForwardSpeed * 0.9;
    if (cameraForwardSpeed > -0.02 && cameraForwardSpeed < 0.02) cameraForwardSpeed = 0.0;

}

// Move the camera left/right based on the current speed (this is little difficult that moving forward/backward)

void cameraUpdateLeftRightSpeed()
{
    double directionX;
    double directionY;
    double directionZ;

    double pitch = cameraXRotation * PI / 180.0;
    double yaw = cameraYRotation * PI / 180.0;

    double rX = -cos(yaw);
    double rY = 0.0;
    double rZ = sin(yaw);
    double rLength = sqrt( rX * rX + rY * rY + rZ * rZ );

    rX = rX / rLength;
    rY = rY / rLength;
    rZ = rZ / rLength;

    directionX = rX;
    directionY = rY;
    directionZ = rZ;

    eyeX = eyeX + directionX * cameraLeftRightSpeed;
    refX = refX + directionX * cameraLeftRightSpeed;

    eyeY = eyeY + directionY * cameraLeftRightSpeed;
    refY = refY + directionY * cameraLeftRightSpeed;

    eyeZ = eyeZ + directionZ * cameraLeftRightSpeed;
    refZ = refZ + directionZ * cameraLeftRightSpeed;


    cameraLeftRightSpeed = cameraLeftRightSpeed * 0.9;
    if (cameraLeftRightSpeed > -0.02 && cameraLeftRightSpeed < 0.02) cameraLeftRightSpeed = 0.0;
}

void rotateCameraY(double rotation)
{
    updateCameraLookAt(cameraXRotation, cameraYRotation + rotation);
}

void cameraMoveUpDown(double movement)
{
    eyeY = eyeY + movement;
    refY = refY + movement;
}

// Basically does the zoom in/out
void changeFocusOfView(double angle)
{
    fovAngle = fovAngle + angle;
    if (fovAngle < 40.0) fovAngle = 40.0;
    if (fovAngle > 90.0) fovAngle = 90.0;
}



void resetCamera()
{
    eyeX = 0.0;
    eyeY = 2.5;
    eyeZ = 20.0;
    refX = 0.0;
    refY = 2.5;
    refZ = 19.0;
    cameraYRotation = 0.0;
    newCameraYRotation = 0.0;
    cameraRotationSpeed = 0.1;
    cameraXRotation = 0.0;
    newCameraXRotation = 0.0;
    cameraForwardSpeed = 0.0;
    cameraLeftRightSpeed = 0.0;
    forwardX = eyeX;
    forwardY = eyeY;
    forwardZ = eyeZ + 1.0;
    rightX = eyeX + 1.0;
    rightY = eyeY;
    rightZ = eyeZ;
    fovAngle = 70.0;
}








void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'T':
    case 't':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'w':
    case 'W':
        cameraMoveForward();
        break;
    case 's':
    case 'S':
        cameraMoveBackward();
        break;
    case 'd':
    case 'D':
        cameraMoveRight();
        break;
    case 'a':
    case 'A':
        cameraMoveLeft();
        break;
    case 'q':
    case 'Q':
        rotateCameraY(1.5); // Rotate left
        break;
    case 'e':
    case 'E':
        rotateCameraY(-1.5); // Rotate right
        break;
    case 'z':
    case 'Z':
        cameraMoveUpDown(0.5);  // Move up
        break;
    case 'x':
    case 'X':
        cameraMoveUpDown(-0.5); // Move down
        break;
    case '+':
    case '=':
        changeFocusOfView(-1.0); // Zoom in
        break;
    case '-':
        changeFocusOfView(1.0); // Zoom out
        break;
    case 'r':
    case 'R':
        resetCamera();  // Reset camera
        break;
//    case '1': //to turn on and off light one moon and sun light
//        if(s1 == false)
//        {
//            a0=true;
//            d0=true;
//            s0=true;
//            s1 = true;
//            glEnable( GL_LIGHT0);
//            break;
//        }
//        else if(s1 == true)
//        {
//            a0=true;
//            d0=true;
//            s0=true;
//            s1 = false;
//            glDisable( GL_LIGHT0);
//            break;
//        }
//
//    case '2': //to turn on and off light 2 monument light
//        if(s2 == false)
//        {
//            a0=true;
//            d0=true;
//            s0=true;
//            s2 = true;
//            glEnable( GL_LIGHT1);
//            break;
//        }
//        else if(s2 == true)
//        {
//            a0=true;
//            d0=true;
//            s0=true;
//            s2 = false;
//            glDisable( GL_LIGHT1);
//            break;
//        }
//
//    case '4'://ambient
//        a0=true;
//        d0=false;
//        s0=false;
//        break;
//    case '5'://diffuse
//        a0=false;
//        d0=true;
//        s0=false;
//        break;
//    case '6'://specular
//        a0=false;
//        d0=false;
//        s0=true;
//        break;
//    case '7'://cloud on 0ff
//        if(clo1==1)
//        {
//            clo=1;
//            clo1=0;
//        }
//        else
//        {
//            clo=0;
//            clo1=1;
//        }
//        break;
//    case '8'://rain on off
//        if(f3==1)
//        {
//            f2=1;
//            f3=0;
//        }
//        else
//        {
//            f2=0;
//            f3=1;
//
//        }
//        break;
//    case '9'://night mode on off
//        if(n2==1)
//        {
//            n1=1;
//            n2=0;
//        }
//        else
//        {
//            n1=0;
//            n2=1;
//
//        }
//        break;
    case 27:    // Escape key
        exit(1);
    }
    glutPostRedisplay();
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if(AniFlag == 1)
    {
        if(ya>-50 && yFlag == 1)
            ya = ya - 0.2;

        if(ya<=-50 && yFlag == 1)
            yFlag = 0;

        if(ya<50 && yFlag == 0)
            ya = ya + 0.2;

        if(ya>=50 && yFlag == 0)
            yFlag = 1;


        if(xa>-10 && xFlag == 1)
            xa = xa - 0.2;

        if(xa<=-10 && xFlag == 1)
            xFlag = 0;

        if(xa<10 && xFlag == 0)
            xa = xa + 0.2;

        if(xa>=10 && xFlag == 0)
            xFlag = 1;
    }
    glutPostRedisplay();

}




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setPerspectiveProjection();
    cameraUpdateForwardSpeed();
    cameraUpdateLeftRightSpeed();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  objX,objY,objZ);//camera position target position and rolling of camera

    glViewport(0, 0, windowWidth, windowHeight);
//    light0();
//    light1();
    glPushMatrix();
    glScalef(2,2,2);
    wall();
    it_park_func();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
   // cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<endl;
}







static void resizeView(int width, int height)
{
    //glViewport(0, 0, width, width/rat);
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -2.0, 2.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}






int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    glutInitWindowPosition(120,120);
    glutInitWindowSize(1200, 1000);
    glutCreateWindow("KUET IT PARK");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    printf("\t********** Activities **********\n");
    printf( "\tFOR Camera Movement , Hold + Drag On The Mouse \n");
    printf(" \tFOR Forward Movement , PRESS W/w \n ");
    printf(" \tFOR Backward Movement , PRESS S/s \n ");
    printf(" \tFOR Right Movement , PRESS D/d \n ");
    printf(" \tFOR Left Movement , PRESS A/a \n ");
    printf(" \tFOR Rotating Left , PRESS Q/q \n ");
    printf(" \tFOR Rotating Right , PRESS E/e \n ");
    printf(" \tFOR Up Movement , PRESS Z/z \n ");
    printf(" \tFOR Down Movement , PRESS X/x \n ");
    printf(" \tFOR Rotating On Off Along Y Axis , PRESS T/t \n ");
    printf("\tFOR ZOOM IN, PRESS + \n");
    printf("\tFOR ZOOM OUT, PRESS - \n");
    printf("\tTo turn on and off light 1(Sunlight Normal DayLight & Moonlight spotlight) ,press 1 \n");
    printf("\tTo turn on and off light 2 (Monument light) ,press 2\n");
    printf("\tTo turn on and off ambient property ,press 4\n");
    printf("\tTo turn on and off diffuse property ,press 5\n");
    printf("\tTo turn on and off specular property ,press 6\n");
    printf("\tFOR Cloud Movement On and Off, PRESS 7 \n");
    printf("\tFOR Rain Effect On and Off, PRESS 8 \n");
    printf("\tFOR Night Effect On and Off, PRESS 9 \n");
    printf("\tTO Reset, PRESS R \n");

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
//    light0();
//    light1();



    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMouseFunc(myMouseFunc);
    glutMotionFunc(myMotionFunc);
    glutKeyboardFunc(myKeyboardFunc);
    // Here is our new entry in the main function
	glutReshapeFunc(resizeView);
    glutMainLoop();

    return 0;
}
