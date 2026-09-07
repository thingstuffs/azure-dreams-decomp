#include "common.h"

extern u16 D_80013714[];
extern s32 D_80082EB8[];
extern s32 D_80083170[];
extern s32 D_800E296C[];
extern s32 D_800E4938[];

extern void func_8008D008(void);
extern void func_800A56E0(u32);

void func_8008CF6C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (!(D_80013714[0] & 1)) {
        if (D_800E296C[0] & 0x200000) {
            if (D_80083170[0] & 0x80) {
                func_800A56E0(0x506);
                func_8008D008();
            }
        } else {
            *(u8 *)((u8 *)arg0 + 0x9A) = 0x19;
            func_800A56E0(0x514);
            D_800E4938[0] = arg3;
            *(u8 *)((u8 *)arg0 + 0x9B) = 0;
            {
                s32 flags;

                flags = D_800E296C[0];
                *(s32 *)((u8 *)arg0 + 0x8C) = 0;
                D_80082EB8[0] = 0;
                ASM_KEEP(flags);   /* MATCH pin: retail register colouring depends on it */
                D_800E296C[0] = flags | 0x2000;
            }
        }
    }
}

/* MECHANISM: The inherited CFG naturally preserves the 0x20 frame and s0/s1/s2 holds.
   A short-lived flags split pins the D_800E296C reload to v0; ASM_KEEP after both
   zero stores delays ori until retail word 37 while the D_80082EB8 page uses v1. */
