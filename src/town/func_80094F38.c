#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"


#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800927C8();
extern M2C_UNK func_80093D48();
extern M2C_UNK func_800942B0();
extern M2C_UNK func_80094378();
extern M2C_UNK func_8009451C();
extern M2C_UNK func_80095094();
extern s16 func_80095978();
extern M2C_UNK func_80095A94();
extern M2C_UNK func_80095C80();

typedef struct {
    u8 pad[0x10];
    s32 field_10;
} State80083160;

extern State80083160 D_80083160;
extern void *D_800CFCC4[3];
extern u8 D_800CFCEF[9];
extern u8 D_800FE488[9];




typedef struct S_80092698_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80092698_2;   /* D_800CFCC4[0] in func_80092698 */

void func_80092698(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    u16 temp_v0_2;
    State80083160 *state = &D_80083160;
    u8 *data;
    register M2C_UNK saved_arg2 ASM_REG("$19") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    func_80095C80(arg1);
    ASM_KEEP(saved_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_80095094(arg1);
    data = D_800FE488;
    temp_v0 = func_80095978(arg1, data);
    if ((temp_v0 - arg1->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(arg0, arg1, saved_arg2);
            func_800927C8();
            return;
        }
        goto block_6;
    }
    if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, temp_v0, data);
    }
block_6:
    temp_v0_2 = arg0->unk_0A.as_u16 - 1;
    arg0->unk_0A.as_u16 = temp_v0_2;
    if ((s16)temp_v0_2 < 0) {
        if (D_800CFCC4[0] != NULL) {
            if (((S_80092698_2 *)(D_800CFCC4[0]))->unk_14 == 2) {
                func_80093D48(arg0, arg1, saved_arg2);
                func_800927C8();
                return;
            }
            func_8009451C(arg0, arg1, saved_arg2);
            func_800927C8();
            return;
        }
        func_8009451C(arg0, arg1, saved_arg2);
        func_800927C8();
        return;
    }
    if (state->field_10 & 0x10) {
        func_800942B0(arg0, arg1, saved_arg2);
    }
}
