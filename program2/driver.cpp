// Standard Headers
#include <stdio.h>
#include <stdlib.h>

// GLEW
#include <GL/glew.h>

// GLFW
#include<glfw3.h>
GLFWwindow *window;

// GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

int g_width, g_height;

void window_callback(GLFWwindow *window, int width, int height) {
   g_width = width;
   g_height = height;

   glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
   // Initialize GLFW
   if ( !glfwInit() ) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return -1;
   }

   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

   g_width = 1024;
   g_height = 768;

   // Open a window and create the OpenGL context
   window = glfwCreateWindow(g_width, g_height, "Program 2A", NULL, NULL);
   if (window == NULL) {
      fprintf(stderr, "Failed to open GLFW window\n");
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   // Set the callback for when the window changes size
   glfwSetWindowSizeCallback(window, window_callback);

   // Initialize GLEW
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      glfwTerminate();
      return -1;
   }

   // Ensure we can capture the escape key being pressed
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

   // SET BACKGROUND
   glClearColor(0, 0, 0, 0);

   // Create and compile the GLSL program from the shaders
   GLuint programID = LoadShaders("P2VertexShader.vertexshader", "P2FragmentShader.fragmentshader");

   // Get a handle for the buffers
   GLuint vertexPosition_modelspaceID = glGetAttribLocation(programId, "vertexPosition_modelspace");

   // Get the handle for the vertexColor in the VertexShader
   GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");

   GLuint uWinScaleID = glGetUniformLocation(programID, "uWinScale");
   GLuint uWinSizeID = glGetUniformLocation(programID, "winSize");
   GLuint winCenterID = glGetUniformLocation(programID, "winCenter");

   static const GLfloat vertex_data[] = {
      // Enter points here
   };

   static const GLfloat color_data[] = {
      // Enter colors here
   };

   // SET UP THE POSITION BUFFER
   GLuint vertexbuffer;
   glGenBuffers(1, &vertexbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
   
   // SET UP THE COLOR BUFFER
   GLuint colorbuffer;
   glGenBuffers(1, &colorbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

   do {

      // Clear the screen
      glClear( GL_COLOR_BUFFER_BIT );

      // Use our shader
      glUseProgram(programID);
      
      // Scale for window size
      if (g_width > g_height) {
         glUniform2f(uWinScale, g_height/(float)g_width, 1.0);
      } else {
         glUniform2f(uWinScale, 1.0, g_width/(float)g_height);
      }
      
      glUniform2f(uWinSizeID, g_width, g_height);
      glUniform2f(winCenterID, g_width / 2.0, g_height / 2.0);

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


      // Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, 9); // 3 indices starting at 0 -> 1 triangle

      glDisableVertexAttribArray(vertexPosition_modelspaceID);

      // Swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();

   } // Check if the ESC key was pressed or the window was closed
   while ( glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

   // Cleanup
   glDeleteBuffers(1, &vertexbuffer);
   glDeleteProgram(programID);

   // CLose OpenGL window and terminate GLFW
   glfwTerminate();

   return 0;
}
