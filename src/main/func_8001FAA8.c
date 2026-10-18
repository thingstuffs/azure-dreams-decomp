#include "common.h"

typedef struct S_func_80406AA8_0 {
    u8 pad_00[4];
    s32 unk_04;
    u8 pad_08[4];
    s32 unk_0C[6];
    s32 unk_24;
    u8 pad_28[4];
    s32 unk_2C;
    u8 pad_30[4];
    void (*unk_34)(void);
    u8 pad_38[8];
    s32 unk_40;
} S_func_80406AA8_0;

typedef struct S_func_80406AA8_1 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
} S_func_80406AA8_1;

extern void initialize_destination_template_state(short *dest, int index, int mode);
extern s32 process_entry_with_table_value(s32 entry_id, s32 request_id);
extern void forward_value_initcardmessageobject(void *value);
extern void func_80405A00(s32 object, s32 value);
extern void func_80404688(s32 object);
extern void func_80400908(void);
extern void func_804069FC(void);
extern void set_global(void);
extern void handle_menu_selection_input(void);
extern s32 D_80010208;

/* Updates the state and selects its next callback based on the current entry check. */
void update_menu_object_state(S_func_80406AA8_0 *state)
{
    S_func_80406AA8_1 *state_base;
    s32 check_result;

    initialize_destination_template_state(0x80010000, state->unk_2C,
                  state->unk_24);
    check_result = process_entry_with_table_value(state->unk_2C, 0x80010000);
    state_base = (S_func_80406AA8_1 *)((u8 *)state - 0x20);
    if (check_result == 0) {
        state->unk_34 = handle_menu_selection_input;
        forward_value_initcardmessageobject(state_base);
        ((S_func_80406AA8_1 *)((u8 *)state - 0x20))->unk_10 = func_804069FC;
    } else {
        func_80405A00(state->unk_04, state->unk_2C);
        func_80404688(*(s32 *)((u8 *)state + (0xC + state->unk_2C * 4)));
        if (D_80010208 != 0) {
            ((S_func_80406AA8_1 *)((u8 *)state - 0x20))->unk_10 = set_global;
        } else {
            ((S_func_80406AA8_1 *)((u8 *)state - 0x20))->unk_10 = handle_menu_selection_input;
        }
    }
    func_80400908();
    state->unk_40 = 0;
}
