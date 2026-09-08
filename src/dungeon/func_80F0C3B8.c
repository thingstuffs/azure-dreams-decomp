#include "common.h"

extern void func_80044A50(void *);
extern void func_800BC318(void *);
extern void func_800AD594(void *, s32);

extern s16 D_80083460[];
extern u8 D_80170F74[];

/* Dims the effect and clears its object and owner state when flagged. */
void func_80173BB8(void *effect, s32 unused, void *primitive, void *owner)
{
    u8 intensity;
    void *effect_object;

    if (*(u8 *)((u8 *)effect + 0x9B) == 0) {
        intensity = *(u8 *)((u8 *)primitive + 0xC) - 0x10;
        *(u8 *)((u8 *)primitive + 0xE) = intensity;
        *(u8 *)((u8 *)primitive + 0xD) = intensity;
        *(u8 *)((u8 *)primitive + 0xC) = intensity;
        if (*(u16 *)((u8 *)primitive + 0x14) & 0xE000) {
            effect_object = (u8 *)effect - 0x20;
            func_80044A50(effect_object);
            func_800BC318(effect_object);
            func_800AD594(owner, 0x800);
            D_80083460[5]--;
            *(u32 *)((u8 *)primitive + 0xC) = 0;
            *(u8 *)((u8 *)owner + 0x6D) = 0;
            *(u16 *)((u8 *)owner + 0x46) &= 0x7FFF;
            *(void **)((u8 *)effect + 0x8C) = D_80170F74;
        }
    }
}
