#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F00_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; volatile u16 u; u16 p; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172F00_0;   /* arg0 in func_80172F00 */


extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];

/* Updates staged directional motion, then restores the entity to its tile and animation. */
void func_80172F00(void *action, void *motion, void *sprite, void *entity)
{
    s16 timer_signed;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_vx;
    s32 rounded_vy;
    s32 tracked_entity;
    s32 *global_state;
    s32 state;
    u16 timer;

    state = ((S_80172F00_0 *)action)->unk_9B;
    direction = (((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 9) & 7;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    func_800AD4D0(entity);
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFFD0000;
        func_800AAA54(action, motion, sprite, D_80174ADC);
        return;
    }

    {
        u32 mask_bit_27 = 0xF7FFFFFF;
        u32 mask_bit_18 = 0xFFFBFFFF;
        u32 entity_flags;
        u16 action_flags;

        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            ((s16 *)&D_8006CCD8)[direction] << 18;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            ((s16 *)&D_8006CCE8)[direction] << 18;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0x20000;

        action_flags = ((S_80172F00_0 *)action)->unk_98;
        action_flags |= 8;
        ((S_80172F00_0 *)action)->unk_98 = action_flags;
        entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32;
        entity_flags &= mask_bit_27;
        entity_flags &= mask_bit_18;
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 = entity_flags;
    }

    ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
    timer_signed = -1;
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x228) {
        timer_signed = 8;
    }
    ((S_80172F00_0 *)action)->unk_96.s = timer_signed;

    velocity_x = ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32;
    rounded_vx = velocity_x;
    if (velocity_x < 0) {
        rounded_vx = velocity_x + 3;
    }
    velocity_y = ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = velocity_x - (rounded_vx >> 2);
    rounded_vy = velocity_y;
    if (velocity_y < 0) {
        rounded_vy = velocity_y + 3;
    }
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = velocity_y - (rounded_vy >> 2);
    return;

state_1:
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -=
        ((s16 *)&D_8006CCD8)[direction] << 15;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -= ((s16 *)&D_8006CCE8)[direction] << 15;

    timer_signed = ((S_80172F00_0 *)action)->unk_96.s;
    timer = ((S_80172F00_0 *)action)->unk_96.u;
    if (timer_signed > 0) {
        timer -= 1;
        ((S_80172F00_0 *)action)->unk_96.p = timer;
        goto check_timer;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((S_80172F00_0 *)action)->unk_96.p = 0;
    }

check_timer:
    if (((S_80172F00_0 *)action)->unk_96.s != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
        goto increment_state;
    }

start_action:
    ((S_80172F00_0 *)action)->unk_9B = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFFD0000;
    func_800AAA54(action, motion, sprite, D_80174ADC);
    return;

increment_state:
    ((S_80172F00_0 *)action)->unk_96.s = 5;
    ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
    return;

state_2:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0xFFFD0000;
    if (((S_80172F00_0 *)action)->unk_96.s != 0) {
        s32 tile_coord;
        s32 position_offset;

        tile_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        position_offset = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        position_offset -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (tile_coord - position_offset) << 15;
        tile_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        position_offset = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        position_offset -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (tile_coord - position_offset) << 15;
    }

    timer = ((S_80172F00_0 *)action)->unk_96.p - 1;
    ((S_80172F00_0 *)action)->unk_96.p = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    ((S_80172F00_0 *)action)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x08000000;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 |= 0x00040000;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
    func_80047784(
        sprite,
        D_80174AD4[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

    global_state = &D_80083460;
    tracked_entity = global_state[4];
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        global_state[4] = tracked_entity & 0x7FFFFFFF;
    }
    ((S_80172F00_0 *)action)->unk_8C = D_80171138;
}
