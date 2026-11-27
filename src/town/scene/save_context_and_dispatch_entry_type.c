#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/data.h"

typedef void (*TownEntryAction)(TownObjectSet *, s32, s32);

extern TownObjectSet *active_object_sets;

/* Save the scene context and invoke the action for the selected choice. */
void save_context_and_dispatch_entry_type(void) {
    TownObjectSet *set = active_object_sets + town_scene_root->unk_14;
    s32 choice_index = (u8)set->flags;
    s32 action_index;

    scene_current_entry_value = (s32)(unsigned long)town_scene_root->unk_00;
    action_index = (u8)set->flags;
    ((TownEntryAction)set->choices[action_index].text)(
        set, choice_index, (s32)(unsigned long)town_scene_root->unk_00);
}
