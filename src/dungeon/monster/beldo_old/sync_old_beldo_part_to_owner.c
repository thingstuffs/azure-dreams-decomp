#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/stale_bank_imports.h"
#include "dungeon/data.h"
#include "dungeon/monster/beldo_old.h"
#include "shared/object_node.h"

typedef struct S_8127B000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_8127B000_0;   /* root in sync_old_beldo_part_to_owner */

typedef struct S_8127B000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_8127B000_1;   /* owner in sync_old_beldo_part_to_owner */

typedef struct S_8127B000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8127B000_2;   /* part in sync_old_beldo_part_to_owner */

typedef struct S_8127B000_3 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8127B000_3;   /* dst in sync_old_beldo_part_to_owner */

   /* out in sync_old_beldo_part_to_owner */

typedef struct S_8127B000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8127B000_5;   /* copy in sync_old_beldo_part_to_owner */

typedef struct S_8127B000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8127B000_6;   /* callee_part in sync_old_beldo_part_to_owner */

/* Copies part state and applies smoothed position offsets and phase-dependent shading. */
void sync_old_beldo_part_to_owner(S_8127B000_0 *root, void *output_transform, void *target_part)
{
    s16 offset[3];
    MovingPosition *transform = output_transform;
    S_8127B000_3 *render_part = target_part;
    S_8127B000_1 *owner;
    S_8127B000_2 *owner_part;
    S_8127B000_5 *part_transform;
    S_8127B000_6 *motion_part;
    s8 phase;

    owner = root->unk_AC;
    owner_part = owner->unk_0C;
    part_transform = owner->unk_08;

    if (!(owner_part->unk_14 & 0x80)) {
        render_part->unk_14 &= 0xFF7F;
    }

    transform->x = part_transform->unk_02;
    transform->y = part_transform->unk_06;
    transform->z = part_transform->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DA40(motion_part->unk_08, motion_part, offset,
                      root->unk_B6) != 0) {
        transform->x +=
            (offset[0] + root->unk_B0) / 2;
        transform->y +=
            (offset[1] + root->unk_B2) / 2;
        transform->z +=
            (offset[2] + root->unk_B4) / 2;
        root->unk_B0 = offset[0];
        root->unk_B2 = offset[1];
        root->unk_B4 = offset[2];
    }

    part_transform = render_part->unk_08;
    render_part->unk_1C = owner_part->unk_1C;
    render_part->unk_1E = owner_part->unk_1E;
    render_part->unk_14 = owner_part->unk_14;
    part_transform->unk_01 &= 0xFE;

    if (root->unk_B6 == 1) {
        phase = owner_part->unk_04.s8;
        if (phase < 8) {
            s32 brightness =
                (phase * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        } else {
            s32 brightness =
                ((15 - phase) * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        }
        if (!(owner_part->unk_14 & 0x8000) &&
            owner_part->unk_04.u16 == 0x10C) {
            func_800A4398(0x709);
        }
    }

    if (root->unk_B6 == 2) {
        phase = owner_part->unk_04.s8;
        if (phase < 8) {
            s32 brightness =
                ((7 - phase) * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        } else {
            s32 brightness =
                ((phase - 8) * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        }
        if (!(owner_part->unk_14 & 0x8000) &&
            owner_part->unk_04.u16 == 0x104) {
            func_800A4398(0x709);
        }
    }

    func_80047454(render_part);
    if (owner->unk_1E & 0x8000) {
        NODE_HEADER(root)->flags |= 0x8000;
        beldo_old_transition_flags[0] |= 0x8000;
    }
}


