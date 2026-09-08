#include "common.h"

typedef struct {
    u8 pad00[0x14];
    u16 unk14;
} SubEnt;

typedef struct {
    SubEnt *unk00;
    u8 unk04;
} Arg0Ent;

typedef struct {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 pad0F[0x14 - 0xF];
    u16 unk14;
    u8 pad16[0x1C - 0x16];
    u16 unk1C;
    u16 unk1E;
} Arg2Ent;

typedef struct {
    s32 value;
    s32 pad[2];
} LargeS32;

extern LargeS32 D_800814A0;
extern s32 D_800DEDB0[3];

extern void func_800478B8(void *a0);
extern void func_8003DB94(void *a0, void *a1, s16 a2);
extern void func_80024244(void) __attribute__((noreturn));

/* Grow and fade the effect, advancing or finishing it when its status flags are set. */
void func_8186298C(Arg0Ent *state, void *unused, Arg2Ent *effect)
{
    u16 size;
    u8 brightness;

    state->unk00->unk14++;
    size = effect->unk1E + 0x400;
    brightness = effect->unk0E - 4;
    effect->unk1E = size;
    effect->unk1C = size;
    effect->unk0E = brightness;
    effect->unk0D = brightness;
    effect->unk0C = brightness;
    func_800478B8(effect);

    if (effect->unk14 & 0x6000) {
        if (state->unk04 != 0) {
            *(u16 *)((u8 *)state - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
            func_80024244();
            return;
        } else {
            __asm__ __volatile__("");
            func_8003DB94(effect, D_800DEDB0, 4);
            state->unk04 = 1;
        }
    }
}
