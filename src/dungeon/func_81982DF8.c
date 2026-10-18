#include "modules/dungeon_ovl_19a332c.h"

void move_fade_and_expand_effect(void *effect_data, void *motion_data, void *sprite_data)
{
    ovl_19a332c_81982DF8_Arg2 *sprite = (ovl_19a332c_81982DF8_Arg2 *) sprite_data;
    void *effect = effect_data;
    ovl_19a332c_81982DF8_Arg1 *motion = (ovl_19a332c_81982DF8_Arg1 *) motion_data;
    s16 frames_left;
    s32 next_x;
    u16 scale;
    u16 count_or_scale;
    int zero;
    u8 brightness;
    u8 faded_brightness;
    count_or_scale = D_800269F8 + 1;
    next_x = motion->f0 + motion->fc;
    D_800269F8 = (u16) count_or_scale;
    motion->f0 = next_x;
    zero = 0;
    motion->f4 = motion->f4 + motion->f10;
    motion->f8 = motion->f8 + motion->f14;
    motion->f14 = motion->f14 + 0xC000;
    func_800478B8(sprite);
    brightness = sprite->c;
    faded_brightness = brightness - (((s32) brightness) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->c = faded_brightness;
    sprite->d = faded_brightness;
    sprite->e = faded_brightness;
    scale = sprite->f1c;
    count_or_scale = scale + (((s32) (0x400 - scale)) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
    sprite->f1c = count_or_scale;
    sprite->f1e = count_or_scale;
    frames_left = ((u16) (*((s16 *) (((s8 *) effect) + 0x30)))) - 1;
    *((s16 *) (((s8 *) effect) + 0x30)) = frames_left;
    if ((frames_left << 0x10) <= zero) {
        *((u16 *) (((s8 *) effect) + (-2))) = (u16) ((*((u16 *) (((s8 *) effect) + (-2)))) | 0x8000);
        ((s32 *)(&object_flag_block))[zero] = (s32) (object_flag_block.flags | 0x8000);
    }
}
