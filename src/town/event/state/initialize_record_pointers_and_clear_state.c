#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"

typedef struct S_800A97D8_0 {
    void (*unk_00)();
    u8 pad_04[0x5C];
    void (*unk_60)();
} S_800A97D8_0;   /* arg0 in initialize_record_pointers_and_clear_state; pointer addresses record offset 0x10 */

   /* arg1 in initialize_record_pointers_and_clear_state */


extern void unit_scale_record_handler_address();
extern void D_800A9778(u16 *record);

/* Initialize the record pointers and clear the associated state field. */
void initialize_record_pointers_and_clear_state(void *record_data, EffectStateWordView *state) {
    ((S_800A97D8_0 *)((u8 *)record_data - 0x10))->unk_00 = &unit_scale_record_handler_address;
    ((S_800A97D8_0 *)((u8 *)record_data - 0x10))->unk_60 = &D_800A9778;
    state->unk_08 = 0;
}
