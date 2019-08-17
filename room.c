#ifndef ROOM_C
#define ROOM_C

#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>

#include"video.c"
#include"room_obj.c"

#define PI 3.14159265358979323846

#define EMPTY_SPACE ' '

//number of "pixels" per unit in u/v direction
#define MU 2
#define MV 1

//functions
struct Coord planar(struct Vec v, struct Coord h, double f)
{
    if (v.z < f){
        struct Coord c = {-1, -1};
        return c;
    }

    double r = f/v.z;
    struct Coord c = {(MU * r * v.x) + MU*h.x, (MV * r * v.y) + MV*h.y};
    return c;
}

double scalar (struct Vec vec1, struct Vec vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

void render(struct Video *vid, char gradient[], struct Room room)
{
    int x = vid->x;
    int y = vid->y;

    //draw emptiness first
    for (int i = 0; i < x * y; ++i)
    {
        vid->map[i] = EMPTY_SPACE;
    }

    struct VoxSprite *vs = room.vs;

    //draw xz-plane (implicitly)

    //draw each voxel of sprite (ignore overlap for now)
    for (int i = 0; i < vs->vm.size.x_size; ++i)
    {
        for (int j = 0; j < vs->vm.size.y_size; ++j)
        {
            for (int k = 0; k < vs->vm.size.z_size; ++k)
            {
                //to be transformed vec (non-homogenous)
                struct Vec v;

                //set center
                v.x = vs->c.x + i;
                v.y = vs->c.y + j;
                v.z = vs->c.z + k;

                //scale 
                v.x *= vs->s;
                v.y *= vs->s;
                v.z *= vs->s;

                //transformed reference values for rotation (will be updated after each coordinate)
                struct Vec v_ref = v;

                //rotation self
                const struct Rot rot = vs->rot;

                //rotate
                //x-rotation
                v.y = (cos(rot.x) * (v_ref).y) + (-sin(rot.x) * (v_ref).z);
                v.z = (sin(rot.x) * (v_ref).y) + (cos(rot.x) * (v_ref).z) ;
                v_ref = v;

                //y-rotation
                v.x = (cos(rot.y) * (v_ref).x) + (sin(rot.y) * (v_ref).z);
                v.z = (-sin(rot.y) * (v_ref).x) + (cos(rot.y) * (v_ref).z) ;
                v_ref = v;

                //z-rotation
                v.x = (cos(rot.z) * (v_ref).x) + (-sin(rot.z) * (v_ref).y);
                v.y = (sin(rot.z) * (v_ref).x) + (cos(rot.z) * (v_ref).y) ;

                //translate
                //translation
                const struct Vec tra = vs->t;

                v.x += tra.x;
                v.y += tra.y;
                v.z += tra.z;

                struct Coord c = planar(v, room.h, room.f);
                int cx = (int) c.x;
                int cy = (int) c.y;

                //catch out of sight coordinates and if not already drawn
                if(cx >= 0 && cy>=0 && cx < x && cy < y && vid->map[cy * x + cx] == EMPTY_SPACE){
                    int pos = k * vs->vm.size.y_size * vs->vm.size.x_size  +  j * vs->vm.size.x_size +  i;
                    vid->map[cy * x + cx] = vs->vm.voxels[pos];
                }
            }
        }
    }
}

#endif
