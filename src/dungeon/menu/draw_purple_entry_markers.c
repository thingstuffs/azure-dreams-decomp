#include "dungeon/level/floor_flags.h"
#include "common.h"

extern void submit_activation_command(void);
extern void create_transformed_render_object(u8, u8, s32, s32, s32);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk3648;

typedef struct {
    u8 unk0[6];
    u8 unk6;
    u8 unk7;
    u8 unk8[16];
} Unk39C8;

extern Unk3648 floor_objects[0x20];
extern Unk39C8 dungeon_floor_object_positions[0x20];

/* Create purple markers at eligible entry positions. */
void draw_purple_entry_markers(void) {
    s32 i;

    submit_activation_command();
    for (i = 0; i < 0x20; i++) {
        if ((floor_objects[i].unk1 != 0) && (floor_objects[i].unk0 != 0) &&
            !(floor_objects[i].unk3 & 0x40)) {
            create_transformed_render_object(dungeon_floor_object_positions[i].unk6, dungeon_floor_object_positions[i].unk7,
                          0x802080, FLOOR_TRAPS_VISIBLE, i);
        }
    }
}
