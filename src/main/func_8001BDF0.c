#include "common.h"

extern s32 D_8002D690[4];
extern s32 D_8002D6A0[3];

void func_8001BDF0(void *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *(u8 **) ((u8 *) arg0 + 0x68C + i * 4) = (u8 *) arg0 + 0x6A4 + i * 0x10;
        *(s32 *) ((u8 *) arg0 + 0x704 + i * 0x10) = D_8002D690[0];
        *(s32 *) ((u8 *) arg0 + 0x708 + i * 0x10) = D_8002D690[1];
        *(s32 *) ((u8 *) arg0 + 0x70C + i * 0x10) = D_8002D690[2];
        *(s32 *) ((u8 *) arg0 + 0x710 + i * 0x10) = D_8002D690[3];
        *(s32 *) ((u8 *) arg0 + 0x6A8 + i * 0x10) = (s32) ((u8 *) arg0 + 0x704 + i * 0x10);
        *(u8 **) ((u8 *) arg0 + 0x6AC + i * 0x10) = (u8 *) arg0 + 0x670;
    }
    *(s32 *) ((u8 *) arg0 + 0x670) = D_8002D6A0[0];
    *(s32 *) ((u8 *) arg0 + 0x674) = D_8002D6A0[1];
    *(s32 *) ((u8 *) arg0 + 0x678) = D_8002D6A0[2];
}
