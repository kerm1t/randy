#ifndef __algebra_h__
#define __algebra_h__

/*
  analytic geometry
  linear algebra
*/

struct vec2
{
  vec2() : x(0.0f), y(0.0f) {}
  vec2(float _x, float _y) : x(_x), y(_y) {}
  struct { float x; float y; };
  
};
vec2 operator-(const vec2 v1, const vec2 v2)
{
  return vec2(v2.x - v1.x, v2.y - v1.y);
}

struct vec3
{
  vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  vec3(float _xr, float _yg, float _zb) : x(_xr), y(_yg), z(_zb) {}
  union
  {
    struct { float x; float y; float z; };
    struct { float r; float g; float b; };
  };
};
vec3 operator*(const vec3 v1, const vec3 v2)
{
  return vec3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}
vec3 operator/(const vec3 v1, float f)
{
  return vec3(v1.x/f, v1.y/f, v1.z/f);
}
vec3 operator*(const vec3 v1, const float f)
{
  return vec3(v1.x*f, v1.y*f, v1.z*f);
}
vec3 operator-(const vec3 v1, const vec3 v2)
{
  return vec3(v2.x-v1.x, v2.y-v1.y, v2.z-v1.z);
}
vec3 cross(const vec3 v1, const vec3 v2)
{
  return vec3(v1.y*v2.z - v2.y*v1.z, v1.z*v2.x - v2.z*v1.x, v1.x*v2.y - v2.x*v1.y);
}
float len(const vec3 v)
{
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
float dot(const vec3 v1, const vec3 v2) // dot product, scalar product
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

//float scalar_prod(const vec3 v1, const vec3 v2)
//{
//  return len(v1)*len(v2)*cos()
//}
//typedef glm::vec3 vec3;

vec3 bary_coords(const vec3 a, const vec3 b, const vec3 c, vec2 vec)  // https://www.gamedev.net/forums/topic/621445-barycentric-coordinates-c-code-check/
                                                                      // https://en.wikipedia.org/wiki/Barycentric_coordinate_system
{
  vec3 lambda;
  float determinant = 1 / ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
  lambda.x = ((b.y - c.y) * (vec.x - c.x) + (c.x - b.x) * (vec.y - c.y)) * determinant;
  lambda.y = ((c.y - a.y) * (vec.x - c.x) + (a.x - c.x) * (vec.y - c.y)) * determinant;
  lambda.z = 1 - lambda.x - lambda.y;
  return lambda;
}
#endif
