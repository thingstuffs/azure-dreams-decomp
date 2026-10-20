#include "common.h"

extern s16 query_lowered_transform_position();
extern void unlink_node_if_registered(void *);
extern void copy_indexed_motion_value_and_advance(void *, void *, s32);
extern void add_hex_20000_s_signed_offset_hex_14(void *record);

typedef void (*S_800A9C80_Callback)(void *, void *, s32);

/* Advances position and handles ground contact or continued motion. */
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context) {
    s32 x;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    u16 counter;
    S_800A9C80_Callback callback;

    x = *(s32 *)((u8 *)motion + 0x0);
    velocity_x = *(s32 *)((u8 *)motion + 0xC);
    velocity_y = *(s32 *)((u8 *)motion + 0x10);
    velocity_z = *(s32 *)((u8 *)motion + 0x14);
    x += velocity_x;
    *(s32 *)((u8 *)motion + 0x0) = x;
    *(s32 *)((u8 *)motion + 0x4) += velocity_y;
    *(s32 *)((u8 *)motion + 0x8) += velocity_z;
    if (query_lowered_transform_position(motion, velocity_y, velocity_z) < *(s16 *)((u8 *)motion + 0xA)) {
        *(s16 *)((u8 *)motion + 0xA) = query_lowered_transform_position(motion);
        counter = *(u16 *)((u8 *)entity + 0x90) - 1;
        *(u16 *)((u8 *)entity + 0x90) = counter;
        if ((s16)counter < 0) {
            unlink_node_if_registered(entity);
            callback = *(S_800A9C80_Callback *)((u8 *)entity + 0x54);
            callback(entity, motion, context);
            return;
        }
        copy_indexed_motion_value_and_advance(entity, motion, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(motion);
}
