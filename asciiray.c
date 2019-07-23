#ifndef ASCIIRAY_C
#define ASCIIRAY_C

#include"video.c"
#include"room.c"

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

        5.0
    };

    //printf("gradient has length: %d", get_str_len(gradient))
    //char input = NO_KEY;
    for(int i = -1000; i < 1000; ++i){
        //room.rot_x = i/10.0;
        room.body.rot.y = ((i/100.0)*PI);
        room.body.rot.x = ((i/200.0)*PI);
        room.body.rot.z = ((i/400.0)*PI);

        //room.body.t.x = (double) i;

        // room.t_x = sin(i/12.0) + x/2;
        // room.t_y = cos(i/15.0) + y/2;
        // room.t_z = sin(i/17.0);

        // room.f = i;

        //input = get_input();
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
