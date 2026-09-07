/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef struct S_80ACB000_0 {
    void * unk_00;
} S_80ACB000_0;   /* &D_80083160 in BODY_NAME */

typedef struct S_80ACB000_1 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_80ACB000_1;   /* base in BODY_NAME */

typedef struct S_80ACB000_2 {
    u8 pad_00[0x1C];
    volatile u32 unk_1C;
} S_80ACB000_2;   /* scratch in BODY_NAME */

typedef struct S_80ACB000_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80ACB000_3;   /* arg1_reg in BODY_NAME */

typedef struct S_80ACB000_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80ACB000_4_pre;   /* the 0x8 bytes before arg0_reg in BODY_NAME, addressed as arg0_reg[-1] */

typedef struct S_80ACB000_4 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_80ACB000_4;   /* arg0_reg in BODY_NAME */

typedef struct S_80ACB000_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80ACB000_5;   /* temp_s0 in BODY_NAME */

typedef struct S_80ACB000_6 {
    u32 unk_00;
} S_80ACB000_6;   /* temp_s0_2 in BODY_NAME */

typedef struct S_80ACB000_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80ACB000_7;   /* next in BODY_NAME */

typedef struct S_80ACB000_8 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_80ACB000_8;   /* final_base in BODY_NAME */


#define SPAD_U16(off) (*(u16 *)(scratch + (off)))
#define SPAD_U32(off) (*(u32 *)(scratch + (off)))

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_8016A8FC(void) __attribute__((noreturn));
extern void *D_80083160;

#ifdef __mips__
/* The row starts with a typed constant/jump table; the routine follows it. */
static const u32 func_80ACB000_table[41]
    __asm__("func_80ACB000")
    __attribute__((section(".text.func_80ACB000"), aligned(4))) = {
    0x8016B158U, 0x8016B320U, 0x8016BB54U, 0x8016BB54U,
    0x8016BB54U, 0x8016BB80U, 0x8016BB00U, 0x8016BB00U,
    0x8016BB00U, 0x8016BAACU, 0x8016BAE4U, 0x8016BB80U,
    0x8016BB80U, 0x8016BB44U, 0x8016D020U, 0x8016D070U,
    0x8016D0E4U, 0x8016D158U, 0x8016D1D0U, 0x00000000U,
    0x8016D29CU, 0x8016D4CCU, 0x8016D514U, 0x8016D744U,
    0x8016D7CCU, 0x00000000U, 0x8016D34CU, 0x8016D344U,
    0x8016D33CU, 0x8016D354U, 0x8016D2F8U, 0x8016D2F0U,
    0x8016D2E8U, 0x00000001U, 0x00010001U, 0x00010000U,
    0x0001FFFFU, 0x0000FFFFU, 0xFFFFFFFFU, 0xFFFF0000U,
    0xFFFF0001U,
};
__asm__(".globl func_80ACB000\n"
        ".type func_80ACB000,@function\n"
        ".size func_80ACB000, 644");
#define BODY_NAME composite_body_80ACB000
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80ACB000")))
#else
#define BODY_NAME func_80ACB000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *render_data_in, void *position_in) BODY_ATTR;
/* Projects a point and queues its tile and draw mode in the ordering table. */
BODY_STORAGE s32 BODY_NAME(void *render_data_in, void *position_in)
{
    u32 initial_cursor;
    u32 final_cursor;
    u32 depth;
    S_80ACB000_8 *final_state;
    void *tile;
    void *draw_mode;
    void *next_node;
    register void *render_data ASM_REG("$19") = render_data_in;   /* MATCH pin: retail address form (%hi/%lo vs render_state+offset) depends on it */
    register void *position = position_in;
    void **render_state_ptr = &D_80083160;
    u32 address_mask = 0x00FFFFFFU;
    void *render_state = ((S_80ACB000_0 *)(&D_80083160))->unk_00;
    register u32 length_mask ASM_REG("$20") = 0xFF000000U;   /* MATCH pin: load-bearing for the whole function shape */
    u8 *scratch = (u8 *)0x1F800000;
    register s32 result ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    ASM_KEEP(render_state_ptr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(length_mask);   /* MATCH pin: retail schedule: same instructions, different order without it */

    initial_cursor = ((S_80ACB000_1 *)render_state)->unk_8D0;
    SPAD_U32(0x24) = (u32)render_state + 0xB0;
    ((S_80ACB000_2 *)scratch)->unk_1C = initial_cursor;
    ASM_KEEP(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    SPAD_U16(4) = ((S_80ACB000_3 *)position)->unk_02;
    tile = (void *)((S_80ACB000_2 *)scratch)->unk_1C;
    SPAD_U16(6) = ((S_80ACB000_3 *)position)->unk_06;
    SPAD_U16(8) = ((S_80ACB000_3 *)position)->unk_0A;
    SPAD_U32(0x1C) = (u32)tile + 0xC;

    depth = func_80065420(scratch + 4, (u8 *)tile + 8,
                            scratch + 0xD0, scratch + 0xD4);
    ASM_KEEP(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    SPAD_U32(0x100) = depth;
    if (depth < 0x1E0U) {
        register s32 call_zero ASM_REG("$4") = 0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 call_one = 1;
        u32 color = ((S_80ACB000_4 *)render_data)->unk_08;
        register u32 packet_code ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(call_one);   /* MATCH pin: retail schedule: same instructions, different order without it */
        packet_code = 2;
        ((S_80ACB000_5 *)tile)->unk_00.at03.v = packet_code;
        packet_code = 0x6A;
        ((S_80ACB000_5 *)tile)->unk_04.at00.v = color;
        {
            u32 red = ((S_80ACB000_5 *)tile)->unk_04.at00u.v;
            register u32 green ASM_REG("$6") = ((S_80ACB000_5 *)tile)->unk_04.at01.v;   /* MATCH pin: keeps a statement from moving across a call/branch */
            register u32 blue ASM_REG("$7") = ((S_80ACB000_5 *)tile)->unk_04.at02.v;   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_KEEP(green);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_KEEP(blue);   /* MATCH pin: retail register colouring depends on it */
        }
        ((S_80ACB000_5 *)tile)->unk_04.at03.v = packet_code;
        ((S_80ACB000_5 *)tile)->unk_00.at00.v =
            (((S_80ACB000_5 *)tile)->unk_00.at00.v & length_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & address_mask);
        {
            u32 *ot_entry;
            register u32 ot_tag ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            u32 tile_address;

            ot_entry = (u32 *)(SPAD_U32(0x100) << 2);
            ot_entry = (u32 *)((u32)ot_entry + SPAD_U32(0x24));
            ot_tag = *ot_entry;
            tile_address = (u32)tile & address_mask;
            ot_tag &= length_mask;
            ot_tag |= tile_address;
            *ot_entry = ot_tag;
        }

        draw_mode = (void *)SPAD_U32(0x1C);
        SPAD_U32(0x1C) = (u32)draw_mode + 0xC;
        func_80067F20(draw_mode, 0, 0,
                      func_80066460(call_zero, call_one, call_zero, call_zero) & 0xFFFF, 0);
        ((S_80ACB000_6 *)draw_mode)->unk_00 =
            (((S_80ACB000_6 *)draw_mode)->unk_00 & length_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & address_mask);
        {
            u32 *ot_entry;

            ot_entry = (u32 *)(SPAD_U32(0x100) << 2);
            ot_entry = (u32 *)((u32)ot_entry + SPAD_U32(0x24));
            *ot_entry = (*ot_entry & length_mask) | ((u32)draw_mode & address_mask);
        }
    }

    next_node = ((S_80ACB000_4_pre *)render_data)[-1].unk_00;
    if (next_node != 0) {
        register void *scratch_position ASM_REG("$4") = scratch + 4;   /* MATCH pin: retail schedule: same instructions, different order without it */

        render_data = (u8 *)next_node + 0x20;
        position = ((S_80ACB000_7 *)next_node)->unk_08;
        ASM_KEEP(render_data);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_KEEP(position);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_TAILSLOT_PIN(scratch_position);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8016A8FC();
    }
    final_state = *render_state_ptr;
    final_cursor = SPAD_U32(0x1C);
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    result = 0;
    ASM_KEEP(result);   /* MATCH pin: retail schedule: same instructions, different order without it */
    final_state->unk_8D0 = final_cursor;
    return result;
}
