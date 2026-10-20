#include "common.h"
#include "m2c_compat.h"

void card_boot_refresh_slot_details();                      /* extern */
void draw_cylindrical(void *);                      /* extern */

typedef struct S_80024F3C_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
} S_80024F3C_0;

/* Stores two object values and runs the associated update routines. */
void card_boot_set_slot_details_selection(s32 object_addr, s32 value_7c, s32 value_80) {
    S_80024F3C_0 *object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        object_data->unk_7C = value_7c;
        object_data->unk_80 = value_80;
        draw_cylindrical(object_data);
        card_boot_refresh_slot_details(object_data);
    }
}
