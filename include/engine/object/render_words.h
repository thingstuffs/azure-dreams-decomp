#include "records/Rec_func_80036210_arg0.h"

#ifndef SLUS_RENDER_WORDS_H
#define SLUS_RENDER_WORDS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "engine/window/attached_message_window.h"
#include "engine/node/allocation.h"
#include "engine/node/registration.h"
#include "engine/window.h"

struct SpriteFrameState;

#include "common.h"
#include "records/Rec_func_80034F58_arg0.h"






typedef struct S_80035888_5 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_80035888_5;   /* ((S_80035888_0 *)node)->unk_20 in func_80035888 */

typedef struct S_80035888_6 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80035888_6;   /* ((S_80035888_1 *)object)->unk_74 in func_80035888 */


extern void prepend_embedded_object_node(void *, void *);

extern s32 draw_linked_sprite_nodes(u8 *first_node, u8 *first_transform, struct SpriteFrameState *first_context);
extern void draw_window_rects(void);
extern void func_80037714(void);

extern u8 window_node_list_storage[12];
extern u8 attached_node_default_parameters[12];
extern s16 attached_node_variant_data[];
extern u8 attached_node_default_render_data[12];
extern s32 attached_node_initial_word_14;
extern s32 attached_node_initial_word_18;

/* Initializes a list node with callbacks, attached objects, and rendering state. */

void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner);

#endif
