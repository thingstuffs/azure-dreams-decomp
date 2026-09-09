#include "common.h"

typedef struct S_800AD594_0 {
    u8 pad_00[0x13];
    union { s8 s; u8 u; } unk_13;   /* accessed as both */
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x4];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x2E];
    s32 unk_54;
    u8 pad_58[0xE];
    u8 unk_66;
} S_800AD594_0;   /* arg0 in func_800AD594 */

typedef struct S_800AD594_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AD594_1;   /* counterBase in func_800AD594 */



extern s32 func_80042900(void *, s32);
extern void func_80094E34(void);
extern s32 D_80012090[];
extern s32 D_80083460;

/* Apply a modified reduction to an entity's stored amount and handle a drop to zero. */
void func_800AD594(S_800AD594_0 *entity, s32 base_reduction) {
    s32 remaining_amount;
    s32 reduction;
    s32 one;
    u8 initial_level;
    u8 level_limit;
    u8 *counter_base;

    reduction = base_reduction;
    if (entity->unk_13.s > 0) {
        remaining_amount = entity->unk_24.at00.v;
        initial_level = entity->unk_24.at01.v;
        if ((func_80042900(entity, 0x20) << 16) != 0) {
            reduction = 0;
        } else if (entity->unk_54 & 0x100) {
            reduction = (reduction + 1) >> 1;
        }
        if ((func_80042900(entity, 0xF) << 16) != 0) {
            reduction *= 2;
        }
        remaining_amount -= reduction;
        if (remaining_amount < 0) {
            remaining_amount = 0;
        } else if (remaining_amount > 0x10000) {
            remaining_amount = 0xFFFF;
        }
        level_limit = entity->unk_66;
        entity->unk_24.at00.v = (u16)remaining_amount;
        if (level_limit < entity->unk_24.at01.v) {
            entity->unk_24.at01.v = level_limit;
            entity->unk_24.at00u.v = 0xFF;
        }
        if (entity->unk_24.at01.v == 0) {
            s32 dungeon_mode;

            one = 1;

            dungeon_mode = *(s32 *)0x80012090;
            if ((dungeon_mode == one) &&
                ((entity->unk_13.u == 2) ||
                 (entity->unk_13.u == 0x39))) {
                entity->unk_24.at01.v = dungeon_mode;
                return;
            }
            if (entity->unk_1C & 0x80000) {
                func_80094E34();
            }
            if (initial_level != 0) {
                counter_base = (u8 *)&D_80083460;
                ((S_800AD594_1 *)counter_base)->unk_0A =
                    ((S_800AD594_1 *)counter_base)->unk_0A + 1;
            }
        }
    }
}
