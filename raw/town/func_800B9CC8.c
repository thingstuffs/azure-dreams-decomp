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
    register s32 width ASM_REG("$7");
    register s32 height ASM_REG("$15");
    register s32 row ASM_REG("$11");
    register s32 col ASM_REG("$7");
    s32 tile;
    register s32 index ASM_REG("$5");
    register s32 scratch ASM_REG("$2");
    register s32 row_odd ASM_REG("$10");
    register s32 signed_width ASM_REG("$12");
    register s32 has_columns ASM_REG("$25");
    register s32 signed_x ASM_REG("$9");
    register s32 signed_y ASM_REG("$24");
    register s32 raw_x ASM_REG("$14");
    register s32 raw_y ASM_REG("$13");
    u16 *dst;
    register u16 *tilemap ASM_REG("$8");

    width = *src++;
    height = *src++;
    row = 0;
    raw_x = x;
    raw_y = y;
    scratch = height << 16;
    ASM_KEEP_NV(scratch);
    if (scratch > 0) {
        tile = 0;
        ASM_KEEP_NV(tile);
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
            ASM_KEEP_NV(scratch);
            tilemap = (u16 *)(scratch + 0x2004);
inner:
            ASM_KEEP_NV(row);
            scratch = row + raw_y;
            scratch <<= 7;
            scratch = col + scratch;
            index = raw_x + scratch;
            ASM_KEEP_NV(index);
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
                ASM_MEM_BARRIER();
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
        ASM_KEEP_NV(height);
        scratch <<= 16;
        tile = height << 16;
        if (scratch < tile) {
            goto outer;
        }
    }
}
