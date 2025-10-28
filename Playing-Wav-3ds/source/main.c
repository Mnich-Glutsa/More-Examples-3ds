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

    printf("1;1HCheckpoint 1");

    ncsndInit(true);

    printf("2;1HCheckpoint 2");

    CWAV* cwav = (CWAV*)malloc(sizeof(CWAV));
    FILE* file = fopen("romfs:/hiscore.bcwav", "rb");
    fseek(file, 0, SEEK_END);
    u32 filesize = ftell(file);
    void* buffer = linearAlloc(filesize);

    printf("3;1HCheckpoint 3");

    if (!buffer) svcBreak(USERBREAK_PANIC);

    fseek(file, 0, SEEK_SET);
    fread(buffer, 1, filesize, file);
    fclose(file);                           //w tym bloku się coś pierdoli
    cwavLoad(cwav, buffer, 1);
    cwav->dataBuffer = buffer;

    printf("4;1HCheckpoint 4");

    printf("15;1HA - play");
    printf("16;1HSTART - exitt");
    while (aptMainLoop()) {
        if (hidKeysDown() & KEY_START) break; //Click start to exit program
        if (hidKeysDown() & KEY_A) { cwavPlay(cwav, 0, 1); printf("3;1HSound!"); }
    }

	gfxExit();

    return 0;
}