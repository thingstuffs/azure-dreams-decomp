#include "common.h"

typedef struct S_807B0B3C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_807B0B3C_0_pre;   /* the 0x8 bytes before initial in func_807B0B3C, addressed as initial[-1] */

typedef struct S_807B0B3C_0 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_807B0B3C_0;   /* initial in func_807B0B3C */

typedef struct S_807B0B3C_1 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    s16 unk_06;
    union { u16 u16; u8 u8; } unk_08;   /* accessed as both */
} S_807B0B3C_1;   /* arg0 in func_807B0B3C */

typedef struct S_807B0B3C_2 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_807B0B3C_2;   /* a3p in func_807B0B3C */

typedef struct S_807B0B3C_3 {
    union { volatile u16 v; s16 n; } unk_00;   /* accessed as both */
    union { volatile u16 v; s16 n; } unk_02;   /* accessed as both */
    u16 unk_04;
} S_807B0B3C_3;   /* a0p in func_807B0B3C */

typedef struct S_807B0B3C_4 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    u16 unk_0C;
} S_807B0B3C_4;   /* (u8 *)a2v in func_807B0B3C */

typedef struct S_807B0B3C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B0B3C_5;   /* (u8 *)a2p in func_807B0B3C */

typedef struct S_807B0B3C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_807B0B3C_6;   /* (u8 *)v1 in func_807B0B3C */

typedef struct S_807B0B3C_7 {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    s32 unk_20;
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_807B0B3C_7;   /* prim in func_807B0B3C */

typedef struct S_807B0B3C_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_807B0B3C_8;   /* verts in func_807B0B3C */

typedef struct S_807B0B3C_9 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_9;   /* rootp in func_807B0B3C */

typedef struct S_807B0B3C_10 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_10;   /* entryp in func_807B0B3C */

typedef struct S_807B0B3C_11 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_807B0B3C_11;   /* a1p in func_807B0B3C */

typedef struct S_807B0B3C_12 {
    union { u32 u; s32 s; } unk_00;   /* accessed as both */
    union { u32 u; s32 s; } unk_04;   /* accessed as both */
    union { u32 u; s32 s; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
} S_807B0B3C_12;   /* colors in func_807B0B3C */

typedef struct S_807B0B3C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_807B0B3C_13;   /* dst in func_807B0B3C */

typedef struct S_807B0B3C_14 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u8 pad_12[0x6];
    u16 unk_18;
} S_807B0B3C_14;   /* scratch in func_807B0B3C */

typedef struct S_807B0B3C_15 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_15;   /* (u8 *)offset in func_807B0B3C */



typedef struct {
    s32 sp18;
    s32 sp1C;
} StackLocals;

typedef union {
    long long value;
    struct {
        s32 hi;
        s32 lo;
    } words;
} SignedProduct;

extern s32 func_80065420(void *, void *, void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066708(void *);
extern void func_8006671C(void *, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s32 func_800F8394() __attribute__((noreturn));
extern s32 func_800F83EC() __attribute__((noreturn));
extern s32 func_800F8488() __attribute__((noreturn));
extern s32 func_800F8500() __attribute__((noreturn));
extern s32 func_800F87C0() __attribute__((noreturn));
extern s32 func_800F87C8() __attribute__((noreturn));
extern u8 *D_80083160;

#ifdef NON_MATCHING
#define LOAD_SPLIT_GLOBAL(var) ((var) = &D_80083160)
#else
#define LOAD_SPLIT_GLOBAL(var) \
    do { \
        (var) = (u8 **)0x80080000; \
        ASM_KEEP_NV(var); \
        (var) = (u8 **)((u8 *)(var) + 0x3160); \
    } while (0)
#endif

#ifdef NON_MATCHING
#define LOAD_GLOBAL_PAGE(var) ((var) = &D_80083160)
#define FINISH_GLOBAL_TABLE(var, dep1, dep2) ((void)0)
#else
#define LOAD_GLOBAL_PAGE(var) \
    do { \
        (var) = (u8 **)0x80080000; \
    } while (0)
#define FINISH_GLOBAL_TABLE(var, dep1, dep2) \
    do { \
        ASM_KEEP_DEP_NV(var, dep2); \
        (var) = (u8 **)((u8 *)(var) + 0x3160); \
    } while (0)
#endif

/* Builds and queues textured and shaded quads for an effect and advances to the next object. */
s32 func_807B0B3C(void *object, s32 caller_a1, void *caller_a2) {
    u8 *scratch;
    register u8 *colors ASM_REG("$21");
    u8 *verts;
    register u32 addr_mask;
    u8 *effect;
    register s32 saved_a1 ASM_REG("$5") = caller_a1;
    register void *saved_a2 ASM_REG("$6") = caller_a2;
    register s32 div5_magic ASM_REG("$9");
    StackLocals stack;
    register u32 draw_value ASM_REG("$4");
    s32 vertex_index;
    register s32 depth ASM_REG("$20");
    register s32 bucket_offset ASM_REG("$17");
    register s32 gray ASM_REG("$5");
    void *prim_arg;
    register s32 tex_coord ASM_REG("$2");
    s32 tex_left;
    u8 *world_vertex;
    u8 *screen_vertex;
    register u8 *prim ASM_REG("$16");
    register u8 *object_base ASM_REG("$9");
    u8 *next_object;
    register u16 component ASM_REG("$3");
    s32 coord;

    (void)&object;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);
    colors = scratch;
    ASM_KEEP_NV(colors);
    colors = (u8 *)((u32)colors | 0x40);
    verts = scratch;
    ASM_KEEP_NV(verts);
    verts = (u8 *)((u32)verts | 0x80);
    div5_magic = 0x66666667;
    addr_mask = 0xFFFFFF;
    stack.sp1C = div5_magic;
    ASM_MEM_BARRIER();
    object_base = (u8 *)object;
    effect = object_base;
    if ((((S_807B0B3C_0 *)object_base)->unk_06 >> 10) & 1) {
        u8 *vertex_pair;
        u8 *vertex_ptr;
        register u32 pair_addr ASM_REG("$6");
        register s32 height ASM_REG("$4");
        register s32 frame_remainder ASM_REG("$5");
        register s32 coord_work ASM_REG("$3");
        u16 coord_half;
        register s32 product_hi ASM_REG("$9");
        SignedProduct product;

        vertex_index = 0;
        vertex_pair = scratch;
build_y_pairs:
        coord_work = vertex_index * 2;
        coord_half = ((S_807B0B3C_1 *)effect)->unk_00.u;
        stack.sp18 = coord_work;
        ((S_807B0B3C_2 *)vertex_pair)->unk_08 = coord_half;
        ((S_807B0B3C_2 *)vertex_pair)->unk_00 = coord_half;
        vertex_ptr = vertex_pair + 8;
        coord_work = ((S_807B0B3C_1 *)effect)->unk_02.s;
        if (vertex_index < 2) {
            register s32 lower_coord ASM_REG("$2");

            lower_coord = coord_work - 0x20;
            ASM_TAILSLOT_PIN_TIED(lower_coord);
            return func_800F83EC(vertex_ptr, saved_a1, saved_a2, vertex_pair);
        }
        coord_half = coord_work + 0x20;
        ASM_KEEP(coord_half);
        ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v = coord_half;
        pair_addr = stack.sp18;
        coord_half = ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v;
        pair_addr <<= 3;
        ((S_807B0B3C_2 *)vertex_pair)->unk_02 = coord_half;
        height = ((S_807B0B3C_1 *)effect)->unk_04;
        pair_addr += (u32)scratch;
        ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_0C = height;
        coord_half = ((S_807B0B3C_1 *)effect)->unk_08.u16;
        div5_magic = stack.sp1C;
        frame_remainder = (s16)coord_half;
        product.value = (long long)frame_remainder * div5_magic;
        vertex_index++;
        vertex_pair += 0x10;
        ASM_KEEP_NV(product.words.hi);
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);
        coord_work = product_hi >> 1;
        coord_work -= frame_remainder >> 31;
        frame_remainder -= coord_work * 5;
        height = height + frame_remainder - 0x36;
        ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_04 = height;
        if (vertex_index < 2) {
            goto build_y_pairs;
        }
        depth = 0;
        ASM_TAILSLOT_PIN_TIED(depth);
        return func_800F8500(height, frame_remainder, (void *)pair_addr, vertex_pair);
    }

    {
        s32 pair_addr;
        u8 *vertex_ptr;
        register s32 height ASM_REG("$4");
        s32 second_pair;
        s32 pairs_end;
        register s32 frame_remainder ASM_REG("$5");
        register s32 coord_work ASM_REG("$3");
        register u16 coord_half ASM_REG("$2");
        register s32 product_hi ASM_REG("$9");
        SignedProduct product;

        pair_addr = (s32)scratch;
        second_pair = (s32)scratch + 0x10;
        pairs_end = (s32)scratch + 0x20;
build_x_pairs:
        coord_work = ((S_807B0B3C_1 *)effect)->unk_00.s;
        vertex_ptr = (u8 *)pair_addr + 8;
        if (pair_addr < second_pair) {
            register s32 lower_coord ASM_REG("$2");

            lower_coord = coord_work - 0x20;
            ASM_TAILSLOT_PIN_TIED(lower_coord);
            return func_800F8488(vertex_ptr, saved_a1, (void *)pair_addr, (void *)pairs_end);
        }
        coord_half = coord_work + 0x20;
        ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_08 = coord_half;
        ASM_KEEP_NV(vertex_ptr);
        coord_half = ((S_807B0B3C_3 *)vertex_ptr)->unk_00.v;
        ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_00 = coord_half;
        coord_half = ((S_807B0B3C_1 *)effect)->unk_02.u;
        coord_work = (s32)((u32)8 + (u32)pair_addr);
        ((S_807B0B3C_6 *)((u8 *)coord_work))->unk_02 = coord_half;
        ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_02 = coord_half;
        height = ((S_807B0B3C_1 *)effect)->unk_04;
        ((S_807B0B3C_6 *)((u8 *)coord_work))->unk_04 = height;
        coord_half = ((S_807B0B3C_1 *)effect)->unk_08.u16;
        div5_magic = stack.sp1C;
        frame_remainder = (s16)coord_half;
        product.value = (long long)frame_remainder * div5_magic;
        ASM_KEEP_NV(product.words.hi);
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);
        coord_work = product_hi >> 1;
        coord_work -= frame_remainder >> 31;
        frame_remainder -= coord_work * 5;
        height = height + frame_remainder - 0x36;
        ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_04 = height;
        pair_addr += 0x10;
        ASM_SCHED_BARRIER();
        depth = 0;
        if (pair_addr < pairs_end) {
            goto build_x_pairs;
        }
    }

    vertex_index = depth;
    screen_vertex = verts;
    world_vertex = scratch;
    do {
        register void *world_arg ASM_REG("$4") = world_vertex;
        register void *screen_arg ASM_REG("$5") = screen_vertex;
        register void *projection_arg ASM_REG("$6");
        void *flag_arg;
        register s32 depth_sum ASM_REG("$3");
        s32 vertex_depth;

        projection_arg = &stack.sp18;
        flag_arg = projection_arg;
        vertex_depth = func_80065420(world_arg, screen_arg, projection_arg, flag_arg);
        depth_sum = depth - 8;
        depth = depth_sum + vertex_depth;
        screen_vertex += 4;
        vertex_index++;
        world_vertex += 8;
    } while (vertex_index < 4);

    {
        s32 rounded_depth;

        rounded_depth = depth;
        if (depth < 0) {
            rounded_depth = depth + 3;
        }
        depth = rounded_depth >> 2;
        ASM_KEEP_NV(depth);
    }

    {
        register u8 **render_slot ASM_REG("$9");
        u8 *render_state;

        render_slot = &D_80083160;
        ASM_KEEP_NV(render_slot);
        render_state = *render_slot;
        prim = *(u8 **)(render_state + 0x8D0);
        prim_arg = (void *)prim;
        ASM_KEEP_NV(prim_arg);
        *(u8 **)(render_state + 0x8D0) = prim + 0x34;
    }
    gray = 0xA0A0A0;
    ((S_807B0B3C_7 *)prim)->unk_1C = 0;
    ((S_807B0B3C_7 *)prim)->unk_04 = 0;
    ASM_SCHED_BARRIER();
    ((S_807B0B3C_7 *)prim)->unk_28 = gray;
    ((S_807B0B3C_7 *)prim)->unk_10 = gray;
    func_8006671C(prim_arg, gray);
    func_80066640(prim, 1);
    ((S_807B0B3C_7 *)prim)->unk_18.at02.v = func_80066460(0, 1, 0x280, 0x100);
    {
        u16 clut;
        s32 first_vertex;

        clut = func_8006649C(0x90, 0x1F7);
        first_vertex = ((S_807B0B3C_8 *)verts)->unk_00;
        ((S_807B0B3C_7 *)prim)->unk_0C.at02.v = clut;
        ((S_807B0B3C_7 *)prim)->unk_08 = first_vertex;
    }
    ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_8 *)verts)->unk_04;
    ((S_807B0B3C_7 *)prim)->unk_20 = ((S_807B0B3C_8 *)verts)->unk_08;
    ((S_807B0B3C_7 *)prim)->unk_2C = ((S_807B0B3C_8 *)verts)->unk_0C;

    draw_value = ((S_807B0B3C_1 *)effect)->unk_08.u16 & 7;
    tex_coord = (draw_value & 3) << 5;
    tex_left = tex_coord - 0x80;
    tex_coord -= 0x61;
    draw_value = (draw_value >> 2) << 5;
    ((S_807B0B3C_7 *)prim)->unk_30 = tex_coord;
    ((S_807B0B3C_7 *)prim)->unk_24 = tex_coord;
    tex_coord = draw_value - 0x40;
    draw_value -= 0x21;
    ((S_807B0B3C_7 *)prim)->unk_31 = tex_coord;
    ((S_807B0B3C_7 *)prim)->unk_18.at01.v = tex_coord;
    ((S_807B0B3C_7 *)prim)->unk_18.at00.v = tex_left;
    ((S_807B0B3C_7 *)prim)->unk_0C.at00.v = tex_left;
    ((S_807B0B3C_7 *)prim)->unk_25 = draw_value;
    ((S_807B0B3C_7 *)prim)->unk_0C.at01.v = draw_value;

    if ((u32)depth < 0x1E0U) {
        register u8 **next_render_slot ASM_REG("$9");

        {
            register u8 **render_slot ASM_REG("$9");
            register u8 *render_state ASM_REG("$2");
            register u32 tag_mask ASM_REG("$9");
            u32 prim_tag;
            u32 bucket_tag;

            render_slot = &D_80083160;
            ASM_KEEP_NV(render_slot);
            draw_value = depth * 4;
            render_state = *render_slot;
            tag_mask = 0xFF000000;
            prim_tag = ((S_807B0B3C_7 *)prim)->unk_00;
            render_state = (u8 *)((u32)draw_value + (u32)render_state);
            prim_tag &= tag_mask;
            LOAD_GLOBAL_PAGE(next_render_slot);
            bucket_tag = ((S_807B0B3C_9 *)render_state)->unk_B0;
            FINISH_GLOBAL_TABLE(next_render_slot, bucket_tag, prim_tag);
            ASM_KEEP_NV(next_render_slot);
            ((S_807B0B3C_7 *)prim)->unk_00 = prim_tag | (bucket_tag & addr_mask);
        }
        {
            u8 *render_state;
            u8 *bucket_ptr;
            register u32 tag_mask ASM_REG("$9");

            render_state = *next_render_slot;
            tag_mask = 0xFF000000;
            bucket_ptr = (u8 *)((u32)draw_value + (u32)render_state);
            ((S_807B0B3C_10 *)bucket_ptr)->unk_B0 =
                (((S_807B0B3C_10 *)bucket_ptr)->unk_B0 & tag_mask) |
                ((u32)prim & addr_mask);
            ASM_KEEP(prim);
        }
    }

    {
        register u8 *vertex_ptr ASM_REG("$4");
        register u8 *color_ptr ASM_REG("$5");

        vertex_index = 3;
        color_ptr = colors + 0xC;
        vertex_ptr = scratch + 0x18;
        do {
            coord = ((S_807B0B3C_1 *)effect)->unk_00.s;
            if (vertex_index < 2) {
                ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord - 0x20;
            } else {
                ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord + 0x20;
            }
            coord = ((S_807B0B3C_1 *)effect)->unk_02.s;
            if (vertex_index & 1) {
                ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord + 0x20;
            } else {
                ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord - 0x20;
            }
            vertex_index--;
            ((S_807B0B3C_3 *)vertex_ptr)->unk_04 = ((S_807B0B3C_1 *)effect)->unk_04;
            vertex_ptr -= 8;
            tex_coord = (((S_807B0B3C_1 *)effect)->unk_08.u8 & 3) * 8;
            ((S_807B0B3C_11 *)color_ptr)->unk_02 = tex_coord;
            ((S_807B0B3C_11 *)color_ptr)->unk_01 = tex_coord;
            ((S_807B0B3C_11 *)color_ptr)->unk_00 = tex_coord;
            color_ptr -= 4;
        } while (vertex_index >= 0);
    }

    coord = ((S_807B0B3C_1 *)effect)->unk_06;
    if (coord == 0x400) {
        goto angle_400;
    }
    if (coord > 0x400) {
        goto angle_high;
    }
    if (coord == 0) {
        goto angle_0;
    }
    {
        register s32 last_vertex ASM_REG("$18");
        register u8 *last_screen_vertex ASM_REG("$17");

        last_vertex = 3;
        last_screen_vertex = verts + 0xC;
        ASM_TAILSLOT_PIN_TIED(last_vertex);
        ASM_TAILSLOT_PIN_TIED(last_screen_vertex);
        return func_800F87C8();
    }

angle_high:
    if (coord == 0x800) {
        goto angle_800;
    }
    if (coord != 0xC00) {
        register s32 last_vertex ASM_REG("$18");
        register u8 *last_screen_vertex ASM_REG("$17");

        last_vertex = 3;
        last_screen_vertex = verts + 0xC;
        ASM_TAILSLOT_PIN_TIED(last_vertex);
        ASM_TAILSLOT_PIN_TIED(last_screen_vertex);
        return func_800F87C8();
    }
    goto angle_c00;

angle_0:
    ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
    component = ((S_807B0B3C_1 *)effect)->unk_02.u;
    ASM_SCHED_BARRIER();
    {
        u8 *vertex_ptr;

        vertex_ptr = scratch + 0x10;
        ASM_KEEP_NV(vertex_ptr);
        ((S_807B0B3C_13 *)vertex_ptr)->unk_02 = component;
    }
    ((S_807B0B3C_14 *)scratch)->unk_02 = component;
    return func_800F87C0();

angle_400:
    component = ((S_807B0B3C_1 *)effect)->unk_00.u;
    ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
    ((S_807B0B3C_14 *)scratch)->unk_18 = component;
    ((S_807B0B3C_14 *)scratch)->unk_10 = component;
    return func_800F87C0();

angle_800:
    ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
    component = ((S_807B0B3C_1 *)effect)->unk_02.u;
    ASM_SCHED_BARRIER();
    {
        u8 *vertex_ptr;

        vertex_ptr = scratch + 0x18;
        ASM_KEEP_NV(vertex_ptr);
        ((S_807B0B3C_13 *)vertex_ptr)->unk_02 = component;
    }
    ((S_807B0B3C_14 *)scratch)->unk_0A = component;
    return func_800F87C0();

angle_c00:
    ASM_SCHED_BARRIER();
    component = ((S_807B0B3C_1 *)effect)->unk_00.u;
    ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
    ((S_807B0B3C_14 *)scratch)->unk_08 = component;
    ((S_807B0B3C_14 *)scratch)->unk_00 = component;

    ASM_SCHED_BARRIER();
    vertex_index = 3;
    screen_vertex = verts + 0xC;
    world_vertex = scratch + 0x18;
    do {
        register void *world_arg ASM_REG("$4") = world_vertex;
        register void *screen_arg ASM_REG("$5") = screen_vertex;
        register void *projection_arg ASM_REG("$6");
        void *flag_arg;

        projection_arg = &stack.sp18;
        flag_arg = projection_arg;
        func_80065420(world_arg, screen_arg, projection_arg, flag_arg);
        screen_vertex -= 4;
        vertex_index--;
        world_vertex -= 8;
    } while (vertex_index >= 0);

    if ((u32)depth < 0x1E0U) {
        s32 blend_mode;
        s32 page_x;
        s32 page_y;
        register u8 **next_render_slot ASM_REG("$9");

        {
            register u8 **render_slot ASM_REG("$9");
            u8 *render_state;

            LOAD_SPLIT_GLOBAL(render_slot);
            ASM_KEEP_NV(render_slot);
            render_state = *render_slot;
            prim = *(u8 **)(render_state + 0x8D0);
            {
                s32 first_color;

                first_color = ((S_807B0B3C_12 *)colors)->unk_00.s;
                *(u8 **)(render_state + 0x8D0) = prim + 0x24;
                ((S_807B0B3C_7 *)prim)->unk_04 = first_color;
            }
        }
        ((S_807B0B3C_7 *)prim)->unk_0C.at00u.v = ((S_807B0B3C_12 *)colors)->unk_04.s;
        ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_12 *)colors)->unk_08.s;
        ((S_807B0B3C_7 *)prim)->unk_1C = ((S_807B0B3C_12 *)colors)->unk_0C.s;
        func_80066708(prim);
        func_80066640(prim, 1);
        {
            register u8 **render_slot ASM_REG("$9");
            register u8 *render_state ASM_REG("$2");
            register u32 tag_mask ASM_REG("$9");
            s32 vertex;
            u32 prim_tag;
            u32 bucket_tag;

            LOAD_GLOBAL_PAGE(render_slot);
            vertex = ((S_807B0B3C_8 *)verts)->unk_00;
            prim_tag = ((S_807B0B3C_7 *)prim)->unk_00;
            FINISH_GLOBAL_TABLE(render_slot, vertex, prim_tag);
            ASM_KEEP_NV(render_slot);
            ((S_807B0B3C_7 *)prim)->unk_08 = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_04;
            bucket_offset = depth * 4;
            ((S_807B0B3C_7 *)prim)->unk_10 = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_08;
            ASM_SCHED_BARRIER();
            draw_value = 0;
            ASM_KEEP_NV(draw_value);
            ((S_807B0B3C_7 *)prim)->unk_18.at00u.v = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_0C;
            ASM_SCHED_BARRIER();
            blend_mode = 1;
            ASM_KEEP_NV(blend_mode);
            ((S_807B0B3C_7 *)prim)->unk_20 = vertex;
            render_state = *render_slot;
            tag_mask = 0xFF000000;
            prim_tag &= tag_mask;
            LOAD_GLOBAL_PAGE(next_render_slot);
            render_state = (u8 *)((u32)bucket_offset + (u32)render_state);
            bucket_tag = ((S_807B0B3C_9 *)render_state)->unk_B0;
            FINISH_GLOBAL_TABLE(next_render_slot, bucket_tag, prim_tag);
            ASM_KEEP_NV(next_render_slot);
            ((S_807B0B3C_7 *)prim)->unk_00 = prim_tag | (bucket_tag & addr_mask);
        }
        {
            register u8 *bucket_ptr ASM_REG("$3");
            register u32 tag_mask ASM_REG("$9");
            u32 bucket_tag;

            bucket_ptr = *next_render_slot;
            tag_mask = 0xFF000000;
            bucket_ptr = (u8 *)((u32)bucket_offset + (u32)bucket_ptr);
            bucket_tag =
                (((S_807B0B3C_10 *)bucket_ptr)->unk_B0 & tag_mask) |
                ((u32)prim & addr_mask);
            ASM_SCHED_BARRIER();
            next_render_slot = &D_80083160;
            ASM_KEEP_NV(next_render_slot);
            ((S_807B0B3C_10 *)bucket_ptr)->unk_B0 = bucket_tag;
            bucket_ptr = *next_render_slot;
            ASM_SCHED_BARRIER();
            page_x = draw_value;
            ASM_KEEP_NV(page_x);
            prim = *(u8 **)(bucket_ptr + 0x8D0);
            page_y = draw_value;
            *(u8 **)(bucket_ptr + 0x8D0) = prim + 0xC;
        }
        component = func_80066460(draw_value, blend_mode, page_x, page_y);
        {
            s32 zero;
            void *draw_mode_arg;

            draw_mode_arg = (void *)prim;
            zero = 0;
            func_80067F20(draw_mode_arg, zero, zero, component, 0);
        }

        {
            register u8 **render_slot ASM_REG("$9");
            register u8 *bucket_ptr ASM_REG("$2");
            register u32 tag_mask ASM_REG("$9");
            u32 prim_tag;
            u32 bucket_tag;

            render_slot = &D_80083160;
            ASM_KEEP_NV(render_slot);
            bucket_ptr = *render_slot;
            tag_mask = 0xFF000000;
            prim_tag = ((S_807B0B3C_7 *)prim)->unk_00;
            bucket_ptr = (u8 *)((u32)bucket_offset + (u32)bucket_ptr);
            prim_tag &= tag_mask;
            LOAD_GLOBAL_PAGE(next_render_slot);
            bucket_tag = ((S_807B0B3C_10 *)bucket_ptr)->unk_B0;
            FINISH_GLOBAL_TABLE(next_render_slot, bucket_tag, prim_tag);
            ASM_KEEP_NV(next_render_slot);
            ((S_807B0B3C_7 *)prim)->unk_00 = prim_tag | (bucket_tag & addr_mask);
        }
        {
            u8 *render_state;
            register u32 tag_mask ASM_REG("$9");

            render_state = *next_render_slot;
            tag_mask = 0xFF000000;
            bucket_offset += (s32)render_state;
            ((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 =
                (((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 & tag_mask) |
                ((u32)prim & addr_mask);
        }
    }

    object_base = (u8 *)object;
    next_object = ((S_807B0B3C_0_pre *)object_base)[-1].unk_00;
    if (next_object != 0) {
        next_object += 0x20;
        object = next_object;
        return func_800F8394(next_object);
    }
    ASM_SCHED_BARRIER();
    {
        register s32 zero_result ASM_REG("$0");

        return zero_result;
    }
}
