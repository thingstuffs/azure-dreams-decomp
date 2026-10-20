#include "common.h"
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

extern s32 D_80081458[];
extern u8 D_800AB1E0[];
extern u8 D_800AB708[];
extern u8 D_800D1200[];

/* Creates an object and initializes its state, rendering data, and position. */
void create_person_object(void) {
    s8 *object;
    s8 *state;
    s8 *position;
    s8 *render_data;

    object = (s8 *) create_town_effect_object(0, 0, D_800AB1E0, 0);
    state = object + 0x20;
    if (object != NULL) {
        position = *(s8 **)(object + 8);
        render_data = *(s8 **)(object + 0xC);
        *(s8 *)(state + 0x93) = 1;
        *(s32 *)(render_data + 0x28) = D_80081458[0];
        initialize_object_entries(state, render_data, D_800D1200);
        register_node_if_unregistered(state, project_sprite_chain);
        fill_person_records();
        *(s16 *)(state + 0x90) = 0;
        *(void **)(state + 0x50) = D_800AB708;
        *(s16 *)(state + 0x6A) = 0;
        *(u16 *)(position + 2) = (u16) ((u16)D_80083780.x.w.i);
        *(u16 *)(position + 6) = (u16) ((u16)D_80083780.y.w.i);
        *(s16 *)(position + 0xA) = (s16) (((u16)D_80083780.z.w.i) - get_person_lookup_step(position));
    }
}
