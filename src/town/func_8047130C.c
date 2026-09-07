#include "common.h"
#include "m2c_compat.h"

typedef struct S_8047130C_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8047130C_0;   /* D_80016000 in func_8047130C */

typedef struct S_8047130C_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8047130C_1;   /* ((S_8047130C_0 *)D_80016000)->unk_38 in func_8047130C */




extern S_8047130C_0 *D_80016000;
extern u32 D_8001B210;


s32 func_8047130C(void) {
    return (u32) ((S_8047130C_1 *)(D_80016000->unk_38))->unk_2D5C >= (u32) D_8001B210;
}
