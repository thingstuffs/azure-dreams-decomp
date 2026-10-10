#include "modules/dungeon_ovl_1960800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"





   /* temp_s0 in func_800249F0 */

   /* temp_a3 in func_800249F0 */

   /* the 0x18 bytes before arg0 in func_800249F0, addressed as arg0[-1] */

   /* temp_a0 in func_800249F0 */

   /* temp_v1 in func_800249F0 */

   /* temp_a3_2 in func_800249F0 */

/* Create an object with copied position and packed data, and initialize its rendering state. */
void *func_800249F0(void *source, void *unused_1, void *unused_2, void *packed_data, s32 render_param, s32 render_x,
    s32 render_y, s32 render_mode) {
    s16 render_param_copy;
    S_800249F0_3 *position;
    void *render_state;
    S_800249F0_0 *state;
    void *object;
    S_800249F0_4 *source_position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_2A = 0x3C;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &func_800249A0;
        func_8004491C(object, (s32)func_80045340);
        render_state = (*(void **)((u8 *)object + 0xC));
        ((S_800249F0_1 *)render_state)->unk_14 |= 0xC;
        render_param_copy = render_param;
        ((S_800249F0_1 *)render_state)->unk_10 = (s16) (render_param_copy << 5);
        ((S_800249F0_1 *)render_state)->unk_14 |= 0x80;
        source_position = ((S_800249F0_2_pre *)source)[-1].unk_00;
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) source_position->unk_00;
        position->unk_04 = (s32) source_position->unk_04;
        position->unk_08 = (s32) source_position->unk_08;
        render_state = (*(void **)((u8 *)object + 0xC));
        ((S_800249F0_5 *)render_state)->unk_1C = (s16) render_x;
        ((S_800249F0_5 *)render_state)->unk_1E = (s16) render_y;
        ((S_800249F0_5 *)render_state)->unk_0E = 0x80;
        ((S_800249F0_5 *)render_state)->unk_0D = 0x80;
        ((S_800249F0_5 *)render_state)->unk_0C = (s8) render_mode;
        (*(Packed12 *)((u8 *)object + 0x92)) = *(Packed12 *)packed_data;
        ((S_800249F0_5 *)render_state)->unk_08 = (void *) (object + 0x92);
        return state;
    } else {
        return NULL;
    }
}
