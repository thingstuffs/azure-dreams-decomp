#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_800189BC_2 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
} S_800189BC_2;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_800189BC */

typedef struct S_800189BC_3 {
    u8 pad_00[0x4C];
    M2C_UNK (*unk_4C)(M2C_UNK, M2C_UNK);
} S_800189BC_3;   /* ((S_800189BC_2 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_800189BC */

extern s32 func_8001890C(void *obj);
extern M2C_UNK D_80016000[];
extern u32 D_8001C368[];

typedef struct S_800189BC_0 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_800189BC_0;   /* temp_a0 in func_800189BC */

/* Decrements the object's counter and invokes a callback if the object check succeeds. */
void func_800189BC(void) {
    S_800189BC_0 *counter_obj;

    counter_obj = ((S_800189BC_2 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_38;
    counter_obj->unk_2D5C = (u32) (counter_obj->unk_2D5C - D_8001C368[0]);
    if (func_8001890C(counter_obj) != 0) {
        ((S_800189BC_3 *)(((S_800189BC_2 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_4C(0x10, 5);
    }
}
