#include "common.h"

#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v, s32 z);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void AddPrim(void *ot, void *prim);
extern void *D_80083160[3];

void func_80044D24(void *arg0, void *arg1, s32 arg2)
{
    u8 **root;
    u8 *scratch;
    u8 *entry;
    void *prim;
    u8 *context;
    u8 *script;
    register void *matrix ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register void *translation ASM_REG("$5");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register void *record ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register void *packet ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 depth;
    s16 x;
    s16 y;
    u16 flags;
    u16 trans_x;
    s32 trans_base_x;
    u8 a;
    u8 b;

    (void)arg0;
    context = D_80083160[0];
    entry = arg1;
    scratch = (u8 *)0x1F800000;
    depth = arg2;
    root = (u8 **)D_80083160;
    do { prim = *(void **)(context + 0x8D0); } while (0);
    U32_AT(scratch, 0x20) = (u32)(context + 0x70);
    U32_AT(scratch, 0x38) = 0x1000;
    U32_AT(scratch, 0x48) = 0;
    U16_AT(scratch, 0x8C) = 0;
    U16_AT(scratch, 0x84) = 0;
    U16_AT(scratch, 0x7C) = 0;
    U16_AT(scratch, 0x74) = 0;
    PushMatrix();

    matrix = scratch + 0x50;
    translation = scratch + 0x40;
    script = *(u8 **)(entry + 8);
    flags = U16_AT(entry, 0x14) | 0x8000;
    U16_AT(entry, 0x14) = flags;
    U16_AT(scratch, 0x24) = flags;
    record = script + 1;
    U32_AT(scratch, 0x30) = U16_AT(entry, 0x1C);
    trans_base_x = S16_AT(scratch, 0);
    ASM_USE(record);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    packet = (u8 *)prim + 4;
    U32_AT(scratch, 0x34) = U16_AT(entry, 0x1E);
    trans_x = U16_AT(entry, 0x20);
    U32_AT(scratch, 0x40) = trans_base_x + trans_x;
    U32_AT(scratch, 0x44) = S16_AT(scratch, 2) + U16_AT(entry, 0x22);
    TransMatrix(matrix, translation, trans_x);
    RotMatrix(entry + 0x16, scratch + 0x50);
    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    SetRotMatrix(scratch + 0x50);
    SetTransMatrix(scratch + 0x50);

    for (;;) {
        if (!(script[0] & 0x20)) {
            a = U8_AT(record, 7);
            U32_AT(scratch, 8) = a;
            b = U8_AT(record, 9);
            U32_AT(scratch, 0x10) = b;
            if (a + b >= 0x100) {
                U32_AT(scratch, 0x10) = b - 1;
            }

            a = U8_AT(record, 8);
            U32_AT(scratch, 0xC) = a;
            b = U8_AT(record, 0xA);
            U32_AT(scratch, 0x14) = b;
            if (a + b >= 0x100) {
                U32_AT(scratch, 0x14) = b - 1;
            }

            if ((script[0] ^ U16_AT(scratch, 0x24)) & 1) {
                s32 value;
                if (U16_AT(entry, 0x14) & 0x400) {
                    s32 raw = U8_AT(record, 1);
                    value = (raw << 24) >> 23;
                } else {
                    s32 raw = U8_AT(record, 1);
                    ASM_KEEP_NV(raw);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    value = (raw << 24) >> 24;
                }
                {
                    register s32 neg ASM_REG("$3") = -value;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP_NV(neg);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    S16_AT(scratch, 0x80) = neg;
                    S16_AT(scratch, 0x70) = neg;
                    x = neg - U16_AT(scratch, 0x10);
                }
            } else {
                u16 doubled;
                s32 raw;
                register s32 combined ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s32 value;
                raw = U8_AT(record, 1);
                raw <<= 24;
                doubled = U16_AT(entry, 0x14) & 0x400;
                ASM_KEEP_DEP_NV(raw, doubled);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                value = raw >> 24;
                if (doubled) {
                    value *= 2;
                }
                S16_AT(scratch, 0x80) = value;
                S16_AT(scratch, 0x70) = value;
                combined = U16_AT(scratch, 0x10);
                combined = value + combined;
                x = combined;
            }
            S16_AT(scratch, 0x88) = x;
            S16_AT(scratch, 0x78) = x;

            if ((script[0] ^ U16_AT(scratch, 0x24)) & 2) {
                s32 value;
                if (U16_AT(entry, 0x14) & 0x400) {
                    s32 raw = U8_AT(record, 2);
                    value = (raw << 24) >> 23;
                } else {
                    s32 raw = U8_AT(record, 2);
                    ASM_KEEP_NV(raw);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    value = (raw << 24) >> 24;
                }
                {
                    register s32 neg ASM_REG("$3") = -value;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP_NV(neg);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    S16_AT(scratch, 0x7A) = neg;
                    S16_AT(scratch, 0x72) = neg;
                    y = neg - U16_AT(scratch, 0x14);
                }
            } else {
                u16 doubled;
                s32 raw;
                register s32 combined ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s32 value;
                raw = U8_AT(record, 2);
                raw <<= 24;
                doubled = U16_AT(entry, 0x14) & 0x400;
                ASM_KEEP_DEP_NV(raw, doubled);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                value = raw >> 24;
                if (doubled) {
                    value *= 2;
                }
                S16_AT(scratch, 0x7A) = value;
                S16_AT(scratch, 0x72) = value;
                combined = U16_AT(scratch, 0x14);
                combined = value + combined;
                y = combined;
            }
            S16_AT(scratch, 0x8A) = y;
            S16_AT(scratch, 0x82) = y;

            /* Four rotate-and-translate transforms of the sprite corners
             * (scratchpad 0x70/0x78/0x80/0x88) into the packet's vertex
             * slots. Sanctioned GTE intrinsics (include/common.h). */
            gte_ldv0(scratch + 0x70);
            gte_rtv0tr();
            gte_stsv((u8 *)prim + 8);

            gte_ldv0(scratch + 0x78);
            gte_rtv0tr();
            gte_stsv((u8 *)prim + 0x10);

            gte_ldv0(scratch + 0x80);
            gte_rtv0tr();
            gte_stsv((u8 *)prim + 0x18);

            gte_ldv0(scratch + 0x88);
            gte_rtv0tr();
            gte_stsv((u8 *)prim + 0x20);

            U8_AT(packet, -1) = 9;
            U16_AT(entry, 0x14) &= 0x7FFF;
            {
                s32 sum_x = U32_AT(scratch, 0x10);
                register s32 base_x ASM_REG("$4") = U32_AT(scratch, 8);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                register s32 sum_y ASM_REG("$2") = U32_AT(scratch, 0x14);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s32 base_y = U32_AT(scratch, 0xC);
                sum_x += base_x;
                sum_y += base_y;
                sum_y <<= 8;
                U32_AT(scratch, 0x14) = sum_y;
                {
                    sum_y = base_y;
                    ASM_KEEP_NV(sum_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    U32_AT(scratch, 0x10) = sum_x;
                    U32_AT(scratch, 0xC) = sum_y << 8;
                }
            }

            if (U16_AT(scratch, 0x24) & 0x100) {
                U16_AT(packet, 0xA) = U16_AT(entry, 0x12);
            } else {
                U16_AT(packet, 0xA) =
                    U16_AT(entry, 0x12) + U16_AT(record, 5);
            }
            S16_AT(packet, 8) = U16_AT(scratch, 0xC) + U16_AT(scratch, 8);
            S16_AT(packet, 0x10) =
                U16_AT(scratch, 0xC) + U16_AT(scratch, 0x10);

            {
                u16 base_flags = U16_AT(entry, 0x10);
                u16 out_flags;
                if (base_flags != 0) {
                    out_flags = base_flags +
                        (U16_AT(record, 3) & 0xFF9F);
                } else {
                    out_flags = U16_AT(record, 3);
                }
                U16_AT(packet, 0x12) = out_flags;
            }
            S16_AT(packet, 0x18) =
                U16_AT(scratch, 0x14) + U16_AT(scratch, 8);
            S16_AT(packet, 0x20) =
                U16_AT(scratch, 0x14) + U16_AT(scratch, 0x10);

            if (S16_AT(scratch, 0x50) >= 0x1800) {
                u8 shade = U8_AT(packet, 0x20);
                U8_AT(packet, 0x20) = shade + 0xFF;
                U8_AT(packet, 0x10) = shade;
            }
            if (S16_AT(scratch, 0x58) >= 0x1800) {
                u8 shade = U8_AT(packet, 0x21);
                U8_AT(packet, 0x21) = shade + 0xFF;
                U8_AT(packet, 0x19) = shade;
            }
            if (S16_AT(packet, 4) > S16_AT(packet, 0x1C)) {
                u8 shade = U8_AT(packet, 0x20);
                U8_AT(packet, 0x20) = shade + 0xFF;
                U8_AT(packet, 0x10) = shade;
            }
            if (S16_AT(packet, 6) > S16_AT(packet, 0x1E)) {
                u8 shade = U8_AT(packet, 0x21);
                U8_AT(packet, 0x21) = shade + 0xFF;
                U8_AT(packet, 0x19) = shade;
            }

            {
                u8 code;
                register u16 local_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                code = U8_AT(record, 0);
                entry[0xF] = code;
                local_flags = U16_AT(scratch, 0x24);
                if (local_flags & 8) {
                    u8 adjusted;
                    if (local_flags & 4) {
                        adjusted = code | 2;
                    } else {
                        adjusted = code & 0xFD;
                    }
                    ASM_KEEP_DEP_NV(adjusted, local_flags);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    entry[0xF] = adjusted;
                }
            }

            {
                void *this_prim;
                s32 offset;
                this_prim = prim;
                prim = (u8 *)prim + 0x28;
                offset = (s16)depth * 4;
                {
                    u32 link;
                    link = U32_AT(entry, 0xC);
                    U32_AT(packet, 0) = link;
                }
                {
                    u32 ot_base;
                    do { ot_base = U32_AT(scratch, 0x20); } while (0);
                    packet = (u8 *)packet + 0x28;
                    AddPrim((u8 *)ot_base + offset, this_prim);
                }
            }
        }

        record = (u8 *)record + 0xC;
        if ((s8)script[0] < 0) {
            break;
        }
        script += 0xC;
    }

    PopMatrix();
    *(void **)(root[0] + 0x8D0) = prim;
}
