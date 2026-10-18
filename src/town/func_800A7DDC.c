#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

typedef struct S_800A553C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    M2C_UNK * unk_10;
} S_800A553C_0;   /* arg0 in initialize_effect_record_handlers; pointer addresses record offset 0x10 */


M2C_UNK func_80033D08();                      /* extern */
extern M2C_UNK D_800A5638;
extern M2C_UNK D_800A5FDC;
extern s32 D_800D0460;
extern M2C_UNK D_800D0C50;

/* Set the record handlers, initialize its data, clear the global state, and finish setup. */
void initialize_effect_record_handlers(void *record_data, s32 unused, s32 destination) {
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A5638;
    store_the_in_forwards_field_10_callee_800949_c_4((s32) &D_800D0C50, record_data, (void *) destination);
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_10 = &D_800A5FDC;
    D_800D0460 = 0;
    func_80033D08(record_data);
}
