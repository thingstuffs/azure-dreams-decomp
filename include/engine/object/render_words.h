#ifndef SLUS_RENDER_WORDS_H
#define SLUS_RENDER_WORDS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "engine/node/allocation.h"

#include "common.h"
#include "records/Rec_func_80034F58_arg0.h"

typedef struct S_80035888_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80035888_0;   /* node in func_80035888 */

typedef struct S_80035888_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    u8 pad_0C[0xC];
    s32 unk_18;
    u8 pad_1C[0x28];
    void * unk_44;
    u8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x28];
    void * unk_74;
    u8 unk_78;
} S_80035888_1;   /* object in func_80035888 */

typedef struct S_80035888_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80035888_2;   /* part8 in func_80035888 */

typedef struct S_80035888_3 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
} S_80035888_3;   /* partC in func_80035888 */


typedef struct S_80035888_5 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_80035888_5;   /* ((S_80035888_0 *)node)->unk_20 in func_80035888 */

typedef struct S_80035888_6 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80035888_6;   /* ((S_80035888_1 *)object)->unk_74 in func_80035888 */


extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void runtime_initialize_state_value(void *, s32);
extern void copy_window_params(void *, void *);
extern void func_800375C0(void *, void *);
extern void prepend_embedded_object_node(void *, void *);

extern void runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback(void);
extern void dispatch_window_fade_and_update_extents(struct Func800359FCState *state, struct Func800359FCEvent *event, void *callback_data);
extern void set_window_handler(void);
extern void func_80035AAC(void);
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
