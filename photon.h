
/*  Copyright (c) 2022 Eugenio Arteaga A.

Permission is hereby granted, free of charge, to any 
person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the 
Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice 
shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef PHOTON_PHYSICS_H
#define PHOTON_PHYSICS_H

#ifdef __cplusplus
extern "C" {
#endif

/*===============================================
>>>>>>>>>>>>>>  PHOTON PHYSICS    >>>>>>>>>>>>>>>
Ray casting and primitive shapes for graphics and
physics in 2D and 3D.
=========================== Eugenio Arteaga A. */

#include <stdbool.h>
#include <stddef.h>
#include <fract.h>

typedef struct Rect {
    float x, y, w, h;
} Rect;

typedef struct Circle {
    vec2 pos;
    float radius;
} Circle;

typedef struct Sphere {   
    vec3 pos;
    float radius;
} Sphere;

typedef struct Tri2D {
    vec2 a, b, c;
} Tri2D;

typedef struct Tri3D {
    vec3 a, b, c;
} Tri3D;

typedef struct Hex3D {
    vec3 dimension, position;
} Hex3D;

typedef struct Quad2D {
    vec2 a, b, c, d;
} Quad2D;

typedef struct Ray2D {
    vec2 orig;
    vec2 dir;
} Ray2D;

typedef struct Hit2D {
    float t;
    vec2 normal;
} Hit2D;

typedef struct Ray3D {
    vec3 orig;
    vec3 dir;
} Ray3D;

typedef struct Hit3D {
    float t;
    vec3 normal;
} Hit3D;

typedef struct Box3D {
    vec3 min;
    vec3 max;
} Box3D;

#define _ray3D_at(ray, t) ((vec3){ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t, ray->orig.z + ray->dir.z * t})
#define _ray2D_at(ray, t) ((vec2){ray->orig.x + ray->dir.x * t, ray->orig.y + ray->dir.y * t})

/*******************
 -> Vec Extension <- 
*******************/

vec2 vec2_rand(void);
vec3 vec3_rand(void);
vec2 vec2_reflect(vec2 v, vec2 n);
vec3 vec3_reflect(vec3 v, vec3 n);
bool vec3_refract(vec3 v, vec3 n, float nint, vec3* outRefracted);

/********
 -> 2D <-
********/

bool line2D_intersect(vec2 p0, vec2 p1, vec2 p2, vec2 p3, vec2* out);

Circle circle_new(vec2 pos, float radius);
bool circle_point_overlap(Circle circle, vec2 p);
bool circle_point_overlap_offset(Circle circle, vec2 p, vec2 offset);
bool circle_overlap(Circle c1, Circle c2);
bool circle_overlap_offset(Circle c1, Circle c2, vec2 offset);

Tri2D tri2D_new(vec2 a, vec2 b, vec2 c);
vec3 tri2D_barycenter(const Tri2D* tri, const vec2 p);
bool tri2D_point_overlap(const Tri2D* tri, vec2 p);
bool tri2D_point_overlap_offset(const Tri2D* tri, vec2 p, vec2 offset);
bool tri2D_overlap(const Tri2D* t1, const Tri2D* t2);
bool tri2D_overlap_offset(const Tri2D* t1, const Tri2D* t2, vec2 offset);
bool tri2D_hit(const Tri2D* tri, const Ray2D* ray, Hit2D* outHit);
bool tri2D_hit_range(const Tri2D* tri, const Ray2D* ray, Hit2D* outHit, float max);

Quad2D quad2D_new(vec2 a, vec2 b, vec2 c, vec2 d);
Quad2D rect_to_quad(Rect r);

Rect rect_new(float x, float y, float w, float h);
Rect quad_to_rect(Quad2D q);
bool rect_point_overlap(Rect r, vec2 p);
bool rect_point_overlap_offset(Rect r, vec2 p, vec2 offset);
bool rect_overlap(Rect r1, Rect r2);
bool rect_overlap_offset(Rect r1, Rect r2, vec2 offset);

Hit2D hit2D_new(float t, vec2 normal);
Ray2D ray2D_new(vec2 orig, vec2 dir);
vec2 ray2D_at(const Ray2D* ray, float t);

/********
 -> 3D <-
********/

Sphere sphere_new(vec3 pos, float radius);
bool sphere_hit(Sphere sphere, const Ray3D* ray, Hit3D* outHit);
bool sphere_point_overlap(Sphere sphere, vec3 p);
bool sphere_point_overlap_offset(Sphere sphere, vec3 p, vec3 offset);
bool sphere_overlap(Sphere s1, Sphere s2);
bool sphere_overlap_offset(Sphere s1, Sphere s2, vec3 offset);

Tri3D tri3D_new(vec3 a, vec3 b, vec3 c);
vec3 tri3D_norm(const Tri3D* tri);
bool tri3D_hit(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit);
bool tri3D_hit_fast(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit, const float closest);
bool tri3D_hit_range(const Tri3D* tri, const Ray3D* ray, Hit3D* outHit, float tMin, float tMax);

Hex3D hex3D_new(vec3 dimension, vec3 position);
bool hex3D_overlap(Hex3D a, Hex3D b);

Hit3D hit3D_new(float t, vec3 normal);
Ray3D ray3D_new(vec3 orig, vec3 dir);
vec3 ray3D_at(const Ray3D* ray, float t);

Box3D box3D_new(const vec3 min, const vec3 max);
Box3D box3D_move(const Box3D box, const vec3 v);
Box3D box3D_from_triangle(const Tri3D* t);
Box3D box3D_from_mesh(const vec3* v, const size_t count);
bool box3D_overlap(const Box3D a, const Box3D b);
bool box3D_hit(const Box3D* box, const Ray3D* ray, Hit3D* outHit);
bool box3D_hit_fast(const Box3D* box, const Ray3D* ray, float* tOut);

#ifdef __cplusplus
}
#endif
#endif
