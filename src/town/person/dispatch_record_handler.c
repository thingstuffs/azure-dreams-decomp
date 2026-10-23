#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


extern s32 service_script_controller(void);
extern void dispatch_object_state();
extern u8 object_index_slots[9];
extern M2C_UNK town_actor_control[5];
extern volatile M2C_UNK D_800D5084[20];


typedef struct S_800C3988_1_pre {
    M2C_UNK (*unk_00)(void *, M2C_UNK, M2C_UNK);
    u8 pad_04[0x54];
} S_800C3988_1_pre;

/* Dispatches the record handler or clears its pending state. */
void dispatch_record_handler(Rec_func_80094268_arg0 *record, M2C_UNK dispatch_arg, M2C_UNK dispatch_data, M2C_UNK check_arg) {
    s32 slot_offset;
    s32 handler_addr;
    s32 handler_id;
    u8 *handler_slot;
    M2C_UNK (*handler)(void *, M2C_UNK, M2C_UNK);
    Rec_func_80094268_arg0 *dispatch_record;
    M2C_UNK saved_arg;

    if (service_script_controller() == 0) {
        s32 *state;

        dispatch_object_state(record, dispatch_arg, dispatch_data);
        state = town_actor_control;
        if (record == state[4]) {
            state[4] = 0;
            return;
        }
    } else {
        slot_offset = record->unk_60 * 8;
        handler_slot = &object_index_slots[slot_offset];
        handler_id = *handler_slot;
        if ((u32) (handler_id - 2) < 0x14U) {
            handler_addr = D_800D5084[(s8) handler_id];
            dispatch_record = record;
            handler = (M2C_UNK (*)(void *, M2C_UNK, M2C_UNK)) handler_addr;
            saved_arg = dispatch_arg;
            goto dispatch;
        }
        if ((s8) handler_id >= 0x16) {
            s32 handler_base;
            saved_arg = dispatch_arg;
            dispatch_record = record;
            handler_id = (s8)handler_id * 4;
            handler_base = dispatch_record->unk_5C;
            handler_id = handler_base + handler_id;
            handler = ((S_800C3988_1_pre *)handler_id)[-1].unk_00;
dispatch:
            handler(dispatch_record, saved_arg, dispatch_data);
            return;
        }
        if ((s8) handler_id < 0) {
            *handler_slot = 0U;
            dispatch_object_state(record, dispatch_arg, dispatch_data);
        }
    }
}
