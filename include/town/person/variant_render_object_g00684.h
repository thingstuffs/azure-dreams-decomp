#ifndef TOWN_PERSON_VARIANT_RENDER_OBJECT_G00684_H
#define TOWN_PERSON_VARIANT_RENDER_OBJECT_G00684_H
/* G00684: shared declarations for variant render object. */
/* Original-file evidence (G00684): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CE070, CL:town/func_800CE380, CL:town/func_800CE408, PD:town/engine:800D68B0. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_payload.h"
#include "shared/vector.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"

typedef struct S_800CB9B8_2 S_800CB9B8_2;

typedef struct S_800CB8CC_1 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x38];
    s32 unk_9C;
} S_800CB8CC_1;

/* extern */


/* extern */
typedef struct S_800CB9B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB9B8_1;

/* arg1 in update_entity_relative_position */
typedef struct S_800CB9B8_5 {
    u8 pad_00[0x72];
    s16 unk_72;
} S_800CB9B8_5;

/* ((Rec_D_80082D58 *)arg0)->unk_9C in update_entity_relative_position */
typedef struct S_800CB9B8_6 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800CB9B8_6;

typedef struct S_800CBAAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, s32, s32);
} S_800CBAAC_0;

typedef struct S_800CBAE0_0 {
    s32 * unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
    u8 pad_74[0x32];
    u8 unk_A6;
} S_800CBAE0_0;

/* arg0 in initialize_record_from_table_index; pointer addresses record offset 0x10 */
struct Rec_D_800CFCB4;

/* extern */
struct Rec_D_80082E80;

typedef struct S_800CBB68_2 {
    u8 pad_00[0x96];
    s8 unk_96;
} S_800CBB68_2;

struct IntVector3;

/* extern (function symbol used as callback) */
void *allocate_list_node();
/* extern */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
void unlink_node_if_registered(void *block_data);
/* extern */
/* extern */
void clear_object_slot_and_mark_removed(void *);
s32 is_default_object_data(Rec_func_80094268_arg0 *);
void configure_the_set_mode_n_3(struct Rec_D_800CFCB4 *, s32, s32);
void initialize_optional_object_state(void *, s32, struct Rec_D_80082E80 *, s32);
/* extern */
extern void D_800CBAAC();
extern M2C_UNK D_800D6A58;
void * create_town_effect_object(s32, struct IntVector3 *, s32, s32);
extern s16 query_lowered_transform_position(void *position);

extern s32 D_800D68B0[];

/* Functions defined in this translation unit. */
void * create_and_invoke_render_object(s32 initial_value, s32 resource_index);
void update_entity_relative_position(Rec_D_80082D58 *entity, IntVector3 *out_pos);
void invoke_object_handler(S_800CBAAC_0 *object, s32 callback_arg1, s32 callback_arg2);
void initialize_record_from_table_index(void *record_data, s32 context, Rec_D_80082E80 *state);
void allocate_variant_object(s32 variant, s32 x, s32 y);

#endif
