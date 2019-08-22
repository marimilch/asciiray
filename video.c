#ifndef VIDEO_C
#define VIDEO_C

#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>

#define clear() printf("\033[H\033[J")

#define EMPTY_SPACE ' '

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

void render_brightness_map(struct Video *vid, double *z_map, char gradient[]){
    //get gradient length
    int g_len = get_str_len(gradient);

    //map length
    int len = vid->x * vid->y;

    //draw emptiness first
    for (int i = 0; i < len; ++i)
    {
        vid->map[i] = EMPTY_SPACE;
    }

    //the further away, the darker the char
    for (int i = 0; i < len; ++i)
    {
        if (z_map[i] < 0.0 || z_map[i] > 1.0){
            continue;
        }

        double val = z_map[i];
        
        // double division casted to integer on purpose
        // integerized brightness sets index on the gradient
        int g_pos = val * g_len;

        //just in case, it is out of bounds for whatever reason (seems to happen)
        if(g_pos<0)
        {
            g_pos = 0;
        } 
        else if(g_pos>=g_len)
        {
            g_pos = g_len-1;
        }

        vid->map[i] = gradient[g_pos];
    }
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
