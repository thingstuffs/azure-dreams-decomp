#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80017458_1 {
    u8 pad_00[0x238];
    M2C_UNK (*unk_238)(M2C_UNK, M2C_UNK);
} S_80017458_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80017458 */




extern Rec_D_80016000 *D_80016000;


/* Invoke the system object callback with 0x25 and 0x200. */
void func_80017458(void) {
    ((S_80017458_1 *)(D_80016000->unk_20))->unk_238(0x25, 0x200);
}
