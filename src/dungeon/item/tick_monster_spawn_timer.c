#include "dungeon/item.h"
#include "dungeon/system/random.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[6];
    s16 field_0x6;
    u8 pad8[4];
} DungeonState;

#include "dungeon/level/room_count_data.h"


/* Counts down turns until a monster spawn, then resets the spawn timer. */
void tick_monster_spawn_timer(void) {
    s16 spawn_turns;

    if (dungeon_room_count != 0) {
        spawn_turns = g_dungeon_status.monster_spawn_timer - 1;
        g_dungeon_status.monster_spawn_timer = spawn_turns;
        if (spawn_turns < 0) {
            g_dungeon_status.monster_spawn_timer = (generate_random_value() & 0x1F) | 0x20;
            spawn_floor_monster_from_table(0);
        }
    }
}
