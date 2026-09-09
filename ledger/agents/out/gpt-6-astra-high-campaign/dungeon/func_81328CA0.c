#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801704A0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801704A0_0;   /* arg0 in func_801704A0 */

M2C_UNK func_80047784();
s32 func_800644B8();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
s32 func_800AD9B4();
typedef struct {
    u8 pad[0x24];
    u8 x;
    u8 y;
} Global82E80;
typedef struct {
    u8 pad[8];
    s16 count;
} Global83460;
extern Global82E80 D_80082E80;
extern s16 D_80083228[5];
extern Global83460 D_80083460;
extern u8 D_8016F78C[];
extern u8 D_80174A2C[];

/* Updates movement toward a tile and completes the timed action. */
void func_801704A0(S_801704A0_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, Rec_D_800E3D7C *entity) {
    M2C_UNK facing_aux;
    s32 frames_left;
    s32 next_frame;
    s32 x_step;
    s32 status_flags;
    s32 height;
    s32 y_offset;
    s32 entity_flags;
    u16 action_timer;
    s32 phase;
    Global82E80 *target_tile;
    Global83460 *active_actions;

    phase = action->unk_9B;
    if (phase == 1) {
        goto update_motion;
    }
    if (phase >= 2) {
        goto check_later_phase;
    }
    if (phase == 0) {
        goto start_motion;
    }
    goto update_timer;
check_later_phase:
    if (phase == 2) {
        goto check_landing;
    }
    if (phase == 3) {
        goto update_animation;
    }
    goto update_timer;
start_motion:
    action->unk_98 = (u16) (action->unk_98 | 8);
    entity->unk_1C.as_s32 = (s32) (entity->unk_1C.as_s32 & 0xF7FFFFFF);
    action->unk_9E.s = 5;
    action->unk_A4 = 0;
    action->unk_9B = (u8) (action->unk_9B + 1);
update_motion:
    frames_left = action->unk_9E.s;
    action->unk_90 = (s32) (action->unk_90 - action->unk_A4);
    if (frames_left != 0) {
        s32 x_offset;
        x_step = tile->unk_24;

        x_offset = motion->unk_00.at02_s16.v;
        x_step <<= 6;
        x_offset -= 0x20;

        x_step = (s32) ((x_step - x_offset) << 0x10) / frames_left;
        y_offset = motion->unk_04.at02_s16.v - 0x20;
        motion->unk_0C.as_s32 = x_step;
        motion->unk_10.at00_s32.v = (s32) ((s32) (((tile->unk_25 << 6) - y_offset) << 0x10) / (s16) action->unk_9E.s);
        action->unk_A4 = (s32) ((0 - func_800644B8(action->unk_9E.s * 0x199)) << 0xA);
    }
    height = action->unk_90;
    height += action->unk_A4;
    next_frame = action->unk_9E.u - 1;

    action->unk_9E.s = next_frame;
    action->unk_90 = height;
    if ((next_frame << 0x10) < 0) {
        action->unk_90 = 0;
        action->unk_98 = (u16) (action->unk_98 & 0xFFF7);
        entity->unk_1C.as_s32 = (s32) (entity->unk_1C.as_s32 | 0x08000000);
        action->unk_9B = (u8) (action->unk_9B + 1);
    }
check_landing:
    if (!(entity->unk_1C.as_s32 & 0x08000000)) {
        goto update_timer;
    }
    action->unk_98 = (u16) (action->unk_98 & 0xFFF7);
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, tile->unk_24, tile->unk_25);
    action->unk_9B = action->unk_9B + 1;
    goto update_timer;
update_animation:
    if (tile->unk_2C.as_pu8 != D_80174A2C) {
        tile->unk_2C.as_pu8 = D_80174A2C;
        func_80047784(tile, D_80174A2C[((s32) (D_80083228[0] + entity->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    }
update_timer:
    action_timer = action->unk_96 - 1;
    action->unk_96 = action_timer;
    if ((action_timer << 0x10) <= 0) {
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, tile->unk_24, tile->unk_25);
        func_800A4ACC(entity);
        active_actions = &D_80083460;
        if (active_actions->count != 0) {
            active_actions->count = (u16) active_actions->count - 1;
        }
        entity_flags = entity->unk_1C.as_s32;
        if (!(entity_flags & 0x2000)) {
            goto check_facing;
        }
        status_flags = entity->unk_44.at02_u16.v;
        if (!(status_flags & 0x8000)) {
            goto finish_action;
        }
        entity->unk_44.at02_u16.v = status_flags & 0x7FFF;
        goto finish_action;
check_facing:
        if (entity_flags & 0x410) {
            goto finish_action;
        }
        if (!(entity_flags & 0x20000)) {
            goto finish_action;
        }
        target_tile = &D_80082E80;
        entity->unk_2A.as_s16 = func_800A0818(tile->unk_24, tile->unk_25, target_tile->x, target_tile->y, &facing_aux);
finish_action:
        if ((func_800AD9B4(tile, entity) << 0x10) > 0) {
            action->unk_8C = D_8016F78C;
            func_800A9A04(entity);
        }
    }
}
