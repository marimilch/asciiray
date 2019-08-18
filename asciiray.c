#ifndef ASCIIRAY_C
#define ASCIIRAY_C

#include"video.c"
#include"room.c"
#include"basic_shapes.c"

typedef char byte;

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
    int room_size = x/4;

    struct Video vid;
    vid.x = x;
    vid.y = y;
    char *video = malloc( x*y*sizeof(char) );
    vid.map = video;

    char gradient[] = " .+x#$";

    //prepare room and its sprites
    struct VoxSprite *vs = malloc(sizeof(struct VoxSprite));
    *vs = cube(x/8); 
    vs->t.x = 0.0;
    vs->t.y = 0.0;
    vs->t.z = x/2;

    struct Room room;
    room.vs = vs;
    room.h.x = x/4;
    room.h.y = y/2;
    room.f = 55.0;

    double xd = -0.5;
    double yd = -0.5;
    double zd = -0.5;

    for(int i = -1000; i < 1000; ++i){
        //room.rot_x = i/10.0;
        room.vs->rot.y = ((i/100.0)*PI);
        room.vs->rot.x = ((i/200.0)*PI);
        room.vs->rot.z = ((i/400.0)*PI);

        room.vs->t.y += xd;
        room.vs->t.x += yd;
        room.vs->t.z += zd;

        if ( fabs(room.vs->t.x) >= room_size){
            xd *= -1;
        }

        if ( fabs(room.vs->t.y) >= room_size){
            yd *= -1;
        }

        if ( room.vs->t.z >= room_size || room.vs->t.z < 0){
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
