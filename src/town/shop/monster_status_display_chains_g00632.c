/* Build and join monster status display chains. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8D04, CL:town/func_800B8D2C. */
#include "town/shop/monster_status_display_chains_g00632.h"
#include "town/shop.h"
#include "town/shop/state.h"
#include "engine/texture.h"

/*
 * Calls build_reverse_indexed_chain with (struct S_800491F4 * *)nodes,
 * monster_status_chain_indices, 24 and returns its result.
 */
void *link_monster_status_main_entries(s32 nodes) {
    return build_reverse_indexed_chain((struct S_800491F4 **)nodes, monster_status_chain_indices, 24);
}

/* Stores the fetched chain and initializes its terminal link. */
void join_monster_status_display_chains(ItemMenuPart *owner, s32 source) {
    ItemMenuPart *tail;

    tail = link_monster_status_main_entries(source);
    owner->next = tail;
    if (tail->next != 0) {
        do {
            tail = tail->next;
        } while (tail->next != 0);
    }
    tail->next = link_monster_status_display_entries(source);
}

/* Processes the object's embedded data, then selects a handler by its mode flag. */
void process_object_data_by_mode(Rec_func_800B683C_arg0 *object) {
    join_monster_status_display_chains((void *)object + 0x88, (s32)object->unk_98);
    if (object->unk_08 != 0) {
        func_800B640C(object->unk_04, (s32)object->unk_98,
            object->unk_14);
        return;
    }
    initialize_display_entry(object->unk_04, object->unk_98, object->unk_14);
}
