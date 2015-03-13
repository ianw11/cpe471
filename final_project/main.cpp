// Base code for program 3 - does not compile as is, needs other files 
//and shaders but has skeleton for much of the data transfer for shading
//and traversal of the mesh for computing normals - you must compute normals

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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr
#include "RenderingHelper.h"
#include "openal/include/AL/al.h"
#include "openal/include/AL/alc.h"
#include "openal/include/AL/alext.h"

GLFWwindow* window;
using namespace std;

vector<tinyobj::shape_t> shapes;
vector<tinyobj::shape_t> shapes_cube;
vector<tinyobj::material_t> materials;       // Apparently not used
vector<tinyobj::material_t> materials_cube;  // Apparently not used

int g_width = 700; // 1024
int g_height = 700; // 768
int g_SM = 0;                 // Choose which shading type you want
//float g_Camtrans = -2.5;
float g_angle = 0;            // Y Angle of the models (spins rabbit)
float x_angle = 0;            // X Angle of the models (turns rabbit upside down)
int g_mat_id = 0;             // The material to use for the models
glm::vec3 g_trans(0, 0, 0);   // Translation matrix
glm::vec3 g_scale(1, 1, 1);   // Scale matrix
glm::vec3 g_light(0, 1, 0);   // Position of (point) light

GLuint ShadeProg;
GLuint posBufObj = 0;
GLuint norBufObj = 0;
GLuint indBufObj = 0;

// Handles to the arrays that will hold the cube obj data
GLuint posBufObjCube = 0;
GLuint norBufObjCube = 0;
GLuint indBufObjCube = 0;

//Handles to the shader data
GLint h_aPosition;
GLint h_aNormal;
GLint h_uModelMatrix;                                 // Where a model gets placed
GLint h_uViewMatrix;                                  // !! Camera matrix
GLint h_uLightPos;
GLint h_uMatAmb, h_uMatDif, h_uMatSpec, h_uMatShine;  // Handles to vec3s for material shading
GLint h_uShadeM;
GLint h_uProjMatrix;                                  // Projection matrix handle

int forceNormals = 0;
GLint h_forceNormals;
GLint vbo;

glm::vec3 eye(0, 2, 0);
glm::vec3 lookAt;
glm::vec3 up(0.0, 1.0, 0.0);
float phi = 0, theta = -(M_PI / 2.0); // phi is for up and down

float worldRadius = 0;
int doRotate = 0;

float robotTheta = 0;
int robotDir = 0;

RenderingHelper ModelTrans;

int numMaterials = 9;
enum Material {HEAD, FRAME, CYMBAL, ORANGE, SHINY_BLUE, FLAT_GREY, GOLD, TEAL, UNKNOWN};
#define rgb(X) ((X) / 255.0f)

/* Variables for vibrating various parts of the drum set */
float bdHeadQuiver = 1.0f;
int bdHeadQuiverOn = 0;
int bdHeadQuiverC = 0;
float bdBeaterAngle = 0;

float sdHeadQuiver = 0.0f;
int sdHeadQuiverOn = 0;
int sdHeadQuiverC = 0;

float hhQuiver = 0.0f;
int hhQuiverOn = 0;
float hhRotate = 0.0f;
int hhRotateOn = 0;
int hhRotateC = 0;
int hhRotateDir = 0;

float htQuiver = 0.0f;
int htQuiverOn = 0;
int htQuiverC = 0;

float ltQuiver = 0.0f;
int ltQuiverOn = 0;
int ltQuiverC = 0;

float ccRotate = 0.0f;
int ccRotateOn = 0;
int ccRotateC = 0;
int ccRotateDir = 0;


/* Audio */
#define NUM_SOUNDS 7
ALCdevice *device;
ALCenum error;
ALCcontext *context;
ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
ALuint source;
ALuint buffer;

enum Sound {BASS_DRUM, SNARE_DRUM, CLOSED_HIGH_HAT, OPEN_HIGH_HAT, HIGH_TOM, LOW_TOM, CRASH_CYMBAL};

typedef struct {
   ALvoid *data;
   ALenum format;
   ALsizei freq;
   ALsizei size;
} Audio;

Audio sounds[NUM_SOUNDS];

typedef unsigned long DWORD;


/********** TO DO LIST  **********
1. ADD A WAY FOR THE BDBEATER TO MOVE BACK TO 0
*********************************/

/* helper function to make sure your matrix handle is correct */
inline void safe_glUniformMatrix4fv(const GLint handle, const GLfloat data[]) {
  if (handle >= 0)
    glUniformMatrix4fv(handle, 1, GL_FALSE, data);
}

void resetScaleMatrix() {
   g_scale = glm::vec3(1.0, 1.0, 1.0);
}

/* helper function to send materials to the shader */
void SetMaterial(int i) {
 
   glUseProgram(ShadeProg);
   
   switch (i) {
   case HEAD:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.1);
      glUniform3f(h_uMatDif, rgb(237), rgb(235), rgb(211));
      glUniform3f(h_uMatSpec, 0.14, 0.14, 0.4);
      glUniform1f(h_uMatShine, 10.0);
      break;
   case FRAME:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.1);
      glUniform3f(h_uMatDif, rgb(186), rgb(186), rgb(182));
      glUniform3f(h_uMatSpec, 0.14, 0.14, 0.4);
      glUniform1f(h_uMatShine, 120.0);
      break;
   case CYMBAL:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.1);
      glUniform3f(h_uMatDif, rgb(204), rgb(192), rgb(63));
      glUniform3f(h_uMatSpec, 0.14, 0.14, 0.4);
      glUniform1f(h_uMatShine, 120.0);
      break;
   case ORANGE:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.1);
      glUniform3f(h_uMatDif, rgb(250), rgb(157), rgb(50));
      glUniform3f(h_uMatSpec, 0.14, 0.14, 0.14);
      glUniform1f(h_uMatShine, 10.0);
      break;
   case SHINY_BLUE:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.1);
      glUniform3f(h_uMatDif, 0.0, 0.08, 0.5);
      glUniform3f(h_uMatSpec, 0.14, 0.14, 0.4);
      glUniform1f(h_uMatShine, 120.0);
      break;
   case FLAT_GREY:
      glUniform3f(h_uMatAmb, 0.13, 0.13, 0.14);
      glUniform3f(h_uMatDif, 0.3, 0.3, 0.4);
      glUniform3f(h_uMatSpec, 0.3, 0.3, 0.4);
      glUniform1f(h_uMatShine, 4.0);
      break;
   case GOLD:
      glUniform3f(h_uMatAmb, 0.09, 0.07, 0.08);
      glUniform3f(h_uMatDif, 0.91, 0.782, 0.82);
      glUniform3f(h_uMatSpec, 1.0, 0.913, 0.8);
      glUniform1f(h_uMatShine, 200.0);
      break;
   case TEAL:
      glUniform3f(h_uMatAmb, 0.02, 0.02, 0.01);
      glUniform3f(h_uMatDif, 0.0, 0.6, 0.6);
      glUniform3f(h_uMatSpec, 0.4, 0.4, 0.4);
      glUniform1f(h_uMatShine, 10.0);
      break;
   case UNKNOWN:
      glUniform3f(h_uMatAmb, 0, 0, 0);
      glUniform3f(h_uMatDif, 1.0, 1.0, 0);
      glUniform3f(h_uMatSpec, 0.4, 0.4, 0.4);
      glUniform1f(h_uMatShine, 100.0);
      break;
   
   }
}


/* helper function to set projection matrix - don't touch */
void SetProjectionMatrix() {
   glm::mat4 Projection = glm::perspective(90.0f, (float)g_width/g_height, 0.1f, 100.f);
   safe_glUniformMatrix4fv(h_uProjMatrix, glm::value_ptr(Projection));
}

/* camera controls - do not change beyond the current set up to rotate*/
void SetView() {
   glm::mat4 target = glm::lookAt(eye, eye + lookAt, up);
   safe_glUniformMatrix4fv(h_uViewMatrix, glm::value_ptr(target));
}

void updateLookAt() {
   float x, y, z;
   float radius = 1.0;
   
   x = radius * cos(phi) * cos(theta);
   y = radius * sin(phi);
   z = radius * cos(phi) * cos(90.0 - theta);
   
   lookAt = glm::vec3(x, y, z);
}

/* model transforms */
void SetModel(float rotation = 0) {
  glm::mat4 Trans = glm::translate( glm::mat4(1.0f), g_trans);
  glm::mat4 RotateY = glm::rotate( glm::mat4(1.0f), g_angle, glm::vec3(0.0f, 1, 0));
  glm::mat4 RotateY2 = glm::rotate( glm::mat4(1.0f), rotation, glm::vec3(0.0f, 1, 0));
  glm::mat4 RotateX = glm::rotate( glm::mat4(1.0f), x_angle, glm::vec3(1.0f, 0.0, 0.0f));
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), g_scale);
  glm::mat4 com = Trans*RotateY * RotateY2 * RotateX * scale;
  safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(com));
  resetScaleMatrix();
}


//Given a vector of shapes which has already been read from an obj file
// resize all vertices to the range [-1, 1]
void resize_obj(std::vector<tinyobj::shape_t> &currshapes) {
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
    float scaleX, scaleY, scaleZ;
    float shiftX, shiftY, shiftZ;
    float epsilon = 0.001;

    minX = minY = minZ = 1.1754E+38F;
    maxX = maxY = maxZ = -1.1754E+38F;

    //Go through all vertices to determine min and max of each dimension
    for (size_t i = 0; i < currshapes.size(); i++) {
        for (size_t v = 0; v < currshapes[i].mesh.positions.size() / 3; v++) {
            if(currshapes[i].mesh.positions[3*v+0] < minX) minX = currshapes[i].mesh.positions[3*v+0];
            if(currshapes[i].mesh.positions[3*v+0] > maxX) maxX = currshapes[i].mesh.positions[3*v+0];

            if(currshapes[i].mesh.positions[3*v+1] < minY) minY = currshapes[i].mesh.positions[3*v+1];
            if(currshapes[i].mesh.positions[3*v+1] > maxY) maxY = currshapes[i].mesh.positions[3*v+1];

            if(currshapes[i].mesh.positions[3*v+2] < minZ) minZ = currshapes[i].mesh.positions[3*v+2];
            if(currshapes[i].mesh.positions[3*v+2] > maxZ) maxZ = currshapes[i].mesh.positions[3*v+2];
        }
    }
   //From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX-minX;
   yExtent = maxY-minY;
   zExtent = maxZ-minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
     maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
     maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
     maxExtent = zExtent;
   }
    scaleX = 2.0 /maxExtent;
    shiftX = minX + (xExtent/ 2.0);
    scaleY = 2.0 / maxExtent;
    shiftY = minY + (yExtent / 2.0);
    scaleZ = 2.0/ maxExtent;
    shiftZ = minZ + (zExtent)/2.0;

    //Go through all verticies shift and scale them
    for (size_t i = 0; i < currshapes.size(); i++) {
        for (size_t v = 0; v < currshapes[i].mesh.positions.size() / 3; v++) {
            currshapes[i].mesh.positions[3*v+0] = (currshapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
            assert(currshapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
            assert(currshapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
            currshapes[i].mesh.positions[3*v+1] = (currshapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
            assert(currshapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
            assert(currshapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
            currshapes[i].mesh.positions[3*v+2] = (currshapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
            assert(currshapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
            assert(currshapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
        }
    }
}

void loadShapes(const string &objFile) {
	string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
	if(!err.empty()) {
		cerr << err << endl;
	}
   resize_obj(shapes);
}

void loadShapesCube(const string &objFile) {
   string err = tinyobj::LoadObj(shapes_cube, materials_cube, objFile.c_str());
	if(!err.empty()) {
		cerr << err << endl;
	}
   resize_obj(shapes_cube);
}


vector<float> computeNormals(vector<tinyobj::shape_t> currArr) {
   vector<float> norBuf;
   int idx1, idx2, idx3;
   glm::vec3 v1, v2, v3;
   
   //for every vertex initialize a normal to 0
   for (int j = 0; j < currArr[0].mesh.positions.size()/3; j++) {
      norBuf.push_back(0);
      norBuf.push_back(0);
      norBuf.push_back(0);
   }
   
   // DO work here to compute the normals for every face
   //then add its normal to its associated vertex
   for (int i = 0; i < currArr[0].mesh.indices.size()/3; i++) {
      idx1 = currArr[0].mesh.indices[3*i+0];
      idx2 = currArr[0].mesh.indices[3*i+1];
      idx3 = currArr[0].mesh.indices[3*i+2];
      v1 = glm::vec3(currArr[0].mesh.positions[3*idx1 +0],currArr[0].mesh.positions[3*idx1 +1], currArr[0].mesh.positions[3*idx1 +2]); 
      v2 = glm::vec3(currArr[0].mesh.positions[3*idx2 +0],currArr[0].mesh.positions[3*idx2 +1], currArr[0].mesh.positions[3*idx2 +2]); 
      v3 = glm::vec3(currArr[0].mesh.positions[3*idx3 +0],currArr[0].mesh.positions[3*idx3 +1], currArr[0].mesh.positions[3*idx3 +2]);
      
      glm::vec3 e1 = v2 - v1;
      glm::vec3 e2 = v3 - v1;
      glm::vec3 res = glm::cross(e1, e2);
      glm::vec3 norm = glm::normalize(res);
      
      norBuf[3*idx1+0] += norm.x;
      norBuf[3*idx1+1] += norm.y;
      norBuf[3*idx1+2] += norm.z;
      norBuf[3*idx2+0] += norm.x;
      norBuf[3*idx2+1] += norm.y;
      norBuf[3*idx2+2] += norm.z;
      norBuf[3*idx3+0] += norm.x;
      norBuf[3*idx3+1] += norm.y;
      norBuf[3*idx3+2] += norm.z;
   }
   
   /* After computing, do a final normalizing */
   for (int i = 0; i < norBuf.size() / 3; ++i) {
      glm::vec3 toNorm = glm::vec3(norBuf[3*i+0], norBuf[3*i+1], norBuf[3*i+2]);
      glm::vec3 norm = glm::normalize(toNorm);
      norBuf[3*i+0] = norm.x;
      norBuf[3*i+1] = norm.y;
      norBuf[3*i+2] = norm.z;
   }
   
   return norBuf;
}


void initGL() {
	// Set the background color
	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
	// Enable Z-buffer test
	glEnable(GL_DEPTH_TEST);
   glPointSize(18);
	
	/* STEP 1 - BUNNY */
	
	// Send the position array to the GPU
	const vector<float> &posBuf = shapes[0].mesh.positions;
	glGenBuffers(1, &posBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
	
	// TODO compute the normals per vertex - you must fill this in 
	vector<float> bunnyNormals = computeNormals(shapes);
   
	glGenBuffers(1, &norBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
	glBufferData(GL_ARRAY_BUFFER, bunnyNormals.size()*sizeof(float), &bunnyNormals[0], GL_STATIC_DRAW);
	
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
	
	
	/* STEP 2 - CUBE */
	
	// Send the position array to the GPU
	const vector<float> &posBufCube = shapes_cube[0].mesh.positions;
	glGenBuffers(1, &posBufObjCube);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObjCube);
	glBufferData(GL_ARRAY_BUFFER, posBufCube.size()*sizeof(float), &posBufCube[0], GL_STATIC_DRAW);
	
	vector<float> cubeNormals = computeNormals(shapes_cube);
	
	glGenBuffers(1, &norBufObjCube);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjCube);
	glBufferData(GL_ARRAY_BUFFER, cubeNormals.size()*sizeof(float), &cubeNormals[0], GL_STATIC_DRAW);
	
	// Send the index array to the GPU
	const vector<unsigned int> &indBufCube = shapes_cube[0].mesh.indices;
	glGenBuffers(1, &indBufObjCube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjCube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBufCube.size()*sizeof(unsigned int), &indBufCube[0], GL_STATIC_DRAW);

	// Unbind the arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLSL::checkVersion();
	assert(glGetError() == GL_NO_ERROR);
	
	//initialize the modeltrans matrix stack
   ModelTrans.useModelViewMatrix();
   ModelTrans.loadIdentity();

}

bool installShaders(const string &vShaderName, const string &fShaderName) {
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
	ShadeProg = glCreateProgram();
	glAttachShader(ShadeProg, VS);
	glAttachShader(ShadeProg, FS);
	glLinkProgram(ShadeProg);
   
	GLSL::printError();
	glGetProgramiv(ShadeProg, GL_LINK_STATUS, &rc);
	GLSL::printProgramInfoLog(ShadeProg);
	if(!rc) {
      printf("Error linking shaders %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
      return false;
	}

   /* get handles to attribute data */
    h_aPosition = GLSL::getAttribLocation(ShadeProg, "aPos");
    h_aNormal = GLSL::getAttribLocation(ShadeProg, "aNor");
    h_uProjMatrix = GLSL::getUniformLocation(ShadeProg, "uProjMatrix");
    h_uViewMatrix = GLSL::getUniformLocation(ShadeProg, "uViewMatrix");
    h_uModelMatrix = GLSL::getUniformLocation(ShadeProg, "uModelMatrix");
    h_uLightPos = GLSL::getUniformLocation(ShadeProg, "uLightPos");
    h_uMatAmb = GLSL::getUniformLocation(ShadeProg, "UaColor");
    h_uMatDif = GLSL::getUniformLocation(ShadeProg, "UdColor");
    h_uMatSpec = GLSL::getUniformLocation(ShadeProg, "UsColor");
    h_uMatShine = GLSL::getUniformLocation(ShadeProg, "Ushine");
    h_uShadeM = GLSL::getUniformLocation(ShadeProg, "uShadeModel");
    
    h_forceNormals = GLSL::getUniformLocation(ShadeProg, "forceNormals");
	
	assert(glGetError() == GL_NO_ERROR);
	return true;
}

void updateRobotRadius() {
   if (robotDir) {
      robotTheta -= 1;
      if (robotTheta < -20)
         robotDir = 0;
   } else {
      robotTheta += 1;
      if (robotTheta > 20)
         robotDir = 1;
   }
}

void placeRobotAt(float x, float y, float z, float rotation, int nIndices) {

   ModelTrans.loadIdentity();
   
   /* Chest */
   ModelTrans.translate(glm::vec3(x, y, z));
   ModelTrans.rotate(rotation, glm::vec3(0, 1, 0));
   ModelTrans.pushMatrix(); // Push for (model's) left arm
   ModelTrans.pushMatrix(); // Push for right arm
   ModelTrans.pushMatrix(); // Push for Head
   ModelTrans.pushMatrix(); // Push for Left Foot
   ModelTrans.pushMatrix(); // Push for Right Foot
   
      /* Upper LEFT arm */
      ModelTrans.translate(glm::vec3(.8, 1, 0)); // Move to relative position
      ModelTrans.rotate(30, glm::vec3(0, 0, 1)); // Rotate around origin
      ModelTrans.translate(glm::vec3(2, .5, 0)); // To origin
      ModelTrans.pushMatrix(); // Upper arm
      
         /* Lower Arm/Forearm (waving) */
         ModelTrans.translate(glm::vec3(1, 0, 0)); // Move to relative position
         ModelTrans.rotate(robotTheta, glm::vec3(0, 0, 1)); // Rotate around origin
         ModelTrans.translate(glm::vec3(2, 0, 0)); // To origin
         ModelTrans.scale(2, 1, 1);
         // Draw forearm
         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   ModelTrans.popMatrix();
	   // Draw upper arm
	   ModelTrans.scale(2, .5, .9);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop to draw RIGHT ARM
	ModelTrans.popMatrix();
	   
	   /* Upper RIGHT arm */
      ModelTrans.translate(glm::vec3(-.8, 1.6, 0)); // Move to relative position
      ModelTrans.rotate(45, glm::vec3(0, 0, 1)); // Rotate around origin
      ModelTrans.translate(glm::vec3(-2, .5, 0)); // To origin
      ModelTrans.pushMatrix(); // Upper arm
      
         /* Lower Arm/Forearm */
         ModelTrans.translate(glm::vec3(-1, 0, 0)); // Move to relative position
         //ModelTrans.rotate(0, glm::vec3(0, 0, 1)); // Rotate around origin
         ModelTrans.translate(glm::vec3(-2, 0, 0)); // To origin
         ModelTrans.scale(2, 1, 1);
         // Draw forearm
         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   ModelTrans.popMatrix();
	   // Draw upper arm
	   ModelTrans.scale(2, .5, .9);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop to draw HEAD
	ModelTrans.popMatrix();
	   
	   /* Head */
	   ModelTrans.translate(glm::vec3(0, 4, 0)); // Move to relative position
	   ModelTrans.translate(glm::vec3(0, 0, 0)); // To origin
	   ModelTrans.pushMatrix(); // HEAD
	   ModelTrans.pushMatrix();
	   ModelTrans.pushMatrix();
	      
	      /* Model's Left Eye */
	      ModelTrans.translate(glm::vec3(.5, .5, 1));
	      ModelTrans.scale(.2, .2, .2);
	      // Draw left eye
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      ModelTrans.popMatrix();
	      
	      /* Model's Right Eye */
	      ModelTrans.translate(glm::vec3(-.5, .5, 1));
	      ModelTrans.scale(.2, .2, .2);
	      // Draw right eye
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      ModelTrans.popMatrix();
	      
	      /* Mouth */
	      ModelTrans.translate(glm::vec3(0, -.2, 1));
	      ModelTrans.scale(.7, .2, .2);
	      // Draw Mouth
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   ModelTrans.popMatrix();
	   // Draw Head
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop to draw Left Foot
	ModelTrans.popMatrix();
	
	   /* Left Leg */
      ModelTrans.translate(glm::vec3(-1, -4, 0)); // Move to relative position
      //ModelTrans.rotate(0, glm::vec3(0, 0, 1)); // Rotate around origin
      ModelTrans.translate(glm::vec3(0, 0, 0)); // To origin
      ModelTrans.scale(.5, 2, .9);
      // Draw leg
      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop to draw Right Foot
	ModelTrans.popMatrix();
	
	   /* Right Leg */
      ModelTrans.translate(glm::vec3(1, -4, 0)); // Move to relative position
      //ModelTrans.rotate(0, glm::vec3(0, 0, 1)); // Rotate around origin
      ModelTrans.translate(glm::vec3(0, 0, 0)); // To origin
      ModelTrans.scale(.5, 2, .9);
      // Draw leg
      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	ModelTrans.popMatrix();
	// Draw Chest
	ModelTrans.scale(2, 3, 1);
	glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

}

void scaleCylinder(float x, float y, float z) {
   ModelTrans.scale(x * 2, y * .5, z * 2);
}

void updateQuivers() {
   // BASS DRUM
   if (bdHeadQuiverOn) {
      bdHeadQuiverC++;
      if (bdHeadQuiver < 1.04 && bdHeadQuiverC < 10)
         bdHeadQuiver = 1.05;
      else
         bdHeadQuiver = .95;
      
      if (bdBeaterAngle < 5   )
         bdBeaterAngle += 2;
   } else {
      bdHeadQuiver = 1;
      bdHeadQuiverC = 0;
      
      bdBeaterAngle = 0;
   }
   
   // SNARE DRUM
   if (sdHeadQuiverOn) {
      sdHeadQuiverC++;
      if (sdHeadQuiverC > 10) {
         sdHeadQuiver = 0;
      } else
      if (sdHeadQuiver < .02)
         sdHeadQuiver = .025;
      else
         sdHeadQuiver = -.025;
   } else {
      sdHeadQuiver = 0;
      sdHeadQuiverC = 0;
   }
   
   // HIGH HAT
   if (hhQuiverOn) {
      if (hhQuiver < .07)
         hhQuiver += .0125;
   } else {
      if (hhQuiver > 0) {
         hhQuiver -= .0125;
      }
   }
   // HIGH HAT ROTATE
   if (hhRotateOn) {
      hhRotateC++;
      if (hhRotateC > (hhQuiverOn ? 10 : 30)) {
         hhRotate = 0;
      } else
      if (hhRotateDir) {
         hhRotate -= 2;
         if (hhRotate < -3)
            hhRotateDir = 0;
      } else {
         hhRotate += 2;
         
         if (hhRotate > 3)
            hhRotateDir = 1;
      }
   } else {
      hhRotate = 0;
      hhRotateC = 0;
      hhRotateDir = 0;
   }
   
   // HIGH TOM
   if (htQuiverOn) {
      htQuiverC++;
      if (htQuiverC > 10) {
         htQuiver = 0;
      } else
      if (htQuiver < .02)
         htQuiver = .025;
      else
         htQuiver = -.025;
   } else {
      htQuiver = 0;
      htQuiverC = 0;
   }
   
   // LOW TOM
   if (ltQuiverOn) {
      ltQuiverC++;
      if (ltQuiverC > 10) {
         ltQuiver = 0;
      } else
      if (ltQuiver < .02)
         ltQuiver = .025;
      else
         ltQuiver = -.025;
   } else {
      ltQuiver = 0;
      ltQuiverC = 0;
   }
   
   // CRASH CYMBAL
   if (ccRotateOn) {
      ccRotateC++;
      if (ccRotateC > 30) {
         ccRotate = 0;
      } else
      if (ccRotateDir) {
         ccRotate -= 2;
         if (ccRotate < -3)
            ccRotateDir = 0;
      } else {
         ccRotate += 2;
         
         if (ccRotate > 3)
            ccRotateDir = 1;
      }
   } else {
      ccRotate = 0;
      ccRotateC = 0;
      ccRotateDir = 0;
   }
   
}

void doBunny() {
   int nIndices;
	
	/* FIRST: CODE FOR BUNNY OBJECT */

	// Enable and bind position array for drawing
	GLSL::enableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
	glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Enable and bind normal array for drawing
	GLSL::enableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
	glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Bind index array for drawing
   nIndices = (int)shapes[0].mesh.indices.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObj);
	
	
	SetView();
	
	glUniform3f(h_uLightPos, g_light.x, g_light.y, g_light.z);
   glUniform1i(h_uShadeM, g_SM);
   
   glUniform1i(h_forceNormals, forceNormals);
   
   updateQuivers();

	/*********************/
	
	// Tw * Rw * Tmodel * Rpiv * Tpiv * S * obj
	
	ModelTrans.loadIdentity();
	
	/* Bass drum */
	ModelTrans.translate(glm::vec3(0, 0, -3));
	ModelTrans.rotate(worldRadius, glm::vec3(0, 1, 0));
   ModelTrans.pushMatrix(); // Frame
   ModelTrans.pushMatrix(); // Left stand
   ModelTrans.pushMatrix(); // Right stand
   ModelTrans.pushMatrix(); // Kick part
   ModelTrans.pushMatrix(); // Snare drum/stand
   ModelTrans.pushMatrix(); // High Hat
   ModelTrans.pushMatrix(); // High Tom
   ModelTrans.pushMatrix(); // Low Tom
   ModelTrans.pushMatrix(); // Crash Cymbal
   
      // Draw bass drum FRAME
      ModelTrans.rotate(85, glm::vec3(1, 0, 0));
      scaleCylinder(1.6, .9, 1.6);
      SetMaterial(FRAME);
      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop for LEFT STAND
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(-.6, -.5, .2));
	   ModelTrans.rotate(-30, glm::vec3(0, 0, 1));
	   scaleCylinder(.1, .4, .1);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop for RIGHT STAND
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(.6, -.5, .2));
	   ModelTrans.rotate(30, glm::vec3(0, 0, 1));
	   scaleCylinder(.1, .4, .1);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	// Pop for KICK PART
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(0, -1.3, -.6));
	   ModelTrans.rotate(bdBeaterAngle, glm::vec3(1, 0, 0));
	   ModelTrans.translate(glm::vec3(0, 1, 0));
	   ModelTrans.pushMatrix(); // Beater
	   
	      ModelTrans.translate(glm::vec3(0, .2, 0));
	      scaleCylinder(.2, .1, .2);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   // Beater Stick   
	   ModelTrans.popMatrix();
	   scaleCylinder(.1, .5, .1);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   
	// Pop for SNARE DRUM/STAND
	ModelTrans.popMatrix();
	
	      ModelTrans.translate(glm::vec3(1.2, 0, 0));
	      ModelTrans.pushMatrix(); // Drum
	      ModelTrans.pushMatrix(); // Rim
	      
	         // Snare drum
	         SetMaterial(HEAD);
	         ModelTrans.translate(glm::vec3(0, .1, 0));
	         ModelTrans.rotate(15, glm::vec3(-1, 0, .8));
	         scaleCylinder(1, .3 + sdHeadQuiver, 1);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      // Pop for Rim
	      ModelTrans.popMatrix();
	      
	         // Rim
	         SetMaterial(TEAL);
	         ModelTrans.translate(glm::vec3(0, .1, 0));
	         ModelTrans.rotate(15, glm::vec3(-1, 0, .8));
	         scaleCylinder(1.01, .27, 1.01);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	         
	      // Pop for stand
	      ModelTrans.popMatrix();
	      ModelTrans.translate(glm::vec3(0, -.3, 0));
	      scaleCylinder(.1, .8, .1);
	      SetMaterial(FRAME);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   
	// Pop for HIGH HAT
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(1.8, 0, -.8));
	   ModelTrans.pushMatrix(); // Lower Cymbal
	   ModelTrans.pushMatrix(); // Upper Cymbal
	   
	      // Upper Cymbal
	      SetMaterial(CYMBAL);
	      ModelTrans.translate(glm::vec3(0, 1.09 - hhQuiver, 0));
	      ModelTrans.rotate(0 + hhRotate, glm::vec3(1, 0, 1));
	      ModelTrans.pushMatrix();
	      
	         // Dome
	         ModelTrans.translate(glm::vec3(0, .04, 0));
	         scaleCylinder(.2, .05, .2);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      ModelTrans.popMatrix();
	      scaleCylinder(1, .02, 1);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   // Pop for Lower Cymbal
	   ModelTrans.popMatrix();
	   
	      // Lower Cymbal
	      SetMaterial(CYMBAL);
	      ModelTrans.translate(glm::vec3(0, 1.0, 0));
	      ModelTrans.pushMatrix();
	      
	         // Dome
	         ModelTrans.translate(glm::vec3(0, -.04, 0));
	         scaleCylinder(.2, .05, .2);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      ModelTrans.popMatrix();
	      scaleCylinder(1, .02, 1);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   // Pop for High Hat Stand
	   ModelTrans.popMatrix();
	   ModelTrans.translate(glm::vec3(0, .5, 0));
	   scaleCylinder(.05, 2.5, .05);
	   SetMaterial(FRAME);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	
	// Pop for HIGH TOM
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(.2, .5, 0));
	   ModelTrans.pushMatrix(); // Connector bit
	   
	      ModelTrans.translate(glm::vec3(0, .5, 0));
	      ModelTrans.pushMatrix(); // Tom
	      ModelTrans.pushMatrix(); // Frame
	      
	         // Low Tom Head
	         ModelTrans.translate(glm::vec3(.35, 0, 0));
	         ModelTrans.rotate(-45, glm::vec3(1, 0, 0));
	         scaleCylinder(.7, .4 + htQuiver, .7);
	         SetMaterial(HEAD);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      // Pop for Frame
	      ModelTrans.popMatrix();
	      
	         // Frame
	         ModelTrans.translate(glm::vec3(.35, 0, 0));
	         ModelTrans.rotate(-45, glm::vec3(1, 0, 0));
	         scaleCylinder(.72, .37, .72);
	         SetMaterial(ORANGE);
	         glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	         glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	      // Connector Bit
	      ModelTrans.popMatrix();
	      ModelTrans.rotate(80, glm::vec3(0, 0, 1));
	      scaleCylinder(.05, .2, .05);
	      SetMaterial(FRAME);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   // Stand
	   ModelTrans.popMatrix();
	   scaleCylinder(.1, 1.2, .1);
	   SetMaterial(FRAME);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	
	// Pop for LOW TOM
	ModelTrans.popMatrix();
	
	   ModelTrans.translate(glm::vec3(-1, 0, -1));
	   ModelTrans.pushMatrix(); // Stand 1
	   ModelTrans.pushMatrix(); // Stand 2
	   ModelTrans.pushMatrix(); // Stand 3
	   ModelTrans.pushMatrix(); // Frame
	   
	      // Stand 1
	      ModelTrans.translate(glm::vec3(.3, -.2, 0));
	      ModelTrans.rotate(15, glm::vec3(0, 0, 1));
	      scaleCylinder(.1, 1, .1);
	      SetMaterial(FRAME);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   // Pop for Stand 2
	   ModelTrans.popMatrix();
	   
	      // Stand 2
	      ModelTrans.translate(glm::vec3(-.05, -.2, -.45));
	      ModelTrans.rotate(25, glm::vec3(1, 0, -.5));
	      scaleCylinder(.1, .75, .1);
	      SetMaterial(FRAME);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   // Pop for Stand 3
	   ModelTrans.popMatrix();
	   
	      // Stand 3
	      ModelTrans.translate(glm::vec3(-.15, -.2, .3));
	      ModelTrans.rotate(25, glm::vec3(-1, 0, -1));
	      scaleCylinder(.1, .75, .1);
	      SetMaterial(FRAME);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	      
	   // Pop for Frame
	   ModelTrans.popMatrix();
	   
	      // Frame
	      ModelTrans.rotate(15, glm::vec3(.5, .2, -1));
	      scaleCylinder(1.05, .75, 1.05);
	      SetMaterial(SHINY_BLUE);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   // Low Tom
	   ModelTrans.popMatrix();
	   ModelTrans.rotate(15, glm::vec3(.5, .2, -1));
	   scaleCylinder(1, .8 + ltQuiver, 1);
	   SetMaterial(HEAD);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	
	// Pop for CRASH CYMBAL
	ModelTrans.popMatrix();
	
	   // Crash Cymbal
	   ModelTrans.translate(glm::vec3(1.9, .25, .7));
	   ModelTrans.pushMatrix();
	   
	      // Cymbal
	      ModelTrans.translate(glm::vec3(0, .8, 0));
	      ModelTrans.rotate(0 + ccRotate, glm::vec3(1, 0, -1));
	      scaleCylinder(1.5, .01, 1.5);
	      SetMaterial(CYMBAL);
	      glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	      glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	   ModelTrans.popMatrix();
	   scaleCylinder(.05, 2, .05);
	   SetMaterial(FRAME);
	   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	   glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	   
	
	// Finally pop for BASS DRUM HEAD (our root, lord, and savior)
	ModelTrans.popMatrix();
   
   // Draw bass drum HEAD
   ModelTrans.rotate(85, glm::vec3(1, 0, 0));
   scaleCylinder(1.5, bdHeadQuiver, 1.5);
   SetMaterial(HEAD);
   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);


	/*********************/
	
   // Disable and unbind
   GLSL::disableVertexAttribArray(h_aPosition);
	GLSL::disableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	
void doRobot() {
   int nIndices;
	
	/* SECOND: CODE FOR CUBE OBJECT */
	
	// Enable and bind position array for drawing
	GLSL::enableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObjCube);
	glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Enable and bind normal array for drawing
	GLSL::enableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjCube);
	glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Bind index array for drawing
	nIndices = (int)shapes_cube[0].mesh.indices.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjCube);
	
	//SetView();
	
	//glUniform3f(h_uLightPos, g_light.x, g_light.y, g_light.z);
   //glUniform1i(h_uShadeM, g_SM);
   
   //glUniform1i(h_forceNormals, forceNormals);
   
   /*********************/
   
   SetMaterial(UNKNOWN);
   ModelTrans.loadIdentity();
   ModelTrans.translate(glm::vec3(.75, .75, -4.75));
   ModelTrans.scale(1.75, 1.75, 1.75);
   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
   
   /*
   SetMaterial(3);
   // PLANE
   ModelTrans.loadIdentity();
   ModelTrans.translate(glm::vec3(0, -1, 0));
   ModelTrans.scale(50, .05, 50);
   glUniformMatrix4fv(h_uModelMatrix, 1, GL_FALSE, glm::value_ptr(ModelTrans.modelViewMatrix));
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
   
   SetMaterial(4);
   // CUBE 1 - LIGHT
	g_trans = g_light;
	g_scale = glm::vec3(.2, .2, .2);
	SetModel();
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
	
	SetMaterial(g_mat_id);
	
	// ROBOT 1
	placeRobotAt(-4, 5, -6, 0, nIndices);
	
	// ROBOT 2
	placeRobotAt(4, 5, -10, 45, nIndices);
	
	// ROBOT 3
	placeRobotAt(15, 5, 8, 130, nIndices);
	
	// ROBOT 4
	placeRobotAt(-25, 5, -25, 240, nIndices); // n,n
	
	// ROBOT 5
	placeRobotAt(-30, 5, -25, 50, nIndices); // n,n
	
	// ROBOT 6
	placeRobotAt(30, 5, -30, 0, nIndices); // p,n
	
	// ROBOT 7
	placeRobotAt(30, 5, -25, 180, nIndices); // p,n
	
	
	// ROBOT 8
	placeRobotAt(30, 5, 30, 180, nIndices); // p,p
	
	// ROBOT 9
	placeRobotAt(35, 5, 25, 325, nIndices); // p,p
	
	// ROBOT 10
	placeRobotAt(25, 5, 25, 45, nIndices); // p,p
	*/
   /*********************/
   
   // Disable and unbind
   GLSL::disableVertexAttribArray(h_aPosition);
	GLSL::disableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	
	glUseProgram(0);
	assert(glGetError() == GL_NO_ERROR);
	
	updateRobotRadius();
}



void drawGL() {
   
   // Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Use our GLSL program
	glUseProgram(ShadeProg);
	
	// Compute and send the projection matrix
	SetProjectionMatrix();

   doBunny();
   
   doRobot();
   
   if (doRotate)
      worldRadius += 1;
      
	if (worldRadius > 360) {
	   worldRadius = 0;
	}
	
}

void prepareAudio() {
   alGetError();
   
   device = alcOpenDevice(NULL);
   if (!device) {
      printf("Error in opening audio device");
   }
   error = alGetError();
   if (error != AL_NO_ERROR) {
      //printf("AL Error in opening device: %d\n",error);
   }
   
   context = alcCreateContext(device, NULL);
   if (!alcMakeContextCurrent(context)) {
      printf("Error in making context current\n");
   }
   error = alGetError();
   if (error != AL_NO_ERROR) {
      printf("AL Error in making context current: %d\n",error);
   }
   
   alListener3f(AL_POSITION, 0, 0, 1.0f);
   alListener3f(AL_VELOCITY, 0, 0, 0);
   alListenerfv(AL_ORIENTATION, listenerOri);
   
   alGenSources((ALuint)1, &source);
   alSourcef(source, AL_PITCH, 1);
   alSourcef(source, AL_GAIN, 1);
   alSource3f(source, AL_POSITION, 0, 0, 0);
   alSource3f(source, AL_VELOCITY, 0, 0, 0);
   alSourcei(source, AL_LOOPING, AL_FALSE);
   
   alGenBuffers((ALuint)1, &buffer);
}

void cleanupAudio() {
   alDeleteSources(1, &source);
   alDeleteBuffers(1, &buffer);
   
   device = alcGetContextsDevice(context);

   if (context) {
      alcMakeContextCurrent(NULL);
      alcDestroyContext(context);
   }
   
   if (device) {
      alcCloseDevice(device);
   } else {
      printf("Error - no device to close");
   }
}

/* Adopted (with plenty of changes) from http://www.cpp-home.com/tutorials/333_1.htm */
Audio Load_Wave_File(char *fname) { 
   Audio ret = {NULL, 0, 0, 0};
   
   FILE *fp; 
   //char *sound_buffer = NULL;

   fp = fopen(fname,"rb"); 
   if (!fp) {
      printf("Wave File %s could not be opened\n", fname);
      return ret;
   }
   
   printf("Proceeding to process file %s\n", fname);
   
   /*
Offset   Length   Contents
  0      4 bytes  "RIFF"
  4      4 bytes  <File length - 8>
  8      4 bytes  "WAVE"

 12      4 bytes  "fmt "
 16      4 bytes  <Length of the fmt data> // (=16)
 20      2 bytes  <WAVE File Encoding Tag>
 22      2 bytes  <Channels>     // Channels: 1 = mono, 2 = stereo
 24      4 bytes  <Sample rate>  // Samples per second: e.g., 44100
 28      4 bytes  <bytes/second> // sample rate * block align
 32      2 bytes  <block align>  // channels * bits/sample / 8
 34      2 bytes  <bits/sample>  // 8 or 16

 36      4 bytes  "data"
 40      4 bytes  <Sample data size(n)>
 44     (n)bytes  <Sample data>
   */
   
   char id[5]; //four bytes to hold 'RIFF' and one to hold '\0'
   int size; //32 bit value to hold file size 
   short format_tag, channels, block_align, bits_per_sample; //our 16 values 
   int format_length, sample_rate, avg_bytes_sec, i; //our 32 bit values 
   int data_size;
   
   id[4] = 0;

   fread(id, sizeof(char), 4, fp); //read in first four bytes
   if (!strcmp(id, "RIFF")) { //we had 'RIFF' let's continue
   
      fread(&size, sizeof(int), 1, fp); //read in 32bit size value 
      //printf("File Size: %i\n", size);
      
      fread(id, sizeof(char), 4, fp); //read in 4 byte string now
      if (!strcmp(id,"WAVE")) { //this is probably a wave file since it contained "WAVE" 
      
         fread(id, sizeof(char), 4, fp); //read in 4 bytes "fmt ";
         if (!strcmp(id, "fmt ")) {
         
            fread(&format_length, sizeof(int),1,fp); 
            //printf("format_length: %d\n", format_length);
         
            fread(&format_tag, sizeof(short), 1, fp); //check mmreg.h (i think?) for other
            // possible format tags like ADPCM 
            //printf("format_tag: %u\n", format_tag);
         
            fread(&channels, sizeof(short),1,fp); //1 mono, 2 stereo 
            printf("channels (expecting 1 or 2): %u\n", channels);
         
            // Set al_format
            if (channels == 1) {
               if (format_length == 8) {
                  ret.format = AL_FORMAT_MONO8;
               } else if (format_length == 16) {
                  ret.format = AL_FORMAT_MONO16;
               } else {
                  printf("format_length (%d) is not 8 or 16. Aborting\n", format_length);
               }
            } else if (channels == 2) {
               if (format_length == 8) {
                  ret.format = AL_FORMAT_STEREO8;
               } else if (format_length == 16) {
                  ret.format = AL_FORMAT_STEREO16;
               } else {
                  printf("format_length (%d) is not 8 or 16. Aborting\n", format_length);
               }
            } else {
               printf("Channels (%d) is not 1 or 2. Aborting.\n", channels);
               return ret;
            }
         
            fread(&sample_rate, sizeof(int), 1, fp); //like 44100, 22050, etc... 
            printf("sample_rate (hertz): %d\n", sample_rate);
         
            // Set al_freq
            ret.freq = sample_rate;
         
            fread(&avg_bytes_sec, sizeof(int), 1, fp); //probably won't need this 
            fread(&block_align, sizeof(short), 1, fp); //probably won't need this 
         
            fread(&bits_per_sample, sizeof(short), 1, fp); //8 bit or 16 bit file?
            printf("bits_per_sample: %u\n", bits_per_sample);
          
            fread(id, sizeof(char), 4, fp); //read in 'data'
            if (strcmp(id, "data")) {
               printf("'data' check FAILED\n");
            }
         
               fread(&data_size, sizeof(int), 1, fp); //how many bytes of sound data we have
               printf("Data Size: %d\n", data_size);
               
               // Set al_size
               ret.size = data_size;
         
               ret.data = malloc(sizeof(char) * data_size); //set aside sound buffer space 
               if (ret.data == NULL) {
               
                  int newSize = 0;
                  newSize |= data_size << 24;
                  newSize |= ((data_size & 0x00F0) << 8);
                  newSize |= (data_size & 0x0F00) >> 8;
                  newSize |= (data_size >> 24) & 0x000F;
                  
                  ret.size = newSize;
                  printf("Attempting new Data Size: %d\n", newSize);
                  ret.data = malloc(sizeof(char) * newSize); //set aside sound buffer space
               
                  printf("ERROR! MALLOC failed!\n");
                  return ret;
               }
               
               fread(ret.data, sizeof(char), data_size, fp); //read in our whole sound data chunk 
            
            //} else
               //printf("Error: 'data' check failed: '%s'\n", id);
         } else
            printf("Error: 'fmt ' check failed\n");
      } else 
         printf("Error: RIFF file but not a wave file\n"); 
   } else 
      printf("Error: not a RIFF file\n");
   
   printf("\n");
   
   fclose(fp);
   
   return ret; 
}

/* Audio help from http://ffainelli.github.io/openal-example/ */
void playSound(int song) {
   
   //Audio audio = Load_Wave_File((char *)name);
   Audio audio = sounds[song];
   if (audio.data == NULL) {
      return;
   }
   
   ALboolean loop = AL_FALSE;
   
   alBufferData(buffer, audio.format, audio.data, audio.size, audio.freq);
   alSourcei(source, AL_BUFFER, buffer);
   
   alSourcePlay(source);
   
   /*
   int source_state;
   alGetSourcei(source, AL_SOURCE_STATE, &source_state);
   while (source_state == AL_PLAYING) {
      alGetSourcei(source, AL_SOURCE_STATE, &source_state);
   }
   */
   
}




void window_size_callback(GLFWwindow* window, int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	g_width = w;
	g_height = h;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (action == GLFW_PRESS) {
      //if (key == GLFW_KEY_J)
      //   g_angle += 10;
      //if (key == GLFW_KEY_L)
      //   g_angle -= 10;
      if (key == GLFW_KEY_M)
         g_mat_id = (g_mat_id+1) % numMaterials; 
      if (key == GLFW_KEY_Z)
         g_SM = !g_SM; 
      if (key == GLFW_KEY_Q)
         g_light.x += 0.25; 
      if (key == GLFW_KEY_E)
         g_light.x -= 0.25; 
      
      if (key == GLFW_KEY_N) {
         forceNormals = forceNormals == 0 ? 1 : 0;
      }
      //if (key == GLFW_KEY_I) {
      //   x_angle += 10;
      //}
      //if (key == GLFW_KEY_K) {
      //   x_angle -= 10;
      //}
      
      if (key == GLFW_KEY_W)
         eye += GLfloat(1) * lookAt;
      if (key == GLFW_KEY_S)
         eye -= GLfloat(1) * lookAt;
      if (key == GLFW_KEY_A)
         eye -= glm::normalize(glm::cross(lookAt, up)) * GLfloat(1);
      if (key == GLFW_KEY_D)
         eye += glm::normalize(glm::cross(lookAt, up)) * GLfloat(1);
         
         
      // AUDIO
      
      if (key == GLFW_KEY_SPACE) {
         bdHeadQuiverOn = 1;
         playSound(BASS_DRUM);
      }
      
      if (key == GLFW_KEY_F) {
         sdHeadQuiverOn = 1;
         playSound(SNARE_DRUM);
      }
      
      if (key == GLFW_KEY_H) {
         hhQuiverOn = !hhQuiverOn;
      }
      if (key == GLFW_KEY_J) {
         if (hhQuiverOn)
            playSound(CLOSED_HIGH_HAT);
         else
            playSound(OPEN_HIGH_HAT);
            
         hhRotateOn = 1;
      }
      if (key == GLFW_KEY_U) {
         playSound(HIGH_TOM);
         htQuiverOn = 1;
      }
      if (key == GLFW_KEY_I) {
         playSound(LOW_TOM);
         ltQuiverOn = 1;
      }
      if (key == GLFW_KEY_G) {
         playSound(CRASH_CYMBAL);
         ccRotateOn = 1;
      }
      
      
      
      if (key == GLFW_KEY_P)
         doRotate = 0;
      
      updateLookAt();
      
      
   } else if (action == GLFW_RELEASE) { // RELEASE A KEY
   
   
      cleanupAudio();
      prepareAudio();
      
      // AUDIO
      
      if (key == GLFW_KEY_SPACE)
         bdHeadQuiverOn = 0;
         
      if (key == GLFW_KEY_F)
         sdHeadQuiverOn = 0;
         
      if (key == GLFW_KEY_J)
         hhRotateOn = 0;
         
      if (key == GLFW_KEY_P)
         doRotate = 1;
      
      if (key == GLFW_KEY_U)
         htQuiverOn = 0;
      
      if (key == GLFW_KEY_I)
         ltQuiverOn = 0;
      
      if (key == GLFW_KEY_G)
         ccRotateOn = 0;
      
   }
}

void scroll_callback(GLFWwindow *window, double deltX, double deltY) {
   
   phi += .05 * deltY;
   if (phi > (3.14 / 2.0)) {
      phi = 3.1 / 2.0;
   } else if (phi < (-3.14 / 2.0)) {
      phi = -3.1 / 2.0;
   }
   
   theta -= .05 * deltX;
   
   updateLookAt();
}

int main(int argc, char **argv) {

   // Initialise GLFW
   if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

   // Open a window and create its OpenGL context
   window = glfwCreateWindow( g_width, g_height, "Program 4", NULL, NULL);
   if( window == NULL ) {
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, key_callback);
   glfwSetWindowSizeCallback(window, window_size_callback);
   glfwSetScrollCallback(window, scroll_callback);
   // Initialize GLEW
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
   }

   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
	loadShapes("cylinder.obj");
	loadShapesCube("robot/intact_robot.obj");
	//loadShapes("sphere.obj");
	
   initGL();
   installShaders("vert.glsl", "frag.glsl");

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

   updateLookAt();
   
   
   prepareAudio();
   
   sounds[BASS_DRUM] = Load_Wave_File((char *)"audio/bass_drum.wav");
   sounds[SNARE_DRUM] = Load_Wave_File((char *)"audio/snare_drum.wav");
   sounds[CLOSED_HIGH_HAT] = Load_Wave_File((char *)"audio/closed_high_hat.wav");
   sounds[OPEN_HIGH_HAT] = Load_Wave_File((char *)"audio/open_high_hat.wav");
   sounds[HIGH_TOM] = Load_Wave_File((char *)"audio/high_tom.wav");
   sounds[LOW_TOM] = Load_Wave_File((char *)"audio/low_tom.wav");
   sounds[CRASH_CYMBAL] = Load_Wave_File((char *)"audio/crash_cymbal.wav");

   do {
      drawGL();
      
      // Swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
   while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0 );

   // Close OpenGL window and terminate GLFW
   glfwTerminate();
   
   cleanupAudio();
   for (int s = 0; s < NUM_SOUNDS; ++s) {
      free(sounds[s].data);
   }

	return 0;
}
