#include "common.h"

typedef struct S_800B06F0_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    s16 unk_70;
    s16 unk_72;
    u16 unk_74;
    u8 pad_76[0x4];
    s16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    u16 unk_84;
    u8 pad_86[0x4];
    s16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    union { u32 i; u8 * p; } unk_C0;   /* accessed as both */
    u8 pad_C4[0x20];
    u32 unk_E4;
    u32 unk_E8;
    u32 unk_EC;
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F0;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F4;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F8;   /* overlapping accesses */
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_800B06F0_0;   /* scratch in func_800B06F0 */

typedef struct S_800B06F0_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_1;   /* initial_manager in func_800B06F0 */

typedef struct S_800B06F0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800B06F0_2_pre;   /* the 0x8 bytes before arg0_r in func_800B06F0, addressed as arg0_r[-1] */

typedef struct S_800B06F0_2 {
    u8 ** unk_00;
    u8 * unk_04;
    u16 unk_08;
} S_800B06F0_2;   /* arg0_r in func_800B06F0 */

typedef struct S_800B06F0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800B06F0_3;   /* arg2_r in func_800B06F0 */

typedef struct S_800B06F0_4 {
    s8 unk_00;
} S_800B06F0_4;   /* current in func_800B06F0 */

typedef struct S_800B06F0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} S_800B06F0_5;   /* object in func_800B06F0 */

typedef struct S_800B06F0_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 * unk_0C;
} S_800B06F0_6;   /* next_manager in func_800B06F0 */

typedef struct S_800B06F0_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_7;   /* manager in func_800B06F0 */



typedef struct {
    u8 *manager;
    u8 pad[0x9C];
    u32 value;
} GlobalSlot;

extern GlobalSlot D_80083160[];
extern s32 (*D_800DEFF0[])(s32, void *, void *);

extern s32 func_8003E12C();
extern s32 func_8004C010();
extern void *func_8004CD28();
extern s32 func_800649A0();
extern s32 func_80064A40();
extern s32 func_80064BC0();
extern s32 func_80064CF0();
extern s32 func_80064D80();
extern s32 func_80065480();
extern s32 func_800654B0();
extern s32 func_80065820();
extern void *func_800B0BE0();

/* Transform and emit linked batches of quad primitives into the rendering buffer. */
s32 func_800B06F0(u8 *initial_batch, s32 initial_dispatch_arg, u8 *initial_params)
{
    u8 *batch = initial_batch;
    s32 dispatch_arg = initial_dispatch_arg;
    u8 *params = initial_params;
    u8 *transform = (u8 *)0x1F8000D0;
    GlobalSlot *global_addr = D_80083160;
    u8 *scratch;
    u8 *manager;
    u8 *initial_manager;
    u8 *packet;
    register u8 **primitive_list ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *texture_data;
    u8 *primitive;
    u32 depth;
    u32 global_value;
    register s32 reverse_winding ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    s16 vertex_x;
    s16 vertex_y;
    s32 signed_flags;
    register u8 primitive_flags ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *primitive_check;
    u8 **primitive_ref;
    u8 *next_batch;
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u32 ot_entry_addr;
    s32 quad_extent;
#ifdef NON_MATCHING
    s32 hard_zero = 0;
#else
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: load-bearing for the whole function shape */
#endif

    global_value = *(volatile u32 *)&global_addr->value;
    initial_manager = D_80083160[0].manager;
    ASM_SET(scratch);   /* MATCH pin: load-bearing for the whole function shape */
    scratch = (u8 *)0x1F800000;
    ((S_800B06F0_0 *)scratch)->unk_EC = global_value;
    packet = ((S_800B06F0_1 *)initial_manager)->unk_8D0;
    ((S_800B06F0_0 *)scratch)->unk_20 = initial_manager + 0xB0;

dispatch:
    D_800DEFF0[((S_800B06F0_2 *)batch)->unk_08 & 1](dispatch_arg, params, scratch);

    primitive_list = ((S_800B06F0_2 *)batch)->unk_00;
    depth = ((S_800B06F0_0 *)scratch)->unk_C0.i;
    texture_data = ((S_800B06F0_2 *)batch)->unk_04;

    if (depth < 0x1E0U) {
        ot_entry_addr = depth * 4;
        ot_entry_addr += (u32)((S_800B06F0_0 *)scratch)->unk_20;
        ((S_800B06F0_0 *)scratch)->unk_C0.p = (u8 *)ot_entry_addr;
        ((S_800B06F0_0 *)scratch)->unk_B8 -= 0xA0;
        ((S_800B06F0_0 *)scratch)->unk_BA -= 0x78;
        func_800649A0(depth);

        ((S_800B06F0_0 *)scratch)->unk_100 = ((S_800B06F0_3 *)params)->unk_16;
        ((S_800B06F0_0 *)scratch)->unk_102 = ((S_800B06F0_3 *)params)->unk_18;
        ((S_800B06F0_0 *)scratch)->unk_104 = ((S_800B06F0_3 *)params)->unk_1A;
        ((S_800B06F0_0 *)scratch)->unk_E4 = ((S_800B06F0_3 *)params)->unk_20;
        ((S_800B06F0_0 *)scratch)->unk_E8 = ((S_800B06F0_3 *)params)->unk_22;
        ((S_800B06F0_0 *)scratch)->unk_30 = ((S_800B06F0_3 *)params)->unk_1C;
        ((S_800B06F0_0 *)scratch)->unk_34 = ((S_800B06F0_3 *)params)->unk_1E;
        ((S_800B06F0_0 *)scratch)->unk_38 = 0x1000;

        func_80065820(scratch + 0x100, transform);
        func_80064BC0(transform, scratch + 0x30);
        func_80064D80(transform);
        func_80064CF0(transform);

        primitive = *primitive_list;
        if (primitive == 0)
            goto lists_done;
loop:
            ((S_800B06F0_0 *)scratch)->unk_8C = 0;
            ((S_800B06F0_0 *)scratch)->unk_84 = 0;
            ((S_800B06F0_0 *)scratch)->unk_7C = 0;
            ((S_800B06F0_0 *)scratch)->unk_74 = 0;

            primitive = (u8 *)((u32)primitive | 0x80000000U);

            if ((primitive[0] ^ ((S_800B06F0_3 *)params)->unk_14) & 1) {
                vertex_x = -(s8)primitive[2] - ((S_800B06F0_3 *)params)->unk_20;
                ((S_800B06F0_0 *)scratch)->unk_80 = vertex_x;
                ((S_800B06F0_0 *)scratch)->unk_70 = vertex_x;
                vertex_x -= primitive[0xA];
                goto store_x;
            }

            vertex_x = (s8)primitive[2] - ((S_800B06F0_3 *)params)->unk_20;
            ((S_800B06F0_0 *)scratch)->unk_80 = vertex_x;
            ((S_800B06F0_0 *)scratch)->unk_70 = vertex_x;
            quad_extent = primitive[0xA];
            vertex_x = vertex_x + quad_extent;
store_x:
            (*(s16 *)((u8 *)scratch + 0x88)) = vertex_x;
            (*(s16 *)((u8 *)scratch + 0x78)) = vertex_x;

            if ((primitive[0] ^ ((S_800B06F0_3 *)params)->unk_14) & 2) {
                vertex_y = -(s8)primitive[3] - ((S_800B06F0_3 *)params)->unk_22;
                ((S_800B06F0_0 *)scratch)->unk_7A = vertex_y;
                ((S_800B06F0_0 *)scratch)->unk_72 = vertex_y;
                vertex_y -= primitive[0xB];
                goto store_y;
            }

            vertex_y = (s8)primitive[3] - ((S_800B06F0_3 *)params)->unk_22;
            ((S_800B06F0_0 *)scratch)->unk_7A = vertex_y;
            ((S_800B06F0_0 *)scratch)->unk_72 = vertex_y;
            quad_extent = primitive[0xB];
            vertex_y = vertex_y + quad_extent;
store_y:
            ((S_800B06F0_0 *)scratch)->unk_8A = vertex_y;
            ((S_800B06F0_0 *)scratch)->unk_82 = vertex_y;
            ASM_KEEP(vertex_y);   /* MATCH pin: retail schedule: same instructions, different order without it */

            func_800654B0(
                scratch + 0x70, scratch + 0x78,
                scratch + 0x80, scratch + 0x88,
                scratch + 0xF0, scratch + 0xF4,
                scratch + 0xF8, scratch + 0xFC,
                scratch + 0x90, scratch + 0x94);

            signed_flags = ((S_800B06F0_4 *)primitive)->unk_00;
            primitive_flags = primitive[0];
            if ((signed_flags >= 0) && (primitive_flags & 8)) {
                reverse_winding = primitive_flags & 4;
                if (func_80065480(
                        ((S_800B06F0_0 *)scratch)->unk_F0.at00.v,
                        ((S_800B06F0_0 *)scratch)->unk_F4.at00.v,
                        ((S_800B06F0_0 *)scratch)->unk_F8.at00.v, primitive_flags) <= 0) {
                    if (reverse_winding != 0) {
                        goto fallback;
                    }
                    goto check_2c;
                }
                if (reverse_winding != 0) {
check_2c:
                    if (primitive[1] == 0x2C) {
                        texture_data += 4;
                        goto next_list;
                    }
                    goto next_list;
                }
            }

fallback:
            if (primitive[0] & 4) {
                func_8003E12C(scratch + 0xF0, scratch + 0xF4);
                func_8003E12C(scratch + 0xF8, scratch + 0xFC);
            }

            ((S_800B06F0_5 *)packet)->unk_08 = ((S_800B06F0_0 *)scratch)->unk_F0.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)packet)->unk_0A = ((S_800B06F0_0 *)scratch)->unk_F0.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)packet)->unk_10 = ((S_800B06F0_0 *)scratch)->unk_F4.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)packet)->unk_12 = ((S_800B06F0_0 *)scratch)->unk_F4.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)packet)->unk_18 = ((S_800B06F0_0 *)scratch)->unk_F8.at00u.v + ((S_800B06F0_0 *)scratch)->unk_B8;
            ((S_800B06F0_5 *)packet)->unk_1A = ((S_800B06F0_0 *)scratch)->unk_F8.at02.v + ((S_800B06F0_0 *)scratch)->unk_BA;
            ((S_800B06F0_5 *)packet)->unk_20 = ((S_800B06F0_0 *)scratch)->unk_FC + ((S_800B06F0_0 *)scratch)->unk_B8;
            primitive_check = primitive;
            ((S_800B06F0_5 *)packet)->unk_22 = ((S_800B06F0_0 *)scratch)->unk_FE + ((S_800B06F0_0 *)scratch)->unk_BA;
            primitive_ref = &primitive;

            if ((primitive_check[1] & 0xFC) == 0x2C) {
                packet = func_800B0BE0(((S_800B06F0_0 *)scratch)->unk_C0.i, params, primitive_ref, packet);
                func_8004C010(packet - 0x24, texture_data);
                if (primitive != 0) {
                    goto loop;
                }
                texture_data += 4;
                goto next_list;
            }

            {
                u32 ot_entry;

                ot_entry = ((S_800B06F0_0 *)scratch)->unk_C0.i;
                ASM_KEEP_NV(ot_entry);   /* MATCH pin: retail schedule: same instructions, different order without it */
                packet = func_8004CD28(ot_entry, params, primitive_ref, packet);
            }
            ASM_KEEP(packet);   /* MATCH pin: retail delay-slot fill depends on it */
            if (primitive != 0) {
                goto loop;
            }

next_list:
            primitive_list++;
            primitive = *primitive_list;
            if (*(u8 * volatile *)&primitive != 0) {
                goto loop;
            }
lists_done:
        func_80064A40();
    }

    next_batch = ((S_800B06F0_2_pre *)batch)[-1].unk_00;
    if (next_batch == 0) {
        goto done;
    }
    batch = next_batch + 0x20;
    dispatch_arg = ((S_800B06F0_6 *)next_batch)->unk_08;
    params = ((S_800B06F0_6 *)next_batch)->unk_0C;
    goto dispatch;

done:
    manager = global_addr->manager;
    result = hard_zero;
    ((S_800B06F0_7 *)manager)->unk_8D0 = packet;
    return result;
}
