#include "common.h"

typedef struct S_800BC8D0_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BC8D0_0;   /* arg2 in func_800BC8D0 */

typedef struct S_800BC8D0_1_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BC8D0_1_pre;   /* the 0x10 bytes before arg0 in func_800BC8D0, addressed as arg0[-1] */

typedef struct S_800BC8D0_1 {
    u8 pad_00[0x48];
    void * unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    u8 pad_54[0x4C];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
} S_800BC8D0_1;   /* arg0 in func_800BC8D0 */



extern void func_8003DB94(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F104(void *, s32, void *);
extern u8 D_80045340[];
extern u8 D_80089634[];
extern u8 D_800BE0D4[];
extern s32 D_800D20E8[];
extern u8 D_800D20F4[];

/* Initializes the object with default data and updates its associated state. */
void func_800BC8D0(void *object, s32 init_arg, S_800BC8D0_0 *state)
{
    s32 *defaults;

    state->unk_14 |= 0x1C;
    ((S_800BC8D0_1_pre *)object)[-1].unk_00 = D_800BE0D4;
    ((S_800BC8D0_1 *)object)->unk_50 = 0;
    ((S_800BC8D0_1 *)object)->unk_48 = D_80089634;
    func_8004491C((u8 *)object - 0x20, D_80045340);

    defaults = D_800D20E8;
    ((S_800BC8D0_1 *)object)->unk_A0 = defaults[0];
    ((S_800BC8D0_1 *)object)->unk_A4 = defaults[1];
    ((S_800BC8D0_1 *)object)->unk_A8 = defaults[2];
    func_8008F104(object, init_arg, D_800D20F4);
    func_8003DB94(state, defaults[2], 0);
}
