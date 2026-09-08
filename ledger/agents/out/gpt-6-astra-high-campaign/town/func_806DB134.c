#include "common.h"
#include "records/Rec_D_80016000.h"





typedef struct S_806DB134_1 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(s8 *);
} S_806DB134_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_806DB134 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern Rec_D_80016000 *D_80016000;


/* Pass the two-byte command 0x0A, 0x17 to the state callback. */
void func_806DB134(void) {
    s8 command[2];

    command[1] = 0x17;
    command[0] = 0xA;
    ((S_806DB134_1 *)(D_80016000->unk_20))->unk_50(command);
}
