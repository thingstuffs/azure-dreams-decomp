#include "common.h"

typedef struct S_80171F30_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80171F30_0;   /* object in func_80171F30 */

typedef struct S_80171F30_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171F30_1;   /* arg0 in func_80171F30 */

typedef struct S_80171F30_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80171F30_2;   /* data in func_80171F30 */

typedef struct S_80171F30_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80171F30_3;   /* header in func_80171F30 */

typedef struct S_80171F30_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80171F30_4;   /* tail in func_80171F30 */

typedef struct S_80171F30_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171F30_5;   /* ((S_80171F30_0 *)object)->unk_08 in func_80171F30 */

typedef struct S_80171F30_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171F30_6;   /* ((S_80171F30_1 *)arg0)->unk_08 in func_80171F30 */



extern u8 D_80171704[];
extern u8 D_80171CC0[];
extern u8 D_80171D90[];
extern u8 D_80171E60[];

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_80171FAC(void) __attribute__((noreturn));
extern void func_80172074(void) __attribute__((noreturn));

void func_80171F30(S_80171F30_1 *arg0, s32 arg1, s16 arg2_in, s16 arg3_in)
{
    void *object;
    S_80171F30_3 *header;
    register void *call_object ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_global;
    void *tail;
    register s32 dispatch ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s16 mode ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 selector;
    register s16 arg2 ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    s16 arg3;
    s32 alloc_kind;
    void *alloc_source;

    alloc_kind = 0x211;
    alloc_source = arg0;
    arg3 = arg3_in;
    arg2 = arg2_in;
    object = func_8003FD64(alloc_kind, alloc_source);
    if (object == 0) {
        return;
    }

    mode = arg3;
    dispatch = ((s32)arg3) << 16;
    selector = dispatch >> 16;
    dispatch = (s32)0x80170000;
    if (selector == 0) {
        ASM_KEEP(dispatch);   /* MATCH pin: keeps a statement from moving across a call/branch */
        dispatch += 0x1CC0;
        ASM_TAILSLOT_PIN(dispatch);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80171FAC();
    }
    dispatch = 1;
    if (selector == dispatch) {
        dispatch = (s32)0x80170000;
        ASM_KEEP(dispatch);   /* MATCH pin: keeps a statement from moving across a call/branch */
        dispatch += 0x1D90;
        ASM_TAILSLOT_PIN(dispatch);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80171FAC();
    }

    ASM_KEEP(object);   /* MATCH pin: retail basic-block layout depends on it */
    ((S_80171F30_0 *)object)->unk_10 = D_80171E60;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_02 =
        ((S_80171F30_6 *)(arg0->unk_08))->unk_02;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_06 =
        ((S_80171F30_6 *)(arg0->unk_08))->unk_06;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_0A =
        ((S_80171F30_6 *)(arg0->unk_08))->unk_0A;

    ASM_KEEP(mode);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if ((mode << 16) == 0) {
        void *data;
        s32 random;
        s32 coord;

        random = rand();
        data = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)data)->unk_02;
        random &= 7;
        coord -= 4;
        coord += random;
        ((S_80171F30_2 *)data)->unk_02 = coord;
        random = rand();
        data = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)data)->unk_06;
        random &= 7;
        coord -= 4;
        ASM_KEEP(random);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_TAILSLOT_PIN(coord);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80172074();
    }

    ASM_KEEP(mode);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    {
        void *data;
        s32 random;
        s32 coord;

        random = rand();
        data = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)data)->unk_02;
        random &= 0xF;
        coord -= 0xC;
        coord += random;
        ((S_80171F30_2 *)data)->unk_02 = coord;
        random = rand();
        data = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)data)->unk_06;
        random &= 0xF;
        coord -= 0xC;
        coord += random;
        ((S_80171F30_2 *)data)->unk_06 = coord;
        ASM_KEEP(coord);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    }

    call_object = object;
    call_global = D_80171704;
    header = ((S_80171F30_0 *)object)->unk_0C;
    ASM_KEEP(header);   /* MATCH pin: retail schedule: same instructions, different order without it */
    tail = (u8 *)object + 0x20;
    header->unk_06 = 0;
    ((S_80171F30_4 *)tail)->unk_32 = arg2;
    ((S_80171F30_4 *)tail)->unk_34 = arg2;
    func_8004491C(call_object, call_global);
    ((S_80171F30_0 *)object)->unk_20 = arg1;
    ((S_80171F30_4 *)tail)->unk_08 = arg1;
}

/* MECHANISM: Six callee-saved lifetimes give the 0x30 frame; non-volatile keeps
   on pinned allocator args order li/move before s0/s4 saves without blocking
   the jal delay-slot save.  Fixed v0/v1/a0 continuation values plus sanctioned
   tail-slot pins reproduce both dispatch arms and the RNG continuation. */
