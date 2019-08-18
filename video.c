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

int get_str_len(char str[]){
    int g_len = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        ++g_len;
    }
    return g_len;
}

void text(char *text, int x_pos, int y_pos, struct Video *v){
    int x = v->x;
    int y = v->y;

    for (int i = 0; i < x && text[i] != '\0'; ++i)
    {
        //assume given coordinate is supposed to be center of text
        int pos = y_pos*x + x_pos + i - get_str_len(text)/2;

        //catch out of bounds
        if (pos >= 0 || pos < x*y)
            v->map[pos] = text[i];
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
