#ifndef AUDIO_DEV_H
#define AUDIO_DEV_H
#include<windows.h>
#include<complex.h>
#include<mmsystem.h>
#include<stdio.h>
#include"wav_data.h"
#pragma comment(lib,"winmm.lib")

extern HWAVEOUT hwaveout_device;

void open_audio_dev(WAV_HEADER *info);
void write_audioblock(HWAVEOUT audio_dev,LPSTR blocks,size_t size);
LPSTR load_audio_block(char *filename,size_t *block_size);
char *waveout_error_codes(unsigned int Code);
void pause_playback(HWAVEOUT audio_device);
void resume_playback(HWAVEOUT audio_device);
int get_code();
void volume_control(HWAVEOUT audio_device,int option);
uint32_t return_both_channels(uint16_t low,uint16_t high);
float display_vol_percent(uint16_t packed_value);

typedef struct{
    size_t num_samples;
}global_vars;

#endif