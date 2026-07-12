#ifndef WAV_DATA_H
#define WAV_DATA_H

#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define WAV_HEADER_SIZE 44
#define WAV_CHUNK_ID "RIFF"
#define WAV_CHUNK_FORMAT "WAVE"
#define WAV_SUB_CHUNK1_ID "fmt"
#define WAV_SUB_CHUNK2_ID "data"
#define PCM_FORMAT 1

typedef struct {
    //RIFF chuk
    char chunk_id[4]; //4b
    uint32_t chunk_size;//4b
    char format[4]; //4b
    //fmt sub-chunl
    char sub_chunk_id[4];//4b
    uint32_t sub_chunk_size;//4b
    uint16_t audio_format;//2b
    uint16_t Num_channels;//2b
    uint32_t Sample_rate;//4b
    uint32_t Byte_rate;//4b
    uint16_t Block_align;//2b
    uint16_t BitsPersample;//2b
     //data sub-chunk
    char sub_chunk_id2[4];//4b
    uint32_t sub_chunk2_size;//4b
}WAV_HEADER;

void check_some(char *file);
void *read_pcm_data(WAV_HEADER *headers,char *filename);


#endif