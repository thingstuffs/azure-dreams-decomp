#define DERIVED_OBJ
#define POST_CALL_INCREMENT
#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#ifdef EXPLICIT_DIV255
typedef unsigned long long u64_local;
#define SCALE255(value) ((u32)(((u64_local)(u32)(value) * 0x80808081ULL) >> 39))
#elif defined(DIVISOR_VAR) || defined(CONST_DIVISOR)
#define SCALE255(value) ((u32)(value) / divisor)
#else
#define SCALE255(value) ((u32)(value) / 255)
#endif

extern u8 D_80083160[];
extern s32 func_80069EF8(void);
extern void func_80066844(void *);
extern void func_80066640(void *, s32);
extern void func_800A130C(void *, void *);
extern void func_800A1330(void *, void *);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
#ifdef RET_6658C
extern s32 func_8006658C(void *, void *);
#elif defined(OLD_6658C_PROTO)
extern void func_8006658C();
#else
extern void func_8006658C(void *, void *);
#endif
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

void func_800A1354(u8 *arg0)
{
    u8 **ctx_addr = (u8 **)D_80083160;
    s32 i = 0;
    u32 mask = 0xFFFFFF;
#ifdef DIVISOR_VAR
    u32 divisor = mask >> 16;
#elif defined(CONST_DIVISOR)
    const u32 divisor = 255;
#endif
#ifndef LATE_GEOM_PTRS
#if defined(ASSIGN_GEOM_LATE) || defined(ASSIGN_GEOM_BEFORE_LOOP)
    u8 *p74;
    u8 *p7C;
    u8 *p84;
    u8 *p8C;
#else
    u8 *p74 = (u8 *)0x1F800074;
    u8 *p7C = (u8 *)0x1F80007C;
    u8 *p84 = (u8 *)0x1F800084;
    u8 *p8C = (u8 *)0x1F80008C;
#endif
#endif
    u8 *scratch = (u8 *)0x1F800000;
    u8 *obj = arg0;
    s32 scale;
    u8 *poly;
#ifdef OUTER_POLY_ARG
    u8 *poly_arg;
#endif
    s32 rand1;
    s32 color3;

    scale = FIELD(obj, s16, 0x10);
    FIELD(scratch, u8 *, 0x24) = *ctx_addr + 0xB0;
#ifdef ASSIGN_GEOM_BEFORE_LOOP
    p74 = (u8 *)0x1F800074;
    p7C = (u8 *)0x1F80007C;
    p84 = (u8 *)0x1F800084;
    p8C = (u8 *)0x1F80008C;
#endif
    do {
        u8 *ctx = *ctx_addr;
        u8 *packet;
#ifdef REGISTER_POLY_ARG
        u8 *poly_arg;
#endif
#ifdef DERIVED_OBJ
        obj = arg0 + (i * 4);
#endif

        poly = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = poly + 0x28;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x04) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x0C) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x14) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        color3 = rand1 * func_80069EF8();
        FIELD(poly, u32, 0x1C) = color3 & mask;

        FIELD(poly, u8, 0x04) = SCALE255(FIELD(poly, u8, 0x04) * scale);
        FIELD(poly, u8, 0x05) = SCALE255(FIELD(poly, u8, 0x05) * scale);
        FIELD(poly, u8, 0x06) = SCALE255(FIELD(poly, u8, 0x06) * scale);
        FIELD(poly, u8, 0x0C) = SCALE255(FIELD(poly, u8, 0x0C) * scale);
        FIELD(poly, u8, 0x0D) = SCALE255(FIELD(poly, u8, 0x0D) * scale);
        FIELD(poly, u8, 0x0E) = SCALE255(FIELD(poly, u8, 0x0E) * scale);
        FIELD(poly, u8, 0x14) = SCALE255(FIELD(poly, u8, 0x14) * scale);
        FIELD(poly, u8, 0x15) = SCALE255(FIELD(poly, u8, 0x15) * scale);
        FIELD(poly, u8, 0x16) = SCALE255(FIELD(poly, u8, 0x16) * scale);
        FIELD(poly, u8, 0x1C) = FIELD(poly, u8, 0x04);
        FIELD(poly, u8, 0x1D) = FIELD(poly, u8, 0x05);
        FIELD(poly, u8, 0x1E) = FIELD(poly, u8, 0x06);
        func_80066844(poly);
        func_80066640(poly, 1);

#ifdef ASSIGN_GEOM_LATE
        p74 = (u8 *)0x1F800074;
        p7C = (u8 *)0x1F80007C;
        p84 = (u8 *)0x1F800084;
        p8C = (u8 *)0x1F80008C;
#endif
#ifdef LATE_GEOM_PTRS
        {
            u8 *p74 = (u8 *)0x1F800074;
            u8 *p7C = (u8 *)0x1F80007C;
            u8 *p84 = (u8 *)0x1F800084;
            u8 *p8C = (u8 *)0x1F80008C;
#endif
        func_800A130C(p74, FIELD(FIELD(obj, u8 *, 0x54), void *, 8));
        func_800A130C(p7C, FIELD(FIELD(obj, u8 *, 0x58), void *, 8));
        func_800A130C(p84, FIELD(FIELD(obj, u8 *, 0x5C), void *, 8));
        func_800A1330(p8C, p74);
        FIELD(scratch, s32, 0xC4) = func_800654B0(
            p74, p7C, p84, p8C, scratch + 0xE8, scratch + 0xEC,
            scratch + 0xF0, scratch + 0xF4, scratch + 0x94, scratch + 0x98) - 0x30;
#ifdef LATE_GEOM_PTRS
        }
#endif

        FIELD(poly, u16, 0x08) = FIELD(scratch, u16, 0xE8);
        FIELD(poly, u16, 0x0A) = FIELD(scratch, u16, 0xEA);
        FIELD(poly, u16, 0x10) = FIELD(scratch, u16, 0xEC);
        FIELD(poly, u16, 0x12) = FIELD(scratch, u16, 0xEE);
        FIELD(poly, u16, 0x18) = FIELD(scratch, u16, 0xF0);
        FIELD(poly, u16, 0x1A) = FIELD(scratch, u16, 0xF2);
        FIELD(poly, u16, 0x20) = FIELD(scratch, u16, 0xF4);
        FIELD(poly, u16, 0x22) = FIELD(scratch, u16, 0xF6);
        if (FIELD(scratch, s32, 0xC4) >= 0x1E0)
            FIELD(scratch, s32, 0xC4) = 0x1DF;
#ifdef EARLY_INCREMENT
        i += 3;
#endif
#ifdef DUPLICATE_CALL_TAIL
        i += 3;
        if (FIELD(scratch, s32, 0xC4) < 0) {
            FIELD(scratch, s32, 0xC4) = 0;
            func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly);
        } else {
            func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly);
        }
#elif defined(POLY_BOTH_BRANCHES)
        {
            u8 *poly_arg;
            if (FIELD(scratch, s32, 0xC4) < 0) {
                FIELD(scratch, s32, 0xC4) = 0;
                poly_arg = poly;
            } else {
                poly_arg = poly;
            }
#elif !defined(CLAMP_IN_CALL)
#if defined(REGISTER_POLY_ARG) || defined(OUTER_POLY_ARG)
        poly_arg = poly;
#endif
        if (FIELD(scratch, s32, 0xC4) < 0)
            FIELD(scratch, s32, 0xC4) = 0;
#endif
#ifndef DUPLICATE_CALL_TAIL
#if defined(DERIVED_OBJ)
#if !defined(EARLY_INCREMENT) && !defined(POST_CALL_INCREMENT)
        i += 3;
#endif
#elif defined(INDEXED_OBJ_UPDATE)
        obj = arg0 + ((i + 3) * 4);
        i += 3;
#else
        obj += 0xC;
        i += 3;
#endif
#endif
#ifdef POLY_BOTH_BRANCHES
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly_arg);
        }
#elif defined(CLAMP_IN_CALL)
        func_8006658C(
            (FIELD(scratch, s32, 0xC4) < 0
                ? (FIELD(scratch, s32, 0xC4) = 0, FIELD(scratch, u8 *, 0x24))
                : FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4),
            poly);
#elif !defined(DUPLICATE_CALL_TAIL)
#if defined(REGISTER_POLY_ARG) || defined(OUTER_POLY_ARG)
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly_arg);
#else
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly);
#endif
#endif
#ifdef POST_CALL_INCREMENT
        i += 3;
#endif
        ctx = *ctx_addr;
        packet = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = packet + 0xC;
        func_80067F20(packet, 1, 0, func_80066460(0, 1, 0x140, 0), 0);
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, packet);
    } while (i < 6);
}
