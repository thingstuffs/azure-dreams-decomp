#include "common.h"
#include "records/Rec_D_80082D58.h"


extern void func_80033D08(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8008F134(void);
extern void func_800B9EC4(void);

extern s32 D_800814A0;



typedef struct S_800B9D64_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B9D64_1;   /* arg1 in func_800B9D64 */

typedef struct S_800B9D64_2 {
    u8 pad_00[0x66];
    s16 unk_66;
} S_800B9D64_2;   /* ((Rec_D_80082D58 *)arg0)->unk_9C in func_800B9D64 */

void func_800B9D64(void *arg0, void *arg1)
{
    s16 angle;
    s16 angle2;
    s32 sector;
    s32 value;

    if (*((Rec_D_80082D58 *)arg0)->unk_98.as_pu8 == 0) {
        func_8008F134();
        func_80033D08(arg0);
        (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800B9EC4();
        return;
    }

    angle = ((S_800B9D64_2 *)(((Rec_D_80082D58 *)arg0)->unk_9C))->unk_66;
    sector = angle / 0x200;
    if ((s8)(sector % 4) == ((Rec_D_80082D58 *)arg0)->unk_97) {
        value = func_800644B8((s16)(angle % 0x200) * 2);
        ((S_800B9D64_1 *)arg1)->unk_08 = -((value >> 4) * 0x1E00);
        ((Rec_D_80082D58 *)arg0)->unk_66 = 30;
        func_800B9EC4();
        return;
    }

    if (((Rec_D_80082D58 *)arg0)->unk_66 != 0) {
        s32 value2;
        s32 magnitude;

        ((Rec_D_80082D58 *)arg0)->unk_66 = (u16)((Rec_D_80082D58 *)arg0)->unk_66 - 3;
        angle2 = ((S_800B9D64_2 *)(((Rec_D_80082D58 *)arg0)->unk_9C))->unk_66;
        magnitude = ((func_80064584((s16)(angle2 % 0x200) * 0x18) >> 4)
                     * ((Rec_D_80082D58 *)arg0)->unk_66) << 8;
        value2 = -magnitude;
        
        ((S_800B9D64_1 *)arg1)->unk_08 = value2;
        if (value2 > 0) {
            ((S_800B9D64_1 *)arg1)->unk_08 = magnitude;
            func_800B9EC4();
        }
    } else {
        ((S_800B9D64_1 *)arg1)->unk_08 = 0;
    }
}
