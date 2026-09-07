#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3_32;

extern s32 D_800814A0;

extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 func_800C648C(void *arg0);
extern void func_80033D08(void *arg0);
extern void func_800C6DAC(void);

void func_800C6CE4(void *a0, Vec3_32 *a1)
{
    void *sub = *(void **)((u8 *)a0 + 0x9C);
    Vec3_32 *vec = *(Vec3_32 **)((u8 *)sub - 0x18);

    if (func_800C648C(sub) == 0) {
        func_80033D08(a0);
        *(u16 *)((u8 *)a0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800C6DAC();
        return;
    }
    a1->x = vec->x + func_800644B8(*(s16 *)((u8 *)*(void **)((u8 *)a0 + 0x9C) + 0x72)) * 0x140;
    a1->y = vec->y + func_80064584(*(s16 *)((u8 *)*(void **)((u8 *)a0 + 0x9C) + 0x72)) * 0x140;
    a1->z = vec->z + (s32)0xFFE60000;
}
