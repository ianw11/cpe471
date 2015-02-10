//
// Shinjiro Sueda
// modified ZJ Wood January 2015 - conversion to glfw
// October, 2014
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include "GLSL.h"
#include "tiny_obj_loader.h"

GLFWwindow* window;
using namespace std;

vector<tinyobj::shape_t> shapes;
vector<tinyobj::material_t> materials;
GLuint prog;
GLuint posBufObj = 0;
GLuint norBufObj = 0;
GLuint indBufObj = 0;
GLint aPos = 0;
GLint aNor = 0;
GLint uMV = 0;
GLint uP = 0;

int DEBUG = 0;
int width = 1;
int height = 1;

void loadShapes(const string &objFile)
{
	string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
	if(!err.empty()) {
		cerr << err << endl;
	}
}

void initGL()
{
	// Set the background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable Z-buffer test
	glEnable(GL_DEPTH_TEST);
	
	// Send the position array to the GPU
	const vector<float> &posBuf = shapes[0].mesh.positions;
	glGenBuffers(1, &posBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
	
	// Send the normal array to the GPU
	const vector<float> &norBuf = shapes[0].mesh.normals;
	glGenBuffers(1, &norBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
	glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
	
	// Send the index array to the GPU
	const vector<unsigned int> &indBuf = shapes[0].mesh.indices;
	glGenBuffers(1, &indBufObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);

	// Unbind the arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLSL::checkVersion();
	assert(glGetError() == GL_NO_ERROR);
}

bool installShaders(const string &vShaderName, const string &fShaderName)
{
	GLint rc;
	
	// Create shader handles
	GLuint VS = glCreateShader(GL_VERTEX_SHADER);
	GLuint FS = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Read shader sources
	const char *vshader = GLSL::textFileRead(vShaderName.c_str());
	const char *fshader = GLSL::textFileRead(fShaderName.c_str());
	glShaderSource(VS, 1, &vshader, NULL);
	glShaderSource(FS, 1, &fshader, NULL);
	
	// Compile vertex shader
	glCompileShader(VS);
	GLSL::printError();
	glGetShaderiv(VS, GL_COMPILE_STATUS, &rc);
	GLSL::printShaderInfoLog(VS);
	if(!rc) {
		printf("Error compiling vertex shader %s\n", vShaderName.c_str());
		return false;
	}
	
	// Compile fragment shader
	glCompileShader(FS);
	GLSL::printError();
	glGetShaderiv(FS, GL_COMPILE_STATUS, &rc);
	GLSL::printShaderInfoLog(FS);
	if(!rc) {
		printf("Error compiling fragment shader %s\n", fShaderName.c_str());
		return false;
	}
	
	// Create the program and link
	prog = glCreateProgram();
	glAttachShader(prog, VS);
	glAttachShader(prog, FS);
	glLinkProgram(prog);
	GLSL::printError();
	glGetProgramiv(prog, GL_LINK_STATUS, &rc);
	GLSL::printProgramInfoLog(prog);
	if(!rc) {
		printf("Error linking shaders %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
		return false;
	}
	
	// Set up the shader variables
	aPos = GLSL::getAttribLocation(prog, "aPos");
	aNor = GLSL::getAttribLocation(prog, "aNor");
	uMV = GLSL::getUniformLocation(prog, "MV");
	uP = GLSL::getUniformLocation(prog, "P");
	
	assert(glGetError() == GL_NO_ERROR);
	return true;
}

void printMat(float *A, const char *name = 0)
{
	// OpenGL uses col-major ordering:
	// [ 0  4  8 12]
	// [ 1  5  9 13]
	// [ 2  6 10 14]
	// [ 3  7 11 15]
	// The (i,j)th element is A[i+4*j].
	if(name) {
		printf("%s=[\n", name);
	}
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			printf("%- 5.2f ", A[i+4*j]);
		}
		printf("\n");
	}
	if(name) {
		printf("];");
	}
	printf("\n");
}

void clearMat(float *M) {
   for (int i = 0; i < 16; ++i) {
	   M[i] = 0;
	}
}

void createIdentityMat(float *M)
{
   clearMat(M);
	M[0] = 1;
	M[5] = 1;
	M[10] = 1;
	M[15] = 1;
}

void createTranslateMat(float *T, float x, float y, float z)
{
	createIdentityMat(T);
	T[12] = x;
	T[13] = y;
	T[14] = z;
}

void createScaleMat(float *S, float x, float y, float z)
{
	clearMat(S);
	S[0] = x;
	S[5] = y;
	S[10] = z;
	S[15] = 1;
}

void createRotateMatX(float *R, float radians)
{	
	clearMat(R);
	R[0] = 1;
	R[5] = cos(radians);
	R[6] = sin(radians);
	R[9] = sin(radians) * -1;
	R[10] = cos(radians);
	R[15] = 1;
}

void createRotateMatY(float *R, float radians)
{
	clearMat(R);
	R[0] = cos(radians);
	R[2] = sin(radians) * -1;
	R[5] = 1;
	R[8] = sin(radians);
	R[10] = cos(radians);
	R[15] = 1;
}

void createRotateMatZ(float *R, float radians)
{
	clearMat(R);
	R[0] = cos(radians);
	R[1] = sin(radians);
	R[4] = sin(radians) * -1;
	R[5] = cos(radians);
	R[10] = 1;
	R[15] = 1;
}

void multMat(float *C, const float *A, const float *B)
{
   float c = 0;
	for(int k = 0; k < 4; ++k) {
		// Process kth column of C
		for(int i = 0; i < 4; ++i) {
			// Process ith row of C.
			// The (i,k)th element of C is the dot product
			// of the ith row of A and kth col of B.
         c = 0;
         //vector dot
			for(int j = 0; j < 4; ++j) {
				// IMPLEMENT ME
				c += A[(4 * j) + i] * B[(k * 4) + j];
			}
			C[i + 4*k] = c;
		}
	}
}

void createPerspectiveMat(float *m, float fovy, float aspect, float zNear, float zFar)
{
	// http://www-01.ibm.com/support/knowledgecenter/ssw_aix_61/com.ibm.aix.opengl/doc/openglrf/gluPerspective.htm%23b5c8872587rree
	float f = 1.0f/tan(0.5f*fovy);
	m[ 0] = f/aspect;
	m[ 1] = 0.0f;
	m[ 2] = 0.0f;
	m[ 3] = 0.0f;
	m[ 4] = 0;
	m[ 5] = f;
	m[ 6] = 0.0f;
	m[ 7] = 0.0f;
	m[ 8] = 0.0f;
	m[ 9] = 0.0f;
	m[10] = (zFar + zNear)/(zNear - zFar);
	m[11] = -1.0f;
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 2.0f*zFar*zNear/(zNear - zFar);
	m[15] = 0.0f;
}

void drawGL()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Use our GLSL program
	glUseProgram(prog);

	// Enable and bind position array for drawing
	GLSL::enableVertexAttribArray(aPos);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Enable and bind normal array for drawing
	GLSL::enableVertexAttribArray(aNor);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
	glVertexAttribPointer(aNor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Bind index array for drawing
	int nIndices = (int)shapes[0].mesh.indices.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObj);
	
	// Compute and send the projection matrix
	float P[16];
	createPerspectiveMat(P, 45.0f, (float)width/height, 0.01f, 100.0f);
	glUniformMatrix4fv(uP, 1, GL_FALSE, P);
   
   if (DEBUG) {
      float A[16], B[16], C[16];
      for(int i = 0; i < 16; ++i) { A[i] = i; }
      for(int i = 0; i < 16; ++i) { B[i] = i*i; }
      multMat(C, A, B);
      printMat(A, "A");
      printMat(B, "B");
      printMat(C, "C");
   }

   /*
   float MV[16] = {0};
   createTranslateMat(MV, 0, 0, -2);
   glUniformMatrix4fv(uMV, 1, GL_FALSE, MV);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	*/
	
	/*********************/
	
	/* Left of H */
	float lhMV[16] = {0};
	createTranslateMat(lhMV, -.5, 0, -2);
	float lhS[16] = {0};
	createScaleMat(lhS, .15, .8, .4);
	float lhComp[16] = {0};
	multMat(lhComp, lhMV, lhS);
	// Send and Draw
	glUniformMatrix4fv(uMV, 1, GL_FALSE, lhComp);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	/* Right of H */
	float rhMV[16] = {0};
	createTranslateMat(rhMV, -.3, 0, -2);
	float rhS[16] = {0};
	createScaleMat(rhS, .15, .8, .4);
	float rhComp[16] = {0};
	multMat(rhComp, rhMV, rhS);
	// Send and Draw
	glUniformMatrix4fv(uMV, 1, GL_FALSE, rhComp);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	/* Crossbar */
	float cbMV[16] = {0};
	createTranslateMat(cbMV, -.4, 0, -2);
	float cbS[16] = {0};
	createScaleMat(cbS, .4, .15, .4);
	float cbR[16];
	createRotateMatZ(cbR, 15);
	float cbIntermediate[16];
	multMat(cbIntermediate, cbR, cbS);
	float cbComp[16] = {0};
	multMat(cbComp, cbMV, cbIntermediate);
	// Send and Draw
	glUniformMatrix4fv(uMV, 1, GL_FALSE, cbComp);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	/* Body of I */
	float biS[16];
	createScaleMat(biS, .1, .5, .4);
	float biMV[16];
	createTranslateMat(biMV, .1, -.1, -2);
	float biComp[16];
	multMat(biComp, biMV, biS);
	// Send and Draw
	glUniformMatrix4fv(uMV, 1, GL_FALSE, biComp);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	/* Dot of I */
	float diS[16];
	createScaleMat(diS, .1, .1, .4);
	float diMV[16];
	createTranslateMat(diMV, .1, .4, -2);
	float diComp[16];
	multMat(diComp, diMV, diS);
	// Send and Draw
	glUniformMatrix4fv(uMV, 1, GL_FALSE, diComp);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	/*********************/
	
   // Disable and unbind
	GLSL::disableVertexAttribArray(aPos);
	GLSL::disableVertexAttribArray(aNor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
	assert(glGetError() == GL_NO_ERROR);
	
}

void reshapeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	width = w;
	height = h;
}


int main(int argc, char **argv)
{

// Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    // Open a window and create its OpenGL context
   window = glfwCreateWindow( 1024, 768, "lab 5 - object", NULL, NULL);
   if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

// Initialize GLEW
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
   }

   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	loadShapes("cube.obj");
	initGL();
	installShaders("vert.glsl", "frag.glsl");

   // Dark blue background
   glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    do{
      drawGL();
        // Swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
   while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

	return 0;
}
