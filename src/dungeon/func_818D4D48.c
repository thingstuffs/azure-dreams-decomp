#include "modules/dungeon_ovl_18f4800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_818D4D48_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_818D4D48_0;   /* held_arg0 in func_80024548; pointer addresses record offset 0x2 */

typedef struct RenderFade33 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
} RenderFade33;   /* arg2 in func_80024548 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))




/* Fades and rotates an effect, decrements its timer, and flags completion. */
void func_80024548(void *record_data, s32 unused, RenderFade33 *effect)
{
    void *record_cursor = record_data;
    u16 old_angle;
    u16 ticks_left;
    u16 next_angle;

    ticks_left = ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04;
    D_80025118[0] = 1;
    ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04 = (u16)(ticks_left - 1);

    effect->unk_0C = (u8)((effect->unk_0C * 0xA) / 13);
    effect->unk_0D = (u8)((effect->unk_0D * 0xA) / 13);
    effect->unk_0E = (u8)((effect->unk_0E * 0xA) / 13);

    old_angle = effect->unk_1A;
    next_angle = old_angle + 0x300;
    effect->unk_1A = next_angle;

    if ((u32)(next_angle & 0xFFFF) >= 0x1001U) {
        effect->unk_1A = (u16)(old_angle - 0xD00);
    }

    if ((s16)((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04 <= 0) {
        ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
    }

    if (effect->unk_14 & 0x8000) {
        ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
    }
}
