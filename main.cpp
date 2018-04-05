/*
  RENDY - Software Renderer
  2018 march

  https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm

*/

#include "tgaimage.h"
#include "draw_lib.hpp"
#include "mdl_wavefront.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0, 255, 0, 255);

const zbuffer zbuf;

void lesson1(TGAImage & image) // draw wireframe
{
  std::vector <obj::CPart> v_parts;
  obj::CLoader_OBJ objload;

  objload.loadOBJParts("african_head.obj", v_parts);

  std::cout << v_parts.size() << std::endl;
  for (int i = 0; i < v_parts.size(); i++)
  {
    for (int j = 0; j < v_parts[i].vertices.size(); j += 3)
    {
      float x[3];
      float y[3];
      float z[3];
      float f = 400.0f;
      float xy_center = 500.0f;
      x[0] = xy_center + v_parts[i].vertices[j].x * f;
      y[0] = xy_center + v_parts[i].vertices[j].z * f;
      x[1] = xy_center + v_parts[i].vertices[j + 1].x * f;
      y[1] = xy_center + v_parts[i].vertices[j + 1].z * f;
      x[2] = xy_center + v_parts[i].vertices[j + 2].x * f;
      y[2] = xy_center + v_parts[i].vertices[j + 2].z * f;
      bresenham(image, x[0], y[0], x[1], y[1]);
      bresenham(image, x[1], y[1], x[2], y[2]);
      bresenham(image, x[2], y[2], x[0], y[0]);
    }
  }
}

void triangle(vec2 t0, vec2 t1, vec2 t2, TGAImage &image, TGAColor color)
{
  bresenham(image, t0, t1, color);
  bresenham(image, t1, t2, color);
  bresenham(image, t2, t0, color);
}

void lesson2(TGAImage & image) // draw 3 filled triangles
{
  vec2 t0[3] = { vec2(10, 70),   vec2(50, 160),  vec2(70, 80) };
  vec2 t1[3] = { vec2(180, 50),  vec2(150, 1),   vec2(70, 180) };
  vec2 t2[3] = { vec2(180, 150), vec2(120, 160), vec2(130, 180) };
//  triangle(t0[0], t0[1], t0[2], image, red);
//  triangle(t1[0], t1[1], t1[2], image, white);
//  triangle(t2[0], t2[1], t2[2], image, green);
  triangle_filled(image,t0[0], t0[1], t0[2], red);
  triangle_filled(image, t1[0], t1[1], t1[2],  white);
  triangle_filled(image, t2[0], t2[1], t2[2],  green);
}

void lesson2b(TGAImage & image) // draw african head as filled triangles
{
  std::vector <obj::CPart> v_parts;
  obj::CLoader_OBJ objload;

  objload.loadOBJParts("african_head.obj", v_parts);

  std::cout << v_parts.size() << std::endl;
  for (int i = 0; i < v_parts.size(); i++)
  {
    for (int j = 0; j < v_parts[i].vertices.size(); j += 3)
    {
      vec2 p0,p1,p2;
      float f = 400.0f;
      float xy_center = 500.0f;
      p0.x = xy_center + v_parts[i].vertices[j].x * f;
      p0.y = xy_center + v_parts[i].vertices[j].z * f;
      p1.x = xy_center + v_parts[i].vertices[j + 1].x * f;
      p1.y = xy_center + v_parts[i].vertices[j + 1].z * f;
      p2.x = xy_center + v_parts[i].vertices[j + 2].x * f;
      p2.y = xy_center + v_parts[i].vertices[j + 2].z * f;
      TGAColor col = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
      triangle_filled(image, p0, p1, p2, col);
    }
  }
}

void lesson2c(TGAImage & image) // draw african head with **simple** shading
{
  std::vector <obj::CPart> v_parts;
  obj::CLoader_OBJ objload;

  objload.loadOBJParts("african_head.obj", v_parts);

  std::cout << v_parts.size() << std::endl;
  for (int i = 0; i < v_parts.size(); i++)
  {
    for (int j = 0; j < v_parts[i].vertices.size(); j += 3)
    {
//      if (v_parts[i].vertices[j + 2].y >= -.2) // filters some "backfaces", as we do not have z-buffer yet
      {
        vec3 p0, p1, p2; // must go to vec3 now, in order to compute cross product (s.below)
        float f = 400.0f;
        float xy_center = 500.0f;
        p0.x = xy_center + v_parts[i].vertices[j].x * f;
        p0.y = xy_center + v_parts[i].vertices[j].z * f;
        p1.x = xy_center + v_parts[i].vertices[j + 1].x * f;
        p1.y = xy_center + v_parts[i].vertices[j + 1].z * f;
        p2.x = xy_center + v_parts[i].vertices[j + 2].x * f;
        p2.y = xy_center + v_parts[i].vertices[j + 2].z * f;

        //      vec3 vn = cross(p1 - p0, p2 - p0);
        vec3 vn = cross(v_parts[i].vertices[j + 1] - v_parts[i].vertices[j], v_parts[i].vertices[j + 2] - v_parts[i].vertices[j]);
        float f_len = len(vn);
        vn = vn / f_len;

        vec3 light = vec3(0.1, 0.0, -1.0); // play with these = fun (needs realtime manipulation)
        float ff = dot(vn, light);
        if (ff > 0.0) // back face culling, i.e. remove polygons, that face back from light (later: from the camera)
        {
          int gray = (int)(ff * 255);
          TGAColor col = TGAColor(gray, gray, gray, 255);
          triangle_filled(image, p0, p1, p2, col);
        }
      }
    }
  }
}

void lesson3(TGAImage & image) // draw african head with z-buffer
{
  std::vector <obj::CPart> v_parts;
  obj::CLoader_OBJ objload;

  objload.loadOBJParts("african_head.obj", v_parts);

  std::cout << v_parts.size() << std::endl;
  for (int i = 0; i < v_parts.size(); i++)
  {
    for (int j = 0; j < v_parts[i].vertices.size(); j += 3)
    {
      vec3 p0, p1, p2; // must go to vec3 now, in order to compute cross product (s.below)
      float f = 400.0f;
      float xy_center = 500.0f;
      p0.x = xy_center + v_parts[i].vertices[j].x * f;
      p0.y = xy_center + v_parts[i].vertices[j].z * f;
      p1.x = xy_center + v_parts[i].vertices[j + 1].x * f;
      p1.y = xy_center + v_parts[i].vertices[j + 1].z * f;
      p2.x = xy_center + v_parts[i].vertices[j + 2].x * f;
      p2.y = xy_center + v_parts[i].vertices[j + 2].z * f;

      //      vec3 vn = cross(p1 - p0, p2 - p0);
      vec3 vn = cross(v_parts[i].vertices[j + 1] - v_parts[i].vertices[j], v_parts[i].vertices[j + 2] - v_parts[i].vertices[j]);
      float f_len = len(vn);
      vn = vn / f_len;

      vec3 light = vec3(0.1, 0.0, -1.0); // play with these = fun (needs realtime manipulation)
      float ff = dot(vn, light);
      if (ff > 0.0) // back face culling, i.e. remove polygons, that face back from light (later: from the camera)
      {
        int gray = (int)(ff * 255);
        TGAColor col = TGAColor(gray, gray, gray, 255);
        triangle_filled(image, zbuf, p0, p1, p2, col);
      }
    }
  }
}

int main(int argc, char** argv)
{
	TGAImage image(1000, 1000, TGAImage::RGB);
//	image.set(52, 41, red);
//  Bresenham(image, 0, 0, 100, 100);
  
//  lesson1(image);

  lesson2(image);
//  lesson2b(image);
///  lesson2c(image);
  lesson3(image);

  image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
  image.write_tga_file("output.tga");
  
  return 0;
}

