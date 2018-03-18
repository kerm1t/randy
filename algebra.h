#ifndef __algebra_h__
#define __algebra_h__

struct vec2
{
  vec2() : x(0.0f), y(0.0f) {}
  vec2(float _x, float _y) : x(_x), y(_y) {}
  struct { float x; float y; };
  
};

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
vec3 operator*(const vec3 v1, const float f)
{
  return vec3(v1.x*f, v1.y*f, v1.z*f);
}
//typedef glm::vec3 vec3;
#endif
