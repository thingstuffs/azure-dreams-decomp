#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#ifndef NULL
#define NULL 0
#endif

extern void *create_town_effect_object(s32 parent, s32 position, void *object_value, s32 state_value);
extern s32 get_person_lookup_step(void *coordinates);
extern void fill_person_records(void);
extern void initialize_object_entries(void *state, s32 output, void *entries);
extern void register_node_if_unregistered(void *state, void *callback);

extern s32 loaded_town_resource_attributes[];
extern u8 D_800AB1E0[];
extern u8 D_800AB708[];
extern u8 D_800D1200[];

/* Creates an object and initializes its state, rendering data, and position. */
void create_person_object(void) {
    ObjectNodeHeader *object;
    s8 *state;
    ObjectPosition *position;
    SpriteFrameState *render_data;

    object = (s8 *) create_town_effect_object(0, 0, D_800AB1E0, 0);
    state = ((s8 *)object) + 0x20;
    if (object != NULL) {
        position = *(s8 * *)&object->position;
        render_data = *(s8 * *)&object->sprite;
        *(s8 *)(state + 0x93) = 1;
        render_data->unk_28 = loaded_town_resource_attributes[0];
        initialize_object_entries(state, render_data, D_800D1200);
        register_node_if_unregistered(state, project_sprite_chain);
        fill_person_records();
        *(s16 *)(state + 0x90) = 0;
        *(void **)(state + 0x50) = D_800AB708;
        *(s16 *)(state + 0x6A) = 0;
        position->x.w.i = (u16) ((u16)view_reference_entity.x.w.i);
        position->y.w.i = (u16) ((u16)view_reference_entity.y.w.i);
        position->z.w.i = (s16) (((u16)view_reference_entity.z.w.i) - get_person_lookup_step(position));
    }
}
