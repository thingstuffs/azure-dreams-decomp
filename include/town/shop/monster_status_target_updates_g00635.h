#ifndef TOWN_SHOP_MONSTER_STATUS_TARGET_UPDATES_G00635_H
#define TOWN_SHOP_MONSTER_STATUS_TARGET_UPDATES_G00635_H
/* Release handled entries and change the monster status target (G00635): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B93B0, CL:town/func_800B97F4. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_2;

typedef struct S_800B6B10_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_3;

typedef struct S_800B6B10_4 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_800B6B10_4;

typedef struct S_800B6B10_5 {
    u8 pad_00[0xE];
    s8 unk_0E;
} S_800B6B10_5;

typedef struct S_800B6B10_0 {
    s32 unk_00;
} S_800B6B10_0;

typedef struct S_800B6B10_1 {
    s32 unk_00;
} S_800B6B10_1;

typedef struct S_800B9464_sub {
    u8 pad00[0x98];
    s32 unk98;
} S_800B9464_sub;

typedef struct S_800B9464_a0 {
    u8 pad00[0x1E];
    u16 field_1E;          /* 0x1E */
    S_800B9464_sub sub;    /* 0x20 */
    u16 *arr_bc[1];        /* 0xBC, NULL-terminated pointer array */
} S_800B9464_a0;

/* extern */
typedef struct S_800B6C30_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0x8E];
    s32 unk_98;
} S_800B6C30_0;

#include "engine/resource.h"
#include "slus.h"
/* Canonical global flags word shared by several sibling functions across
 * the codebase (code9.c, code10.c, code11.c, code5.c, w_8004FE78.c, ...).
 * Declared as a plain `extern int` so the address is recomputed separately
 * for the load and the store, matching this function's tail. */
extern int D_800814A0;
extern void release_null_terminated_entries(u16 **a0);
void process_object_data_by_mode(void *);
/* extern */
s32 invalidate_cached_state_and_queue_read(void *);

/* Functions defined in this translation unit. */
void process_handled_entry_types(void **entries);
void process_object_pointer_array(S_800B9464_a0 *object);
void change_monster_status_display_target(s32 objectAddress, s32 field04Value, s16 field08Value);

#endif
