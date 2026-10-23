#include "common.h"
#include "shared/entity_objects.h"

extern void fill_person_records(void);
extern s32 get_person_lookup_step(void *coordinates);
extern u8 person_object_update_address[];
extern u8 person_approach_state_address[];


/* Initialize state and copy default values, adjusting the final output value. */
void initialize_person_state(void *state, void *output) {
    *(void **)((s8 *)state - 0x10) = person_object_update_address;
    fill_person_records();
    *(s16 *)((s8 *)state + 0x90) = 0;
    *(void **)((s8 *)state + 0x50) = person_approach_state_address;
    *(s16 *)((s8 *)state + 0x6A) = 0;

    {
        *(u16 *)((s8 *)output + 2) = ((u16)view_reference_entity.x.w.i);
        *(u16 *)((s8 *)output + 6) = ((u16)view_reference_entity.y.w.i);
        *(s16 *)((s8 *)output + 0xA) = ((u16)view_reference_entity.z.w.i) - get_person_lookup_step(output);
    }
}
