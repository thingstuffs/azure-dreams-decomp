#include "common.h"

typedef struct {
    void *unk0;
    u16 unk4;
} State;

extern void func_80024ADC(void) __attribute__((noreturn));
extern void func_800478B8(void *);
extern s32 D_800814A0[];

/* Updates effect motion and fading, marking completion when the timer expires. */
void func_818C3208(State *state, void *position, void *visual) {
    void *owner;
    u8 color;

    owner = state->unk0;
    *(u16 *)((u8 *)owner + 0xC) += 1;
    state->unk4 += 1;
    *(u16 *)((u8 *)visual + 0x1A) += 0x480;
    *(s32 *)((u8 *)position + 8) += 0xFFF60000;
    func_800478B8(visual);

    if ((s16)state->unk4 < 0x11) {
        color = *(u8 *)((u8 *)visual + 0xC);
        if (color != 0) {
            *(u8 *)((u8 *)visual + 0xC) = color - 0xC;
        }
        color = *(u8 *)((u8 *)visual + 0xD);
        if (color != 0) {
            *(u8 *)((u8 *)visual + 0xD) = color - 0xC;
        }
        color = *(u8 *)((u8 *)visual + 0xE);
        if (color != 0) {
            *(u8 *)((u8 *)visual + 0xE) = color - 0xC;
            func_80024ADC();
        }
        return;
    }

    *(u16 *)((u8 *)state - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    return;
}
