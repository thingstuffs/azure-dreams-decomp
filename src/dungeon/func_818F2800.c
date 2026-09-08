#include "common.h"

typedef struct S_BODY_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_BODY_0;   /* gv in BODY */

typedef struct S_BODY_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_BODY_1;   /* state in BODY */

typedef struct S_BODY_2 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union { struct { u8 v; } at00; struct { void * v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
} S_BODY_2;   /* sp in BODY */

typedef struct S_BODY_3 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
} S_BODY_3;   /* root in BODY */

typedef struct S_BODY_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_BODY_4;   /* sq in BODY */

typedef struct S_BODY_5 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x6];
    s16 unk_28;
    u8 pad_2A[0x6];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_BODY_5;   /* rp in BODY */

typedef struct S_BODY_6 {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x6];
    u16 unk_28;
    u8 pad_2A[0x6];
    u16 unk_30;
    u8 pad_32[0x6];
    u16 unk_38;
} S_BODY_6;   /* q in BODY */

typedef struct S_BODY_7_pre {
    s8 unk_00;
} S_BODY_7_pre;   /* the 0x1 bytes before ent in BODY, addressed as ent[-1] */

typedef struct S_BODY_7 {
    s32 unk_00;
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
    union { struct { s16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
} S_BODY_7;   /* ent in BODY */

typedef struct S_BODY_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_BODY_8;   /* gp[0] in BODY */



#define DM_U8(o)  (*(u8  *)(scratch + (o)))
#define DM_S8(o)  (*(s8  *)(scratch + (o)))
#define DM_U16(o) (*(u16 *)(scratch + (o)))
#define DM_S16(o) (*(s16 *)(scratch + (o)))
#define DM_U32(o) (*(u32 *)(scratch + (o)))
#define DM_S32(o) (*(s32 *)(scratch + (o)))

extern void func_80024248(void) __attribute__((noreturn));
extern void func_8002431C(void) __attribute__((noreturn));
extern void func_800243E4(void) __attribute__((noreturn));
extern void func_80024650(void) __attribute__((noreturn));
extern void func_800246A0(void) __attribute__((noreturn));
extern void func_80024838(void) __attribute__((noreturn));

extern s32 func_800644B8(s32);
extern void func_80064840();
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0();
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065590();
extern void func_80065820();

typedef struct {
    u8 pad[0x3160];
    u8 *table[3];
} GlobalPage;

extern GlobalPage D_80080000;
__asm__(".set D_80080000, 0x80080000");

extern void *D_80083160[];

#ifdef __mips__
extern void func_80024FA4(void);
extern void func_80025090(void);
extern void func_80025150(void);
extern void func_80025418(void);
extern void func_80025798(void);
extern void func_800257CC(void);
extern void func_80025874(void);
extern void func_800258B0(void);
extern void func_80025948(void);
extern void func_800258E4(void);

/* The carved retail range starts with ten words of local table data followed
 * by nine callback addresses, immediately ahead of the executable body. */
static const u32 func_818F2800_prefix[]
    __asm__("func_818F2800")
    __attribute__((section(".text.func_818F2800"), aligned(4))) = {
    (u32)func_80024FA4,
    0x00000020, 0x00200020, 0x00200000, 0x0020FFE0,
    0x0000FFE0, 0xFFE0FFE0, 0xFFE00000, 0xFFE00020, 0x00000000,
};

static void (*const func_818F2800_table[])(void)
    __attribute__((section(".text.func_818F2800"), aligned(4))) = {
    func_80025090, func_80025150, func_80025418,
    func_80025798, func_800257CC, func_80025874,
    func_800258B0, func_80025948, func_800258E4,
};
#endif

#ifdef __mips__
#define BODY func_818F284C
#define BODY_SECTION __attribute__((section(".text.func_818F2800")))
#else
#define BODY func_818F2800
#define BODY_SECTION
#endif

void BODY(void *shape, void *position, void *render_state, u16 depth_offset) BODY_SECTION;
/* Builds textured quad strips and adds visible quads to the ordering table. */
void BODY(void *shape, void *position, void *render_state, u16 depth_offset)
{
    register u8 *scratch ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_BODY_3 *geometry;
    S_BODY_1 *state;
    u8 *part;
    u8 *quad;
    register u8 *packet ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 angle;
    register s32 half ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 strip_x ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 invalid_coord;
    s32 transform_buf[16];
    u16 depth_bias;
    u16 end_column;
    u16 column;
    s32 texture_u;
    u8 *edge_cache;
    void *graphics;
    register u8 *cached_edge ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register GlobalPage *global_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 column_or_x;
    s32 packed_uv;
    s32 texture_value;
    s32 first_column;
    void **globals;
    s32 position_z;

    geometry = shape;
    globals = D_80083160;
    global_page = &D_80080000;
    graphics = global_page->table[0];
    scratch = (u8 *)0x1F800000;

    ASM_KEEP_NV(geometry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    DM_U32(0x20) = (u32)((u8 *)graphics + 0xB0);
    DM_S32(0xE4) = *(s16 *)((u8 *)position + 2);
    state = render_state;
    DM_S32(0xE8) = *(s16 *)((u8 *)position + 6);
    position_z = *(s16 *)((u8 *)position + 0xA);
    ASM_USE(position_z);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    edge_cache = (u8 *)&transform_buf[0];
    ASM_KEEP_NV(edge_cache);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    DM_S32(0xEC) = position_z;
    packet = ((S_BODY_0 *)graphics)->unk_8D0;
    state->unk_14 = (u16)(state->unk_14 | 0x8000);
    depth_bias = depth_offset;
    func_800649A0();
    DM_U32(0x30) = state->unk_1C * 2;
    DM_U32(0x34) = state->unk_1E * 2;
    DM_U32(0x38) = 0x2000;
    DM_U16(0x100) = state->unk_16;
    DM_U16(0x104) = state->unk_1A;
    DM_U16(0x102) = state->unk_18;
    func_80065820(0x1F800100, 0x1F8000D0);
    func_80064AE0(&transform_buf[0]);
    func_80064840(&transform_buf[0], 0x1F8000D0, 0x1F800050);
    func_80064BC0(0x1F800050, 0x1F800030);
    func_80064D80(0x1F800050);
    func_80064CF0(0x1F800050);
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        s32 init_flags;
        part = state->unk_08;
        init_flags = state->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        invalid_coord = 0x7D00;
        DM_U16(0x24) = (u16)init_flags;
    }

next_part:
    half = 0;
    if (!(((S_BODY_2 *)part)->unk_00 & 0x20)) {
        register u8 *cache_cursor ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        u8 *first_part;
        s32 start_x;

        cache_cursor = edge_cache;
        angle = geometry->unk_3A;
        first_column = ((S_BODY_2 *)part)->unk_08.at00.v;
        texture_value = first_column + ((S_BODY_2 *)part)->unk_08.at02.v;
        first_part = state->unk_08;
        end_column = (u16)texture_value;
        start_x = ((S_BODY_4 *)first_part)->unk_02;
        column = (u16)first_column;
        {
            register s32 signed_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            signed_x = start_x << 24;
            ASM_KEEP_NV(signed_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            strip_x = signed_x >> 24;
        }
        do {
            ((S_BODY_5 *)cache_cursor)->unk_38 = (s16)invalid_coord;
            ((S_BODY_5 *)cache_cursor)->unk_30 = (s16)invalid_coord;
            ((S_BODY_5 *)cache_cursor)->unk_28 = (s16)invalid_coord;
            ((S_BODY_5 *)cache_cursor)->unk_20 = (s16)invalid_coord;
            ASM_KEEP_NV(invalid_coord);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            half += 1;
            cache_cursor += 2;
        } while (half < 2);

next_column_pair:
        half = 0;
        column_or_x = column;
        quad = packet + 4;
        texture_u = (s32)(s16)column_or_x;
next_half:
        part = state->unk_08;
        ASM_USE_G_NV(globals);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE_G_NV(position);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(geometry, geometry);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        if (half == 0) {
            s32 texture_v;
            DM_U32(0x08) = texture_u;
            texture_v = ((S_BODY_2 *)part)->unk_08.at01.v;
            DM_U32(0x10) = 1;
            DM_U32(0x0C) = texture_v;
            func_80024248();
        }
        {
            s32 texture_v;
            register s32 half_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            DM_U32(0x08) = texture_u;
            texture_v = ((S_BODY_2 *)part)->unk_08.at01.v;
            half_height = ((S_BODY_2 *)part)->unk_08.at03.v;
            DM_U32(0x10) = 1;
            half_height = (u32)half_height >> 1;
            texture_v = texture_v + half_height;
            DM_U32(0x0C) = texture_v;
        }
        /* --- shared tail of the two arms (retail word 146) --- */
        {
            s32 half_height;
            half_height = (u32)((S_BODY_2 *)part)->unk_08.at03.v >> 1;
            DM_U32(0x14) = half_height;
        }
        ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        {
            s32 left_z;
            left_z = (func_800644B8(angle) * geometry->unk_38) >> 0x10;
            DM_S16(0x84) = (s16)left_z;
            DM_S16(0x74) = (s16)left_z;
        }
        {
            s32 angle_step;
            angle_step = geometry->unk_3C;
            angle += angle_step;
        }
        if (angle >= 0x1001) {
            angle -= 0x1000;
        }
        {
            s32 right_z;
            right_z = (func_800644B8(angle) * geometry->unk_38) >> 0x10;
            DM_S16(0x8C) = (s16)right_z;
            DM_S16(0x7C) = (s16)right_z;
        }
        {
            s32 angle_step;
            angle_step = geometry->unk_3C;
            angle -= angle_step;
        }
        if (angle < 0) {
            angle += 0x1000;
        }
        ASM_KEEP_NV(invalid_coord);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(invalid_coord);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        {
            s32 edge_x;
            if ((((S_BODY_2 *)part)->unk_00 ^ DM_U16(0x24)) & 1) {
                s32 left_x, width;
                left_x = -strip_x;
                width = DM_U16(0x10);
                DM_S16(0x80) = (s16)left_x;
                DM_S16(0x70) = (s16)left_x;
                ASM_USE(strip_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                edge_x = left_x - width;
                ASM_TAILSLOT_PIN_TIED(edge_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_8002431C();
            }
            {
                s32 width;
                width = DM_U16(0x10);
                DM_S16(0x80) = (s16)strip_x;
                DM_S16(0x70) = (s16)strip_x;
                edge_x = strip_x + width;
            }
            DM_S16(0x88) = (s16)edge_x;
            DM_S16(0x78) = (s16)edge_x;
        }
        ASM_KEEP_NV(half);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
            s32 part_flags;
            register s32 state_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 flip_flags;
            part_flags = ((S_BODY_2 *)part)->unk_00;
            ASM_USE(part_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            state_flags = *(volatile u16 *)(scratch + 0x24);
            flip_flags = part_flags;
            ASM_KEEP(flip_flags);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            flip_flags ^= state_flags;
            if (flip_flags & 2) {
                if (half == 0) {
                    s32 edge_y, height;
                    edge_y = ((S_BODY_2 *)part)->unk_03;
                    ASM_USE_NV(edge_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    height = DM_U16(0x14);
                    edge_y = -(s32)(s8)edge_y;
                    DM_S16(0x7A) = (s16)edge_y;
                    DM_S16(0x72) = (s16)edge_y;
                    edge_y = edge_y - height;
                    ASM_TAILSLOT_PIN_TIED(edge_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_800243E4();
                }
                {
                    s32 edge_y, height;
                    register s32 next_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    edge_y = ((S_BODY_2 *)part)->unk_03;
                    ASM_USE_NV(edge_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    height = DM_U16(0x14);
                    edge_y = -(s32)(s8)edge_y;
                    next_height = height;
                    ASM_KEEP_NV(next_height);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    edge_y = edge_y - height;
                    DM_S16(0x7A) = (s16)edge_y;
                    DM_S16(0x72) = (s16)edge_y;
                    edge_y = edge_y - next_height;
                    ASM_TAILSLOT_PIN_TIED(edge_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_800243E4();
                }
            }
        }
        if (half == 0) {
            s32 edge_y, height;
            edge_y = ((S_BODY_2 *)part)->unk_03;
            ASM_USE_NV(edge_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            height = DM_U16(0x14);
            edge_y = (s8)edge_y;
            DM_S16(0x7A) = (s16)edge_y;
            DM_S16(0x72) = (s16)edge_y;
            edge_y = edge_y + height;
            ASM_TAILSLOT_PIN_TIED(edge_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_800243E4();
        }
        {
            s32 edge_y, height;
            register s32 next_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            edge_y = ((S_BODY_2 *)part)->unk_03;
            ASM_USE_NV(edge_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            height = DM_U16(0x14);
            edge_y = (s8)edge_y;
            next_height = height;
            ASM_KEEP_NV(next_height);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            edge_y = edge_y + height;
            DM_S16(0x7A) = (s16)edge_y;
            DM_S16(0x72) = (s16)edge_y;
            edge_y = edge_y + next_height;
            DM_S16(0x8A) = (s16)edge_y;
            DM_S16(0x82) = (s16)edge_y;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        DM_S32(0xC0) = (func_80065590(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88,
                                      packet + 8, packet + 0x10, packet + 0x18, packet + 0x20,
                                      scratch + 0x90, scratch + 0x94)
                        - (s32)(s16)depth_bias) - 6;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            offset = half * 2;
            cached_edge = (u8 *)(offset + (s32)edge_cache);
        }
        if (((S_BODY_6 *)cached_edge)->unk_20.s != invalid_coord) {
            ((S_BODY_7 *)quad)->unk_04.u = ((S_BODY_6 *)cached_edge)->unk_20.u;
            ((S_BODY_7 *)quad)->unk_06.u = ((S_BODY_6 *)cached_edge)->unk_30;
            ((S_BODY_7 *)quad)->unk_14 = ((S_BODY_6 *)cached_edge)->unk_28;
            ((S_BODY_7 *)quad)->unk_16 = ((S_BODY_6 *)cached_edge)->unk_38;
        }
        ((S_BODY_6 *)cached_edge)->unk_20.u = ((S_BODY_7 *)quad)->unk_0C;
        ((S_BODY_6 *)cached_edge)->unk_28 = ((S_BODY_7 *)quad)->unk_1C.u;
        ((S_BODY_6 *)cached_edge)->unk_30 = ((S_BODY_7 *)quad)->unk_0E;
        ((S_BODY_6 *)cached_edge)->unk_38 = ((S_BODY_7 *)quad)->unk_1E.u;
        if ((u32)DM_S32(0xC0) < 0x1E0U) {
            s32 top_visible, three_visible, visible0, visible1, visible2, visible3;
            visible0 = 0;
            if ((u32)((((S_BODY_7 *)quad)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                s32 screen_y;
                screen_y = (((S_BODY_7 *)quad)->unk_06.u + 0x20) & 0xFFFF;
                visible0 = (u32)screen_y < 0x121U;
            }
            visible1 = 0;
            if ((u32)((((S_BODY_7 *)quad)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                s32 screen_y;
                screen_y = (((S_BODY_7 *)quad)->unk_0E + 0x20) & 0xFFFF;
                visible1 = (u32)screen_y < 0x121U;
            }
            visible2 = 0;
            top_visible = visible0 | visible1;
            if ((u32)((((S_BODY_7 *)quad)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                s32 screen_y;
                screen_y = (((S_BODY_7 *)quad)->unk_16 + 0x20) & 0xFFFF;
                visible2 = (u32)screen_y < 0x121U;
            }
            visible3 = 0;
            three_visible = top_visible | visible2;
            if ((u32)((((S_BODY_7 *)quad)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                s32 screen_y;
                screen_y = (((S_BODY_7 *)quad)->unk_1E.u + 0x20) & 0xFFFF;
                visible3 = (u32)screen_y < 0x121U;
            }
            if ((three_visible | visible3) != 0) {
                ((S_BODY_7_pre *)quad)[-1].unk_00 = 9;
                state->unk_14 = (u16)(state->unk_14 & 0x7FFF);
                {
                    s32 right_u, bottom_v;
                    right_u = DM_U32(0x10) + DM_U32(0x08);
                    DM_U32(0x10) = right_u;
                    if (right_u & 0x100) {
                        DM_U32(0x10) = right_u - 1;
                    }
                    bottom_v = DM_U32(0x14) + DM_U32(0x0C);
                    DM_U32(0x14) = bottom_v;
                    if (bottom_v & 0x100) {
                        DM_U32(0x14) = bottom_v - 1;
                    }
                }
                DM_U32(0x0C) <<= 8;
                DM_U32(0x14) <<= 8;
                if (DM_U16(0x24) & 0x100) {
                    s32 clut;
                    clut = state->unk_12;
                    ((S_BODY_7 *)quad)->unk_0A = (s16)clut;
                    func_80024650();
                }
                packed_uv = state->unk_12;
                packed_uv = packed_uv + ((S_BODY_2 *)part)->unk_06;
                ((S_BODY_7 *)quad)->unk_0A = (s16)packed_uv;
                /* --- retail word 404 --- */
                packed_uv = DM_U16(0x0C);
                packed_uv = packed_uv + DM_U16(0x08);
                ((S_BODY_7 *)quad)->unk_08 = (s16)packed_uv;
                packed_uv = DM_U16(0x0C);
                packed_uv = packed_uv + DM_U16(0x10);
                ((S_BODY_7 *)quad)->unk_10.s16 = (s16)packed_uv;
                {
                    s32 page_override, texture_page;
                    page_override = state->unk_10;
                    if (page_override != 0) {
                        s32 page_sum;
                        texture_page = ((S_BODY_2 *)part)->unk_04 & 0xFF9F;
                        page_sum = page_override + texture_page;
                        ASM_TAILSLOT_PIN_TIED(page_sum);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        func_800246A0();
                    }
                    texture_page = ((S_BODY_2 *)part)->unk_04;
                    /* --- retail word 424 --- */
                    ((S_BODY_7 *)quad)->unk_12 = (u16)texture_page;
                }
                packed_uv = DM_U16(0x14);
                packed_uv = packed_uv + DM_U16(0x08);
                ((S_BODY_7 *)quad)->unk_18.at00.v = (s16)packed_uv;
                packed_uv = DM_U16(0x14);
                texture_value = DM_U16(0x10);
                column_or_x = ((S_BODY_7 *)quad)->unk_04.s;
                packed_uv = packed_uv + texture_value;
                ((S_BODY_7 *)quad)->unk_20.at00.v = (s16)packed_uv;
                if ((s32)((S_BODY_7 *)quad)->unk_1C.s < column_or_x) {
                    u8 edge_uv, corner_uv;
                    edge_uv = ((S_BODY_7 *)quad)->unk_10.u8;
                    corner_uv = ((S_BODY_7 *)quad)->unk_20.at00u.v;
                    edge_uv = (u8)(edge_uv - 1);
                    corner_uv = (u8)(corner_uv - 1);
                    ((S_BODY_7 *)quad)->unk_10.u8 = edge_uv;
                    ((S_BODY_7 *)quad)->unk_20.at00u.v = corner_uv;
                }
                {
                    s32 top_y;
                    top_y = ((S_BODY_7 *)quad)->unk_06.s;
                    if ((s32)((S_BODY_7 *)quad)->unk_1E.s < top_y) {
                        u8 edge_uv, corner_uv;
                        edge_uv = ((S_BODY_7 *)quad)->unk_18.at01.v;
                        corner_uv = ((S_BODY_7 *)quad)->unk_20.at01.v;
                        edge_uv = (u8)(edge_uv - 1);
                        corner_uv = (u8)(corner_uv - 1);
                        ((S_BODY_7 *)quad)->unk_18.at01.v = edge_uv;
                        ((S_BODY_7 *)quad)->unk_20.at01.v = corner_uv;
                    }
                }
                texture_value = ((S_BODY_2 *)part)->unk_01;
                state->unk_0C.at03.v = (u8)texture_value;
                {
                    s32 render_flags;
                    render_flags = DM_U16(0x24);
                    if (render_flags & 8) {
                        if (render_flags & 4) {
                            s32 blend_command;
                            blend_command = texture_value | 2;
                            state->unk_0C.at03.v = (u8)blend_command;
                        } else {
                            s32 opaque_command;
                            opaque_command = texture_value & 0xFD;
                            state->unk_0C.at03.v = (u8)opaque_command;
                        }
                    }
                }
                ((S_BODY_7 *)quad)->unk_00 = state->unk_0C.at00.v;
                quad += 0x28;
                *(u32 *)packet = (*(u32 *)packet & 0xFF000000)
                             | (((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] & 0xFFFFFF);
                ((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] =
                    (((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] & 0xFF000000)
                    | ((s32)packet & 0xFFFFFF);
                packet += 0x28;
            }
        }
        half += 1;
        if (half < 2) {
            goto next_half;
        }
        {
            s32 angle_step;
            angle_step = geometry->unk_3C;
            angle += angle_step;
        }
        if (angle >= 0x1001) {
            angle -= 0x1000;
        }
        column = (u16)(column + 1);
        {
            s32 next_column;
            next_column = (s32)(s16)column;
            strip_x += 1;
            if (next_column != (s32)end_column) {
                goto next_column_pair;
            }
        }
        func_80024838();
    }
    {
        void (*callback)(void *, void *, void *, void *);

        callback = ((S_BODY_2 *)part)->unk_08.at00u.v;
        if (callback != 0) {
            callback(geometry, position, state, part);
        }
    }
    {
        s32 part_flags;
        part_flags = (s8)((S_BODY_2 *)part)->unk_00;
        part += 0xC;
        if (part_flags >= 0) {
            goto next_part;
        }
    }
    func_80064A40();
    ((S_BODY_8 *)(globals[0]))->unk_8D0 = packet;
}
#ifdef __mips__
__asm__(".size func_818F2800, 2200");
#endif
