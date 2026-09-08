#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_81862B74_0_pre {
    u16 unk_00;
} S_81862B74_0_pre;   /* the 0x2 bytes before arg0 in func_81862B74, addressed as arg0[-1] */

typedef struct S_81862B74_0 {
    void * unk_00;
    u16 unk_04;
} S_81862B74_0;   /* arg0 in func_81862B74 */

typedef struct S_81862B74_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81862B74_1;   /* temp_v1 in func_81862B74 */



M2C_UNK func_8002425C();             /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

/* Increment counters, call func_8002425C at ten, and propagate target status flags. */
void func_81862B74(void *state, M2C_UNK context, Rec_D_80082E80 *target) {
    u16 update_count;
    S_81862B74_1 *linked_object;

    linked_object = ((S_81862B74_0 *)state)->unk_00;
    linked_object->unk_14 = (u16) (linked_object->unk_14 + 1);
    func_800478B8(target);
    update_count = ((S_81862B74_0 *)state)->unk_04 + 1;
    ((S_81862B74_0 *)state)->unk_04 = update_count;
    if ((s16) update_count == 0xA) {
        func_8002425C(((S_81862B74_0 *)state)->unk_00, context);
    }
    if (target->unk_14.at00_u16.v & 0x6000) {
        ((S_81862B74_0_pre *)state)[-1].unk_00 = (u16) (((S_81862B74_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
