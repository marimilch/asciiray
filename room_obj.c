#ifndef ROOM_OBJ_C
#define ROOM_OBJ_C

struct Vec 
{
    double x;
    double y;
    double z;
};

struct Trigone
{
    struct Vec v1;
    struct Vec v2;
    struct Vec v3;
};

struct VecArr
{
    int count;
    struct Vec vecs[8];
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

struct Shape
{
    //scale
    double s;

    //rotation
    struct Rot r;

    //center
    struct Vec c;

    //translation
    struct Vec t;
    struct Trigone *tris;
};

struct Body
{
    struct VecArr vecs;

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
    struct Body body;

    //optical center
    struct Coord h;

    //focal length of the lense
    double f;
};

#endif