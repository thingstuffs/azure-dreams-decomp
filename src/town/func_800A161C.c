#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"


typedef struct S_8009ED7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009ED7C_1;   /* temp_a0 in func_8009ED7C */

typedef struct S_8009ED7C_2_pre {
    u16 unk_00;
} S_8009ED7C_2_pre;   /* the 0x2 bytes before arg0 in func_8009ED7C, addressed as arg0[-1] */



M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK itm_mon_koyaw_set(); /* extern */
M2C_UNK func_800C0C88();                            /* extern */
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;
extern s32 D_80100B50[];
extern s32 D_80100B68[];

/* Move toward the target and finalize the object when its countdown expires. */
void func_8009ED7C(void *object, M2C_UNK context, void *motion) {
    s32 *target_pos;
    s32 *global_flags;
    u16 ticks_or_flags;

    target_pos = D_80100B50;
    ((EntityRec *)motion)->unk_0C = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_00 - ((EntityRec *)motion)->x.v) / 2);
    ((EntityRec *)motion)->unk_10 = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_04 - ((EntityRec *)motion)->y.v) / 2);
    ((EntityRec *)motion)->flags14 = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_08 - ((EntityRec *)motion)->z.v) / 2);
    func_8009539C(motion);
    func_8008F294(context, motion);
    func_8008F664(context, motion);
    ticks_or_flags = ((Rec_D_80082D58 *)object)->unk_6C.as_u16 - 1;
    ((Rec_D_80082D58 *)object)->unk_6C.as_u16 = ticks_or_flags;
    if ((ticks_or_flags << 0x10) <= 0) {
        itm_mon_koyaw_set(D_80100B68[0], object + 0x4C, &D_80100AF8, 0);
        func_8008F134(object);
        func_80033D08(object);
        ticks_or_flags = ((S_8009ED7C_2_pre *)object)[-1].unk_00;
        global_flags = ((s32 *)(&objectFlagBlock));
        (*(u16 *)((u8 *)object + -2)) = (u16) (ticks_or_flags | 0x8000);
        *global_flags = *global_flags | 0x8000;
        func_800C0C88();
    }
}
