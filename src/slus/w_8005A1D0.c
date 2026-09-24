#include "common.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern void func_80059DAC(void);

/* Removes the first matching entry from D_800869C0, shifts later entries down, and calls func_80059DAC. */
void func_8005A1D0(u32 addr)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_800869C0[i].addr == addr) {
            for (; i < 16; i++) {
                D_800869C0[i].size = D_800869C0[i + 1].size;
                D_800869C0[i].addr = D_800869C0[i + 1].addr;
                if (D_800869C0[i].addr == 0) {
                    break;
                }
            }
            func_80059DAC();
            return;
        }
    }
}
