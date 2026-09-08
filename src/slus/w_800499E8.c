#include "common.h"

extern u8 D_80080B28[16];
extern u8 D_80080B2C[16];
extern void bzero(void *, s32);

/* Builds a tinted rectangle with gradient top and bottom bands. */
void *func_800499E8(u8 *cmd, u8 *rect, u8 *tint)
{
    u8 edge_color[4];
    u8 center_color[4];
    u32 top_edge;
    u32 bottom_edge;
    u32 top_center;
    u32 bottom_center;
    u8 *start;

    memcpy(edge_color, D_80080B28, 4);
    memcpy(center_color, D_80080B2C, 4);
    bzero(cmd, 0x14);

    if ((*(s32 *)tint & 0xFFFFFF) != 0x808080) {
        edge_color[0] = (edge_color[0] * tint[0]) >> 7;
        edge_color[1] = (edge_color[1] * tint[1]) >> 7;
        edge_color[2] = (edge_color[2] * tint[2]) >> 7;
        if ((*(s32 *)tint & 0xFFFFFF) != 0x808080) {
            center_color[0] = (center_color[0] * tint[0]) >> 7;
            center_color[1] = (center_color[1] * tint[1]) >> 7;
            center_color[2] = (center_color[2] * tint[2]) >> 7;
        }
    }

    cmd[1] = 0x38;
    top_edge = *(u32 *)edge_color;
    top_center = *(u32 *)center_color;
    *(u32 *)(cmd + 4) = top_edge;
    *(u32 *)(cmd + 0xC) = top_edge;
    *(u32 *)(cmd + 0x10) = top_center;
    *(u32 *)(cmd + 0x14) = top_center;
    cmd[2] = rect[0];
    cmd[3] = rect[2];
    cmd[0xA] = rect[4];
    cmd[0xB] = *(s16 *)(rect + 6) / 4;

    cmd += 0x18;
    cmd[1] = 0x28;
    *(u32 *)(cmd + 4) = *(u32 *)center_color;
    cmd[2] = rect[0];
    cmd[3] = rect[2] + *(s16 *)(rect + 6) / 4;
    cmd[0xA] = rect[4];
    cmd[0xB] = *(s16 *)(rect + 6) / 2;

    cmd += 0xC;
    cmd[1] = 0x38;
    bottom_center = *(u32 *)center_color;
    bottom_edge = *(u32 *)edge_color;
    *(u32 *)(cmd + 4) = bottom_center;
    *(u32 *)(cmd + 0xC) = bottom_center;
    *(u32 *)(cmd + 0x10) = bottom_edge;
    *(u32 *)(cmd + 0x14) = bottom_edge;
    cmd[2] = rect[0];
    cmd[3] = rect[2] + *(s16 *)(rect + 6) / 4 + *(s16 *)(rect + 6) / 2;
    cmd[0xA] = rect[4];
    cmd[0xB] = rect[6] - *(s16 *)(rect + 6) / 4 - *(s16 *)(rect + 6) / 2;

    cmd += 0x18;
    start = cmd - 0x3C;
    ASM_USE_NV(start);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    cmd[1] = 0x81;
    *(u16 *)(cmd + 4) = 0x10;
    *(u16 *)(cmd + 6) = 1;
    cmd[0] |= 0x80;

    return start;
}
