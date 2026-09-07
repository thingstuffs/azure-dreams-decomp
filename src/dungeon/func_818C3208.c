#include "common.h"

typedef struct {
    void *unk0;
    u16 unk4;
} State;

extern void func_80024ADC(void) __attribute__((noreturn));
extern void func_800478B8(void *);
extern s32 D_800814A0[];

void func_818C3208(State *arg0, void *arg1, void *arg2) {
    void *p;
    u8 v;

    p = arg0->unk0;
    *(u16 *)((u8 *)p + 0xC) += 1;
    arg0->unk4 += 1;
    *(u16 *)((u8 *)arg2 + 0x1A) += 0x480;
    *(s32 *)((u8 *)arg1 + 8) += 0xFFF60000;
    func_800478B8(arg2);

    if ((s16)arg0->unk4 < 0x11) {
        v = *(u8 *)((u8 *)arg2 + 0xC);
        if (v != 0) {
            *(u8 *)((u8 *)arg2 + 0xC) = v - 0xC;
        }
        v = *(u8 *)((u8 *)arg2 + 0xD);
        if (v != 0) {
            *(u8 *)((u8 *)arg2 + 0xD) = v - 0xC;
        }
        v = *(u8 *)((u8 *)arg2 + 0xE);
        if (v != 0) {
            *(u8 *)((u8 *)arg2 + 0xE) = v - 0xC;
            func_80024ADC();
        }
        return;
    }

    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    return;
}

/* MECHANISM: The void return ABI removes the seed's synthetic two-word value-return block,
   so the third byte's zero branch reaches the shared epilogue exactly.
   Held arg0/arg2 bases produce the 0x20 s1/s0 frame; noreturn preserves the retail tail j/store. */
