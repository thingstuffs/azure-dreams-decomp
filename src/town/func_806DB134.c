#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_806DB134_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806DB134_0;   /* D_80016000 in func_806DB134 */

typedef struct S_806DB134_1 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(s8 *);
} S_806DB134_1;   /* ((S_806DB134_0 *)D_80016000)->unk_20 in func_806DB134 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern S_806DB134_0 *D_80016000;


void func_806DB134(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 0xA;
    ((S_806DB134_1 *)(D_80016000->unk_20))->unk_50(sp10);
}
