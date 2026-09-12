#include "common.h"

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} SpawnEntry;

typedef struct {
    u16 flags;
    u16 value;
    u16 extra;
} MapCell;

extern u16 func_800A4E2C(u8 *, u8 *);
extern void func_8009A21C(s32, s32, s32);
extern s32 func_800A6D30(void);

extern s32 D_80012090;
extern s16 D_8008146C;
extern u8 D_8008333C[32];
extern u8 D_800E3548[];
extern u8 D_800E3648[];
extern u8 D_800E36C8[];
extern u8 D_800E39C8[];
extern u8 D_800E3CD8[];

/* Spawns up to four elevators at unoccupied positions and updates their map cells. */
void func_8001784C(void) {
    s32 state;
    u8 x;
    u8 y;
    register u8 *config ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    MapCell *map;
    s32 spawn_count;
    s32 slot_index;
    u8 *meta_base;
    SpawnEntry *entries;

    {
        u8 *state_page;
        state_page = (u8 *)0x80010000;
        state = *(s32 *)(state_page + 0x2090);
    }
    config = D_8008333C;
    map = *(MapCell **)D_8008333C;

    if ((state == 2) || (D_8008146C != 0x28)) {
        spawn_count = 0;
        meta_base = D_800E3548;

retry:
        do {
        } while ((s16)func_800A4E2C(&x, &y) < 0);

        {
            u8 *meta;
            u8 *position;

            slot_index = 0;
            position = D_800E36C8;
            meta = meta_base;

            do {
                if ((meta[1] != 0) && (position[0] == x) &&
                    (position[1] == y)) {
                    goto retry;
                }
                position += 12;
                slot_index++;
                meta += 4;
            } while (slot_index < 0x40);
        }

        {
            register u8 *position_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *meta;
            register u8 *position ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            slot_index = 0;
            position_page = (u8 *)0x800e0000;
            ASM_KEEP(position_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            position = position_page + 0x39c8;
            meta = (u8 *)&D_800E3648;

            do {
                if ((meta[1] != 0) && (position[6] == x) &&
                    (position[7] == y)) {
                    goto retry;
                }
                position += 24;
                slot_index++;
                meta += 4;
            } while (slot_index < 0x20);
        }

        entries = (SpawnEntry *)D_800E3CD8;
        {
            SpawnEntry *entry = &entries[spawn_count];
            s32 spawn_x;
            s32 spawn_y;
            s32 cell_offset;
            s32 row_offset;
            s32 update_row_shift;
            s32 copy_row_shift;
            s32 flags_row_shift;
            s32 cell_flags;
            s32 cell_index;
            MapCell *spawn_cell;
            s32 update_size;

            spawn_x = x;
            spawn_y = y;
            entry->kind = 2;
            entry->x = spawn_x;
            entry->y = spawn_y;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

            row_offset = y;
            update_row_shift = *(s16 *)(config + 0x14);
            cell_offset = x;
            cell_index = cell_offset + (row_offset << update_row_shift);
            map[cell_index].value -= 0x20;

            copy_row_shift = *(s16 *)(config + 0x14);
            entry->value = map[cell_offset + (row_offset << copy_row_shift)].value;

            flags_row_shift = *(s16 *)(config + 0x14);
            ASM_KEEP(flags_row_shift);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            cell_flags = 1;
            ASM_KEEP(cell_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            row_offset <<= flags_row_shift;
            cell_offset += row_offset;
            spawn_cell = (MapCell *)(cell_offset * 6 + (s32)map);
            update_size = 0x20;
            spawn_cell->flags = cell_flags;
            func_8009A21C(spawn_x, spawn_y, update_size);
        }

        if ((func_800A6D30() & 0x3F) == 0) {
            spawn_count++;
            if (spawn_count < 4) {
                goto retry;
            }
        }

        spawn_count++;
        while (spawn_count < 4) {
            entries[spawn_count].kind = 0;
            spawn_count++;
        }
    }
}
