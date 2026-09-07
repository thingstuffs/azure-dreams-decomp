#include "common.h"

/* Sibling struct (matches src/w_80054C58.c's S_800847D0 exactly for the
 * fields touched here): flags1 at 0x0, flags2 at 0x4. */
typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u8 pad08[0x2C];
} S_800847D0;

/* Opaque state-block struct: only its address is taken here (never
 * dereferenced), but sibling functions in this wave show a function-pointer
 * field at 0x0, an s32 flag/counter at 0x4, and an s16 timer at 0x8. Declared
 * >8 bytes to force %hi/%lo addressing. */
typedef struct S_800848F8 {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ u8 pad0A[0x36];
} S_800848F8;

extern S_800847D0 D_800847D0;
extern S_800848F8 D_800848F8;

extern void func_800550E8(void);
extern s32 func_80059D60(void);
extern s32 func_800545F4(S_800848F8 *a0);
extern void func_800553D4(s32 a0);
extern void func_80054538(S_800848F8 *a0);

/* Fires an event (func_800550E8) if flags2 bit 0x2 is set. Then, if flags1
 * bit 0x100 is set, checks a CD/task status via func_80059D60(): if it's 3,
 * or otherwise if func_800545F4 on D_800848F8 signals failure (-1), raises
 * event 0x71 via func_800553D4. Finally always dispatches func_80054538 on
 * D_800848F8. */
void func_8005440C(void) {
    if (D_800847D0.flags2 & 0x2) {
        func_800550E8();
    }

    if (D_800847D0.flags1 & 0x100) {
        if (func_80059D60() == 3 || func_800545F4(&D_800848F8) == -1) {
            func_800553D4(0x71);
        }
    }

    func_80054538(&D_800848F8);
}
