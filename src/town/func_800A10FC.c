#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009E85C_0_pre {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} S_8009E85C_0_pre;   /* the 0x10 bytes before arg0 in func_8009E85C, addressed as arg0[-1] */

typedef struct S_8009E85C_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[0x1E];
    s16 unk_6C;
    u8 pad_6E[0x27];
    u8 unk_95;
    u8 pad_96[0xA];
    s32 unk_A0;
} S_8009E85C_0;   /* arg0 in func_8009E85C */

typedef struct S_8009E85C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009E85C_1;   /* arg1 in func_8009E85C */

typedef struct S_8009E85C_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x4];
    volatile s16 unk_10;
    u8 pad_12[0x2];
    union { volatile u16 s; u16 u; } unk_14;   /* accessed as both */
} S_8009E85C_2;   /* arg2 in func_8009E85C */

typedef struct S_8009E85C_3 {
    u8 pad_00[0x9C8];
    volatile s32 unk_9C8;
} S_8009E85C_3;   /* active_base in func_8009E85C */

typedef struct S_8009E85C_4 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_8009E85C_4;   /* tail_self in func_8009E85C */

typedef struct S_8009E85C_5_pre {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} S_8009E85C_5_pre;   /* the 0x10 bytes before call_a0 in func_8009E85C, addressed as call_a0[-1] */


M2C_UNK D_8009E714();         /* extern */
M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_800374F4();                     /* extern */
M2C_UNK func_8009DC8C();     /* extern */
M2C_UNK func_8009E918();                     /* extern */
M2C_UNK func_8009E95C();                            /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern s32 D_800D09C8[];

void func_8009E85C(void *arg0, S_8009E85C_1 *arg1, S_8009E85C_2 *arg2) {
    u8 *page = (u8 *)0x80010000;
    s32 *active_base;
    s32 active;
    s32 init_flags;
    S_8009E85C_4 *tail_self;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register M2C_UNK (*callback)(void *, void *, void *) ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    void *call_a0;
    void *call_a1;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_a2;
    u16 flags;
    u8 temp_v1;

    ((S_8009E85C_0_pre *)arg0)[-1].unk_00 = D_8009E714;
    ((S_8009E85C_0 *)arg0)->unk_A0 = 0xFFE00000;
    arg1->unk_08 = 0xFFE00000;
    ((S_8009E85C_0 *)arg0)->unk_4C = page[(((S_8009E85C_0 *)arg0)->unk_95 * 4) + 0x980];
    temp_v1 = page[(((S_8009E85C_0 *)arg0)->unk_95 * 4) + 0x981];
    ((S_8009E85C_0 *)arg0)->unk_4D = temp_v1;
    if (temp_v1 == 0x12) {
        arg2->unk_08 = &D_8006E240;
        func_8009E918();
        return;
    }
    func_8009DC8C(arg0, arg2, ((S_8009E85C_0 *)arg0)->unk_4C, M2C_FIELD(page, s32 *, ((page[(((S_8009E85C_0 *)arg0)->unk_95 * 4) + 0x983] & 0x3F) * 0x54) + 0xA94));
    func_80033CD8(arg0, &D_80045340);
    init_flags = 0x20;
    active_base = (s32 *)0x800D0000;
    arg2->unk_10 = init_flags;
    flags = arg2->unk_14.s;
    active = ((S_8009E85C_3 *)active_base)->unk_9C8;
    arg2->unk_14.u = (u16)(flags | 0x1C);
    if (active == 0) {
        ((S_8009E85C_0 *)arg0)->unk_6C = func_800374F4(0x1000);
        func_8009E95C();
        return;
    }
    tail_self = arg0;
       /* MATCH pin: retail schedule: same instructions, different order without it */
    tail_self->unk_6C = 0;
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    call_a0 = tail_self;
    call_a1 = arg1;
    call_a2 = arg2;
       /* MATCH pin: retail schedule: same instructions, different order without it */
    callback = ((S_8009E85C_5_pre *)call_a0)[-1].unk_00;
    D_800D09C8[0] = 0;
    callback(call_a0, call_a1, call_a2);
}

/* MECHANISM: A held 0x80010000 page recreates retail's shared a1 table base and argument lifetimes.
   A split volatile RMW plus guarded v0/v1 roles interleaves the flag and global loads without a nop.
   Pinned tail ABI roles and ASM_MEM_BARRIER keep the s0 store before a0-a2 setup and the global clear
   in the indirect-call delay slot. */
