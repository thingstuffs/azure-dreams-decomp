#include "common.h"

#define SPAD_U16(off) (*(u16 *)(scratch + (off)))
#define SPAD_U32(off) (*(u32 *)(scratch + (off)))

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_801708FC(void) __attribute__((noreturn));
extern void *D_80083160;

typedef void (*Callback)(void);

typedef struct S_80AC50A4_0 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_80AC50A4_0;   /* base in func_80AC50A4 */

typedef struct S_80AC50A4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC50A4_1;   /* input in func_80AC50A4 */

typedef struct S_80AC50A4_2 {
    u8 pad_00[0x1C];
    volatile u32 unk_1C;
} S_80AC50A4_2;   /* scratch in func_80AC50A4 */

typedef struct S_80AC50A4_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80AC50A4_3_pre;   /* the 0x8 bytes before state in func_80AC50A4, addressed as state[-1] */

typedef struct S_80AC50A4_3 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_80AC50A4_3;   /* state in func_80AC50A4 */

typedef struct S_80AC50A4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80AC50A4_4;   /* temp_s0 in func_80AC50A4 */

typedef struct S_80AC50A4_5 {
    u32 unk_00;
} S_80AC50A4_5;   /* temp_s0_2 in func_80AC50A4 */

typedef struct S_80AC50A4_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80AC50A4_6;   /* next in func_80AC50A4 */

typedef struct S_80AC50A4_7 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_80AC50A4_7;   /* *global in func_80AC50A4 */


extern void func_80171158(void);
extern void func_80171320(void);
extern void func_80171B54(void);
extern void func_80171B80(void);
extern void func_80171B00(void);
extern void func_80171AAC(void);
extern void func_80171AE4(void);
extern void func_80171B44(void);
extern void func_80173020(void);
extern void func_80173070(void);
extern void func_801730E4(void);
extern void func_80173158(void);
extern void func_801731D0(void);
extern void func_8017329C(void);
extern void func_801734CC(void);
extern void func_80173514(void);
extern void func_80173744(void);
extern void func_801737CC(void);
extern void func_8017334C(void);
extern void func_80173344(void);
extern void func_8017333C(void);
extern void func_80173354(void);
extern void func_801732F8(void);
extern void func_801732F0(void);
extern void func_801732E8(void);

struct CallbackBlock {
    Callback callbacks[33];
    u32 vectors[8];
};

const struct CallbackBlock func_80AC5000 __attribute__((section(".text.func_80AC5000"))) = {
    {
        func_80171158, func_80171320, func_80171B54, func_80171B54,
        func_80171B54, func_80171B80, func_80171B00, func_80171B00,
        func_80171B00, func_80171AAC, func_80171AE4, func_80171B80,
        func_80171B80, func_80171B44, func_80173020, func_80173070,
        func_801730E4, func_80173158, func_801731D0, 0,
        func_8017329C, func_801734CC, func_80173514, func_80173744,
        func_801737CC, 0, func_8017334C, func_80173344,
        func_8017333C, func_80173354, func_801732F8, func_801732F0,
        func_801732E8
    },
    {
        0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001
    }
};

#ifdef __mips__
__asm__(".size func_80AC5000, 644");
#endif

/* Projects a position and queues a colored tile and draw mode in the ordering table. */
s32 func_80AC50A4(void *render_state, void *coord_data)
{
    u32 *tile_slot;
    u32 *mode_slot;
    u32 depth;
    void *tile_packet;
    void *mode_packet;
    void *render_buffer;
    void *position;
    void *projection_out;
    void *projection_flags;
    u32 initial_cursor;
    register u32 slot_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    register void *state ASM_REG("$19") = render_state;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_80AC50A4_1 *input = coord_data;
    void **render_buffer_ptr;
    u8 *scratch;
    u32 address_mask;
    u32 length_mask;
    void *next_node;

    render_buffer_ptr = &D_80083160;
    address_mask = 0x00FF0000U;
    ASM_KEEP_NV(address_mask);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    render_buffer = D_80083160;
    address_mask |= 0xFFFFU;
    length_mask = 0xFF000000U;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    initial_cursor = ((S_80AC50A4_0 *)render_buffer)->unk_8D0;
    SPAD_U32(0x24) = (u32)render_buffer + 0xB0;
    SPAD_U32(0x1C) = initial_cursor;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    position = scratch + 4;
    ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    projection_out = scratch + 0xD0;
    pos_x = input->unk_02;
    tile_packet = (void *)((S_80AC50A4_2 *)scratch)->unk_1C;
    projection_flags = scratch + 0xD4;
    SPAD_U16(4) = pos_x;
    pos_y = input->unk_06;
    coord_data = (u8 *)tile_packet + 8;
    SPAD_U16(6) = pos_y;
    pos_z = input->unk_0A;
    SPAD_U32(0x1C) = (u32)tile_packet + 0xC;
    SPAD_U16(8) = pos_z;

    depth = func_80065420(position, coord_data, projection_out, projection_flags);
    SPAD_U32(0x100) = depth;
    if (depth < 0x1E0U) {
        s32 rand_zero = 0;
        s32 rand_one = 1;
        u32 color_word;
        register u32 packet_byte ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(rand_zero);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(rand_one);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        color_word = ((S_80AC50A4_3 *)state)->unk_08;
        packet_byte = 2;
        ((S_80AC50A4_4 *)tile_packet)->unk_00.at03.v = packet_byte;
        packet_byte = 0x6A;
        ((S_80AC50A4_4 *)tile_packet)->unk_04.at00.v = color_word;
        {
            u32 red = ((S_80AC50A4_4 *)tile_packet)->unk_04.at00u.v;
            register u32 green ASM_REG("$6") = ((S_80AC50A4_4 *)tile_packet)->unk_04.at01.v;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register u32 blue ASM_REG("$7") = ((S_80AC50A4_4 *)tile_packet)->unk_04.at02.v;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(green);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(blue);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        }
        ((S_80AC50A4_4 *)tile_packet)->unk_04.at03.v = packet_byte;
        ((S_80AC50A4_4 *)tile_packet)->unk_00.at00.v =
            (((S_80AC50A4_4 *)tile_packet)->unk_00.at00.v & length_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & address_mask);
        tile_slot = (u32 *)(SPAD_U32(0x100) * 4 + SPAD_U32(0x24));
        slot_word = *tile_slot;
        *tile_slot = (slot_word & length_mask) | ((u32)tile_packet & address_mask);

        mode_packet = (void *)SPAD_U32(0x1C);
        SPAD_U32(0x1C) = (u32)mode_packet + 0xC;
        func_80067F20(mode_packet, 0, 0,
                      func_80066460(rand_zero, rand_one,
                                    rand_zero, rand_zero) & 0xFFFF, 0);
        ((S_80AC50A4_5 *)mode_packet)->unk_00 =
            (((S_80AC50A4_5 *)mode_packet)->unk_00 & length_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & address_mask);
        mode_slot = (u32 *)(SPAD_U32(0x100) * 4 + SPAD_U32(0x24));
        *mode_slot = (*mode_slot & length_mask) | ((u32)mode_packet & address_mask);
        ASM_KEEP(length_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }

    next_node = ((S_80AC50A4_3_pre *)state)[-1].unk_00;
    if (next_node != 0) {
        register void *next_position ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = (u8 *)next_node + 0x20;
        input = ((S_80AC50A4_6 *)next_node)->unk_08;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        next_position = scratch + 4;
        ASM_TAILSLOT_PIN(next_position);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801708FC();
    }
    ASM_KEEP(render_buffer_ptr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_80AC50A4_7 *)(*render_buffer_ptr))->unk_8D0 = SPAD_U32(0x1C);
    return 0;
}
