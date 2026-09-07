#include "common.h"

typedef struct S_80020360_0_pre {
    u16 unk_00;
} S_80020360_0_pre;   /* the 0x2 bytes before arg0 in func_80020360, addressed as arg0[-1] */

typedef struct S_80020360_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_80020360_0;   /* arg0 in func_80020360 */

typedef struct S_80020360_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020360_1;   /* data in func_80020360 */

typedef struct S_80020360_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80020360_2;   /* (void *)page in func_80020360 */



extern s32 D_800814A0;

void func_80020360(void *arg0)
{
    s16 state;
    S_80020360_1 *data;
    u16 value;
    u16 flags;
    u16 count;
    register u32 page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    state = ((S_80020360_0 *)arg0)->unk_00.s;
    data = ((S_80020360_0 *)arg0)->unk_04;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    value = ((S_80020360_0 *)arg0)->unk_02 - 1;
    ((S_80020360_0 *)arg0)->unk_02 = value;
    if ((value << 16) > 0) {
        return;
    }
    flags = ((S_80020360_0 *)arg0)->unk_16;
    count = ((S_80020360_0 *)arg0)->unk_00.u;
    flags &= 0xFFFD;
    count++;
    ((S_80020360_0 *)arg0)->unk_16 = flags;
    ((S_80020360_0 *)arg0)->unk_00.u = count;
    return;

state_one:
    if (data->unk_2A & 1) {
        page = 0x80080000;
        ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_80020360_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        ((S_80020360_2 *)((void *)page))->unk_14A0 |= 0x8000;
    }
}

/* MECHANISM: Retail is a frameless leaf; both apparent jumps target the local epilogue.
   The state-zero arm uses sibling halfword temporaries so both loads precede both stores.
   A guarded $v1 page local holds 0x80080000 for the D_800814A0 RMW tail. */
