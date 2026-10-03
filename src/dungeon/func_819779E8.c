#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800251E8_0_pre {
    u16 unk_00;
} S_800251E8_0_pre;   /* the 0x2 bytes before object in func_800251E8, addressed as object[-1] */

typedef struct S_800251E8_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u16 unk_08;
} S_800251E8_0;   /* object in func_800251E8 */

typedef struct S_800251E8_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_800251E8_1;   /* linked in func_800251E8 */

/* Advances the object's timed state and updates its 30 entries. */
void func_800251E8(void *object_data)
{
    void *object;
    S_800251E8_1 *linked;
    s32 state;
    s32 entry_index;
    u32 entry_offset;
    u16 accumulated_value;
    u16 increment;
    u16 counter;
    s32 signed_value;
    s32 adjusted_value;

    object = object_data;
    linked = ((S_800251E8_0 *)object)->unk_00;
    linked->unk_1A++;
    ((S_800251E8_0 *)object)->unk_06.s++;
    state = ((S_800251E8_0 *)object)->unk_04.s;
    switch (state) {
    case 0:
        ((S_800251E8_0 *)object)->unk_08 -= 0xC0;
        if (((S_800251E8_0 *)object)->unk_06.u < 8) {
            break;
        }
        ((S_800251E8_0 *)object)->unk_06.s = 0;
        ((S_800251E8_0 *)object)->unk_04.u++;
        break;
    case 1:
        if (((S_800251E8_0 *)object)->unk_06.u < 12) {
            break;
        }
        ((S_800251E8_0 *)object)->unk_06.s = 0;
        ((S_800251E8_0 *)object)->unk_04.u++;
        break;
    case 2:
        if (((S_800251E8_0 *)object)->unk_06.u < 4) {
            break;
        }
        ((S_800251E8_0 *)object)->unk_06.s = 0;
        ((S_800251E8_0 *)object)->unk_04.u++;
        break;
    case 3:
        if (((S_800251E8_0 *)object)->unk_06.u < 8) {
            break;
        }
        ((S_800251E8_0 *)object)->unk_06.s = 0;
        ((S_800251E8_0 *)object)->unk_04.u++;
        break;
    case 4:
        ((S_800251E8_0_pre *)object)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    entry_index = 0;

    entry_offset = 0;
    do {
        accumulated_value = ((u16 *)object)[entry_offset + 0x23];
        increment = ((S_800251E8_0 *)object)->unk_08;
        counter = ((u16 *)object)[entry_offset + 5];
        counter++;
        ((u16 *)object)[entry_offset + 0x23] = accumulated_value + increment;
        counter += entry_index / 6;
        ((u16 *)object)[entry_offset + 5] = counter;
        if (entry_index >= 6) {
            signed_value = ((s16 *)object)[entry_offset + 0x41];
            if (entry_index < 24) {
                adjusted_value = signed_value + 5;
                adjusted_value -= entry_index;
            } else {
                adjusted_value = signed_value - 19;
            }
            ((s16 *)object)[entry_offset + 0x41] = adjusted_value;
        }
        entry_index++;
        entry_offset++;
    } while (entry_index < 30);

    return;
}
