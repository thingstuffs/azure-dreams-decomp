#include "common.h"
#include "shared/object_flags.h"
#include "shared/types3a_types.h"


extern void reset_item_menu_object_state(s32 object);
extern void schedule_item_menu_child_release(s32 object);
extern void set_object_data_pointer_2(s32 object);
extern void func_8004E130(void);
extern void handle_selection_and_create_object(void);

// Set the high-bit flags and pass the three parameters to their handlers.
void start_item_menu_object_processing(ItemMenuParameters *parameters) {
    s32 firstParameter = parameters->field0;
    ((u16 *)parameters)[-1] |= 0x8000;
    object_flag_block.flags |= 0x8000;
    reset_item_menu_object_state(firstParameter);
    schedule_item_menu_child_release(parameters->field4);
    set_object_data_pointer_2(parameters->field8);
    func_8004E130();
    handle_selection_and_create_object();
}
