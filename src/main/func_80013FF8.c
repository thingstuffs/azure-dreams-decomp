#include "common.h"

typedef struct Object13B18 Object13B18;
extern void card_boot_set_paired_choice_animations(Object13B18 *, s32 *, s32 *);

/* Pass the data at offset 0x20 to card_boot_set_paired_choice_animations. */
void card_boot_update_paired_choice_animations(s32 base_addr, s32 *enable_flags, s32 *active_flags) {
    card_boot_set_paired_choice_animations((Object13B18 *)(base_addr + 0x20), enable_flags, active_flags);
}
