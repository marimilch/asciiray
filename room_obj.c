#ifndef ROOM_OBJ_C
#define ROOM_OBJ_C

struct Vec 
{
    double x; //to right
    double y; //to bottom
    double z; //to back
};

struct Size
{
    int x_size;
    int y_size;
    int z_size;
};

struct VecArr
{
    int count;

    //C-Array
    struct Vec *vecs;
};

struct VoxMap
{
    struct Size size;
    //doubles represent brightness level
    double *voxels;
};

struct Coord
{
    double x;
    double y;
};

struct Rot
{
    //counter clockwise rotation around axis
    double x;
    double y;
    double z;
};

struct VoxSprite
{
    struct VoxMap vm;

    //center
    struct Vec c;

    //scale
    double s;

    //translation
    struct Vec t;

    //rotation
    struct Rot rot;
};

struct Room
{
    struct VoxSprite *vs;

    //optical center
    struct Coord h;

    //focal length of the lense
    double f;

    //render distance (for distance dependent brightness)
    double rd;
};

#endif