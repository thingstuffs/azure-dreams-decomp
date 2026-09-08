#include "common.h"
#include "records/Rec_func_8009EE9C_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800644B8();
M2C_UNK func_8009F1C0();
M2C_UNK func_8009F48C();
extern s32 D_800834B8[3];
extern M2C_UNK D_80093328;
extern M2C_UNK D_80093524[3];
extern s32 D_800CFCC4[3];


typedef struct S_8009EE9C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009EE9C_0;   /* arg2 in func_8009EE9C */


/* Update position and displacement, then dispatch the active entity handler. */
void func_8009EE9C(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, S_8009EE9C_0 *motion, M2C_UNK context) {
    s32 previous_pos;

    previous_pos = motion->unk_08;
    motion->unk_08 = (u32) (entity->unk_A0 + (func_800644B8(entity->unk_6C) << 6) + 0xFFFC0000);
    entity->unk_6C = (s16) ((u16) entity->unk_6C + 0x40);
    motion->unk_14 = (s32) (motion->unk_08 - previous_pos);
    if (D_800CFCC4[0] == entity_id) {
        if (D_800834B8[0] == &D_80093328) {
            func_8009F1C0(entity, D_800CFCC4[0], motion, context);
            return;
        }
        if (D_800834B8[0] == D_80093524) {
            func_8009F48C(entity, D_800CFCC4[0], motion, context);
        }
    }
}
