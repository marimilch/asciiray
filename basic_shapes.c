#ifndef BASIC_SHAPES_C
#define BASIC_SHAPES_C

#include<stdbool.h>
#include<stdlib.h>
#include"room_obj.c"

// probably laziest way to create cube voxels, lol 
struct VoxSprite cube(int cube_length){
    struct VoxMap vm;

    vm.size.x_size = cube_length;
    vm.size.y_size = cube_length;
    vm.size.z_size = cube_length;

    //DONT FORGET TO FREE ME!!!!!1!1!1!!111
    vm.voxels = malloc(cube_length*cube_length*cube_length*sizeof(char));
 
    for (int i = 0; i < cube_length; ++i)
    {
        for (int j = 0; j < cube_length; ++j)
        {
            for (int k = 0; k < cube_length; ++k)
            {
                bool is_cube_point = 
                    i == 0 || i == cube_length || 
                    j == 0 || j == cube_length || 
                    k == 0 || k == cube_length
                ;
                if (is_cube_point){
                    int pos = cube_length*cube_length*i + cube_length*j + k;
                    vm.voxels[pos]= 'X';
                }
            }
        }
    }

    struct VoxSprite vs = {
        {{0,0,0},NULL},
        {0.0,0.0,0.0},
        1,
        {0.0,0.0,0.0},
        {0.0,0.0,0.0}
    };

    vs.vm = vm;

    vs.c.x = ((double) cube_length)/2;
    vs.c.y = ((double) cube_length)/2;
    vs.c.z = ((double) cube_length)/2;

    return vs;
}

#endif
