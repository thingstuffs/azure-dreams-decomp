#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800243C4_arg1.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/screen.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "shared/sprite_frame_state.h"

extern void *create_linked_effect_segments(ObjectPosition *);

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

#include "dungeon/effect/sprite_effect_count_data.h"








typedef struct S_800243C4_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_800243C4_4;   /* arg2 in func_800243C4 */

typedef struct S_800243C4_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800243C4_5;   /* ((S_800243C4_0 *)arg0)->unk_08 in func_800243C4 */

/* Updates the effect's position, then brightens and fades its color. */
void advance_linked_segment_flash(ScreenTransitionEffectBody *effect, ObjectPosition *position, S_800243C4_4 *color)
{
    s16 phase;
    u16 phase_value;
    MovingPosition *base_position;
    SpriteFrameState *source;

    sprite_effect_update_count = sprite_effect_update_count + 1;
    phase = effect->unk_2C.s;
    phase_value = effect->unk_2C.u;

    if (phase == 0) {
        source = ((S_800243C4_5 *)(effect->unk_08))->unk_0C;
        if (effect->unk_2E == 0) {
            if (resolve_record_orientation_or_fallback(source->source, source,
                              (u8 *)effect + 0x24, 0) != 0) {
                effect->unk_2E = 1;
            } else if (source->flags & 0x8000) {
                effect->unk_2E = 1;
                effect->unk_28.s = -0x40;
            }
            if (effect->unk_2E == 0) {
                return;
            }
        }

        base_position = ((S_800243C4_5 *)(effect->unk_08))->unk_08;
        position->x.w.i =
            base_position->x + effect->unk_24;
        position->y.w.i =
            base_position->y + effect->unk_26;
        position->z.w.i =
            base_position->z + effect->unk_28.u;
        if (create_linked_effect_segments(position) != 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            effect->unk_2C.u = effect->unk_2C.u + 1;
            return;
        }
    } else if (phase == 1) {
        if ((u8)color->unk_0C < 0xC0) {
            color->unk_0C += 0x202020;
            return;
        }
        effect->unk_2C.u = phase_value + 1;
        return;
    } else if (phase == 2) {
        color->unk_0C += 0xFFFBFBFC;
        if ((u8)color->unk_0C == 0) {
            NODE_HEADER(effect)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
