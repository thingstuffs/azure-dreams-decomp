#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A0.h"

typedef struct S_800C5D80_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5D80_0;   /* arg1 in func_800C5D80 */


typedef struct S_800C5D80_2 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800C5D80_2;   /* arg0 in func_800C5D80; pointer addresses record offset 0x2 */

typedef struct S_800C5D80_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5D80_3;   /* global in func_800C5D80 */



M2C_UNK func_800478B8();                      /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;

void func_800C5D80(void *arg0, S_800C5D80_0 *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_v0;
    u8 temp_v1;

    arg1->unk_08 += arg1->unk_14;
    arg1->unk_14 += 0x2000;
    func_800478B8(arg2);
    temp_v1 = arg2->unk_0C.at00_u8.v - ((s32) arg2->unk_0C.at00_u8.v / (s16) ((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_12);
    arg2->unk_0C.at00_u8.v = temp_v1;
    arg2->unk_0C.at01_u8.v = temp_v1;
    arg2->unk_0C.at02_u8.v = temp_v1;
    temp_v0 = (u16) ((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_12 - 1;
    ((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_12 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        if (((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_0E == 0) {
            S_800C5D80_3 *global = &D_80083460;

            global->unk_0A = (u16) (global->unk_0A - 1);
        }
        ((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800C5D80_2 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        ((Rec_D_800814A0 *)(&D_800814A0))->unk_00 = (s32) (((Rec_D_800814A0 *)(&D_800814A0))->unk_00 | 0x8000);
    }
}

/* MECHANISM: Separate compound RMWs preserve retail's shared +0x14 load and v1 copy.
   A named D_80083460 base keeps +0xA as a displacement; the corrected u8 quotient
   expression restores the divide sequence, with cdk-G0 providing the retail schedule. */
