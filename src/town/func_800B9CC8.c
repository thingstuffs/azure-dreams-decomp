#include "common.h"

extern u16 D_80162004[];

#ifdef NON_MATCHING
#define TOWN_TILE_PAGE ((u8 *)D_80162004 - 0x2004)
#else
#define TOWN_TILE_PAGE ((u8 *)0x80160000)
#endif

#define OUTPUT_TILE(value) do { \
    scratch = (s16)x; \
    scratch *= 2; \
    scratch += (s32)tilemap; \
    dst = (u16 *)scratch; \
    tile = (value); \
    goto store; \
} while (0)

#define OUTPUT_TILE_INDEX(value) do { \
    scratch = (s16)index; \
    scratch *= 2; \
    scratch += (s32)tilemap; \
    dst = (u16 *)scratch; \
    tile = (value); \
    goto store; \
} while (0)

void func_800B7428(s32 x, s32 y, u16 *src)
{
    s32 width;
    register s32 height ASM_REG("$15");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 row;
    s32 col;
    s32 tile;
    register s32 index ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 scratch ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 row_odd;
    s32 signed_width;
    s32 has_columns;
    register s32 signed_x ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    register s32 signed_y ASM_REG("$24");   /* MATCH pin: retail keeps a computation the compiler would drop */
    register s32 raw_x ASM_REG("$14");   /* MATCH pin: retail register colouring depends on it */
    register s32 raw_y ASM_REG("$13");   /* MATCH pin: load-bearing for the whole function shape */
    u16 *dst;
    register u16 *tilemap ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

    width = *src++;
    height = *src++;
    row = 0;
    raw_x = x;
    raw_y = y;
    scratch = height << 16;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    if (scratch > 0) {
        tile = 0;
        ASM_KEEP_NV(tile);   /* MATCH pin: retail delay-slot fill depends on it */
        scratch = width << 16;
        signed_width = scratch >> 16;
        has_columns = tile < signed_width;
        scratch = y << 16;
        signed_y = scratch >> 16;
        scratch = x << 16;
        signed_x = scratch >> 16;
outer:
        col = 0;
        if (has_columns) {
            scratch = row << 16;
            scratch >>= 16;
            scratch += signed_y;
            row_odd = scratch & 1;
            scratch = (s32)TOWN_TILE_PAGE;
            ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
            tilemap = (u16 *)(scratch + 0x2004);
inner:
            ASM_KEEP_NV(row);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            scratch = row + raw_y;
            scratch <<= 7;
            scratch = col + scratch;
            index = raw_x + scratch;
            ASM_KEEP_NV(index);   /* MATCH pin: retail delay-slot fill depends on it */
            x = index;
            tile = *src;
            switch (tile) {
            case 0:
                break;

            case 0x135:
            case 0x137:
            case 0x154:
            case 0x15E:
                if (row_odd != 0) {
                    if (((s16)col + signed_x) & 1) {
                        OUTPUT_TILE(0x15E);
                    } else {
                        OUTPUT_TILE(0x137);
                    }
                } else if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE(0x154);
                } else {
                    OUTPUT_TILE(0x135);
                }

            case 0x136:
            case 0x138:
            case 0x153:
            case 0x15D:
                if (row_odd != 0) {
                    if (((s16)col + signed_x) & 1) {
                        OUTPUT_TILE(0x138);
                    } else {
                        OUTPUT_TILE(0x15D);
                    }
                } else if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE(0x136);
                } else {
                    OUTPUT_TILE(0x153);
                }

            case 0x141:
            case 0x142:
                if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE(0x142);
                } else {
                    OUTPUT_TILE(0x141);
                }

            case 0x143:
            case 0x144:
            case 0x15B:
            case 0x15C:
                if (row_odd != 0) {
                    if (((s16)col + signed_x) & 1) {
                        OUTPUT_TILE(0x144);
                    } else {
                        OUTPUT_TILE(0x143);
                    }
                } else if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE(0x15C);
                } else {
                    OUTPUT_TILE(0x15B);
                }

            case 0x13D:
            case 0x13E:
            case 0x13F:
            case 0x140:
                if (row_odd != 0) {
                    if (((s16)col + signed_x) & 1) {
                        OUTPUT_TILE_INDEX(0x140);
                    } else {
                        OUTPUT_TILE_INDEX(0x13F);
                    }
                } else if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE_INDEX(0x13E);
                } else {
                    OUTPUT_TILE_INDEX(0x13D);
                }

            case 0x149:
            case 0x14A:
            case 0x14B:
            case 0x14C:
                if (row_odd != 0) {
                    if (((s16)col + signed_x) & 1) {
                        OUTPUT_TILE_INDEX(0x14C);
                    } else {
                        OUTPUT_TILE_INDEX(0x14B);
                    }
                } else if (((s16)col + signed_x) & 1) {
                    OUTPUT_TILE_INDEX(0x14A);
                } else {
                    OUTPUT_TILE_INDEX(0x149);
                }

            default:
                scratch = (s16)x;
                scratch *= 2;
                ASM_MEM_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                tile = *src;
                scratch += (s32)tilemap;
                dst = (u16 *)scratch;
store:
                *dst = tile;
                break;
            }
            scratch = col + 1;
            col = scratch;
            src++;
            scratch <<= 16;
            scratch >>= 16;
            if (scratch < signed_width) {
                goto inner;
            }
        }
        scratch = row + 1;
        row = scratch;
        ASM_KEEP_NV(height);   /* MATCH pin: load-bearing for the whole function shape */
        scratch <<= 16;
        tile = height << 16;
        if (scratch < tile) {
            goto outer;
        }
    }
}
