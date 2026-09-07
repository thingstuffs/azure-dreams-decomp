typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    s16 value;
    s16 unk2;
    u16 flags;
} Entry;

typedef struct {
    Entry *entries;
    u8 pad4[0x10];
    s16 shift;
} DungeonGrid;

typedef struct {
    u8 pad0[0x1DC];
    DungeonGrid grid;
} SharedState;

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern SharedState D_80083160;

/* Returns the grid entry value at the selected offset and writes its flags. */
s16 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags)
{
    s32 grid_x;
    s32 grid_y;
    s32 index;
    SharedState *state;
    Entry *entry;

    grid_x = x + D_8006CCD8[offset_index];
    state = &D_80083160;
    grid_y = y + D_8006CCE8[offset_index];
    index = grid_x + (grid_y << state->grid.shift);
    entry = (Entry *)((index * sizeof(Entry)) +
                      (unsigned long)state->grid.entries);
    *flags = entry->flags;
    return entry->value;
}
