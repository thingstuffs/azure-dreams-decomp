#include "common.h"

typedef struct {
    u8 *field0;
    u8 pad04[0x10];
    s16 field14;
} DungeonState;

typedef struct {
    s32 field0;
    u16 flags;
} DungeonCell;

typedef struct {
    u8 pad00[0x10];
    s16 field10;
    s16 field12;
    s16 field14;
    u16 field16;
} GlobalState;

extern DungeonState D_8008333C;
extern GlobalState D_80082E60;
extern s8 D_800DCF5B[9];
extern s32 D_800E296C[3];

extern void func_80043B4C(void);

/* Mark fixed dungeon cells and initialize global coordinates and flags. */
void func_807AF2F4(void)
{
    DungeonState *dungeon;
    u8 *cells;
    GlobalState *global_state;
    s32 coord;

    dungeon = &D_8008333C;
    cells = dungeon->field0;

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->field14)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x1D);

    coord = 0x23;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->field14)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    coord = 0x12;
    do {
        ((DungeonCell *)(cells + (coord << dungeon->field14) * 6 + 0x60))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord << dungeon->field14) * 6 + 0x11A))->flags |= 0x8000;
        coord++;
    } while (coord < 0x20);

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x20 << dungeon->field14)) * 6))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord + (0x21 << dungeon->field14)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    ((DungeonCell *)(cells + (0x23 << dungeon->field14) * 6 + 0xBA))->flags |= 0x8000;
    ((DungeonCell *)(cells + (0x23 << dungeon->field14) * 6 + 0xC0))->flags |= 0x8000;

    func_80043B4C();

    global_state = &D_80082E60;
    global_state->field10 = 0x1F;
    global_state->field12 = 0x39;
    D_800DCF5B[0] = 1;
    global_state->field16 |= 1;
    D_800E296C[0] |= 0x10000000;
}
