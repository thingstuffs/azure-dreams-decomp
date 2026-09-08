#include "common.h"

typedef struct Packed8 {
    u32 word0;
    u32 word1;
} __attribute__((packed)) Packed8;

typedef struct Coord {
    s16 x;
    s16 y;
} Coord;

typedef union Scratch {
    s32 word;
    u16 half;
    u8 byte;
} Scratch;

extern u8 D_80083160[];

extern s32 func_80065420(Packed8 *, Coord *, Coord *, Coord *);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_800666F4(void *);
extern s32 func_80069EF8(void);

#define LOAD_PTR(p) (*(u8 **)(p))
#define LOAD_U32(p) (*(u32 *)(p))
#define STORE_U32(p, v) (*(u32 *)(p) = (v))
#define STORE_U16(p, v) (*(u16 *)(p) = (v))
#define STORE_U8(p, v) (*(u8 *)(p) = (v))

s32 func_81845068(u8 *arg0)
{
    u32 selectors[4];
    Packed8 packed;
    Coord coords[3];
    u8 *node;
    u8 *current;
    register u8 *next ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *global;
    register u8 *alloc_ctx ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *table_ctx;
    register u8 *table_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *prim;
    Coord *coord_base;
    Coord *coord;
    register Coord *shared;
    s32 i;
    s32 index;
    u16 offset_half_first;
    u16 offset_half_second;
    s32 temp;
    s32 color0;
    s32 color1;
    s32 random;
    register u32 mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 table_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 x0;
    u16 y0;
    u16 y1;

    node = arg0;
    global = D_80083160;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    selectors[0] = 0xA0;
    do { selectors[1] = 0x80; } while (0);
    coord_base = &coords[0];
    selectors[2] = 0;
    selectors[3] = 0x20;
    mask = 0xFFFFFF;

    do {
        current = node;
        packed = *(Packed8 *)(node + 4);
        i = 0;
        shared = &coords[2];
        coord = coord_base;
        do {
            index = func_80065420(&packed, coord, shared, shared) - 8;
            coord++;
            i++;
            *(u16 *)((u8 *)&packed + 4) =
                *(u16 *)((u8 *)&packed + 4) + 0xB0;
        } while (i < 2);

        shared = (Coord *)(coords[0].y - coords[1].y);

        if ((u32)index < 0x1E0) {
            alloc_ctx = LOAD_PTR(global);
            prim = LOAD_PTR(alloc_ctx + 0x8D0);
            LOAD_PTR(alloc_ctx + 0x8D0) = prim + 0x34;
            STORE_U32(prim + 4, 0x00808080);
            func_800666F4(prim);
            func_80066640(prim, 1);
            STORE_U16(prim + 0x16, func_80066460(0, 0, 0x2C0, 0x100));
            STORE_U16(prim + 0x0E, func_8006649C(0xA0, 0x1F7));

            ((Scratch *)&coords[2])->word = (s32)shared / 6;
            x0 = coords[0].x;
            offset_half_first = ((Scratch *)&coords[2])->half;
            x0 += offset_half_first;
            STORE_U16(prim + 0x10, x0);
            STORE_U16(prim + 8, x0);
            x0 = coords[0].x - offset_half_first;
            STORE_U16(prim + 0x20, x0);
            STORE_U16(prim + 0x18, x0);
            y0 = coords[0].y;
            STORE_U16(prim + 0x1A, y0);
            STORE_U16(prim + 0x0A, y0);
            y1 = coords[1].y;
            STORE_U16(prim + 0x22, y1);
            STORE_U16(prim + 0x12, y1);

            temp = 7 - *(s16 *)(current + 0x2A);
            ((Scratch *)&coords[2])->word = temp;
            table_entry = (u8 *)(index * 4);
            ASM_KEEP_NV(table_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            color1 = (((Scratch *)&coords[2])->byte & 3) << 5;
            color0 = color1 - 0x80;
            color1 -= 0x61;
            STORE_U8(prim + 0x1C, color0);
            STORE_U8(prim + 0x0C, color0);
            STORE_U8(prim + 0x24, color1);
            STORE_U8(prim + 0x14, color1);
            temp = ((Scratch *)&coords[2])->word >> 2;
            temp <<= 5;
            STORE_U8(prim + 0x25, temp);
            STORE_U8(prim + 0x1D, temp);
            STORE_U8(prim + 0x15, temp + 0x1F);
            STORE_U8(prim + 0x0D, temp + 0x1F);
            {
                register u32 high_mask ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                table_ctx = LOAD_PTR(global);
                table_word = LOAD_U32(table_ctx + 0xB0 + index * 4);
                STORE_U32(prim, (LOAD_U32(prim) & high_mask) | (table_word & mask));
                table_ctx = LOAD_PTR(global);
                table_entry += (u32)table_ctx;
                table_word = LOAD_U32(table_entry + 0xB0);
                table_word &= high_mask;
                STORE_U32(table_entry + 0xB0,
                          table_word | ((u32)prim & mask));
            }
        }

        alloc_ctx = LOAD_PTR(global);
        prim = LOAD_PTR(alloc_ctx + 0x8D0);
        LOAD_PTR(alloc_ctx + 0x8D0) = prim + 0x34;
        STORE_U32(prim + 4, 0x00161616);
        func_800666F4(prim);
        func_80066640(prim, 1);
        STORE_U16(prim + 0x16, func_80066460(0, 3, 0x2C0, 0x100));
        STORE_U16(prim + 0x0E, func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8));

        i = func_80069EF8() & 1;
        temp = *(u8 *)&selectors[i];
        STORE_U8(prim + 0x1C, temp);
        STORE_U8(prim + 0x0C, temp);
        temp = *(u8 *)&selectors[i] + 0x5F;
        STORE_U8(prim + 0x24, temp);
        STORE_U8(prim + 0x14, temp);
        temp = *((u8 *)&selectors[i] + 8) + 0x20;
        STORE_U8(prim + 0x15, temp);
        STORE_U8(prim + 0x0D, temp);
        temp = *((u8 *)&selectors[i] + 8);
        STORE_U8(prim + 0x25, temp);
        STORE_U8(prim + 0x1D, temp);

        random = func_80069EF8();
        i = (random % 64) - 0x20;
        table_word = (s32)shared / 6;
        ((Scratch *)&coords[2])->word = table_word;
        i = (i >> 1) + (i >> 2);
        table_word = (u16)coords[0].x;
        offset_half_second = ((Scratch *)&coords[2])->half;
        x0 = table_word + offset_half_second + i;
        STORE_U16(prim + 0x10, x0);
        STORE_U16(prim + 8, x0);
        x0 = coords[0].x - offset_half_second + i * 2;
        STORE_U16(prim + 0x20, x0);
        STORE_U16(prim + 0x18, x0);
        y0 = coords[0].y;
        table_entry = (u8 *)(index * 4);
        STORE_U16(prim + 0x1A, y0);
        STORE_U16(prim + 0x0A, y0);
        y1 = coords[1].y;
        STORE_U16(prim + 0x22, y1);
        STORE_U16(prim + 0x12, y1);

        {
            register u32 high_mask ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            table_ctx = LOAD_PTR(global);
            table_word = LOAD_U32(table_ctx + 0xB0 + index * 4);
            STORE_U32(prim, (LOAD_U32(prim) & high_mask) | (table_word & mask));
            table_ctx = LOAD_PTR(global);
            table_entry += (u32)table_ctx;
            table_word = LOAD_U32(table_entry + 0xB0);
            table_word &= high_mask;
            STORE_U32(table_entry + 0xB0,
                      table_word | ((u32)prim & mask));
        }

        next = LOAD_PTR(node - 8);
        node = next + 0x20;
    } while (next != 0);

    ASM_SET(next);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 0;
}
