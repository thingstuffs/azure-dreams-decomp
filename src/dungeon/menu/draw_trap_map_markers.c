#include "dungeon/level/floor_flags.h"
#include "common.h"
#include "dungeon/menu.h"

extern void * create_map_marker(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode);

typedef struct {
    u8 kind;
    u8 category;
    u8 unk2;
    u8 flags;
} Unk3648;

typedef struct {
    u8 unk0[6];
    u8 tile_x;
    u8 tile_y;
    u8 unk8[16];
} Unk39C8;

extern Unk3648 floor_objects[0x20];
extern Unk39C8 dungeon_floor_object_positions[0x20];

/* Create purple markers at eligible entry positions. */
void draw_trap_map_markers(void) {
    s32 i;

    begin_map_marker_draw();
    for (i = 0; i < 0x20; i++) {
        if ((floor_objects[i].category != 0) && (floor_objects[i].kind != 0) &&
            !(floor_objects[i].flags & 0x40)) {
            create_map_marker(dungeon_floor_object_positions[i].tile_x, dungeon_floor_object_positions[i].tile_y,
                          0x802080, FLOOR_TRAPS_VISIBLE, i);
        }
    }
}
