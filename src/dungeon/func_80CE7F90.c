#include "dungeon/monster/troll/troll_flash_effects.h"
#include "shared/sprite_frame_state.h"

/* Creates an effect at an offset position with randomized attributes and motion. */
void spawn_random_color_burst_particle(void *source, void *position) {
    T_80171790_S_80171790_5 *source_obj;
    T_80171790_S_80171790_4 *source_pos;
    s32 obj_or_angle;
    s32 data_or_speed;
    T_80171790_S_80171790_0 *effect_state;
    void *init_obj;
    T_80171790_S_80171790_3 *effect_pos;
    u8 random_byte_1;
    u8 random_byte_2;

    source_obj = source;
    source_pos = position;
    obj_or_angle = (s32) func_8003FC64(0x212);
    if (obj_or_angle != 0) {
        init_obj = (void *) obj_or_angle;
        effect_state = (void *) obj_or_angle + 0x20;
        effect_state->unk_18 = 6;
        effect_state->unk_1A = 6;
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_10 = &update_saved_rgb_fade;
        register_node(init_obj, ((s32 *)update_rotating_actor_aura));
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((SpriteFrameState *)data_or_speed)->tpage_abr = 0x60;
        ((SpriteFrameState *)data_or_speed)->flags =
            (u16) (((SpriteFrameState *)data_or_speed)->flags | 0xC);
        effect_pos = ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_08;
        effect_pos->unk_02 = source_pos->unk_02;
        effect_pos->unk_06 = source_pos->unk_06;
        effect_pos->unk_0A =
            (s16) (source_pos->unk_0A - 0x50);
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((SpriteFrameState *)data_or_speed)->scale_y = 0x1000;
        ((SpriteFrameState *)data_or_speed)->scale_x = 0x1000;
        ((SpriteFrameState *)data_or_speed)->color.c.r = rand();
        ((SpriteFrameState *)data_or_speed)->color.c.g = rand();
        ((SpriteFrameState *)data_or_speed)->color.c.b = rand();
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_20 =
            ((SpriteFrameState *)data_or_speed)->color.c.r;
        random_byte_1 = ((SpriteFrameState *)data_or_speed)->color.c.g;
        effect_state->unk_01 = random_byte_1;
        random_byte_2 = ((SpriteFrameState *)data_or_speed)->color.c.b;
        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;
        effect_state->unk_02 = random_byte_2;
        obj_or_angle = rand() & 0xFFF;
        data_or_speed =
            (source_obj->unk_AE * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_62 =
            (source_obj->unk_AE * func_800644B8(obj_or_angle)) >> 0xC;
        obj_or_angle = rand() & 0xFFF;
        effect_state->unk_5A =
            (data_or_speed * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_5E =
            (data_or_speed * func_800644B8(obj_or_angle)) >> 0xC;
    }
}

/* MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
   reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body.
   Two scheduler seams retain the random_byte_1 load-delay nop,
       while a split random_byte_2 live range hoists its lbu. */
