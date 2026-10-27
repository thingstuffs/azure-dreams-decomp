#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item_menu_actions.h"

typedef struct S_800AE494_0 {
    s32 unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_800AE494_0;   /* arg0 in run_item_menu_record_handlers; pointer addresses record offset 0x10 */


struct S_800B0418_0; void set_item_menu_record_active(struct S_800B0418_0 *);                         /* extern */
struct S_800B0700_0; void schedule_item_menu_child_release(struct S_800B0700_0 *);                         /* extern */

/* Pass the record handles to their handlers and clear its secondary handle and status. */
void run_item_menu_record_handlers(void *record_payload) {
    schedule_item_menu_child_release((struct S_800B0700_0 *)(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14));
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14 = 0;
    set_item_menu_record_active((struct S_800B0418_0 *)(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_10));
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_00 = 0;
}
