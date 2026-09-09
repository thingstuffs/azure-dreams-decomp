#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK func_800C337C();
extern u8 D_80082660[9];
extern M2C_UNK D_800CFCB4[5];
extern volatile M2C_UNK D_800D5084[20];



typedef struct S_800C3988_1_pre {
    M2C_UNK (*unk_00)(void *, M2C_UNK, M2C_UNK);
    u8 pad_04[0x54];
} S_800C3988_1_pre;   /* the 0x58 bytes before (((s8) temp_v1 * 4) + ((Rec_func_80094268_arg0 *)arg0)->unk_5C) in func_800C3988, addressed as (((s8) temp_v1 * 4) + ((Rec_func_80094268_arg0 *)arg0)->unk_5C)[-1] */

/* Dispatches the record handler or clears its pending state. */
void func_800C3988(Rec_func_80094268_arg0 *record, M2C_UNK dispatch_arg, M2C_UNK dispatch_data, M2C_UNK check_arg) {
    s32 slot_offset;
    s32 handler_addr;
    u8 handler_id;
    u8 *handler_slot;
    register M2C_UNK (*handler)(void *, M2C_UNK, M2C_UNK) ASM_REG("$2"); /* MATCH: merge the dispatch target in v0. */
    Rec_func_80094268_arg0 *dispatch_record;
    M2C_UNK saved_arg;

    if (func_800352FC(record, dispatch_arg, dispatch_data, check_arg) == 0) {
        s32 *state;

        func_800C337C(record, dispatch_arg, dispatch_data);
        state = D_800CFCB4;
        if (record == state[4]) {
            state[4] = 0;
            return;
        }
    } else {
        slot_offset = record->unk_60 * 8;
        handler_slot = &D_80082660[slot_offset];
        handler_id = *handler_slot;
        if ((u32) (handler_id - 2) < 0x14U) {
            dispatch_record = record;
            handler_addr = D_800D5084[(s8) handler_id];
            handler = (M2C_UNK (*)(void *, M2C_UNK, M2C_UNK)) handler_addr;
            saved_arg = dispatch_arg;
            goto dispatch;
        }
        if ((s8) handler_id >= 0x16) {
            register s32 handler_base ASM_REG("$2"); /* MATCH: load the record handler_base into v0 before indexing. */
            saved_arg = dispatch_arg;
            dispatch_record = record;
            handler_base = dispatch_record->unk_5C;
            handler = ((S_800C3988_1_pre *)((((s8) handler_id * 4) + handler_base)))[-1].unk_00;
        dispatch:
            handler(dispatch_record, saved_arg, dispatch_data);
            return;
        }
        if ((s8) handler_id < 0) {
            *handler_slot = 0U;
            func_800C337C(record, dispatch_arg, dispatch_data);
        }
    }
}
