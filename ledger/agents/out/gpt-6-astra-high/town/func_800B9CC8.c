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
    dst_tile = (u16 *)scratch; \
    tile = (value); \
    goto store; \
} while (0)

#define OUTPUT_TILE_INDEX(value) do { \
    scratch = (s16)tile_index; \
    scratch *= 2; \
    scratch += (s32)tilemap; \
    dst_tile = (u16 *)scratch; \
    tile = (value); \
    goto store; \
} while (0)

/* Copies nonzero tiles into the town tilemap, selecting variants by map coordinate parity. */
void func_800B7428(s32 x, s32 y, u16 *src_tiles)
{
    s32 width;
    register s32 height ASM_REG("$15");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 row;
    s32 col;
    s32 tile;
    register s32 tile_index ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 scratch ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 map_row_odd;
    s32 signed_width;
    s32 has_columns;
    register s32 origin_x_s16 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    register s32 origin_y_s16 ASM_REG("$24");   /* MATCH pin: retail keeps a computation the compiler would drop */
    register s32 origin_x ASM_REG("$14");   /* MATCH pin: retail register colouring depends on it */
    register s32 origin_y ASM_REG("$13");   /* MATCH pin: load-bearing for the whole function shape */
    u16 *dst_tile;
    register u16 *tilemap ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

    width = *src_tiles++;
    height = *src_tiles++;
    row = 0;
    origin_x = x;
    origin_y = y;
    scratch = height << 16;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    if (scratch > 0) {
        tile = 0;
        ASM_KEEP_NV(tile);   /* MATCH pin: retail delay-slot fill depends on it */
        scratch = width << 16;
        signed_width = scratch >> 16;
        has_columns = tile < signed_width;
        scratch = y << 16;
        origin_y_s16 = scratch >> 16;
        scratch = x << 16;
        origin_x_s16 = scratch >> 16;
outer:
        col = 0;
        if (has_columns) {
            scratch = row << 16;
            scratch >>= 16;
            scratch += origin_y_s16;
            map_row_odd = scratch & 1;
            scratch = (s32)TOWN_TILE_PAGE;
            ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
            tilemap = (u16 *)(scratch + 0x2004);
inner:
            ASM_KEEP_NV(row);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            scratch = row + origin_y;
            scratch <<= 7;
            scratch = col + scratch;
            tile_index = origin_x + scratch;
            ASM_KEEP_NV(tile_index);   /* MATCH pin: retail delay-slot fill depends on it */
            x = tile_index;
            tile = *src_tiles;
            switch (tile) {
            case 0:
                break;

            case 0x135:
            case 0x137:
            case 0x154:
            case 0x15E:
                if (map_row_odd != 0) {
                    if (((s16)col + origin_x_s16) & 1) {
                        OUTPUT_TILE(0x15E);
                    } else {
                        OUTPUT_TILE(0x137);
                    }
                } else if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE(0x154);
                } else {
                    OUTPUT_TILE(0x135);
                }

            case 0x136:
            case 0x138:
            case 0x153:
            case 0x15D:
                if (map_row_odd != 0) {
                    if (((s16)col + origin_x_s16) & 1) {
                        OUTPUT_TILE(0x138);
                    } else {
                        OUTPUT_TILE(0x15D);
                    }
                } else if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE(0x136);
                } else {
                    OUTPUT_TILE(0x153);
                }

            case 0x141:
            case 0x142:
                if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE(0x142);
                } else {
                    OUTPUT_TILE(0x141);
                }

            case 0x143:
            case 0x144:
            case 0x15B:
            case 0x15C:
                if (map_row_odd != 0) {
                    if (((s16)col + origin_x_s16) & 1) {
                        OUTPUT_TILE(0x144);
                    } else {
                        OUTPUT_TILE(0x143);
                    }
                } else if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE(0x15C);
                } else {
                    OUTPUT_TILE(0x15B);
                }

            case 0x13D:
            case 0x13E:
            case 0x13F:
            case 0x140:
                if (map_row_odd != 0) {
                    if (((s16)col + origin_x_s16) & 1) {
                        OUTPUT_TILE_INDEX(0x140);
                    } else {
                        OUTPUT_TILE_INDEX(0x13F);
                    }
                } else if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE_INDEX(0x13E);
                } else {
                    OUTPUT_TILE_INDEX(0x13D);
                }

            case 0x149:
            case 0x14A:
            case 0x14B:
            case 0x14C:
                if (map_row_odd != 0) {
                    if (((s16)col + origin_x_s16) & 1) {
                        OUTPUT_TILE_INDEX(0x14C);
                    } else {
                        OUTPUT_TILE_INDEX(0x14B);
                    }
                } else if (((s16)col + origin_x_s16) & 1) {
                    OUTPUT_TILE_INDEX(0x14A);
                } else {
                    OUTPUT_TILE_INDEX(0x149);
                }

            default:
                scratch = (s16)x;
                scratch *= 2;
                ASM_MEM_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                tile = *src_tiles;
                scratch += (s32)tilemap;
                dst_tile = (u16 *)scratch;
store:
                *dst_tile = tile;
                break;
            }
            scratch = col + 1;
            col = scratch;
            src_tiles++;
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
