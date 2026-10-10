#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* arg0 in func_8196B074 */

   /* arg1 in func_8196B074 */



/* Advance motion, resolve collisions, and mark expired objects for removal. */
void func_80024874(void *motion, void *position, s32 update_id) {
    s32 height;
    u16 remaining_ticks;

    remaining_ticks = ((S_8196B074_0 *)motion)->unk_2C;
    D_800269B4 = 1;
    ((S_8196B074_0 *)motion)->unk_2C = remaining_ticks - 1;
    func_800478B8(update_id);
    ((S_8196B074_1 *)position)->unk_00.at00.v += ((S_8196B074_0 *)motion)->unk_8C;
    ((S_8196B074_0 *)motion)->unk_8C += ((S_8196B074_0 *)motion)->unk_98;
    if ((func_800A45D8(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
        ((S_8196B074_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)position)->unk_00.at00.v -= ((S_8196B074_0 *)motion)->unk_8C;
        ((S_8196B074_0 *)motion)->unk_8C = 0;
        ((S_8196B074_0 *)motion)->unk_98 = 0;
    }
    ((S_8196B074_1 *)position)->unk_04.at00.v += ((S_8196B074_0 *)motion)->unk_90;
    ((S_8196B074_0 *)motion)->unk_90 += ((S_8196B074_0 *)motion)->unk_9C;
    if ((func_800A45D8(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
        ((S_8196B074_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_8196B074_1 *)position)->unk_04.at00.v -= ((S_8196B074_0 *)motion)->unk_90;
        ((S_8196B074_0 *)motion)->unk_90 = 0;
        ((S_8196B074_0 *)motion)->unk_9C = 0;
    }
    ((S_8196B074_1 *)position)->unk_08.at00.v += ((S_8196B074_0 *)motion)->unk_94;
    ((S_8196B074_0 *)motion)->unk_94 += ((S_8196B074_0 *)motion)->unk_A0;
    height = ((S_8196B074_1 *)position)->unk_08.at02.v;
    if (((s16)func_800BCB04(((S_8196B074_1 *)position)->unk_00.at02.v, ((S_8196B074_1 *)position)->unk_04.at02.v,
                       (s16)((u16)((S_8196B074_1 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_8196B074_0 *)motion)->unk_94 = 0;
        ((S_8196B074_0 *)motion)->unk_90 = 0;
        ((S_8196B074_0 *)motion)->unk_8C = 0;
        ((S_8196B074_1 *)position)->unk_08.at02.v = (s16)func_800BCB04(((S_8196B074_1 *)position)->unk_00.at02.v,
            ((S_8196B074_1 *)position)->unk_04.at02.v,
                                               (s16)((u16)((S_8196B074_1 *)position)->unk_08.at02.v - 4)) - 0x11;
        ((S_8196B074_1 *)position)->unk_08.at00u.v = 0;
        ((S_8196B074_0 *)motion)->unk_2C = 0;
    }
    if ((s16)((S_8196B074_0 *)motion)->unk_2C <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
