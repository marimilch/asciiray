#ifndef BASIC_SHAPES_C
#define BASIC_SHAPES_C

#include"room_obj.c"

struct Shape cube(){
    struct Trigone *t = malloc(12*sizeof(struct Trigone));

    struct Vec ful = {0,0,0};
    struct Vec fur = {0,1,0};
    struct Vec fdl = {1,0,0};
    struct Vec fdr = {1,1,0};

    struct Vec bul = {0,0,1};
    struct Vec bur = {0,1,1};
    struct Vec bdl = {1,0,1};
    struct Vec bdr = {1,1,1};

    //front
    t[0] = {ful, fur, fdl};
    t[1] = {fdl, fdr, fur};

    //left
    t[2] = {ful, bul, bdl};
    t[3] = {ful, fdl, bdl};

    //right
    t[4] = {fur, fdr, bur};
    t[5] = {bdr, fdr, bur};

    //top
    t[6] = {ful, bul, fur};
    t[7] = {bur, bul, fur};

    //bottom
    t[8] = {fdl, bdl, fdr};
    t[9] = {bdr, bdl, fdr};

    //back
    t[10] = {bul, bur, bdl};
    t[11] = {bdl, bdr, bur};

    struct Shape s;
    return s;
}

#endif
