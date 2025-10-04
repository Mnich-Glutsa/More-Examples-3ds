#include <citro2d.h>

#include <3ds.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

int x = 100;
int y = 100;

int controls() {
    hidScanInput();

    if (hidKeysDown() & KEY_START) return 1;

    circlePosition pos;

    hidCircleRead(&pos);

    if (pos.dx % 10 == 0) {
        x += pos.dx / 10;
    } else {
        x += (pos.dx - pos.dx % 10) / 20;
    }

    if (pos.dy % 10 == 0) {
        y -= pos.dy / 10;
    } else {
        y -= (pos.dy - pos.dy % 10) / 10;
    }

    if ((SCREEN_WIDTH - 25) < x) x = SCREEN_WIDTH - 25;
    if (x < 0) x = 0;
    if ((SCREEN_HEIGHT - 25) < y) y = SCREEN_HEIGHT - 25;
    if (y < 0) y = 0;

    printf("\x1b[1;1H%04d", x);
    printf("\x1b[2;1H%04d", y);

    return 0;
}

//---------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------
    // Init libs
	gfxInitDefault(); //bez tego crashuje 2ds'a XDD
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

    u32 clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
 	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    while (aptMainLoop()) {

        if (controls() == 1) break;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, clrBlack);
        C2D_SceneBegin(top);

        C2D_DrawRectSolid(x, y, 0, 25, 25, clrRed);
        //C2D_DrawRectSolid(położenie prawej, położenie od góry, ??, szerokość, wysokosc, kolor);

        C3D_FrameEnd(0);
    }
    C2D_Fini();
	C3D_Fini();
 	gfxExit();
	return 0;
}