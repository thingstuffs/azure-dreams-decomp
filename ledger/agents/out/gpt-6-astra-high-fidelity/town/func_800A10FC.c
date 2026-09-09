#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_8009E85C_0_pre {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} S_8009E85C_0_pre;   /* the 0x10 bytes before arg0 in func_8009E85C, addressed as arg0[-1] */


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
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern s32 D_800D09C8[];

void func_8009E85C(void *arg0, S_8009E85C_1 *arg1, S_8009E85C_2 *arg2) {
    u8 *page = (u8 *)0x80010000;
    s32 *active_base;
    s32 active;
    s32 init_flags;
    S_8009E85C_4 *tail_self;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register M2C_UNK (*callback)(void *, void *, void *) ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *call_a0;
    void *call_a1;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_a2;
    u16 flags;
    u8 temp_v1;

    ((S_8009E85C_0_pre *)arg0)[-1].unk_00 = D_8009E714;
    ((Rec_func_80094268_arg0 *)arg0)->unk_A0 = 0xFFE00000;
    arg1->unk_08 = 0xFFE00000;
    ((Rec_func_80094268_arg0 *)arg0)->unk_4C = page[(((Rec_func_80094268_arg0 *)arg0)->unk_95 * 4) + 0x980];
    temp_v1 = page[(((Rec_func_80094268_arg0 *)arg0)->unk_95 * 4) + 0x981];
    ((Rec_func_80094268_arg0 *)arg0)->unk_4D = temp_v1;
    if (temp_v1 == 0x12) {
        arg2->unk_08 = &D_8006E240;
    } else {
        func_8009DC8C(arg0, arg2, ((Rec_func_80094268_arg0 *)arg0)->unk_4C, M2C_FIELD(page, s32 *, ((page[(((Rec_func_80094268_arg0 *)arg0)->unk_95 * 4) + 0x983] & 0x3F) * 0x54) + 0xA94));
    }
    func_80033CD8(arg0, &D_80045340);
    init_flags = 0x20;
    active_base = (s32 *)0x800D0000;
    arg2->unk_10 = init_flags;
    flags = arg2->unk_14.s;
    active = ((S_8009E85C_3 *)active_base)->unk_9C8;
    arg2->unk_14.u = (u16)(flags | 0x1C);
    tail_self = arg0;
    if (active == 0) {
        ((Rec_func_80094268_arg0 *)arg0)->unk_6C.as_s16 = func_800374F4(0x1000);
    } else {
        /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tail_self->unk_6C = 0;
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    call_a0 = tail_self;
    call_a1 = arg1;
    call_a2 = arg2;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    callback = ((S_8009E85C_5_pre *)call_a0)[-1].unk_00;
    D_800D09C8[0] = 0;
    callback(call_a0, call_a1, call_a2);
}

/* MECHANISM: A held 0x80010000 page recreates retail's shared a1 table base and argument lifetimes.
   A split volatile RMW plus guarded v0/v1 roles interleaves the flag and global loads without a nop.
   Pinned tail ABI roles and ASM_MEM_BARRIER keep the s0 store before a0-a2 setup and the global clear
   in the indirect-call delay slot. */
