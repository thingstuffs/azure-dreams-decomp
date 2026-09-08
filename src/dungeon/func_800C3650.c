#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8DB0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    s32 unk_14;
} S_800C8DB0_0;   /* arg0 in func_800C8DB0 */


M2C_UNK func_80099844();
s32 func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800DC1B8();
extern s32 D_800DCF20;
extern M2C_UNK D_800E1937;
extern M2C_UNK D_800E1A6D;

/* Attempts action 6 when the entity passes its state and threshold checks. */
s32 func_800C8DB0(S_800C8DB0_0 *entity, s16 threshold, s8 action_arg) {
    s16 remainder;
    s32 sample;
    u8 state_byte;

    if ((entity->unk_13 != 0) && ((entity->unk_08.at00.v & 0xFF0000FF) || (entity->unk_0E != 0))) {
        state_byte = entity->unk_0E;
        if (((u8) entity->unk_08.at00.v + entity->unk_08.at03.v + state_byte) != 0) {
            sample = func_800A6D30(state_byte) & 0xFFFF;
            if (entity->unk_03 != 0) {
                remainder = sample % entity->unk_03;
            } else {
                remainder = 0;
            }
            if ((remainder < threshold || threshold == 0xFF) && (s16)func_800A48F0(entity, 6, action_arg) >= 0) {
                func_80099844(entity, &D_800E1937);
                if (entity->unk_13 == 0) {
                    func_800DC1B8(D_800DCF20);
                }
                return 1;
            }
        }
    }
    if (entity->unk_14 & 0x4000) {
        func_80099844(entity, &D_800E1A6D);
    }
    return 0;
}
