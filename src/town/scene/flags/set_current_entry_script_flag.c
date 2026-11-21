#include "common.h"
#include "shared/record_ptrs.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "shared/town_root.h"
#include "town/scene.h"

extern u8 D_80020000[];

/* Pass the current object set's flag to the module's flag writer. */
void set_current_entry_script_flag(void)
{
    /* BYTES: Each placed copy relocates the page symbol used to reach its table slot. */
    const u32 *table_address = (const u32 *)((unsigned long)D_80020000 - 0x3C90);
    s32 index = town_scene_root->unk_14;
    TownObjectSet *set = index + (TownObjectSet *)(unsigned long)*table_address;

    set_script_flag_bit(set->entry_flag);
}
