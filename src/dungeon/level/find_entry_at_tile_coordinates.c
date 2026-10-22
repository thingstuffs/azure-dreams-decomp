#include "common.h"

typedef struct {
    u8 unk0;
    u8 active;
    u8 unk2;
    u8 unk3;
} Slot;

typedef struct {
    u8 unk0[6];
    u8 x;
    u8 y;
    u8 unk8[0xA];
    s16 z;
    u8 unk14[4];
} Status;

extern Slot floor_objects[];
extern Status dungeon_floor_object_positions[];
extern s32 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Finds an active floor object at the tile within 64 height units, or returns -1. */
s32 find_entry_at_tile_coordinates(s16 x, s16 y, s16 z) {
    s32 rv;
    u16 flags;
    s32 i;
    s32 delta;

    if ((get_offset_map_cell_value_and_flags(x - 1, y, 0, &flags) << 16) == 0) {
        rv = -1;
        return rv;
    }
    if (flags & 0x20) {
        i = 0;
        do {
            if (floor_objects[i].active != 0 && dungeon_floor_object_positions[i].x == x &&
                dungeon_floor_object_positions[i].y == y) {
                delta = z - dungeon_floor_object_positions[i].z;
                if (delta < 0) {
                    delta = -delta;
                }
                if (delta < 0x40) {
                    rv = (s16)i;
                    return rv;
                }
            }
            i++;
        } while (i < 0x20);
    }
    return -1;
}

/* MECHANISM: func_800B510C is a j-only noreturn dispatcher (config/sibcall_syms.dungeon.txt)
   that is SERVED ITS ARGUMENT IN $v0, so the return value must be materialised BEFORE the
   tail call, not after it: an `s32 rv` carrier assigned then
   `func_800B510C(); return rv;`. */
