#pragma once

#include "math.h"
//#include "2dframebuf.hpp"
#include "tgaimage.h"
#include "algebra.h"

int draw_progress(unsigned char * data)
{
  /*  char r, g, b;
  r = g = b = 255;
  for (int i = 0; i < iloopy; i++)
  {
  int x = 10+i;
  fbuf2D.setPixel(data, x, 64/2-1, r, g, b);
  fbuf2D.setPixel(data, x, 64 / 2, r, g, b);
  fbuf2D.setPixel(data, x, 64 / 2 + 1, r, g, b);
  }
  */  return true;
}

int draw_arrow(unsigned char * data)
{
  /*  char r, g, b;

  for (int i = 0; i < 64; i++)
  {
  r = ((i + 1) % 3) * 255;
  g = (i % 3) * 255;
  b = ((i - 1) % 3) * 255;
  fbuf2D.setPixel(data,                i, (iloopy + i) % 64, r, g, b);  //   "\"   left part of arrow
  fbuf2D.setPixel(data, (2 * 64 - 2) - i, (iloopy + i) % 64, r, g, b);  //   "/"  right part of arrow
  }
  */  return true;
}

//void Bresenham(FrameBuf2D * fbuf, int x0, int y0, int x1, int y1, const glm::vec3 col, unsigned char * data) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
void bresenham(TGAImage & img, int x0, int y0, const int x1, const int y1, const TGAColor col = TGAColor(255, 255, 255, 255)) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2; // error value e_xy

    while (true)
    {
//        fbuf->setPixel(data,x0,y0,255,255,255);
        img.set(x0, y0, col);

        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; } // e_xy+e_x > 0
        if (e2 < dx) { err += dx; y0 += sy; } // e_xy+e_y < 0
    }
}
void bresenham(TGAImage & img, vec2 p1, vec2 p2, TGAColor col) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
{
  bresenham(img, p1.x, p1.y, p2.x, p2.y, col);
}
/*
bool bresenham_step(TGAImage & img, int & x0, int & y0, const int x1, const int y1, int & e2, int err, const int dx, const int dy, const int sx, const int sy, const TGAColor col = TGAColor(255, 255, 255, 255)) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
{
  //        fbuf->setPixel(data,x0,y0,255,255,255);
  img.set(x0, y0, col);

  if (x0 == x1 && y0 == y1) return false;
  e2 = 2 * err;
  if (e2 > dy) { err += dy; x0 += sx; } // e_xy+e_x > 0
  if (e2 < dx) { err += dx; y0 += sy; } // e_xy+e_y < 0
  return true;
}*/
void bresenham_arr(TGAImage & img, int x0, int y0, const int x1, const int y1, int * xarr, const TGAColor col = TGAColor(255, 255, 255, 255)) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
{
  int dx = abs(x1 - x0), sx = x0<x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0<y1 ? 1 : -1;
  int err = dx + dy, e2; // error value e_xy

  while (true)
  {
    //        fbuf->setPixel(data,x0,y0,255,255,255);
    img.set(x0, y0, col);
    xarr[y0] = x0; // <-- wichtig! x-pos merken!

    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 > dy) { err += dy; x0 += sx; } // e_xy+e_x > 0
    if (e2 < dx) { err += dx; y0 += sy; } // e_xy+e_y < 0
  }
}
void triangle_filled(TGAImage & img, vec2 p0, vec2 p1, vec2 p2, TGAColor col = TGAColor(255, 255, 255, 255))
{
  // sortiere nach y
  vec2 top, middle, bottom,tmp;
  if (p1.y < p0.y)
  {
    top = p1;
    middle = p0;
  }
  else
  {
    top = p0;
    middle = p1;
  }
  if (p2.y < middle.y)
  {
    if (p2.y < top.y)
    {
      bottom = middle;
      middle = top;
      top = p2;
    }
    else
    {
      bottom = middle;
      middle = p2;
    }
  }
  else
  {
    bottom = p2;
  }

/* tut's nicht, da Linien mit unterschiedlich schneller "geschwindigkeit" gesetzt werden
  // von top nach middle
  if (middle.x < bottom.x)
  {
    // bresenham init
    int x0[2];
    int y0[2];
    int x1[2];
    int y1[2];
    int dx[2];
    int dy[2];
    int err[2];
    int sx[2];
    int sy[2];
    int e2[2]; // error value e_xy
    x0[0] = top.x;
    y0[0] = top.y;
    x1[0] = middle.x;
    y1[0] = middle.y;
    dx[0] = abs(x1[0] - x0[0]);
    dy[0] = -abs(y1[0] - y0[0]);
    sx[0] = x0[0] < x1[0] ? 1 : -1;
    sy[0] = y0[0] < y1[0] ? 1 : -1;
    err[0] = dx[0] + dy[0];

    x0[1] = top.x;
    y0[1] = top.y;
    x1[1] = bottom.x;
    y1[1] = bottom.y;
    dx[1] = abs(x1[1] - x0[1]);
    dy[1] = -abs(y1[1] - y0[1]);
    sx[1] = x0[1] < x1[1] ? 1 : -1;
    sy[1] = y0[1] < y1[1] ? 1 : -1;
    err[1] = dx[1] + dy[1];

    bool bleft = bresenham_step(img, x0[0], y0[0], x1[0], y1[0], e2[0], err[0], dx[0], dy[0], sx[0], sy[0]);
    bool bright = bresenham_step(img, x0[1], y0[1], x1[1], y1[1], e2[1], err[1], dx[1], dy[1], sx[1], sy[1]);
//    bresenham(img, x0[0], y0[0], x0[1], y0[1]);
    while (bleft && bright)
    {
      bleft = bresenham_step(img, x0[0], y0[0], x1[0], y1[0], e2[0], err[0], dx[0], dy[0], sx[0], sy[0]);
      bright = bresenham_step(img, x0[1], y0[1], x1[1], y1[1], e2[1], err[1], dx[1], dy[1], sx[1], sy[1]);
//      bresenham(img, x0[0], y0[0], x0[1], y0[1]);
    }
  }
  else
  {
    // top --> bottom
  }
  // von middle nach bottom

  */
  int xarr[1000]; // 2do: vector instead of fixed array (depends on screen dimensions)
  int xarr2[1000];
  bresenham_arr(img, top.x, top.y, middle.x, middle.y, xarr,col);
  bresenham_arr(img, top.x, top.y, bottom.x, bottom.y,  xarr2,col);
  bresenham_arr(img, middle.x, middle.y, bottom.x, bottom.y, xarr,col);
  for (int y = top.y; y < bottom.y; y++)
  {
    bresenham(img, xarr[y], y, xarr2[y], y,col); // man kann sogar noch einfacher mit x-Schleife schreiben
  }
}

/*
void bresenham_circle(FrameBuf2D * fbuf, int x0, int y0, int radius, const glm::vec3 col, unsigned char * data) // https://de.wikipedia.org/wiki/Bresenham-Algorithmus
{
,    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    fbuf->setPixel(data,x0, y0 + radius,col.r,col.g,col.b);
    fbuf->setPixel(data,x0, y0 - radius,col.r,col.g,col.b);
    fbuf->setPixel(data,x0 + radius, y0,col.r,col.g,col.b);
    fbuf->setPixel(data,x0 - radius, y0,col.r,col.g,col.b);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        fbuf->setPixel(data,x0 + x, y0 + y,col.r,col.g,col.b); // oct. 6
        fbuf->setPixel(data,x0 - x, y0 + y,col.r,col.g,col.b); // 2
        fbuf->setPixel(data,x0 + x, y0 - y,col.r,col.g,col.b); // 1
        fbuf->setPixel(data,x0 - x, y0 - y,col.r,col.g,col.b); // 5
        fbuf->setPixel(data,x0 + y, y0 + x,col.r,col.g,col.b); // 7
        fbuf->setPixel(data,x0 - y, y0 + x,col.r,col.g,col.b); // 3
        fbuf->setPixel(data,x0 + y, y0 - x,col.r,col.g,col.b); // 4
        fbuf->setPixel(data,x0 - y, y0 - x,col.r,col.g,col.b); // 8
    }
}
*/
