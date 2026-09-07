#include "common.h"

/* If D_800847D0.flags1 bit 0x100 is set, raises event 0x71 via func_800553D4.
 * Then always calls func_8005B418, calls func_80055C50 for i in [0,4), and
 * finally dispatches func_8005A428 then func_8005A4B8. */
/* Sibling struct (matches src/w_8005440C.c / w_80054C58.c's S_800847D0 for the
 * fields touched here): flags1 at 0x0. */
typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u8 pad04[0x30];
} S_800847D0;

extern S_800847D0 D_800847D0;

extern void func_800553D4(s32 a0);
extern void func_8005B418();
extern void func_80055C50(s16 a0);
extern void func_8005A428(void);
extern void func_8005A4B8(void);

void func_80054228(void)
{
    s16 i;

    if (D_800847D0.flags1 & 0x100) {
        func_800553D4(0x71);
    }

    func_8005B418(0);

    for (i = 0; i < 4; i++) {
        func_80055C50(i);
    }

    func_8005A428();
    func_8005A4B8();
}
