#include "common.h"

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} PositionEntry;

extern void func_8009A350(s16, s16, s32, u16 *);
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

/* Finds an active entry at the given tile within 64 height units if the left tile has flag 0x800. */
s32 func_800A70E4(s32 input_x, s32 input_y, s32 input_z) {
    s32 held_x;
    s32 held_z;
    s32 held_y;
    s32 result;
    register s32 entry_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 y;
    u16 tile_flags;
    ActiveEntry *active_entry;
    PositionEntry *position;
    s32 height_delta;
    s32 x;
    s32 z;

    held_x = input_x;
    held_z = input_z;
    func_8009A350((s16)(held_x - 1), (held_y = (s16)input_y), 0, &tile_flags);
    entry_index = 0;
    if (tile_flags & 0x800) {
        goto scan;
    }
    result = -1;
    goto done;
success:
    result = (s16)entry_index;
    goto done;
scan:
    x = (s16)held_x;
    y = held_y;
    z = (s16)held_z;
    result = 0x800E0000;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    position = (PositionEntry *)(result + 0x36C8);
    result = 0x800E0000;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    active_entry = (ActiveEntry *)(result + 0x3548);
check_entry:
    if ((active_entry->active != 0) && (position->x == x) && (position->y == y)) {
        height_delta = z - position->value;
        if (height_delta < 0) {
            height_delta = 0 - height_delta;
        }
        if (height_delta >= 0x40) {
            goto next_entry;
        }
        goto success;
    }
next_entry:
    position++;
    entry_index += 1;
    active_entry++;
    if (entry_index >= 0x40) {
        result = -1;
        goto done;
    }
    goto check_entry;
done:
    ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    return result;
}

/* MECHANISM: True-space epilogue targets are two pre-scan return trampolines; s32 formals
   plus guarded s1/s2/s0 carriers reproduce the raw/narrow argument lifetimes and 0x28 saves.
   Counter/y carriers fix volatile roles; v0 page keeps emit the split +36C8/+3548 bases. */
