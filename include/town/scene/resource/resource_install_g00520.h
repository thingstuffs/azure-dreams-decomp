#ifndef TOWN_SCENE_RESOURCE_RESOURCE_INSTALL_G00520_H
#define TOWN_SCENE_RESOURCE_RESOURCE_INSTALL_G00520_H
/* Resource install shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8008D588, CL:town/func_8008D5BC, CL:town/func_8008D630, CL:town/func_8008D6EC, CL:town/func_8008D7CC, CL:town/func_8008D850, CL:town/func_8008D988, PD:town/engine:800CF720. */

#include "common.h"

typedef struct TownAllocEntry {
    s8 kind;
    s8 state;
    s16 value;
    s32 size;
} TownAllocEntry;

typedef struct {
    u8 pad0[8];
    u32 flags0;
    u32 flags1;
} Item;

typedef struct {
    u8 pad0[0x48];
    s32 value48;
    u8 pad4C[0x14];
    s32 value60;
    u8 pad64[0x34];
    Item *item98;
} Object;

typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} TownState;

typedef struct S_8008B23C_0 {
    u32 unk_00;
    s32 unk_04;
} S_8008B23C_0;

extern u32 *D_801131EC[3];
extern s32 resource_cache_records[];
extern s32 town_resource_buffer;
extern void start_cd_read(u32 *, s32);
extern void func_8008AC84(s32);
extern s32 sum_resource_bytes(s32);
extern void shift_resource_entries_and_data(s32, s32);
s32 find_resource_index_by_key(s32 targetField0, s32 targetField1, s32 targetField2);
/* extern */
void move_resource_to_front(s32);
extern TownState town_resource_context;
extern void call_script(s32);

/* Functions defined in this translation unit. */
u32 *find_packed_resource_descriptor(s32 flag_bit, s32 high_key, s32 low_key);
s32 install_resource_descriptor_at_front(s32 kind, s32 state, s32 value, s32 start_index);
void ensure_resource_at_front(s32 kind, s32 state, s32 value);
void submit_object_resource_data(Object *object);
void ensure_packed_resource_list(u8 *entries_in);

#endif
