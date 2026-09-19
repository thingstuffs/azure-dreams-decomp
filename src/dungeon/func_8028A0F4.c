#include "common.h"

typedef struct {
    u8 pad0[12];
    u8 *entries;
    u8 pad10[4];
} DungeonGroup;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} DungeonRect;

typedef struct {
    u8 pad0[6];
    u8 px;
    u8 py;
    u8 pad8[16];
} DungeonSpot;

typedef struct {
    u8 kind;
    u8 f1;
    u8 f2;
    u8 f3;
} DungeonSlot;

extern void func_8009A21C(u8, u8, s32);
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);
extern DungeonGroup D_80073414[];
extern DungeonSlot D_800E3648[];
extern DungeonSpot D_800E39C8[];

/* Populate dungeon slots at random eligible positions within the rectangle. */
void func_8001D0F4(DungeonRect *rect)
{
    u16 tile_flags;
    s32 slot_limit_calc;
    s16 slot_limit;
    s32 item_kind;
    s16 stored_kind;
    s32 special_roll;
    s32 slot_index;
    u32 kind_roll;
    u16 item_flags;
    DungeonGroup *item_category_table;
    u32 x_offset;
    u32 y_offset;

    special_roll = func_800A6D30() & 0xFF;
    slot_limit_calc = ((rect->height * rect->width) >> 3) +
                 (func_800A6D30() & 7);
    slot_limit = slot_limit_calc;
    if ((s16)slot_limit_calc >= 29) {
        slot_limit = 28;
    }
    slot_index = (s16)slot_limit;

    if (slot_index >= 0) {
        item_category_table = D_80073414;
        
        
        
        do {
            x_offset = func_800A6DA4(0, (rect->width - 1) & 0xFFFF) & 0xFFFF;
            y_offset = func_800A6DA4(0, (rect->height - 1) & 0xFFFF) & 0xFFFF;
            func_8009A350((s16)(rect->x + x_offset - 1),
                          (s16)(rect->y + y_offset), 0, &tile_flags);
            if (!(tile_flags & 0x8820)) {
                D_800E39C8[slot_index].px = (u8)rect->x + x_offset;
                D_800E39C8[slot_index].py = (u8)rect->y + y_offset;
                if (special_roll == 0) {
                    D_800E3648[slot_index].kind = 7;
                } else {
                    kind_roll = func_800A6D30() & 0xFFFF;
                    item_kind = (kind_roll % 19) + 1;
                    item_flags = *(u16 *)(item_category_table[21].entries +
                                           ((s16)item_kind * 12));
                    stored_kind = item_kind;
                    if ((item_flags & 0x3000) == 0x3000) {
                        goto next_spot;
                    }
                    D_800E3648[slot_index].kind = stored_kind;
                }
                D_800E3648[slot_index].f1 = 0x15;
                D_800E3648[slot_index].f3 = 0x80;
                D_800E3648[slot_index].f2 = 0;
                func_8009A21C(D_800E39C8[slot_index].px, D_800E39C8[slot_index].py, 0x20);
            }
next_spot:
            
            slot_index--;
        } while (slot_index >= 0);
    }
}
