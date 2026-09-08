#include "common.h"
#include "records/Rec_D_80082E80.h"




#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern void func_800C4174(void *arg0, M2C_UNK arg1, void *arg2);
extern u8 D_80082660;
extern M2C_UNK D_800D5518;
extern M2C_UNK D_800D5624;
extern M2C_UNK D_800D562C;
extern M2C_UNK D_800D5654;
extern M2C_UNK D_800D5658;


typedef struct S_800C5C70_1 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    s32 unk_60;
    u8 pad_64[0xC];
    s8 unk_70;
    u8 unk_71;
    u8 pad_72[0xA];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C5C70_1;   /* arg0 in func_800C5C70 */

/* Reset the indexed flag, install handlers, and update the object on input flags 0x6000. */
void func_800C5C70(void *object, M2C_UNK context, void *input) {
    if (((Rec_D_80082E80 *)input)->unk_14.at00_u16.v & 0x6000) {
        func_800C2E84(object, input, &D_800D5518);
        *((((S_800C5C70_1 *)object)->unk_60 * 8) + &D_80082660) = 0;
        ((S_800C5C70_1 *)object)->unk_58 = &D_800D5654;
        ((S_800C5C70_1 *)object)->unk_5C = &D_800D5658;
        ((S_800C5C70_1 *)object)->unk_7C = &D_800D5624;
        ((S_800C5C70_1 *)object)->unk_80 = &D_800D562C;
        ((S_800C5C70_1 *)object)->unk_70 = 1;
        ((S_800C5C70_1 *)object)->unk_71 = (u8) (((S_800C5C70_1 *)object)->unk_71 | 1);
        func_800C4174(object, context, input);
    }
}
