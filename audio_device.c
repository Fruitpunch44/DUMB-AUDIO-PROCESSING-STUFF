#include"audio_device.h"
#include"keyboard.h"
#include<stdint.h>

DWORD default_auido = 65535;//start with max volume
#define KEY_UP 256 + 72
#define KEY_DOWN 256 + 80

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

void pause_playback(HWAVEOUT auido_device){

    if(waveOutPause(auido_device)!=MMSYSERR_NOERROR){
        fprintf(stderr,"unable to pause");
        return;
    }
}

void resume_playback(HWAVEOUT auido_device){
    if(waveOutRestart(auido_device)!=MMSYSERR_NOERROR){
        fprintf(stderr,"unable to resume");
        return;
    }
}

//check for keyboard input and return the key code
int get_code(){
    int ch = _getch();
    if(ch == 0 || ch ==224){
        ch = 256 + _getch();
    }
    return ch;
}
void volume_control(HWAVEOUT audio_device,int option){
    switch(option){
        case KEY_UP:
            DWORD volume_inc = 1000;
            default_auido += volume_inc;
            if(default_auido>65535){
                fprintf(stdout,"already at max\n");
                return;
            }
            if(waveOutSetVolume(audio_device,default_auido)!=MMSYSERR_NOERROR){
                fprintf(stderr,"unable to set volume\n");
                return;
            }
            fprintf(stdout,"current vol %d\n",default_auido);
            break;
        case KEY_DOWN:
         DWORD volume_dec = 1000;
            default_auido -= volume_dec;
            if(default_auido<0){
                fprintf(stdout,"already at min\n");
                return;
            }
            if(waveOutSetVolume(audio_device,default_auido)!=MMSYSERR_NOERROR){
                fprintf(stderr,"unable to set volume\n");
                return;
            }
            fprintf(stdout,"current vol %d\n",default_auido);
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
    }
}

void write_audioblock(HWAVEOUT audio_dev,LPSTR blocks,size_t size){
    //INIT OUR WAVHEADER
    WAVEHDR header;
    MMRESULT result;//return val of waveout
    ZeroMemory(&header,sizeof(header));
    header.dwBufferLength =size;
    header.lpData = blocks;
    result = waveOutPrepareHeader(audio_dev,&header,sizeof(header));
    fprintf(stdout,"Error code: %s\n", waveout_error_codes(result));
    if(waveOutPrepareHeader(audio_dev,&header,sizeof(header)) != MMSYSERR_NOERROR){
        fprintf(stderr,"unable to prepare  waveform audio block");
        return;
    }
    waveOutWrite(audio_dev,&header,sizeof(header));
        while(1){
        if(_kbhit()){
            int ch = get_code();
            playback_keys check = ch;
            switch(check){
                case PAUSE:
                    pause_playback(hwaveout_device);
                    fprintf(stdout,"playback paused\n");
                    break;
                case RESUME:
                    resume_playback(hwaveout_device);
                    fprintf(stdout,"playback resumed\n");
                    break;
                case STOP:
                    waveOutReset(hwaveout_device);
                    fprintf(stdout,"playback stopped\n");
                    return;
                case KEY_DOWN:
                    fprintf(stdout,"DOWN button %d\n", check);
                    volume_control(audio_dev,check);
                    break;
                case KEY_UP:
                    fprintf(stdout,"UP button %d\n", check);
                    volume_control(audio_dev,check);
                    break;
                default:
                    fprintf(stdout,"invalid command %d\n",check);
            }
        }
        Sleep(50);
    }
    Sleep(500);

    while(waveOutUnprepareHeader(audio_dev,&header,sizeof(header)) == WAVERR_STILLPLAYING){
        Sleep(100);
    }
}

LPSTR load_audio_block(char *filename,size_t *block_size){
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