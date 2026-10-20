#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[6];
    s16 field_0x6;
    u8 pad8[4];
} DungeonState;

extern void spawn_floor_monster_from_table(s32);
extern s32 generate_random_value(void);
extern s16 D_8008146E;


/* Counts down turns until a monster spawn, then resets the spawn timer. */
void tick_monster_spawn_timer(s32 unused0, s32 unused1, s32 unused2, s32 unused3) {
    s16 spawn_turns;

    if (D_8008146E != 0) {
        spawn_turns = g_dungeon_status.unk_06 - 1;
        g_dungeon_status.unk_06 = spawn_turns;
        if (spawn_turns < 0) {
            g_dungeon_status.unk_06 = (generate_random_value() & 0x1F) | 0x20;
            spawn_floor_monster_from_table(0);
        }
    }
}
