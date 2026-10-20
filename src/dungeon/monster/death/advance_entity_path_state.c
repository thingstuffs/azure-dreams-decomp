#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171FC8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171FC8_0;   /* arg3 in advance_entity_path_state */

typedef struct S_80171FC8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171FC8_1;   /* arg2 in advance_entity_path_state */

typedef struct S_80171FC8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_2;   /* tile in advance_entity_path_state */

typedef struct S_80171FC8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_80171FC8_3;   /* arg0 in advance_entity_path_state */

typedef struct S_80171FC8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_4;   /* (u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s in advance_entity_path_state */


extern s32 select_sprite_entry();
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s16 get_rounded_facing_and_rounding_flag();

extern u8 D_80174634[];

/* Advance the entity along its path and update its movement state. */
void advance_entity_path_state(void *motion_state, s32 unused, void *entity, void *path_state)
{
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    u16 hp;
    u16 energy;
    u16 step_index;
    void *path_entry;

    if (((S_80171FC8_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if ((s32)((S_80171FC8_0 *)path_state)->unk_71.u <= ((S_80171FC8_0 *)path_state)->unk_8A.s) {
        return;
    }

    if (((S_80171FC8_1 *)entity)->unk_2C != D_80174634) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80174634;
        select_sprite_entry(entity,
                      D_80174634[((g_game_work.view.viewAngle + ((S_80171FC8_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
                      0);
    }

    path_entry = (u8 *)path_state + ((S_80171FC8_0 *)path_state)->unk_8A.s;
    if (((S_80171FC8_1 *)entity)->unk_24 == ((S_80171FC8_2 *)path_entry)->unk_74 &&
        ((S_80171FC8_1 *)entity)->unk_25 == ((S_80171FC8_2 *)path_entry)->unk_7C) {
        hp = ((S_80171FC8_3 *)motion_state)->unk_92;
        energy = ((S_80171FC8_0 *)path_state)->unk_88;
        ((S_80171FC8_3 *)motion_state)->unk_92 = hp + 0x20;
        step_index = ((S_80171FC8_0 *)path_state)->unk_8A.u;
        ((S_80171FC8_0 *)path_state)->unk_88 = energy - 0x20;
        ((S_80171FC8_0 *)path_state)->unk_8A.u = step_index + 1;
    } else {
        flags = ((S_80171FC8_0 *)path_state)->unk_1C;
        old_x = ((S_80171FC8_1 *)entity)->unk_24;
        old_y = ((S_80171FC8_1 *)entity)->unk_25;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        ((S_80171FC8_1 *)entity)->unk_24 = ((S_80171FC8_4 *)((u8 *)path_state
            + ((S_80171FC8_0 *)path_state)->unk_8A.s))->unk_74;
        ((S_80171FC8_1 *)entity)->unk_25 = ((S_80171FC8_4 *)((u8 *)path_state
            + ((S_80171FC8_0 *)path_state)->unk_8A.s))->unk_7C;
        ((S_80171FC8_0 *)path_state)->unk_8A.u += 1;

        cycle_map_cell_flags(((S_80171FC8_1 *)entity)->unk_24, ((S_80171FC8_1 *)entity)->unk_25,
                      (((S_80171FC8_0 *)path_state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        ((S_80171FC8_0 *)path_state)->unk_2A =
            get_rounded_facing_and_rounding_flag(old_x, old_y, ((S_80171FC8_1 *)entity)->unk_24,
                          ((S_80171FC8_1 *)entity)->unk_25, (u8 *)motion_state + 0x98);
    }

    ((S_80171FC8_3 *)motion_state)->unk_9A = 0xF;
    ((S_80171FC8_3 *)motion_state)->unk_8C = 0;
    (*(s32 *)((u8 *)path_state + 0x1C)) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((S_80171FC8_3 *)motion_state)->unk_96 = 0;
        return;
    }

    ((S_80171FC8_3 *)motion_state)->unk_96 = 8;
    step_count = ((S_80171FC8_0 *)path_state)->unk_71.u;
    if (step_count > 0) {
        ((S_80171FC8_3 *)motion_state)->unk_96 = 8 / step_count;
    }

    return;
}
