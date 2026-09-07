#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D4EA0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_806D4EA0_0;   /* D_80016000 in func_806D4EA0 */

typedef struct S_806D4EA0_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_806D4EA0_1;   /* ((S_806D4EA0_0 *)D_80016000)->unk_1C in func_806D4EA0 */




extern S_806D4EA0_0 *D_80016000;
extern M2C_UNK D_80018AE4;
extern M2C_UNK *D_80018BA4;
extern M2C_UNK D_80018B38;


void func_806D4EA0(void) {
    D_80018BA4 = &D_80018AE4;
    ((S_806D4EA0_1 *)(D_80016000->unk_1C))->unk_40 = &D_80018B38;
}
