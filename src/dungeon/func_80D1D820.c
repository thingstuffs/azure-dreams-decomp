/* Relink of matched dungeon/func_80D11820; every changed retail word is a paired relocation. */
#define spawn_random_velocity_offset_effect func_80165020
#define create_timed_offset_motion_effect D_80164D2C
#define move_fade_and_accelerate_effect D_80164F0C
#include "modules/dungeon_ovl_7f43f800_p02.h"
extern s32 rand(void);

/* Spawns an effect at an offset from its parent with randomized velocity. */
void func_80165020(EntityRec *parent, s16 effect_id, s32 effect_param, s32 unused, s16 x_offset,
    s16 y_offset, s16 z_offset) {
    register s16 saved_effect_id = effect_id;
    register s32 saved_effect_param = effect_param;
    T_80171020_S_80171020_2 *position_x;
    T_80171020_S_80171020_3 *position_y;
    T_80171020_S_80171020_1 *effect_state;
    void *effect;

    effect = func_8003FD64(0x211, parent);
    if (effect == NULL) {
        return;
    }
    ((T_80171020_S_80171020_0 *)effect)->unk_10 = &move_fade_and_accelerate_effect;
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_02 =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_02 + x_offset);
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_06 =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_06 + y_offset);
    ((T_80171020_S_80171020_6 *)(((T_80171020_S_80171020_4 *)effect)->unk_08))->unk_0A =
        (s16) (((T_80171020_S_80171020_7 *)((*(void * *)&parent->z)))->unk_0A + z_offset);
    effect_state = effect + 0x20;
    effect_state->unk_40 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_44 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_48 = (s32) (((rand() & 0x3FFF) - 0x6000) * 0x10);
    position_x = ((T_80171020_S_80171020_0 *)effect)->unk_08;
    position_x->unk_00 = (s32) (position_x->unk_00 + (effect_state->unk_40 * 2));
    position_y = ((T_80171020_S_80171020_0 *)effect)->unk_08;
    position_y->unk_04 = (s32) (position_y->unk_04 + (effect_state->unk_44 * 2));
    effect_state->unk_54 = 0x8000;
    effect_state->unk_14 = saved_effect_id;
    effect_state->unk_32 = 0x14;
    effect_state->unk_34 = 0x14;
    func_8004491C(effect, &create_timed_offset_motion_effect);
    ((T_80171020_S_80171020_0 *)effect)->unk_20 = saved_effect_param;
    effect_state->unk_08 = saved_effect_param;
}
