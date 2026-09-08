#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D6FEC_0_pre {
    u16 unk_00;
} S_800D6FEC_0_pre;   /* the 0x2 bytes before arg0 in func_800D6FEC, addressed as arg0[-1] */

typedef struct S_800D6FEC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x18];
    void * unk_B0;
} S_800D6FEC_0;   /* arg0 in func_800D6FEC */

typedef struct S_800D6FEC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6FEC_1;   /* arg1 in func_800D6FEC */

typedef struct S_800D6FEC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6FEC_2;   /* temp_v1 in func_800D6FEC */


M2C_UNK func_800478B8();                     /* extern */
extern s32 D_800814A0[3];

/* Copy stored values, run the update, and flag completion when the count reaches zero. */
void func_800D6FEC(void *object, S_800D6FEC_1 *output, M2C_UNK update_arg) {
    u16 remaining;
    S_800D6FEC_2 *source;

    source = ((S_800D6FEC_0 *)object)->unk_B0;
    output->unk_02 = (u16) source->unk_02;
    output->unk_06 = (u16) source->unk_06;
    output->unk_0A = (u16) source->unk_0A;
    func_800478B8(update_arg);
    remaining = ((S_800D6FEC_0 *)object)->unk_96 - 1;
    ((S_800D6FEC_0 *)object)->unk_96 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_800D6FEC_0_pre *)object)[-1].unk_00 = (u16) (((S_800D6FEC_0_pre *)object)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
