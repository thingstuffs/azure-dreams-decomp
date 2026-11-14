#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/person/position.h"
#include "town/map/object.h"
#include "town/map/position.h"
#include "town/player.h"

struct S_8003FE78;
struct Rec_D_800FE490; 

extern struct S_800C01DC_1 map_runtime_state;
#include "records/Rec_D_800CFCB4.h"
#include "town/data.h"
extern Rec_D_800CFCB4 town_actor_control;
extern u8 D_800D0420[];
#include "records/Rec_D_800FE490.h"
#include "shared/dungeon_projectile_views.h"
#include "town/scene.h"
#include "engine/scene.h"

extern Rec_D_800FE490 town_motion_list;

typedef struct S_800C01DC_1 {
    u8 pad_00[0x10];
    u16 * unk_10;
    u16 unk_14;
    u16 unk_16;
} S_800C01DC_1;   /* base in init_view_reference_entity */

/* Initializes the town object and sets its position from the current position entry. */
void init_view_reference_entity(void) {
    ProjectileObject *object;

    town_scene_init_callback = 0;
    object = initialize_scene_object_in_buffer(0, &scene_object_list_anchor.next, 0x22);
    object->update_callback = &init_minigame_player_actor;
    object->sprite = &reference_tile_object.frame_entry;
    object->position = &view_reference_entity.x.v;
    initialize_circular_list_head();
    init_scene_list_node(&town_actor_control, &view_reference_entity.x.v, &D_800D0420);
    init_town_motion_list();
    init_secondary_list_record(&town_motion_list, (s32)(&view_reference_entity.x.v), (s32)(&D_800D0420));
    {
        S_800C01DC_1 *position_data;
        u16 *position_entry;

        position_data = &map_runtime_state;
        position_entry = position_data->unk_10;
        view_reference_entity.x.w.i = (s16) (position_data->unk_14 + position_entry[0]);
        view_reference_entity.y.w.i = (s16) (position_data->unk_16 + position_entry[1]);
        view_reference_entity.z.w.i = query_lowered_transform_position(&view_reference_entity.x.v);
    }
    sync_collision_motion_xyz((void *)&view_reference_entity.x.v);
}
