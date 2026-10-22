#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in update_record_and_install_next_table, addressed as arg0[-1] */

typedef struct S_80026748_0 {
    void * unk_00;
    s32 unk_04;
} S_80026748_0;   /* arg0 in update_record_and_install_next_table */

typedef struct S_80026748_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80026748_1;   /* arg1 in update_record_and_install_next_table */

typedef struct S_80026748_2 {
    u8 pad_00[0x58];
    u16 unk_58;
} S_80026748_2;

typedef struct S_80026748_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80026748_3;   /* arg2 in update_record_and_install_next_table */


/* Advance effect motion and shrink its scale, marking completion at the threshold. */
void update_record_and_install_next_table(void *effect, S_80026748_1 *motion, S_80026748_3 *transform) {
    ObjectStatusPrefix16 *effect_view = effect;
    u16 scale;
    S_80026748_2 *render_state;

    render_state = ((S_80026748_0 *)effect)->unk_00;
    motion->unk_00 = (s32) (motion->unk_00 + ((S_80026748_0 *)effect)->unk_04);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    render_state->unk_58 = (u16) (render_state->unk_58 | 1);
    scale = transform->unk_1E - 0x100;
    transform->unk_1E = scale;
    transform->unk_1C = scale;
    if ((u32) (scale & 0xFFFF) < 0x201U) {
        render_state->unk_58 = (u16) (render_state->unk_58 & 0xFFFE);
        effect_view[-1].unk_00 = (u16) (effect_view[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
