#include "common.h"

extern u16 D_80013714[];
extern s32 D_80082EB8[];
extern s32 D_80083170[];
extern s32 D_800E296C[];
extern s32 D_800E4938[];

extern void func_800A56E0(u32);

/* Initialize the actor action state or signal that the action is blocked. */
void func_8008CF6C(void *actor, s32 unused_1, s32 unused_2, s32 action_value) {
    if (!(D_80013714[0] & 1)) {
        if (D_800E296C[0] & 0x200000) {
            if (D_80083170[0] & 0x80) {
                func_800A56E0(0x506);
                return;
            }
        } else {
            *(u8 *)((u8 *)actor + 0x9A) = 0x19;
            func_800A56E0(0x514);
            D_800E4938[0] = action_value;
            *(u8 *)((u8 *)actor + 0x9B) = 0;
            {
                s32 flags;

                flags = D_800E296C[0];
                *(s32 *)((u8 *)actor + 0x8C) = 0;
                D_80082EB8[0] = 0;
                ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                D_800E296C[0] = flags | 0x2000;
            }
        }
    }
}
