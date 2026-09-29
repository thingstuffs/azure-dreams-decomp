#include "common.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172290_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172290_0;   /* arg0 in func_80172290 */


extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_80170E5C;

/* Advance arcing movement toward the destination tile and finalize the landing. */
void func_80172290(S_80172290_0 *animation, EntityRec *motion, Rec_D_80082E80 *destination, EntityRec *entity) {
    s32 query_output;
    s32 frames_left;
    s32 entity_flags;
    s32 phase;

    phase = animation->unk_9B;
    switch (phase) {
    case 0:
        animation->unk_98 |= 8;
        motion->flags14 = 0xFFEE0000;
        entity->flags1C &= 0xF7FFFFFF;
        animation->unk_A0 = 0;
        animation->unk_9B++;
    case 1:
        frames_left = animation->unk_96.s;
        animation->unk_90 -= animation->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = destination->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = destination->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->unk_10 =
                    ((target_y - current_y) << 16) / animation->unk_96.s;
            }
            animation->unk_A0 += motion->flags14;
            motion->flags14 += 0x40000;
        }

        animation->unk_90 += animation->unk_A0;
        if (animation->unk_96.s < 2) {
            animation->unk_90 = 0;
            animation->unk_98 &= 0xFFF7;
            entity->flags1C |= 0x08000000;
            animation->unk_9B++;
        }
    case 2:
        if (entity->flags1C & 0x08000000) {
            animation->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, destination->unk_24, destination->unk_25);
            animation->unk_9B++;
        }
    }

    if ((s16)--animation->unk_96.u <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        func_800AD594(entity, 4);
        func_800A4ACC(entity);

        {
            DungeonGlobalStatus *global_state = &dungeonStatus;

            if (global_state->unk_08 != 0) {
                (*(u16 *)&global_state->unk_08)--;
            }
        }

        entity_flags = entity->flags1C;
        if (entity_flags & 0x2000) {
            if (entity->unk_46 & 0x8000) {
                entity->unk_46 &= 0x7FFF;
            }
        } else if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {

                entity->facing = func_800A0818(
                    destination->unk_24, destination->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &query_output);
            }
        }

        if ((func_800AD9B4(destination, entity) << 16) > 0) {
            animation->unk_8C = &D_80170E5C;
            func_800A9A04(entity);
        }
    }

    return;
}
