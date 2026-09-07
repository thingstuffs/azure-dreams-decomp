#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A9D00_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_800A9D00_0;   /* temp_v0 in func_800A9D00 */

typedef struct S_800A9D00_1 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800A9D00_1;   /* base in func_800A9D00 */

typedef struct S_800A9D00_2 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_800A9D00_2;   /* ((S_800A9D00_1 *)base)->unk_2C in func_800A9D00 */



extern s32 func_8009368C();
extern s32 func_80093744();
extern s32 func_800C172C();
extern s8 D_800834B8[0x30];

void func_800A9D00(void) {
    s8 *base;
    S_800A9D00_0 *temp_v0;

    base = D_800834B8;
    temp_v0 = base - 0x20;
    if ((func_8009368C(base, temp_v0->unk_08,
                      temp_v0->unk_0C) != 0) &&
        (((S_800A9D00_1 *)base)->unk_2C != NULL) &&
        (((S_800A9D00_2 *)(((S_800A9D00_1 *)base)->unk_2C))->unk_4C == 0xD04)) {
        func_800C172C();
    }
    func_80093744();
}

/* MECHANISM: Hold &D_800834B8 across the first call so it occupies s0,
   while deriving the two pre-base call arguments through a short-lived pointer. */
