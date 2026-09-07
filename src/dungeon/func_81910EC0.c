#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define KEEP_MEMDEP_NV_EXPR(v, s, m) ({ ASM_KEEP_MEMDEP_NV(v, s, m); 0; })
/* Same address as D_80083160 (0x80083178 - 0x18); spelled off D_80083178 so the
   %hi page is one CONST rtx shared with the pin below.  Links to identical words. */
#define GFX_ROOT_SLOT (((u8 *)&D_80083178) - 0x18)
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
#define VS32_AT(p, o) (*(volatile s32 *)((u8 *)(p) + (o)))

typedef struct GfxContext {
    u8 pad0[0x8D0];
    u8 *cursor;
} GfxContext;

extern GfxContext *D_80083160[3];

extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

void func_81910EC0(void *arg0, void *arg1, s16 arg2, s16 arg3)
{
    u8 *page_scratch;
    u8 *obj = arg0;
    u8 *global = (KEEP_MEMDEP_NV_EXPR(obj, page_scratch, *(u8 **)GFX_ROOT_SLOT),
                  *(u8 **)GFX_ROOT_SLOT);
    s32 i = 0;
    s32 xscale = arg2;
    s32 divisor = arg3;
    s32 scaled = xscale < divisor;
    register u32 lowmask ASM_REG("$20") = 0x00FFFFFF;   /* MATCH pin: load-bearing for the whole function shape */
    u32 highmask = 0xFF000000;
    u8 *iter = obj;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *new_var;

    PTR_AT(scratch, 0x18) = global + 0xB0;
    new_var = GFX_ROOT_SLOT;
    do {
        GfxContext **pool = (GfxContext **)new_var;
        u8 *poly;
        u8 *next;
        s32 delta;
        u16 value;
        u16 value2;
        u32 index;

        poly = (*pool)->cursor;
        (*pool)->cursor = poly + 0x24;

        U8_AT(poly, 3) = 8;
        U8_AT(poly, 7) = 0x3A;
        U8_AT(poly, 4) = U8_AT(obj, 0x40);
        U8_AT(poly, 5) = U8_AT(obj, 0x41);
        U8_AT(poly, 6) = U8_AT(obj, 0x42);
        U8_AT(poly, 0xC) = U8_AT(obj, 0x40);
        U8_AT(poly, 0xD) = U8_AT(obj, 0x41);
        U8_AT(poly, 0xE) = U8_AT(obj, 0x42);
        U8_AT(poly, 0x14) = U8_AT(obj, 0x40);
        U8_AT(poly, 0x15) = U8_AT(obj, 0x41);
        U8_AT(poly, 0x16) = U8_AT(obj, 0x42);
        U8_AT(poly, 0x1C) = U8_AT(obj, 0x40);
        U8_AT(poly, 0x1D) = U8_AT(obj, 0x41);
        U8_AT(poly, 0x1E) = U8_AT(obj, 0x42);

        next = obj + (((i + 2) % 5) * 4);
        {
            u16 first_value = VU16_AT(iter, 0x1A);

            U16_AT(scratch, 0x74) = first_value;
            U16_AT(scratch, 0x64) = first_value;
        }

        delta = S32_AT(next, 0x18) - VS32_AT(iter, 0x18);
        S32_AT(scratch, 0x108) = delta;
        if (scaled) {
            S32_AT(scratch, 0x108) = (delta / divisor) * xscale;
        }

        value = VU16_AT(iter, 0x1A) + U16_AT(scratch, 0x10A);
        U16_AT(scratch, 0x7C) = value;
        U16_AT(scratch, 0x6C) = value;

        value2 = VU16_AT(iter, 0x2E);
        U16_AT(scratch, 0x76) = value2;
        U16_AT(scratch, 0x66) = value2;

        delta = S32_AT(next, 0x2C) - VS32_AT(iter, 0x2C);
        S32_AT(scratch, 0x10C) = delta;
        if (scaled) {
            S32_AT(scratch, 0x10C) = (delta / divisor) * xscale;
        }

        value2 = VU16_AT(iter, 0x2E) + U16_AT(scratch, 0x10E);
        U16_AT(scratch, 0x7E) = value2;
        U16_AT(scratch, 0x6E) = value2;

        value = U16_AT(arg1, 0xA) - U16_AT(obj, 0x10);
        U16_AT(scratch, 0x70) = value;
        U16_AT(scratch, 0x68) = value;

        value = U16_AT(arg1, 0xA);
        U16_AT(scratch, 0x78) = value;
        U16_AT(scratch, 0x80) = value;

        U32_AT(scratch, 0xB4) = func_80065590(
            scratch + 0x64, scratch + 0x6C,
            scratch + 0x74, scratch + 0x7C,
            scratch + 0xD8, scratch + 0xDC,
            scratch + 0xE0, scratch + 0xE4,
            scratch + 0x84, scratch + 0x88);

        U16_AT(poly, 8) = U16_AT(scratch, 0xD8);
        U16_AT(poly, 0xA) = U16_AT(scratch, 0xDA);
        U16_AT(poly, 0x10) = U16_AT(scratch, 0xDC);
        U16_AT(poly, 0x12) = U16_AT(scratch, 0xDE);
        U16_AT(poly, 0x18) = U16_AT(scratch, 0xE0);
        U16_AT(poly, 0x1A) = U16_AT(scratch, 0xE2);
        U16_AT(poly, 0x20) = U16_AT(scratch, 0xE4);
        U16_AT(poly, 0x22) = U16_AT(scratch, 0xE6);

        index = U32_AT(scratch, 0xB4);
        if (index < 0x1E0) {
            U32_AT(poly, 0) = (U32_AT(poly, 0) & highmask) |
                (*(u32 *)(PTR_AT(scratch, 0x18) + index * 4) & lowmask);
            *(u32 *)(PTR_AT(scratch, 0x18) + U32_AT(scratch, 0xB4) * 4) =
                (*(u32 *)(PTR_AT(scratch, 0x18) + U32_AT(scratch, 0xB4) * 4) & highmask) |
                ((u32)poly & lowmask);

            pool = (GfxContext **)new_var;
            poly = (*pool)->cursor;
            (*pool)->cursor = poly + 0xC;
            func_80067F20(poly, 0, 0,
                (u16)func_80066460(0, S16_AT(obj, 0x12), 0, 0), 0);

            U32_AT(poly, 0) = (U32_AT(poly, 0) & highmask) |
                (*(u32 *)(PTR_AT(scratch, 0x18) + U32_AT(scratch, 0xB4) * 4) & lowmask);
            {
                u32 final_index = U32_AT(scratch, 0xB4);

                poly = (u8 *)((u32)poly & lowmask);
                *(u32 *)(PTR_AT(scratch, 0x18) + final_index * 4) =
                    (*(u32 *)(PTR_AT(scratch, 0x18) + final_index * 4) & highmask) |
                    (u32)poly;
            }
        }

        i++;
        iter += 4;
    } while (i < 5);
}
