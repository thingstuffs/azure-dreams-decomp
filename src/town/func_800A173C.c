#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009EE9C_arg0.h"



s32 func_800644B8();
void initialize_the_entity_s_action_copy_selected_state_hex_13();
void call_callee_80033_d_08_set_handler();
extern s32 D_800834B8[3];
extern s32 D_80093328;
extern M2C_UNK D_80093524[3];
extern s32 D_800CFCC4[3];


typedef struct S_8009EE9C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009EE9C_0;   /* arg2 in update_position_displacement_dispatch_active_entity_handler */


/* Update position and displacement, then dispatch the active entity handler. */
void update_position_displacement_dispatch_active_entity_handler(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, S_8009EE9C_0 *motion, s32 context) {
    s32 previous_pos;

    previous_pos = motion->unk_08;
    motion->unk_08 = (u32) (entity->unk_A0 + (func_800644B8(entity->unk_6C) << 6) + 0xFFFC0000);
    entity->unk_6C = (s16) ((u16) entity->unk_6C + 0x40);
    motion->unk_14 = (s32) (motion->unk_08 - previous_pos);
    if (D_800CFCC4[0] == entity_id) {
        if (D_800834B8[0] == &D_80093328) {
            initialize_the_entity_s_action_copy_selected_state_hex_13(entity, D_800CFCC4[0], motion, context);
            return;
        }
        if (D_800834B8[0] == D_80093524) {
            call_callee_80033_d_08_set_handler(entity, D_800CFCC4[0], motion, context);
        }
    }
}
