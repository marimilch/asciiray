#ifndef ASCIIRAY_C
#define ASCIIRAY_C

#include"video.c"
#include"room.c"

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

    //create cube points
    struct Room room = 
    {
        {
            //number of coordinates and coordinates
            {
                8, 
                {
                    {-5.0,5.0,-5.0},
                    {5.0,-5.0,-5.0},
                    {-5.0,-5.0,-5.0},
                    {5.0,5.0,-5.0},
                    {-5.0,5.0,5.0},
                    {5.0,-5.0,5.0},
                    {-5.0,-5.0,5.0},
                    {5.0,5.0,5.0}
                }
            },
            //center
            {
                0.0,
                0.0,
                0.0
            },
            //scale
            25.0,
            //translation
            {
                0.0,
                0.0,
                300.0
            },
            //rotation
            {
                0.0,
                0.0,
                0.0,
            }
        },
        //optical center
        {
            20.0,
            10.0
        },

        6.0
    };

    byte xd = 5;
    byte yd = 5;
    byte zd = 5;

    for(int i = -1000; i < 1000; ++i){
        //room.rot_x = i/10.0;
        room.body.rot.y = ((i/100.0)*PI);
        room.body.rot.x = ((i/200.0)*PI);
        room.body.rot.z = ((i/400.0)*PI);

        room.body.t.y += xd;
        room.body.t.x += yd;
        room.body.t.z += zd;

        if (room.body.t.x >= ROOM_SIZE || room.body.t.x <= -ROOM_SIZE){
            xd *= -1;
        }

        if (room.body.t.y >= ROOM_SIZE || room.body.t.y <= -ROOM_SIZE){
            yd *= -1;
        }

        if (room.body.t.z >= ROOM_SIZE || room.body.t.z <= -ROOM_SIZE){
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
    free(video);
    return 0;
}

#endif
