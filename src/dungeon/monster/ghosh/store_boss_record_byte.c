#include "common.h"
#include "dungeon/monster/ghosh.h"

/* Stores a byte at the given offset in the resident byte table. */
void store_boss_record_byte(s32 offset, s8 value) {
    ((s8 *)0x8001360C)[offset] = value;
}
