#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/person/position.h"

struct S_8003FE78; void * initialize_scene_object_in_buffer(s32, struct S_8003FE78 *, s16);
void initialize_circular_list_head(void);
struct Rec_D_800CFCB4; void handle_insert_initialize_two_values_status_flags(struct Rec_D_800CFCB4 *, s32, s32);
void initialize_pointer_table_self_links(void);
struct Rec_D_800FE490; void initialize_the_store_two_values_set_state_flags(struct Rec_D_800FE490 *, s32, s32);
void run_the_three_update_routines_context(s32);

extern struct S_800C01DC_1 map_runtime_state;
typedef struct S_800C02C4_1 S_800C02C4_1;
void initialize_object_rendering_resources(void *object_data, void *unused, S_800C02C4_1 *render_data);
#include "records/Rec_D_800CFCB4.h"
extern Rec_D_800CFCB4 town_actor_control;
extern u8 D_800D0420[];
extern s32 town_scene_init_callback;
#include "records/Rec_D_800FE490.h"
#include "shared/dungeon_projectile_views.h"
extern Rec_D_800FE490 town_motion_list;



typedef struct S_800C01DC_1 {
    u8 pad_00[0x10];
    u16 * unk_10;
    u16 unk_14;
    u16 unk_16;
} S_800C01DC_1;   /* base in initialize_object_at_current_position */

/* Initializes the town object and sets its position from the current position entry. */
void initialize_object_at_current_position(void) {
    ProjectileObject *object;

    town_scene_init_callback = 0;
    object = initialize_scene_object_in_buffer(0, ((void *)&scene_object_list_anchor.next), 0x22);
    object->update_callback = &initialize_object_rendering_resources;
    object->sprite = &reference_tile_object.frame_entry;
    object->position = &view_reference_entity.x.v;
    initialize_circular_list_head();
    handle_insert_initialize_two_values_status_flags(&town_actor_control, (s32)(&view_reference_entity.x.v), (s32)(&D_800D0420));
    initialize_pointer_table_self_links();
    initialize_the_store_two_values_set_state_flags(&town_motion_list, (s32)(&view_reference_entity.x.v), (s32)(&D_800D0420));
    {
        s8 *position_data;
        u16 *position_entry;

        position_data = (s8 *) &map_runtime_state;
        position_entry = ((S_800C01DC_1 *)position_data)->unk_10;
        view_reference_entity.x.w.i = (s16) (((S_800C01DC_1 *)position_data)->unk_14 + position_entry[0]);
        view_reference_entity.y.w.i = (s16) (((S_800C01DC_1 *)position_data)->unk_16 + position_entry[1]);
        view_reference_entity.z.w.i = query_lowered_transform_position(&view_reference_entity.x.v);
    }
    run_the_three_update_routines_context((s32)(&view_reference_entity.x.v));
}
