#include "common.h"

typedef struct S_8004C080_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004C080_0;   /* command in func_8004C080 */

typedef struct S_8004C080_1 {
    u8 pad_00[0x3];
    s8 unk_03;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} S_8004C080_1;   /* packet in func_8004C080 */

typedef struct S_8004C080_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8004C080_2;   /* record in func_8004C080 */



typedef struct Tint8004C080 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} Tint8004C080;

extern s32 func_8004C010(u8 *dst, Tint8004C080 *tint);
extern void *func_8004BDDC(Tint8004C080 *tint0, Tint8004C080 *tint1,
                           u8 *packet, void *record, u8 *command);
extern void SetTexWindow(void *packet, s16 *values);
extern void SetDrawMode(void *packet, s32 a1, s32 a2, s32 a3, s32 a4);
extern void *func_8004B954(Tint8004C080 *tint0, Tint8004C080 *tint1,
                           u8 *packet, void *record, u8 *command,
                           s32 *count, s32 mode);

void *func_8004C080(Tint8004C080 *tint0, Tint8004C080 *tint1,
                    u8 *packet, void *record, u8 *command, s32 *count)
{
    u8 code;
    s32 group;
    s32 sub;
    s32 group2;
    u8 *color;
    s16 values[4];

    code = ((S_8004C080_0 *)command)->unk_01;
    group = code & 0xFC;

    if (group == 0x28) {
        color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        ((S_8004C080_1 *)packet)->unk_03 = 5;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_1 *)packet)->unk_10;
        ((S_8004C080_1 *)packet)->unk_10 = ((S_8004C080_1 *)packet)->unk_18;
        ((S_8004C080_1 *)packet)->unk_14 = ((S_8004C080_1 *)packet)->unk_20;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        goto done;
    }

    if (group == 0x48) {
        color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        ((S_8004C080_1 *)packet)->unk_03 = 5;
        ((S_8004C080_1 *)packet)->unk_14 = 0x55555555;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        ((S_8004C080_1 *)packet)->unk_08 = ((S_8004C080_1 *)packet)->unk_10;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_1 *)packet)->unk_20;
        ((S_8004C080_1 *)packet)->unk_10 = ((S_8004C080_1 *)packet)->unk_18;
        goto done;
    }

    if (group == 0x38) {
        color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        record = (u8 *)record + 0xC;
        sub = 8;
        color = packet + 0xC;
        ((S_8004C080_1 *)packet)->unk_03 = sub;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = group;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_2 *)record)->unk_00;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        color = packet + 0x14;
        ((S_8004C080_1 *)packet)->unk_14 = ((S_8004C080_2 *)record)->unk_04;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        color = packet + 0x1C;
        ((S_8004C080_1 *)packet)->unk_1C = ((S_8004C080_2 *)record)->unk_08;
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        goto done;
    }

    if (group == 0x3C) {
        record = func_8004BDDC(tint0, tint1, packet, record, command);
        goto done;
    }

    if (!(code & 0x80)) {
        goto done;
    }

    sub = code & 0x7F;
    if (sub == 0) {
        values[0] = ((S_8004C080_0 *)command)->unk_08;
        values[1] = ((S_8004C080_0 *)command)->unk_09;
        values[2] = ((S_8004C080_0 *)command)->unk_0A + 1;
        values[3] = ((S_8004C080_0 *)command)->unk_0B + 1;
        SetTexWindow(packet, values);
        goto done;
    }

    group2 = sub & 0x7C;
    if (sub == 1) {
        SetDrawMode(packet, 1, ((S_8004C080_0 *)command)->unk_04.at02.v,
                      ((S_8004C080_0 *)command)->unk_04.at00u.v, 0);
        goto done;
    }

    if (group2 == 0x30) {
        record = func_8004B954(tint0, tint1, packet, record, command, count, 1);
        goto done;
    }
    if (group2 == 0x20) {
        record = func_8004B954(tint0, tint1, packet, record, command, count, 0);
    }
done:
    return record;
}
