#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


extern s32 check_progress_against_callback(void);
extern u32 D_8001C368[];

/* Decrements the object's counter and invokes a callback if the object check succeeds. */
void tick_object_counter_and_invoke_callback(void) {
    TownStateRecord *counter_obj;

    counter_obj = D_80016000->unk_38;
    counter_obj->unk_2D5C = (u32) (((signed int)counter_obj->unk_2D5C) - D_8001C368[0]);
    if (check_progress_against_callback() != 0) {
        ((s32 (*) (s32, s32))D_80016000->unk_20->callback_04C)(0x10,
            5);
    }
}
