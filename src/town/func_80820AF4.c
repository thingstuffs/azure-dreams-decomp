#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800232F4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    void * unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    s16 unk_16;
} S_800232F4_0;   /* obj in func_800232F4 */

typedef struct S_800232F4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_800232F4_1;   /* owner in func_800232F4 */


extern void func_800537D0(s32, s32, void *);
/* Updates the display value, then moves the object outward and flags it when out of bounds. */
void func_800232F4(void *object)
{
    u8 *obj;
    void *owner;
    s16 state;
    register u16 step;

    obj = object;
    state = ((S_800232F4_0 *)obj)->unk_00.s;
    owner = ((S_800232F4_0 *)obj)->unk_0C;

    switch (state) {
    case 0:
    step = *((S_800232F4_0 *)obj)->unk_08;
    func_800537D0(step * 100, 5,
                  ((S_800232F4_0 *)obj)->unk_04 + 4);
    if (((S_800232F4_1 *)owner)->unk_5C != 3) {
        return;
    }

    if (((S_800232F4_0 *)obj)->unk_16 < 120) {
        ((S_800232F4_0 *)obj)->unk_02.s = -8;
    } else {
        ((S_800232F4_0 *)obj)->unk_02.s = 8;
    }
    ((S_800232F4_0 *)obj)->unk_00.u++;
        break;

    case 1:
    ((S_800232F4_0 *)obj)->unk_16 += ((S_800232F4_0 *)obj)->unk_02.s;
    ((S_800232F4_0 *)obj)->unk_16 += ((S_800232F4_0 *)obj)->unk_02.s >> 2;
    if ((u16)(((S_800232F4_0 *)obj)->unk_16 + 8) >= 249) {
        (*(u16 *)((u8 *)obj + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
        break;
    }
}
