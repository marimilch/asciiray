#ifndef ASCIIRAY_C
#define ASCIIRAY_C

#include"video.c"
#include"room.c"
#include"basic_shapes.c"

#define ROOM_SIZE 300

typedef char byte;

int main(int argc, char *argv[])
{
    int x = 80;
    int y = 20;

    struct Video vid;
    vid.x = x;
    vid.y = y;
    char *video = malloc( x*y*sizeof(char) );
    vid.map = video;

    char gradient[] = " .+x#$";

    //prepare room and its sprites
    struct VoxSprite *vs = malloc(sizeof(struct VoxSprite));
    *vs = cube(8); 
    vs->t.x = x/2;
    vs->t.y = y/2;
    vs->t.z = -100.0;

    struct Room room;
    room.vs = vs;
    room.h.x = x/2;
    room.h.y = y/2;
    room.f = 10.0;

    byte xd = 5;
    byte yd = 5;
    byte zd = 5;

    for(int i = -1000; i < 1000; ++i){
        //room.rot_x = i/10.0;
        room.vs->rot.y = ((i/100.0)*PI);
        room.vs->rot.x = ((i/200.0)*PI);
        room.vs->rot.z = ((i/400.0)*PI);

        room.vs->t.y += xd;
        room.vs->t.x += yd;
        room.vs->t.z += zd;

        if (room.vs->t.x >= ROOM_SIZE || room.vs->t.x <= -ROOM_SIZE){
            xd *= -1;
        }

        if (room.vs->t.y >= ROOM_SIZE || room.vs->t.y <= -ROOM_SIZE){
            yd *= -1;
        }

        if (room.vs->t.z >= ROOM_SIZE || room.vs->t.z <= -ROOM_SIZE){
            zd *= -1;
        }

        render(&vid, gradient, room);
        text("I M A G I C U B E", 10, 2, &vid);

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
