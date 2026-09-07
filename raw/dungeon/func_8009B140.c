#include "common.h"

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

extern s32 D_800814A0;
extern u8 D_80082E80[];
extern u8 D_80083478[];
extern s16 D_8008347C;
extern u32 D_800835E4[];
extern u8 D_800E2968;
extern s32 D_800E296C;

extern void func_80042640(void *, s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(s32, s32, s32);
extern s32 func_8009FB34(s32, s32);
extern void func_800A0B64(void) __attribute__((noreturn));
extern SpawnFunc func_800A0B94(s32, void *, s32);
extern void func_800A152C(s32, s32);
extern void *func_800A1618(s32, s32);
extern void func_800A1D4C(void *, s32);
extern void func_800A32A4(void *);
extern void func_800A4E2C(u8 *, u8 *);
extern s32 func_800A6D30(void);
extern s32 func_800A9230(void *);
extern s32 func_800BCB04(s32, s32, s32);

void func_800A08A0(s32 arg0) {
    register void *object ASM_REG("$16");
    s32 type;
    s32 kind;
    s32 variant;
    register u8 raw_variant ASM_REG("$4");
    s16 attempt;
    register s32 distance ASM_REG("$21");
    u8 *map;
    s32 table_index;
    s32 value;
    register s32 dx ASM_REG("$3");
    register s32 dy ASM_REG("$2");
    u8 x;
    u8 y;
    register u32 *limits ASM_REG("$3");
    SpawnFunc spawn;

    distance = 0x100;
    if (D_800E296C & 0x10000000) {
        return;
    }
    if (D_8008347C >= 0x20) {
        return;
    }

    attempt = 0;
    map = D_80082E80;
    kind = (s16)arg0;
    table_index = (kind - 2) * 2;

    do {
        func_800A4E2C(&x, &y);
        if ((s16)func_8009FB34(x, y) < 0) {
            continue;
        }

        if (kind == 0) {
            register s32 y_value ASM_REG("$4");
            {
                register s32 x_value ASM_REG("$2");
                dx = map[0x24];
                x_value = x;
                y_value = y;
                dx -= x_value;
            }
            dy = map[0x25];
            if (dx < 0) {
                dx = -dx;
            }
            dy -= y_value;
            if (dy < 0) {
                dy = -dy;
            }
            ASM_USE_NV(dy);
            distance = dx + dy;
        }
        if ((s16)distance < 0x21) {
            continue;
        }

        {
            register s16 selected_index ASM_REG("$3");
            register u8 *entry ASM_REG("$3");

            selected_index = (kind < 2) ?
                             ((func_800A6D30() & 0xF) * 2) : table_index;
            {
                u8 **base_addr = (u8 **)&D_80083478;
                s32 signed_index = selected_index;
                u8 *base = *base_addr;
                entry = (u8 *)(signed_index + (s32)base);
            }
            ASM_KEEP(entry);
            raw_variant = entry[1];
            D_800E2968 = raw_variant;
            type = entry[0];
        }

        if (type == 0) {
            return;
        }
        variant = raw_variant;
        object = func_800A1618(type, 1);
        ASM_KEEP(object);
        ASM_CLOBBER("$2");
        if (object == 0) {
            continue;
        }

        ASM_CLOBBER("$6");
        value = func_800BCB04((x << 6) | 0x20, (y << 6) | 0x20, -0x400);
        spawn = func_800A0B94(type, object, 1);
        object = spawn(0, x, y, (s16)value);
        if (object == 0) {
            return;
        }

        func_800A152C(type, 1);
        func_80042640(object, type);
        ((u8 *)object)[0x43] = func_800A6D30();
        ((u8 *)object)[0x12] = 0;

        if (kind >= 2) {
            u8 *owner = *(u8 **)((u8 *)object - 0x14);
            func_8009A3D0(owner[0x24], owner[0x25], 0x3000);
            func_800A32A4(object);
            func_8009A028(object);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_800A0B64();
        }

        limits = D_800835E4;
        ((u32 *)((u8 *)object + 0x18))[0] = limits[variant];
        limits++;
        if (*(u32 *)((u8 *)object + 0x18) >= limits[((u8 *)object)[0x11]]) {
            u32 *loop_limits = limits;
            u32 limit_value;
            do {
                func_800A1D4C(object, 0);
                limit_value = loop_limits[((u8 *)object)[0x11]];
            } while (*(u32 *)((u8 *)object + 0x18) >= limit_value);
        }
        if (((u8 *)object)[0x49] != 0) {
            return;
        }
        *(s32 *)((u8 *)object + 0x48) = func_800A9230(object);
        func_800A0B64();
    } while (++attempt < 0x10);
}
