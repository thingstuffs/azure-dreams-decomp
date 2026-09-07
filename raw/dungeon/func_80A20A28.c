#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define TMP FIELD(storage, s32, 0x7C)
#define OUTX FIELD(storage, s16, 0x78)
#define OUTY FIELD(storage, s16, 0x7A)

extern s32 func_80065420();
extern s16 func_80066460();
extern void func_80066640();
extern void func_800666F4(void *);
extern void func_800DBA90();

extern u8 D_80083160[0x8D4];
extern u8 D_8017087C[];

s32 func_80174228(u8 *arg0)
{
    u8 storage[0x80];
    s32 depth;
    s32 depth_old;
    s32 depth_input;
    s32 depth_result;
    s32 x_condition;
    u8 *slot;
    s32 maxx;
    s32 depth_offset;
    u8 *work_ptr;
    u8 *setup_cursor;
    s32 packed_x;
    s32 packed_y;
    s32 i;
    register s32 *tmpp ASM_REG("$20");
    s32 delta;
    s32 q;
    s32 value;
    register s32 tail_y ASM_REG("$7");
    register s32 pos_y ASM_REG("$6");
    u8 *next;
    register s32 x0 ASM_REG("$4");
    register s32 x1 ASM_REG("$4");
    register s32 y0;
    register s32 y1;
    register s32 width;
    register s32 neg_width;
    u32 mask24;
    register u32 hi8 ASM_REG("$5");
    register u8 *vertex0 ASM_REG("$3");
    register u8 *vertex ASM_REG("$16");
    u8 *prim;
    u8 shade;
    u8 tex_height;
    u8 *context;
    u8 *context2;
    u8 *dst;
    u8 *mirror;
    u32 mirror_addr;
    s16 *elem_ptr;
    s32 elem;
    s32 item_term;
    s32 raw;
    s32 ret;
    s32 d8;
    s32 outv;
    u32 outu;
    u16 item_u;
    s32 half;
    register u8 *item ASM_REG("$23");
    register s32 abs11 ASM_REG("$2");
    u8 *page;
    register u8 *sb ASM_REG("$4");
    register u8 *setup ASM_REG("$4");

    page = D_80083160;
    __builtin_memcpy(storage, D_8017087C, 8);
    depth = 0;
    slot = storage + 8;

    do {
    item = arg0;
    work_ptr = slot;
    i = 3;
    tail_y = -0xA0;
    pos_y = 0x10;
    FIELD(storage, s32, 0x7C) = 0x40;
    width = FIELD(storage, u16, 0x7C);
    vertex0 = work_ptr + 0x18;
    neg_width = -width;
    do {
        FIELD(vertex0, u16, 0) = width;
        if (i < 2) {
            FIELD(vertex0, u16, 0) = neg_width;
        }
        FIELD(vertex0, s16, 2) = 0;
        if (i & 1) {
            FIELD(vertex0, s16, 4) = tail_y;
        } else {
            FIELD(vertex0, s16, 4) = pos_y;
        }
        i--;
        vertex0 -= 8;
    } while (i >= 0);

    setup = storage + 0x28;
    ASM_KEEP_NV(setup);
    packed_x &= 0xFFFF;
    packed_y &= 0xFFFF;
    i = 3;
    setup_cursor = page;
    abs11 = FIELD(setup_cursor, u16, 0xC8);
    ASM_USE_NV(abs11);
    FIELD(storage, s16, 0x32) = 0;
    FIELD(storage, s16, 0x30) = 0;
    setup_cursor = slot;
    tmpp = &TMP;
    vertex = setup_cursor + 0x18;
    FIELD(storage, u8 *, 0x28) = setup_cursor;
    FIELD(storage, u8 *, 0x2C) = setup_cursor;
    FIELD(storage, s16, 0x34) = -abs11;
    __builtin_memcpy(storage + 0x38, item, 8);
    FIELD(storage, s16, 0x40) = 4;
    FIELD(storage, s16, 0x42) = 0;
    func_800DBA90(setup, neg_width, pos_y, tail_y);

    packed_x |= 0x75300000;
    packed_x &= 0xFFFF0000;
    packed_x |= 0x7530;
    packed_y |= 0x8AD00000;
    packed_y &= 0xFFFF0000;
    packed_y |= 0x8AD0;

    do {
        ret = func_80065420(vertex, &OUTX, tmpp, tmpp);
        depth_input = depth;
        outv = OUTX;
        depth_old = depth_input - 8;
        ASM_USE2_NV(outv, depth_old);
        depth_result = depth_old + ret;
        x_condition = (s16)packed_y < outv;
        depth = depth_result;
        outu = (u16)OUTX;
        if (x_condition) {
            packed_y &= 0xFFFF0000;
            outu |= packed_y;
            packed_y = outu;
        } else if (outv < (s16)packed_x) {
            packed_x &= 0xFFFF0000;
            outu |= packed_x;
            packed_x = outu;
        }
        outv = OUTY;
        outu = (u16)OUTY;
        if ((packed_y >> 16) < outv) {
            packed_y &= 0xFFFF;
            packed_y = packed_y | (outu << 16);
        } else if (outv < (packed_x >> 16)) {
            packed_x &= 0xFFFF;
            packed_x = packed_x | (outu << 16);
        }
        i--;
        vertex -= 8;
    } while (i >= 0);

    i = 1;
    depth >>= 2;
    item_u = FIELD(item, u16, 0xE);
    ASM_KEEP_MEMDEP_NV(item_u, dst, storage[0]);
    dst = storage + 0x60;
    FIELD(storage, u16, 0x5E) = item_u;
    do {
        mirror_addr = (0xB - i) * 2;
        mirror_addr += (u32)storage;
        mirror = (u8 *)mirror_addr;
        raw = FIELD(storage, u16, 0x48 + (0xC - i) * 2);
        i++;
        half = (raw << 16) >> 17;
        FIELD(dst, s16, 0) = half;
        FIELD(mirror, s16, 0x48) = half;
        dst += 2;
    } while (i < 0xC);

    if ((u32)depth < 0x1E0U) {
        i = 0;
        do {
            context = FIELD(page, u8 *, 0);
            prim = FIELD(context, u8 *, 0x8D0);
            FIELD(context, u8 *, 0x8D0) = prim + 0x28;

            elem_ptr = (s16 *)(storage + i * 2 - 0x10);
            ASM_USE(elem_ptr);
            abs11 = 0xB;
            abs11 -= i;
            elem = FIELD(elem_ptr, s16, 0x58);
            if (abs11 < 0) {
                abs11 = -abs11;
            }
            elem -= abs11;
            item_term = FIELD(item, s16, 0x18);
            elem *= 2;
            item_term *= 4;
            item_term += 0x5C;
            elem += item_term;
            TMP = elem;
            if (elem < 0) {
                TMP = 0;
            }
            shade = TMP;
            FIELD(prim, u8, 6) = shade;
            FIELD(prim, u8, 5) = shade;
            FIELD(prim, u8, 4) = shade;
            func_800666F4(prim);
            func_80066640(prim, 1);
            FIELD(prim, s16, 0x16) = func_80066460(2, 1, 0x340, 0x100);

            abs11 = i * FIELD(storage, s16, 4);
            x0 = abs11 / 23;
            FIELD(prim, s8, 0x14) = x0;
            FIELD(prim, s8, 0xC) = x0;
            value = x0;
            value += ((FIELD(storage, u16, 4) << 16) >> 16) / 23;
            FIELD(prim, u8, 0x1D) = 0;
            FIELD(prim, u8, 0xD) = 0;
            FIELD(prim, s8, 0x24) = value;
            FIELD(prim, s8, 0x1C) = value;

            tex_height = FIELD(storage, u8, 6);
            ASM_USE(tex_height);
            FIELD(prim, u8, 0x25) = tex_height;
            value = FIELD(prim, u8, 0xD) + 2;
            if (tex_height >= 2) {
                value = FIELD(prim, u8, 0xD) + FIELD(prim, u8, 0x25);
            }
            maxx = (s16)packed_y;
            delta = maxx - (s16)packed_x;
            FIELD(prim, u8, 0x25) = value;
            FIELD(prim, u8, 0x15) = value;

            q = (delta * i) / 23;
            TMP = q;
            if (i < 0xB) {
                TMP = q + FIELD(item, s16, 0xA);
                if ((delta >> 1) < TMP) {
                    TMP = delta >> 1;
                }
            } else if (i >= 0xC) {
                TMP = q - FIELD(item, s16, 0xA);
                if (TMP < (delta >> 1)) {
                    TMP = delta >> 1;
                }
            }

            x0 = (u16)TMP + packed_x;
            FIELD(prim, s16, 0x10) = x0;
            FIELD(prim, s16, 8) = x0;
            x1 = x0 + delta / 23;
            FIELD(prim, s16, 0x20) = x1;
            FIELD(prim, s16, 0x18) = x1;

            sb = storage;
            y0 = FIELD(sb, u16, 0x48 + i * 2) + (packed_x >> 16);
            FIELD(prim, s16, 0x1A) = y0;
            FIELD(prim, s16, 0xA) = y0;
            y1 = FIELD(sb, u16, 0x48 + i * 2) + (packed_y >> 16);
            FIELD(prim, s16, 0x22) = y1;
            FIELD(prim, s16, 0x12) = y1;

            depth_offset = depth * 4;
            hi8 = 0xFF000000;
            mask24 = 0x00FFFFFF;
            context = FIELD(page, u8 *, 0);
            FIELD(prim, u32, 0) = (FIELD(prim, u32, 0) & hi8) |
                (FIELD(context, u32, 0xB0 + depth_offset) & mask24);
            context2 = FIELD(page, u8 *, 0);
            FIELD(context2, u32, 0xB0 + depth_offset) =
                (FIELD(context2, u32, 0xB0 + depth_offset) & hi8) |
                ((u32)prim & mask24);

            i++;
        } while (i < 0x17);
    }

    next = FIELD(arg0, u8 *, -8);
    if (next == 0) {
        break;
    }
    arg0 = next + 0x20;
    } while (1);
    return 0;
}
