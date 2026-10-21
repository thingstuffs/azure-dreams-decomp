#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_D_800CFCB4.h"

#ifndef NULL
#define NULL 0
#endif


extern s32 add_motion_deltas_to_position(void *);
extern s32 process_the_item_index_available_report_success();
extern s32 initialize_entity_flags_transform_type_dependent_variant();
extern s32 dispatch_paired_table_values();
extern s32 D_800D09C8[];


/* Updates motion toward the target and resolves the entity when its countdown expires. */
void update_motion_toward_target_resolves_entity_countdown_expires(void *entity, s32 context, ObjectPosition *motion, s32 mode) {
    s32 result[5];
    s8 *linked_flag;
    s8 *clear_flag;
    u16 ticks_left;
    u32 delta_y;
    s32 offset_z;
    u8 slot;

    motion->velocity_x = (s32)((s32)(D_80083780.x.v - motion->x.v) / 2);
    delta_y = D_80083780.y.v - motion->y.v;
    motion->velocity_y = (s32)((s32)(delta_y + (delta_y >> 31)) >> 1);
    offset_z = motion->z.v + 0x200000;
    motion->velocity_z = (s32)((s32)(D_80083780.z.v - offset_z) / 2);
    add_motion_deltas_to_position(motion);
    ticks_left = ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 - 1;
    ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        slot = ((Rec_D_800CFCB4 *)entity)->unk_95;
        if (process_the_item_index_available_report_success(entity, context, motion, mode, result) != 0) {
            if (((Rec_D_800CFCB4 *)entity)->unk_4D.as_u8 == 0x13) {
                u8 *state_table = (u8 *)0x80010000;
                s32 record_index = state_table[slot * 4 + 0x983] & 0x3F;
                state_table[record_index * 0x54 + 0xAC4] = 1;
                linked_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (linked_flag != NULL) {
                    *linked_flag = 0;
                }
                D_800D09C8[0] = 0;
                clear_flag = linked_flag;
            } else {
                (*(s32 *)((u8 *)((slot * 4)) + (0x80010980))) = 0;
                clear_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (clear_flag != NULL) {
                    *clear_flag = 0;
                }
            }
            dispatch_paired_table_values(clear_flag);
            return;
        }
        motion->x.v = 0;
        motion->y.v = 0;
        motion->x.w.i = ((Rec_D_800CFCB4 *)entity)->unk_84;
        motion->y.w.i = ((Rec_D_800CFCB4 *)entity)->unk_86;
        initialize_entity_flags_transform_type_dependent_variant(entity, context, motion, mode);
    }
}
