#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8004BDDC_0 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u16 v; } at02; } unk_18;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    u8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_28;   /* overlapping accesses */
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_8004BDDC_0;   /* arg2 in func_8004BDDC */

typedef struct S_8004BDDC_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004BDDC_1;   /* arg4 in func_8004BDDC */

typedef struct S_8004BDDC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8004BDDC_2;   /* temp_s3 in func_8004BDDC */


M2C_UNK func_8004C010();                 /* extern */

/* Build a textured Gouraud quad packet with tinted vertex colors and adjusted UV bounds. */
void *func_8004BDDC(s32 tint_a, s32 tint_b, void *packet, void *record, void *command) {
    register void *color_record ASM_REG("$19");   /* MATCH pin: slus-diff */
    s8 u_end;
    s8 v_end;
    u8 u_span;
    u8 v_span;
    void *color_1;
    void *color_2;
    void *color_3;
    void *color_0;

    ((S_8004BDDC_0 *)packet)->unk_2C = (s32) ((S_8004BDDC_0 *)packet)->unk_20.at00.v;
    ((S_8004BDDC_0 *)packet)->unk_20.at00.v = (s32) ((S_8004BDDC_0 *)packet)->unk_18.at00.v;
    ((S_8004BDDC_0 *)packet)->unk_14.at00.v = (s32) ((S_8004BDDC_0 *)packet)->unk_10.at00.v;
    color_record = record;
    {
        u8 u_start = *(volatile u8 *) ((u8 *) command + 8);
        u_span = *(volatile u8 *) ((u8 *) command + 0xA);
        if ((u_span + u_start) >= 0x100) {
            ((S_8004BDDC_1 *)command)->unk_0A = (u8) (u_span - 1);
        }
    }
    {
        u8 v_start = *(volatile u8 *) ((u8 *) command + 9);
        v_span = *(volatile u8 *) ((u8 *) command + 0xB);
        if ((v_span + v_start) >= 0x100) {
            ((S_8004BDDC_1 *)command)->unk_0B = (u8) (v_span - 1);
        }
    }
    color_record = (void *) ((u8 *) color_record + 0xC);
    color_1 = packet + 0x10;
    ((S_8004BDDC_0 *)packet)->unk_10.at00.v = (s32) ((S_8004BDDC_2 *)color_record)->unk_00;
    ((S_8004BDDC_0 *)packet)->unk_04 = (u8) ((S_8004BDDC_0 *)packet)->unk_10.at03.v;
    func_8004C010(color_1, tint_a);
    func_8004C010(color_1, tint_b);
    color_2 = packet + 0x1C;
    ((S_8004BDDC_0 *)packet)->unk_1C.at00.v = (s32) ((S_8004BDDC_2 *)color_record)->unk_04;
    ((S_8004BDDC_0 *)packet)->unk_05 = (u8) ((S_8004BDDC_0 *)packet)->unk_1C.at03.v;
    func_8004C010(color_2, tint_a);
    func_8004C010(color_2, tint_b);
    color_3 = packet + 0x28;
    ((S_8004BDDC_0 *)packet)->unk_28.at00.v = (s32) ((S_8004BDDC_2 *)color_record)->unk_08;
    ((S_8004BDDC_0 *)packet)->unk_06 = (u8) ((S_8004BDDC_0 *)packet)->unk_28.at03.v;
    func_8004C010(color_3, tint_a);
    func_8004C010(color_3, tint_b);
    color_0 = packet + 4;
    func_8004C010(color_0, tint_a);
    func_8004C010(color_0, tint_b);
    ((S_8004BDDC_0 *)packet)->unk_03 = 0xC;
    ((S_8004BDDC_0 *)packet)->unk_07 = (u8) ((S_8004BDDC_1 *)command)->unk_01;
    ((S_8004BDDC_0 *)packet)->unk_0C = (u8) ((S_8004BDDC_1 *)command)->unk_08;
    ((S_8004BDDC_0 *)packet)->unk_0E = (u16) ((S_8004BDDC_1 *)command)->unk_06;
    ((S_8004BDDC_0 *)packet)->unk_0D = (u8) ((S_8004BDDC_1 *)command)->unk_09;
    if ((((S_8004BDDC_0 *)packet)->unk_14.at00u.v < ((S_8004BDDC_0 *)packet)->unk_08) ||
        (((S_8004BDDC_0 *)packet)->unk_08 != ((S_8004BDDC_0 *)packet)->unk_20.at00u.v)) {
        ((S_8004BDDC_1 *)command)->unk_0A = (u8) (((S_8004BDDC_1 *)command)->unk_0A - 1);
    }
    u_end = ((S_8004BDDC_1 *)command)->unk_08 + ((S_8004BDDC_1 *)command)->unk_0A;
    ((S_8004BDDC_0 *)packet)->unk_30 = u_end;
    ((S_8004BDDC_0 *)packet)->unk_18.at00u.v = u_end;
    ((S_8004BDDC_0 *)packet)->unk_18.at01.v = (u8) ((S_8004BDDC_1 *)command)->unk_09;
    ((S_8004BDDC_0 *)packet)->unk_18.at02.v = (u16) ((S_8004BDDC_1 *)command)->unk_04;
    ((S_8004BDDC_0 *)packet)->unk_24 = (u8) ((S_8004BDDC_1 *)command)->unk_08;
    if ((((S_8004BDDC_0 *)packet)->unk_20.at02.v < ((S_8004BDDC_0 *)packet)->unk_0A) ||
        (((S_8004BDDC_0 *)packet)->unk_0A != ((S_8004BDDC_0 *)packet)->unk_14.at02.v)) {
        ((S_8004BDDC_1 *)command)->unk_0B = (u8) (((S_8004BDDC_1 *)command)->unk_0B - 1);
    }
    v_end = ((S_8004BDDC_1 *)command)->unk_09 + ((S_8004BDDC_1 *)command)->unk_0B;
    ((S_8004BDDC_0 *)packet)->unk_31 = v_end;
    ((S_8004BDDC_0 *)packet)->unk_25 = v_end;
    return color_record;
}
