#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
extern int abs(int);

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

extern u32 level_experience_table[];
extern u8 entity_spawn_variant_code;

extern void func_80042640(void *, s32);
extern void unlink_entity_node(void *);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern s32 find_active_rect_containing_point(s32, s32);
extern SpawnFunc load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read);
extern void retain_spawn_resource(s16 entry_type, s16 entry_key);
extern void *find_or_retain_sprite_resource_slot(s32, s32);
extern void raise_entity_level(void *, s32);
extern void * detach_record_and_update_slot_state(void *);
extern void select_dungeon_spawn_tile(u8 *, u8 *);
/* Retail 0x800A6D30 (+0xC15D0 in DUNGEON.BIN), 48 bytes: RNG reads no argument registers, including a3. */
extern s32 generate_random_value(void);
extern s32 select_random_eligible_item_entry(void *);

/* Places a monster from the spawn table and raises it to the selected level. */
void spawn_floor_monster_from_table(s32 spawn_mode) {
    void *monster;
    s32 monster_type;
    s32 mode;
    s32 spawn_level;
    register u8 raw_variant;
    s16 attempt;
    s32 distance;
    TileObject *reference_object;
    s32 fixed_entry_offset;
    s32 spawn_height;
    s32 dx;
    s32 dy;
    u8 tile_x;
    u8 tile_y;
    u32 *limits = 0;
    u32 *next_limits;
    SpawnFunc spawn_monster;
    void *level_monster; /* MATCH: Both threshold arms supply the call argument in the branch delay slot. */

    distance = 0x100;
    if (dungeon_floor_flags & 0x10000000) {
        return;
    }
    if (g_dungeon_status.monster_count >= 0x20) {
        return;
    }

    attempt = 0;
    reference_object = &reference_tile_object;
    mode = (s16)spawn_mode;
    fixed_entry_offset = (mode - 2) * 2;

    for (; attempt < 0x10; ++attempt) {
        select_dungeon_spawn_tile(&tile_x, &tile_y);
        if ((s16)find_active_rect_containing_point(tile_x, tile_y) < 0) {
            continue;
        }

        if (mode == 0) {
            dx = abs(reference_object->tile_position.parts.tile_x - tile_x);
            dy = abs(reference_object->tile_position.parts.tile_y - tile_y);
            distance = dx + dy;
        }
        if ((s16)distance < 0x21) {
            continue;
        }

        {
            s16 entry_offset;
            u8 *spawn_entry;

            entry_offset = (mode < 2) ?
                             ((generate_random_value() & 0xF) * 2) : fixed_entry_offset;
            {
                u8 **spawn_table_addr = (u8 **)((u8 *)(&g_dungeon_status.monster_spawn_table));
                s32 signed_entry_offset = entry_offset;
                u8 *spawn_table = *spawn_table_addr;
                spawn_entry = (u8 *)(signed_entry_offset + (long)spawn_table);
            }
            raw_variant = spawn_entry[1];
            spawn_level = raw_variant;
            entity_spawn_variant_code = raw_variant;
            monster_type = spawn_entry[0];
        }

        if (monster_type == 0) {
            return;
        }
        monster = find_or_retain_sprite_resource_slot(monster_type, 1);
        if (monster == 0) {
            continue;
        }

        spawn_height = sample_terrain_surface_height((tile_x << 6) | 0x20, (tile_y << 6) | 0x20, -0x400);
        spawn_monster = load_monster_resource_data(monster_type, monster, 1);
        monster = spawn_monster(0, tile_x, tile_y, (s16)spawn_height);
        if (monster == 0) {
            return;
        }

        retain_spawn_resource(monster_type, 1);
        func_80042640(monster, monster_type);
        ((u8 *)monster)[0x43] = generate_random_value();
        ((u8 *)monster)[0x12] = 0;

        if (mode >= 2) {
            u8 *owner = *(u8 **)((u8 *)monster - 0x14);
            update_map_cell_flags_with_item_limit(owner[0x24], owner[0x25], 0x3000);
            detach_record_and_update_slot_state(monster);
            unlink_entity_node(monster);
            *(u16 *)((u8 *)monster - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }

        limits = level_experience_table;
        ((u32 *)((u8 *)monster + 0x18))[0] = limits[spawn_level];
        next_limits = limits + 1;
        if (*(u32 *)((u8 *)monster + 0x18) >= next_limits[((u8 *)monster)[0x11]]) {
            u32 *level_thresholds;
            u32 next_level_exp;
            level_thresholds = next_limits;
            do {
                /*
                 * BUG: second-tower spawn groups can request level 100 on floor 99. At level 99,
                 * raise_entity_level stops changing the monster, so this loop never exits.
                 * Found and documented by the Azure Dreams community
                 * (adrando.com/guide/bugs.html).
                 */
                raise_entity_level(monster, 0);
                next_level_exp = level_thresholds[((u8 *)monster)[0x11]];
            } while (*(u32 *)((u8 *)monster + 0x18) >= next_level_exp);
        }
        level_monster = monster;
        if (((u8 *)level_monster)[0x49] != 0) {
            return;
        }
        *(s32 *)((u8 *)monster + 0x48) = select_random_eligible_item_entry(monster);
        return;
    }
}
