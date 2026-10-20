#include "dungeon/monster/unicorn/advance_record_state_and_set_completion_flags.h"
#include "shared/sprite_frame_state.h"

/* Update the effect's orbit and height, fade its color, and mark it for removal when its life expires. */
void update_orbit_height_and_fade_effect(void *effect, EntityRec *position, SpriteFrameState *primitive) {
    s16 life;
    s16 angle;
    s16 next_life;

    angle = ((T_801741A0_S_801741A0_0 *)effect)->unk_1E - 0x12C;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1E = (u16) angle;
    position->x.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_40 + (func_80064584(angle) * 0x280));
    position->y.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_44
        + (func_800644B8((s16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1E) * 0x280));
    position->z.v = (s32) (position->z.v + 0xFFF60000);
    func_800478B8(primitive);
    if ((((T_801741A0_S_801741A0_0 *)effect)->unk_1A < 0x11) && (((T_801741A0_S_801741A0_0 *)effect)->unk_20 == 0) && !(rand() & 0xF)) {
        create_tinted_sprite_effect_supplied_position(effect, position, primitive);
    }
    life = ((T_801741A0_S_801741A0_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->color.c.r = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_00 * life) / 9);
        primitive->color.c.g = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_01 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
        primitive->color.c.b = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_02 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1A - 1;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 = (u16) (((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
