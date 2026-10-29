#ifndef TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
#define TOWN_SHOP_MONSTER_STATUS_DISPLAY_CHAINS_G00632_H
/* Build and join monster status display chains (G00632): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8D04, CL:town/func_800B8D2C. */

#include "common.h"

typedef struct S_800B648C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B648C_0;

/* arg0 in join_monster_status_display_chains */
typedef struct S_800B648C_1 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
} S_800B648C_1;

/* extern */
struct S_800B648C_0;

/* extern */
typedef struct S_800B6508_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0xA];
    s32 unk_14;
    u8 pad_18[0x80];
    s32 unk_98;
} S_800B6508_0;

struct S_800491F4;
extern struct S_800491F4 *build_reverse_indexed_chain(struct S_800491F4 **node_table, u8 *indices, s32 index_limit);
extern u8 monster_status_chain_indices[];
/* extern */
void *link_monster_status_display_entries();
void initialize_display_entry(s32, void *, s32);
/* extern */
void func_800B640C(s32, s32, s32);

/* Functions defined in this translation unit. */
void *link_monster_status_main_entries(s32 nodes);
void join_monster_status_display_chains(S_800B648C_0 *owner, s32 source);
void process_object_data_by_mode(void *object);

#endif
