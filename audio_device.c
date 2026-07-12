#include"audio_device.h"
#include<stdint.h>

char *waveout_error_codes(unsigned int CODE){
    switch (CODE)
    {
    case MMSYSERR_NOERROR:
        return " MMSYSERR_NOERROR ";
        break;
    case MMSYSERR_INVALHANDLE:
        return "MMSYSERR_INVALIDHANDLE";
        break;
    case MMSYSERR_NODRIVER:
        return "MMSYSERR_NODRIVER";
        break;
    case MMSYSERR_NOMEM:
        return "MMSYSERR_NOMEM";
        break;
    default:
        return "INVALID ERROR CODE";
        break;
    }
}

void open_audio_dev(WAV_HEADER *info){
    WAVEFORMATEX wav_format;
    wav_format.wFormatTag = info->audio_format;//pcm
    wav_format.nChannels =info->Num_channels;
    wav_format.nSamplesPerSec=info->Sample_rate;
    wav_format.nAvgBytesPerSec =info->Byte_rate;
    wav_format.nBlockAlign = info->Block_align;
    wav_format.wBitsPerSample =info->BitsPersample;
    wav_format.cbSize = 0;

    if(waveOutOpen(&hwaveout_device,WAVE_MAPPER,&wav_format,0,0,WAVE_ALLOWSYNC)!=MMSYSERR_NOERROR){
        fprintf(stderr,"unable to open device\n");
    }
    else{
        fprintf(stdout,"wave mapper device was opened success\n");
        waveOutClose(hwaveout_device);
    }
}

void write_audioblock(HWAVEOUT audio_dev,LPSTR blocks,uint16_t size){
    //INIT OUR WAVHEADER
    WAVEHDR header;
    MMRESULT result;//return val of waveout
    ZeroMemory(&header,sizeof(header));
    header.dwBufferLength =size;
    header.lpData =blocks;
    result = waveOutPrepareHeader(audio_dev,&header,sizeof(header));
    waveout_error_codes(result);
    if(waveOutPrepareHeader(audio_dev,&header,sizeof(header)) != MMSYSERR_NOERROR){
        fprintf(stderr,"unable to prepare  waveform audio block");
        return;
    }
    waveOutWrite(audio_dev,&header,sizeof(header));
    Sleep(500);

    while(waveOutUnprepareHeader(audio_dev,&header,sizeof(header)) == WAVERR_STILLPLAYING){
        Sleep(100);
    }
}

LPSTR load_audio_block(char *filename,uint16_t *block_size){
    FILE *fp = fopen(filename,"rb");
    if(!fp){
        fprintf(stderr,"unable to open file");
        return NULL;
    }
    fseek(fp,0,SEEK_END);
    long block_size_bytes =ftell(fp);
    fprintf(stdout,"block size in bytes %ld\n",block_size_bytes);
    void *block = malloc(block_size_bytes);
    if(!block){
        fprintf(stderr,"error in allocating block sizes");
        fclose(fp);
        return NULL;
    }
    fseek(fp,0,SEEK_SET);//GO BACK TO THE BEGINING
    fread(block,1,block_size_bytes,fp);
    *block_size = block_size_bytes;
    fclose(fp);
    return (LPSTR)block;
}