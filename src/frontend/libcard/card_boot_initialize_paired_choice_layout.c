#include "common.h"
#include "m2c_compat.h"

void card_boot_refresh_paired_choice_labels(u8 *);                         /* extern */
struct Object13B18; void card_boot_set_paired_choice_animations(struct Object13B18 *, s32 *, s32 *);   /* extern */
void card_boot_layout_left_right_labels(s32);                            /* extern */
void set_entry_destination_and_value(void *);                         /* extern */
extern M2C_UNK D_8002807C;
extern M2C_UNK D_80028084;

/* Update the record using the two shared data addresses. */
void card_boot_initialize_paired_choice_layout(s32 record_addr) {
    card_boot_layout_left_right_labels(record_addr);
    set_entry_destination_and_value((void *)(record_addr));
    card_boot_set_paired_choice_animations((struct Object13B18 *)(record_addr), &D_8002807C, &D_80028084);
    card_boot_refresh_paired_choice_labels((u8 *)(record_addr));
}
