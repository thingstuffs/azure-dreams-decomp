#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {} EmptyArg;

extern void func_800242C8(void) __attribute__((noreturn));
extern void func_8002458C(void) __attribute__((noreturn));
extern void func_80024594(void) __attribute__((noreturn));
extern void func_800245E4(void) __attribute__((noreturn));
extern void func_80024854(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, EmptyArg);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern u8 D_80083150[];
extern u8 D_80083160_quad[] __asm__("D_80083160");
extern u8 D_80083160_line[] __asm__("D_80083160");
extern u8 D_80083160_tpage[] __asm__("D_80083160");
void func_8187A9A8(void *arg0, void *arg1, void *arg2, s32 arg3)
{
    register u8 *entry_value ASM_REG("$2");
    u8 *page_color;
    register u8 *mesh ASM_REG("$18") = arg0;
    register u8 *object ASM_REG("$20") = arg2;
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;
    register s32 raw_depth ASM_REG("$16");
    register u8 *texture ASM_REG("$22");
    register u8 *texture_data ASM_REG("$19");
    register u32 low_mask ASM_REG("$21");
    u32 high_mask;
    s32 depth;
    u16 object_flags;
    MATRIX matrix;

    entry_value = *(u8 **)(D_80083150 + 0x10);
    ASM_KEEP_MEMDEP(entry_value, page_color, *(u8 **)(D_80083150 + 0x10));
    ASM_KEEP(mesh);
    ASM_KEEP(object);
    FIELD(scratch, u8 *, 0x24) = entry_value + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    raw_depth = arg3;
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    low_mask = 0x00FFFFFF;
    object_flags = FIELD(object, u16, 0x14);
    object_flags |= 0x8000;
    high_mask = 0xFF000000;
    ASM_USE_NV(high_mask);
    FIELD(object, u16, 0x14) = object_flags;

    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(object, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(object, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(object, u16, 0x18);
    func_80065820((u8 *)0x1F8000A4, (u8 *)0x1F800074);
    func_80064AE0(&matrix);
    func_80064840(&matrix, (u8 *)0x1F800074, (u8 *)0x1F800054);
    func_80064BC0((u8 *)0x1F800054, (u8 *)0x1F800034);
    func_80064D80((u8 *)0x1F800054);
    func_80064CF0((u8 *)0x1F800054);
    ASM_KEEP(scratch);

    ASM_KEEP(raw_depth);
    depth = (s16)raw_depth;
    texture = FIELD(object, u8 *, 8);
    texture_data = texture + 1;
    FIELD(scratch, u16, 0x28) = FIELD(object, u16, 0x14);
    ASM_KEEP(texture);

    if (FIELD(mesh, u8, 0x4E) != 0) {
        register u8 *packet ASM_REG("$16");
        s32 index;
        register u16 flags ASM_REG("$3");
        register u8 tex_flags ASM_REG("$4");
        s32 adjust;
        u8 *state;
        register u8 **state_ref ASM_REG("$10");

        state_ref = (u8 **)D_80083160_quad;
        ASM_KEEP(state_ref);
        state = *state_ref;
        packet = FIELD(state, u8 *, 0x8D0);
        ASM_KEEP(packet);
        FIELD(state, u8 *, 0x8D0) = packet + 0x28;

        FIELD(scratch, s32, 0x0C) = texture_data[7];
        FIELD(scratch, s32, 0x10) = texture_data[8];
        FIELD(scratch, s32, 0x14) = texture_data[9];
        FIELD(scratch, s32, 0x18) = texture_data[0xA];

        FIELD(scratch, u16, 0xB0) = FIELD(mesh, u16, 0x58);
        FIELD(scratch, u16, 0xB8) = FIELD(mesh, u16, 0x5A);
        FIELD(scratch, u16, 0xC0) = FIELD(mesh, u16, 0x5C);
        FIELD(scratch, u16, 0xC8) = FIELD(mesh, u16, 0x5E);
        FIELD(scratch, u16, 0xB2) = FIELD(mesh, u16, 0x60);
        FIELD(scratch, u16, 0xBA) = FIELD(mesh, u16, 0x62);
        FIELD(scratch, u16, 0xC2) = FIELD(mesh, u16, 0x64);
        FIELD(scratch, u16, 0xCA) = FIELD(mesh, u16, 0x66);
        FIELD(scratch, u16, 0xB4) = FIELD(mesh, u16, 0x68);
        FIELD(scratch, u16, 0xBC) = FIELD(mesh, u16, 0x6A);
        FIELD(scratch, u16, 0xC4) = FIELD(mesh, u16, 0x6C);
        FIELD(scratch, u16, 0xCC) = FIELD(mesh, u16, 0x6E);

        index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0x10,
                              packet + 0x18, packet + 0x20,
                              scratch + 0xD0, scratch + 0xD4,
                              ({ EmptyArg empty; empty; })) - depth - 6;
        FIELD(scratch, s32, 0x100) = index;

        if ((u32)index < 0x1E0 &&
            ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121)) |
             (((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181) &&
              ((u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121)))) {
            FIELD(packet, u8, 3) = 9;
            FIELD(packet, u8, 7) = 0x2C;
            FIELD(object, u16, 0x14) &= 0x7FFF;

            FIELD(scratch, s32, 0x14) += FIELD(scratch, s32, 0x0C);
            if (FIELD(scratch, s32, 0x14) & 0x100) {
                FIELD(scratch, s32, 0x14)--;
            }
            FIELD(scratch, s32, 0x18) += FIELD(scratch, s32, 0x10);
            if (FIELD(scratch, s32, 0x18) & 0x100) {
                FIELD(scratch, s32, 0x18)--;
            }
            FIELD(scratch, s32, 0x10) <<= 8;
            FIELD(scratch, s32, 0x18) <<= 8;

            adjust = FIELD(object, u16, 0x12);
            if (adjust != 0) {
                if (FIELD(scratch, u16, 0x28) & 0x100) {
                    FIELD(packet, u16, 0x0E) = adjust;
                    func_80024594();
                }
                {
                    register u32 helper_value ASM_REG("$2");
                    helper_value = adjust + FIELD(texture_data, u16, 5);
                    ASM_TAILSLOT_PIN(helper_value);
                    func_8002458C();
                }
            }
            FIELD(packet, u16, 0x0E) = FIELD(texture_data, u16, 5);

            FIELD(packet, u16, 0x0C) = FIELD(scratch, u16, 0x10) +
                                       FIELD(scratch, u16, 0x0C);
            FIELD(packet, u16, 0x14) = FIELD(scratch, u16, 0x10) +
                                       FIELD(scratch, u16, 0x14);

            adjust = FIELD(object, u16, 0x10);
            if (adjust != 0) {
                register u32 helper_value ASM_REG("$2");
                helper_value = adjust +
                    (FIELD(texture_data, u16, 3) & 0xFF9F);
                ASM_TAILSLOT_PIN(helper_value);
                func_800245E4();
            }
            FIELD(packet, u16, 0x16) = FIELD(texture_data, u16, 3);

            FIELD(packet, u16, 0x1C) = FIELD(scratch, u16, 0x18) +
                                       FIELD(scratch, u16, 0x0C);
            FIELD(packet, u16, 0x24) = FIELD(scratch, u16, 0x18) +
                                       FIELD(scratch, u16, 0x14);

            if (FIELD(packet, s16, 8) > FIELD(packet, s16, 0x20)) {
                FIELD(packet, u8, 0x14)--;
                FIELD(packet, u8, 0x24)--;
            }
            if (FIELD(packet, s16, 0x0A) > FIELD(packet, s16, 0x22)) {
                FIELD(packet, u8, 0x1D)--;
                FIELD(packet, u8, 0x25)--;
            }

            tex_flags = texture_data[0];
            FIELD(object, u8, 0x0F) = tex_flags;
            flags = FIELD(scratch, u16, 0x28);
            if (flags & 8) {
                FIELD(object, u8, 0x0F) = (flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }
            ASM_KEEP(flags);
            ASM_KEEP(tex_flags);

            FIELD(packet, u32, 4) = FIELD(object, u32, 0x0C);
            FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & high_mask) |
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & low_mask);
            FIELD(FIELD(scratch, u32 *, 0x24), u32,
                  FIELD(scratch, s32, 0x100) * 4) =
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & high_mask) |
                ((u32)packet & low_mask);
            ASM_KEEP(packet);
        }
    }

    if (FIELD(mesh, u8, 0x4E) == 0) {
        register u8 *packet ASM_REG("$16");
        s32 index;
        s32 average;
        s32 final_average;
        s32 lhs;
        s32 rhs;
        register s32 final_lhs ASM_REG("$3");
        register s32 final_rhs ASM_REG("$9");
        u16 flags;
        u8 *call0;
        u8 *call1;
        u8 *call2;
        u8 *call3;
        register u8 *call4 ASM_REG("$8");
        u8 *call5;
        u8 *call6;
        u8 *call7;
        register s32 call_a0 ASM_REG("$4");
        register s32 call_a1 ASM_REG("$5");
        register u32 *table_entry ASM_REG("$6");
        u32 packet_word;
        register s32 packet_code ASM_REG("$2");
        register u8 *state ASM_REG("$3");
        register u8 **state_ref ASM_REG("$10");

        state_ref = (u8 **)D_80083160_line;
        ASM_KEEP(state_ref);
        state = *state_ref;
        ASM_KEEP(state);
        packet = FIELD(state, u8 *, 0x8D0);
        ASM_KEEP(packet);
        FIELD(state, u8 *, 0x8D0) = packet + 0x10;

        lhs = FIELD(mesh, s16, 0x58);
        rhs = FIELD(mesh, s16, 0x5C);
        ASM_KEEP(lhs);
        ASM_KEEP(rhs);
        call0 = scratch + 0xB0;
        ASM_KEEP(call0);
        average = (lhs + rhs) / 2;
        FIELD(scratch, s16, 0xC0) = average;
        FIELD(scratch, s16, 0xB0) = average;
        lhs = FIELD(mesh, s16, 0x5A);
        rhs = FIELD(mesh, s16, 0x5E);
        ASM_KEEP(lhs);
        ASM_KEEP(rhs);
        call1 = scratch + 0xB8;
        ASM_KEEP(call1);
        average = (lhs + rhs) / 2;
        FIELD(scratch, s16, 0xC8) = average;
        FIELD(scratch, s16, 0xB8) = average;
        lhs = FIELD(mesh, s16, 0x60);
        rhs = FIELD(mesh, s16, 0x64);
        ASM_KEEP(lhs);
        ASM_KEEP(rhs);
        call2 = scratch + 0xC0;
        ASM_KEEP(call2);
        average = (lhs + rhs) / 2;
        FIELD(scratch, s16, 0xC2) = average;
        FIELD(scratch, s16, 0xB2) = average;
        lhs = FIELD(mesh, s16, 0x62);
        rhs = FIELD(mesh, s16, 0x66);
        ASM_KEEP(lhs);
        ASM_KEEP(rhs);
        call3 = scratch + 0xC8;
        ASM_KEEP(call3);
        average = (lhs + rhs) / 2;
        FIELD(scratch, s16, 0xCA) = average;
        FIELD(scratch, s16, 0xBA) = average;
        lhs = FIELD(mesh, s16, 0x68);
        rhs = FIELD(mesh, s16, 0x6C);
        ASM_KEEP(lhs);
        ASM_KEEP(rhs);
        call4 = packet + 8;
        ASM_KEEP_NV(call4);
        average = (lhs + rhs) / 2;
        FIELD(scratch, s16, 0xC4) = average;
        FIELD(scratch, s16, 0xB4) = average;
        final_lhs = FIELD(mesh, s16, 0x6A);
        final_rhs = FIELD(mesh, s16, 0x6E);
        call5 = packet + 0x0C;
        call6 = scratch + 0xD0;
        call7 = scratch + 0xD4;

        index = func_80065590(call0, call1,
                              call2, call3,
                              call4, call5,
                              call4, call5,
                              call6, call7,
                              ({
                                  EmptyArg empty;
                                  final_average = (final_lhs + final_rhs) / 2;
                                  FIELD(scratch, s16, 0xCC) = final_average;
                                  ASM_JALDELAY_PIN(final_average);
                                  FIELD(scratch, s16, 0xBC) = final_average;
                                  empty;
                              })) - depth - 6;
        FIELD(scratch, s32, 0x100) = index;

        flags = FIELD(scratch, u16, 0x28);
        if (flags & 8) {
            if (flags & 4) {
                register u32 helper_value ASM_REG("$2");
                helper_value = FIELD(object, u8, 0x0F) | 2;
                ASM_TAILSLOT_PIN(helper_value);
                func_80024854();
            }
            FIELD(object, u8, 0x0F) &= 0xFD;
        }

        call_a0 = 0;
        packet_word = FIELD(object, u32, 0x0C);
        FIELD(packet, u8, 3) = 3;
        ASM_SET(packet_code);
        packet_code = 0x42;
        ASM_KEEP(packet_word);
        ASM_KEEP(packet_code);
        ASM_SCHED_BARRIER();
        call_a1 = 1;
        state_ref = (u8 **)D_80083160_tpage;
        ASM_KEEP(state_ref);
        FIELD(packet, u32, 4) = packet_word;
        FIELD(packet, u8, 7) = packet_code;

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & high_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & low_mask);
        table_entry = (u32 *)
            (((u32)FIELD(scratch, s32, 0x100) << 2) +
             (u32)FIELD(scratch, u32 *, 0x24));
        ASM_KEEP(table_entry);
        {
            register u32 table_word ASM_REG("$3");
            register u32 packet_low ASM_REG("$2");

            table_word = *table_entry;
            packet_low = (u32)packet & low_mask;
            table_word &= high_mask;
            table_word |= packet_low;
            *table_entry = table_word;
        }

        state = *state_ref;
        packet = FIELD(state, u8 *, 0x8D0);
        FIELD(state, u8 *, 0x8D0) = packet + 0x0C;
        func_80067F20(packet, 0, 0,
                     func_80066460(call_a0, call_a1,
                                   call_a0, call_a0) & 0xFFFF, 0);

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & high_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & low_mask);
        FIELD(FIELD(scratch, u32 *, 0x24), u32,
              FIELD(scratch, s32, 0x100) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & high_mask) |
            ((u32)packet & low_mask);
    }

    ASM_KEEP(low_mask);
    if ((s8)*texture >= 0) {
        texture_data += 0x0C;
        ASM_KEEP(texture_data);
        texture += 0x0C;
        ASM_TAILSLOT_PIN(texture);
        func_800242C8();
    }
    func_80064A40();
}
