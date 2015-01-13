/*
  CPE 471 Lab 1 
  Base code for Rasterizer
  Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Image.h"
#include "types.h"

float calculateArea (Vertex a, Vertex b, Vertex c) {
    return ((b.p.x - a.p.x) * (c.p.y - a.p.y)) - ((c.p.x - a.p.x) * (b.p.y - a.p.y));
}

int main(void) {

  // make a color
  color_t clr1;
//56	142	142
  clr1.r = 56.0/255;
  clr1.g = 142.0/255;
  clr1.b = 200.0/255;

    // make a color
    color_t clr2;
    //56	142	142
    clr2.r = 200.0/255;
    clr2.g = 56.0/255;
    clr2.b = 142.0/255;
    
    // make a color
    color_t clr3;
    //56	142	142
    clr3.r = 56.0/255;
    clr3.g = 200.0/255;
    clr3.b = 10.0/255;
    
    Triangle t;
    Box myBox;
    Vertex a,b,c;

    myBox.min.x = INT_MAX;
    myBox.min.y = INT_MAX;
    myBox.max.x = INT_MIN;
    myBox.max.y = INT_MIN;

    for (int i = 0; i < 3; i++) {
        printf("Enter a point: ");
        scanf("%d %d", &t.points[i].x, &t.points[i].y);
        
        if (t.points[i].x < myBox.min.x) {
            myBox.min.x = t.points[i].x;
        }
        
        if (t.points[i].y < myBox.min.y) {
            myBox.min.y = t.points[i].y;
        }
        
        if (t.points[i].x > myBox.max.x) {
            myBox.max.x = t.points[i].x;
        }
        
        if (t.points[i].y > myBox.max.y) {
            myBox.max.y = t.points[i].y;
        }
    }
    
    a.p = t.points[0];
    a.c = clr1;
    b.p = t.points[1];
    b.c = clr2;
    c.p = t.points[2];
    c.c = clr3;
    
    float triangleArea = calculateArea(a,b,c);
    
  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);

  // set a square to be the color above
  for (int i=myBox.min.x; i < myBox.max.x; i++) {
    for (int j=myBox.min.y; j < myBox.max.y; j++) {
        
        float areaC = ((b.p.x - a.p.x) * (j - a.p.y)) - ((b.p.y - a.p.y) * (i - a.p.x));
        float areaB = ((a.p.x - c.p.x) * (j - c.p.y)) - ((a.p.y - c.p.y) * (i - c.p.x));
        float gamma = areaC / triangleArea;
        float beta = areaB / triangleArea;
        float alpha = 1 - beta - gamma;
        
        
        
        if (gamma >= 0 && beta >= 0 && alpha >= 0) {
            
            color_t clr;
            clr.r = alpha * clr1.r + beta * clr2.r + gamma * clr3.r;
            clr.g = alpha * clr1.g + beta * clr2.g + gamma * clr3.g;
            clr.b = alpha * clr1.b + beta * clr2.b + gamma * clr3.b;
            img.pixel(i, j, clr);
        }
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}
