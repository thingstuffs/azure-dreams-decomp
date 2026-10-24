#ifndef TOWN_SCENE_FLAGS_CALL_RESET_DISPATCH_STATE_FLAGS_G01229_H
#define TOWN_SCENE_FLAGS_CALL_RESET_DISPATCH_STATE_FLAGS_G01229_H
/* Call reset dispatch state flags. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01229 - CL:town/func_804686A4. */

#include "common.h"
#include "shared/town_event_state.h"
#include "script_symbols.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef s32 Callback(s32);

typedef s32 (*TownPairCallback)(s32, s32);

typedef void *(*EventOpcodeHandler)(void);

typedef struct S_80019560_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
} S_80019560_0;

extern s32 func_8001E82C(void);
extern u8 D_80018A30[];
extern void *D_80018448[];
extern void *D_800186A8[];
/* extern */
void process_history_entries_by_mode(void);
/* extern */
void func_8001E578(s32);
/* extern */
extern s16 D_800178BA[0x10];
extern EventOpcodeHandler D_800178E8[4];
extern void *D_8001E95C[0x10];

/* Shared import declarations; data casts preserve each measured view. */
extern u32 func_8001E670(s32 condition_id);
extern void func_8001E5F0(s32 event_flag_id);

/* Functions defined in this translation unit. */
void *call_reset_dispatch_state_flags(void);
void *tick_shop_event_state(void);
void *query_event_state_or_reset(void);
void *get_callback_selected_table_value(void);
void run_event_opcode_script(s32 setup_arg0, s32 setup_arg1, s32 setup_arg2, s32 setup_arg3);
void reset_dispatch_state_and_flags(void);

#endif
