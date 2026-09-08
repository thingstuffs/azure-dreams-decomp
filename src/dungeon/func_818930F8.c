#include "common.h"
#include "m2c_compat.h"

typedef struct S_818930F8_0_pre {
    u16 unk_00;
} S_818930F8_0_pre;   /* the 0x2 bytes before arg0 in func_818930F8, addressed as arg0[-1] */

typedef struct S_818930F8_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
} S_818930F8_0;   /* arg0 in func_818930F8 */

typedef struct S_818930F8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818930F8_1;   /* temp_v1 in func_818930F8 */


extern M2C_UNK func_80024824();
extern M2C_UNK func_800478B8();
extern s32 D_800814A0[3];

/* Advance the object counters, apply the initial frame offset, and flag completion. */
void func_818930F8(void *state, M2C_UNK draw_context, M2C_UNK update_context) {
    s16 frame;
    S_818930F8_1 *object;

    object = ((S_818930F8_0 *)state)->unk_00;
    object->unk_14 = (u16) (object->unk_14 + 1);
    ((S_818930F8_0 *)state)->unk_04 = (u16) (((S_818930F8_0 *)state)->unk_04 + 1);
    func_800478B8(update_context);
    frame = (s16) ((S_818930F8_0 *)state)->unk_04;
    if (frame < 5) {
        func_80024824(((S_818930F8_0 *)state)->unk_00, draw_context, 8, (s16) ((frame * 0x10) - 0x40));
    }
    if ((s16) ((S_818930F8_0 *)state)->unk_04 > ((S_818930F8_0 *)state)->unk_06) {
        ((S_818930F8_0_pre *)state)[-1].unk_00 = (u16) (((S_818930F8_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
