#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"

typedef struct {
    s32 field0;
    u16 flags;
} DungeonCell;


extern s8 D_800DCF5B[9];

extern void func_80043B4C(void);

/* Mark fixed dungeon cells and initialize global coordinates and flags. */
void func_807AF2F4(void)
{
    MapGrid *dungeon;
    u8 *cells;
    RuntimeDispatchState *global_state;
    s32 coord;

    dungeon = &gameWork.map;
    cells = ((u8 *)dungeon->cells);

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x1D);

    coord = 0x23;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    coord = 0x12;
    do {
        ((DungeonCell *)(cells + (coord << dungeon->shiftX) * 6 + 0x60))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord << dungeon->shiftX) * 6 + 0x11A))->flags |= 0x8000;
        coord++;
    } while (coord < 0x20);

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x20 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord + (0x21 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    ((DungeonCell *)(cells + (0x23 << dungeon->shiftX) * 6 + 0xBA))->flags |= 0x8000;
    ((DungeonCell *)(cells + (0x23 << dungeon->shiftX) * 6 + 0xC0))->flags |= 0x8000;

    func_80043B4C();

    global_state = &D_80082E60;
    global_state->unk_10 = 0x1F;
    global_state->unk_12 = 0x39;
    D_800DCF5B[0] = 1;
    global_state->flags16 |= 1;
    D_800E296C |= 0x10000000;
}
