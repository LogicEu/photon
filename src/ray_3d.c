#include <photon.h>

Ray3D ray3D_new(vec3 orig, vec3 dir) 
{
    Ray3D ray = {orig, dir};
    return ray;
}

vec3 ray3D_at(const Ray3D* restrict ray, float t) 
{ 
    return vec3_add(ray->orig, vec3_mult(ray->dir, t)); 
}