#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


typedef struct {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
} ByteBuf;

typedef struct {
    u8 x;
    u8 y;
} CoordBuf;

s32 test_resident_bit(s32);
void upload_vram_row_and_cache(void *, s32, s32, s32);
s32 select_dungeon_spawn_tile(u8 *, u8 *);
s32 get_item_category_value(u8 *item);
void place_item_at_valid_floor_position(u8, u8, s16, s32, void *);
s16 sample_terrain_surface_height(s32, s32, s16);
s32 has_saved_entry_key(s32, s32);
s32 has_active_dungeon_cell_key(s32, s32);
extern u8 D_80081484[];
extern u8 D_800F6D48[];

/* Advance the animation and handle delayed object spawning. */
void animate_and_schedule_dungeon_spawn(EntityRec *state) {
    ByteBuf spawn_data;
    CoordBuf spawn_tile;
    s16 spawn_height;
    s16 spawn_delay;
    s32 height_result;
    u16 anim_ticks;
    u16 anim_offset;

    anim_ticks = ((u16)state->x.w.i) - 1;
    state->x.w.i = anim_ticks;
    if ((anim_ticks << 0x10) <= 0) {
        state->x.w.i = 1U;
        anim_offset = ((u16)state->y.w.i) + 8;
        state->y.w.i = anim_offset;
        if ((s16) anim_offset >= 0x70) {
            state->y.w.i = 0U;
        }
        upload_vram_row_and_cache(D_800F6D48 + ((s16) ((u16)state->y.w.i) * 4), 0x7380, 1, 2);
    }
    if ((test_resident_bit(0xA2) != 0) && ((has_saved_entry_key(6, 3) << 0x10) == 0) && ((has_active_dungeon_cell_key(6, 3) << 0x10) == 0)) {
        u8 *mode;
        mode = D_80081484;
        if ((mode[0] != 3) || (mode[1] != 6)) {
            if ((*(s16 *)&state->z) == 0) {
                (*(s16 *)&state->z) = 0x40;
            }
        }
    }
    if ((*(s16 *)&state->z) != 0) {
        spawn_delay = (u16) (*(s16 *)&state->z) - 1;
        (*(s16 *)&state->z) = spawn_delay;
        if ((spawn_delay << 0x10) == 0) {
            spawn_data.a = 3;
            spawn_data.b = 6;
            spawn_data.c = 0;
            spawn_data.d = 0;
            do {

            } while ((select_dungeon_spawn_tile(&spawn_tile.x, &spawn_tile.y) << 0x10) < 0);
            height_result = sample_terrain_surface_height((spawn_tile.x << 6) | 0x20, (spawn_tile.y << 6) | 0x20, -0x400);
            spawn_height = height_result;
            place_item_at_valid_floor_position(spawn_tile.x, spawn_tile.y, spawn_height, get_item_category_value(&spawn_data), &spawn_data);
        }
    }
}
