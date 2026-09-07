#include "common.h"
#include "m2c_compat.h"

typedef struct S_8047E24C_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8047E24C_0;   /* D_80016000 in func_8047E24C */

typedef struct S_8047E24C_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8047E24C_1;   /* ((S_8047E24C_0 *)D_80016000)->unk_1C in func_8047E24C */




extern S_8047E24C_0 *D_80016000;
extern M2C_UNK D_8001781C;
extern M2C_UNK *D_8001794C;
extern M2C_UNK D_8001857C;


void func_8047E24C(void) {
    D_8001794C = &D_8001781C;
    ((S_8047E24C_1 *)(D_80016000->unk_1C))->unk_40 = &D_8001857C;
}
