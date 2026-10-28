#include "common.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"

#include "town/person/object/initialize_object_entries_api.h"

extern s32 town_object_resource_table[];
extern s32 D_800D11D0[];
extern s32 D_800D11EC[];
extern s32 D_800AAB20[];

/* Initialize the object's resources, animation state, and callback table. */
void initialize_person_resources(void *object, void *transform, void *anim_state) {
    configure_the_set_mode_n_2(object, transform, &town_object_resource_table);
    initialize_optional_object_state(object, transform, anim_state, &D_800D11D0);
    initialize_object_entries(object, anim_state, D_800D11EC);
    *(void **)((s8 *)object - 0x10) = &D_800AAB20;
}
