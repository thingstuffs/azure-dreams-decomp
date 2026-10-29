#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

s32 lookup_entry_and_apply_record_code();     /* extern */
extern s32 D_80018E48;

/* Apply operation 0x5BE and dispatch D_80018E48 with the supplied value and context. */
void apply_scene_operation_5_be(s32 value, s32 unused, s32 context) {
    func_80018ADC(F_sbs11_pad27);
    lookup_entry_and_apply_record_code(&D_80018E48, value, context);
}
