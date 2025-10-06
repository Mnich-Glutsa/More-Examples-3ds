#include <citro2d.h>

#include <3ds.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define BOTTOM_SCREEN_WIDTH 320

static const char HelloWorld[] = {"Hello World!"};

C2D_TextBuf g_staticBuf;
C2D_Text g_staticText;

//-----------------------------------------------------
int main(int argc, char **argv)
//-----------------------------------------------------
{
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer

    C2D_TextParse(&g_staticText, g_staticBuf, HelloWorld);

    C2D_TextOptimize(&g_staticText);

    while (aptMainLoop()) {
        if (hidKeysDown() & KEY_START) break; //Click start to exit program

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bottom, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
		C2D_SceneBegin(bottom);

        C2D_DrawText(&g_staticText, C2D_AlignCenter, BOTTOM_SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 1, 1);
        //Center, Location x, Location y, ??, size, size

        C3D_FrameEnd(0);
    }
    C2D_Fini();
    C3D_Fini();
	gfxExit();
    return 0;
}