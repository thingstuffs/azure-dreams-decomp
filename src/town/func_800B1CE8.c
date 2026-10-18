#include "common.h"
#include "m2c_compat.h"
#include "shared/types3a_types.h"

typedef struct S_800AF448_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    void * unk_A8;
} S_800AF448_0;   /* arg0 in update_item_menu_enabled_record */

   /* ((S_800AF448_0 *)arg0)->unk_00 in update_item_menu_enabled_record */

typedef struct S_800AF448_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 ** unk_14;
} S_800AF448_2;   /* ((S_800AF448_0 *)arg0)->unk_A8 in update_item_menu_enabled_record */
struct S8004CBFC_a0;
struct S8004CBFC_a1;
void func_8004CBFC(struct S8004CBFC_a0 *state, struct S8004CBFC_a1 *entry, int *cursor);      /* extern */
extern M2C_UNK D_80071244;
extern M2C_UNK D_800792DC;


/* Update an enabled object's data and reset its referenced pointer. */
void update_item_menu_enabled_record(void *object) {
    if (((ItemMenuEnabledView *)(((S_800AF448_0 *)object)->unk_00))->unk_1C != 0) {
        func_8004CBFC(object + 0x1C, &D_800792DC, ((S_800AF448_2 *)(((S_800AF448_0 *)object)->unk_A8))->unk_10);
        *((S_800AF448_2 *)(((S_800AF448_0 *)object)->unk_A8))->unk_14 = &D_80071244;
    }
}
