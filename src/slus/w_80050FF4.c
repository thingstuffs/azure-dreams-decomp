#include "common.h"

#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 DrawSync(s32);
extern s32 func_8003E4FC();
extern s32 func_8003F320(void);
extern s32 func_80041344();
extern s32 D_80080B9C;
extern s32 D_80080BAC;
extern s32 D_80081480;
extern s32 func_8003E140;

void func_80050FF4(s8 *arg0) {
    *arg0 = 0;
    func_8003E4FC(6, &D_80080BAC, NULL);
    func_8003E4FC(0xFF, &func_8003E140, arg0);
    func_8003F320();
    func_80041344(0x80020000, *(s32 *)0x80081480);
    DrawSync(0);
    *arg0 = 0;
    func_8003E4FC(6, &D_80080B9C, NULL);
    func_8003E4FC(0xFF, &func_8003E140, arg0);
    func_8003F320();
}
