#ifndef TOWN_SCENE_HISTORY_H
#define TOWN_SCENE_HISTORY_H
/* Town group history */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01209 - CL:town/func_8046C280, CL:town/func_8046C414, CL:town/func_80477674, CL:town/func_8047BE74, PD:town/image_3ef000:8001B0D0, PD:town/ll34_400000_80016000:80018E44. */

#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"

typedef struct S_8001D188_3 {
    u8 pad_00[0x6000];
    Rec_D_80016000 *unk_6000;
} S_8001D188_3;

/* page in prepend_entry_to_group_history */
typedef struct S_8001D188_0 {
    u8 pad_00[0x6000];
    Rec_D_80016000 *unk_6000;
} S_8001D188_0;

/* page in prepend_entry_to_group_history */
typedef struct S_8001D188_1 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x44];
    void * unk_6C;
    u8 pad_70[0x17C];
    s16 * unk_1EC;
} S_8001D188_1;

typedef struct {
    s16 vx;
    s16 vy;
    s32 unused;
} Entry;

typedef struct {
    s16 flag;
    s16 unused;
    Entry *entries;
} Lookup;

/* cursor in prepend_entry_to_group_history */
extern s32 query_priority_event_state(void);
extern s8 D_8001916C[];
extern s8 D_80019178[];
extern s8 D_8001917C[];
extern s8 D_80019184[];
extern s8 D_80019190[];

/* Functions defined in this translation unit. */
void prepend_entry_to_group_history(s32 entry_index, s32 lookup_arg1, s32 lookup_arg2, s32 lookup_arg3);
void *get_indexed_vertex_and_trace(s32 group, s32 n, s32 lookup_variant);

#endif
