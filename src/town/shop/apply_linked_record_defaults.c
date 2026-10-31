#include "common.h"
#include "m2c_compat.h"
#include "slus.h"
#include "town/shop.h"

typedef struct S_800B2F38_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800B2F38_0;   /* arg0 in apply_linked_record_defaults */

typedef struct S_800B2F38_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 ** unk_14;
} S_800B2F38_1;   /* ((S_800B2F38_0 *)arg0)->unk_A8 in apply_linked_record_defaults */

extern M2C_UNK D_80071244;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 shop_cursor_template;


/* Apply D_800792DC using the linked value and set the linked target to D_80071244. */
void apply_linked_record_defaults(void *record_arg) {
    S_800B2F38_0 *record = record_arg;

    initialize_scaled_entry_cursor(record_arg + 0x1C, &shop_cursor_template, ((S_800B2F38_1 *)(record->unk_A8))->unk_10);
    *((S_800B2F38_1 *)(record->unk_A8))->unk_14 = &D_80071244;
}
