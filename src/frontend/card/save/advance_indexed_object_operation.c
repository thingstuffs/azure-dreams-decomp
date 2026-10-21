#include "common.h"

extern s32 get_table_entry_by_flag(void *callPtr);
extern void forward_value_initcardmessageobject_arguments(void *callPtr);
extern void forward_target_initcardmessageobject(void *callPtr);
extern void func_80405ED4(void *base);
extern void handle_object_menu_input(void);
extern void func_80405AB4(void);
extern void func_80405A64(void);

extern u8 card_slot_header_cache[];

void advance_indexed_object_operation(void *inputPtr)
{
    u8 *base;
    s32 index;
    s32 result;

    base = inputPtr;
    index = *(s32 *)(base + 0x28);
    inputPtr = base - 0x20;
    if (*(s32 *)(card_slot_header_cache + (index << 7)) == 0) {
        result = get_table_entry_by_flag(inputPtr);
        inputPtr = 0;
        inputPtr = base - 0x20;
        if (result < 3) {
            *(void (**)(void))(base + 0x34) = handle_object_menu_input;
            forward_value_initcardmessageobject_arguments(inputPtr);
        } else {
            func_80405ED4(base);
            return;
        }
    } else {
        *(void (**)(void))(base + 0x34) = func_80405AB4;
        forward_target_initcardmessageobject(inputPtr);
    }
    *(void (**)(void))(base - 0x10) = func_80405A64;
}
