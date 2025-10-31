#include <3ds.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <ncsnd.h>
#include <cwav.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

//-----------------------------------------------------
int main(int argc, char **argv)
//-----------------------------------------------------
{
    gfxInitDefault();
    romfsInit();

    consoleInit(GFX_TOP, NULL);

    printf("\x1b[1;1HCheckpoint 1");

    ncsndInit(true);

    printf("\x1b[2;1HCheckpoint 2");

    CWAV* cwav = (CWAV*)malloc(sizeof(CWAV));
    FILE* file = fopen("romfs:/hiscore.bcwav", "rb");
    fseek(file, 0, SEEK_END);
    u32 filesize = ftell(file);
    void* buffer = linearAlloc(filesize);

    printf("\x1b[3;1HCheckpoint 3");

    if (!buffer) svcBreak(USERBREAK_PANIC);

    fseek(file, 0, SEEK_SET);
    printf("\x1b[4;1HCheckpoint 4");
    fread(buffer, 1, filesize, file); //o tu dokładnie się psuje
    printf("\x1b[5;1HCheckpoint 5");
    fclose(file);
    printf("\x1b[6;1HCheckpoint 6");
    cwavLoad(cwav, buffer, 1);
    printf("\x1b[7;1HCheckpoint 7");
    cwav->dataBuffer = buffer;

    printf("\x1b[8;1HCheckpoint 8");

    printf("\x1b[15;1HA - play");
    printf("\x1b[16;1HSTART - exitt");
    while (aptMainLoop()) {
        if (hidKeysDown() & KEY_START) break; //Click start to exit program
        if (hidKeysDown() & KEY_A) { cwavPlay(cwav, 0, 1); printf("\x1b[18;1HSound!"); }
    }

	gfxExit();

    return 0;
}