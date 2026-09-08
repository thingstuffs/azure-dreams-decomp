#include "common.h"

typedef struct {
    u8 bytes[12];
} Blob12;

extern void **D_80174CD8[];
extern u8 D_80045340[];
void *func_8003FC64(s32);
void func_8004491C(void *, void *);
extern s32 D_801723D0;
extern Blob12 D_80174AC8;

/* Creates and initializes an effect offset from the current object's position. */
void func_801724D4(void) {
    s32 *source_pos;
    u8 *effect;
    u8 *sprite;
    s32 *effect_pos;
    u8 *effect_state;

    source_pos = (s32 *)D_80174CD8[0][2];
    effect = (u8 *)func_8003FC64(0x212);
    if (effect != (void *)0) {
        effect_state = effect + 0x20;
        *(s16 *)(effect_state + 0x16) = 0x1E;
        *(s16 *)(effect_state + 0x18) = 0x1E;
        *(void **)(effect + 0x10) = &D_801723D0;
        func_8004491C(effect, D_80045340);
        sprite = *(u8 **)(effect + 0xC);
        *(s16 *)(sprite + 0x10) = 0x20;
        *(s16 *)(sprite + 6) = 0;
        *(u16 *)(sprite + 0x14) |= 0xC;
        effect_pos = *(s32 **)(effect + 8);
        effect_pos[0] = source_pos[0];
        effect_pos[1] = source_pos[1];
        effect_pos[2] = source_pos[2] + 0xFFC80000;
        sprite = *(u8 **)(effect + 0xC);
        *(s16 *)(sprite + 0x1E) = 0x400;
        *(s16 *)(sprite + 0x1C) = 0x400;
        *(u8 *)(sprite + 0xD) = 0x80;
        *(u8 *)(sprite + 0xC) = 0x80;
        *(u8 *)(sprite + 0xE) = 0;
        *(Blob12 *)(effect + 0x48) = D_80174AC8;
        *(void **)(sprite + 8) = effect + 0x48;
    }
}
