#include "audio_device.h"
// to do add a function to read the file bytes
WAV_HEADER MY_WAV;
HWAVEOUT hwaveout_device;

void *read_pcm_data(WAV_HEADER *headers,char *filename){
    FILE *fp = fopen(filename,"rb");
    fseek(fp,WAV_HEADER_SIZE,SEEK_SET);//GO OVER TO THE DATA SECTION
    int16_t *samples = malloc(headers->sub_chunk2_size);
    if(!samples){
        fprintf(stderr,"error in allocation");
        fclose(fp);
        return NULL;
    }
    size_t num_samples = headers->sub_chunk2_size / headers->Block_align;
    fread(samples,headers->sub_chunk2_size,1,fp);
    //GET NUMBER OF SAMPLES
    fprintf(stdout,"Number of samples: %zu\n",num_samples);
    fclose(fp);
}

void check_some(char *filename){
    FILE *fp = fopen(filename,"rb");
    if(!fp){
        fprintf(stderr,"unable to open file");
        return;
    }
    //check if it's a wav file
    fread(&MY_WAV,sizeof(WAV_HEADER),1,fp);

    if(strncmp(MY_WAV.chunk_id,WAV_CHUNK_ID,4) != 0){
        fprintf(stderr,"not a wav file\n");
        fclose(fp);
        return;
    }

    if(strncmp(MY_WAV.format,WAV_CHUNK_FORMAT,4) != 0){
        fprintf(stderr,"not a wav file\n");
        fclose(fp);
        return;
    }

    if(MY_WAV.audio_format != PCM_FORMAT){
        fprintf(stderr,"not a PCM wav file\n");
        fclose(fp);
        return;
    }
    

    fprintf(stdout, "file format %s\n", MY_WAV.chunk_id);
    fprintf(stdout, "chunk_size %u\n", MY_WAV.chunk_size);
    fprintf(stdout, "sub_chunk_id %s\n", MY_WAV.sub_chunk_id);
    fprintf(stdout, "sub_chunk_size %u\n", MY_WAV.sub_chunk_size);
    fprintf(stdout, "audio_format %u\n", MY_WAV.audio_format);
    fprintf(stdout, "Num_channels %u\n", MY_WAV.Num_channels);
    fprintf(stdout, "Sample_rate %u\n", MY_WAV.Sample_rate);
    fprintf(stdout, "Byte_rate %u\n", MY_WAV.Byte_rate);
    fprintf(stdout, "Block_align %u\n", MY_WAV.Block_align);
    fprintf(stdout, "BitsPersample %u\n", MY_WAV.BitsPersample);
    fprintf(stdout, "sub_chunk_id2 %s\n", MY_WAV.sub_chunk_id2);
    fprintf(stdout, "sub_chunk2_size %u\n", MY_WAV.sub_chunk2_size);
    read_pcm_data(&MY_WAV,filename);


}


int main(int argc, char *argv[]){
    LPSTR block; //POINTER TO THE AUDIO BLOCK
    size_t block_size;//SIZE OF THE AUDIO BLOCK
    if(argc < 2){
        fprintf(stderr,"Usage: %s <filename>\n",argv[0]);
        return 1;
    }
    if((block = load_audio_block(argv[1],&block_size)) == NULL){
        fprintf(stderr,"unable to load audio block\n");
        return 1;
    }
    check_some(argv[1]);
    open_audio_dev(&MY_WAV);
    write_audioblock(hwaveout_device,block,block_size);
    return 0;
}