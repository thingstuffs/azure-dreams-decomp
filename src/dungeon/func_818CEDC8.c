#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* arg1 in func_800245C8 */

   /* the 0x2 bytes before arg0 in func_800245C8, addressed as arg0[-1] */

   /* arg0 in func_800245C8 */



s32 rand();

/* Updates effect motion, collisions, animation, scale, and expiration. */
void func_800245C8(void *state, B32_818CEDC8_S_818CEDC8_0 *position, Rec_D_80082E80 *sprite) {
    s32 current_z;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 life_left;
    s32 collision_z;

    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_58);
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v,
                       (collision_z = position->unk_08.at02.v, D_80025924[0] = 1, collision_z)) << 0x10) != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v - ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C);
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = 0;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_58 = 0;
    }
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_5C);
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0) {
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v - ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50);
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = 0;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_5C = 0;
    }
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54);
    {
        s32 accel_z = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_60;
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54 += accel_z;
    }
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) ((((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C * 0x60) / 100);
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) ((((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 * 0x60) / 100);
    current_z = position->unk_08.at02.v;
    if ((func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02u.v - 4)) - 0x10) < current_z) {
        ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_54 = 0;
        position->unk_08.at02.v = (s16) (func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02.v - 4)) - 0x11);
        position->unk_08.at00u.v = 0;
        if (((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_08 == 0) {
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_08 = 1;
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_4C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
            ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_50 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
        }
    }
    frame_count = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_04 + 1;
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_04 = frame_count;
    if (!(frame_count & 3)) {
        func_800478B8(sprite);
    }
    scale_x = sprite->unk_1C.at00_u16.v + 0x64;
    sprite->unk_1C.at00_u16.v = scale_x;
    if ((u32) (scale_x & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at00_u16.v = 0x1000U;
    }
    scale_y = sprite->unk_1C.at02_u16.v + 0x64;
    sprite->unk_1C.at02_u16.v = scale_y;
    if ((u32) (scale_y & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at02_u16.v = 0x1000U;
    }
    life_left = ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_02 - 1;
    ((B32_818CEDC8_S_818CEDC8_1 *)state)->unk_02 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        ((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((B32_818CEDC8_S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
