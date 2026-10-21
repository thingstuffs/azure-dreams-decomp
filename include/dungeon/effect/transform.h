#ifndef DUNGEON_OVL_7E765800_H
#define DUNGEON_OVL_7E765800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_8189E934_Input6 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
} Row_8189E934_Input6;

typedef struct Row_8189E934_Tail {
    s16 pad0;
    s16 tag;
    s32 copy;
    s32 value;
} Row_8189E934_Tail;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Row_8189E934_S_80024134_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} Row_8189E934_S_80024134_0;   /* temp_v0 in func_80024134 */

/* Allocates an object, initializes its display data, and copies the input state. */
typedef struct Row_8189EA64_S_80024264_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    void * unk_08;
} Row_8189EA64_S_80024264_0;   /* arg0 in func_80024264 */

typedef struct Row_8189EA64_S_80024264_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_8189EA64_S_80024264_1;   /* owner in func_80024264 */

/* Advances the timed state sequence and updates the record channels and packed values. */
#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Row_8189EBBC_S_800243BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} Row_8189EBBC_S_800243BC_0;   /* temp_v0 in func_800243BC */

typedef struct Row_8189EBBC_S_800243BC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} Row_8189EBBC_S_800243BC_1;   /* temp_v1 in func_800243BC */

typedef struct Row_8189EBBC_S_800243BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8189EBBC_S_800243BC_3;   /* arg1 in func_800243BC */

typedef struct Row_8189EBBC_S_800243BC_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8189EBBC_S_800243BC_4;   /* temp_v1_3 in func_800243BC */

/* Creates an object with a random sprite variant and copies its transform. */
void register_node(void *, void *);
void func_8004491C(void *, void *);
s32 rand(void);
void advance_sprite_animation_and_textures(void *record);
s32 select_record_entry_and_value();
extern u8 D_80024020[];
extern u8 D_80024C78[];
extern s32 D_80024264;
extern s32 transform_effect_tag;
extern s32 D_800DEF08;
s32 allocate_display_object_and_copy_state(s32 stored_value, void *input, s16 stored_tag);
void create_randomized_grayscale_effect(Row_8189EA64_S_80024264_0 *sequence, s32 unused, Rec_D_80082E80 *record);
s32 create_randomized_transform_effect(s32 owner_id, Row_8189EBBC_S_800243BC_3 *transform);
#endif
