#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80083460.h"

s32 func_80042900(void *, s32);
s32 func_800A1C58(void *);
void func_800A1D4C(void *, s32);
void func_800A56E0(s32);
void func_800C77D0(void *, s32, s32, s32);
extern u16 D_80013714;
extern s32 D_8007359C;
extern s8 D_80080A88;
extern s8 D_80080AA0;
extern M2C_UNK D_80083460;
extern s32 D_800E296C;


typedef struct S_800AAB10_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s32 unk_0C;
} S_800AAB10_0;   /* state in func_800AAB10 */


typedef struct S_800AAB10_2_pre {
    u16 unk_00;
    u8 pad_02[0x12];
} S_800AAB10_2_pre;   /* the 0x14 bytes before ((temp_a0 * 0x14) + D_8007359C) in func_800AAB10, addressed as ((temp_a0 * 0x14) + D_8007359C)[-1] */


/* Processes the selected record, checks eligibility, and clears completed state. */
s32 func_800AAB10(s32 buffer_addr, M2C_UNK source, M2C_UNK unused, Rec_D_800E3D7C *record) {
    s32 eligible;
    u8 type_id;
    u8 *state;

    eligible = 0;
    if (D_800E296C & 0x100000) {
        state = (u8 *)&D_80083460;
        if (((S_800AAB10_0 *)state)->unk_0C != 0) {
            if (((S_800AAB10_0 *)state)->unk_0C == record) {
                if (((S_800AAB10_0 *)state)->unk_0A == 0) {
                    if (!(((S_800AAB10_0 *)state)->unk_02 & 8)) {
                        func_800C77D0((void *)(buffer_addr - 0x20), source, 8, 0x300);
                        func_800A1D4C(record, 1);
                        func_800A56E0(0x201);
                        if (!(D_80013714 & 2)) {
                            D_80080AA0 = 1;
                            D_80080A88 = 0;
                        }
                        if (!(record->unk_54.as_s32 & 0x800000) && (record->unk_14.as_s32 & 0x4000)) {
                            type_id = record->unk_10.at03_u8.v;
                            if ((((S_800AAB10_2_pre *)(((type_id * 0x14) + D_8007359C)))[-1].unk_00 & 0x80) && (type_id >= 2U) && ((u8) record->unk_10.at01_u8.v >= 0x14U) && !(record->unk_1C.as_s32 & 0x228) && ((func_80042900(record, 0x18) << 0x10) == 0)) {
                                eligible = 1;
                            }
                        }
                        if ((func_800A1C58(record) << 0x10) == 0) {
                            goto clear_state;
                        }
                        goto return_zero;
                    }
                }
            }
            return 0;
        }
        goto return_zero;
    }
    goto return_result;
return_zero:
    return 0;
clear_state:
    ((Rec_D_80083460 *)(&D_80083460))->unk_0C = 0;
return_result:
    return eligible;
}
