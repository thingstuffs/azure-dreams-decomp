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
extern s32 plt_carry_item_del_ext();
extern s32 func_800C172C();
extern s8 D_800834B8[0x30];

/* Invokes func_800C172C for an eligible linked object with code 0xD04, then calls plt_carry_item_del_ext. */
void func_800A9D00(void) {
    s8 *stateBase;
    S_800A9D00_0 *precedingState;

    stateBase = D_800834B8;
    precedingState = stateBase - 0x20;
    if ((func_8009368C(stateBase, precedingState->unk_08,
                      precedingState->unk_0C) != 0) &&
        (((S_800A9D00_1 *)stateBase)->unk_2C != NULL) &&
        (((S_800A9D00_2 *)(((S_800A9D00_1 *)stateBase)->unk_2C))->unk_4C == 0xD04)) {
        func_800C172C();
    }
    plt_carry_item_del_ext();
}
