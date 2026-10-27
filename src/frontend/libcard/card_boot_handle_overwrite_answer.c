#include "common.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Placed copy of card_boot_enter_copying_progress. */
extern void func_800263C0(void *object_data);


/* Selects write_text_and_advance_selection when the state field is nonzero or enters copying progress. */
void card_boot_handle_overwrite_answer(void *object_data) {
    if (*(s32 *)((u8 *)object_data + 0x38) != 0) {
        *(s32 **)((u8 *)object_data - 0x10) = write_text_and_advance_selection;
        return;
    }
    func_800263C0(object_data);
}
