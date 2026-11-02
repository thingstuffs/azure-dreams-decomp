#ifndef TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
#define TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
/* Build and join monster status display chains (G00632): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8D04, CL:town/func_800B8D2C. */

#include "common.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "shared/item_menu.h"


/* arg0 in join_monster_status_display_chains */

/* extern */

/* extern */

struct S_800491F4;
extern struct S_800491F4 *build_reverse_indexed_chain(struct S_800491F4 **node_table, u8 *indices, s32 index_limit);
extern u8 monster_status_chain_indices[];
/* extern */
void initialize_display_entry(s32, void *, s32);
/* extern */
void func_800B640C(s32, s32, s32);

/* Functions defined in this translation unit. */
void *link_monster_status_main_entries(s32 nodes);
void join_monster_status_display_chains(ItemMenuPart *owner, s32 source);
void process_object_data_by_mode(Rec_func_800B683C_arg0 *object);

#endif
