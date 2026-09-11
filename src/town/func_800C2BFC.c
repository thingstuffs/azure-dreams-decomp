#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_80100D98.h"

typedef struct S_800C035C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x6];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    s16 unk_12;
    u8 pad_14[0x8];
    void * unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x4];
    void * unk_54;
    s32 unk_58;
    s32 unk_5C;
} S_800C035C_0;   /* arg0 in func_800C035C */

typedef struct S_800C035C_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800C035C_1;   /* arg1 in func_800C035C */

typedef struct S_800C035C_2 {
    u8 pad_00[0x2E];
    u16 unk_2E;
    u8 pad_30[0x8];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
} S_800C035C_2;   /* temp_s5 in func_800C035C */

typedef struct S_800C035C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; volatile s16 u; volatile u16 p; } unk_C8;   /* accessed as both */
} S_800C035C_3;   /* temp_s3 in func_800C035C */

typedef struct S_800C035C_4 {
    s16 unk_00;
    s16 unk_02;
} S_800C035C_4;   /* temp_s4 in func_800C035C */

typedef struct S_800C035C_5 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_5;   /* ((temp_v1_6 * 2) + (s8 *) temp_s5) in func_800C035C */

typedef struct S_800C035C_6 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_6;   /* ((temp_s0 * 2) + (s8 *) temp_s5) in func_800C035C */

typedef struct S_800C035C_7 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_7;   /* ((temp_v1_9 * 2) + (s8 *) temp_s5) in func_800C035C */



typedef struct S_800C035C_10 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_10;   /* ((((S_800C035C_4 *)temp_s4)->unk_00 * 2) + (s8 *) temp_s5) in func_800C035C */


typedef struct {
    s32 w[6];
} Blk24;

typedef struct {
    s32 w[5];
} Blk20;

M2C_UNK func_80022F34();              /* extern */
M2C_UNK func_800239A0();     /* extern */
M2C_UNK func_80033B9C();              /* extern */
M2C_UNK change_map();                       /* extern */
M2C_UNK func_800489F4();     /* extern */
M2C_UNK func_80048AC8(void *, s32);             /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK reserve_tw_mon_load();     /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800953D0();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
M2C_UNK func_80095910();                   /* extern */
M2C_UNK func_800A48B0();           /* extern */
M2C_UNK func_800ABD74();                      /* extern */
s16 func_800C2AE8();                      /* extern */
extern void *jtbl_80089978[];
__asm__(".set jtbl_80089978, 0x80089978");
extern s32 D_800135B4;
__asm__(".set D_800135B4, 0x800135B4");
extern M2C_UNK D_8006CCF8;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80089960;
extern u8 D_800CFCEE;
extern M2C_UNK D_800FE490;
extern M2C_UNK D_80100D98;

/* Updates movement, jumping, course progress, and sprite orientation from player input. */
void func_800C035C(void *actor, S_800C035C_1 *motion, Rec_D_80082E80 *sprite) {
    Blk24 ground_probe;
    Blk20 event_params;
    s32 prev_stage;
    s16 course_type;
    s32 wait_stage;
    s32 stage_time;
    s32 active_stage;
    s16 ground_height;
    s16 view_angle;
    s32 speed;
    s32 sprite_dir;
    s32 angle_base;
    s32 angle_value;
    s32 motion_adjustment;
    s32 state;
    s32 held_buttons;
    register s32 angle_delta ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 heading_or_speed;
    s32 view_error;
    s32 turn_size;
    s32 motion_flags;
    u16 elapsed_time;
    S_800C035C_3 *controls;
    S_800C035C_4 *progress;
    S_800C035C_2 *course;

    controls = &D_80083160;
    course = ((S_800C035C_0 *)actor)->unk_54;
    progress = (s8 *)actor + 0x50;
    func_800953D0(motion);
    func_80095910(&D_800FE490);
    func_8009539C(motion);
    motion->unk_00 = (s32) (motion->unk_00 + ((S_800C035C_0 *)actor)->unk_58);
    motion->unk_04 = (s32) (motion->unk_04 + ((S_800C035C_0 *)actor)->unk_5C);
    ((S_800C035C_0 *)actor)->unk_58 = (s32) ((s32) ((S_800C035C_0 *)actor)->unk_58 >> 1);
    ((S_800C035C_0 *)actor)->unk_5C = (s32) ((s32) ((S_800C035C_0 *)actor)->unk_5C >> 1);
    ground_probe = *(Blk24 *) motion;
    course_type = course->unk_3C;
    if ((course_type == 2) || (course_type == 6)) {
        ground_probe.w[2] = 0xFE000000;
    }
    ground_height = func_800C2AE8(&ground_probe);
    if ((ground_height << 0x10) > 0) {
        ground_height = 0;
    }
    if ((controls->unk_10 & 0x20) && (((S_800C035C_0 *)actor)->unk_48 <= 0x200000)) {
        func_800ABD74(motion);
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (((S_800C035C_0 *)actor)->unk_48 + 0x80000);
    }
    if (controls->unk_10 & 0x40) {
        motion_adjustment = ((S_800C035C_0 *)actor)->unk_48;
        if (motion_adjustment >= (s32) 0xFFE00000) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (motion_adjustment + 0xFFF80000);
        }
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x20) {
        speed = ((S_800C035C_0 *)actor)->unk_48;
        if (speed < 0) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x20000);
        } else if (speed <= 0xFFFFF) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x18000);
        } else {
            goto apply_drag;
        }
    } else if (held_buttons & 0x40) {
        speed = ((S_800C035C_0 *)actor)->unk_48;
        if (speed > 0) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0xFFFE0000);
        } else if (speed > (s32) 0xFFF00000) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0xFFFE8000);
        } else {
            goto apply_drag;
        }
    }
    speed = ((S_800C035C_0 *)actor)->unk_48;
apply_drag:
    if (speed < (s32) 0xFFFF0000) {
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x10000);
    } else if (speed > 0x10000) {
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed - 0x10000);
    } else {
        ((S_800C035C_0 *)actor)->unk_48 = 0;
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x8000) {
        heading_or_speed = ((S_800C035C_0 *)actor)->unk_10.s + 0x20;
        goto wrap_heading;
    }
    if (held_buttons & 0x2000) {
        heading_or_speed = ((S_800C035C_0 *)actor)->unk_10.s + 0xFE0;
wrap_heading:
        ((S_800C035C_0 *)actor)->unk_10.s = (u16) (heading_or_speed & 0xFFF);
    }
    motion->unk_0C = (s32) (func_800644B8((s16) ((S_800C035C_0 *)actor)->unk_10.s) * ((s32) ((S_800C035C_0 *)actor)->unk_48 >> 0xC));
    motion->unk_10 = (s32) (func_80064584((s16) ((S_800C035C_0 *)actor)->unk_10.s) * ((s32) ((S_800C035C_0 *)actor)->unk_48 >> 0xC));
    angle_base = controls->unk_C8.s - 0x800;
    angle_value = ((S_800C035C_0 *)actor)->unk_10.u;
    angle_delta = angle_value - angle_base;
wrap_angle_delta:
    if (angle_delta >= 0x801) {
        angle_delta -= 0x1000;
        goto wrap_angle_delta;
    }
    if (angle_delta < -0x800) {
        angle_delta += 0x1000;
        goto wrap_angle_delta;
    }
    motion_adjustment = 0x30000;
    heading_or_speed = ((S_800C035C_0 *)actor)->unk_48;
    motion_adjustment |= 0xFFFF;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (heading_or_speed < 0) {
        heading_or_speed = 0 - heading_or_speed;
    }
    motion_adjustment = motion_adjustment < heading_or_speed;
    if (motion_adjustment && (controls->unk_08 & 0xA000)) {
        if (angle_delta < -0x180) {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x980;
        } else if (angle_delta >= 0x181) {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x680;
        } else if (angle_delta < 0) {
            view_angle = (u16) controls->unk_C8.s - 0x10;
        } else if (angle_delta > 0) {
            view_angle = (u16) controls->unk_C8.s + 0x10;
        } else {
            goto align_view;
        }
    } else {
        view_error = angle_delta;
        if (angle_delta < 0) {
            view_error = 0 - view_error;
        }
        if (view_error >= 8) {
            motion_adjustment = angle_delta >> 3;
            view_angle = (u16) controls->unk_C8.s + motion_adjustment;
        } else {
align_view:
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x800;
        }
    }
    controls->unk_C8.s = view_angle;
    controls->unk_C8.u = (s16) ((controls->unk_C8.p + 0x1000) & 0xFFF);
    do {
        turn_size = angle_delta;
    } while (0);
    if (angle_delta < 0) {
        turn_size = 0 - turn_size;
    }
    if (turn_size >= 0xA0) {
        if (ground_height <= (motion->unk_08.at02.v + 2)) {
            if (((S_800C035C_0 *)actor)->unk_48 > 0xC0000) {
                func_800ABD74(motion);
            }
        }
    }
    if (D_800CFCEE != 0) {
        motion->unk_14 = 0;
        func_800954F4(motion);
    }
    if (motion->unk_08.at02.v > ground_height) {
        motion->unk_08.at02.v = ground_height;
        if (motion->unk_14 >= 0) {
            motion->unk_14 = 0;
        }
        if (((S_800C035C_0 *)actor)->unk_4C & 1) {
            func_800ABD74(motion);
        }
        motion_adjustment = -2;
        motion_flags = ((S_800C035C_0 *)actor)->unk_4C & motion_adjustment;
    } else {
        motion_flags = ((S_800C035C_0 *)actor)->unk_4C | 1;
    }
    ((S_800C035C_0 *)actor)->unk_4C = motion_flags;
    if ((controls->unk_10 & 0x10) && (ground_height == motion->unk_08.at02.v)) {
        motion->unk_14 = -0x140000;
    }
    motion->unk_14 = (s32) (motion->unk_14 + 0x20000);
    {
        static void *const state_labels[] = {&&state_init, &&state_intro, &&state_wait, &&state_active, &&state_finish};
        (void) state_labels;
        state = ((S_800C035C_0 *)actor)->unk_08;
        if ((u32) state < 5) {
            goto *jtbl_80089978[state];
        }
        goto update_sprite;
    }
    {
state_init:
        ((S_800C035C_0 *)actor)->unk_10.s = 0xC00U;
        motion->unk_08.at00.v = 0;
        progress->unk_02 = 0;
        progress->unk_00 = 0;
        controls->unk_C8.s = 0xC00;
        goto stop_motion;
state_intro:
        controls->unk_C8.s = (s16) (((0x20 - course->unk_2E) << 5) + 0xC00);
        ((S_800C035C_0 *)actor)->unk_10.s = 0xC00U;
        goto stop_motion;
state_wait:
        controls->unk_C8.s = (s16) ((0x10 - course->unk_2E) << 5);
        wait_stage = progress->unk_00;
        if (wait_stage < 4) {
            ((S_800C035C_5 *)(((wait_stage * 2) + (s8 *) course)))->unk_30 =
                (u16) (((S_800C035C_5 *)(((wait_stage * 2) + (s8 *) course)))->unk_30 + 1);
        }
stop_motion:
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        goto update_sprite;
state_active:
        prev_stage = progress->unk_00;
        func_80022F34(motion, progress);
        func_800239A0(course, progress, 0);
        if (progress->unk_00 != prev_stage) {
            s32 *best_time;

            best_time = (s32 *)0x800135B4;
            ASM_KEEP(best_time);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            stage_time = ((S_800C035C_6 *)(((prev_stage * 2) + (s8 *) course)))->unk_30;
            if (stage_time < *best_time) {
                *best_time = (s32) stage_time;
                course->unk_38 = stage_time;
                func_80033B9C(0x596, best_time);
            }
        }
        active_stage = progress->unk_00;
        if (active_stage < 4) {
            elapsed_time = ((S_800C035C_7 *)(((active_stage * 2) + (s8 *) course)))->unk_30;
            ((S_800C035C_7 *)(((active_stage * 2) + (s8 *) course)))->unk_30 = (u16) (elapsed_time + 1);
            if ((s16) elapsed_time >= 0x7530) {
                ((S_800C035C_10 *)(((progress->unk_00 * 2) + (s8 *) course)))->unk_30 = 0x7530;
            }
        }
        goto update_sprite;
state_finish:
        event_params = *(Blk20 *) &D_80089960;
        reserve_tw_mon_load(2);
        change_map(&event_params);
        ((S_800C035C_0 *)actor)->unk_08 = (s16) ((u16) ((S_800C035C_0 *)actor)->unk_08 + 1);
    }
update_sprite:
    {
        register s32 sprite_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        angle_base = (s32) ((S_800C035C_0 *)actor)->unk_10.u - 0x1500;
        angle_value = controls->unk_C8.s;
        sprite_angle = angle_value - angle_base;
        sprite_dir = (sprite_angle & 0xFFF) >> 9;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    ((S_800C035C_0 *)actor)->unk_10.s = (u16) ((((S_800C035C_0 *)actor)->unk_10.s + 0x2000) & 0xFFF);
    if (((S_800C035C_0 *)actor)->unk_12 != sprite_dir) {
        if (sprite->unk_2C.as_s32 != 0) {
            func_800489F4(sprite, ((u8 *)((S_800C035C_0 *)actor)->unk_1C)[sprite_dir], sprite->unk_04.as_s8, 0);
        }
        ((S_800C035C_0 *)actor)->unk_12 = (s16) sprite_dir;
    }
    if (((u8 *)&D_8006CCF8)[sprite_dir] != 0) {
        sprite->unk_14.at00_u16.v |= 1;
    } else {
        sprite->unk_14.at00_u16.v &= 0xFFFE;
    }
    func_80048AC8(sprite, 0);
    func_800A48B0(&D_80100D98, motion);
    ((Rec_D_80100D98 *)(&D_80100D98))->unk_08 = 0;
}
