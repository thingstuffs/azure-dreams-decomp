#include "common.h"

typedef struct S_func_804061C4_0 {
    u8 pad_00[4];
    s32 unk_04;
    u8 pad_08[0x20];
    s32 unk_28;
    u8 pad_2C[8];
    void (*unk_34)(void);
    s32 unk_38;
} S_func_804061C4_0;

typedef struct S_func_804061C4_1 {
    void (*unk_00)(void);
} S_func_804061C4_1;

extern s32 card_dev_run_slot_operation(s32 slot_index);
extern void initialize_card_message_object_with_code_0x13(void *object);
extern void func_80404688(s32 entry_object);
extern void handle_object_menu_input(void);
extern void func_80405A64(void);

/* Updates state callbacks and processes five entries if the state check succeeds. */
void process_five_object_entries(S_func_804061C4_0 *state)
{
    s32 entry;
    s32 entry_count;

    if (state->unk_38 != 0) {
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = handle_object_menu_input;
        return;
    }

    if (card_dev_run_slot_operation(state->unk_28) != 0) {
        entry_count = 0;
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = handle_object_menu_input;
        do {
            entry = state->unk_04;
            state = (S_func_804061C4_0 *)((u8 *)state + 4);
            entry_count++;
            func_80404688(entry);
        } while (entry_count < 5);
    } else {
        state->unk_34 = handle_object_menu_input;
        initialize_card_message_object_with_code_0x13((u8 *)state - 0x20);
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = func_80405A64;
    }

    return;
}
