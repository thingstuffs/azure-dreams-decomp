/* Build and join monster status display chains (G00632). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8D04, CL:town/func_800B8D2C. */
#include "town/shop/monster_status_display_chains_g00632.h"
#include "town/shop.h"

/*
 * Calls build_reverse_indexed_chain with (struct S_800491F4 * *)nodes,
 * monster_status_chain_indices, 24 and returns its result.
 */
void *link_monster_status_main_entries(s32 nodes) {
    return build_reverse_indexed_chain((struct S_800491F4 **)nodes, monster_status_chain_indices, 24);
}

/* Stores the fetched chain and initializes its terminal link. */
void join_monster_status_display_chains(S_800B648C_0 *owner, s32 source) {
    S_800B648C_1 *tail;

    tail = link_monster_status_main_entries(source);
    owner->unk_0C = tail;
    if (tail->unk_0C.s != 0) {
        do {
            tail = tail->unk_0C.u;
        } while (tail->unk_0C.s != 0);
    }
    tail->unk_0C.s = link_monster_status_display_entries(source);
}

/* Processes the object's embedded data, then selects a handler by its mode flag. */
void process_object_data_by_mode(void *object) {
    join_monster_status_display_chains(object + 0x88, ((S_800B6508_0 *)object)->unk_98);
    if (((S_800B6508_0 *)object)->unk_08 != 0) {
        func_800B640C(((S_800B6508_0 *)object)->unk_04, ((S_800B6508_0 *)object)->unk_98,
            ((S_800B6508_0 *)object)->unk_14);
        return;
    }
    initialize_display_entry(((S_800B6508_0 *)object)->unk_04, (void *)(((S_800B6508_0 *)object)->unk_98), ((S_800B6508_0 *)object)->unk_14);
}
