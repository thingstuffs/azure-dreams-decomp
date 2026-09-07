#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8003DB94();  /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_800DECF8;

typedef struct S_818A4B40_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_818A4B40_0;   /* arg0 in func_818A4B40 */

typedef struct S_818A4B40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818A4B40_1;   /* temp_v1 in func_818A4B40 */

typedef struct S_818A4B40_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818A4B40_2;   /* arg1 in func_818A4B40 */


void func_818A4B40(S_818A4B40_0 *arg0, S_818A4B40_2 *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_s0;
    s32 temp_v0_2;
    s32 var_s0;
    u16 temp_v0;
    S_818A4B40_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    temp_v0 = arg0->unk_04 + arg0->unk_06;
    arg0->unk_04 = temp_v0;
    if ((s16) temp_v0 < -0x80) {
        temp_v0_2 = rand();
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = temp_v0_2 + 0xFFF;
        }
        temp_s0 = temp_v0_2 - ((var_s0 >> 0xC) << 0xC);
        arg1->unk_02 = (s16) (arg0->unk_08 + ((s32) (func_800644B8(temp_s0) * 2) >> 8));
        arg1->unk_06 = (s16) (arg0->unk_0A + ((s32) (func_80064584(temp_s0) * 2) >> 8));
        arg0->unk_04 = (u16) (arg0->unk_04 + 0x80);
        arg0->unk_06 = (u16) (-6 - (rand() % 5));
    }
    arg1->unk_0A = (s16) (arg0->unk_0C + arg0->unk_04);
    func_800478B8(arg2);
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(arg2, &D_800DECF8, 0);
    }
}
