#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"

   /* arg1 in func_8196C280 */

   /* arg0 in func_8196C280 */

   /* arg2 in func_8196C280 */





/* Move the effect with collision checks, shrink its sprite, and expire it when finished. */
void func_80025A80(void *effect, void *position, void *sprite) {
    u16 age;
    u16 reduced_scale_x;
    u16 reduced_scale_y;
    u16 life_left;
    u16 scale_x;
    u16 next_scale_y;

    ((S_8196C280_0 *)position)->unk_00.at00.v += ((S_8196C280_1 *)effect)->unk_8C;
    ((S_8196C280_1 *)effect)->unk_8C += ((S_8196C280_1 *)effect)->unk_98;
    {
        u16 check_x;
        u16 check_y;
        s32 check_z;

        check_x = ((S_8196C280_0 *)position)->unk_00.at02.v;
        check_y = ((S_8196C280_0 *)position)->unk_04.at02.v;
        check_z = ((S_8196C280_0 *)position)->unk_08.at02.v;
        D_800269B4 = 1;
        if ((func_800A45D8(check_x, check_y, check_z) << 0x10) != 0) {
            ((S_8196C280_0 *)position)->unk_00.at00.v -= ((S_8196C280_1 *)effect)->unk_8C;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_1 *)effect)->unk_98 = 0;
        }
    }
    ((S_8196C280_0 *)position)->unk_04.at00.v += ((S_8196C280_1 *)effect)->unk_90;
    ((S_8196C280_1 *)effect)->unk_90 += ((S_8196C280_1 *)effect)->unk_9C;
    if ((func_800A45D8(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v,
        ((S_8196C280_0 *)position)->unk_08.at02.v) << 0x10) != 0) {
        ((S_8196C280_0 *)position)->unk_04.at00.v -= ((S_8196C280_1 *)effect)->unk_90;
        ((S_8196C280_1 *)effect)->unk_90 = 0;
        ((S_8196C280_1 *)effect)->unk_9C = 0;
    }
    ((S_8196C280_0 *)position)->unk_08.at00.v += ((S_8196C280_1 *)effect)->unk_94;
    ((S_8196C280_1 *)effect)->unk_94 += ((S_8196C280_1 *)effect)->unk_A0;
    {
        s32 height;

        height = ((S_8196C280_0 *)position)->unk_08.at02.v;
        if (((s16)func_800BCB04(((S_8196C280_0 *)position)->unk_00.at02.v, ((S_8196C280_0 *)position)->unk_04.at02.v,
            (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
            ((S_8196C280_1 *)effect)->unk_94 = 0;
            ((S_8196C280_1 *)effect)->unk_90 = 0;
            ((S_8196C280_1 *)effect)->unk_8C = 0;
            ((S_8196C280_0 *)position)->unk_08.at02.v = (s16)func_800BCB04(((S_8196C280_0 *)position)->unk_00.at02.v,
                ((S_8196C280_0 *)position)->unk_04.at02.v, (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - 4))
            - 0x11;
            ((S_8196C280_0 *)position)->unk_08.at00u.v = 0;
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
    }
    age = ((S_8196C280_1 *)effect)->unk_50;
    ((S_8196C280_1 *)effect)->unk_50 = age + 1;
    if ((s16)age >= 3) {
        scale_x = ((S_8196C280_2 *)sprite)->unk_1C;
        next_scale_y = ((S_8196C280_2 *)sprite)->unk_1E;
        reduced_scale_x = scale_x - 0x100;
        scale_x = reduced_scale_x;
        if ((s16)reduced_scale_x < 0) {
            scale_x = 0;
        }
        reduced_scale_y = next_scale_y - 0x100;
        next_scale_y = reduced_scale_y;
        if ((s16)reduced_scale_y < 0) {
            next_scale_y = 0;
        }
        if (((next_scale_y << 0x10) == 0) || ((scale_x << 0x10) == 0)) {
            ((S_8196C280_1 *)effect)->unk_2C = 0;
        }
        ((S_8196C280_2 *)sprite)->unk_1C = scale_x;
        ((S_8196C280_2 *)sprite)->unk_1E = next_scale_y;
    }
    func_80024AF8(effect, position, sprite,
        (s16)(((S_8196C280_0 *)position)->unk_00.at02.v - ((u16)D_80083780.x.w.i)),
        (s16)(((S_8196C280_0 *)position)->unk_04.at02.v - ((u16)D_80083780.y.w.i)),
        (s16)(((S_8196C280_0 *)position)->unk_08.at02u.v - ((u16)D_80083780.z.w.i)));
    life_left = ((S_8196C280_1 *)effect)->unk_2C - 1;
    ((S_8196C280_1 *)effect)->unk_2C = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    if (((S_8196C280_2 *)sprite)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
