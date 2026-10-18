#include "common.h"

s32 lookup_entry_and_apply_record_code();     /* extern */
void func_80018ADC(s32);                     /* extern */
extern s32 D_80018E48;

/* Apply operation 0x5BE and dispatch D_80018E48 with the supplied value and context. */
void apply_scene_operation_5_be(s32 value, s32 unused, s32 context) {
    func_80018ADC(0x5BE);
    lookup_entry_and_apply_record_code(&D_80018E48, value, context);
}
