#include<stdlib.h>
#include<conio.h>
typedef enum {
    PAUSE = 112,//ASCII value for p
    STOP = 115,//ASCII value for s
    RESUME = 114,//ASCII value for r
    RELOAD = 87,//does nothinhg for now, ASCII value for W
    KEY_UP = 256 + 72,
    KEY_DOWN = 256 + 80,
}playback_keys;