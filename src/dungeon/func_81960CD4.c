#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* scratch in create_linked_objects */

   /* the 0x2 bytes before arg0 in create_linked_objects, addressed as arg0[-1] */

   /* arg0 in create_linked_objects */

   /* arg1 in create_linked_objects */

   /* arg2 in create_linked_objects */

s32 rand();

/* Rotate and move a quad, fade its color in and out, then mark it for removal. */
void create_linked_objects(void *quad, S_81960CD4_2 *motion, S_81960CD4_3 *effect) {
    u8 *scratch = (u8 *)0x1F800000;
    u16 rotation[3];
    s16 remaining_count;
    s16 fade_in_ticks;
    s16 fade_out_ticks;
    s32 blue_step;
    u16 center_z;
    u16 effect_count;
    u8 fade_in_blue;
    u8 fade_in_red;
    u8 fade_in_green;
    u8 fade_out_red;
    u8 fade_out_green;
    u8 fade_out_blue;
    u16 update_count;
    u16 vertex_z;

    ((S_81960CD4_0 *)scratch)->unk_70 = ((S_81960CD4_1 *)quad)->unk_10 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_78 = ((S_81960CD4_1 *)quad)->unk_18 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_80 = ((S_81960CD4_1 *)quad)->unk_20 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_88 = ((S_81960CD4_1 *)quad)->unk_28 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_72 = ((S_81960CD4_1 *)quad)->unk_12 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7A = ((S_81960CD4_1 *)quad)->unk_1A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_82 = ((S_81960CD4_1 *)quad)->unk_22 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_8A = ((S_81960CD4_1 *)quad)->unk_2A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_74 = ((S_81960CD4_1 *)quad)->unk_14 - motion->unk_08.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7C = ((S_81960CD4_1 *)quad)->unk_1C - motion->unk_08.at02.v;
    update_count = D_80027330;
    vertex_z = ((S_81960CD4_1 *)quad)->unk_24;
    center_z = motion->unk_08.at02.v;
    D_80027330 = (u16)(update_count + 1);
    ((S_81960CD4_0 *)scratch)->unk_84 = vertex_z - center_z;
    ((S_81960CD4_0 *)scratch)->unk_8C = ((S_81960CD4_1 *)quad)->unk_2C - motion->unk_08.at02.v;
    func_800649A0(center_z);
    rotation[0] = effect->unk_16;
    rotation[1] = effect->unk_18;
    rotation[2] = 0;
    ((S_81960CD4_0 *)scratch)->unk_30 = effect->unk_1C;
    ((S_81960CD4_0 *)scratch)->unk_34 = effect->unk_1E;
    ((S_81960CD4_0 *)scratch)->unk_38 = 0x1000;
    ((S_81960CD4_0 *)scratch)->unk_6C = 0;
    ((S_81960CD4_0 *)scratch)->unk_68 = 0;
    ((S_81960CD4_0 *)scratch)->unk_64 = 0;
    func_80065820(rotation, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);
    func_80065320(scratch + 0x70, scratch + 0x98, scratch + 0x94);
    func_80065320(scratch + 0x78, scratch + 0xA0, scratch + 0x94);
    func_80065320(scratch + 0x80, scratch + 0xA8, scratch + 0x94);
    func_80065320(scratch + 0x88, scratch + 0xB0, scratch + 0x94);
    func_80064A40();
    motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v + motion->unk_0C);
    motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + motion->unk_10);
    motion->unk_08.at00.v = (s32)(motion->unk_08.at00.v + motion->unk_14);
    ((S_81960CD4_1 *)quad)->unk_10 = (u16)(((S_81960CD4_0 *)scratch)->unk_98 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_18 = (u16)(((S_81960CD4_0 *)scratch)->unk_A0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_20 = (u16)(((S_81960CD4_0 *)scratch)->unk_A8 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_28 = (u16)(((S_81960CD4_0 *)scratch)->unk_B0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_12 = (u16)(((S_81960CD4_0 *)scratch)->unk_9A + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1A = (u16)(((S_81960CD4_0 *)scratch)->unk_A2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_22 = (u16)(((S_81960CD4_0 *)scratch)->unk_AA + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2A = (u16)(((S_81960CD4_0 *)scratch)->unk_B2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_14 = (u16)(((S_81960CD4_0 *)scratch)->unk_9C + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1C = (u16)(((S_81960CD4_0 *)scratch)->unk_A4 + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_24 = (u16)(((S_81960CD4_0 *)scratch)->unk_AC + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2C = (u16)(((S_81960CD4_0 *)scratch)->unk_B4 + motion->unk_08.at02.v);
    if (((S_81960CD4_1 *)quad)->unk_48.s == 0) {
        fade_in_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_in_red + ((s32)(0xC0 - fade_in_red) / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_in_green = effect->unk_0D;
        remaining_count = ((S_81960CD4_1 *)quad)->unk_4C;
        fade_in_blue = effect->unk_0E;
        effect->unk_0D = (u8)(fade_in_green + ((s32)(0xC0 - fade_in_green) / remaining_count));
        blue_step = (s32)(0xC0 - fade_in_blue) / (s16)((S_81960CD4_1 *)quad)->unk_4C;
        effect->unk_0E = (u8)(fade_in_blue + blue_step);
        fade_in_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_in_ticks;
        if ((fade_in_ticks << 0x10) <= 0) {
            motion->unk_0C = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_10 = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_14 = (s32)(((rand() & 0x3F) - 0x20) << 0x10);
            effect->unk_16 = (u16)((rand() & 0x3FF) - 0x200);
            effect->unk_18 = (u16)((rand() & 0x3FF) - 0x200);
            ((S_81960CD4_1 *)quad)->unk_4C = 0x10;
            ((S_81960CD4_1 *)quad)->unk_48.u = (u16)(((S_81960CD4_1 *)quad)->unk_48.u + 1);
            return;
        }
    } else {
        fade_out_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_out_red - ((s32)fade_out_red / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_green = effect->unk_0D;
        effect->unk_0D = (u8)(fade_out_green - ((s32)fade_out_green / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_blue = effect->unk_0E;
        effect->unk_0E = (u8)(fade_out_blue - ((s32)fade_out_blue / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_out_ticks;
        if ((fade_out_ticks << 0x10) <= 0) {
            remaining_count = *(s16 *)((u16 *)&D_800273BC);
            if (remaining_count != 0) {
                effect_count = D_800273BC.value - 1;
                (*(u16 *)((u16 *)&D_800273BC)) = effect_count;
                if ((s16)effect_count == 1) {
                    (*(u16 *)((u16 *)&D_800273BC)) = 0U;
                }
            }
            ((S_81960CD4_1_pre *)quad)[-1].unk_00 = (u16)(((S_81960CD4_1_pre *)quad)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
    }
}
