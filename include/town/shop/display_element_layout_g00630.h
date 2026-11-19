#ifndef TOWN_SHOP_DISPLAY_ELEMENT_LAYOUT_G00630_H
#define TOWN_SHOP_DISPLAY_ELEMENT_LAYOUT_G00630_H
/* Lay out three display elements and complementary values: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B79CC. */

#include "common.h"
#include "shared/item_menu.h"
#include "shared/sprite_part_command.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* extern */
extern s32 D_80077FBC[];
extern u8 D_800D1794;

/* Functions defined in this translation unit. */
void *set_complementary_entry_bytes(void *entry, s16 amount);
void *layout_three_display_elements(ActorRecord *actor, ItemMenuPart **elements, SpritePartCommand *content);

#endif
