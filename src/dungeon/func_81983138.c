#include "modules/dungeon_ovl_19a332c.h"

void *spawn_thirty_two_angled_particles(s16 x, s16 y, s16 z, s16 angle, s32 unused_context) {
    s32 direction_x;
    s32 direction_y;
    s32 ring_angle;
    s32 direction_angle;
    s32 particle_index;
    ovl_19a332c_81983138_S_80024938_2 *sprite;
    ovl_19a332c_81983138_S_80024938_1 *motion;
    void *particle;
    union { ovl_19a332c_81983138_S_80024938_3 * pointer; s32 value; } effect_state;
    union { s32 value; s32 *pointer; } size_texture;

    particle_index = 0;
    direction_angle = angle + 0x400;
    do {
        particle = func_8003FC64(0x202);
        if (particle != NULL) {
            ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_10 = (void *)advance_effect_motion_and_color_fade;
            func_8004491C(particle, func_80045340);
            motion = ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_08;
            motion->unk_02 = x;
            motion->unk_06 = y;
            motion->unk_0A = z;
            ring_angle = particle_index << 7;
            direction_x = func_80064584(direction_angle);
            motion->unk_0C = (s32) ((s32) (direction_x * func_80064584(ring_angle)) >> 6);
            direction_y = func_800644B8(direction_angle);
            motion->unk_10 = (s32) ((s32) (direction_y * func_80064584(ring_angle)) >> 6);
            motion->unk_14 = (s32) (func_800644B8(ring_angle) << 6);
            effect_state.value = 0x808080;
            sprite = ((ovl_19a332c_81983138_S_80024938_0 *)particle)->unk_0C;
            size_texture.value = 0x400;
            sprite->unk_1E = size_texture.value;
            sprite->unk_1C = size_texture.value;
            size_texture.pointer = &D_800269EC;
            sprite->unk_0C = effect_state.value;
            effect_state.value = sprite->unk_14;
            sprite->unk_08 = size_texture.pointer;
            sprite->unk_10 = 0x20;
            sprite->unk_14 = (u16) (effect_state.value | 0xC);
            effect_state.pointer = particle + 0x20;
            effect_state.pointer->unk_30 = 0xC;
            effect_state.pointer->unk_36 = (u16) angle;
        }
        particle_index += 1;
    } while (particle_index < 0x20);
    return particle;
}
