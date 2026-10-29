#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame.h"

   /* the 0x2 bytes before arg0 in update_record_and_install_next_table, addressed as arg0[-1] */

typedef struct S_80026748_0 {
    void * unk_00;
    s32 unk_04;
} S_80026748_0;   /* arg0 in update_record_and_install_next_table */


typedef struct S_80026748_2 {
    u8 pad_00[0x58];
    u16 unk_58;
} S_80026748_2;


/* Advance effect motion and shrink its scale, marking completion at the threshold. */
void update_record_and_install_next_table(void *effect, ObjectPosition *motion, SpriteFrameState *transform) {
    ObjectStatusPrefix16 *effect_view = effect;
    u16 scale;
    S_80026748_2 *render_state;

    render_state = ((S_80026748_0 *)effect)->unk_00;
    motion->x.v = (s32) (motion->x.v + ((S_80026748_0 *)effect)->unk_04);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    render_state->unk_58 = (u16) (render_state->unk_58 | 1);
    scale = transform->scale_y - 0x100;
    transform->scale_y = scale;
    transform->scale_x = scale;
    if ((u32) (scale & 0xFFFF) < 0x201U) {
        render_state->unk_58 = (u16) (render_state->unk_58 & 0xFFFE);
        effect_view[-1].flags = (u16) (effect_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
