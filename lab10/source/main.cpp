//
// Base code for textures - creates a cube and ground plane that are textured
// with two different textures - ZJ Wood
//

#include <stdio.h>
#include <stdlib.h>
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

/*data structure for the image used for  texture mapping */
typedef struct Image {
  unsigned long sizeX;
  unsigned long sizeY;
  char *data;
} Image;

Image *TextureImage;

typedef struct RGB {
  GLubyte r;
  GLubyte g; 
  GLubyte b;
} RGB;

RGB myimage[64][64];
RGB* g_pixel;

//forward declaration of image loading and texture set-up code
int ImageLoad(char *filename, Image *image);
GLvoid LoadTexture(char* image_file, int tex_id);

GLFWwindow* window;
using namespace std;

vector<tinyobj::shape_t> shapes;
vector<tinyobj::material_t> materials;

//Handles to the shader data
GLuint prog;
GLuint posBufObj = 0;
GLuint norBufObj = 0;
GLuint indBufObj = 0;
//Handles to the shader data
GLint h_uTexUnit;
GLint h_uTexUnit2;
GLint h_aPosition;
GLint h_aNormal;
GLint h_aTexCoord;
GLint h_uModelMatrix;
GLint h_uViewMatrix;
GLint h_uProjMatrix;
GLuint CubeBuffObj, CIndxBuffObj, TexBuffObj, GrndBuffObj, GIndxBuffObj, GrndTexBuffObj;
static float g_width, g_height;
float theta;
int g_CiboLen, g_GiboLen;
float g_angle = 0;
int g_mat_id =0;
glm::vec3 g_trans(0, 0, -8);

GLint h_isGround;

inline void safe_glUniformMatrix4fv(const GLint handle, const GLfloat data[]) {
  if (handle >= 0)
    glUniformMatrix4fv(handle, 1, GL_FALSE, data);
}

/* projection matrix */
void SetProjectionMatrix() {
  glm::mat4 Projection = glm::perspective(45.0f, (float)g_width/g_height, 0.1f, 100.f);
  safe_glUniformMatrix4fv(h_uProjMatrix, glm::value_ptr(Projection));
}

/* camera controls  - slightly wacky - always look where model moved to - fix 
before you copy this into another file
*/
void SetView() {
  glm::mat4 camera = glm::lookAt( vec3(0, 3, 3), g_trans, vec3(0, 1,0));
  safe_glUniformMatrix4fv(h_uViewMatrix, glm::value_ptr(camera));
}

/* model transforms */
void SetModel() {
  glm::mat4 Trans = glm::translate( glm::mat4(1.0f), g_trans);
  glm::mat4 RotateY = glm::rotate( glm::mat4(1.0f), g_angle, glm::vec3(0.0f, 1, 0));
  glm::mat4 com = Trans*RotateY;
  safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(com));
}

void initGL()
{
	// Set the background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable Z-buffer test
	glEnable(GL_DEPTH_TEST);
	
    /* texture specific settings */
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


static void initGround() {

   float g_groundSize = 20;
   float g_groundY = -1.5;

  // A x-z plane at y = g_groundY of dimension [-g_groundSize, g_groundSize]^2
    float GrndPos[] = {
    -g_groundSize, g_groundY, -g_groundSize,
    -g_groundSize, g_groundY,  g_groundSize,
     g_groundSize, g_groundY,  g_groundSize,
     g_groundSize, g_groundY, -g_groundSize
    };

    float GrndNorm[] = {
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0,
     0, 1, 0
    };


  static GLfloat GrndTex[] = {
      0, 0, // back
      0, 1,
      1, 1,
      1, 0 };

    unsigned short idx[] = {0, 1, 2, 0, 2, 3};

    g_GiboLen = 6;
    glGenBuffers(1, &GrndBuffObj);
    glBindBuffer(GL_ARRAY_BUFFER, GrndBuffObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GrndPos), GrndPos, GL_STATIC_DRAW);

    glGenBuffers(1, &GrndTexBuffObj);
    glBindBuffer(GL_ARRAY_BUFFER, GrndTexBuffObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GrndTex), GrndTex, GL_STATIC_DRAW);

    glGenBuffers(1, &GIndxBuffObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIndxBuffObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

}

/* intialize the cube data */
/* Evil lurks here - watch the order of the faces - one is reversed */
static void initCube() {

  float CubePos[] = {
    -1.5, -1.5, -1.5, //back face 5 verts :0 - clockwise 
    -1.5, 1.5, -1.5,
    1.5, 1.5, -1.5,
    1.5, -1.5, -1.5,
    1.5, -1.5, 1.5, //right face 5 verts :4
    1.5, 1.5, 1.5,
    1.5, 1.5, -1.5,
    1.5, -1.5, -1.5,
    -1.5, -1.5, 1.5, //front face 4 verts :8
    -1.5, 1.5, 1.5,
    1.5, 1.5, 1.5,
    1.5, -1.5, 1.5,
    -1.5, -1.5, -1.5, //left face 4 verts :12
    -1.5, 1.5, -1.5,
    -1.5, 1.5, 1.5,
    -1.5, -1.5, 1.5
  };

   static GLfloat CubeTex[] = {
      .75, 0, // back 
      .75, 1,
      .5, 1,
      .5, 0,
      .25, 0, //right 
      .25, 1,
      .5, 1,
      .5, 0,
      0, 0, //front 
      0, 1,
      .25, 1,
      .25, 0,
      .75, 0, // left 
      .75, 1,
      1, 1,
      1, 0
    }; 
   
    unsigned short idx[] = {0, 1, 2,  2, 3, 0,  4, 5, 6, 6, 7, 4,  8, 9, 10, 10, 11, 8,  12, 13, 14, 14, 15, 12};

    g_CiboLen = 24;
    glGenBuffers(1, &CubeBuffObj);
    glBindBuffer(GL_ARRAY_BUFFER, CubeBuffObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubePos), CubePos, GL_STATIC_DRAW);

    glGenBuffers(1, &CIndxBuffObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CIndxBuffObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

    glGenBuffers(1, &TexBuffObj);
    glBindBuffer(GL_ARRAY_BUFFER, TexBuffObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeTex), CubeTex, GL_STATIC_DRAW);

}

void initGeom() {
  initCube();
  initGround();
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
        /* get handles to attribute data */
   h_aPosition = GLSL::getAttribLocation(prog, "aPosition");
   h_aNormal = GLSL::getAttribLocation(prog, "aNormal");
   h_aTexCoord = GLSL::getAttribLocation(prog,  "aTexCoord");
   h_uTexUnit = GLSL::getUniformLocation(prog, "uTexUnit");
   h_uProjMatrix = GLSL::getUniformLocation(prog, "uProjMatrix");
   h_uViewMatrix = GLSL::getUniformLocation(prog, "uViewMatrix");
   h_uModelMatrix = GLSL::getUniformLocation(prog, "uModelMatrix");
   
   h_isGround = GLSL::getUniformLocation(prog, "isGround");
   	
	assert(glGetError() == GL_NO_ERROR);
	return true;
}


void drawGL()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    //Start our shader
    glUseProgram(prog);

    //Set up matrix transforms
    SetProjectionMatrix();
    SetView();
    SetModel();

    //set up the texture unit
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);

    glUniform1i(h_uTexUnit, 0);
    
    /* Draw cube */
    glBindTexture(GL_TEXTURE_2D, 0);
    GLSL::enableVertexAttribArray(h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, CubeBuffObj);
    glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLSL::enableVertexAttribArray(h_aTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, TexBuffObj);
    glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0); 
    
    // bind ibo
    glUniform1i(h_isGround, 0);
    // draw!
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CIndxBuffObj);
    glDrawElements(GL_TRIANGLES, g_CiboLen, GL_UNSIGNED_SHORT, 0);

    glDrawElements(GL_TRIANGLES, g_GiboLen, GL_UNSIGNED_SHORT, 0);

    GLSL::disableVertexAttribArray(h_aPosition);

   /* Draw ground */
   glUniform1i(h_isGround, 1);
    glBindTexture(GL_TEXTURE_2D, 1);
    GLSL::enableVertexAttribArray(h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, GrndBuffObj);
    glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLSL::enableVertexAttribArray(h_aTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, GrndTexBuffObj);
    glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // draw!
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GIndxBuffObj);
    glDrawElements(GL_TRIANGLES, g_GiboLen, GL_UNSIGNED_SHORT, 0);

    GLSL::disableVertexAttribArray(h_aPosition);
    GLSL::disableVertexAttribArray(h_aTexCoord);
    
   //Disable the shader
    glUseProgram(0);
    glDisable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
	assert(glGetError() == GL_NO_ERROR);
	
}

void reshapeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	g_width = w;
	g_height = h;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
      g_angle += 10;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
      g_angle -= 10;
}

int main(int argc, char **argv)
{

   // Initialise GLFW
   if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
   }

   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

   g_width = 1024;
   g_height = 768;
   // Open a window and create its OpenGL context
   window = glfwCreateWindow( g_width, g_height, "lab 10  - textures", NULL, NULL);
   if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   glfwSetKeyCallback(window, key_callback);


   // Initialize glad
   if (!gladLoadGL()) {
      fprintf(stderr, "Unable to initialize glad");
      glfwDestroyWindow(window);
      glfwTerminate();
      return 1;
   }

	initGL();
   initGeom();
	installShaders("tex_vert.glsl", "tex_frag.glsl");
   //load in the other image textures
   //You must have an openGL context in order to call these functions
   LoadTexture((char *)"earth1.bmp", 0);
   LoadTexture((char *)"cloud5.bmp", 1);

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



//routines to load in a bmp files - must be 2^nx2^m and a 24bit bmp
GLvoid LoadTexture(char* image_file, int texID) { 
  
  TextureImage = (Image *) malloc(sizeof(Image));
  if (TextureImage == NULL) {
    printf("Error allocating space for image");
    exit(1);
  }
  cout << "trying to load " << image_file << endl;
  if (!ImageLoad(image_file, TextureImage)) {
    exit(1);
  }  
  /*  2d texture, level of detail 0 (normal), 3 components (red, green, blue),            */
  /*  x size from image, y size from image,                                              */    
  /*  border 0 (normal), rgb color data, unsigned byte data, data  */ 
  glBindTexture(GL_TEXTURE_2D, texID);
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    TextureImage->sizeX, TextureImage->sizeY,
    0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); /*  cheap scaling when image bigger than texture */    
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); /*  cheap scaling when image smalled than texture*/
  
}


/* BMP file loader loads a 24-bit bmp file only */

/*
* getint and getshort are help functions to load the bitmap byte by byte
*/
static unsigned int getint(FILE *fp) {
  int c, c1, c2, c3;
  
  /*  get 4 bytes */ 
  c = getc(fp);  
  c1 = getc(fp);  
  c2 = getc(fp);  
  c3 = getc(fp);
  
  return ((unsigned int) c) +   
    (((unsigned int) c1) << 8) + 
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE *fp){
  int c, c1;
  
  /* get 2 bytes*/
  c = getc(fp);  
  c1 = getc(fp);
  
  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

/*  quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */

int ImageLoad(char *filename, Image *image) {
  FILE *file;
  unsigned long size;                 /*  size of the image in bytes. */
  unsigned long i;                    /*  standard counter. */
  unsigned short int planes;          /*  number of planes in image (must be 1)  */
  unsigned short int bpp;             /*  number of bits per pixel (must be 24) */
  char temp;                          /*  used to convert bgr to rgb color. */
  
  /*  make sure the file is there. */
  if ((file = fopen(filename, "rb"))==NULL) {
    printf("File Not Found : %s\n",filename);
    return 0;
  }
  
  /*  seek through the bmp header, up to the width height: */
  fseek(file, 18, SEEK_CUR);
  
  /*  No 100% errorchecking anymore!!! */
  
  /*  read the width */    image->sizeX = getint (file);
  
  /*  read the height */ 
  image->sizeY = getint (file);
  
  /*  calculate the size (assuming 24 bits or 3 bytes per pixel). */
  size = image->sizeX * image->sizeY * 3;
  
  /*  read the planes */    
  planes = getshort(file);
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    return 0;
  }
  
  /*  read the bpp */    
  bpp = getshort(file);
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return 0;
  }
  
  /*  seek past the rest of the bitmap header. */
  fseek(file, 24, SEEK_CUR);
  
  /*  read the data.  */
  image->data = (char *) malloc(size);
  if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0; 
  }
  
  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
  }
  
  for (i=0;i<size;i+=3) { /*  reverse all of the colors. (bgr -> rgb) */
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] = temp;
  }
  
  fclose(file); /* Close the file and release the filedes */
  
  /*  we're done. */
  return 1;
}





