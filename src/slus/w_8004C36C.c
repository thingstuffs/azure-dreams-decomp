/* func_8004C36C -- byte-exact, gcc-2.7.2-cdk -O2 (aspsx 2.56); psyq4.1 O2 ties.
 *
 * Walks a two-level node list and emits one GPU packet per sprite command,
 * OT-linking each packet as it goes.
 *
 * LOCAL FRAME (total 0x158 = 0x18 outgoing-arg area + 0x110 buf + 4 count
 * + 0x28 for the ten saved registers ra/fp/s7..s0):
 *   buf   -> sp+0x18  ($s1)   the whole 0x110 work block; gcc's cse rewrites
 *                             every stack access relative to it once &buf is
 *                             live in a callee-saved register for the loop.
 *     +0x00 12B command record (copied from the command list, passed to
 *           func_8004C080 as its `cmd` argument)
 *     +0x18 OT base pointer (= D_80083160[0] + 0x70)
 *     +0x20 VECTOR translation   +0x30/+0x40 VECTOR scale x2
 *     +0x50 SVECTOR rotation     +0x58/+0x60/+0x68/+0x70 the four quad corners
 *     +0x78 tint0   +0x7C MATRIX ($s5 = sp+0x94)
 *     +0xA8 16B node info (tint1 at +0xA8, prio byte at +0xB7)
 *     +0xB8 12B pose (3 rot s16 + 3 trans s16)
 *     +0xC4 MATRIX ($s0)   +0xE4 MATRIX ($s7 = sp+0xFC)
 *     +0x10C texture-page index
 *   count -> sp+0x128         packet counter shared with func_8004C080
 *
 * gte_stsxy3() below is the three-DISTINCT-address SXY0/SXY1/SXY2 store group
 * (retail 8004C774/8/C: swc2 $12/$13/$14 through three separate bases).  It is
 * NOT gte_stsxy3_g3, which folds one base with the POLY_G3 offsets 8/16/24.
 * OWNER ITEM: move this macro into include/common.h beside gte_stsxy3_g3 (with
 * the matching NON_MATCHING arm) -- then match.py needs no --allow-asm.
 */
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

void func_8004C36C(u8 *parent, u8 *node)
{
    u8 buf[0x110];
    s32 count;
    u8 *L;
    u8 *packet;
    u8 *m7;
    u8 *m5;
    u32 mask_lo;
    register u32 mask_hi ASM_REG("$22");   /* MATCH pin: slus-diff */
    u8 *cmd;
    u8 *m0;
    u8 *rot0;
    u8 *ctx;
    u8 **root;
    register s32 t ASM_REG("$2");   /* MATCH pin: slus-diff */

    m7 = buf + 0xE4;
    m5 = buf + 0x7C;
    mask_lo = 0xFFFFFF;
    root = (u8 **)D_80083160;
    ctx = (u8 *)D_80083160[0];
    mask_hi = 0xFF000000;
    L = buf;
    packet = *(u8 **)(ctx + 0x8D0);
    U32_AT(L, 0x18) = (u32)(ctx + 0x70);
    U32_AT(L, 0x38) = 0;
    PushMatrix();
    U16_AT(L, 0x74) = 0;
    U16_AT(L, 0x6C) = 0;
    U16_AT(L, 0x64) = 0;
    U16_AT(L, 0x5C) = 0;

top:
    if (node == 0) {
        goto tail;
    }
    rot0 = L + 0x50;
    U32_AT(L, 0xB8) = U32_AT(U32_AT(node, 8), 0);
    U32_AT(L, 0xBC) = U32_AT(U32_AT(node, 8), 4);
    m0 = L + 0xC4;
    U32_AT(L, 0xC0) = U32_AT(U32_AT(node, 8), 8);
    U32_AT(L, 0x20) = S16_AT(U32_AT(node, 4), 8) + S16_AT(L, 0xBE);
    U32_AT(L, 0x24) = S16_AT(U32_AT(node, 4), 0xA) + S16_AT(L, 0xC0);
    {
        s32 z = S16_AT(U32_AT(node, 4), 0xC) + S16_AT(L, 0xC2);
        U32_AT(L, 0x50) = U32_AT(L, 0xB8);
        U32_AT(L, 0x54) = U32_AT(L, 0xBC);
        U32_AT(L, 0x28) = z;
    }
    RotMatrix(rot0, m0);
    TransMatrix(m0, L + 0x20);
    U32_AT(L, 0x40) = S16_AT(U32_AT(node, 4), 4);
    U32_AT(L, 0x44) = S16_AT(U32_AT(node, 4), 6);
    U32_AT(L, 0x78) = U32_AT(U32_AT(node, 4), 0);
    U32_AT(L, 0x10C) = U8_AT(U32_AT(node, 4), 0xF);

walk:
    node = *(u8 **)(node + 0xC);
    if (node == 0) {
        goto tail;
    }
    cmd = *(u8 **)(node + 0);
    if (cmd == 0) {
        goto walk;
    }
    rot0 = L + 0x50;
    U32_AT(L, 0xA8) = U32_AT(U32_AT(node, 4), 0);
    U32_AT(L, 0xAC) = U32_AT(U32_AT(node, 4), 4);
    U32_AT(L, 0xB0) = U32_AT(U32_AT(node, 4), 8);
    U32_AT(L, 0xB4) = U32_AT(U32_AT(node, 4), 0xC);
    U32_AT(L, 0x50) = U32_AT(U32_AT(node, 8), 0);
    U32_AT(L, 0x54) = U32_AT(U32_AT(node, 8), 4);
    RotMatrix(rot0, m7);
    U32_AT(L, 0x20) = S16_AT(U32_AT(node, 8), 6);
    U32_AT(L, 0x24) = S16_AT(U32_AT(node, 8), 8);
    U32_AT(L, 0x28) = S16_AT(U32_AT(node, 8), 0xA) + S16_AT(L, 0xB4);
    TransMatrix(m7, L + 0x20);
    CompMatrix(L + 0xC4, m7, m5);
    U32_AT(L, 0x30) = S16_AT(L, 0xAC);
    U32_AT(L, 0x34) = S16_AT(L, 0xAE);
    ScaleMatrix(m5, L + 0x30);
    ScaleMatrix(m5, L + 0x40);
    SetRotMatrix(m5);
    SetTransMatrix(m5);

command:
    U32_AT(L, 0x00) = U32_AT(cmd, 0);
    U32_AT(L, 0x04) = U32_AT(cmd, 4);
    U32_AT(L, 0x08) = U32_AT(cmd, 8);
    if (U32_AT(L, 8) != 0) {
        if (U8_AT(L, 0) & 1) {
            s32 raw = U8_AT(L, 2);
            u32 b = U16_AT(L, 0xB0);
            u32 d = U16_AT(L, 0x20);
            ASM_KEEP_DEP_NV(raw, b);   /* MATCH pin: slus-diff */
            ASM_KEEP_DEP_NV(raw, d);   /* MATCH pin: slus-diff */
            t = b - ((raw << 24) >> 24) - d - U16_AT(L, 0xBE);
            S16_AT(L, 0x68) = t;
            S16_AT(L, 0x58) = t;
            t = t - U8_AT(L, 0xA);
        } else {
            s32 raw = U8_AT(L, 2);
            u32 b = U16_AT(L, 0xB0);
            u32 d = U16_AT(L, 0x20);
            ASM_KEEP_DEP_NV(raw, b);   /* MATCH pin: slus-diff */
            ASM_KEEP_DEP_NV(raw, d);   /* MATCH pin: slus-diff */
            t = b + ((raw << 24) >> 24) - d - U16_AT(L, 0xBE);
            S16_AT(L, 0x68) = t;
            S16_AT(L, 0x58) = t;
            t = t + U8_AT(L, 0xA);
        }
        S16_AT(L, 0x70) = t;
        S16_AT(L, 0x60) = t;
        ASM_KEEP(L);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        if (U8_AT(L, 0) & 2) {
            s32 raw = U8_AT(L, 3);
            u32 b = U16_AT(L, 0xB2);
            u32 d = U16_AT(L, 0x24);
            ASM_KEEP_DEP_NV(raw, b);   /* MATCH pin: slus-diff */
            ASM_KEEP_DEP_NV(raw, d);   /* MATCH pin: slus-diff */
            t = b - ((raw << 24) >> 24) - d - U16_AT(L, 0xC0);
            S16_AT(L, 0x62) = t;
            S16_AT(L, 0x5A) = t;
            t = t - U8_AT(L, 0xB);
        } else {
            s32 raw = U8_AT(L, 3);
            u32 b = U16_AT(L, 0xB2);
            u32 d = U16_AT(L, 0x24);
            ASM_KEEP_DEP_NV(raw, b);   /* MATCH pin: slus-diff */
            ASM_KEEP_DEP_NV(raw, d);   /* MATCH pin: slus-diff */
            t = b + ((raw << 24) >> 24) - d - U16_AT(L, 0xC0);
            S16_AT(L, 0x62) = t;
            S16_AT(L, 0x5A) = t;
            t = t + U8_AT(L, 0xB);
        }
        S16_AT(L, 0x72) = t;
        S16_AT(L, 0x6A) = t;
        ASM_KEEP(L);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        gte_ldv3(L + 0x58, L + 0x60, L + 0x68);
        gte_rtpt();
        gte_stsxy3(packet + 8, packet + 0x10, packet + 0x18);
        gte_ldv0(L + 0x70);
        gte_rtps();
        gte_stsxy(packet + 0x20);
    }

    {
        register s32 grp ASM_REG("$3") = U8_AT(L, 1) & 0xFC;   /* MATCH pin: slus-diff */
        if (grp != 0x2C) goto big;
    }
    {
        if (U8_AT(L, 8) + U8_AT(L, 0xA) >= 0x100) {
            U8_AT(L, 0xA) = U8_AT(L, 0xA) - 1;
        }
        if (U8_AT(L, 9) + U8_AT(L, 0xB) >= 0x100) {
            U8_AT(L, 0xB) = U8_AT(L, 0xB) - 1;
        }
        S8_AT(packet, 3) = 9;
        U32_AT(packet, 4) = U32_AT(L, 0xA8);
        func_8004C010(packet + 4, L + 0x78);
        {
            u8 c1 = U8_AT(L, 1);
            register u8 c8 ASM_REG("$4") = U8_AT(L, 8);   /* MATCH pin: slus-diff */
            register s32 p8 ASM_REG("$5") = S16_AT(packet, 8);   /* MATCH pin: slus-diff */
            register s32 p10 ASM_REG("$2") = S16_AT(packet, 0x10);   /* MATCH pin: slus-diff */
            U8_AT(packet, 7) = c1;
            U8_AT(packet, 0xC) = c8;
            {
                u16 c6 = U16_AT(L, 6);
                u8 c9 = U8_AT(L, 9);
                U16_AT(packet, 0xE) = c6;
                U8_AT(packet, 0xD) = c9;
                if (p10 < p8 || p8 != S16_AT(packet, 0x18)) {
                    U8_AT(L, 0xA) = U8_AT(L, 0xA) - 1;
                }
            }
        }
        {
            register u8 c8 ASM_REG("$3") = U8_AT(L, 8);   /* MATCH pin: slus-diff */
            register u8 ca ASM_REG("$2") = U8_AT(L, 0xA);   /* MATCH pin: slus-diff */
            u8 c9 = U8_AT(L, 9);
            s32 pa = S16_AT(packet, 0xA);
            register u8 sum ASM_REG("$3") = c8 + ca;   /* MATCH pin: slus-diff */
            U8_AT(packet, 0x24) = sum;
            U8_AT(packet, 0x14) = sum;
            U8_AT(packet, 0x15) = c9;
            {
                register u8 d8 ASM_REG("$4") = U8_AT(L, 8);   /* MATCH pin: slus-diff */
                s32 p1a = S16_AT(packet, 0x1A);
                u16 c4;
                c4 = U16_AT(L, 4);
                U16_AT(packet, 0x16) = c4;
                U8_AT(packet, 0x1C) = d8;
                if (p1a < pa || pa != S16_AT(packet, 0x12)) {
                    U8_AT(L, 0xB) = U8_AT(L, 0xB) - 1;
                }
            }
        }
        {
            register u8 e9 ASM_REG("$3") = U8_AT(L, 9);   /* MATCH pin: slus-diff */
            register u8 eb ASM_REG("$2") = U8_AT(L, 0xB);   /* MATCH pin: slus-diff */
            register u8 sum2 ASM_REG("$3") = e9 + eb;   /* MATCH pin: slus-diff */
            U8_AT(packet, 0x25) = sum2;
            U8_AT(packet, 0x1D) = sum2;
        }
        {
            u32 *ot = (u32 *)((U8_AT(L, 0xB7) << 2)
                              + ((U32_AT(L, 0x10C) << 2) + U32_AT(L, 0x18)));
            U32_AT(packet, 0) = (U32_AT(packet, 0) & mask_hi) | (*ot & mask_lo);
        }
        {
            u32 *ot = (u32 *)((U8_AT(L, 0xB7) << 2)
                              + ((U32_AT(L, 0x10C) << 2) + U32_AT(L, 0x18)));
            *ot = (*ot & mask_hi) | ((u32)packet & mask_lo);
        }
        {
            u8 len = U8_AT(packet, 3);
            u8 *q;
            cmd = cmd + 0xC;
            q = packet + (len << 2);
            packet = q + 4;
        }
        goto next;
    }

big:
    count = 1;
    cmd = (u8 *)func_8004C080(L + 0x78, L + 0xA8, packet, cmd, L, &count);
    count = count - 1;
    if (count != -1) {
        s32 end = -1;
        do {
            {
                u32 *ot = (u32 *)((U8_AT(L, 0xB7) << 2)
                                  + ((U32_AT(L, 0x10C) << 2) + U32_AT(L, 0x18)));
                U32_AT(packet, 0) = (U32_AT(packet, 0) & mask_hi) | (*ot & mask_lo);
            }
            {
                u32 *ot = (u32 *)((U8_AT(L, 0xB7) << 2)
                                  + ((U32_AT(L, 0x10C) << 2) + U32_AT(L, 0x18)));
                *ot = (*ot & mask_hi) | ((u32)packet & mask_lo);
            }
            {
                s32 c;
                u8 len;
                u8 *q;
                c = count;
                len = U8_AT(packet, 3);
                c = c - 1;
                q = packet + (len << 2);
                packet = q + 4;
                count = c;
            }
        } while (count != end);
    }
    cmd = cmd + 0xC;

next:
    if (!(U8_AT(L, 0) & 0x80)) {
        goto command;
    }
    goto walk;

tail:
    {
        u8 *nx = *(u8 **)(parent - 8);
        if (nx != 0) {
            parent = nx + 0x20;
            node = *(u8 **)(nx + 0xC);
            goto top;
        }
    }
    PopMatrix();
    *(u8 **)(root[0] + 0x8D0) = packet;
}
