#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<iostream>
#include"BmpLoader.h"

using namespace std;
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=900, windowWidth=1200,eyeX=22, eyeY=12, eyeZ=80, refX = 20, refY=10,refZ=0, objX=0,objY=1,objZ=0,c1=0,c2=0,meghX=0,clo=1,clo1=1,f2=0,f3=0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean  day = true;
//49.172 138.472 -32.2561 49.1693 137.552 -32.6485

GLboolean bRotate = false, uRotate = false;
double radius = 4;
double PI=3.14159;

int yFlag = 1, xFlag = 1,AniFlag=1;
GLfloat ya = 50,xa = 10;

//Lighting  and Texture part
GLboolean  bulb_switch = false, lamp_switch=false, bulb_ambient_light=true, bulb_diffusion_light=true, bulb_specular_light=true, lamp_ambient_light=true, lamp_diffusion_light=true, lamp_specular_light=true;
GLboolean birds_eye =false;

unsigned int ID[100],ID1;

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


static GLfloat Cube[8][3] =
{
    {0.0, 0.0, 0.0},    //0
    {1.0, 0.0, 0.0},    //1
    {1.0, 0.0, 1.0},    //2
    {0.0, 0.0, 1.0},    //3
    {0.0, 1.0, 0.0},    //4
    {1.0, 1.0, 0.0},    //5
    {1.0, 1.0, 1.0},    //6
    {0.0, 1.0, 1.0}     //7
};

static GLubyte Cube_indeces[6][4] =
{
    {2,6,7,3},
    {5,4,7,6},
    {1,5,6,2},
    {3,7,4,0},
    {0,1,2,3},
    {1,6,4,5}

};


void MainLight() //Main light Source
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, 80, 0, 1.0};

    if(bulb_ambient_light == true)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    }

    if(bulb_diffusion_light == true)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    }

    if(bulb_specular_light == true)
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void SpotLight()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0,0,0, 1.0 };
    GLfloat Shine[] = { 120 };

    //glEnable( GL_LIGHT2);

    if(lamp_ambient_light == true)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    }

    if(lamp_diffusion_light == true)
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    }

    if(lamp_specular_light == true)
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glLightfv( GL_LIGHT2, GL_SHININESS, Shine);
    GLfloat spot_direction[] = { 0,-1,0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
    glPopMatrix();
}





static GLfloat v_box[8][3] =
{
    {-2.0, 0.0, -2.0},
    {2.0, 0.0, -2.0},
    {-2.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},

    {-2.0, 2.0, -2.0},
    {2.0, 2.0, -2.0},
    {-2.0, 2.0, 2.0},
    {2.0, 2.0, 2.0}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

unsigned int id;

/*void LoadTexture(const char*filename)
{

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}*/

void LoadTexture(const char*filename,int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void drawCube(GLfloat c1,GLfloat c2,GLfloat c3)
{
    glBegin(GL_QUADS);

    GLfloat mat_ambient[] = { c1, c2, c3, 1.0 };//ambient e diffuse er one third hbe
    GLfloat mat_diffuse[] = { c1*.5, c2*.5, c3*.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    for (GLint i = 0; i <6; i++)
    {
        //LoadTexture("C:\\Users\\USER\\Desktop\\Lab 3 CW\\Lab_3\\Texture\\snail.bmp");
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(Cube[Cube_indeces[i][0]][0], Cube[Cube_indeces[i][0]][1], Cube[Cube_indeces[i][0]][2],
                    Cube[Cube_indeces[i][1]][0], Cube[Cube_indeces[i][1]][1], Cube[Cube_indeces[i][1]][2],
                    Cube[Cube_indeces[i][2]][0], Cube[Cube_indeces[i][2]][1], Cube[Cube_indeces[i][2]][2]);

        glVertex3fv(&Cube[Cube_indeces[i][0]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&Cube[Cube_indeces[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&Cube[Cube_indeces[i][2]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&Cube[Cube_indeces[i][3]][0]);
        glTexCoord2f(0,0);


    }

    glEnd();
}






//
void draw_sphere(GLfloat c1, GLfloat c2, GLfloat c3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.4, c2*0.4, c3*0.4, 1.0 };
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



void cylinder()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[3]);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic,1);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic,0.15f,0.15f,1.5f,32,32);
    gluDeleteQuadric(quadratic);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void sphere(double x=1,double y=1,double z=1)
{
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*x, 0.5*y, 0.5*z, 1.0 };
    GLfloat mat_diffuse[] = { x, y, z, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    GLfloat mat_emission[] = {0.3*x, 0.2*y, 0.2*z, 1.0};
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90.0f, 1.0f, 1.0f, 0.0f);
    gluSphere(qobj, 2, 20, 16);
    gluDeleteQuadric(qobj);
    glPopMatrix();

}


void Material (float diff_r, float diff_g, float diff_b)
{
    float amb_r = diff_r/2, amb_g = diff_g/2, amb_b = diff_b/2;
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { amb_r, amb_g, amb_b,1.0 };
    GLfloat mat_diffuse[] = { diff_r, diff_g, diff_b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {80};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

void piller()
{
    GLUquadricObj* quadro = gluNewQuadric();
    gluQuadricNormals(quadro, GLU_SMOOTH);
    gluQuadricTexture(quadro, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    Material(1,1,1);
    //glColor3f(1,1,1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 5);
    //glTranslatef(1.8,0,0);
    gluCylinder(quadro,.8,.8,11,32,32);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadro);
}


void base_cylinder_second_building()
{
//        glDisable(GL_COLOR_MATERIAL);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
//    double c1=1.0,c2=1.9,c3=1.0;
//    GLfloat mat_ambient1[] = { 1.0*c1, 1.0*c1, 1.0, 1.0 };
//    GLfloat mat_diffuse1[] = { 1.0*c3, 1.0*c2, 1.0, 1.0 };
//    GLfloat mat_specular1[] = { 1.0*c2, 1.0, 1.0*c3, 1.0 };
//    GLfloat mat_shininess1[] = {60};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    //front first pillar
      glColor3f(.5,.5,.5);
    glTranslatef(40,12,-2);
    glRotatef(90,1,0,0);

    gluCylinder(gluNewQuadric(),.8,.8,11,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);

    //front second pillar
    glPushMatrix();
    // glColor3f(1,1,1);
    glTranslatef(50,12,-2);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.8,.8,11,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);

    glPushMatrix();
    glTranslatef(40,12,-10);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.8,.8,11,32,32);
    glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //front second pillar
    glPushMatrix();
    glTranslatef(50,12,-10);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.8,.8,11,32,32);
    glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //1st pillar in middle
    glPushMatrix();
    glTranslatef(16.5,43,-21);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //2nd pillar in middle
    glPushMatrix();
    glTranslatef(31,43,-21);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);

    //1st pillar in front
    glPushMatrix();
    glTranslatef(12.8,43,-5);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //2nd pillar in front
    glPushMatrix();
    glTranslatef(31,43,-5);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();



//    glDisable(GL_TEXTURE_2D);
//
//
//
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //1st pillar in back
    glPushMatrix();
    glTranslatef(20,43,-48);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 5);
    //2nd pillar in back
    glPushMatrix();
    glTranslatef(31,43,-48);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.5,.5,43,32,32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);

    //staircases cylinder
//    glEnable(GL_COLOR_MATERIAL);
//

//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(33,15,7);
//    glColor3f(1,0,0);
    glRotatef(20,1,0,0);
    glRotatef(5,0,1,0);
    gluCylinder(gluNewQuadric(),.1,.1,23,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(33,15,7);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,5,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(33.3,14,10);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,5,3,3);
    glPopMatrix();

//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(33.6,13,13);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,7,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(33.9,11.5,17);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,5,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(34.4,9.8,21.5);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,7,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(34.6,8.7,24.5);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    gluCylinder(gluNewQuadric(),.1,.1,5,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(34.9,7.7,27.5);
//    glColor3f(0,1,0);
//    glRotatef(20,1,0,0);
    glRotatef(90,1,0,0);
    Material(.5,.0,.0);
    gluCylinder(gluNewQuadric(),.1,.1,7,3,3);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);







}





void staircases(double tx,double ty,double tz)
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    glScalef(30,3,10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void lamp()
{



    glPushMatrix();


    glTranslatef(0,10,30);
    SpotLight();
    glPopMatrix();

    glPushMatrix();

    GLfloat mat_bg[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1, 1.0 };
    GLfloat mat_emission[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {120};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(0,10,30);

    //glScalef(1,.1,1);
    drawCube(1,1,1);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_bg);
    glPopMatrix();
    glPopMatrix();




}
void rain()
{

    for(int i=1; i<=100; i++)
    {


        int x=rand(),y=rand();
        x%=640;
        y%=480;
        //if(x>=120&&x<=280&&y<=280)continue;
        glBegin(GL_LINES);
        glColor3b(1,1,1);
        glVertex2d(x,y);
        glVertex2d(x+5,y+5);
        glEnd();
    }
}



void tree()
{
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    //body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    Material(1,1,1);
    glRotatef(90,1,0,0);
    gluCylinder(quad, 2.5, 2.5, 50, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //head
//    glPushMatrix();
//    Material(0,0.25,0);
//    glutSolidSphere (2.5, 32, 32);
//    glPopMatrix();

    //leaf
    float tx = 0, ty = -10, tz = 0, sx = 1, sy = 1, sz = 1;
    for(int i=0; i<10; i++)
    {
        glPushMatrix();
        Material(0.2, 0.5,0.0);
        glTranslatef(tx,ty,tz);
        glRotatef(-90,1,0,0);
        glScalef(sx, sy, sz);
        glutSolidCone(12-i,10,32,32);
        glPopMatrix();
        ty += 5;// sx -= 0.08;
    }
}


void it_park_func()
{
    // glEnable(GL_COLOR_MATERIAL);
    //IT PARK1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    // glColor3f(.5f, 0.5f, 0.5f);
    glRotatef(-10,0,1,0);
    glTranslatef(-12,-.8,-55);
    glScalef(20,46,60);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //IT PARK2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    // glColor3f(.4f, 0.5f, 0.3f);

    glTranslatef(35,13,-56);
    glScalef(25,32,80);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    base_cylinder_second_building();

    //back left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glTranslatef(-3,-1,-71);
    glScalef(35.8,40,14);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    //back right
    glPushMatrix();
    glTranslatef(33,-1,-71);
    glScalef(26,46,15);
    // glColor3f(.3,.3,.9);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    int ty=10,tz=-5;
    for(int i=0; i<=2; i++)
    {
        staircases(6,ty,tz);
        ty-=2;
        tz+=3;
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glTranslatef(6,5,10);
    glScalef(30,2,10);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ty=3;
    tz=13;
    for(int i=0; i<=2; i++)
    {
        staircases(6,ty,tz);
        ty-=2;
        tz+=3;
    }

    glPushMatrix();
    glTranslatef(0,0,-1);
    glRotatef(-1,0,1,0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    //back design front
    glPushMatrix();
    glTranslatef(20,0,-45);
    glScalef(8.5,1,.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    //back design back
    glPushMatrix();
    glTranslatef(20,0,-30);
    glScalef(8.5,1,.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    //back design left
    glPushMatrix();
    glTranslatef(20,0,-45);
    glScalef(.5,1,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    //back design right
    glPushMatrix();
    glTranslatef(28,0,-45);
    glScalef(.5,1,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//    back design middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glPushMatrix();
    glTranslatef(20,0,-45);
    //  glColor3f(1,0,0);
    glScalef(8,.1,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    glPushMatrix();
    glRotatef(-1,0,1,0);
    glTranslatef(0,0,20);

    //front design
    //front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    // glColor3f(0,0,1);
    glTranslatef(18,0,-45);
    glScalef(10,1,.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    glTranslatef(18,0,-30);
    glScalef(10.5,1,.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    glTranslatef(18,0,-45);
    glScalef(.5,1,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    glTranslatef(28,0,-45);
    glScalef(.5,1,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(18,0,-45);
    //glColor3f(1,0,0);
    glScalef(10,.05,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //2nd floor middle
    //for texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(11,13.1,-50);
    glScalef(16,.2,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //2nd floor middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(11,13,-50);
    glScalef(16,.2,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //2nd floor railing middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    //  glColor3f(.5,.6,.7);
    glTranslatef(12,13,-44);
    glScalef(14.5,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //2nd floor railing middle back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    // glColor3f(.5,.6,.7);
    glTranslatef(12,13,-50);
    glScalef(14,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //2nd floor back texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,13.05,-79);
    glScalef(11,.05,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //2nd floor back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,12.9,-79);
    glScalef(11,.2,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //2nd floor railing back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    // glColor3f(.9,.1,.7);
    glTranslatef(7.3,13,-74.8);
    glScalef(10.3,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    //3rd floor middle texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(11,23.1,-50);
    glScalef(16,.05,6);
    // glColor3f(.5f,.5f,.01f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(11,22.9,-50);
    glScalef(16,.2,6);
    // glColor3f(.5f,.5f,.01f);
    drawCube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);




    //3rd floor railing middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    //  glColor3f(.5,.6,.7);
    glTranslatef(12,23,-44);
    glScalef(14.5,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //3rd floor railing middle back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    // glColor3f(.5,.6,.7);
    glTranslatef(12,23,-50);
    glScalef(14,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    //3rd floor back with texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,23.2,-79);
    glScalef(11,.05,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //3rd floor back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,23,-79);
    glScalef(11,.2,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor railing  back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    //glColor3f(.9,.1,.7);
    glTranslatef(8,23,-74.8);
    glScalef(9.5,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //4th floor middle texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glTranslatef(12.5,33.2,-50);
    glScalef(22,.5,6);
    //  glColor3f(.5f,.1f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //4th floor middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glTranslatef(12.5,32.8,-50);
    glScalef(22,.2,6);
    //  glColor3f(.5f,.1f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //4th floor railing middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
//    glRotatef(-5,0,1,0);
    // glColor3f(.5,.6,.7);
    glTranslatef(15.5,33,-44);
    glScalef(15,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //4th floor railing middle back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
//    glRotatef(-5,0,1,0);
    //glColor3f(.5,.6,.7);
    glTranslatef(16.5,33,-50);
    glScalef(14,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //4th floor back texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,33.3,-79);
    glScalef(11,.1,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //4th floor back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-5,0,1,0);
    glTranslatef(13,33,-79);
    glScalef(11,.3,6);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //4th floor railing  back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    // glColor3f(.9,.1,.7);
    glTranslatef(7,33,-74.8);
    glScalef(10.5,3,.1);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //fifth floor middle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glTranslatef(10,43,-50);
    glScalef(25,1,10);
//   glColor3f(.9f,.1f,1.0f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fifth floor front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glTranslatef(8,43,-30);
    glScalef(28,1,10);
//   glColor3f(.9f,.1f,1.0f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fifth floor front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glTranslatef(16,43,-75);
    glScalef(17,1,8);

    // glColor3f(.9f,.1f,1.0f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //2nd floor left texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(3,13.2,-78.4);
    glScalef(5,.1,52);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //2nd floor left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(3,12.8,-78.4);
    glScalef(5,.3,52);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //2nd floor right texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,13.2,-77);
    glScalef(5,.2,52);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //2nd floor right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,13,-77);
    glScalef(5,.2,52);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    //3rd floor left texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(4,23,-78.4);
    glScalef(5,.2,64);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(4,22.7,-78.4);
    glScalef(5,.2,64);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //3rd floor right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,23.2,-77);
    glScalef(5,.1,81);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,23,-77);
    glScalef(5,.1,81);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //3rd floor left
//        glPushMatrix();
//    glRotatef(1,0,1,0);
//    glTranslatef(31,22.8,-77);
//    glScalef(5,.2,81);
//   // glColor3f(.9f,.9f,.1f);
//    drawCube(1,1,1);
//    glPopMatrix();




    //4th floor left texture

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(3,33.3,-78.4);
    glScalef(5,.2,63.5);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //4th floor left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(-10,0,1,0);
    glTranslatef(3,32.9,-78.4);
    glScalef(5,.2,63.5);
    // glColor3f(.1f,.9f,.9f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //4th floor right texture

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,33.3,-77);
    glScalef(5,.2,81);
    //glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //4th floor right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glPushMatrix();
    glRotatef(1,0,1,0);
    glTranslatef(31,33,-77);
    glScalef(5,.2,81);
    //glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //2nd floor raling 1st
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(16,13,-22.5);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,18);
    //  glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //  2nd floor railing left 2nd
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(21,13,-52);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,24);
    //  glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //3rd floor raling second part
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(21,23,-52);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,24);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor raling first part
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(16,23,-22.6);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,30.5);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //4th floor raling 1st part
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(16,33,-24);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,31.5);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //4th floor railing 2nd part
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(21,33,-52.1);
    glRotatef(-10,0,1,0);
    glScalef(.1,3,23);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //2nd floor raling right side 1st
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(31,13,-21.5);
    glRotatef(-1,0,1,0);
    glScalef(.1,3,17);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
////2nd floor raling right side 2nd
    glPushMatrix();
    glTranslatef(31,13,-50);
    glRotatef(-1,0,1,0);
    glScalef(.1,3,23);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    //3rd floor railing side right 2nd
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(31,23,-50.2);
    glRotatef(-1,0,1,0);
    glScalef(.1,3,23.5);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //3rd floor railing side right 1st
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(31,23,-21);
    glRotatef(-1,0,1,0);
    glScalef(.1,3,45);
    // glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //4th floor railing side 2nd
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(31,33,-50.1);
    glRotatef(0,0,1,0);
    glScalef(.1,3,20.7);
    //glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    //4th floor railing side 1st
    glPushMatrix();
    glTranslatef(31,33,-23.6);
    glRotatef(0,0,1,0);
    glScalef(.1,3,47.5);
    //glColor3f(.9f,.9f,.1f);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //garden left side
    glPushMatrix();
    glTranslatef(-10,-1,10);
    glScalef(15,.5,.5);
    drawCube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,-1,25);
    glScalef(15,.5,.5);
    drawCube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-10,-1,10);
    glScalef(.5,.5,15);
    drawCube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4.5,-1,10);
    glScalef(.5,.5,15);
    drawCube(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,20,30);
//    glEnable(GL_COLOR);
    glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
    glRasterPos2i(10, 10);
    std::string s = "Sheikh Kamal It Incubation & Training Center,Kuet,Khulna";
    void * font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0);
        glutBitmapCharacter(font, c);
    }
//     glDisable(GL_COLOR);
//    drawCube(1,1,1);
    glPopMatrix();



}

void materialProperty()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

/*void skydraw()
{
    int width = 512;
    int height = 512;
    int length = 512;

    //start in this coordinates
    int x = 0;
    int y = 0;
    int z = 0;

    //center the square
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;

    // Bind the BACK texture of the sky map to the BACK side of the cube
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    //FRONT
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
    glEnd();

    //BOTTOM
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
    glEnd();

    //TOP
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();

    //LEFT
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);

    glEnd();

    //RIGHT
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();
}
*/






//void sky(float x, float y, float z, float width, float height, float length)
//{
//    materialProperty();
//    glDisable(GL_DEPTH_TEST);
//    x = x - width  / 2;
//    y = y - height / 2;
//    z = z - length / 2;
//
//
//    //front
//    glEnable(GL_TEXTURE_2D);
//    if(day == true)
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    else
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y, z);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y, z+length);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z);
//    glEnd();
//
//    //up;
//    if(day == true)
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    else
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y+height, z+length);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
//    glEnd();
//
//    //back
//
//    if(day == true)
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    else
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    glBegin(GL_QUADS);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y+height,z);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z+length);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z+length);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);
//    glEnd();
//
//    //right
//    if(day == true)
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    else
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    } //10
//    glBegin(GL_QUADS);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y, z);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height, z);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
//    glEnd();
//
//    //left
//
//    if(day == true)
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    }
//    else
//    {
//        glBindTexture(GL_TEXTURE_2D,16);
//    } //11
//    glBegin(GL_QUADS);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,          y,        z+length);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,          y+height, z+length);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,        z+length);
//    glEnd();
//
//    glDisable(GL_TEXTURE_2D);
//}
//









void makecylinder(float height,float Base)
{
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    //glColor3f(r, g, b);
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj, Base, Base - (0.2 * Base), height, 20, 20);
    glPopMatrix();
}


void maketree(float height,float Base)
{

    glPushMatrix();
    float angle;
    makecylinder(height, Base);
    glTranslatef(0.0f, height,0.0f);
    height -= height * 0.2f;
    Base -= Base * 0.3f;

    if (height > 1)
    {
        angle = 22.5f;
        glPushMatrix();
        glRotatef(angle, -1.0f, 0.0f, 0.0f);
        maketree(height, Base);
        glPopMatrix();
        glPushMatrix();
        glRotatef(angle, 0.5f, 0.0f, 0.866f);
        maketree(height, Base);
        glPopMatrix();
        glPushMatrix();
        glRotatef(angle, 0.5f, 0.0f, -0.866f);
        maketree(height, Base);
        glPopMatrix();
    }
    glPopMatrix();
}

void wall()
{
    //front wall
    //glColor3f(0.7f, .7f, 0.6f);
//    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-20,-.4,50);
    glScalef(70, 1.5, 1);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    drawCube(1,1,1);
    // drawCube(0.30,0.30,0.3);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left side_wall
    // glColor3f(0.7f, .7f, 0.6f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();

    glTranslatef(-20,-.4,-70);
    glScalef(.5, 1.5, 120);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right side_wall
    // glColor3f(0.7f, .7f, 0.6f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(51,-.4,-55);
    glScalef(.5, 2, 90);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    //floor
    // glColor3f(.3f, .3f, .3f);
    glPushMatrix();
    glTranslatef(-30,-1,-60);
    glScalef(90, .1, 120);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    //drawCube();
    drawCube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    //floor in right it building
    //glColor3f(.7f, .7f, .3f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    glTranslatef(34,-1,-60);
    glScalef(17, 2, 78);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    //drawCube();
    drawCube(1,1,1);
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);

    //staircase

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    // glColor3f(.1f, .7f, .9f);
    glPushMatrix();
    glTranslatef(51,-1,-8);
    glScalef(3, 1, 5);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    //drawCube();
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    //staircase
    // glColor3f(.9f, 1.7f, .9f);
    glPushMatrix();
    glTranslatef(51,0,-8);
    glScalef(2, 1, 5);
    //glRotatef( 30,0.0, 0.0, 1.0 );
    //drawCube();
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);

    //staircase left side
    // glColor3f(.0f, 0.0f, .9f);
    glPushMatrix();
    glTranslatef(6,-1,5);
    glScalef(.1, 8, 15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tree1

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(40.5,-1,23);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //tree2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(41,-1,33);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //tree3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(47,-1,24);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //tree4
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(47,-1,33);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //garden back
    glPushMatrix();
    glTranslatef(40,-1,23);
    glScalef(8,.5,.5);
    drawCube(1,1,1);
    glPopMatrix();

    //garden front
    glPushMatrix();
    glTranslatef(40,-1,33);
    glScalef(8,.5,.5);
    drawCube(1,1,1);
    glPopMatrix();
    //garden left

    glPushMatrix();
    glTranslatef(40,-1,23);
    glScalef(.5,.5,10);
    drawCube(1,1,1);
    glPopMatrix();



    //garden right
    glPushMatrix();
    glTranslatef(48,-1,23);
    glScalef(.5,.5,10.5);
    drawCube(1,1,1);
    glPopMatrix();


    //light handle right
    glPushMatrix();
    glTranslatef(44.2,-1,28);
    glScalef(.2,6,.2);
    drawCube(1,1,1);
    glPopMatrix();


    //light handle left
    glPushMatrix();
    glTranslatef(-2,-1,20);
    glScalef(.2,6,.2);
    drawCube(1,1,1);
    glPopMatrix();



    //middle tree on  left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(-3,-1,20);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(4,-1,15);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(-8,-1,15);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(4,-1,24);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(-8,-1,24);
    maketree(4.0,.1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //grass on left side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(-9.5,-.9,10);
    glScalef(14.3,.2,15);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //grass on the right side

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    glTranslatef(40.5,-.9,24);
    glScalef(8,.2,9.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,15);
//    glPushMatrix();
//    glTranslatef(0,10,30);

    //glRotatef(180,0,1,0);
    //glScalef(25,3,1);
    // drawCube(1,1,1);
//    glPopMatrix();

//    sky(eyeX+(0.05*refX),eyeY+(0.05*refY),eyeZ+(0.05*refZ),250,250,250);
//     glDisable(GL_TEXTURE_2D);
}




void light_func()
{

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(-4,0,10);
    lamp();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(44,0,13);
    glScalef(.5,.5,.5);
    lamp();
    glPopMatrix();




}

void cloud()
{

    glEnable(GL_TEXTURE_2D);
    glScalef(0.5,1,0.5);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,ID[5]);


    glTranslatef(0,4,0);
    glScalef(1.15,1.15,1.15);
    sphere();
    glPopMatrix();
    glPushMatrix();
    //glScalef(1.5,1.5,1.5);
    glTranslatef(-1,1.5,1);
    sphere();
    glPopMatrix();
    glPushMatrix();
    //glScalef(1.5,1.5,1.5);
    glTranslatef(2,1.25,1.5);
    sphere();
    glPopMatrix();
    glPushMatrix();
    // glScalef(0.75,1,0.75);
    glTranslatef(3.75,2.5,0);
    sphere();
    glPopMatrix();
    glPushMatrix();
    // glScalef(0.75,1,0.75);
    glTranslatef(-3.75,2.5,0);
    sphere();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void movecloud(float a)

{
    // float meghX=meghX+a;
    if (clo == 1)
    {
        meghX +=.05;
    }
    if (meghX+a>35)
    {
        meghX = -35;
    }
    glPushMatrix();
    glTranslatef(meghX, 0, 0);
    cloud();
    glPopMatrix();


}

void cloud_area(float a, float b)//1st 2 row cloud
{
    glPushMatrix();
    glTranslatef(-10,a,-b);
    movecloud(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,a,-b);
    movecloud(-10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20,a,-b);
    movecloud(20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,a,-b);
    movecloud(-20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,a,-b);
    movecloud(0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,a-5,-b);
    movecloud(15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,a-5,-b);
    movecloud(-15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,a-5,-b);
    movecloud(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,a-5,-b);
    movecloud(-5);
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

    case '1': //to turn on and off bulb
        if(bulb_switch == false)
        {
            bulb_switch = true;
            bulb_ambient_light=true;
            bulb_diffusion_light=true;
            bulb_specular_light=true;
            glEnable( GL_LIGHT0);
            break;
        }
        else if(bulb_switch == true)
        {
            bulb_switch = false;
            bulb_ambient_light=false;
            bulb_diffusion_light=false;
            bulb_specular_light=false;
            glDisable( GL_LIGHT0);
            break;
        }
        break;

    case'2': //turn on/off ambient light 1
            if(bulb_ambient_light == false)
            {
                bulb_ambient_light=true;
                break;
            }
            else
            {
                bulb_ambient_light=false;
                break;
            }


    case'3':
            if(bulb_diffusion_light == false)
            {
                bulb_diffusion_light=true;
                break;
            }
            else
            {
                bulb_diffusion_light=false;
                break;
            }

    case'4':
            if(bulb_specular_light == false)
            {
                bulb_specular_light=true;
                break;
            }
            else
            {
                bulb_specular_light=false;
                break;
            }


    case '5': //to turn on and off lamp
        if(lamp_switch == false)
        {
            lamp_switch = true;
            lamp_ambient_light=true;
            lamp_diffusion_light=true;
            lamp_specular_light=true;
            glEnable( GL_LIGHT2);
            break;
        }
        else if(lamp_switch == true)
        {
            lamp_switch = false;
            lamp_ambient_light=false;
            lamp_diffusion_light=false;
            lamp_specular_light=false;
            glDisable( GL_LIGHT2);
            break;
        }
        break;

    case'6': //turn on/off ambient lamp light
            if(lamp_ambient_light == false)
            {
                lamp_ambient_light=true;
                break;
            }
            else
            {
                lamp_ambient_light=false;
                break;
            }

    case'7':
            if(lamp_diffusion_light == false)
            {
                lamp_diffusion_light=true;
                break;
            }
            else
            {
                lamp_diffusion_light=false;
                break;
            }


    case'8':
            if(lamp_specular_light == false)
            {
                lamp_specular_light=true;
                break;
            }
            else
            {
                lamp_specular_light=false;
                break;
            }
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
    // cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<refX<<" "<<refY<<" "<<refZ<<endl;
    //glViewport(0, 0, windowWidth, windowHeight);
//    light0();
//    light1();
    glPushMatrix();
    glScalef(2,2,2);
    wall();
    light_func();
    it_park_func();
    glPushMatrix();
    glTranslatef(0,40,10);
    cloud_area(100,55);
    glPopMatrix();
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
    glFrustum(-ar, ar, -ar, ar, 2.0, 100.0);

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

    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\wall.bmp", 1);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\floor.bmp", 2);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\staircase_floor.bmp", 3);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\IT_park_white.bmp", 4);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\column_texture.bmp", 5);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\mosaic_wall.bmp", 6);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\water_texture.bmp", 7);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\rockTexture.bmp", 8);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\glass_texture.bmp", 9);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\railing_cylinder_texture.bmp", 10);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\grass_texture.bmp", 11);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\floor_balcony.bmp", 12);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\building_texture.bmp", 13);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\wood_texture.bmp", 14);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\title.bmp", 15);
    LoadTexture("C:\\Users\\USER\\Desktop\\Graphics_Project\\KUET_IT_PARK\\sky.bmp", 16);
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
    MainLight();



    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMouseFunc(myMouseFunc);
    glutMotionFunc(myMotionFunc);
    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resizeView);
    glutMainLoop();

    return 0;
}
