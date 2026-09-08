#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_806D4EA0_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_806D4EA0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_806D4EA0 */




extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80018AE4;
extern M2C_UNK *D_80018BA4;
extern M2C_UNK D_80018B38;


/* Initializes the global and current record's data pointers. */
void func_806D4EA0(void) {
    D_80018BA4 = &D_80018AE4;
    ((S_806D4EA0_1 *)(D_80016000->unk_1C.as_pv))->unk_40 = &D_80018B38;
}
