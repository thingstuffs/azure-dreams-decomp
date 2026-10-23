#include "common.h"

extern s32 select_object_setup_path(void *object, s32 request_data, s32 request_param, s32 check_param);
extern s32 rsin(s32 angle);
extern s32 rcos(s32 angle);
extern s32 *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(void *box_a, void *box_b);
extern void initialize_object_from_context(void *object, void *unusedArg, s32 initValue);

extern u8 D_800CFCB4[];

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Updates turning motion, applies a position adjustment, and checks the timer. */
void update_turning_motion_and_timer(void *actor, void *position, s32 update_param, s32 check_param) {
    s32 *adjustment;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(actor, (s32)position, update_param, check_param) != 0) {
        return;
    }

    angle = U16_AT(actor, 0x86);
    U16_AT(actor, 0x86) = angle - 0x40;
    S16_AT(actor, 0x72) = angle - 0x440;

    U16_AT(position, 2) = U16_AT(actor, 0x84) +
        rsin(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84));
    U16_AT(position, 6) = U16_AT(actor, 0x86) +
        rcos(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84)) -
        U16_AT(actor, 0x84);

    adjustment = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(actor, D_800CFCB4);
    if (adjustment != 0) {
        axis = adjustment[0];
        if (axis != 2) {
            if (axis == 0) {
                S32_AT(position, 0) -= adjustment[1];
            } else if (axis == 1) {
                S32_AT(position, 4) -= adjustment[1];
            }
            initialize_object_from_context(actor, position, update_param);
            return;
        }
    }

    timer = U16_AT(actor, 0x6C) - 1;
    U16_AT(actor, 0x6C) = timer;
    if ((s32)(timer << 16) <= 0) {
        initialize_object_from_context(actor, position, update_param);
    }
}
