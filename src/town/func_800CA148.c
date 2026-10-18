#include "common.h"

extern s32 *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(void *object, void *ptr);
extern void install_stored_value_handler(void *object, void *position, s32 update_arg);
extern void func_800C7C3C(void *object, void *position, s32 update_arg);
extern void clear_mother_event_record_field(void *object, void *position, s32 update_arg);

extern u8 D_800CFCB4[];
extern s32 D_80113220[];

/* Applies a motion offset or interpolates the position toward the object coordinates. */
void apply_mother_event_motion_offset(void *object, void *position, s32 update_arg) {
    s32 *motion_entry;
    s32 state;
    s32 frames_left;

    motion_entry = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, D_800CFCB4);
    if (motion_entry != 0) {
        state = motion_entry[0];
        if (state != 2) {
            if (state == 0) {
                ((s32 *)position)[0] -= motion_entry[1];
            } else if (state == 1) {
                ((s32 *)position)[1] -= motion_entry[1];
            }
            func_800C7C3C(object, position, update_arg);
            return;
        }
    }

    frames_left = --D_80113220[0];
    if (frames_left <= 0) {
        install_stored_value_handler(object, position, update_arg);
        clear_mother_event_record_field(object, position, update_arg);
        *(u16 *)((u8 *)position + 2) = *(u16 *)((u8 *)object + 0x84);
        *(u16 *)((u8 *)position + 6) = *(u16 *)((u8 *)object + 0x86);
        return;
    }

    *(u16 *)((u8 *)position + 2) +=
        ((s16)*(u16 *)((u8 *)object + 0x84) -
         *(s16 *)((u8 *)position + 2)) / frames_left;
    *(u16 *)((u8 *)position + 6) +=
        ((s16)*(u16 *)((u8 *)object + 0x86) -
         *(s16 *)((u8 *)position + 6)) / frames_left;
}
