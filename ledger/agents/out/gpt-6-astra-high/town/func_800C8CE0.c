#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C6440_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C6440_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C6440 */




extern M2C_UNK D_800D58B8;


/* Set both linked pointers to D_800D58B8. */
void func_800C6440(Rec_func_80094268_arg0 *record) {
    *record->unk_7C.as_ppm = &D_800D58B8;
    ((S_800C6440_2 *)(((Rec_func_80094268_arg0 *)record)->unk_80))->unk_04 = &D_800D58B8;
}
