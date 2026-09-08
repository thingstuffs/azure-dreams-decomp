#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"


typedef struct S_800AFD5C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800AFD5C_2;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_9C in func_800AFD5C */


typedef struct S_800AFD5C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
} S_800AFD5C_0;   /* arg0 in func_800AFD5C; pointer addresses record offset 0x10 */


void func_800AF9C4(void *arg0);
extern M2C_UNK D_800AFD00[];

/* Update the linked value from the current step and advance the state after six steps. */
void func_800AFD5C(void *object) {
    s32 step;
    s32 nextStep;

    step = ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18;
    ((S_800AFD5C_2 *)(((Rec_func_800AF254_arg1 *)object)->unk_9C))->unk_06 = (s16) ((step << 0xC) / 5);
    nextStep = ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18 + 1;
    ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18 = nextStep;
    if (nextStep < 6) {
    } else {
        ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_00 = &D_800AFD00;
    }
    func_800AF9C4(object);
}
