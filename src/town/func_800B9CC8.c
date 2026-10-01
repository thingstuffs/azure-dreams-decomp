#include "common.h"

extern u16 D_80162004[];

/* Copies nonzero tiles into the town tilemap, selecting variants by map coordinate parity. */
void func_800B7428(s16 x, s16 y, u16 *src_tiles)
{
    s16 width;
    s16 height;
    s16 row;
    s16 col;
    s16 index;

    width = *src_tiles++;
    height = *src_tiles++;
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            index = ((row + y) << 7) + col + x;
            switch (*src_tiles) {
            case 0:
                break;
            case 0x135:
            case 0x137:
            case 0x154:
            case 0x15E:
            if ((row + y) & 1) {
                if ((col + x) & 1) {
                    D_80162004[index] = 0x15E;
                } else {
                    D_80162004[index] = 0x137;
                }
            } else if ((col + x) & 1) {
                D_80162004[index] = 0x154;
            } else {
                D_80162004[index] = 0x135;
            }
            break;
            case 0x136:
            case 0x138:
            case 0x153:
            case 0x15D:
            if ((row + y) & 1) {
                if ((col + x) & 1) {
                    D_80162004[index] = 0x138;
                } else {
                    D_80162004[index] = 0x15D;
                }
            } else if ((col + x) & 1) {
                D_80162004[index] = 0x136;
            } else {
                D_80162004[index] = 0x153;
            }
            break;
            case 0x141:
            case 0x142:
                if ((col + x) & 1) {
                    D_80162004[index] = 0x142;
                } else {
                    D_80162004[index] = 0x141;
                }
                break;
            case 0x143:
            case 0x144:
            case 0x15B:
            case 0x15C:
            if ((row + y) & 1) {
                if ((col + x) & 1) {
                    D_80162004[index] = 0x144;
                } else {
                    D_80162004[index] = 0x143;
                }
            } else if ((col + x) & 1) {
                D_80162004[index] = 0x15C;
            } else {
                D_80162004[index] = 0x15B;
            }
            break;
            case 0x13D:
            case 0x13E:
            case 0x13F:
            case 0x140:
            if ((row + y) & 1) {
                if ((col + x) & 1) {
                    D_80162004[index] = 0x140;
                } else {
                    D_80162004[index] = 0x13F;
                }
            } else if ((col + x) & 1) {
                D_80162004[index] = 0x13E;
            } else {
                D_80162004[index] = 0x13D;
            }
            break;
            case 0x149:
            case 0x14A:
            case 0x14B:
            case 0x14C:
            if ((row + y) & 1) {
                if ((col + x) & 1) {
                    D_80162004[index] = 0x14C;
                } else {
                    D_80162004[index] = 0x14B;
                }
            } else if ((col + x) & 1) {
                D_80162004[index] = 0x14A;
            } else {
                D_80162004[index] = 0x149;
            }
            break;
            default:
                D_80162004[index] = *src_tiles;
                break;
            }
            src_tiles++;
        }
    }
}
