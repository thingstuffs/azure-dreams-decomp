#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_80054C58.c, etc.) */

/* Canonical "task/timer object" struct (see src/w_800552C8.c). */


extern void func_800552C8(void);
extern void func_8005AF74(s16 a0);
extern void func_8005AFF4(s16 a0);
extern void func_800550E8(void);
extern void func_8005B070(s16 a0);
extern void func_8005B16C(s16 a0);

/* Clears, activates, or deactivates a status effect according to the supplied code. */
void func_800553D4(u8 code) {
    switch (code) {
    case 0x71:
        if (D_800847D0.flags00 & 0x1100) {
            D_800848F8.unk_08 = 0;
            func_800552C8();
            func_8005AF74(D_800847D0.unk_22);
            func_8005AFF4(D_800847D0.unk_22);
        }
        D_800848F8.unk_04 = 0;
        D_800847D0.flags00 &= ~0x100;
        D_800847D0.flags00 &= ~0x1000;
        D_800847D0.flags04 &= ~2;
        if (D_800847D0.unk_26 != -1) {
            func_800550E8();
        }
        break;
    case 0xE1:
        if (D_800847D0.flags00 & 0x100) {
            func_8005B070(D_800847D0.unk_22);
            D_800847D0.flags00 = (D_800847D0.flags00 & ~0x100) | 0x1000;
        }
        break;
    case 0xF1:
        if (D_800847D0.flags00 & 0x1000) {
            func_8005B16C(D_800847D0.unk_22);
            D_800847D0.flags00 = (D_800847D0.flags00 & ~0x1000) | 0x100;
        }
        break;
    }
}
