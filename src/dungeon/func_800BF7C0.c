#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800C4F20_10 {
    u8 pad_00[0x1C];
    void * unk_1C;
    u8 pad_20[0x4];
    void * unk_24;
} S_800C4F20_10;   /* arg0 in func_800C4F20 */

typedef struct S_800C4F20_11 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x70];
    s16 unk_88;
} S_800C4F20_11;   /* ((S_800C4F20_10 *)arg0)->unk_24 in func_800C4F20 */

typedef struct S_800C4F20_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4F20_12;   /* ((S_800C4F20_10 *)arg0)->unk_1C in func_800C4F20 */


typedef struct S_800C4F20_0_pre {
    u16 unk_00;
} S_800C4F20_0_pre;   /* the 0x2 bytes before arg0 in func_800C4F20, addressed as arg0[-1] */

typedef struct S_800C4F20_0 {
    u8 pad_00[0x20];
    void * unk_20;
    void * unk_24;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x2];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
} S_800C4F20_0;   /* arg0 in func_800C4F20 */

typedef struct S_800C4F20_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C4F20_1;   /* arg2 in func_800C4F20 */

typedef struct S_800C4F20_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_2;   /* temp_a1_2 in func_800C4F20 */

typedef struct S_800C4F20_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_3;   /* tail_ptr in func_800C4F20 */

typedef struct S_800C4F20_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C4F20_5;   /* arg1 in func_800C4F20 */

typedef struct S_800C4F20_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C4F20_6;   /* (void *) c2_v0 in func_800C4F20 */

typedef struct S_800C4F20_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_7;   /* temp_a1_4 in func_800C4F20 */

typedef struct S_800C4F20_8 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C4F20_8;   /* temp_a0_7 in func_800C4F20 */


s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
M2C_UNK func_800A56E0();

/* Updates an object's staged scale and position animation. */
void func_800C4F20(void *anim, S_800C4F20_5 *position, S_800C4F20_1 *transform) {
    s16 exit_mode;
    s16 move_ticks;
    s16 rise_ticks;
    s16 grow_ticks;
    s16 grow_left;
    s16 orbit_left;
    s16 move_left;
    s16 finish_left;
    s32 state_or_mode;
    s16 shrink_ticks;
    s32 height_delta;
    s32 target_y;
    s32 target_x;
    s32 orbit_offset;
    s32 x_delta;
    u16 grow_scale;
    u16 grown_scale;
    u16 grow_height;
    u16 shrink_scale;
    u16 shrunk_scale;
    u16 start_scale;
    u16 next_scale;
    u16 stretch_height;
    u16 end_scale;
    u16 final_scale;
    S_800C4F20_8 *owner;
    S_800C4F20_2 *grow_target;
    S_800C4F20_7 *shrink_target;
    EntityRec *orbit_center;

    state_or_mode = ((S_800C4F20_0 *)anim)->unk_28.s;
    switch (state_or_mode) {
    case 0:
        grow_ticks = ((S_800C4F20_0 *)anim)->unk_2A;
        if (grow_ticks != 0) {
            grow_scale = transform->unk_1E;
            grown_scale = grow_scale + ((s32) (0x1000 - grow_scale) / grow_ticks);
            grow_height = transform->unk_20;
            transform->unk_1E = grown_scale;
            transform->unk_1C = grown_scale;
            transform->unk_20 = (u16) (grow_height + ((s32) (0x1000
                - grow_height) / (s16) ((S_800C4F20_0 *)anim)->unk_2A));
            grow_target = ((S_800C4F20_0 *)anim)->unk_20;
            start_scale = grow_target->unk_1E;
            next_scale = start_scale + ((s32) (0x400 - start_scale) / (s16) ((S_800C4F20_0 *)anim)->unk_2A);
            grow_target->unk_1E = next_scale;
            grow_target->unk_1C = next_scale;
            ((S_800C4F20_0 *)anim)->unk_32 = (s16) ((u16) ((S_800C4F20_0 *)anim)->unk_32
                - ((s16) ((S_800C4F20_0 *)anim)->unk_32 / (s16) ((S_800C4F20_0 *)anim)->unk_2A));
        }
        grow_left = (u16) ((S_800C4F20_0 *)anim)->unk_2A - 1;
        ((S_800C4F20_0 *)anim)->unk_2A = grow_left;
        if ((grow_left << 0x10) > 0) {
            break;
        }
        transform->unk_1E = 0x1000U;
        transform->unk_1C = 0x1000U;
        transform->unk_20 = 0x1000U;
        {
            S_800C4F20_3 *target_transform = ((S_800C4F20_0 *)anim)->unk_20;
            target_transform->unk_1E = 0x800U;
            target_transform->unk_1C = 0x800U;
        }
        ((S_800C4F20_0 *)anim)->unk_32 = 0;
        ((S_800C4F20_0 *)anim)->unk_2A = 0x20;
        ((S_800C4F20_0 *)anim)->unk_28.s = (s16) (((S_800C4F20_0 *)anim)->unk_28.u + 1);
        break;
    case 1:
        orbit_offset = func_80064584(((S_800C4F20_0 *)anim)->unk_2E);
        orbit_center = &D_80083780;
        target_x = orbit_center->x.w.i + (orbit_offset >> 6);
        target_y = orbit_center->y.w.i + (func_800644B8(((S_800C4F20_0 *)anim)->unk_2E) >> 6);
        x_delta = target_x - position->unk_02;
        if (x_delta < 0) {
            x_delta += 3;
        }
        position->unk_02 = (s16) ((u16) position->unk_02 + (x_delta >> 2));
        position->unk_06 = (s16) ((u16) position->unk_06 + ((s32) (target_y - position->unk_06) / 4));
        orbit_offset = (func_800644B8(((S_800C4F20_0 *)anim)->unk_2C << 5, target_y) >> 6) + 0x40;
        height_delta = orbit_center->z.w.i - position->unk_0A;
        position->unk_0A = (s16) ((u16) position->unk_0A + ((s32) (height_delta - orbit_offset) / 4));
        ((S_800C4F20_0 *)anim)->unk_2E = (s16) ((u16) ((S_800C4F20_0 *)anim)->unk_2E + 0x40
            + (func_80069EF8(height_delta) & 0x1F));
        exit_mode = ((S_800C4F20_0 *)anim)->unk_36;
        if (exit_mode == 0) {
            break;
        }
        orbit_left = (u16) ((S_800C4F20_0 *)anim)->unk_2A - 1;
        ((S_800C4F20_0 *)anim)->unk_2A = orbit_left;
        if ((orbit_left << 0x10) > 0) {
            break;
        }
        state_or_mode = exit_mode;
        if (state_or_mode == 1 || state_or_mode == 3) {
            ((S_800C4F20_0 *)anim)->unk_2A = 0x10;
            ((S_800C4F20_0 *)anim)->unk_28.s = (s16) (((S_800C4F20_0 *)anim)->unk_28.u + 1);
        } else {
            ((S_800C4F20_0 *)anim)->unk_2A = 0x20;
            ((S_800C4F20_0 *)anim)->unk_28.s = (s16) ((u16) ((S_800C4F20_0 *)anim)->unk_28.s + 0x10);
            func_800A56E0(0x518);
        }
        break;
    case 2:
        move_ticks = ((S_800C4F20_0 *)anim)->unk_2A;
        if (move_ticks != 0) {
            s32 x_work;
            s32 x_step;

            x_work = (s32) ((S_800C4F20_0 *)anim)->unk_20;
            x_step = ((S_800C4F20_6 *)((void *) x_work))->unk_24;
            x_work = position->unk_02;
            x_step <<= 6;
            x_work -= 0x20;
            x_step -= x_work;
            x_step /= move_ticks;
            position->unk_02 = (s16) ((u16) position->unk_02 + x_step);
            {
                s32 y_work;
                s32 y_step;

                y_work = (s32) ((S_800C4F20_0 *)anim)->unk_20;
                height_delta = ((S_800C4F20_0 *)anim)->unk_2A;
                y_step = ((S_800C4F20_6 *)((void *) y_work))->unk_25;
                y_work = position->unk_06;
                y_step <<= 6;
                y_work -= 0x20;
                y_step -= y_work;
                y_step /= height_delta;
                position->unk_06 = (s16) ((u16) position->unk_06 + y_step);
            }
            position->unk_0A = (s16) ((u16) position->unk_0A
                + ((s32) (((S_800C4F20_11 *)(((S_800C4F20_10 *)anim)->unk_24))->unk_88
                - position->unk_0A) / (s16) ((S_800C4F20_0 *)anim)->unk_2A));
        }
        move_left = (u16) ((S_800C4F20_0 *)anim)->unk_2A - 1;
        ((S_800C4F20_0 *)anim)->unk_2A = move_left;
        if ((move_left << 0x10) > 0) {
            break;
        }
        ((S_800C4F20_0 *)anim)->unk_2A = 0x10;
        ((S_800C4F20_0 *)anim)->unk_28.s = (s16) (((S_800C4F20_0 *)anim)->unk_28.u + 1);
        break;
    case 3:
        shrink_ticks = ((S_800C4F20_0 *)anim)->unk_2A;
        if (shrink_ticks != 0) {
            shrink_scale = transform->unk_1E;
            shrunk_scale = shrink_scale - ((s32) shrink_scale / shrink_ticks);
            transform->unk_1E = shrunk_scale;
            transform->unk_1C = shrunk_scale;
            stretch_height = transform->unk_20;
            transform->unk_20 = (u16) (stretch_height + ((s32) (0x2000
                - stretch_height) / (s16) ((S_800C4F20_0 *)anim)->unk_2A));
            shrink_target = ((S_800C4F20_0 *)anim)->unk_20;
            end_scale = shrink_target->unk_1E;
            final_scale = end_scale + ((s32) (0x1000 - end_scale) / (s16) ((S_800C4F20_0 *)anim)->unk_2A);
            shrink_target->unk_1E = final_scale;
            shrink_target->unk_1C = final_scale;
            ((S_800C4F20_0 *)anim)->unk_32 = (s16) ((u16) ((S_800C4F20_0 *)anim)->unk_32 + ((s32) (0x400
                - ((S_800C4F20_0 *)anim)->unk_32) / (s16) ((S_800C4F20_0 *)anim)->unk_2A));
        }
        goto tick_finish;
    case 17:
        rise_ticks = ((S_800C4F20_0 *)anim)->unk_2A;
        if (rise_ticks != 0) {
            position->unk_0A = (s16) ((u16) position->unk_0A + ((s32) (-0x400 - position->unk_0A) / rise_ticks));
        }
tick_finish:
        finish_left = (u16) ((S_800C4F20_0 *)anim)->unk_2A - 1;
        ((S_800C4F20_0 *)anim)->unk_2A = finish_left;
        if ((finish_left << 0x10) > 0) {
            break;
        }
        owner = ((S_800C4F20_0 *)anim)->unk_24;
        owner->unk_14 = (s32) (owner->unk_14 & 0xFFEFFFFF);
        ((S_800C4F20_0_pre *)anim)[-1].unk_00 = (u16) (((S_800C4F20_0_pre *)anim)[-1].unk_00 | 0x8000);
        (*(s32 *)&objectFlagBlock.flags) = (s32) (objectFlagBlock.flags | 0x8000);
        return;
    }
    if (((S_800C4F20_11 *)(((S_800C4F20_10 *)anim)->unk_24))->unk_14 & 0x100000) {
        ((S_800C4F20_12 *)(((S_800C4F20_10 *)anim)->unk_1C))->unk_02 = (u16) position->unk_02;
        ((S_800C4F20_12 *)(((S_800C4F20_10 *)anim)->unk_1C))->unk_06 = (u16) position->unk_06;
        ((S_800C4F20_12 *)(((S_800C4F20_10 *)anim)->unk_1C))->unk_0A = (u16) position->unk_0A;
    }
    ((S_800C4F20_0 *)anim)->unk_2C = (s16) ((u16) ((S_800C4F20_0 *)anim)->unk_2C + 1);
    transform->unk_1A = (u16) (transform->unk_1A - 0x80);
    return;
}
