#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002644C_0 {
    s32 * unk_00;
    u8 pad_04[0x40];
    void (*unk_44)(void *);
} S_8002644C_0;   /* arg0 in card_boot_enter_overwrite_confirmation; pointer addresses record offset 0x10 */

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Set record pointers around an update of its embedded data. */
void card_boot_enter_overwrite_confirmation(void *record_part) {
    ((S_8002644C_0 *)((u8 *)record_part - 0x10))->unk_44 = &card_boot_handle_overwrite_answer;
    card_boot_show_overwrite_confirmation(record_part - 0x20, record_part + 0x38);
    ((S_8002644C_0 *)((u8 *)record_part - 0x10))->unk_00 = &D_800261F0;
}
