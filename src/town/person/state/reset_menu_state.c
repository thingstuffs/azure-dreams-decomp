#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person/state.h"
#include "town/person/object.h"
#include "town/data.h"
extern s32 D_800D55A0[];
extern PersonDescriptor D_800D55A8;
extern s32 D_800D55D0[];
extern TownIndexedHandler D_800D55D4[];

/* Resets menu state and switches handlers when the input flags request it. */
void reset_menu_state(TownObjectRecord *menu, ObjectPosition *update_arg, SpriteFrameState *input) {
    if (input->flags & 0x6000) {
        initialize_object_entries(menu, input, person_menu_object_entries);
        object_index_slots[menu->slot].motion_id = 0;
        menu->state_handlers = D_800D55D0;
        menu->indexed_handlers = D_800D55D4;
        menu->animation_tables.as_pv = D_800D55A0;
        menu->descriptor = &D_800D55A8;
        menu->bounds_index = 0;
        apply_object_setup_and_update(menu, update_arg, input);
    }
}
