/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_801588FC(void) __attribute__((noreturn));
extern u8 D_80083160[];


#ifdef __mips__
static const u32 bank_words[] __asm__("func_80ADD000")
    __attribute__((section(".text.func_80ADD000"), aligned(4))) = {
    0x80159158, 0x80159320, 0x80159B54, 0x80159B54,
    0x80159B54, 0x80159B80, 0x80159B00, 0x80159B00,
    0x80159B00, 0x80159AAC, 0x80159AE4, 0x80159B80,
    0x80159B80, 0x80159B44, 0x8015B020, 0x8015B070,
    0x8015B0E4, 0x8015B158, 0x8015B1D0, 0x00000000,
    0x8015B29C, 0x8015B4CC, 0x8015B514, 0x8015B744,
    0x8015B7CC, 0x00000000, 0x8015B34C, 0x8015B344,
    0x8015B33C, 0x8015B354, 0x8015B2F8, 0x8015B2F0,
    0x8015B2E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80ADD000\n"
        ".size func_80ADD000, 644");
#define BODY_NAME func_80ADD0A4
#else
#define BODY_NAME func_80ADD000
#endif


typedef struct S_80ADD000_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80ADD000_0;   /* ctx in BODY_NAME */

typedef struct S_80ADD000_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80ADD000_1;   /* input in BODY_NAME */

typedef struct S_80ADD000_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80ADD000_2;   /* prim in BODY_NAME */

typedef struct S_80ADD000_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80ADD000_3_pre;   /* the 0x8 bytes before object in BODY_NAME, addressed as object[-1] */

typedef struct S_80ADD000_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80ADD000_3;   /* object in BODY_NAME */

typedef struct S_80ADD000_4 {
    u32 unk_00;
} S_80ADD000_4;   /* prim2 in BODY_NAME */

typedef struct S_80ADD000_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80ADD000_5;   /* node in BODY_NAME */

typedef struct S_80ADD000_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80ADD000_6;   /* *global_slot in BODY_NAME */

s32 BODY_NAME(void *arg0, void *arg1) {
    void *object = arg0;
    S_80ADD000_1 *input = arg1;
    void **global_slot = (void **)D_80083160;
    void *ctx = *global_slot;
    u32 low_mask = 0xFF0000;
    u32 high_mask;
    u8 *scratch;
    void *prim;
    u32 index;
    void *prim2;
    void *node;

    ASM_KEEP_NV(object);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(global_slot);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(low_mask, ctx);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    low_mask |= 0xFFFF;
    high_mask = 0xFF000000;
    ASM_KEEP_NV(high_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    (*(void * *)((u8 *)scratch + 0x1C)) = ((S_80ADD000_0 *)ctx)->unk_8D0;
    (*(void * *)((u8 *)scratch + 0x24)) = (u8 *)ctx + 0xB0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    (*(u16 *)((u8 *)scratch + 4)) = input->unk_02;
    prim = (*(void * volatile *)((u8 *)scratch + 0x1C));
    (*(u16 *)((u8 *)scratch + 6)) = input->unk_06;
    (*(u16 *)((u8 *)scratch + 8)) = input->unk_0A;
    (*(void * *)((u8 *)scratch + 0x1C)) = (u8 *)prim + 0xC;
    index = func_80065420(scratch + 4, (u8 *)prim + 8,
                          scratch + 0xD0, scratch + 0xD4);
    (*(u32 *)((u8 *)scratch + 0x100)) = index;
    if (index < 0x1E0U) {
        ((S_80ADD000_2 *)prim)->unk_04.at00.v = ((S_80ADD000_3 *)object)->unk_08;
        ((S_80ADD000_2 *)prim)->unk_00.at03.v = 2;
        {
            register u8 dead_read0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register u8 dead_read1 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register u8 dead_read2 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            dead_read0 = ((S_80ADD000_2 *)prim)->unk_04.at00u.v;
            dead_read1 = ((S_80ADD000_2 *)prim)->unk_04.at01.v;
            dead_read2 = ((S_80ADD000_2 *)prim)->unk_04.at02.v;
        }
        ((S_80ADD000_2 *)prim)->unk_04.at03.v = 0x6A;
        ((S_80ADD000_2 *)prim)->unk_00.at00.v =
            (((S_80ADD000_2 *)prim)->unk_00.at00.v & high_mask) |
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & low_mask);
        {
            register u32 *rmw_ptr ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            rmw_ptr = (u32 *)(((*(u32 *)((u8 *)scratch + 0x100)) << 2) +
                              (u32)(*(u32 * *)((u8 *)scratch + 0x24)));
            ASM_KEEP_NV(rmw_ptr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            {
                register u32 rmw_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                u32 prim_low;
                rmw_value = *rmw_ptr;
                prim_low = (u32)prim & low_mask;
                rmw_value &= high_mask;
                rmw_value |= prim_low;
                *rmw_ptr = rmw_value;
            }
        }
        prim2 = (*(void * *)((u8 *)scratch + 0x1C));
        (*(void * *)((u8 *)scratch + 0x1C)) = (u8 *)prim2 + 0xC;
        func_80067F20(prim2, 0, 0,
                      func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        ((S_80ADD000_4 *)prim2)->unk_00 =
            (((S_80ADD000_4 *)prim2)->unk_00 & high_mask) |
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & low_mask);
        (*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) =
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & high_mask) |
            ((u32)prim2 & low_mask);
    }
    node = ((S_80ADD000_3_pre *)object)[-1].unk_00;
    if (node != NULL) {
        register void *tail_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        object = (u8 *)node + 0x20;
        input = ((S_80ADD000_5 *)node)->unk_08;
        ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        tail_arg0 = scratch + 4;
        ASM_TAILSLOT_PIN(tail_arg0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801588FC();
    }
    {
        register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

#ifdef NON_MATCHING
        hard_zero = 0;
#else
        ASM_SET(hard_zero);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#endif
        ((S_80ADD000_6 *)(*global_slot))->unk_8D0 = (*(void * *)((u8 *)scratch + 0x1C));
        result = hard_zero;
        return result;
    }
}
