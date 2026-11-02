#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person/state.h"
#include "town/person/object.h"
extern s32 person_menu_object_entries[];
extern u8 D_800D55A0[];
extern u8 D_800D55A8[];
extern u8 D_800D55D0[];
extern u8 D_800D55D4[];

/* Resets menu state and switches handlers when the input flags request it. */
void reset_menu_state(TownObjectRecord *menu, ObjectPosition *update_arg, void *input) {
    if (*(u16 *)((u8 *)input + 0x14) & 0x6000) {
        initialize_object_entries(menu, input, person_menu_object_entries);
        object_index_slots[menu->slot].unk_00 = 0;
        *(void **)((u8 *)menu + 0x58) = D_800D55D0;
        *(void **)((u8 *)menu + 0x5C) = D_800D55D4;
        menu->unk_7C.as_pv = D_800D55A0;
        *(void **)((u8 *)menu + 0x80) = D_800D55A8;
        menu->unk_70 = 0;
        apply_object_setup_and_update(menu, update_arg, input);
    }
}
