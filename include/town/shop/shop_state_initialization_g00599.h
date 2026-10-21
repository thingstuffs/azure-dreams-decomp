#ifndef TOWN_SHOP_SHOP_STATE_INITIALIZATION_G00599_H
#define TOWN_SHOP_SHOP_STATE_INITIALIZATION_G00599_H
/* Shop state initialization declarations (G00599). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0888, CL:town/func_800B0994, CL:town/func_800B09E8, CL:town/func_800B0B44. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct {
    s32 words[17];
} Record68;

typedef struct {
    s32 words[17];
} CopyBlock;

typedef struct {
    u8 pad0[0x30];
    s32 value;
    CopyBlock block;
} Source;

typedef struct {
    u8 pad0[0x38];
    s32 value38;
    u8 pad3C[0x60];
    s32 value9C;
    u8 padA0[8];
    s32 valueA8;
    u8 padAC[0xE];
    u8 valueBA;
    u8 padBB[0xD];
    CopyBlock block;
} TownState;

/* extern */
struct FuncArg;

typedef struct S_800AE1AC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    s32 unk_2C;
} S_800AE1AC_0;

typedef struct S_800AE1AC_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800AE1AC_1;

typedef struct FuncArg {
    u8 pad0[4];
    s32 field4;
    u8 pad8[0x20];
    s32 field28;
    s32 field2C;
} FuncArg;

void refresh_paged_selection_state();
/* extern */
s32 allocate_paged_shop_item_list();
/* extern */
s32 create_dual_buffer_object();
/* extern */
void advance_dispatch_when_countdown_expires(void *state_data);
extern void set_shop_object_data_if_present(s32 object);
extern void set_object_data_pointer_2(s32 object);
extern s32 D_80082AB4[];

extern TownState runtime_script_state;

/* Functions defined in this translation unit. */
void copy_global_state_and_record_block(s32 *record);
void initialize_state_from_source(Source *source);
void *open_shop(s32 unused, s32 primary_param, s32 secondary_param, s32 shared_param);
void process_record_and_apply_flags(FuncArg *record);

#endif
