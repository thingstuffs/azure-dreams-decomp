#include "common.h"

typedef struct {
    s32 base;
    u8 pad_04[0x10];
    s16 shift;
} DungeonState;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Packed8;

extern u8 D_80082E80[0x28];
extern DungeonState D_8008333C;
extern u16 D_80083462;
extern s32 D_800814A0;
extern u8 *D_800814A8;
extern u8 D_800DCF5B;
extern u8 *D_800E3D7C;
extern Packed8 D_800F8B24;

extern void func_80043A68(void);
extern void func_80094E34(void);

#define CLEAR_HIGH_BIT(ptr) \
    (*(u16 *)((u8 *)(ptr) + 4) = *(u16 *)((u8 *)(ptr) + 4) & 0x7FFF)

/* Reveal the fixed-map cheat: set the map mode from the item used, clear the hidden bit on every listed tile and finish the owner. */
void func_807AEF8C(void *owner) {
    DungeonState *state;
    s32 base;
    u8 *tile;
    u8 *tile_b;
    u8 *row_tile;
    u8 *row_tile_b;
    u8 *col_tile;
    u8 *col_tile_b;
    u8 *edge_tile;
    u8 *edge_tile_b;
    u8 *mode_page;
    u8 *objects;
    u8 *object;
    u32 copy_dest;
    u16 flags;
    s16 mode;
    s32 i;
    s32 i3;

    base = D_8008333C.base;
    mode = 0;
    state = &D_8008333C;
    if (!(D_80083462 & 2)) {
        return;
    }
    if (*(s32 *)(D_800E3D7C + 0x14) & 0x100000) {
        return;
    }
    if (D_80082E80[0x25] != 0x24) {
        return;
    }
    if (D_80082E80[0x24] == 0x1F) {
        mode = 2;
    } else if (D_80082E80[0x24] == 0x20) {
        mode = 1;
    }
    if (mode == 0) {
        return;
    }

    func_80094E34();
    copy_dest = 0x80013720;
    *(Packed8 *)copy_dest = D_800F8B24;
    mode_page = (u8 *)0x80010000;
    flags = *(u16 *)(mode_page + 0x3714);
    *(s16 *)(mode_page + 0x371A) = mode - 1;
    *(u16 *)(mode_page + 0x3718) = 0;
    *(u16 *)(mode_page + 0x3716) = 0;
    *(u16 *)(mode_page + 0x3714) = flags | 1;

    tile = (u8 *)(((0x23 << state->shift) * 6) + base + 0xBA);
    CLEAR_HIGH_BIT(tile);
    tile_b = (u8 *)(((0x23 << state->shift) * 6) + base + 0xC0);
    CLEAR_HIGH_BIT(tile_b);

    i = 0x10;
    do {
        row_tile = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(row_tile);
        i++;
    } while (i < 0x1D);

    i = 0x23;
    do {
        row_tile_b = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(row_tile_b);
        i++;
    } while (i < 0x30);

    i3 = 0x12;
    do {
        col_tile = (u8 *)(((i3 << state->shift) * 6) + base + 0x60);
        CLEAR_HIGH_BIT(col_tile);
        col_tile_b = (u8 *)(((i3 << state->shift) * 6) + base + 0x11A);
        CLEAR_HIGH_BIT(col_tile_b);
        i3++;
    } while (i3 < 0x20);

    i = 0x10;
    do {
        edge_tile = (u8 *)(((i + (0x20 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(edge_tile);
        edge_tile_b = (u8 *)(((i + (0x21 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(edge_tile_b);
        i++;
    } while (i < 0x30);

    func_80043A68();
    i = 0;
    *(u16 *)((u8 *)owner - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
    objects = D_800814A8;
    do {
        object = *(u8 **)(objects + 0xAC);
        if (object != 0) {
            *(u16 *)(object + 0x46) &= 0x7FFF;
        }
        i++;
        objects += 4;
    } while (i < 2);
    D_800DCF5B = 0;
}
