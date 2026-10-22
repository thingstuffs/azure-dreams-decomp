#ifndef TOWN_SHOP_DISPATCH_INDEXED_HANDLER_G01154_H
#define TOWN_SHOP_DISPATCH_INDEXED_HANDLER_G01154_H
/* dispatch indexed handler g01154. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01154 - CL:town/func_800B47B0, CL:town/func_800B47E8. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B1DCC_arg0.h"

typedef void (*DispatchFunc)(void *context, void *self);

typedef struct S_800B1F80_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B1F80_1;

typedef struct S_800B2068_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B2068_1;

extern DispatchFunc D_800D1638[];
extern DispatchFunc D_800D1640[];
s32 advance_index_with_directional_clamp(s32 index, s32 step, s32 count);

/* Functions defined in this translation unit. */
void dispatch_indexed_handler(void *context, s32 handler_index);
void dispatch_indexed_handler_alt(void *context, s32 handler_index);
void update_active_entry_and_notify_handlers(s8 *state, s32 input);
void decrement_entry_and_notify_handlers(void *state);

#endif
