/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_8015E8FC(void) __attribute__((noreturn));
extern u8 D_80083160[];


#ifdef __mips__
static const u32 prefix_words[] __asm__("func_80AD7000")
    __attribute__((section(".text.func_80AD7000"), aligned(4))) = {
    0x8015F158, 0x8015F320, 0x8015FB54, 0x8015FB54,
    0x8015FB54, 0x8015FB80, 0x8015FB00, 0x8015FB00,
    0x8015FB00, 0x8015FAAC, 0x8015FAE4, 0x8015FB80,
    0x8015FB80, 0x8015FB44, 0x80161020, 0x80161070,
    0x801610E4, 0x80161158, 0x801611D0, 0x00000000,
    0x8016129C, 0x801614CC, 0x80161514, 0x80161744,
    0x801617CC, 0x00000000, 0x8016134C, 0x80161344,
    0x8016133C, 0x80161354, 0x801612F8, 0x801612F0,
    0x801612E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80AD7000\n"
        ".size func_80AD7000, 644");
#define BODY_NAME func_80AD70A4
#else
#define BODY_NAME func_80AD7000
#endif


typedef struct S_80AD7000_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80AD7000_0;   /* ctx in BODY_NAME */

typedef struct S_80AD7000_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AD7000_1;   /* input in BODY_NAME */

typedef struct S_80AD7000_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80AD7000_2;   /* prim in BODY_NAME */

typedef struct S_80AD7000_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80AD7000_3_pre;   /* the 0x8 bytes before object in BODY_NAME, addressed as object[-1] */

typedef struct S_80AD7000_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80AD7000_3;   /* object in BODY_NAME */

typedef struct S_80AD7000_4 {
    u32 unk_00;
} S_80AD7000_4;   /* prim2 in BODY_NAME */

typedef struct S_80AD7000_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80AD7000_5;   /* node in BODY_NAME */

typedef struct S_80AD7000_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80AD7000_6;   /* *global_slot in BODY_NAME */

/* Queue a projected point and its drawing state, then process the linked object. */
s32 BODY_NAME(void *object_ptr, void *position_ptr) {
    void *object = object_ptr;
    S_80AD7000_1 *position = position_ptr;
    void **context_slot = (void **)D_80083160;
    void *render_ctx = *context_slot;
    u32 address_mask = 0xFF0000;
    u32 length_mask;
    u8 *scratch;
    void *point_prim;
    u32 ot_index;
    void *state_prim;
    void *linked_node;

    ASM_KEEP_NV(object);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP_NV(context_slot);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP_DEP_NV(address_mask, render_ctx);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    address_mask |= 0xFFFF;
    length_mask = 0xFF000000;
    ASM_KEEP_NV(length_mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    (*(void * *)((u8 *)scratch + 0x1C)) = ((S_80AD7000_0 *)render_ctx)->unk_8D0;
    (*(void * *)((u8 *)scratch + 0x24)) = (u8 *)render_ctx + 0xB0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    (*(u16 *)((u8 *)scratch + 4)) = position->unk_02;
    point_prim = (*(void * volatile *)((u8 *)scratch + 0x1C));
    (*(u16 *)((u8 *)scratch + 6)) = position->unk_06;
    (*(u16 *)((u8 *)scratch + 8)) = position->unk_0A;
    (*(void * *)((u8 *)scratch + 0x1C)) = (u8 *)point_prim + 0xC;
    ot_index = func_80065420(scratch + 4, (u8 *)point_prim + 8,
                          scratch + 0xD0, scratch + 0xD4);
    (*(u32 *)((u8 *)scratch + 0x100)) = ot_index;
    if (ot_index < 0x1E0U) {
        ((S_80AD7000_2 *)point_prim)->unk_04.at00.v = ((S_80AD7000_3 *)object)->unk_08;
        ((S_80AD7000_2 *)point_prim)->unk_00.at03.v = 2;
        {
            register u8 red ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
            register u8 green ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
            register u8 blue ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
            red = ((S_80AD7000_2 *)point_prim)->unk_04.at00u.v;
            green = ((S_80AD7000_2 *)point_prim)->unk_04.at01.v;
            blue = ((S_80AD7000_2 *)point_prim)->unk_04.at02.v;
        }
        ((S_80AD7000_2 *)point_prim)->unk_04.at03.v = 0x6A;
        ((S_80AD7000_2 *)point_prim)->unk_00.at00.v =
            (((S_80AD7000_2 *)point_prim)->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & address_mask);
        {
            register u32 *ot_entry ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
            ot_entry = (u32 *)(((*(u32 *)((u8 *)scratch + 0x100)) << 2) +
                              (u32)(*(u32 * *)((u8 *)scratch + 0x24)));
            ASM_KEEP_NV(ot_entry);   /* MATCH pin: load-bearing for the whole function shape */
            {
                register u32 ot_tag ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
                u32 prim_address;
                ot_tag = *ot_entry;
                prim_address = (u32)point_prim & address_mask;
                ot_tag &= length_mask;
                ot_tag |= prim_address;
                *ot_entry = ot_tag;
            }
        }
        state_prim = (*(void * *)((u8 *)scratch + 0x1C));
        (*(void * *)((u8 *)scratch + 0x1C)) = (u8 *)state_prim + 0xC;
        func_80067F20(state_prim, 0, 0,
                      func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        ((S_80AD7000_4 *)state_prim)->unk_00 =
            (((S_80AD7000_4 *)state_prim)->unk_00 & length_mask) |
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & address_mask);
        (*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) =
            ((*(u32 *)((u8 *)((*(u32 * *)((u8 *)scratch + 0x24))) + (*(u32 *)((u8 *)scratch + 0x100)) * 4)) & length_mask) |
            ((u32)state_prim & address_mask);
    }
    linked_node = ((S_80AD7000_3_pre *)object)[-1].unk_00;
    if (linked_node != NULL) {
        register void *scratch_position ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        object = (u8 *)linked_node + 0x20;
        position = ((S_80AD7000_5 *)linked_node)->unk_08;
        ASM_KEEP(object);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(scratch);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        scratch_position = scratch + 4;
        ASM_TAILSLOT_PIN(scratch_position);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8015E8FC();
    }
    {
        register s32 zero ASM_REG("$0");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

#ifdef NON_MATCHING
        zero = 0;
#else
        ASM_SET(zero);   /* MATCH pin: keeps a statement from moving across a call/branch */
#endif
        ((S_80AD7000_6 *)(*context_slot))->unk_8D0 = (*(void * *)((u8 *)scratch + 0x1C));
        result = zero;
        return result;
    }
}
