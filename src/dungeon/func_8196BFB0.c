#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"

   /* arg1 in func_8196BFB0 */

   /* arg0 in func_8196BFB0 */

   /* arg2 in func_8196BFB0 */

   /* camera in func_8196BFB0 */




/* Updates and renders a shrinking object with collision and lifetime checks. */
void func_800257B0(void *object, void *position, void *render_state)
{
    s32 height;
    s16 scale_x;
    s16 scale_y;
    s32 collide_x;
    s32 collide_y;
    s32 collide_z;

    ((S_8196BFB0_0 *)position)->unk_00.at00.v += ((S_8196BFB0_1 *)object)->unk_8C;
    ((S_8196BFB0_1 *)object)->unk_8C += ((S_8196BFB0_1 *)object)->unk_98;
    collide_x = ((S_8196BFB0_0 *)position)->unk_00.at02.v;
    collide_y = ((S_8196BFB0_0 *)position)->unk_04.at02.v;
    collide_z = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    D_800269B4 = 1;
    if ((s16)func_800A45D8(collide_x, collide_y, collide_z) != 0) {
        ((S_8196BFB0_0 *)position)->unk_00.at00.v -= ((S_8196BFB0_1 *)object)->unk_8C;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_1 *)object)->unk_98 = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_04.at00.v += ((S_8196BFB0_1 *)object)->unk_90;
    ((S_8196BFB0_1 *)object)->unk_90 += ((S_8196BFB0_1 *)object)->unk_9C;
    if ((s16)func_800A45D8(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_08.at02.v) != 0) {
        ((S_8196BFB0_0 *)position)->unk_04.at00.v -= ((S_8196BFB0_1 *)object)->unk_90;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_9C = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_08.at00.v += ((S_8196BFB0_1 *)object)->unk_94;
    ((S_8196BFB0_1 *)object)->unk_94 += ((S_8196BFB0_1 *)object)->unk_A0;

    height = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    if ((s16)(s16)func_800BCB04(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           (s16)(((S_8196BFB0_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_8196BFB0_1 *)object)->unk_94 = 0;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_0 *)position)->unk_08.at02.v =
            (s16)func_800BCB04(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                          ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                          (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - 4)) - 0x11;
        ((S_8196BFB0_0 *)position)->unk_08.at00u.v = 0;
        ((S_8196BFB0_1 *)object)->unk_2C = 0;
    }

    if (((S_8196BFB0_1 *)object)->unk_50++ >= 3) {
        scale_x = ((S_8196BFB0_2 *)render_state)->unk_1C.u;
        scale_y = ((S_8196BFB0_2 *)render_state)->unk_1E.u;
        scale_x = scale_x - 0x100;
        if (scale_x < 0) {
            scale_x = 0;
        }
        scale_y = scale_y - 0x100;
        if (scale_y < 0) {
            scale_y = 0;
        }
        ((S_8196BFB0_2 *)render_state)->unk_1C.s = scale_x;
        ((S_8196BFB0_2 *)render_state)->unk_1E.s = scale_y;
    }

    func_80024AF8(object, position, render_state,
                  (s16)(((S_8196BFB0_0 *)position)->unk_00.at02.v - ((u16)D_80083780.x.w.i)),
                  (s16)(((S_8196BFB0_0 *)position)->unk_04.at02.v - ((u16)D_80083780.y.w.i)),
                  (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - ((u16)D_80083780.z.w.i)));

    if (--((S_8196BFB0_1 *)object)->unk_2C <= 0) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

    if (((S_8196BFB0_2 *)render_state)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
