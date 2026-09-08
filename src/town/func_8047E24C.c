#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8047E24C_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8047E24C_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_8047E24C */




extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_8001781C;
extern M2C_UNK *D_8001794C;
extern M2C_UNK D_8001857C;


/* Set the global and current record's pointers to their static data. */
void func_8047E24C(void) {
    D_8001794C = &D_8001781C;
    ((S_8047E24C_1 *)(D_80016000->unk_1C.as_pv))->unk_40 = &D_8001857C;
}
