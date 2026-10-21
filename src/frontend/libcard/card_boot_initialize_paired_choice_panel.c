#include "common.h"
#include "records/Rec_func_80026CF0_arg0.h"
void func_80026C00(void *, void *, void *);         /* extern */
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"


/* Store the initial value, link embedded data, and update the record. */
void card_boot_initialize_paired_choice_panel(s8 *record, s32 initial_value) {
    ((Rec_func_80026CF0_arg0 *)record)->unk_00 = initial_value;
    func_80026C00(record + 0x50, record + 0x28, record + 0x38);
    card_boot_initialize_paired_choice_layout(record);
}
