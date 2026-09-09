#include "common.h"

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 DrawSync(s32);
extern s32 Control_CD();
extern s32 func_8003F320(void);
extern s32 func_80041344();
extern s32 D_80080B9C;
extern s32 D_80080BAC;
extern s32 D_80081480;
extern s32 func_8003E140;

/* Runs two callback sequences, resetting their shared status byte before each. */
void func_80050FF4(s8 *status) {
    *status = 0;
    Control_CD(6, &D_80080BAC, NULL);
    Control_CD(0xFF, &func_8003E140, status);
    func_8003F320();
    func_80041344(0x80020000, *(s32 *)0x80081480);
    DrawSync(0);
    *status = 0;
    Control_CD(6, &D_80080B9C, NULL);
    Control_CD(0xFF, &func_8003E140, status);
    func_8003F320();
}
