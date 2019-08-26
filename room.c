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

double *create_z_map(int length)
{
    //remember to free me
    double *z_map = malloc(sizeof(double)*length);
    for (int i = 0; i < length; ++i)
    {
        z_map[i] = -1.0;
    }

    return z_map;
}

//should have given room as a pointer but whatevs, it's just a little demo
void render(struct Video *vid, char gradient[], struct Room room)
{
    int x = vid->x;
    int y = vid->y;

    //holds the z-vals of the planared voxel
    double *z_map = create_z_map(x*y);

    //brightness-map of points (just a map of distances multiplied with the brightness value of an object)
    double *brightness_map = create_z_map(x*y);

    struct VoxSprite *vs = room.vs;

    //draw xz-plane (implicitly)

    //write z-coordinate on position, where the planared voxel will be
    for (int i = 0; i < vs->vm.size.x_size; ++i)
    {
        for (int j = 0; j < vs->vm.size.y_size; ++j)
        {
            for (int k = 0; k < vs->vm.size.z_size; ++k)
            {
                //extra variable for a little better readability
                int voxel_index = k * vs->vm.size.y_size * vs->vm.size.x_size  +  j * vs->vm.size.x_size + i;

                //get the brightness level of planared voxel
                double voxel_brightness = vs->vm.voxels[voxel_index];

                //if negative, assume nothingness, so skippable
                if (voxel_brightness < 0.0){
                    continue;
                }

                //to be transformed vec (non-homogenous)
                struct Vec v;

                //set center
                v.x = -vs->c.x + (double)i * 1.0/VOX_DENSITY;
                v.y = -vs->c.y + (double)j * 1.0/VOX_DENSITY;
                v.z = -vs->c.z + (double)k * 1.0/VOX_DENSITY;

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

                // if( i == 0 && j == 0 && k == 0){
                //     //debug info

                //     printf("first point at (%f,%f,%f)\n", v.x, v.y, v.z);
                // }

                //catch out of sight coordinates and if old value not nearer than new one
                //exception -> if negative, it means nothing is there right now
                if(cx >= 0 && cy>=0 && cx < x && cy < y){
                    int pos = cy * x + cx;
                    double *saved_z_val = &z_map[pos];
                    if( v.z < *saved_z_val || *saved_z_val < 0.0){
                        *saved_z_val = v.z;
                        brightness_map[pos] = (voxel_brightness * ( room.rd - (v.z - room.f) ))/room.rd;
                    }
                } 
                // else {
                //     if (cx < 0){
                //         text("<-", 4, y/2, vid);
                //     } 
                //     if (cy < 0){
                //         text("/\\", x/2, 4, vid);
                //     } 
                //     if (cx >= x){
                //         text("->", x-5, y/2, vid);
                //     } 
                //     if (cy >= y){
                //         text("\\/", x/2, y-5, vid);
                //     }
                // }
            }
        }
    }
    free(z_map);
    render_brightness_map(vid, brightness_map, gradient);
    free(brightness_map);
}

#endif
