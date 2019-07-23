#ifndef VIDEO_C
#define VIDEO_C

#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>

#define clear() printf("\033[H\033[J")

struct Video
{
    int x;
    int y;
    char *map;
};

void text(char *text, int x_pos, int y_pos, struct Video *v){
    int x = v->x;
    int y = v->y;

    for (int i = 0; i < x && text[i] != '\0'; ++i)
    {
        v->map[y_pos*x + x_pos + i] = text[i];
    }
}

void print(struct Video *v)
{
    int x = v->x;
    int y = v->y;

    char *vid_string = malloc( ((v->x+1)*v->y+1)*sizeof(double) );
    for (int i = 0; i < y; ++i)
    {

        for (int j = 0; j < x; ++j)
        {
            vid_string[i*(x+1) + j]= v->map[i*x + j];
        }
        vid_string[i*(x+1)+x] = '\n';
    }
    vid_string[y*x] = '\0';
    printf("%s", vid_string);
    free(vid_string);
}

#endif
