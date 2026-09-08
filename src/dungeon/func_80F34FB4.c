#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;
typedef struct {
    Vec3s item[3];
} Vec3sTable;

extern Vec3sTable D_80170838;
extern Vec3sTable D_8017084C;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80174AA4[];
extern u8 D_80083498[];
extern u8 D_80174AAC[];
extern u8 D_80170E94[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern void *D_80170860[];
s32 func_8003DE58();
void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C();
s16 func_80066460();
s16 func_8006649C();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
extern M2C_UNK D_800DB618;
extern M2C_UNK D_800DB660;
extern u8 D_80174A8C;
extern u8 D_80174A94;


typedef struct S_801727B4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    u16 unk_A8;
    u16 unk_AA;
    u16 unk_AC;
    u16 unk_AE;
    u16 unk_B0;
} S_801727B4_0;   /* arg0 in func_801727B4 */




typedef struct S_801727B4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xC];
    u16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
} S_801727B4_4;   /* temp_s0 in func_801727B4 */

/* Updates a staged movement animation, emits effects, and restores the actor at its starting position. */
void func_801727B4(void *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *animation, void *actor) {
    static void *const state_labels[] = { &&start_motion, &&start_jump, &&update_jump, &&emit_effect, &&finish_animation, &&return_to_start };
    Vec3sTable effect_vectors_a;
    Vec3sTable effect_vectors_b;
    s32 reverse_facing;
    s32 actor_handle;
    s32 facing;
    s32 has_offset;
    s32 direction_index;
    s32 vertical_speed;
    u32 fade_steps;
    s32 wrapped_facing;
    s32 axis_distance;
    s32 start_coord;
    u16 effect_coord;
    u16 ticks_left;
    u8 state;
    u8 previous_state;
    S_801727B4_4 *effect_data;
    void *effect;

    effect_vectors_a = D_80170838;
    effect_vectors_b = D_8017084C;
    state = ((S_801727B4_0 *)action)->unk_9B;
    if (state >= 6U) {
        goto done;
    }
    (void)state_labels;
    goto *D_80170860[(u32)(state)];
start_motion:
    ((S_801727B4_0 *)action)->unk_A8 = (u16) motion->unk_00.at02_u16.v;
    ((S_801727B4_0 *)action)->unk_AA = (u16) motion->unk_04.at02_u16.v;
    if (!(animation->unk_14.at00_u16.v & 0x8000)) {
        goto set_velocity;
    }
    ((S_801727B4_0 *)action)->unk_9B = 5U;
    animation->unk_14.at00_u16.v = (u16) (animation->unk_14.at00_u16.v | 0x6000);
    func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    goto done;
set_velocity:
    facing = ((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
    reverse_facing = facing + 4;
    wrapped_facing = reverse_facing;
    if (reverse_facing >= 0) {
        goto apply_velocity;
    }
    wrapped_facing = facing + 0xB;
apply_velocity:
    direction_index = reverse_facing - (wrapped_facing & 0x18);
    motion->unk_0C.as_s32 = (s32) ((s16) D_8006CCD8[direction_index] * 0x30000);
    motion->unk_10.at00_s32.v = (s32) ((s16) D_8006CCE8[direction_index] * 0x30000);
    animation->unk_2C.as_pu8 = &D_80174A8C;
    func_80047784(animation, (&D_80174A8C)[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    goto increment_state_load;
start_jump:
    if (!(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animation->unk_2C.as_pu8 = &D_80174A94;
    func_80047784(animation, (&D_80174A94)[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)action)->unk_90 = 0;
    ((S_801727B4_0 *)action)->unk_98 = (u16) (((S_801727B4_0 *)action)->unk_98 | 8);
    motion->unk_14.as_s32 = 0xFFF40000;
    goto increment_state_load;
update_jump:
    vertical_speed = motion->unk_14.as_s32 + 0x20000;
    motion->unk_14.as_s32 = vertical_speed;
    ((S_801727B4_0 *)action)->unk_90 = (s32) (((S_801727B4_0 *)action)->unk_90 + vertical_speed);
    if (!(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    motion->unk_0C.as_s32 = (s32) ((s32) (0 - motion->unk_0C.as_s32) >> 1);
    motion->unk_10.at00_s32.v = (s32) ((s32) (0 - motion->unk_10.at00_s32.v) >> 1);
    animation->unk_2C.as_pu8 = D_80174AA4;
    func_80047784(animation, D_80174AA4[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)action)->unk_96 = 7;
    ((S_801727B4_0 *)action)->unk_9B = (u8) (((S_801727B4_0 *)action)->unk_9B + 1);
    goto done;
emit_effect:
    if (animation->unk_04.as_s8 >= 3) {
        goto create_effect;
    }
    if (func_8003DE58(animation->unk_08, animation, action + 0xAC, 0) != 0) {
        goto translate_offset;
    }
    ((S_801727B4_0 *)action)->unk_B0 = 0U;
    ((S_801727B4_0 *)action)->unk_AE = 0U;
    ((S_801727B4_0 *)action)->unk_AC = 0U;
translate_offset:
    ((S_801727B4_0 *)action)->unk_AC = (u16) (((S_801727B4_0 *)action)->unk_AC + motion->unk_00.at02_u16.v);
    ((S_801727B4_0 *)action)->unk_AE = (u16) (((S_801727B4_0 *)action)->unk_AE + motion->unk_04.at02_u16.v);
    ((S_801727B4_0 *)action)->unk_B0 = (u16) (((S_801727B4_0 *)action)->unk_B0 + motion->unk_08.at02_u16.v);
    goto update_timer;
create_effect:
    effect = func_8003FD64(1, D_80083498);
    if (effect == NULL) {
        goto update_timer;
    }
    (*(M2C_UNK **)((u8 *)effect + 0x10)) = &D_800DB618;
    func_8004491C(effect, &D_800DB660);
    effect_data = effect + 0x20;
    effect_data->unk_10 = (u16) ((S_801727B4_0 *)action)->unk_AC;
    effect_data->unk_12 = (u16) ((S_801727B4_0 *)action)->unk_AE;
    effect_data->unk_14 = (u16) ((S_801727B4_0 *)action)->unk_B0;
    has_offset = func_8003DE58(animation->unk_08, animation, action + 0xAC, 0);
    if (has_offset == 0) {
        ((S_801727B4_0 *)action)->unk_B0 = 0U;
        ((S_801727B4_0 *)action)->unk_AE = 0U;
        ((S_801727B4_0 *)action)->unk_AC = 0U;
    }
    {
        s32 purple;
        s32 light_gray;
        s32 base_gray;

        purple = 0x200020;
        light_gray = 0xC0C0C0;
        effect_coord = ((S_801727B4_0 *)action)->unk_AC + motion->unk_00.at02_u16.v;
        ((S_801727B4_0 *)action)->unk_AC = effect_coord;
        effect_data->unk_08 = effect_coord;
        effect_coord = ((S_801727B4_0 *)action)->unk_AE + motion->unk_04.at02_u16.v;
        ((S_801727B4_0 *)action)->unk_AE = effect_coord;
        effect_data->unk_0A = effect_coord;
        effect_coord = ((S_801727B4_0 *)action)->unk_B0 + motion->unk_08.at02_u16.v;
        ((S_801727B4_0 *)action)->unk_B0 = effect_coord;
        effect_data->unk_0C = effect_coord;
        effect_data->unk_2C = (u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16;
        effect_data->unk_2E = 0x10;
        effect_data->unk_30 = 0x10;
        effect_data->unk_36 = 0x10;
        effect_data->unk_04 = purple;
        effect_data->unk_18 = light_gray;
        fade_steps = 6 - animation->unk_04.as_s8;
        base_gray = 0x141414;
        effect_data->unk_1C = (s32) ((fade_steps * 0x30303) + base_gray);
        (*(Vec3s *)((u8 *)effect + 0x40)) = effect_vectors_a.item[animation->unk_04.as_s8 - 3];
        (*(Vec3s *)((u8 *)effect + 0x46)) = effect_vectors_b.item[animation->unk_04.as_s8 - 3];
        effect_data->unk_32 = func_80066460(0, 1, 0x2C0, 0x100);
        effect_data->unk_34 = func_8006649C(0, 0x1F8);
    }
update_timer:
    ticks_left = ((S_801727B4_0 *)action)->unk_96 - 1;
    ((S_801727B4_0 *)action)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) == 0) {
        goto trigger_action;
    }
    if (!(animation->unk_14.at00_u16.v & 0x8000)) {
        goto check_animation;
    }
trigger_action:
    func_8009C12C(actor, animation, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    func_800A56E0(0x808);
check_animation:
    if (!(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animation->unk_2C.as_pu8 = D_80174AAC;
    func_80047784(animation, D_80174AAC[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)action)->unk_98 = (u16) (((S_801727B4_0 *)action)->unk_98 & 0xFFF7);
    ((S_801727B4_0 *)action)->unk_9B = (u8) (((S_801727B4_0 *)action)->unk_9B + 1);
    goto done;
finish_animation:
    if (!(animation->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    animation->unk_2C.as_pu8 = D_80174AAC;
    func_80047784(animation, D_80174AAC[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    if (!(animation->unk_14.at00_u16.v & 0x8000)) {
        goto advance_state;
    }
    func_800A2B04(motion, animation->unk_24, animation->unk_25);
advance_state:
increment_state_load:
    previous_state = ((S_801727B4_0 *)action)->unk_9B;
increment_state:
    ((S_801727B4_0 *)action)->unk_9B = (u8) (previous_state + 1);
    goto done;
return_to_start:
    axis_distance = (s16) motion->unk_00.at02_u16.v;
    start_coord = (s16) ((S_801727B4_0 *)action)->unk_A8;
    axis_distance = axis_distance - start_coord;
    if (axis_distance >= 0) {
        goto check_x_distance;
    }
    axis_distance = 0 - axis_distance;
check_x_distance:
    if (axis_distance >= 0x41) {
        goto adjust_position;
    }
    axis_distance = (s16) motion->unk_04.at02_u16.v;
    start_coord = (s16) ((S_801727B4_0 *)action)->unk_AA;
    axis_distance = axis_distance - start_coord;
    if (axis_distance >= 0) {
        goto check_y_distance;
    }
    axis_distance = 0 - axis_distance;
check_y_distance:
    if (axis_distance < 0x41) {
        goto check_start_position;
    }
adjust_position:
    func_800A2B04(motion, animation->unk_24, animation->unk_25);
check_start_position:
    if ((s16) motion->unk_00.at02_u16.v != (s16) ((S_801727B4_0 *)action)->unk_A8) {
        goto done;
    }
    if ((s16) motion->unk_04.at02_u16.v != (s16) ((S_801727B4_0 *)action)->unk_AA) {
        goto done;
    }
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, animation->unk_24, animation->unk_25);
    func_800AD594(actor, 0x100);
    ((S_801727B4_0 *)action)->unk_8C = D_80170E94;
    *D_8008346C = 0;
    func_800A4ACC(actor);
    if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x7FFF);
    } else {
        *D_800E3DE8 = actor - 0x20;
    }
update_actor_handle:
    actor_handle = ((Rec_D_800E3D7C *)actor)->unk_60.as_s32;
    if (actor_handle == 0) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_14.as_s32 & 0x20000) {
        goto done;
    }
    func_800C8EFC(actor_handle, 0x10);
done:
    return;
}
