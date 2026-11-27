#include "common.h"
#include "dungeon/system/random.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"


/* Stores the low four bits of the computed result in the global slot. */
void store_random_nibble(void) {
    g_dungeon_status.monster_spawn_timer = generate_random_value() & 0xF;
}
