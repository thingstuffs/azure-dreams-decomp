#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
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
extern void func_800BC69C(void);
extern void func_800BC758(void);
extern void func_800BC7BC(void);
extern void func_800BC914(s32, s32);
extern u8 D_8006CD30[];
extern u8 D_80083160[];

#ifdef NON_MATCHING
#define GLOBAL_PAGE_8008 (D_80083160 - 0x3160)
#else
#define GLOBAL_PAGE_8008 ((u8 *)0x80080000)
#endif

void func_800BC4D4(void *arg0, void *arg1, u16 arg2, s32 arg3)
{
    register u8 *scratch_init ASM_REG("$4") = (u8 *)0x1F800000;
    register u8 *scratch_b8 ASM_REG("$5") = scratch_init;
    register u8 *scratch_90 ASM_REG("$6");
    register u8 *scratch_94 ASM_REG("$7");
    register u8 *scratch ASM_REG("$17");
    register u8 *global_page ASM_REG("$3");
    register u8 **global ASM_REG("$23");
    register u8 *page_color ASM_REG("$2");
    u8 *matrix;
    u8 *packet;
    u8 *packet_next;
    u8 *texture;
    u8 *texture_data;
    u8 *packet_field;
    register u8 *root ASM_REG("$2");
    u32 projected;
    u32 projected_minus7;
    u32 index;
    s32 depth;
    s32 value;
    s32 color0;
    s32 color1;
    s32 shifted;
    register s32 color_sum ASM_REG("$3");
    register s32 color_mix ASM_REG("$2");
    s16 coord_x;
    s16 coord_y;
    u16 screen_x;
    u16 depth_coord;
    u16 texture_height;
    u16 texture_x;
    u16 texture_y;

    ASM_KEEP_NV(scratch_init);
    ASM_KEEP_NV(scratch_b8);
    scratch_b8 = (u8 *)((u32)scratch_b8 | 0xB8);
    ASM_KEEP_MEMDEP_NV(scratch_init, page_color, *(u8 **)D_80083160);
    scratch_90 = scratch_init;
    ASM_KEEP_NV(scratch_90);
    scratch = scratch_init;
    scratch_90 = (u8 *)((u32)scratch_90 | 0x90);
    root = *(u8 **)D_80083160;
    packet = FIELD(root, u8 *, 0x8D0);
    FIELD(scratch, u8 *, 0x20) = root + 0xB0;
#ifdef NON_MATCHING
    global_page = D_80083160 - 0x3160;
#else
    ASM_SET(global_page);
#endif
    FIELD(scratch, s32, 0xEC) = 0;
    FIELD(scratch, s32, 0xE8) = 0;
    FIELD(scratch, s32, 0xE4) = 0;
    FIELD(scratch, s16, 0x8C) = 0;
    FIELD(scratch, s16, 0x84) = 0;
    FIELD(scratch, s16, 0x7C) = 0;
    FIELD(scratch, s16, 0x74) = 0;

    texture = FIELD(arg1, u8 *, 8);
    texture_height = FIELD(arg1, u16, 0x14);
    ASM_CLOBBER("$7");
    scratch_94 = scratch_init;
    ASM_KEEP_NV(scratch_94);
    FIELD(scratch, u16, 0x24) = texture_height;
    texture_x = FIELD(arg0, u16, 2);
    ASM_SCHED_BARRIER();
    scratch_94 = (u8 *)((u32)scratch_94 | 0x94);
    ASM_SCHED_BARRIER();
    FIELD(scratch, u16, 0) = texture_x;
    texture_y = FIELD(arg0, u16, 6);
    ASM_CLOBBER("$23");
    global = (u8 **)(global_page + 0x3160);
    ASM_KEEP_NV(global);
    FIELD(scratch, u16, 2) = texture_y;
    FIELD(scratch, u16, 4) = arg2;

    projected = func_80065420(scratch_init, scratch_b8,
                              scratch_90, scratch_94);
    matrix = D_8006CD30;
    FIELD(scratch, u32, 0xC0) = projected;
    FIELD(matrix, s32, 0x1C) = projected * 4;
    projected_minus7 = projected - 7;
    index = projected_minus7 - arg3;
    FIELD(scratch, u32, 0xC0) = index;

    if (index < 0x1E0U) {
        func_800649A0();

        screen_x = FIELD(scratch, u16, 0xB8);
        depth_coord = FIELD(scratch, u16, 4);
        FIELD(scratch, u16, 0xB8) = screen_x - 0xA0;
        FIELD(scratch, u16, 0xBA) -= 0x78;
        depth = ((FIELD(arg0, s16, 0xA) - (s16)depth_coord) << 5) + 0x1000;
        FIELD(scratch, s32, 0x38) = depth;
        if (depth < 0) {
            FIELD(scratch, s32, 0x38) = 0;
        }

        value = FIELD(scratch, s32, 0x38);
        FIELD(scratch, s32, 0x30) = value;
        FIELD(scratch, s32, 0x34) = (s32)(value + ((u32)value >> 31)) >> 1;
        func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
        texture_data = texture + 4;
        ASM_KEEP_NV(texture_data);
        packet_field = packet + 7;
        ASM_KEEP_NV(packet_field);
        func_80064840(matrix, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);

        FIELD(scratch, u32, 0x30) = FIELD(arg1, u16, 0x1C);
        FIELD(scratch, u32, 0x34) = FIELD(arg1, u16, 0x1E);
        FIELD(scratch, s32, 0x38) = 0x1000;
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);

        if (!(texture[0] & 0x20)) {
            register s32 packet_zero ASM_REG("$5");
            register s32 packet_zero2 ASM_REG("$6");
            register u8 *packet_arg ASM_REG("$4");
            u32 texture4;
            u32 texture6;
            u32 texture7;

            packet_zero = 0;
            ASM_KEEP_NV(packet_zero);
            texture4 = texture_data[4];
            ASM_SCHED_BARRIER();
            packet_arg = packet;
            ASM_KEEP_NV(packet_arg);
            FIELD(scratch, u32, 8) = texture4;
            FIELD(scratch, u32, 0xC) = texture_data[5];
            texture6 = texture_data[6];
            ASM_SCHED_BARRIER();
            packet_zero2 = packet_zero;
            ASM_KEEP_NV(packet_zero2);
            FIELD(scratch, u32, 0x10) = texture6;
            texture7 = texture_data[7];
            ASM_SCHED_BARRIER();
            packet_field += 0xC;
            ASM_KEEP_NV(packet_field);
            FIELD(scratch, u32, 0x14) = texture7;

            func_80067EF4(packet_arg, packet_zero, packet_zero2);
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          packet);
            packet_next = packet + 0xC;
            packet = packet_next;

            if ((texture[0] ^ FIELD(scratch, u16, 0x24)) & 1) {
                register s16 tail_value ASM_REG("$2");

                tail_value = -(s8)texture_data[-2];
                ASM_KEEP_NV(tail_value);
                FIELD(scratch, s16, 0x80) = tail_value;
                FIELD(scratch, s16, 0x70) = tail_value;
                tail_value -= FIELD(scratch, u16, 0x10);
                ASM_TAILSLOT_PIN(tail_value);
                func_800BC758();
                return;
            }

            coord_x = (s8)texture_data[-2];
            FIELD(scratch, s16, 0x80) = coord_x;
            FIELD(scratch, s16, 0x70) = coord_x;
            coord_x += FIELD(scratch, u16, 0x10);
            FIELD(scratch, s16, 0x88) = coord_x;
            FIELD(scratch, s16, 0x78) = coord_x;

            if ((texture[0] ^ FIELD(scratch, u16, 0x24)) & 2) {
                register s16 tail_value ASM_REG("$2");

                tail_value = -(s8)texture_data[-1];
                ASM_KEEP_NV(tail_value);
                FIELD(scratch, s16, 0x7A) = tail_value;
                FIELD(scratch, s16, 0x72) = tail_value;
                tail_value -= FIELD(scratch, u16, 0x14);
                ASM_TAILSLOT_PIN(tail_value);
                func_800BC7BC();
                return;
            }

            coord_y = (s8)texture_data[-1];
            FIELD(scratch, s16, 0x7A) = coord_y;
            FIELD(scratch, s16, 0x72) = coord_y;
            coord_y += FIELD(scratch, u16, 0x14);
            FIELD(scratch, s16, 0x8A) = coord_y;
            FIELD(scratch, s16, 0x82) = coord_y;

            ASM_KEEP_NV(scratch);
            {
                register s16 *call_a0 ASM_REG("$4") = (s16 *)(scratch + 0x70);
                register s16 *call_a1 ASM_REG("$5") = (s16 *)(scratch + 0x78);
                register s16 *call_a2 ASM_REG("$6") = (s16 *)(scratch + 0x80);
                register s16 *call_a3 ASM_REG("$7") = (s16 *)(scratch + 0x88);
                u16 call_x;
                u16 call_y;

                ASM_KEEP4_NV(call_a0, call_a1, call_a2, call_a3);
                func_800654B0(call_a0, call_a1, call_a2, call_a3,
                              (s16 *)(scratch + 0xF0), (s16 *)(scratch + 0xF4),
                              (s16 *)(scratch + 0xF8), (s16 *)(scratch + 0xFC),
                              (GeomTailArgs){(s16 *)(scratch + 0x90),
                                             (s16 *)(scratch + 0x94)},
                              (call_x = FIELD(scratch, u16, 0x70),
                               KEEP_NV_EXPR(call_x),
                               call_y = FIELD(scratch, u16, 0x78),
                               call_x += 6,
                               call_y += 6,
                               KEEP_DEP_NV_EXPR(call_x, call_y),
                               FIELD(scratch, u16, 0x70) = call_x,
                               FIELD(scratch, u16, 0x78) = call_y,
                               (GeomSideEffects){}));
            }

            FIELD(packet_field, s16, 1) = FIELD(scratch, u16, 0xF0) + FIELD(scratch, u16, 0xB8);
            FIELD(packet_field, s16, 3) = FIELD(scratch, u16, 0xF2) + FIELD(scratch, u16, 0xBA);
            FIELD(packet_field, s16, 9) = FIELD(scratch, u16, 0xF4) + FIELD(scratch, u16, 0xB8);
            FIELD(packet_field, s16, 0xB) = FIELD(scratch, u16, 0xF6) + FIELD(scratch, u16, 0xBA);
            FIELD(packet_field, s16, 0x11) = FIELD(scratch, u16, 0xF8) + FIELD(scratch, u16, 0xB8);
            FIELD(packet_field, s16, 0x13) = FIELD(scratch, u16, 0xFA) + FIELD(scratch, u16, 0xBA);
            FIELD(packet_field, s16, 0x19) = FIELD(scratch, u16, 0xFC) + FIELD(scratch, u16, 0xB8);
            {
                u16 final_value = FIELD(scratch, u16, 0xFE);
                u16 final_base = FIELD(scratch, u16, 0xBA);

                FIELD(packet_field, s8, -4) = 9;
                FIELD(packet_field, s16, 0x1B) = final_value + final_base;
            }

            color_sum = FIELD(scratch, s32, 0x10);
            color0 = FIELD(scratch, s32, 8);
            ASM_KEEP_DEP_NV(color0, color_sum);
            color_mix = FIELD(scratch, s32, 0xC);
            color1 = FIELD(scratch, s32, 0x14);
            color_sum += color0;
            color_mix += color1;
            FIELD(scratch, s32, 0x10) = color_sum;
            color_sum = FIELD(scratch, s32, 0xC);
            color_mix <<= 8;
            FIELD(scratch, s32, 0x14) = color_mix;
            color_sum <<= 8;
            FIELD(scratch, s32, 0xC) = color_sum;
            shifted = color_sum;
            shifted += color0;

            if (FIELD(texture_data, u16, 0) & 0x80) {
                register u32 tail_page ASM_REG("$2") = 0x7F800000;

                ASM_PAGEBASE_PIN(tail_page);
                func_800BC914(color0, color1);
                return;
            }

            shifted += 0x7FC00000;
            FIELD(packet_field, s32, 5) = shifted;
            FIELD(packet_field, s32, 0xD) = FIELD(scratch, s32, 0xC) +
                                                  FIELD(scratch, s32, 0x10) +
                                                  ((s16)FIELD(texture_data, u16, 0) << 16);
            {
                register s32 first_x ASM_REG("$2");
                register s32 first_add ASM_REG("$3");
                register s32 first_y ASM_REG("$5");

                first_x = FIELD(scratch, u16, 0x14);
                first_add = FIELD(scratch, u16, 8);
                first_y = FIELD(packet_field, s16, 1);
                first_x += first_add;
                FIELD(packet_field, s16, 0x15) = first_x;
                ASM_SCHED_BARRIER();
                {
                    register s32 second_x ASM_REG("$3");
                    register s32 second_add ASM_REG("$4");
                    register s32 last_x ASM_REG("$2");

                    second_x = FIELD(scratch, u16, 0x14);
                    second_add = FIELD(scratch, u16, 0x10);
                    last_x = FIELD(packet_field, s16, 0x19);
                    second_x += second_add;
                    FIELD(packet_field, s16, 0x1D) = second_x;

                    if (last_x < first_y) {
                        FIELD(packet_field, u8, 0xD)--;
                        FIELD(packet_field, u8, 0x1D)--;
                    }
                }
            }
            if (FIELD(packet_field, s16, 3) > FIELD(packet_field, s16, 0x1B)) {
                FIELD(packet_field, u8, 0x16)--;
                FIELD(packet_field, u8, 0x1E)--;
            }

            FIELD(packet_field, s32, -3) = FIELD(arg1, s32, 0xC);
            FIELD(packet_field, u8, 0) = 0x2E;
            packet_field += 0x28;
            ASM_KEEP_NV(packet_field);
            packet_field += 0xC;
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          packet);
            packet += 0x28;
            func_80067EF4(packet, 1, 0);
            func_8006658C(FIELD(scratch, u8 *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          packet);
            packet += 0xC;
        }

        texture_data += 0xC;
        if ((s8)texture[0] >= 0) {
            ASM_KEEP(packet_field);
            ASM_KEEP(texture_data);
            texture += 0xC;
            ASM_TAILSLOT_PIN(texture);
            func_800BC69C();
            return;
        }
        func_80064A40();
    }

    FIELD(*global, u8 *, 0x8D0) = packet;
}
