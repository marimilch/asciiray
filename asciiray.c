#ifndef ASCIIRAY_C
#define ASCIIRAY_C

#include"video.c"
#include"room.c"
#include"basic_shapes.c"

typedef char byte;

#define FOCAL_LENGTH 55.0

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./ascii_ray width height\n");
        printf("Warning: Not a raytracer, uses voxels and camera matrix.\nI was stupid to call it that, lol\n");
        return 0;
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int room_width = x/2;
    int room_height = y;

    struct Video vid;
    vid.x = x;
    vid.y = y;
    char *video = malloc( x*y*sizeof(char) );
    vid.map = video;

    char gradient[] = ".:+xX#W";

    //prepare room and its sprites
    struct VoxSprite *vs = malloc(sizeof(struct VoxSprite));

    int cube_size = x/8 * VOX_DENSITY;

    //distance midpoint to corner of cube
    double cd = sqrt((double)3*cube_size*cube_size/4);

    //distance cube mid point + focal length
    double cf = cd + FOCAL_LENGTH;

    double room_depth = 1.5 * (sqrt(3*room_width*room_height) + cf);

    *vs = cube(cube_size, true); 
    vs->t.x = 0.0;
    vs->t.y = 0.0;
    vs->t.z = room_depth / 2.0;

    struct Room room;
    room.vs = vs;
    room.h.x = x/4;
    room.h.y = y/2;
    room.f = FOCAL_LENGTH;
    //render to the end of the room
    room.rd = room_depth;

    double xd = -0.5;
    double yd = -0.6;
    double zd = -1.4;

    for(int i = -1000; i < 1000; ++i){
        //room.rot_x = i/10.0;
        room.vs->rot.y = ((i/100.0)*PI);
        room.vs->rot.x = ((i/200.0)*PI);
        room.vs->rot.z = ((i/400.0)*PI);

        room.vs->t.x += xd;
        room.vs->t.y += yd;
        room.vs->t.z += zd;

        if ( fabs(room.vs->t.x) >= room_width - cd){
            xd *= -1;
        }

        if ( fabs(room.vs->t.y) >= room_height - cd){
            yd *= -1;
        }

        if ( room.vs->t.z + cf >= room_depth || room.vs->t.z < cf){
            zd *= -1;
        }

        render(&vid, gradient, room);
        text(" I M A G I C U B E ", x/2, y/8, &vid);

        print(&vid);
        //printf("%d", i);
        //60 fps (theoretically)
        usleep(40000);
        // rotate(gradient);
        clear();

        if (i==999){
            i = -1000;
        }

    } 
    // draw(x, y, video, gradient);
    // print(x, y, video);
    free(vs->vm.voxels);
    free(vs);
    free(video);
    return 0;
}

#endif
