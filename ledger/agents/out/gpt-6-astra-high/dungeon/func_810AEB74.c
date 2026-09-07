#include "common.h"

typedef struct S_80172374_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_80172374_0;   /* arg0 in func_80172374 */

typedef struct S_80172374_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172374_1;   /* arg1 in func_80172374 */

typedef struct S_80172374_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172374_2;   /* arg3 in func_80172374 */

typedef struct S_80172374_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172374_3;   /* arg2 in func_80172374 */

typedef struct S_80172374_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80172374_4;   /* global in func_80172374 */

typedef struct S_80172374_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172374_5;   /* map in func_80172374 */



extern s16 func_800A0818();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A9A04();
extern void func_800AD594();
extern s32 func_800AD9B4();

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80170E54;

/* Advances a jump toward the target tile and finishes movement when the timer expires. */
void func_80172374(S_80172374_0 *motion, S_80172374_1 *position, S_80172374_3 *target_tile, S_80172374_2 *entity) {
    s32 direction_aux;
    s32 jump_state;
    s32 frames_left;
    s16 next_frames;
    s32 entity_flags;
    u8 *action_counters;

    jump_state = motion->unk_9B;
    if (jump_state == 1) {
        goto advance_jump;
    }
    if (jump_state < 2) {
        if (jump_state == 0) {
            goto begin_jump;
        }
        goto tick_timer;
    }
    if (jump_state == 2) {
        goto land;
    }
    goto tick_timer;

begin_jump:
    if (motion->unk_96 != 8) {
        goto tick_timer;
    }
    motion->unk_98 |= 8;
    position->unk_14 = 0xFFEE0000;
    entity->unk_1C &= 0xF7FFFFFF;
    motion->unk_A4 = 0;
    motion->unk_9B++;

advance_jump:
    frames_left = motion->unk_96;
    motion->unk_90 -= motion->unk_A4;
    if (frames_left != 0) {
        register s32 coord ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
        s32 axis_origin;

        coord = target_tile->unk_24 << 6;
        axis_origin = position->unk_02 - 0x20;
        coord = ((coord - axis_origin) << 16) / frames_left;
        axis_origin = position->unk_06 - 0x20;
        position->unk_0C = coord;
        coord = target_tile->unk_25 << 6;
        position->unk_10 = ((coord - axis_origin) << 16) / motion->unk_96;
        motion->unk_A4 += position->unk_14;
        position->unk_14 += 0x40000;
    }
    motion->unk_90 += motion->unk_A4;
    if (motion->unk_96 < 3) {
        motion->unk_90 = 0;
        motion->unk_98 &= 0xFFF7;
        entity->unk_1C |= 0x08000000;
        motion->unk_9B++;
    }

land:
    if (entity->unk_1C & 0x08000000) {
        motion->unk_98 &= 0xFFF7;
        position->unk_14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, target_tile->unk_24, target_tile->unk_25);
        motion->unk_9B++;
    }

tick_timer:
    next_frames = (u16)motion->unk_96 - 1;
    motion->unk_96 = next_frames;
    if ((next_frames << 16) <= 0) {
        position->unk_14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        func_800A2B04(position, target_tile->unk_24, target_tile->unk_25);
        func_800AD594(entity, 5);
        func_800A4ACC(entity);

        action_counters = (u8 *)&D_80083460;
        if (((S_80172374_4 *)action_counters)->unk_08 != 0) {
            ((S_80172374_4 *)action_counters)->unk_08 = (u16)((S_80172374_4 *)action_counters)->unk_08 - 1;
        }

        entity_flags = entity->unk_1C;
        if (entity_flags & 0x2000) {
            if (entity->unk_46 & 0x8000) {
                entity->unk_46 &= 0x7FFF;
            }
            goto update_entity;
        }
        if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {
                u8 *reference_tile = D_80082E80;

                entity->unk_2A = func_800A0818(
                    target_tile->unk_24, target_tile->unk_25,
                    ((S_80172374_5 *)reference_tile)->unk_24, ((S_80172374_5 *)reference_tile)->unk_25, &direction_aux);
            }
        }

update_entity:
        if ((func_800AD9B4(target_tile, entity) << 16) > 0) {
            motion->unk_8C = &D_80170E54;
            func_800A9A04(entity);
        }
    }
}
