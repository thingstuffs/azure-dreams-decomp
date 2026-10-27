#include "common.h"

typedef struct S_80700A20_0 {
    u8 pad_00[0x8];
    s32 *unk_08;
} S_80700A20_0;

typedef struct S_80700A20_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_80700A20_1;

extern s32 func_8070021C();
extern void forward_indexed_table_value(s32 index);
extern void func_807002D4(s32 index);
extern s32 dispatch_first_failed_entry_b(void);

/* When gate 2 and the counter both pass, refresh the status byte and return the stage handler's result. */
s32 refresh_status_when_gate_2_and_counter_pass(s32 entry)
{
    S_80700A20_1 *status;

    if ((func_8070021C(2) != 0) &&
        (*((S_80700A20_0 *)(*(void **)0xA0700F5C))->unk_08 > 0)) {
        forward_indexed_table_value(2);
        status = *(void **)0xA0700F40;
        status->unk_0E = status->unk_0E;
        return dispatch_first_failed_entry_b();
    }
    func_807002D4(2);
    return entry;
}
