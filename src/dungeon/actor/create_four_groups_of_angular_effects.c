#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

void register_node(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void draw_textured_ellipse(void *, void *, s32, s32);
extern u8 D_8002744C[9];
extern u8 D_80028880[9];
extern u8 D_8002888C[9];
extern s16 view_facing_angle_alias;
extern s32 D_800CEEFC[3];
/* Creates four groups of 32 effect objects with angularly distributed motion. */
void *create_four_groups_of_angular_effects(s16 pos_x, s16 pos_y, s16 pos_z)
{
    s32 rect[2];
    s32 angle;
    u16 facing;
    s32 base_angle;
    s32 motion_angle;
    s32 scale_shift;
    s32 sample_angle;
    s32 sample_index;
    s32 group_index;
    void *effect;
    u8 *positions;
    u8 *effect_state;
    u8 *sprite;
    void *data;
    void *callback = D_8002744C;

    rect[0] = 0x01800380;
    rect[1] = 0x400040;
    angle = ((view_facing_angle_alias + 0x500) >> 9) & 7;
    facing = (u8)angle << 9;
    sprite = D_8002888C;
    data = rect;
    draw_textured_ellipse(sprite, data, 1, 0);
    base_angle = angle << 9;
    group_index = 0;
next_group:
    sample_index = 0;
    motion_angle = base_angle + 0x400;
    scale_shift = 5 - group_index;
spawn:
    effect = allocate_flagged_object_node(0x202);
    if (effect != 0) {
        *(void **)((u8 *)effect + 0x10) = callback;
        data = D_800CEEFC;
        register_node(effect, data);
        positions = *(u8 **)((u8 *)effect + 8);
        *(s16 *)(positions + 2) = pos_x;
        *(s16 *)(positions + 0xE) = pos_x;
        *(s16 *)(positions + 6) = pos_y;
        *(s16 *)(positions + 0x12) = pos_y;
        *(s16 *)(positions + 0xA) = pos_z;
        *(s16 *)(positions + 0x16) = pos_z;
        sample_angle = sample_index << 7;
        effect_state = (u8 *)effect + 0x20;
        *(s32 *)(effect_state + 0xC) = (func_80064584(motion_angle) * func_80064584(sample_angle)) >> scale_shift;
        *(s32 *)(effect_state + 0x10) = (func_800644B8(motion_angle) * func_80064584(sample_angle)) >> scale_shift;
        *(s32 *)(effect_state + 0x14) = func_800644B8(sample_angle) << ((group_index >> 1) + 7);
        sprite = *(u8 **)((u8 *)effect + 0xC);
        data = (void *)0x808080;
        ((SpriteFrameState *)sprite)->scale_y = 0x400;
        ((SpriteFrameState *)sprite)->scale_x = 0x400;
        ((SpriteFrameState *)sprite)->source = D_80028880;
        ((SpriteFrameState *)sprite)->tpage_abr = 0x20;
        ((SpriteFrameState *)sprite)->color.word = (s32)data;
        ((SpriteFrameState *)sprite)->flags |= 0xC;
        *(s16 *)(effect_state + 0x66) = 0xC;
        *(u16 *)(effect_state + 0x74) = facing;
    }
    sample_index++;
    if (sample_index < 0x20) {
        goto spawn;
    }
    group_index++;
    if (group_index < 4) {
        goto next_group;
    }
    return effect;
}
