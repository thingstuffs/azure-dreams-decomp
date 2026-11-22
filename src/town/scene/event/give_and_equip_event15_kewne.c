#include "common.h"
#include "shared/monster_ids.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void give_and_equip_event15_kewne(void) {
    TownListEntry *item;
    Rec_D_80016000 *root;
    TownServiceTable *services;
    unsigned char slot;

    town_scene_root->services->load_name_window(0);
    item = town_scene_root->services->set_item_w0(MONSTER_KEWNE, 0x13, 0, 0);
    root = town_scene_root;
    slot = item->flags & 0x3F;
    services = root->services;
    item->flags = slot;
    /* BYTES: The second assignment to the root register keeps the state load beside the flag store. */
    root = (Rec_D_80016000 *)root->town_state;
    /* BYTES: The copy service reads all four entry bytes. Reusing the root register keeps the state load beside the flag store. */
    services->copy_monster_to_slot(0, item, &((TownStateRecord *)root)->saved_monsters[slot], 1);
    town_scene_root->services->equip_item(MONSTER_KEWNE, 0x13);
    town_scene_root->services->set_packed_flag(2, 1);
}
