#include "common.h"

typedef struct S_800BC4D4_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BC4D4_0;   /* root in func_800BC4D4 */

typedef struct S_800BC4D4_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    union { u32 u32; s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_10;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    u8 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    union { s32 s; u32 u; } unk_30;   /* accessed as both */
    union { s32 s; u32 u; } unk_34;   /* accessed as both */
    s32 unk_38;
    u8 pad_3C[0x34];
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    union { s16 s; u16 u; } unk_78;   /* accessed as both */
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
} S_800BC4D4_1;   /* scratch in func_800BC4D4 */

typedef struct S_800BC4D4_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800BC4D4_2;   /* arg1 in func_800BC4D4 */

typedef struct S_800BC4D4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC4D4_3;   /* arg0 in func_800BC4D4 */

typedef struct S_800BC4D4_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800BC4D4_4;   /* matrix in func_800BC4D4 */

typedef struct S_800BC4D4_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800BC4D4_5_pre;   /* the 0x4 bytes before packet_field in func_800BC4D4, addressed as packet_field[-1] */

typedef struct S_800BC4D4_5 {
    u8 unk_00;
    u8 pad_01[0xC];
    u8 unk_0D;
    u8 pad_0E[0x8];
    u8 unk_16;
    u8 pad_17[0x6];
    u8 unk_1D;
    u8 unk_1E;
} S_800BC4D4_5;   /* packet_field in func_800BC4D4 */

typedef struct S_800BC4D4_6 {
    u16 unk_00;
} S_800BC4D4_6;   /* texture_data in func_800BC4D4 */

typedef struct S_800BC4D4_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BC4D4_7;   /* *global in func_800BC4D4 */


#define KEEP_NV_EXPR(v) ({ ASM_KEEP_NV(v); 0; })
#define KEEP_DEP_NV_EXPR(v, d) ({ ASM_KEEP_DEP_NV(v, d); 0; })

typedef struct ScratchGeom {
    u8 pad70[0x70];
    s16 p70;
    u8 pad72[6];
    s16 p78;
    u8 pad7a[6];
    s16 p80;
    u8 pad82[6];
    s16 p88;
    u8 pad8a[6];
    s16 p90;
    u8 pad92[2];
    s16 p94;
    u8 pad96[0x5a];
    s16 pF0;
    u8 padF2[2];
    s16 pF4;
    u8 padF6[2];
    s16 pF8;
    u8 padFA[2];
    s16 pFC;
    u8 padFE[2];
} ScratchGeom;

typedef struct GeomTailArgs {
    s16 *arg9;
    s16 *arg10;
} GeomTailArgs;

typedef struct GeomSideEffects {
} GeomSideEffects;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0(s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *,
                          GeomTailArgs, GeomSideEffects);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern u8 D_8006CD30[];
extern u8 D_80083160[];

#ifdef NON_MATCHING
#define GLOBAL_PAGE_8008 (D_80083160 - 0x3160)
#else
#define GLOBAL_PAGE_8008 ((u8 *)0x80080000)
#endif

void func_800BC4D4(void *arg0, void *arg1, u16 arg2, s32 arg3)
{
    register u8 *scratch_init ASM_REG("$4") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *scratch_b8 ASM_REG("$5") = scratch_init;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *scratch_90;
    u8 *scratch_94;
    register u8 *scratch ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *global_page;
    register u8 **global ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register u8 *page_color ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *matrix;
    u8 *packet;
    u8 *packet_next;
    u8 *texture;
    u8 *texture_data;
    u8 *packet_field;
    u8 *root;
    u32 projected;
    u32 projected_minus7;
    u32 index;
    s32 depth;
    s32 value;
    register s32 color0 ASM_REG("$4"); /* MATCH: retain the color operand register across page selection. */
    register s32 color1 ASM_REG("$5"); /* MATCH: retain the color operand register across page selection. */
    s32 shifted;
    s32 color_sum;
    s32 color_mix;
    register s32 coord_x ASM_REG("$2"); /* MATCH: coordinate arms share v0 at the merged stores. */
    register s32 coord_y ASM_REG("$2"); /* MATCH: coordinate arms share v0 at the merged stores. */
    u16 screen_x;
    u16 depth_coord;
    u16 texture_height;
    u16 texture_x;
    u16 texture_y;

    scratch_b8 = (u8 *)((u32)scratch_b8 | 0xB8);
    ASM_KEEP_MEMDEP_NV(scratch_init, page_color, *(u8 **)D_80083160);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    scratch_90 = scratch_init;
    ASM_KEEP_NV(scratch_90);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    scratch = scratch_init;
    scratch_90 = (u8 *)((u32)scratch_90 | 0x90);
    root = *(u8 **)D_80083160;
    packet = ((S_800BC4D4_0 *)root)->unk_8D0;
    ((S_800BC4D4_1 *)scratch)->unk_20 = root + 0xB0;
#ifdef NON_MATCHING
    global_page = D_80083160 - 0x3160;
#else
    ASM_SET(global_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#endif
    ((S_800BC4D4_1 *)scratch)->unk_EC = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E8 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E4 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_8C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_84 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_7C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_74 = 0;

    texture = ((S_800BC4D4_2 *)arg1)->unk_08;
    texture_height = ((S_800BC4D4_2 *)arg1)->unk_14;
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch_94 = scratch_init;
    ASM_KEEP_NV(scratch_94);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_800BC4D4_1 *)scratch)->unk_24 = texture_height;
    texture_x = ((S_800BC4D4_3 *)arg0)->unk_02;
    scratch_94 = (u8 *)((u32)scratch_94 | 0x94);
    ((S_800BC4D4_1 *)scratch)->unk_00 = texture_x;
    texture_y = ((S_800BC4D4_3 *)arg0)->unk_06;
    ASM_CLOBBER("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    global = (u8 **)(global_page + 0x3160);
    ((S_800BC4D4_1 *)scratch)->unk_02 = texture_y;
    ((S_800BC4D4_1 *)scratch)->unk_04 = arg2;

    projected = func_80065420(scratch_init, scratch_b8,
                              scratch_90, scratch_94);
    matrix = D_8006CD30;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = projected;
    ((S_800BC4D4_4 *)matrix)->unk_1C = projected * 4;
    projected_minus7 = projected - 7;
    index = projected_minus7 - arg3;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = index;

    if (index < 0x1E0U) {
        func_800649A0();

        screen_x = ((S_800BC4D4_1 *)scratch)->unk_B8;
        depth_coord = ((S_800BC4D4_1 *)scratch)->unk_04;
        ((S_800BC4D4_1 *)scratch)->unk_B8 = screen_x - 0xA0;
        ((S_800BC4D4_1 *)scratch)->unk_BA -= 0x78;
        depth = ((((S_800BC4D4_3 *)arg0)->unk_0A - (s16)depth_coord) << 5) + 0x1000;
        ((S_800BC4D4_1 *)scratch)->unk_38 = depth;
        if (depth < 0) {
            ((S_800BC4D4_1 *)scratch)->unk_38 = 0;
        }

        value = ((S_800BC4D4_1 *)scratch)->unk_38;
        ((S_800BC4D4_1 *)scratch)->unk_30.s = value;
        ((S_800BC4D4_1 *)scratch)->unk_34.s = (s32)(value + ((u32)value >> 31)) >> 1;
        func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
        texture_data = texture + 4;
        ASM_KEEP_NV(texture_data);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        packet_field = packet + 7;
        func_80064840(matrix, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);

        ((S_800BC4D4_1 *)scratch)->unk_30.u = ((S_800BC4D4_2 *)arg1)->unk_1C;
        ((S_800BC4D4_1 *)scratch)->unk_34.u = ((S_800BC4D4_2 *)arg1)->unk_1E;
        ((S_800BC4D4_1 *)scratch)->unk_38 = 0x1000;
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);

        for (;;) {
            if (!(texture[0] & 0x20)) {
                register s32 packet_zero ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                register s32 packet_zero2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u8 *packet_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                u32 texture4;
                u32 texture6;
                u32 texture7;

                packet_zero = 0;
                ASM_KEEP_NV(packet_zero);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                texture4 = texture_data[4];
                packet_arg = packet;
                ASM_KEEP_NV(packet_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                ((S_800BC4D4_1 *)scratch)->unk_08.u32 = texture4;
                ((S_800BC4D4_1 *)scratch)->unk_0C.u = texture_data[5];
                texture6 = texture_data[6];
                packet_zero2 = packet_zero;
                ((S_800BC4D4_1 *)scratch)->unk_10.u32 = texture6;
                texture7 = texture_data[7];
                packet_field += 0xC;
                ((S_800BC4D4_1 *)scratch)->unk_14.u32 = texture7;

                func_80067EF4(packet_arg, packet_zero, packet_zero2);
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet_next = packet + 0xC;
                packet = packet_next;

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 1) {
                    u32 tail_value;

                    coord_x = texture_data[-2];
                    tail_value = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ASM_KEEP_DEP_NV(coord_x, tail_value); /* MATCH: load the unsigned byte and extent before sign extension. */
                    coord_x = (s8)coord_x;
                    coord_x = -coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x -= tail_value;
                } else {
                    u32 tail_value;

                    coord_x = texture_data[-2];
                    tail_value = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ASM_KEEP_DEP_NV(coord_x, tail_value); /* MATCH: load the unsigned byte and extent before sign extension. */
                    coord_x = (s8)coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x += tail_value;
                }
                ((S_800BC4D4_1 *)scratch)->unk_88 = coord_x;
                ((S_800BC4D4_1 *)scratch)->unk_78.s = coord_x;

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 2) {
                    u32 tail_value;

                    coord_y = texture_data[-1];
                    tail_value = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ASM_KEEP_DEP_NV(coord_y, tail_value); /* MATCH: load the unsigned byte and extent before sign extension. */
                    coord_y = (s8)coord_y;
                    coord_y = -coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y -= tail_value;
                } else {
                    u32 tail_value;

                    coord_y = texture_data[-1];
                    tail_value = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ASM_KEEP_DEP_NV(coord_y, tail_value); /* MATCH: load the unsigned byte and extent before sign extension. */
                    coord_y = (s8)coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y += tail_value;
                }
                ((S_800BC4D4_1 *)scratch)->unk_8A = coord_y;
                ((S_800BC4D4_1 *)scratch)->unk_82 = coord_y;

                ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                {
                    s16 *call_a0 = (s16 *)(scratch + 0x70);
                    s16 *call_a1 = (s16 *)(scratch + 0x78);
                    register s16 *call_a2 ASM_REG("$6") = (s16 *)(scratch + 0x80);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register s16 *call_a3 ASM_REG("$7") = (s16 *)(scratch + 0x88);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    u16 call_x;
                    u16 call_y;

                    ASM_KEEP4_NV(call_a0, call_a1, call_a2, call_a3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    func_800654B0(call_a0, call_a1, call_a2, call_a3,
                                  (s16 *)(scratch + 0xF0), (s16 *)(scratch + 0xF4),
                                  (s16 *)(scratch + 0xF8), (s16 *)(scratch + 0xFC),
                                  (GeomTailArgs){(s16 *)(scratch + 0x90),
                                                 (s16 *)(scratch + 0x94)},
                                  (call_x = ((S_800BC4D4_1 *)scratch)->unk_70.u,
                                   KEEP_NV_EXPR(call_x),
                                   call_y = ((S_800BC4D4_1 *)scratch)->unk_78.u,
                                   call_x += 6,
                                   call_y += 6,
                                   KEEP_DEP_NV_EXPR(call_x, call_y),
                                   ((S_800BC4D4_1 *)scratch)->unk_70.u = call_x,
                                   ((S_800BC4D4_1 *)scratch)->unk_78.u = call_y,
                                   (GeomSideEffects){}));
                }

                (*(s16 *)((u8 *)packet_field + 1)) = ((S_800BC4D4_1 *)scratch)->unk_F0 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 3)) = ((S_800BC4D4_1 *)scratch)->unk_F2 + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 9)) = ((S_800BC4D4_1 *)scratch)->unk_F4 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 0xB)) = ((S_800BC4D4_1 *)scratch)->unk_F6 + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 0x11)) = ((S_800BC4D4_1 *)scratch)->unk_F8 + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)((u8 *)packet_field + 0x13)) = ((S_800BC4D4_1 *)scratch)->unk_FA + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)((u8 *)packet_field + 0x19)) = ((S_800BC4D4_1 *)scratch)->unk_FC + ((S_800BC4D4_1 *)scratch)->unk_B8;
                {
                    u16 final_value = ((S_800BC4D4_1 *)scratch)->unk_FE;
                    u16 final_base = ((S_800BC4D4_1 *)scratch)->unk_BA;

                    ((S_800BC4D4_5_pre *)packet_field)[-1].unk_00 = 9;
                    (*(s16 *)((u8 *)packet_field + 0x1B)) = final_value + final_base;
                }

                color_sum = ((S_800BC4D4_1 *)scratch)->unk_10.s32;
                color0 = ((S_800BC4D4_1 *)scratch)->unk_08.s32;
                ASM_KEEP_DEP_NV(color0, color_sum);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                color_mix = ((S_800BC4D4_1 *)scratch)->unk_0C.s;
                color1 = ((S_800BC4D4_1 *)scratch)->unk_14.s32;
                color_sum += color0;
                color_mix += color1;
                ((S_800BC4D4_1 *)scratch)->unk_10.s32 = color_sum;
                color_sum = ((S_800BC4D4_1 *)scratch)->unk_0C.s;
                color_mix <<= 8;
                ((S_800BC4D4_1 *)scratch)->unk_14.s32 = color_mix;
                color_sum <<= 8;
                ((S_800BC4D4_1 *)scratch)->unk_0C.s = color_sum;
                shifted = color_sum;
                shifted += color0;

                {
                    register u32 tail_page ASM_REG("$2"); /* MATCH: both page choices feed v0 in the shared addition. */

                    if (((S_800BC4D4_6 *)texture_data)->unk_00 & 0x80) {
                        ASM_SCHED_BARRIER(); /* MATCH: keep page materialization after the guard. */
                        tail_page = 0x7F800000;
                    } else {
                        ASM_SCHED_BARRIER(); /* MATCH: keep page materialization after the guard. */
                        tail_page = 0x7FC00000;
                    }
                    ASM_KEEP(tail_page); /* MATCH: keep one shared addition after page selection. */
                    shifted += tail_page;
                }
                (*(s32 *)((u8 *)packet_field + 5)) = shifted;
                (*(s32 *)((u8 *)packet_field + 0xD)) = ((S_800BC4D4_1 *)scratch)->unk_0C.s +
                                                      ((S_800BC4D4_1 *)scratch)->unk_10.s32 +
                                                      ((s16)((S_800BC4D4_6 *)texture_data)->unk_00 << 16);
                {
                    s32 first_x;
                    s32 first_add;
                    s32 first_y;

                    first_x = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    first_add = ((S_800BC4D4_1 *)scratch)->unk_08.u16;
                    first_y = (*(s16 *)((u8 *)packet_field + 1));
                    first_x += first_add;
                    (*(s16 *)((u8 *)packet_field + 0x15)) = first_x;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    {
                        s32 second_x;
                        s32 second_add;
                        register s32 last_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                        second_x = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                        second_add = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                        last_x = (*(s16 *)((u8 *)packet_field + 0x19));
                        second_x += second_add;
                        (*(s16 *)((u8 *)packet_field + 0x1D)) = second_x;

                        if (last_x < first_y) {
                            ((S_800BC4D4_5 *)packet_field)->unk_0D--;
                            ((S_800BC4D4_5 *)packet_field)->unk_1D--;
                        }
                    }
                }
                if ((*(s16 *)((u8 *)packet_field + 3)) > (*(s16 *)((u8 *)packet_field + 0x1B))) {
                    ((S_800BC4D4_5 *)packet_field)->unk_16--;
                    ((S_800BC4D4_5 *)packet_field)->unk_1E--;
                }

                (*(s32 *)((u8 *)packet_field + -3)) = ((S_800BC4D4_2 *)arg1)->unk_0C;
                ((S_800BC4D4_5 *)packet_field)->unk_00 = 0x2E;
                packet_field += 0x28;
                ASM_KEEP_NV(packet_field);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                packet_field += 0xC;
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet += 0x28;
                func_80067EF4(packet, 1, 0);
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                                  ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet += 0xC;
            }

            texture_data += 0xC;
            if ((s8)texture[0] >= 0) {
                ASM_KEEP(packet_field);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(texture_data);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                texture += 0xC;
                continue;
            }
            break;
        }
        func_80064A40();
    }

    ((S_800BC4D4_7 *)(*global))->unk_8D0 = packet;
}
