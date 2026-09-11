#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80023260_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    u8 pad_14[0x4];
    union { volatile u16 s; s16 u; u16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x4];
    s16 unk_2A;
} S_80023260_0;   /* arg0 in func_80023260 */

typedef struct S_80023260_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80023260_1;   /* arg1 in func_80023260 */


typedef struct S_80023260_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u16 unk_06;
    u8 pad_08[0x6];
    u16 unk_0E;
} S_80023260_3;   /* temp_s2 in func_80023260 */

typedef struct S_80023260_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80023260_4;   /* temp_s5 in func_80023260 */

typedef struct S_80023260_5 {
    u8 pad_00[0x3C];
    s16 unk_3C;
} S_80023260_5;   /* ((((S_80023260_0 *)arg0)->unk_24 * 2) + temp_fp) in func_80023260 */


M2C_UNK func_800211C4();      /* extern */
M2C_UNK func_80022F34();              /* extern */
M2C_UNK func_800239A0();            /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();              /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800ABD74();                 /* extern */
s16 func_800C2AE8();                      /* extern */
typedef struct {
    void *ptr;
    s16 field4;
    u16 flags;
    s16 field8;
    s16 padA;
} Record12;

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} Stack24;

extern Record12 D_800242D8[];
extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_800D2388[];

/* Updates path following, turning, sprite state, and ground movement. */
void func_80023260(void *actor, void *motion, void *sprite) {
    s16 target_x;
    s16 steer_y;
    s16 target_y;
    s16 steer_x;
    s16 ground_height;
    s32 state;
    s16 pos_y;
    s16 pos_x;
    s16 turn_bias;
    s32 damped_bias;
    s32 surface_kind;
    s32 turn_limit;
    s32 abs_bias;
    s32 bias_step;
    s32 heading_error;
    s32 model_base;
    s32 path_flag;
    s32 path_speed;
    s32 speed;
    s32 idle_state;
    s32 offset_x;
    register s32 offset_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 heading;
    s32 path_heading;
    s32 final_state;
    s32 sprite_config;
    s32 angle_delta;
    s32 turn_step;
    s32 reached_point;
    s32 distance_y;
    s32 distance_x;
    u16 old_state;
    u16 path_ticks;
    s32 path_flags;
    s16 clamp_value;
    Record12 *paths;
    void *position_ref;
    void *waypoint;
    void *actor_ref;
    u8 *directions;

    actor_ref = actor;
    paths = D_800242D8;
    model_base = ((S_80023260_0 *)actor)->unk_00;
    waypoint = paths[((S_80023260_0 *)actor)->unk_22].ptr + (((S_80023260_0 *)actor)->unk_1C * 8);
    func_800478B8(sprite);
    position_ref = actor + 0x14;
    func_80022F34(motion, position_ref);
    func_800239A0(model_base, position_ref, ((S_80023260_0 *)actor)->unk_24);
    func_8009539C(motion);
    reached_point = 0;
    ((S_80023260_1 *)motion)->unk_00.at00.v = (s32) (((S_80023260_1 *)motion)->unk_00.at00.v + ((S_80023260_0 *)actor)->unk_0C.s);
    ((S_80023260_1 *)motion)->unk_04.at00.v = (s32) (((S_80023260_1 *)motion)->unk_04.at00.v + ((S_80023260_0 *)actor)->unk_10.s);
    offset_x = ((S_80023260_0 *)actor)->unk_0C.u;
    offset_y = ((S_80023260_0 *)actor)->unk_10.u;
    old_state = ((S_80023260_0 *)actor)->unk_18.s;
    ((S_80023260_0 *)actor)->unk_10.s = offset_y >> 1;
    state = ((S_80023260_0 *)actor)->unk_18.u;
    ((S_80023260_0 *)actor)->unk_0C.s = offset_x >> 1;
    idle_state = 2;
    if (state == idle_state) {
        goto update_motion;
    }
    if (state >= 3) {
        goto check_path_state;
    }
    if (state == 0) {
        goto init_state;
    }
    if (state == 1) {
        goto init_sprite;
    }
    goto update_motion;
check_path_state:
    if (state == 0x100) {
        goto follow_path;
    }
    if (state > 0x100) {
        goto update_motion;
    }
    if (state == 3) {
        goto reset_sprite;
    }
    goto update_motion;
init_state:
    ((S_80023260_0 *)actor)->unk_18.p = old_state + 1;
    return;
init_sprite:
    ((S_80023260_0 *)actor)->unk_2A = 0x800;
    sprite_config = D_80081458[0];
    directions = D_800D2388;
    ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = directions;
    ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v = sprite_config;
    func_80047784(sprite, D_800D2388[((D_80083228 + ((S_80023260_0 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_80023260_0 *)actor)->unk_18.p = (u16) (((S_80023260_0 *)actor)->unk_18.p + 1);
    goto update_motion;
reset_sprite:
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_800D2388 - 8;
    func_80047784(sprite, (D_800D2388 - 8)[((D_80083228 + ((S_80023260_0 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_80023260_0 *)actor)->unk_18.p = idle_state;
    goto update_motion;
follow_path:
    path_ticks = ((S_80023260_0 *)actor)->unk_1A + 1;
    ((S_80023260_0 *)actor)->unk_1A = path_ticks;
    if ((((S_80023260_0 *)actor)->unk_04 <= 0x200000) && (((S_80023260_3 *)waypoint)->unk_06 & 2)) {
        if (((s16) path_ticks % (s16) paths[((S_80023260_0 *)actor)->unk_22].flags) == 0) {
            func_800ABD74(motion);
            ((S_80023260_0 *)actor)->unk_04 = (s32) (((S_80023260_0 *)actor)->unk_04 + 0x80000);
        }
    }
    path_speed = ((S_80023260_0 *)actor)->unk_04;
    if ((path_speed <= 0xFFFFF) && (((S_80023260_3 *)waypoint)->unk_06 & 1)) {
        ((S_80023260_0 *)actor)->unk_04 = (s32) (path_speed + 0x20000);
    }
    heading = ((S_80023260_4 *)actor_ref)->unk_2A;
    path_heading = ((S_80023260_3 *)waypoint)->unk_04;
    angle_delta = heading - path_heading;
    turn_step = 0;
    while (angle_delta >= 0x801) {
        angle_delta -= 0x1000;
    }
    while (angle_delta < -0x800) {
        angle_delta += 0x1000;
    }
    heading_error = angle_delta;
    path_flags = ((S_80023260_3 *)waypoint)->unk_06;
    path_flag = path_flags & 8;
    if (path_flag != 0) {
        path_flag = path_flags & 0x10;
        if (path_flag != 0) {
            target_x = ((S_80023260_3 *)waypoint)->unk_00;
            turn_limit = D_800242D8[((S_80023260_0 *)actor)->unk_22].field8;
            if (((S_80023260_1 *)motion)->unk_00.at02.v >= target_x) {
                reached_point = 1;
            }
            goto steer_along_x;
        }
        turn_limit = 0 - D_800242D8[((S_80023260_0 *)actor)->unk_22].field8;
        if (((S_80023260_1 *)motion)->unk_00.at02.v <= ((S_80023260_3 *)waypoint)->unk_00) {
            reached_point = 1;
        }
steer_along_x:
        steer_y = ((S_80023260_3 *)waypoint)->unk_02;
        pos_y = ((S_80023260_1 *)motion)->unk_04.at02.v;
        distance_y = steer_y - pos_y;
        if (distance_y < 0) {
            distance_y = 0 - distance_y;
        }
        if (distance_y >= 5) {
            turn_step = 0x20;
            if (pos_y >= steer_y) {
                if ((0 - turn_limit) < heading_error) {
                    turn_step = -0x20;
                }
                goto apply_turn;
            }
            goto check_turn_limit;
        }
        goto apply_turn;
    }
    path_flag = path_flags & 0x10;
    if (path_flag != 0) {
        target_y = ((S_80023260_3 *)waypoint)->unk_02;
        turn_limit = D_800242D8[((S_80023260_0 *)actor)->unk_22].field8;
        if (((S_80023260_1 *)motion)->unk_04.at02.v >= target_y) {
            reached_point = 1;
        }
        goto steer_along_y;
    }
    turn_limit = 0 - D_800242D8[((S_80023260_0 *)actor)->unk_22].field8;
    if (((S_80023260_1 *)motion)->unk_04.at02.v <= ((S_80023260_3 *)waypoint)->unk_02) {
        reached_point = 1;
    }
steer_along_y:
    steer_x = ((S_80023260_3 *)waypoint)->unk_00;
    pos_x = ((S_80023260_1 *)motion)->unk_00.at02.v;
    distance_x = steer_x - pos_x;
    if (distance_x < 0) {
        distance_x = 0 - distance_x;
    }
    if (distance_x >= 5) {
        turn_step = 0x20;
        if (pos_x < steer_x) {
            if ((0 - turn_limit) < heading_error) {
                turn_step = -0x20;
            }
            goto apply_turn;
        }
check_turn_limit:
        if (turn_limit < heading_error) {
            turn_step = -0x20;
        }
        goto apply_turn;
    }
apply_turn:
    if ((((S_80023260_3 *)waypoint)->unk_06 & 4) && (reached_point != 0)) {
        ((S_80023260_1 *)motion)->unk_14 = -0x140000;
    }
    bias_step = turn_step >> 4;
    ((S_80023260_4 *)actor_ref)->unk_2A = (s16) ((u16) ((S_80023260_4 *)actor_ref)->unk_2A + turn_step);
    ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E + bias_step);
    ((S_80023260_0 *)actor)->unk_1C = (s16) ((u16) ((S_80023260_0 *)actor)->unk_1C + reached_point);
    if ((reached_point != 0) && (((S_80023260_3 *)waypoint)->unk_06 & 0x20)) {
        if (rand(bias_step, heading_error, turn_limit, turn_step) & 1) {
            ((S_80023260_3 *)waypoint)->unk_0E = (u16) (((S_80023260_3 *)waypoint)->unk_0E | 2);
            goto wrap_path;
        }
        ((S_80023260_3 *)waypoint)->unk_0E = (u16) (((S_80023260_3 *)waypoint)->unk_0E & 0xFFFD);
        goto wrap_path;
    }
wrap_path:
    if (((S_80023260_0 *)actor)->unk_1C >= 0xF) {
        ((S_80023260_0 *)actor)->unk_1A = 0U;
        ((S_80023260_0 *)actor)->unk_1C = 0;
    }
    goto update_motion;
update_motion:
    turn_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (turn_bias > 0) {
        ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E - 1);
    } else if (turn_bias < 0) {
        ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E + 1);
    }
    damped_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (damped_bias < -9) {
        clamp_value = -9;
        goto clamp_store;
    }
    clamp_value = damped_bias < 0xA;
    if (clamp_value != 0) {
        goto clamp_done;
    }
    clamp_value = 9;
clamp_store:
    ((S_80023260_0 *)actor)->unk_1E = clamp_value;
clamp_done:
    abs_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (abs_bias < 0) {
        abs_bias = 0 - abs_bias;
    }
    if ((abs_bias >= 6) && (((u16) ((S_80023260_0 *)actor)->unk_1A >> 1) & 1)) {
        func_800ABD74(motion);
    }
    {
        Stack24 ground_probe = *(Stack24 *)motion;
        surface_kind = ((S_80023260_5 *)(((((S_80023260_0 *)actor)->unk_24 * 2) + model_base)))->unk_3C;
        if ((surface_kind == 2) || (surface_kind == 6)) {
            ground_probe.field8 = 0xFE000000;
        }
        ground_height = func_800C2AE8(&ground_probe);
        ((S_80023260_1 *)motion)->unk_0C = (s32) (func_80064584(((S_80023260_4 *)actor_ref)->unk_2A) * ((s32) ((S_80023260_0 *)actor)->unk_04 >> 0xC));
        ((S_80023260_1 *)motion)->unk_10 = (s32) (func_800644B8(((S_80023260_4 *)actor_ref)->unk_2A) * ((s32) ((S_80023260_0 *)actor)->unk_04 >> 0xC));
        if (ground_height < ((S_80023260_1 *)motion)->unk_0A) {
            ((S_80023260_1 *)motion)->unk_0A = ground_height;
            if (((S_80023260_1 *)motion)->unk_14 >= 0) {
                ((S_80023260_1 *)motion)->unk_14 = 0;
            }
            if (((S_80023260_0 *)actor)->unk_08 & 1) {
                func_800ABD74(motion);
            }
            ((S_80023260_0 *)actor)->unk_08 = (s32) (((S_80023260_0 *)actor)->unk_08 & -2);
        } else {
            ((S_80023260_0 *)actor)->unk_08 = (s32) (((S_80023260_0 *)actor)->unk_08 | 1);
        }
        speed = ((S_80023260_0 *)actor)->unk_04;
        if (speed < -0x10000) {
            ((S_80023260_0 *)actor)->unk_04 = speed + 0x10000;
        } else if (speed > 0x10000) {
            ((S_80023260_0 *)actor)->unk_04 = speed - 0x10000;
        } else {
            ((S_80023260_0 *)actor)->unk_04 = 0;
        }
        ((S_80023260_1 *)motion)->unk_14 = (s32) (((S_80023260_1 *)motion)->unk_14 + 0x20000);
        final_state = ((S_80023260_0 *)actor)->unk_18.u;
        if (final_state != 0) {
            func_800211C4(actor_ref, actor, sprite);
        }
    }
}
