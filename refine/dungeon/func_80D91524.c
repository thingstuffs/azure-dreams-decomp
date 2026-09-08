#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172D24_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D24_1;   /* arg0 in func_80172D24 */





extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E68;
extern u8 D_80173874[];

/* Updates timed directional movement and settles the entity at its grid position. */
void func_80172D24(void *action, void *motion, void *sprite, void *entity)
{
    s16 *direction_y;
    s16 *direction_x_table;
    s16 frames_left;
    s16 timer_or_state;
    s16 duration;
    s32 decel_offset;
    s32 velocity_y;
    s32 direction;
    s32 launch_offset;
    s32 velocity_x;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;
    s32 target_x;
    s32 position_x;
    s32 target_y;
    s32 position_y;
    s32 *tracking_data;
    s32 tracked_entity;
    u8 state;

    direction = (((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 9) & 7;
    state = ((S_80172D24_1 *)action)->unk_9B;

    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        return;
    }

state_0:
    func_800AD4D0(entity);
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        goto start_action;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172D24_1 *)action)->unk_96.s = 0;
        ((S_80172D24_1 *)action)->unk_9B = 3;
        return;
    }
    ((S_80172D24_1 *)action)->unk_96.s = 12;
    ((S_80172D24_1 *)action)->unk_9B++;

state_1:
    timer_or_state = ((S_80172D24_1 *)action)->unk_96.s - 1;
    ((S_80172D24_1 *)action)->unk_96.s = timer_or_state;
    if ((timer_or_state << 16) != 0) {
        return;
    }

    (*(void * *)((u8 *)sprite + 0x2C)) = D_80173874;
    func_80047784(sprite,
        D_80173874[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

    direction_x_table = (s16 *)&D_8006CCD8;
    launch_offset = direction * 2;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
        *(s16 *)((u8 *)direction_x_table + launch_offset) << 19;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 + launch_offset) << 19;

    duration = -1;
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x228) {
        duration = 8;
    }
    ((S_80172D24_1 *)action)->unk_96.s = duration;

    velocity_x = ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32;
    rounded_velocity_x = velocity_x;
    if (velocity_x < 0) {
        rounded_velocity_x = velocity_x + 3;
    }
    velocity_y = ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = velocity_x - (rounded_velocity_x >> 2);
    rounded_velocity_y = velocity_y;
    if (velocity_y < 0) {
        rounded_velocity_y = velocity_y + 3;
    }
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = velocity_y - (rounded_velocity_y >> 2);
    timer_or_state = ((S_80172D24_1 *)action)->unk_9B + 1;
    goto store_state;

state_2:
    direction_x_table = (s16 *)&D_8006CCD8;
    decel_offset = direction * 2;
    direction_y = (s16 *)((u8 *)&D_8006CCE8 + decel_offset);
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -=
        *(s16 *)((u8 *)direction_x_table + decel_offset) << 16;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -= *direction_y << 16;

    if (((S_80172D24_1 *)action)->unk_96.u > 0) {
        ((S_80172D24_1 *)action)->unk_96.s--;
    } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((S_80172D24_1 *)action)->unk_96.s = 0;
    }
    if (((S_80172D24_1 *)action)->unk_96.u != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
        duration = 8;
        goto increment_state;
    }

start_action:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800AAA54(action, motion, sprite, D_80173874);
    return;

increment_state:
    timer_or_state = ((S_80172D24_1 *)action)->unk_9B + 1;
    ((S_80172D24_1 *)action)->unk_96.s = duration;

store_state:
    ((S_80172D24_1 *)action)->unk_9B = timer_or_state;
    return;

state_3:
    frames_left = ((S_80172D24_1 *)action)->unk_96.u;
    if (frames_left != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        position_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - position_x) << 15) / frames_left;

        target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        position_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            ((target_y - position_y) << 15) / ((S_80172D24_1 *)action)->unk_96.u;
    }

    timer_or_state = ((S_80172D24_1 *)action)->unk_96.s - 1;
    ((S_80172D24_1 *)action)->unk_96.s = timer_or_state;
    if ((timer_or_state << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    tracking_data = &D_80083460;
    tracked_entity = *(s32 *)((u8 *)tracking_data + 0x10);
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        *(s32 *)((u8 *)tracking_data + 0x10) = tracked_entity & 0x7FFFFFFF;
    }
    ((S_80172D24_1 *)action)->unk_8C = &D_80170E68;
}
