#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026494_0 {
    s32 * unk_00;
    u8 pad_04[0x40];
    s32 * unk_44;
} S_80026494_0;   /* arg0 in card_boot_enter_insufficient_space_advice; pointer addresses record offset 0x10 */


void card_boot_show_insufficient_space_overwrite_advice();                         /* extern */
extern M2C_UNK D_800261F0;
extern M2C_UNK D_800265B8;

/* Set record pointers around an update of its base record. */
void card_boot_enter_insufficient_space_advice(void *record_part) {
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_44 = &D_800265B8;
    card_boot_show_insufficient_space_overwrite_advice(record_part - 0x20);
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_00 = &D_800261F0;
}
