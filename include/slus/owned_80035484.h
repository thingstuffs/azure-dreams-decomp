#ifndef SLUS_OWNED_80035484_H
#define SLUS_OWNED_80035484_H
struct S_800355EC_0;

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "engine/node/allocation.h"

struct SpriteFrameState;


#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(void *);

typedef struct S_func_80035484_1 {
    struct S_func_80035484_4 *model;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x5C];
    Callback unk_68;
    u8 pad_6C[8];
    void *unk_74;
} S_func_80035484_1;

typedef struct S_func_80035484_4 {
    u8 pad_00[8];
    u16 unk_08;
    u8 pad_0A[6];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x48];
    s32 unk_60;
} S_func_80035484_4;

typedef struct S_func_80035484_5 {
    u8 pad_00[2];
    u8 unk_02;
} S_func_80035484_5;


extern void runtime_initialize_state_value(void *modelPtr, s32 value);
extern void prepend_embedded_object_node(void *configPtr, void *statePtr);
extern s32 register_node(void *objectPtr, void (*callback)(void));

extern s32 draw_linked_sprite_nodes(u8 *first_node, u8 *first_transform, struct SpriteFrameState *first_context);
void invoke_window_object_callback(struct S_800355EC_0 *object, void *context, void *output);
extern void init_window_object(void *callbackData);
extern void func_80035614(void *callbackData);

extern s16 window_variant_model_values[];
extern void *window_variant_render_data[];
extern u8 window_default_render_data[];
extern void *current_window_object;
extern void *window_node_list_storage[3];

/* Creates a runtime object and initializes its model, transform, and appearance. */

void create_window_object(void *object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config);
void func_80035484(void *object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config);

#endif
