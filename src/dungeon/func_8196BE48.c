#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before obj in func_8196BE48, addressed as obj[-1] */

   /* obj in func_8196BE48 */

   /* arg2 in func_8196BE48 */



/* Advance the effect animation, offset its sprite, and mark it expired when its lifetime ends. */
void func_80025648(void *effect_data, s32 unused, void *sprite) {
    u8 *effect = effect_data;
    u8 *global_page = (u8 *)&D_800269B4 - 0x69B4;
    u16 frame_ticks;
    u16 frame_index;
    u8 texture_u;

    ((S_8196BE48_0 *)effect)->unk_2C = (u16)(((S_8196BE48_0 *)effect)->unk_2C - 1);
    ((S_8196BE48_1 *)sprite)->unk_1C = (u16)(((S_8196BE48_1 *)sprite)->unk_1C + 0x7C);
    ((S_8196BE48_1 *)sprite)->unk_1E = (u16)(((S_8196BE48_1 *)sprite)->unk_1E + 0x54);
    frame_ticks = ((S_8196BE48_0 *)effect)->unk_34 + 1;
    *(s16 *)(global_page + 0x69B4) = 1;
    ((S_8196BE48_0 *)effect)->unk_34 = frame_ticks;
    if ((s16)frame_ticks == 3) {
        frame_index = ((S_8196BE48_0 *)effect)->unk_50 + 1;
        ((S_8196BE48_0 *)effect)->unk_50 = frame_index;
        if ((s16)frame_index < 7) {
            ((S_8196BE48_0 *)effect)->unk_34 = 0;
            texture_u = ((S_8196BE48_0 *)effect)->unk_40 + 0x18;
            ((S_8196BE48_0 *)effect)->unk_40 = texture_u;
            if ((texture_u & 0xFF) == 0x60) {
                ((S_8196BE48_0 *)effect)->unk_40 = 0;
                ((S_8196BE48_0 *)effect)->unk_41 = (u8)(((S_8196BE48_0 *)effect)->unk_41 + 0x20);
            }
        }
    }
    if ((s16)((S_8196BE48_0 *)effect)->unk_2C <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_8196BE48_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
