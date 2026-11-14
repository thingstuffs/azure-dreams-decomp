#ifndef TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
#define TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
/* Build and join monster status display chains: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8D04, CL:town/func_800B8D2C. */

#include "common.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "shared/item_menu.h"


/* arg0 in join_monster_status_display_chains */

/* extern */

/* extern */

struct S_800491F4;
extern u8 monster_status_chain_indices[];
/* extern */
void initialize_display_entry(s32, void *, s32);
/* extern */
void func_800B640C(s32, s32, s32);

/* Functions defined in this translation unit. */
void *link_monster_status_main_entries(s32 nodes);
void join_monster_status_display_chains(ItemMenuPart *owner, s32 source);
void build_monster_status_display(Rec_func_800B683C_arg0 *object);

#endif
