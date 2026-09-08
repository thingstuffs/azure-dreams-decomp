#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;


typedef struct S_80175BE0_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x18];
    u16 unk_B4;
} S_80175BE0_1;   /* arg0 in func_80175BE0 */


/* Reset motion and transfer the pending amount after the entity checks pass. */
void func_80175BE0(S_80175BE0_1 *state, Rec_D_800E3D7C *motion, M2C_UNK unused, void *entity) {
    ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, motion, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            state->unk_8C = 0;
            state->unk_9A = 0x18;
            state->unk_9B = 0;
            state->unk_96 = 0;
            motion->unk_14.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
            motion->unk_0C.as_s32 = 0;
            state->unk_92 = (u16) (state->unk_92 + ((Rec_D_800E3D7C *)entity)->unk_88.as_u16);
            state->unk_B4 = (u16) ((Rec_D_800E3D7C *)entity)->unk_88.as_u16;
            ((Rec_D_800E3D7C *)entity)->unk_88.as_u16 = 0U;
            state->unk_98 = (u16) (state->unk_98 | 8);
            func_800A4ACC(entity);
            ((Rec_D_800E3D7C *)entity)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_6D.as_u8 - 1);
        }
    }
}
