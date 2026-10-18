#include "common.h"
#include "m2c_compat.h"

s32 lookup_entry_and_apply_record_code();     /* extern */
M2C_UNK func_80018ADC();                     /* extern */
extern s32 D_80018E48;

/* Apply operation 0x5BE and dispatch D_80018E48 with the supplied value and context. */
void apply_scene_operation_5_be(s32 value, M2C_UNK unused, M2C_UNK context) {
    func_80018ADC(0x5BE);
    lookup_entry_and_apply_record_code(&D_80018E48, value, context);
}
