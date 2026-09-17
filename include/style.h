#include<stdio.h>
#include"raylib.h"
#include <stdlib.h>

//colors
#define BLACK (Color){0, 0, 0, 255}
#define Purple (Color){153,0,153,255}
#define SkyBlue (Color){153,204,255}
#define HighYellow (Color){255,255,102}
#define Somedarkred (Color){255,51,153}


//Vizualization mode 
typedef enum {
    WaveForm,
    Standard,
    StarBurst,
    Num_Modes = 3
}Visual_modes;

typedef struct {
    char *wav_name;
    unsigned int wav_size;
    unsigned int time;
} WAV_Info;

extern Visual_modes cur_visual_mode=Standard;

void change_visualmode_prev(){
    cur_visual_mode == (cur_visual_mode - 1 + Num_Modes) % Num_Modes;
}
void change_visualmode_next(){
    cur_visual_mode == (cur_visual_mode +1 +Num_Modes)% Num_Modes;
}