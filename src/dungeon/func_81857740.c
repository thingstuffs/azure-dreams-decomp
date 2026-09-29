#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80024F40_0_pre {
    u16 unk_00;
} S_80024F40_0_pre;   /* the 0x2 bytes before arg0 in func_80024F40, addressed as arg0[-1] */

typedef struct S_80024F40_0 {
    void * unk_00;
    u8 pad_04[0x30];
    union { u8 u8; s32 s32; } unk_34;   /* accessed as both */
    u8 pad_38[0xA];
    s16 unk_42;
    u8 pad_44[0x6];
    union { s16 s; u16 u; } unk_4A;   /* accessed as both */
} S_80024F40_0;   /* arg0 in func_80024F40 */

typedef struct S_80024F40_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024F40_1;   /* temp_v0 in func_80024F40 */

s16 func_8006649C();
s32 func_80069EF8();

/* Fades the object's packed color to zero, then sets completion flags. */
void func_80024F40(void *object) {
    s16 fade_state;
    void *linked_object;

    linked_object = ((S_80024F40_0 *)object)->unk_00;
    ((S_80024F40_1 *)linked_object)->unk_52 =
        (u16)(((S_80024F40_1 *)linked_object)->unk_52 | 0x8000);
    ((S_80024F40_0 *)object)->unk_42 =
        func_8006649C((func_80069EF8() & 0xF) * 0x10, 0x1F8);
    fade_state = ((S_80024F40_0 *)object)->unk_4A.s;
    switch (fade_state) {
    case 0:
        if ((u8)((S_80024F40_0 *)object)->unk_34.u8 < 0x31U) {
            ((S_80024F40_0 *)object)->unk_34.s32 = 0;
            ((S_80024F40_0 *)object)->unk_4A.u++;
            return;
        }
        ((S_80024F40_0 *)object)->unk_34.s32 = ((S_80024F40_0 *)object)->unk_34.s32 - 0x303030;
        break;
    case 1:
        (*(u16 *)((u8 *)object + -2)) =
            (u16)(((S_80024F40_0_pre *)object)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
        break;
    }
}
