#include "common.h"
#include "shared/object_flags.h"
#include "shared/entity.h"


extern s32 func_80033D08(void *, EntityRec *);
extern s32 func_80095388();
extern s32 func_8009539C();
extern s16 func_800C2AE8();

extern u8 D_8009C5D8[];


typedef struct S_8009C4E8_0_pre {
    u16 unk_00;
} S_8009C4E8_0_pre;   /* the 0x2 bytes before arg0 in func_8009C4E8, addressed as arg0[-1] */

typedef struct S_8009C4E8_0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_8009C4E8_0;   /* arg0 in func_8009C4E8 */


typedef struct S_8009C4E8_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8009C4E8_2;   /* arg2 in func_8009C4E8 */

/* Updates a timed object, expiring it or stopping its motion at the height limit. */
void func_8009C4E8(void *object, EntityRec *motion, S_8009C4E8_2 *appearance) {
    s16 height_limit;
    u16 timer;

    timer = ((S_8009C4E8_0 *)object)->unk_6C - 1;
    ((S_8009C4E8_0 *)object)->unk_6C = timer;
    if ((s16)(timer) < 0) {
        func_80033D08(object, motion);
        ((S_8009C4E8_0_pre *)object)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    func_80095388(motion);
    func_8009539C(motion);
    height_limit = func_800C2AE8(motion);
    if (motion->z.w.i > height_limit) {
        motion->z.w.i = height_limit;
        motion->unk_0C = 0;
        motion->unk_10 = 0;
        motion->flags14 = 0;
        appearance->unk_0E = 0x40;
        appearance->unk_0D = 0x40;
        appearance->unk_0C = 0x40;
        appearance->unk_10 = 0x20;
        appearance->unk_14 |= 0x1C;
        ((S_8009C4E8_0 *)object)->unk_50 = D_8009C5D8;
    }
}
