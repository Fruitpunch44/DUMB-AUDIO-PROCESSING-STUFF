#ifndef AUDIO_DEV_H
#define AUDIO_DEV_H
#include<windows.h>
#include<mmsystem.h>
#include<stdio.h>
#include"wav_data.h"
#pragma comment(lib,"winmm.lib")

extern HWAVEOUT hwaveout_device;
void open_audio_dev(WAV_HEADER *info);
void write_audioblock(HWAVEOUT audio_dev,LPSTR blocks,size_t size);
LPSTR load_audio_block(char *filename,size_t *block_size);
char *waveout_error_codes(unsigned int Code);

#endif