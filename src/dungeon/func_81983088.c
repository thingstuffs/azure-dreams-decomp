#include "modules/dungeon_ovl_19a332c.h"

void func_80024888(void *effect, ovl_19a332c_81983088_S_80024888_0 *motion, ovl_19a332c_81983088_S_80024888_1 *color) {
    s32 velocity_x;
    s32 velocity_y;
    u16 update_count;
    u8 brightness;
    u8 faded_brightness;
    u16 life_left;

    update_count = D_800269F8;
    velocity_x = motion->unk_0C;
    velocity_y = motion->unk_10;
    D_800269F8 = update_count + 1;
    motion->unk_00 = motion->unk_00 + velocity_x;
    motion->unk_04 = motion->unk_04 + velocity_y;
    motion->unk_08 = motion->unk_08 + motion->unk_14;
    motion->unk_14 = motion->unk_14 + 0x2000;
    brightness = color->unk_0C;
    faded_brightness = brightness - (brightness >> 4);
    color->unk_0C = faded_brightness;
    color->unk_0D = faded_brightness;
    color->unk_0E = faded_brightness;
    life_left = ((ovl_19a332c_81983088_S_80024888_2 *)effect)->unk_30 - 1;
    ((ovl_19a332c_81983088_S_80024888_2 *)effect)->unk_30 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((ovl_19a332c_81983088_S_80024888_2_pre *)effect)[-1].unk_00 = ((ovl_19a332c_81983088_S_80024888_2_pre *)effect)[-1].unk_00 | 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
