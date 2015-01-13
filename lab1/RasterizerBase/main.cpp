/*
  CPE 471 Lab 1 
  Base code for Rasterizer
  Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "types.h"

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point a;
  Point b;
  Point c;
} Triangle;

typedef struct {
  int minX;
  int minY;
  int maxX;
  int maxY;
} BoundingBox;

int main(void) {

  // make a color
  color_t clr;

  clr.r = 0.5;
  clr.g = 0.5;
  clr.b = 0.9;

  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);


  Triangle t;

  printf("Enter 3 coordinates\nX1> ");
  scanf("%d", &t.a.x);
  printf("Y1> ");
  scanf("%d", &t.a.y);
  printf("X2> ");
  scanf("%d", &t.b.x);
  printf("Y2> ");
  scanf("%d", &t.b.y);
  printf("X3> ");
  scanf("%d", &t.c.x);
  printf("Y3> ");
  scanf("%d", &t.c.y);

  printf("You entered 3 points || (%d, %d) (%d, %d) (%d, %d)\n", t.a.x, t.a.y, t.b.x, t.b.y, t.c.x, t.c.y);

  printf("Computing bounding box...\n");

  BoundingBox box;

  int minX = 640;
  if (t.a.x < minX)
    minX = t.a.x;
  if (t.b.x < minX)
    minX = t.b.x;
  if (t.c.x < minX)
    minX = t.c.x;
  box.minX = minX;

  int minY = 480;
  if (t.a.y < minY)
    minY = t.a.y;
  if (t.b.y < minY)
    minY = t.b.y;
  if (t.c.y < minY)
    minY = t.c.y;
  box.minY = minY;

  int maxX = 0;
  if (t.a.x > maxX)
    maxX = t.a.x;
  if (t.b.x > maxX)
    maxX = t.b.x;
  if (t.c.x > maxX)
    maxX = t.c.x;
  box.maxX = maxX;

  int maxY = 0;
  if (t.a.y > maxY)
    maxY = t.a.y;
  if (t.b.y > maxY)
    maxY = t.b.y;
  if (t.c.y > maxY)
    maxY = t.c.y;
  box.maxY = maxY;

  printf("Bounding box: (%d, %d) to (%d, %d)\n", box.minX, box.minY, box.maxX, box.maxY);


  // set a square to be the color above
  for (int i=box.minX; i < box.maxX; i++) {
    for (int j=box.minY; j < box.maxY; j++) {
      img.pixel(i, j, clr);
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}
