#ifndef DUNGEON_MENU_OBJECT_TABLE_INITIALIZATION_G00375_H
#define DUNGEON_MENU_OBJECT_TABLE_INITIALIZATION_G00375_H
/* Object table initialization shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D7228, CL:dungeon/func_800D7484, CL:dungeon/func_800D74DC, CL:dungeon/func_800D7594. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct S_800DCCF4_0 {
    s32 unk_00;
    s32 * unk_04;
    s32 * unk_08;
    s32 * unk_0C;
} S_800DCCF4_0;

typedef struct {
    u8 pad_00[0x38];
    s32 *field_38;
    u8 field_3C[1];
} ObjectHeader;

extern Template0 display_block_defaults;
extern Vec3 display_vector_defaults;
/* extern */
extern M2C_UNK D_800E2804;
extern M2C_UNK D_800E2828;
extern M2C_UNK D_800E28B8;
extern s32 create_callback_pair_default(s32);
extern void register_node(void *, void *);
extern void initialize_complemented_state(void *);
extern s32 run_object_setup_and_finalize(void *, s32);
extern u8 dungeon_menu_tag[];
extern u8 D_800DC8F8[];
extern void *dungeon_menu_object[];

/* Functions defined in this translation unit. */
void initialize_nine_records_and_vectors(u8 *object);
s32 initialize_object_tables_2(S_800DCCF4_0 *object, s32 mode);
void *allocate_object_with_failure_flag(void);

#endif
