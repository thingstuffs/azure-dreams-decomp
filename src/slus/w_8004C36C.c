#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v);
extern void RotMatrix(void *r, void *m);
extern void CompMatrix(void *m0, void *m1, void *m2);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern s32 func_8004C010(void *dst, void *tint);
extern void *func_8004C080(void *t0, void *t1, void *packet, void *record,
                           void *cmd, s32 *count);
extern void *D_80083160[3];

/* Transform and tint sprites from node lists, then link their packets into the ordering table. */
void func_8004C36C(u8 *parent, u8 *node)
{
    u8 work_buf[0x110];
    s32 packet_count;
    u8 *work;
    u8 *packet;
    u8 *node_matrix;
    u8 *sprite_matrix;
    u32 addr_mask;
    register u32 size_mask ASM_REG("$22");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u8 *cmd;
    u8 *parent_matrix;
    u8 *rotation;
    u8 *render_ctx;
    u8 **render_state;
    register s32 coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    node_matrix = work_buf + 0xE4;
    sprite_matrix = work_buf + 0x7C;
    addr_mask = 0xFFFFFF;
    render_state = (u8 **)D_80083160;
    render_ctx = (u8 *)D_80083160[0];
    size_mask = 0xFF000000;
    work = work_buf;
    packet = *(u8 **)(render_ctx + 0x8D0);
    U32_AT(work, 0x18) = (u32)(render_ctx + 0x70);
    U32_AT(work, 0x38) = 0;
    PushMatrix();
    U16_AT(work, 0x74) = 0;
    U16_AT(work, 0x6C) = 0;
    U16_AT(work, 0x64) = 0;
    U16_AT(work, 0x5C) = 0;

top:
    if (node == 0) {
        goto tail;
    }
    rotation = work + 0x50;
    U32_AT(work, 0xB8) = U32_AT(U32_AT(node, 8), 0);
    U32_AT(work, 0xBC) = U32_AT(U32_AT(node, 8), 4);
    parent_matrix = work + 0xC4;
    U32_AT(work, 0xC0) = U32_AT(U32_AT(node, 8), 8);
    U32_AT(work, 0x20) = S16_AT(U32_AT(node, 4), 8) + S16_AT(work, 0xBE);
    U32_AT(work, 0x24) = S16_AT(U32_AT(node, 4), 0xA) + S16_AT(work, 0xC0);
    {
        s32 trans_z = S16_AT(U32_AT(node, 4), 0xC) + S16_AT(work, 0xC2);
        U32_AT(work, 0x50) = U32_AT(work, 0xB8);
        U32_AT(work, 0x54) = U32_AT(work, 0xBC);
        U32_AT(work, 0x28) = trans_z;
    }
    RotMatrix(rotation, parent_matrix);
    TransMatrix(parent_matrix, work + 0x20);
    U32_AT(work, 0x40) = S16_AT(U32_AT(node, 4), 4);
    U32_AT(work, 0x44) = S16_AT(U32_AT(node, 4), 6);
    U32_AT(work, 0x78) = U32_AT(U32_AT(node, 4), 0);
    U32_AT(work, 0x10C) = U8_AT(U32_AT(node, 4), 0xF);

walk:
    node = *(u8 **)(node + 0xC);
    if (node == 0) {
        goto tail;
    }
    cmd = *(u8 **)(node + 0);
    if (cmd == 0) {
        goto walk;
    }
    rotation = work + 0x50;
    U32_AT(work, 0xA8) = U32_AT(U32_AT(node, 4), 0);
    U32_AT(work, 0xAC) = U32_AT(U32_AT(node, 4), 4);
    U32_AT(work, 0xB0) = U32_AT(U32_AT(node, 4), 8);
    U32_AT(work, 0xB4) = U32_AT(U32_AT(node, 4), 0xC);
    U32_AT(work, 0x50) = U32_AT(U32_AT(node, 8), 0);
    U32_AT(work, 0x54) = U32_AT(U32_AT(node, 8), 4);
    RotMatrix(rotation, node_matrix);
    U32_AT(work, 0x20) = S16_AT(U32_AT(node, 8), 6);
    U32_AT(work, 0x24) = S16_AT(U32_AT(node, 8), 8);
    U32_AT(work, 0x28) = S16_AT(U32_AT(node, 8), 0xA) + S16_AT(work, 0xB4);
    TransMatrix(node_matrix, work + 0x20);
    CompMatrix(work + 0xC4, node_matrix, sprite_matrix);
    U32_AT(work, 0x30) = S16_AT(work, 0xAC);
    U32_AT(work, 0x34) = S16_AT(work, 0xAE);
    ScaleMatrix(sprite_matrix, work + 0x30);
    ScaleMatrix(sprite_matrix, work + 0x40);
    SetRotMatrix(sprite_matrix);
    SetTransMatrix(sprite_matrix);

command:
    U32_AT(work, 0x00) = U32_AT(cmd, 0);
    U32_AT(work, 0x04) = U32_AT(cmd, 4);
    U32_AT(work, 0x08) = U32_AT(cmd, 8);
    if (U32_AT(work, 8) != 0) {
        if (U8_AT(work, 0) & 1) {
            s32 offset_x = U8_AT(work, 2);
            u32 origin_x = U16_AT(work, 0xB0);
            u32 trans_x = U16_AT(work, 0x20);
            ASM_KEEP_DEP_NV(offset_x, origin_x);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(offset_x, trans_x);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            coord = origin_x - ((offset_x << 24) >> 24) - trans_x - U16_AT(work, 0xBE);
            S16_AT(work, 0x68) = coord;
            S16_AT(work, 0x58) = coord;
            coord = coord - U8_AT(work, 0xA);
        } else {
            s32 offset_x = U8_AT(work, 2);
            u32 origin_x = U16_AT(work, 0xB0);
            u32 trans_x = U16_AT(work, 0x20);
            ASM_KEEP_DEP_NV(offset_x, origin_x);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(offset_x, trans_x);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            coord = origin_x + ((offset_x << 24) >> 24) - trans_x - U16_AT(work, 0xBE);
            S16_AT(work, 0x68) = coord;
            S16_AT(work, 0x58) = coord;
            coord = coord + U8_AT(work, 0xA);
        }
        S16_AT(work, 0x70) = coord;
        S16_AT(work, 0x60) = coord;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        if (U8_AT(work, 0) & 2) {
            s32 offset_y = U8_AT(work, 3);
            u32 origin_y = U16_AT(work, 0xB2);
            u32 trans_y = U16_AT(work, 0x24);
            ASM_KEEP_DEP_NV(offset_y, origin_y);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(offset_y, trans_y);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            coord = origin_y - ((offset_y << 24) >> 24) - trans_y - U16_AT(work, 0xC0);
            S16_AT(work, 0x62) = coord;
            S16_AT(work, 0x5A) = coord;
            coord = coord - U8_AT(work, 0xB);
        } else {
            s32 offset_y = U8_AT(work, 3);
            u32 origin_y = U16_AT(work, 0xB2);
            u32 trans_y = U16_AT(work, 0x24);
            ASM_KEEP_DEP_NV(offset_y, origin_y);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(offset_y, trans_y);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            coord = origin_y + ((offset_y << 24) >> 24) - trans_y - U16_AT(work, 0xC0);
            S16_AT(work, 0x62) = coord;
            S16_AT(work, 0x5A) = coord;
            coord = coord + U8_AT(work, 0xB);
        }
        S16_AT(work, 0x72) = coord;
        S16_AT(work, 0x6A) = coord;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        gte_ldv3(work + 0x58, work + 0x60, work + 0x68);
        gte_rtpt();
        gte_stsxy3(packet + 8, packet + 0x10, packet + 0x18);
        gte_ldv0(work + 0x70);
        gte_rtps();
        gte_stsxy(packet + 0x20);
    }

    {
        register s32 opcode ASM_REG("$3") = U8_AT(work, 1) & 0xFC;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        if (opcode != 0x2C) goto big;
    }
    {
        if (U8_AT(work, 8) + U8_AT(work, 0xA) >= 0x100) {
            U8_AT(work, 0xA) = U8_AT(work, 0xA) - 1;
        }
        if (U8_AT(work, 9) + U8_AT(work, 0xB) >= 0x100) {
            U8_AT(work, 0xB) = U8_AT(work, 0xB) - 1;
        }
        S8_AT(packet, 3) = 9;
        U32_AT(packet, 4) = U32_AT(work, 0xA8);
        func_8004C010(packet + 4, work + 0x78);
        {
            u8 gpu_code = U8_AT(work, 1);
            register u8 tex_u ASM_REG("$4") = U8_AT(work, 8);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register s32 screen_x0 ASM_REG("$5") = S16_AT(packet, 8);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register s32 screen_x1 ASM_REG("$2") = S16_AT(packet, 0x10);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            U8_AT(packet, 7) = gpu_code;
            U8_AT(packet, 0xC) = tex_u;
            {
                u16 clut = U16_AT(work, 6);
                u8 tex_v = U8_AT(work, 9);
                U16_AT(packet, 0xE) = clut;
                U8_AT(packet, 0xD) = tex_v;
                if (screen_x1 < screen_x0 || screen_x0 != S16_AT(packet, 0x18)) {
                    U8_AT(work, 0xA) = U8_AT(work, 0xA) - 1;
                }
            }
        }
        {
            register u8 tex_u ASM_REG("$3") = U8_AT(work, 8);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register u8 tex_width ASM_REG("$2") = U8_AT(work, 0xA);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            u8 tex_v = U8_AT(work, 9);
            s32 screen_y0 = S16_AT(packet, 0xA);
            register u8 tex_right ASM_REG("$3") = tex_u + tex_width;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            U8_AT(packet, 0x24) = tex_right;
            U8_AT(packet, 0x14) = tex_right;
            U8_AT(packet, 0x15) = tex_v;
            {
                register u8 left_u ASM_REG("$4") = U8_AT(work, 8);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                s32 screen_y2 = S16_AT(packet, 0x1A);
                u16 tex_page;
                tex_page = U16_AT(work, 4);
                U16_AT(packet, 0x16) = tex_page;
                U8_AT(packet, 0x1C) = left_u;
                if (screen_y2 < screen_y0 || screen_y0 != S16_AT(packet, 0x12)) {
                    U8_AT(work, 0xB) = U8_AT(work, 0xB) - 1;
                }
            }
        }
        {
            register u8 tex_v ASM_REG("$3") = U8_AT(work, 9);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register u8 tex_height ASM_REG("$2") = U8_AT(work, 0xB);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            register u8 tex_bottom ASM_REG("$3") = tex_v + tex_height;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            U8_AT(packet, 0x25) = tex_bottom;
            U8_AT(packet, 0x1D) = tex_bottom;
        }
        {
            u32 *ot = (u32 *)((U8_AT(work, 0xB7) << 2)
                              + ((U32_AT(work, 0x10C) << 2) + U32_AT(work, 0x18)));
            U32_AT(packet, 0) = (U32_AT(packet, 0) & size_mask) | (*ot & addr_mask);
        }
        {
            u32 *ot = (u32 *)((U8_AT(work, 0xB7) << 2)
                              + ((U32_AT(work, 0x10C) << 2) + U32_AT(work, 0x18)));
            *ot = (*ot & size_mask) | ((u32)packet & addr_mask);
        }
        {
            u8 packet_words = U8_AT(packet, 3);
            u8 *packet_end;
            cmd = cmd + 0xC;
            packet_end = packet + (packet_words << 2);
            packet = packet_end + 4;
        }
        goto next;
    }

big:
    packet_count = 1;
    cmd = (u8 *)func_8004C080(work + 0x78, work + 0xA8, packet, cmd, work, &packet_count);
    packet_count = packet_count - 1;
    if (packet_count != -1) {
        s32 stop_count = -1;
        do {
            {
                u32 *ot = (u32 *)((U8_AT(work, 0xB7) << 2)
                                  + ((U32_AT(work, 0x10C) << 2) + U32_AT(work, 0x18)));
                U32_AT(packet, 0) = (U32_AT(packet, 0) & size_mask) | (*ot & addr_mask);
            }
            {
                u32 *ot = (u32 *)((U8_AT(work, 0xB7) << 2)
                                  + ((U32_AT(work, 0x10C) << 2) + U32_AT(work, 0x18)));
                *ot = (*ot & size_mask) | ((u32)packet & addr_mask);
            }
            {
                s32 remaining;
                u8 packet_words;
                u8 *packet_end;
                remaining = packet_count;
                packet_words = U8_AT(packet, 3);
                remaining = remaining - 1;
                packet_end = packet + (packet_words << 2);
                packet = packet_end + 4;
                packet_count = remaining;
            }
        } while (packet_count != stop_count);
    }
    cmd = cmd + 0xC;

next:
    if (!(U8_AT(work, 0) & 0x80)) {
        goto command;
    }
    goto walk;

tail:
    {
        u8 *next_parent = *(u8 **)(parent - 8);
        if (next_parent != 0) {
            parent = next_parent + 0x20;
            node = *(u8 **)(next_parent + 0xC);
            goto top;
        }
    }
    PopMatrix();
    *(u8 **)(render_state[0] + 0x8D0) = packet;
}
