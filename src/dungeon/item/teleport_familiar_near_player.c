#include "shared/object_node.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"


#ifndef NULL
#define NULL 0
#endif


typedef struct S_800C1F28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C1F28_1;


typedef struct {
    u8 pad[0x24];
    u8 coord0;
    u8 coord1;
} Coord;

typedef struct {
    u8 pad0[0x1C];
    u32 flags;
    u8 pad1[0x68];
    u16 value;
} ArgObj;

typedef struct {
    u8 pad[8];
    u16 value;
} Entry;

extern s16 D_800DCED4[];
extern u8 D_800C1EC4;

extern s32 get_entity_class(void *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern s32 find_valid_nearby_position(u8 *entry, s16 target_x, s16 target_y, s16 *out_x, s16 *out_y);
extern u16 sample_terrain_surface_height(s32, s32, s16);
extern void create_orbiting_teleport_effect(void *owner, s16 effect_value, s16 direction, s16 effect_mode);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Creates a relocation task and updates the object's tile and height. */
void *teleport_familiar_near_player(void *object, s16 action_arg) {
    s16 tile_x;
    s16 tile_y;
    s32 tile_mask;
    u16 target_height;
    u16 source_height;
    u8 source_y;
    S_800C1F28_1 *task_object;
    u8 *position;
    u8 *task_data;
    void *task;
    s32 object_index;
    u8 old_x;
    u8 old_y;

    task = func_8003FC64(2);
    if (task != NULL) {
        object_index = get_entity_class(object);
        create_orbiting_teleport_effect(object, D_800DCED4[object_index], action_arg, 3);
        tile_mask = 0x3000;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        position = *(u8 **)((u8 *)object - 0x14);
        task_data = (u8 *)task + 0x20;
        old_x = position[0x24];
        old_y = position[0x25];
        if (((Rec_D_80082E80 *)object)->unk_1C.at00_u32.v & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);
        if ((find_valid_nearby_position(0, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &tile_x, &tile_y) << 16) == 0) {
            tile_x = ((Coord *)position)->coord0;
            source_height = ((ArgObj *)object)->value;
            source_y = ((Coord *)position)->coord1;
            tile_y = source_y;
            ((Entry *)task_data)->value = source_height;
        } else {
            target_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0,
                                          ((tile_y << 6) + 0x20) & 0xFFE0,
                                          (s16)(((Rec_D_80082E80 *)object)->unk_88.as_u16 - 0x20));
            *(u16 *)(task_data + 8) = target_height;
            if ((s16)target_height >= 0x201) {
                *(u16 *)(task_data + 8) = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0,
                                                        ((tile_y << 6) + 0x20) & 0xFFE0,
                                                        -0x400);
            }
        }
        position[0x24] = (u8)tile_x;
        position[0x25] = (u8)tile_y;
        ((Rec_D_80082E80 *)object)->unk_88.as_u16 = *(u16 *)(task_data + 8);
        *(void **)((u8 *)task + 0x10) = &D_800C1EC4;
        *(void **)(task_data + 0xC) = object;
        *(s16 *)(task_data + 2) = 0x20;
        *(s16 *)(task_data + 4) = position[0x24];
        task_object = *(void **)(task_data + 0xC);
        *(s16 *)(task_data + 6) = position[0x25];
        cycle_map_cell_flags(position[0x24], position[0x25],
                      (task_object->unk_1C & 0x2000) ? 0x300 : 0x3000);
    }
    return task;
}
