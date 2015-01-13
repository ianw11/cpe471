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

std::vector<Vertex> turnVerticesTo2d(std::vector<float> vertices, int width, int height) {
   std::vector<Vertex> ret;
   
   float midWidth = (float)width / 2.0;
   float midHeight = (float)height / 2.0;
   
   for (size_t v = 0; v < vertices.size() / 3; v++) {
      float x = vertices[3 * v];
      float y = vertices[3 * v + 1];
      float z = vertices[3 * v + 2];
      
      Vertex vertex;
      vertex.x = x * midWidth + midWidth;
      vertex.y = y * midHeight + midHeight;
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


/*
 * Main function
 */

int main(int argc, const char* argv[]) {
   bool DEBUG = true;
   std::string inputfile;
   
   if (argc != 2) {
      std::cout << "Program requires a file as an argument" << std::endl;
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
	
	int width, height;
	
	std::cout << "Enter width: ";
	scanf("%d", &width);
	std::cout << "Enter height: ";
	scanf("%d", &height);
	
	// make a color
	color_t clr;
	clr.r = 0.5;
	clr.g = 0.5;
	clr.b = 0.9;
	
 	// make a 400x400 image (allocates buffer on the heap)
	Image img(width, height);

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
         
         std::vector<Vertex> vertices = turnVerticesTo2d(currShape.mesh.positions, width, height);
         
         std::vector<Triangle> triangles = assignVerticesToFaces(vertices, currShape.mesh.indices);
         
         for (int tri_num = 0; tri_num < triangles.size(); ++tri_num) {
            Triangle currTri = triangles[tri_num];
            for (int i = currTri.bounds.minX; i < currTri.bounds.maxX; ++i) {
               for (int j = currTri.bounds.minY; j < currTri.bounds.maxY; ++j) {
                  img.pixel(i, j, clr);
               }
            }
         }
         
      }
	}

	
	/*
	// set a square to be the color above
	for (int i=50; i < 100; i++) {
		for (int j=50; j < 100; j++) {
			img.pixel(i, j, clr);
		}
	}
	*/
	
	// write the targa file to disk
	// true to scale to max color, false to clamp to 1.0
	img.WriteTga((char *)"awesome.tga", true); 
}
