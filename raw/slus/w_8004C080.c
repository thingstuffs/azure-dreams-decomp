#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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

    code = FIELD(command, u8, 1);
    group = code & 0xFC;

    if (group == 0x28) {
        color = packet + 4;
        FIELD(packet, s32, 4) = FIELD(command, s32, 4);
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        FIELD(packet, s8, 3) = 5;
        FIELD(packet, s32, 0xC) = FIELD(packet, s32, 0x10);
        FIELD(packet, s32, 0x10) = FIELD(packet, s32, 0x18);
        FIELD(packet, s32, 0x14) = FIELD(packet, s32, 0x20);
        FIELD(packet, u8, 7) = FIELD(command, u8, 1);
        goto done;
    }

    if (group == 0x48) {
        color = packet + 4;
        FIELD(packet, s32, 4) = FIELD(command, s32, 4);
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        FIELD(packet, s8, 3) = 5;
        FIELD(packet, s32, 0x14) = 0x55555555;
        FIELD(packet, u8, 7) = FIELD(command, u8, 1);
        FIELD(packet, s32, 8) = FIELD(packet, s32, 0x10);
        FIELD(packet, s32, 0xC) = FIELD(packet, s32, 0x20);
        FIELD(packet, s32, 0x10) = FIELD(packet, s32, 0x18);
        goto done;
    }

    if (group == 0x38) {
        color = packet + 4;
        FIELD(packet, s32, 4) = FIELD(command, s32, 4);
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        record = (u8 *)record + 0xC;
        sub = 8;
        color = packet + 0xC;
        FIELD(packet, s8, 3) = sub;
        FIELD(packet, u8, 7) = group;
        FIELD(packet, u8, 7) = FIELD(command, u8, 1);
        FIELD(packet, s32, 0xC) = FIELD(record, s32, 0);
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        color = packet + 0x14;
        FIELD(packet, s32, 0x14) = FIELD(record, s32, 4);
        func_8004C010(color, tint0);
        func_8004C010(color, tint1);
        color = packet + 0x1C;
        FIELD(packet, s32, 0x1C) = FIELD(record, s32, 8);
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
        values[0] = FIELD(command, u8, 8);
        values[1] = FIELD(command, u8, 9);
        values[2] = FIELD(command, u8, 0xA) + 1;
        values[3] = FIELD(command, u8, 0xB) + 1;
        SetTexWindow(packet, values);
        goto done;
    }

    group2 = sub & 0x7C;
    if (sub == 1) {
        SetDrawMode(packet, 1, FIELD(command, u16, 6),
                      FIELD(command, s16, 4), 0);
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
