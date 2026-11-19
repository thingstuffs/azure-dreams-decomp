#include "common.h"
#include "frontend/card/save_slot.h"
#include "frontend/card/save.h"
#include "shared/object_node.h"

extern s32 get_table_entry_by_flag(void *callPtr);
extern void forward_value_initcardmessageobject_arguments(void *callPtr);
extern void forward_target_initcardmessageobject(void *callPtr);
extern void func_80405ED4(void *base);
extern void func_80405AB4(void);
extern void func_80405A64(void);


/* Chooses the next card operation and message callbacks from the selected slot header and table result. */
void select_save_slot_callback(void *inputPtr)
{
    u8 *base;
    s32 index;
    s32 result;

    base = inputPtr;
    index = *(s32 *)(base + 0x28);
    inputPtr = base - 0x20;
    if (card_slot_header_cache[index].fields.marker == 0) {
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
    NODE_HEADER(base)->update_callback = func_80405A64;
}
