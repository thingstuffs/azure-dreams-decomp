#include "common.h"
#include "records/Rec_D_80082D58.h"


extern void func_80033D08(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8008F134(void *);

extern s32 D_800814A0;



typedef struct S_800B9D64_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B9D64_1;   /* arg1 in func_800B9D64 */

typedef struct S_800B9D64_2 {
    u8 pad_00[0x66];
    s16 unk_66;
} S_800B9D64_2;   /* ((Rec_D_80082D58 *)arg0)->unk_9C in func_800B9D64 */

/* Updates an angle-driven offset and handles inactive objects. */
void func_800B9D64(void *object, void *offset_state)
{
    s16 angle;
    s16 decay_angle;
    s32 sector;
    s32 phase_value;

    if (*((Rec_D_80082D58 *)object)->unk_98.as_pu8 == 0) {
        func_8008F134(object);
        func_80033D08(object);
        (*(u16 *)((u8 *)object + (-2))) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

    angle = ((S_800B9D64_2 *)(((Rec_D_80082D58 *)object)->unk_9C))->unk_66;
    sector = angle / 0x200;
    if ((s8)(sector % 4) == ((Rec_D_80082D58 *)object)->unk_97) {
        phase_value = func_800644B8((s16)(angle % 0x200) * 2);
        ((S_800B9D64_1 *)offset_state)->unk_08 = -((phase_value >> 4) * 0x1E00);
        ((Rec_D_80082D58 *)object)->unk_66 = 30;
        return;
    }

    if (((Rec_D_80082D58 *)object)->unk_66 != 0) {
        s32 offset;
        s32 amplitude;

        ((Rec_D_80082D58 *)object)->unk_66 = (u16)((Rec_D_80082D58 *)object)->unk_66 - 3;
        decay_angle = ((S_800B9D64_2 *)(((Rec_D_80082D58 *)object)->unk_9C))->unk_66;
        amplitude = ((func_80064584((s16)(decay_angle % 0x200) * 0x18) >> 4)
                     * ((Rec_D_80082D58 *)object)->unk_66) << 8;
        offset = -amplitude;

        ((S_800B9D64_1 *)offset_state)->unk_08 = offset;
        if (offset > 0) {
            ((S_800B9D64_1 *)offset_state)->unk_08 = amplitude;
            return;
        }
    } else {
        ((S_800B9D64_1 *)offset_state)->unk_08 = 0;
    }
}
