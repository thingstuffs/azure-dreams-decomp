#include "common.h"

typedef struct S_818D4A94_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_818D4A94_0;   /* arg1 in func_818D4A94 */

typedef struct S_818D4A94_1_pre {
    u16 unk_00;
} S_818D4A94_1_pre;   /* the 0x2 bytes before arg0 in func_818D4A94, addressed as arg0[-1] */

typedef struct S_818D4A94_1 {
    u8 pad_00[0x32];
    u16 unk_32;
    s16 unk_34;
    u8 pad_36[0x6];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4A94_1;   /* arg0 in func_818D4A94 */



extern s16 D_80025118[5];
extern s32 D_800814A0[3];

void func_818D4A94(void *arg0, S_818D4A94_0 *arg1)
{
    register s32 x ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 a ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 aux ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 one;
    s32 z;

    x = arg1->unk_00.at00.v;
    x += ((S_818D4A94_1 *)arg0)->unk_3C;
    arg1->unk_00.at00.v = x;
    x = arg1->unk_04;
    x += ((S_818D4A94_1 *)arg0)->unk_40;
    arg1->unk_04 = x;
    x = arg1->unk_08;
    x += ((S_818D4A94_1 *)arg0)->unk_44;
    arg1->unk_08 = x;

    x = ((S_818D4A94_1 *)arg0)->unk_3C;
    z = ((S_818D4A94_1 *)arg0)->unk_48;
    a = ((S_818D4A94_1 *)arg0)->unk_4C;
    aux = ((S_818D4A94_1 *)arg0)->unk_50;
    x += z;
    ((S_818D4A94_1 *)arg0)->unk_3C = x;
    x = ((S_818D4A94_1 *)arg0)->unk_40;
    z = ((S_818D4A94_1 *)arg0)->unk_44;
    x += a;
    z += aux;
    ((S_818D4A94_1 *)arg0)->unk_40 = x;
    x = ((S_818D4A94_1 *)arg0)->unk_34;
    ASM_USE(x);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_MEM_NV(a, D_80025118[0]);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_USE2_NV(a, x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_818D4A94_1 *)arg0)->unk_44 = z;
    a = arg1->unk_00.at02.v;
    ASM_USE(a);   /* MATCH pin: retail schedule: same instructions, different order without it */
    one = 1;
    ASM_USE2_NV(a, one);   /* MATCH pin: retail schedule: same instructions, different order without it */
    x -= a;
    if (x < 0) {
        x = -x;
    }
    x = x < 0x10;
    D_80025118[0] = one;
    if (x) {
        ((S_818D4A94_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    x = ((S_818D4A94_1 *)arg0)->unk_32;
    x -= 8;
    ((S_818D4A94_1 *)arg0)->unk_32 = x;
    x <<= 16;
    if (x <= 0) {
        ((S_818D4A94_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
