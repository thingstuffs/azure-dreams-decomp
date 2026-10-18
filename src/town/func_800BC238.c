#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_800B9998_0 {
    u8 pad_00[0x66];
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    u8 pad_68[0x30];
    s8 * unk_98;
} S_800B9998_0;   /* arg0 in deactivate_object_triggered */

typedef struct S_800B9998_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B9998_2;   /* p1 in deactivate_object_triggered */

typedef struct S_800B9998_3 {
    u8 pad_00[0x1A];
    union { u16 s; u16 u; } unk_1A;   /* accessed as both */
} S_800B9998_3;   /* p2 in deactivate_object_triggered */


extern void func_80033D08(void *);
extern s32 classify_object_against_bounds(void *, void *);

/* Deactivate the object when triggered; otherwise update its spin from nearby motion and advance rotation. */
void deactivate_object_triggered(void *object, void *position, void *rotation) {
    u8 *position_data = position;
    u8 *rotation_data = rotation;
    s8 *active_flag;
    EntityRec *town_state;
    s32 dx;
    s32 dy;
    s32 near_x;
    s32 speed_sq;
    s32 position_y;
    s32 raw_speed;
    s32 angle_step;
    s32 t;

    if (classify_object_against_bounds(object, position) != 0) {
        active_flag = ((S_800B9998_0 *)object)->unk_98;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        func_80033D08(object);
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    raw_speed = ((S_800B9998_0 *)object)->unk_66.s;
    position_y = ((S_800B9998_0 *)object)->unk_66.u;
    if (position_y >= 0x100) {
        ((S_800B9998_0 *)object)->unk_66.s = raw_speed - 0x20;
    } else {
        if (position_y >= 0x10) {
            ((S_800B9998_0 *)object)->unk_66.s = raw_speed - 0x10;
        } else {
            ((S_800B9998_0 *)object)->unk_66.s = 0;
        }
    }
    town_state = &D_80083780;
    dx = town_state->x.w.i;
    dy = ((S_800B9998_2 *)position_data)->unk_02;
    position_y = ((S_800B9998_2 *)position_data)->unk_06;
    dx -= dy;
    dx = abs(dx);
    dx = (s16)dx;
    dy = town_state->y.w.i;
    near_x = dx < 0x81;
    dy -= position_y;
    dy = abs(dy);

    if (near_x && ((s16)dy < 0x81)) {
        speed_sq = (((Fixed1616 *)&town_state->unk_0C)->w.i * ((Fixed1616 *)&town_state->unk_0C)->w.i) +
              (((Fixed1616 *)&town_state->unk_10)->w.i * ((Fixed1616 *)&town_state->unk_10)->w.i);
        ((S_800B9998_0 *)object)->unk_66.s =
            ((S_800B9998_0 *)object)->unk_66.s +
            ((s32)(speed_sq + ((u32)speed_sq >> 31)) >> 1);
    }

    if (((S_800B9998_0 *)object)->unk_66.u >= 0x601) {
        ((S_800B9998_0 *)object)->unk_66.s = 0x600;
    }

    angle_step = ((S_800B9998_0 *)object)->unk_66.s + 0x80;
    ((S_800B9998_3 *)rotation_data)->unk_1A.s = ((S_800B9998_3 *)rotation_data)->unk_1A.s + angle_step;
    t = ((S_800B9998_3 *)rotation_data)->unk_1A.u;
    ((S_800B9998_3 *)rotation_data)->unk_1A.u = t & 0xFFF;

    return;
}
