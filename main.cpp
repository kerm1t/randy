#include "tgaimage.h"
#include "draw_lib.hpp"
#include "mdl_wavefront.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv)
{
	TGAImage image(1000, 1000, TGAImage::RGB);
//	image.set(52, 41, red);
//  Bresenham(image, 0, 0, 100, 100);
  
  std::vector <obj::CPart> v_parts;
  obj::CLoader_OBJ objload;

  objload.loadOBJParts("african_head.obj",v_parts);

  std::cout << v_parts.size() << std::endl;
  for (int i = 0; i < v_parts.size(); i++)
  {
    for (int j = 0; j < v_parts[i].vertices.size(); j+=3)
    {
      float x[3];
      float y[3];
      float z[3];
      float f = 400.0f;
      float xy_center = 500.0f;
      x[0] = xy_center + v_parts[i].vertices[j].x * f;
      y[0] = xy_center + v_parts[i].vertices[j].z * f;
      x[1] = xy_center + v_parts[i].vertices[j+1].x * f;
      y[1] = xy_center + v_parts[i].vertices[j+1].z * f;
      x[2] = xy_center + v_parts[i].vertices[j+2].x * f;
      y[2] = xy_center + v_parts[i].vertices[j+2].z * f;
      Bresenham(image, x[0], y[0], x[1], y[1]);
      Bresenham(image, x[1], y[1], x[2], y[2]);
      Bresenham(image, x[2], y[2], x[0], y[0]);
    }
  }
  image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	return 0;
}

