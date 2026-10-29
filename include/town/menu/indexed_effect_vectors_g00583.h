#ifndef TOWN_MENU_INDEXED_EFFECT_VECTORS_G00583_H
#define TOWN_MENU_INDEXED_EFFECT_VECTORS_G00583_H
/* inferred-strong G00583: indexed_effect_vectors_g00583; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AAAE8. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"

typedef struct S_800A8184_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
} S_800A8184_1;

void register_node_if_unregistered(void *block_data, void *registration_id);
s32 lookup_item_category_mapped_value(s32 category_index, s32 record_index);
/* extern */
/* extern */
extern s32 item_effect_descriptor;
extern void D_800A8248(void *object, s32 *out_vector, void *unused);
extern s32 scene_object_payload_alias[2];
extern s32 town_position_callback_address;
extern s32 D_80097EA0;
extern s32 town_target_height_offset;
extern void unlink_node_if_registered(void *object);

/* Functions defined in this translation unit. */
void create_indexed_effect_object(s32 index, s32 kind);
void copy_adjusted_vector_or_flag_object(void *object, s32 *out_vector, void *unused);

#endif
