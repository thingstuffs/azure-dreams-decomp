#include "common.h"
#include "frontend/card/save.h"

typedef struct S_func_8001F150_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0x34];
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x4];
    void (*unk_54)(void);
} S_func_8001F150_0;

typedef struct S_func_8001F150_1 {
    s32 unk_00;
    u8 pad_04[0x7C];
} S_func_8001F150_1;

extern void initialize_card_message_object_with_code_7(void *object);
extern void func_80405A64(void);
extern void process_menu_input_and_cursor_state(void);
extern s32 card_slot_header_cache[];

/* Selects the object's next callback based on whether its indexed entry is active. */
void select_object_callback_by_entry(void *object_state)
{
    void (*next_callback)(void);
    S_func_8001F150_0 *object_base;
    s32 entry_index;
    s32 entry_active;

    entry_index = ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_48;
    entry_active = ((S_func_8001F150_1 *)card_slot_header_cache)[entry_index].unk_00;
    object_base = (S_func_8001F150_0 *)((u8 *)object_state - 0x20);
    if (entry_active != 0) {
        next_callback = process_menu_input_and_cursor_state;
        ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_4C = entry_index;
    } else {
        ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_54 = handle_object_menu_input;
        initialize_card_message_object_with_code_7(object_base);
        next_callback = func_80405A64;
    }
    ((S_func_8001F150_0 *)((u8 *)object_state - 0x20))->unk_10 = next_callback;
}
