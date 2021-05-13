#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"

float angle = 0;
// variables to save bmp
GLuint textureBarn, textureDoor, textureGrass, 
       textureRoof, textureWindow, textureSky,
       textureHay, textureNight;

//
int state = 1;

void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
    GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
    GLfloat specularR, GLfloat specularG, GLfloat specularB,
    GLfloat shininess) {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawSky() {
    // Sky

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureSky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -10);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 0.1);  glVertex3f(-10, 10, 0);
    glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(10, 10, 0);
    glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(10, -10, 0);
    glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-10, -10, 0);
    glEnd();
    glPopMatrix();
}

void drawNightSky() {
    // Sky

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureNight);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -10);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 2.0, 0.1);  glVertex3f(-10, 10, 0);
    glTexCoord3f(4.0, 2.0, 0.1);  glVertex3f(10, 10, 0);
    glTexCoord3f(4.0, 0.0, 0.1);  glVertex3f(10, -10, 0);
    glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-10, -10, 0);
    glEnd();
    glPopMatrix();
}

void drawGrass() {
    // Grass
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureGrass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 70.0, 1);  glVertex3f(-50, -1.5, 50);
    glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-50, -1.5, -50);
    glTexCoord3f(70.0, 0.0, -1);  glVertex3f(50, -1.5, -50);
    glTexCoord3f(70.0, 70.0, 1);  glVertex3f(50, -1.5, 50);
    glEnd();
    glPopMatrix();
}

void drawFrontSide() {

    // Front side
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureBarn);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0, 2.0, 0.1);  glVertex3f(-2, 0, -1);
    glTexCoord3f(4.0, 2.0, 0.1);  glVertex3f(2, 0, -1);
    glTexCoord3f(4.0, 0.0, 0.1);  glVertex3f(2, -1.5, -1);
    glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-2, -1.5, -1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureRoof);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Roof
    glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, -2.0);
    glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, -2.0);
    glTexCoord3f(4.0, 0.0, 1.25); glVertex3f(2.2, -0.1, -.25);
    glTexCoord3f(0.0, 0.0, 1.25); glVertex3f(-2.2, -0.1, -.25);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureDoor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Door
    glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-0.3, -0.4, -.9001);
    glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.3, -0.4, -.9001);
    glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.3, -1.5, -.9001);
    glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-0.3, -1.5, -.9001);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureWindow);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Window Left
    glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-1.5, -0.3, -.9001);
    glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(-0.75, -0.3, -.9001);
    glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(-0.75, -0.8, -.9001);
    glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-1.5, -0.8, -.9001);
    glEnd();

    glBegin(GL_QUADS);  // Window Right
    glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, -.9001);
    glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, -.9001);
    glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, -.9001);
    glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, -.9001);
    glEnd();
    glPopMatrix();
}

void drawBackSide() {
    // Back side
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBarn);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-2, 0, -3);
    glTexCoord3f(4.0, 2.0, -1);  glVertex3f(2, 0, -3);
    glTexCoord3f(4.0, 0.0, -1);  glVertex3f(2, -1.5, -3);
    glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-2, -1.5, -3);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureRoof);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Roof
    glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, -2);
    glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, -2);
    glTexCoord3f(4.0, 0.0, -1.25); glVertex3f(2.2, -0.1, -3.25);
    glTexCoord3f(0.0, 0.0, -1.25); glVertex3f(-2.2, -0.1, -3.25);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureWindow);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Window Left
    glTexCoord3f(0.0, 1.0, -1.0001); glVertex3f(-1.5, -0.3, -2.0001);
    glTexCoord3f(1.0, 1.0, -1.0001); glVertex3f(-0.75, -0.3, -2.0001);
    glTexCoord3f(1.0, 0.0, -1.0001); glVertex3f(-0.75, -0.8, -2.0001);
    glTexCoord3f(0.0, 0.0, -1.0001); glVertex3f(-1.5, -0.8, -2.0001);
    glEnd();

    glBegin(GL_QUADS);  // Window Right
    glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, -2.0001);
    glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, -2.0001);
    glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, -2.0001);
    glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, -2.0001);
    glEnd();

    glPopMatrix();
}

void drawRightSide() {
    // Right side
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureBarn);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0, 2.0, 1); glVertex3f(2, 0, -1);
    glTexCoord3f(2.0, 2.0, -1); glVertex3f(2, 0, -3);
    glTexCoord3f(2.0, 0.0, -1); glVertex3f(2, -1.5, -3);
    glTexCoord3f(0.0, 0.0, 1); glVertex3f(2, -1.5, -1);
    glEnd();


    glBegin(GL_TRIANGLES);  // Wall Upper
    glTexCoord3f(0.0, 1.0, 0); glVertex3f(2, 0.5, -2.0);
    glTexCoord3f(1.0, 0.0, 1); glVertex3f(2, 0, -1);
    glTexCoord3f(-1.0, 0.0, -1); glVertex3f(2, 0, -3);
    glEnd();
    glPopMatrix();
}

void drawLeftSide() {
    // Left side
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureBarn);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0, 0, -6);
    glRotatef(angle, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0, 2.0, 1);    glVertex3f(-2, 0, -1);
    glTexCoord3f(2.0, 2.0, -1);    glVertex3f(-2, 0, -3);
    glTexCoord3f(2.0, 0.0, -1);    glVertex3f(-2, -1.5, -3);
    glTexCoord3f(0.0, 0.0, 1);    glVertex3f(-2, -1.5, -1);
    glEnd();

    glBegin(GL_TRIANGLES);  // Wall Upper
    glTexCoord3f(0.0, 1.0, 0);    glVertex3f(-2, 0.5, -2.0);
    glTexCoord3f(1.0, 0.0, 1);    glVertex3f(-2, 0, -1);
    glTexCoord3f(-1.0, 0.0, -1);    glVertex3f(-2, 0, -3);
    glEnd();
    glPopMatrix();
}

void drawHay() {  
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureHay);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(1, -.6, -3.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    // front wall
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 0.1);  glVertex3f(.5, 0, 0);
    glTexCoord3f(2.0, 1.0, 0.1);  glVertex3f(0, 0, 0);
    glTexCoord3f(2.0, 0.0, 0.1);  glVertex3f(0, -.5, 0);
    glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(.5, -.5, 0);
    glEnd();
    

    // right wall
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 1);    glVertex3f(.5, 0, 0);
    glTexCoord3f(2.0, 1.0, -1);   glVertex3f(.5, 0, -.5);
    glTexCoord3f(2.0, 0.0, -1);   glVertex3f(.5, -.5, -.5);
    glTexCoord3f(0.0, 0.0, 1);    glVertex3f(.5, -.5, 0);
    glEnd();

    // left wall
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 1);    glVertex3f(0, 0, 0);
    glTexCoord3f(2.0, 1.0, -1);   glVertex3f(0, 0, -.5);
    glTexCoord3f(2.0, 0.0, -1);   glVertex3f(0, -.5, -.5);
    glTexCoord3f(0.0, 0.0, 1);    glVertex3f(0, -.5, 0);
    glEnd();

    // back wall
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 1);    glVertex3f(.5, 0, -.5);
    glTexCoord3f(2.0, 1.0, -1);   glVertex3f(0, 0, -.5);
    glTexCoord3f(2.0, 0.0, -1);   glVertex3f(0, -.5, -.5);
    glTexCoord3f(0.0, 0.0, 1);    glVertex3f(.5, -.5, -.5);
    glEnd();

    // top
    glBegin(GL_QUADS);
    glTexCoord3f(0.0, 1.0, 1);    glVertex3f(.5, 0, 0);
    glTexCoord3f(2.0, 1.0, -1);   glVertex3f(0, 0, -.5);
    glTexCoord3f(2.0, 0.0, -1);   glVertex3f(0, 0, 0);
    glTexCoord3f(0.0, 0.0, 1);    glVertex3f(.5, 0, -.5);
    glEnd();


    glPopMatrix();
}

void drawSpringBarn() {
    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    // Draw the barn
    drawSky();
    drawGrass();
    drawFrontSide();
    drawBackSide();
    drawRightSide();
    drawLeftSide();
    drawHay();

    glutSwapBuffers();

    glutPostRedisplay();
}

void drawNightBarn() {
    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    drawNightSky();
    drawGrass();
    drawFrontSide();
    drawBackSide();
    drawRightSide();
    drawLeftSide();
    drawHay();

    

    glutSwapBuffers();

    glutPostRedisplay();
}

void mainMenuHandler(int choice) {
    switch (choice) {
    case 1:
        state = 1;
        break;
    case 2:
        state = 2;
        break;
    case 3:
        state = 3;
        break;
    case 4:
        state = 4;
        break;
    case 5:
        state = 5;
        break;
    }
}



void display(void) {

    //drawSpringBarn();
    //drawNightBarn();

    if (state == 1)
        drawSpringBarn();
    else if (state == 2)
        drawNightBarn();
    else
        drawSpringBarn();




}


void changeScene(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        state++;
        break;
    case GLUT_KEY_LEFT:
        state--;
        break;
    }
    glutPostRedisplay();
}


GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
        0,                            //0 for now
        GL_RGB,                       //Format OpenGL uses for image
        image->width, image->height,  //Width and height
        0,                            //The border of the image
        GL_RGB, //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                          //as unsigned numbers
        image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    Image* image = loadBMP("./barn.bmp");
    textureBarn = loadTexture(image);
    image = loadBMP("./door.bmp");
    textureDoor = loadTexture(image);
    image = loadBMP("./grass.bmp");
    textureGrass = loadTexture(image);
    image = loadBMP("./roof.bmp");
    textureRoof = loadTexture(image);
    image = loadBMP("./window.bmp");
    textureWindow = loadTexture(image);
    image = loadBMP("./sky.bmp");
    textureSky = loadTexture(image);
    image = loadBMP("./hay.bmp");
    textureHay = loadTexture(image);
    image = loadBMP("./night.bmp");
    textureNight = loadTexture(image);
    delete image;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Barn");
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(resize);
    //glutSpecialFunc(changeScene);
    glutDisplayFunc(display);
    Initialize();

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 4, 20);
    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(7.0, 7.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    /* tell GLUT to wait for events */
    //glClearColor(0.25f, 0.5f, 0.9f, 0.1f);
    glClearColor(0.1, 0.1, 0.1, 1);
    glViewport(0, 0, 500, 500);

    glutCreateMenu(mainMenuHandler);
    glutAddMenuEntry("Spring Barn", 1);
    glutAddMenuEntry("Night Barn", 2);
    glutAddMenuEntry("Exit", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
