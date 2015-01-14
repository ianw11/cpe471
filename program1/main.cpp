#include <iostream>
#include <stdio.h>
#include <cassert>
#include <cfloat>
#include "tiny_obj_loader.h"
#include "Image.h"

/*
 * Struct definitions
 */
 
typedef struct {
   float x, y, z;
} Vertex;

typedef struct {
   float minX, maxX, minY, maxY;
} BoundingBox;

typedef struct {
   Vertex vrtx_a, vrtx_b, vrtx_c;
   color_t clr_a, clr_b, clr_c;
   BoundingBox bounds;
   float area;
} Triangle;


/*
 * Helper Functions
 */

BoundingBox prepareBoundingBox(BoundingBox b) {
   b.minX = FLT_MAX;
   b.maxX = FLT_MIN;
   b.minY = FLT_MAX;
   b.maxY = FLT_MIN;
   
   return b;
}

void updateBoundingBox(Triangle *tri) {
   if (tri->vrtx_a.x < tri->bounds.minX)
      tri->bounds.minX = tri->vrtx_a.x;
   if (tri->vrtx_b.x < tri->bounds.minX)
      tri->bounds.minX = tri->vrtx_b.x;
   if (tri->vrtx_c.x < tri->bounds.minX)
      tri->bounds.minX = tri->vrtx_c.x;
   
   if (tri->vrtx_a.x > tri->bounds.maxX)
      tri->bounds.maxX = tri->vrtx_a.x;
   if (tri->vrtx_b.x > tri->bounds.maxX)
      tri->bounds.maxX = tri->vrtx_b.x;
   if (tri->vrtx_c.x > tri->bounds.maxX)
      tri->bounds.maxX = tri->vrtx_c.x;
   
   
   if (tri->vrtx_a.y < tri->bounds.minY)
      tri->bounds.minY = tri->vrtx_a.y;
   if (tri->vrtx_b.y < tri->bounds.minY)
      tri->bounds.minY = tri->vrtx_b.y;
   if (tri->vrtx_c.y < tri->bounds.minY)
      tri->bounds.minY = tri->vrtx_c.y;
      
   if (tri->vrtx_a.y > tri->bounds.maxY)
      tri->bounds.maxY = tri->vrtx_a.y;
   if (tri->vrtx_b.y > tri->bounds.maxY)
      tri->bounds.maxY = tri->vrtx_b.y;
   if (tri->vrtx_c.y > tri->bounds.maxY)
      tri->bounds.maxY = tri->vrtx_c.y;
}

float calculateArea (Vertex a, Vertex b, Vertex c) {
    return ((b.x - a.x) * (c.y - a.y)) - ((c.x - a.x) * (b.y - a.y));
}

float **makeArray(int width, int height) {
   float **arr = new float *[width];
   for (int i = 0; i < width; ++i) {
      arr[i] = new float[height];
   }
   
   return arr;
}

void deleteArray  (float **arr, int width, int height) {
   for (int i = 0; i < width; ++i) {
      delete [] arr[i];
   }
   delete [] arr;
}


int worldToPixelsX(float x, int width, int height) {
   if (width >= height) {
      x *= ((float)width / height);
      
      float d = (width - 1.0) / 2.0;
      float c = (width - 1.0) * ( (float)height / (2.0 * width));
      return c * x + d;
   } else {
      return ((width - 1.0) / 2.0) * x + ((width - 1.0) / 2.0);
   }  
}

int worldToPixelsY(float y, int width, int height) {
   if (width >= height) {
      return ((height - 1.0) / 2.0) * y + ((height - 1.0) / 2.0);
   } else {
      y *= ((float)height / width);
      return (height - 1.0) * (width / (2.0 * height)) * y + ((height - 1.0) / 2.0);
   }
}

std::vector<Vertex> turnVerticesTo2d(std::vector<float> vertices, int width, int height) {
   std::vector<Vertex> ret;
   
   for (size_t v = 0; v < vertices.size() / 3; v++) {
      float x = vertices[3 * v];
      float y = vertices[3 * v + 1];
      float z = vertices[3 * v + 2];
      
      Vertex vertex;
      vertex.x = worldToPixelsX(x, width, height);
      vertex.y = worldToPixelsY(y, width, height);
      vertex.z = z;
      
      //printf("New vertices: %f, %f, %f\n", vertex.x, vertex.y, vertex.z);
      
      ret.push_back(vertex);
   }
   
   return ret;
}

std::vector<Triangle> assignVerticesToFaces(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
   std::vector<Triangle> triangles;

   for (int i = 0; i < indices.size() / 3; ++i) {
      Triangle tri;
      tri.bounds = prepareBoundingBox(tri.bounds);
      
      tri.vrtx_a = vertices[indices[i * 3]];
      tri.vrtx_b = vertices[indices[i * 3 + 1]];
      tri.vrtx_c = vertices[indices[i * 3 + 2]];
      
      updateBoundingBox(&tri);
      
      tri.area = calculateArea(tri.vrtx_a, tri.vrtx_b, tri.vrtx_c);
      
      triangles.push_back(tri);
   }
   
   return triangles;
}


float computeZDepth(float d) {
   return 127.0 * d + 127.0;
}

bool rasterize(Triangle tri, int i, int j, float **depth) {
   float areaC = ((tri.vrtx_b.x - tri.vrtx_a.x) * (j - tri.vrtx_a.y)) - ((tri.vrtx_b.y - tri.vrtx_a.y) * (i - tri.vrtx_a.x));
   float areaB = ((tri.vrtx_a.x - tri.vrtx_c.x) * (j - tri.vrtx_c.y)) - ((tri.vrtx_a.y - tri.vrtx_c.y) * (i - tri.vrtx_c.x));
   float gamma = areaC / tri.area;
   float beta = areaB / tri.area;
   float alpha = 1 - beta - gamma;
   
   if (alpha >= 0 && beta >= 0 && gamma >= 0) {
      float d = computeZDepth(alpha * tri.vrtx_a.z + beta * tri.vrtx_b.z + gamma * tri.vrtx_c.z);
      if (depth[i][j] < d && d < 256) {
            depth[i][j] = d;
      }
      
      return true;
   }
   
   return false;
}

color_t computeColor(int i, int j, int width, float **depth, int method) {
   color_t clr;
   clr.r = 0;
   clr.g = 0;
   clr.b = 0;
   
   if (isinf(depth[i][j]))
      return clr;
   
   if (method == 2) {
      clr.r = (i / (float) width);
      clr.g = clr.r;
      clr.b = 1 - clr.r;
   } else {
      clr.r = depth[i][j];
      clr.g = 0;
      clr.b = 0;
   }
   
   return clr;
}



/*
 * Main function
 */

int main(int argc, const char* argv[]) {
   bool DEBUG = false;
   std::string inputfile;
   
   if (argc != 2) {
      std::cout << "Program requires a file as an argument" << std::endl;
      std::cout << "Running world to pixel tests instead" << std:: endl;
      
      std::cout << "Enter an x-coordinate: ";
      float x;
      scanf("%f", &x);
      
      std::cout << "Enter a width: ";
      int width;
      scanf("%d", &width);
      
      std::cout << "Enter a height: ";
      int height;
      scanf("%d", &height);
      
      std::cout << "Testing with x: " << x << " width: " << width << " height: " << height << std::endl;
      
      int pixel = worldToPixelsX(x, width, height);
      
      std::cout << "The result is: " << pixel << std::endl;
      
      exit(1);
   }
   
   inputfile = argv[1];
   std::cout << "Opening file " << inputfile << std::endl;
	
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str());

	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}
	
	int width, height, method;
	
	std::cout << "Enter width: ";
	scanf("%d", &width);
	std::cout << "Enter height: ";
	scanf("%d", &height);
	std::cout << "Enter method of coloring (1 for depth, 2 for x-axis): ";
	scanf("%d", &method);
	
 	// make a 400x400 image (allocates buffer on the heap)
	Image img(width, height);
	
	if (width < height) {
	   height = width;
	} else {
	   width = height;
	}
	
	float **depth = makeArray(width, height);
	for (int i = 0; i < width; ++i) {
	   for (int j = 0; j < height; ++j) {
	      depth[i][j] = -1 * std::numeric_limits<float>::infinity();
	   }
	}

   if (DEBUG) {
      std::cout << "# of shapes: " << shapes.size() << std::endl;
      for (size_t i = 0; i < shapes.size(); i++) {
         tinyobj::shape_t currShape = shapes[i];
         
         printf("Size of shape[%ld].indices: %ld\n", i, currShape.mesh.indices.size());
         
         assert((currShape.mesh.indices.size() % 3) == 0);
   
         for (size_t f = 0; f < currShape.mesh.indices.size() / 3; f++) {
            printf("  triangle[%ld] = %d, %d, %d\n", f, currShape.mesh.indices[3*f+0], currShape.mesh.indices[3*f+1], currShape.mesh.indices[3*f+2]);
         }

         printf("shape[%ld].vertices: %ld\n", i, currShape.mesh.positions.size());
         
         assert((currShape.mesh.positions.size() % 3) == 0);
      
         for (size_t v = 0; v < currShape.mesh.positions.size() / 3; v++) {
            printf("  vertex[%ld] = (%f, %f, %f)\n", v,
               currShape.mesh.positions[3*v+0],
               currShape.mesh.positions[3*v+1],
               currShape.mesh.positions[3*v+2]);
         }
      }
   }
   
      
   for (size_t i = 0; i < shapes.size(); i++) {
      tinyobj::shape_t currShape = shapes[i];

      assert((currShape.mesh.indices.size() % 3) == 0);
      assert((currShape.mesh.positions.size() % 3) == 0);
      
      std::vector<Vertex> vertices = turnVerticesTo2d(currShape.mesh.positions, width, height);
      std::vector<Triangle> triangles = assignVerticesToFaces(vertices, currShape.mesh.indices);
      
      for (int tri_num = 0; tri_num < triangles.size(); ++tri_num) {
         Triangle currTri = triangles[tri_num];
         
         for (int i = currTri.bounds.minX; i < currTri.bounds.maxX; ++i) {
            for (int j = currTri.bounds.minY; j < currTri.bounds.maxY; ++j) {
               
               rasterize(currTri, i, j, depth);
               
            }
         }
      }
	}
	
	for (int i = 0; i < width; ++i) {
	   for (int j = 0; j < height; ++j) {
	      img.pixel(i, j, computeColor(i, j, width, depth, method));
	   }
	}
	
	deleteArray(depth, width, height);
	
	// write the targa file to disk
	// true to scale to max color, false to clamp to 1.0
	img.WriteTga((char *)"awesome.tga", true); 
}
