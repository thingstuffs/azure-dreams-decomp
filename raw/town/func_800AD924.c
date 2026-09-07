#include "common.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s16 pad0;
    u16 f2;
    s16 pad4;
    u16 f6;
    s16 pad8;
    u16 fA;
} S_80083780;

extern void *func_8009C390(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern s32 func_800AAE98(void *arg0);
extern void func_800AAEFC(void);
extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern void func_80033CD8(void *arg0, void *arg1);

extern s32 D_80081458[];
extern S_80083780 D_80083780;
extern u8 D_800AB1E0[];
extern u8 D_800AB708[];
extern u8 D_800D1200[];
extern u8 D_80045340[];

void func_800AB084(void) {
    s8 *temp_v0;
    s8 *temp_s0;
    s8 *temp_s1;
    s8 *temp_a1;

    temp_v0 = (s8 *) func_8009C390(0, 0, D_800AB1E0, 0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        temp_s1 = *(s8 **)(temp_v0 + 8);
        temp_a1 = *(s8 **)(temp_v0 + 0xC);
        *(s8 *)(temp_s0 + 0x93) = 1;
        *(s32 *)(temp_a1 + 0x28) = D_80081458[0];
        func_800C2E84(temp_s0, temp_a1, D_800D1200);
        func_80033CD8(temp_s0, D_80045340);
        func_800AAEFC();
        *(s16 *)(temp_s0 + 0x90) = 0;
        *(void **)(temp_s0 + 0x50) = D_800AB708;
        *(s16 *)(temp_s0 + 0x6A) = 0;
        *(u16 *)(temp_s1 + 2) = (u16) D_80083780.f2;
        *(u16 *)(temp_s1 + 6) = (u16) D_80083780.f6;
        *(s16 *)(temp_s1 + 0xA) = (s16) (D_80083780.fA - func_800AAE98(temp_s1));
    }
}
