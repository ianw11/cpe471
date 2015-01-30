// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

int g_width = 750, g_height = 750;
float l_time = 0;
float l_time_delta = 0.003;
float radius = .2;
float p_radius;

int numPoints = 40;

void window_callback(GLFWwindow* window, int width, int height) {
   g_width = width;
   g_height = height;
   
   printf("Window size changed: %d, %d\n", width, height);
   
   glViewport(0, 0, width, height);
}

int worldToPixelsX(double x, int width, int height) {
   if (width >= height) {
      x *= ((double)width / height);
      
      return (width - 1.0) * ( (double)height / (2.0 * width)) * x + ((width - 1.0) / 2.0);
   } else {
      return ((width - 1.0) / 2.0) * x + ((width - 1.0) / 2.0);
   }
}

int worldToPixelsY(double y, int width, int height) {
   if (width >= height) {
      return ((height - 1.0) / 2.0) * y + ((height - 1.0) / 2.0);
   } else {
      y *= ((double)height / width);
      return (height - 1.0) * (width / (2.0 * height)) * y + ((height - 1.0) / 2.0);
   }
}

float worldToPixelsF(double w, int width, int height) {
   int lo = width < height ? width : height;
   return (((w + 1.0) / 2.0) * lo) - (lo / 2.0);
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow( g_width, g_height, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ) {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
   glfwSetWindowSizeCallback(window, window_callback);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
   // We will use this programID to add data later
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
   
   // Gets the handle for the vertexColor in the VertexShader
   GLuint vertexColor = glGetAttribLocation(programID, "vertexColor");
   
   GLuint uWinScale = glGetUniformLocation(programID, "uWinScale");
   
   GLuint uWinSizeID = glGetUniformLocation(programID, "winSize");
   GLuint v_winSizeID = glGetUniformLocation(programID, "v_winSize");
   
   GLuint timeID = glGetUniformLocation(programID, "time");
   GLuint w_radiusID = glGetUniformLocation(programID, "radius");
   GLuint p_radiusID = glGetUniformLocation(programID, "p_radius");
   
   // Get a handle to the background positions
   GLuint backgroundID = glGetAttribLocation(programID, "background");
   GLuint isBackgroundID = glGetUniformLocation(programID, "isBackground");
   
   /* Create the random points */
   GLfloat vertex_buffer_data[numPoints*3];
   srand(0);
   for (int i = 0; i < numPoints * 3; ++i) {
      // Creates a number between 0 and 1
      float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      
      vertex_buffer_data[i] = (random * 2.0) - 1.0;
   }
   
   /* Create and set the color buffer */
   GLfloat color_buffer[numPoints * 3];
   for (int i = 0; i < numPoints * 3; i += 3) {
      color_buffer[i] = 2.0 / 255.0;
      color_buffer[i + 1] = 178.0 / 255.0;
      color_buffer[i + 2] = 168.0 / 255.0;
   }
   
   /* Create the background polygons */
   GLfloat background_buffer[] = {
      -1.0f, -1.0f, 0.0f,
       1.0f,  1.0f, 0.0f,
      -1.0f,  1.0f, 0.0f,
      
       1.0f,  1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f
   };
   
   /* Convert world to pixels for the radius we want */
   p_radius = worldToPixelsF(radius, g_width, g_height);
   

   /*
	static const GLfloat g_vertex_buffer_data[] = { 
		-0.8f, -0.9f, 0.0f,
		 0.8f, -0.9f, 0.0f,
		 0.0f,  0.9f, 0.0f,
      
      -0.9f,  0.9f, 0.0f,
      -0.9f, -0.9f, 0.0f,
      -0.1f,  0.9f, 0.0f,
      
       0.1f,  0.9f, 0.0f,
       0.9f, -0.9f, 0.0f,
       0.9f,  0.9f, 0.0f
	};
   
   static const GLfloat g_color_buffer_data[] = {
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      
      1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f,
      0.0f, 0.0f, 0.0f,
      
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f
   };
    */
   

   // SET UP THE POSITION BUFFER
	GLuint vertexbuffer;                                                                            // Declare a handle to the vertex buffer
	glGenBuffers(1, &vertexbuffer);                                                                 // GenBuffer(?)
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);                                                    // Bind local vertexbuffer handle to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);  // Buffer/Send the data in local vertex_buffer_data
   
   // SET UP THE COLOR BUFFER
   GLuint colorbuffer;
   glGenBuffers(1, &colorbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);
   
   // SET UP THE BACKGROUND BUFFER
   GLuint backgroundbuffer;
   glGenBuffers(1, &backgroundbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, backgroundbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(background_buffer), background_buffer, GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glBlendEquation(GL_FUNC_ADD);

		// Use our shaders
		glUseProgram(programID);
      
      // Scale for window size
      if (g_width > g_height) {
         glUniform2f(uWinScale, g_height/(float)g_width, 1.0);
      } else {
         glUniform2f(uWinScale, 1.0, g_width/(float)g_height);
      }
      
      // Send over size of the window to each shader
      glUniform2f(uWinSizeID, g_width, g_height);
      glUniform2f(v_winSizeID, g_width, g_height);
      
      /* Send and update time */
      glUniform1f(timeID, l_time);
      l_time += l_time_delta;
      
      /* Send radius */
      glUniform1f(w_radiusID, radius);
      glUniform1f(p_radiusID, p_radius);
      
      
      
      
      
      // DRAW BACKGROUND BEFORE ANYTHING ELSE
      glEnableVertexAttribArray(backgroundID);
      glBindBuffer(GL_ARRAY_BUFFER, backgroundbuffer);
      glVertexAttribPointer(
         backgroundID,
         3,
         GL_FLOAT,
         GL_FALSE,
         0,
         (void *)0
      );
      
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
      
      // 2ND ATTRIBUTE BUFFER : COLORS
      glEnableVertexAttribArray(vertexColor);
      glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
      glVertexAttribPointer(
         vertexColor,                // attribute, no reason but must match something
         3,                // size
         GL_FLOAT,         // type
         GL_FALSE,         // nomalized?
         0,                // stride
         (void*)0          // array
      );
      
      
      
      // Turn on background
      glUniform1i(isBackgroundID, 1);
      
      // Draw the triangles !
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glDisableVertexAttribArray(backgroundID);
      
      // Turn off background
      glUniform1i(isBackgroundID, 0);

      // Draw points
      glPointSize(25);
      glDrawArrays(GL_POINTS, 0, numPoints);
      
		glDisableVertexAttribArray(vertexPosition_modelspaceID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

