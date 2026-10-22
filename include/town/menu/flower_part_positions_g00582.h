#ifndef TOWN_MENU_FLOWER_PART_POSITIONS_G00582_H
#define TOWN_MENU_FLOWER_PART_POSITIONS_G00582_H
/* inferred-strong G00582: flower_part_positions_g00582; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AA910. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_views.h"
#include "shared/object_index_slots.h"
#include "shared/object_flags.h"

/* extern */
struct IntVector3;

/* extern */

typedef struct S_800A7FD8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800A7FD8_1;

typedef struct {
    u8 pad_00[0x72];
    s16 angle;
} Inner;

typedef struct {
    u8 pad_00[8];
    u16 *coords;
    u8 pad_0C[0x14];
    Inner inner;
} Object;

typedef struct {
    s32 unk_0;
    Object *object;
} ObjectSlot;

void register_node_if_unregistered(void *block_data, s32 registration_id);
/* extern */
s32 lookup_item_category_mapped_value(s32, s32);
void * create_town_effect_object(s32, struct IntVector3 *, s32, s32);
extern s32 service_script_controller(void);
extern void unlink_node_if_registered(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

/* Functions defined in this translation unit. */
void present_flower_set(s32 initial_value);
void update_linked_part_position(u16 *part, u16 *out_coords, void *unused);

#endif
