#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C838C_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C838C_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C838C */




M2C_UNK func_800C3050(); /* extern */
extern M2C_UNK D_800D6244;
extern M2C_UNK D_800D62D8;
extern M2C_UNK D_800D62E0;
extern M2C_UNK D_800D6308;
extern M2C_UNK D_800D630C;


void func_800C838C(Rec_func_80094268_arg0 *arg0) {
    func_800C3050(arg0, 0xA, &D_800D6308, &D_800D630C, &D_800D62D8, &D_800D62E0);
    ((S_800C838C_1 *)(arg0->unk_80))->unk_04 = &D_800D6244;
}

/* MECHANISM: Keeping arg0 as the leading call argument holds it in s0 across the call
   and restores the two sibling outgoing stack slots, yielding the retail 0x20 frame.
   The 2.7.2-cdk-G0 lineage supplies the retail address-materialization order exactly. */
