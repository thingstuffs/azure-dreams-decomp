#include "common.h"
#include "m2c_compat.h"

typedef struct S_819AD81C_0_pre {
    u16 unk_00;
} S_819AD81C_0_pre;   /* the 0x2 bytes before entity in func_819AD81C, addressed as entity[-1] */

typedef struct S_819AD81C_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x8];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x2];
    union { struct { s16 v; } at00; struct { s32 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_3C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_40;   /* overlapping accesses */
    u16 unk_44;
    union { s16 s; u16 u; } unk_46;   /* accessed as both */
    s16 unk_48;
} S_819AD81C_0;   /* entity in func_819AD81C */

typedef struct S_819AD81C_1 {
    s32 unk_00;
    s8 unk_04;
    u8 pad_05[0x7];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_819AD81C_1;   /* gfx in func_819AD81C */

typedef struct S_819AD81C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} S_819AD81C_2;   /* motion in func_819AD81C */

typedef struct S_819AD81C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_819AD81C_3_pre;   /* the 0x14 bytes before node in func_819AD81C, addressed as node[-1] */

typedef struct S_819AD81C_3 {
    u8 pad_00[0x34];
    s16 unk_34;
    u8 pad_36[0x26];
    union { void * p; s32 i; } unk_5C;   /* accessed as both */
    u8 pad_60[0x28];
    s16 unk_88;
} S_819AD81C_3;   /* node in func_819AD81C */

typedef struct S_819AD81C_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    u8 unk_24;
    u8 unk_25;
} S_819AD81C_4;   /* info in func_819AD81C */

typedef struct S_819AD81C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819AD81C_5;   /* attached in func_819AD81C */

typedef struct S_819AD81C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819AD81C_6;   /* link in func_819AD81C */


extern int D_800814A8[4];
extern s32 D_800814A0;
M2C_UNK func_800257D0();
M2C_UNK func_80025840();
M2C_UNK func_8002590C();
M2C_UNK func_8002593C();
M2C_UNK func_80025B78();
M2C_UNK func_80025FCC();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80065450();
M2C_UNK func_8009CE1C();
s32 func_800A07D0();
s32 func_800A45D8();
M2C_UNK func_800B653C();
extern s8 D_8002758C[];
extern u8 D_800287A2;
extern s32 D_800287A4;

/* Per-frame homing-projectile step: fade in/out, fly toward the target tile, wake anything it passes and expire. */
void func_819AD81C(void *entity, void *motion, void *gfx) {
    typedef struct {
        s16 unk0;
        u16 unk2;
        s16 unk4;
        u16 unk6;
        s16 unk8;
        u16 unkA;
        s32 unkC;
        s32 unk10;
        s32 unk14;
    } Local20;
    typedef struct {
        s16 unk0;
        s16 unk2;
        s16 unk4;
    } Local38;
    Local20 warp_params;
    Local38 zero_vec;
    M2C_UNK rotated;
    s16 phase;
    s16 fade_left;
    s16 fade_left_out;
    s16 hits_left;
    s32 tile_y;
    s32 vel_x;
    register s32 sub_dest ASM_REG("$3");   /* retained from the base: preserves the two subtraction destinations */
    s32 dz;
    s8 level;
    s8 want_kind;
    u8 tint;
    u8 next_tint;
    u8 tint_out;
    u8 next_tint_out;
    u16 saved_x;
    u16 saved_y;
    void *node;
    void *attached;
    void *info;
    void *head;
    void *link;

    link = ((S_819AD81C_0 *)entity)->unk_20;
    if (link == 0) {
        phase = ((S_819AD81C_0 *)entity)->unk_2C.s;
        if (phase == 0) {
            tint = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint = tint + ((s32) (0x80 - tint) / ((S_819AD81C_0 *)entity)->unk_30);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint;
            fade_left = (u16) ((S_819AD81C_0 *)entity)->unk_30 - 1;
            ((S_819AD81C_0 *)entity)->unk_30 = fade_left;
            if ((fade_left << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0x808080;
                ((S_819AD81C_0 *)entity)->unk_2C.u = (u16) (((S_819AD81C_0 *)entity)->unk_2C.u + 1);
                goto block_10;
            }
            goto block_10;
        }
        if (phase >= 2) {
            tint_out = ((S_819AD81C_1 *)gfx)->unk_0C.at00.v;
            next_tint_out = tint_out - ((s32) tint_out / (s16) ((S_819AD81C_0 *)entity)->unk_30);
            ((S_819AD81C_1 *)gfx)->unk_0C.at00.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at01.v = next_tint_out;
            ((S_819AD81C_1 *)gfx)->unk_0C.at02.v = next_tint_out;
            fade_left_out = (u16) ((S_819AD81C_0 *)entity)->unk_30 - 1;
            ((S_819AD81C_0 *)entity)->unk_30 = fade_left_out;
            if ((fade_left_out << 0x10) <= 0) {
                ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = 0;
                goto remove_object;
            }
            if (((S_819AD81C_0 *)entity)->unk_2C.s < 3) {
                goto block_10;
            }
        } else {
block_10:
            ((S_819AD81C_2 *)motion)->unk_0C.at00.v = (s32) (func_80064584(((S_819AD81C_0 *)entity)->unk_34) << 8);
            ((S_819AD81C_2 *)motion)->unk_10.at00.v = (s32) (func_800644B8(((S_819AD81C_0 *)entity)->unk_34) << 8);
            level = ((S_819AD81C_1 *)gfx)->unk_04;
            if (level < 3) {
                vel_x = ((S_819AD81C_2 *)motion)->unk_0C.at00.v;
                ((S_819AD81C_2 *)motion)->unk_0C.at00.v = (s32) (vel_x - (vel_x >> (level + 1)));
                sub_dest = ((S_819AD81C_2 *)motion)->unk_10.at00.v;
                ((S_819AD81C_2 *)motion)->unk_10.at00.v = (s32) (sub_dest - (sub_dest >> (((S_819AD81C_1 *)gfx)->unk_04 + 1)));
            }
            ((S_819AD81C_2 *)motion)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_08.at00.v - ((S_819AD81C_2 *)motion)->unk_14);
            ((S_819AD81C_2 *)motion)->unk_00.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_00.at00.v + ((S_819AD81C_2 *)motion)->unk_0C.at00.v);
            ((S_819AD81C_2 *)motion)->unk_04.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_04.at00.v + ((S_819AD81C_2 *)motion)->unk_10.at00.v);
            ((S_819AD81C_2 *)motion)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)motion)->unk_08.at00.v + ((S_819AD81C_2 *)motion)->unk_14);
            ((S_819AD81C_1 *)gfx)->unk_16 = 0x400U;
            ((S_819AD81C_1 *)gfx)->unk_1A = (u16) (func_800A07D0(0, 0, ((S_819AD81C_2 *)motion)->unk_0C.at02.v, ((S_819AD81C_2 *)motion)->unk_10.at02.v) - 0x400);
            func_80025840(gfx, entity + 0x32, ((S_819AD81C_0 *)entity)->unk_38, ((S_819AD81C_0 *)entity)->unk_36);
            func_800257D0(entity, ((S_819AD81C_1 *)gfx)->unk_00);
            if (((S_819AD81C_1 *)gfx)->unk_14 & 0x4000) {
                ((S_819AD81C_1 *)gfx)->unk_04 = 0;
            }
            if (((S_819AD81C_0 *)entity)->unk_46.s > 0) {
                ((S_819AD81C_0 *)entity)->unk_3C.at00.v = (s16) ((s16) ((S_819AD81C_2 *)motion)->unk_00.at02.v / 64);
                tile_y = (s16) ((S_819AD81C_2 *)motion)->unk_04.at02.v / 64;
                ((S_819AD81C_0 *)entity)->unk_3C.at02.v = (s16) tile_y;
                if (((S_819AD81C_0 *)entity)->unk_40.at00.v != ((S_819AD81C_0 *)entity)->unk_3C.at00u.v) {
                    if ((func_800A45D8(((((S_819AD81C_0 *)entity)->unk_3C.at00.v << 6) + 0x20) & 0xFFE0, ((tile_y << 6) + 0x20) & 0xFFE0, ((S_819AD81C_2 *)motion)->unk_08.at02.v) << 0x10) != 0) {
                        ((S_819AD81C_0 *)entity)->unk_30 = 4;
                        ((S_819AD81C_0 *)entity)->unk_2C.s = 3;
                        return;
                    }
                    node = (void *) D_800814A8[0];
                    head = node;
                    link = ((S_819AD81C_3 *)node)->unk_5C.p;
                    node = link + 0x20;
                    if (node != head) {
                        do {
                            info = ((S_819AD81C_3_pre *)node)[-1].unk_00;
                            if (((S_819AD81C_4 *)info)->unk_24 == ((S_819AD81C_0 *)entity)->unk_3C.at00.v) {
                                if (((S_819AD81C_4 *)info)->unk_25 == ((S_819AD81C_0 *)entity)->unk_3C.at02.v) {
                                    dz = ((S_819AD81C_3 *)node)->unk_88;
                                    sub_dest = ((S_819AD81C_2 *)motion)->unk_08.at02.v;
                                    dz -= sub_dest;
                                    if (dz < 0) {
                                        dz = 0 - dz;
                                    }
                                    if (dz < 0x40) {
                                        func_8009CE1C(node, 0xC, D_800287A2, 0xA, (s32) (s16) (((S_819AD81C_0 *)entity)->unk_44 << 9), D_800287A4, 2);
                                    }
                                }
                            }
                            node = ((S_819AD81C_3 *)node)->unk_5C.i + 0x20;
                        } while (node != (void *) D_800814A8[0]);
                    }
                    saved_x = ((S_819AD81C_0 *)entity)->unk_3C.at00p.v;
                    hits_left = ((S_819AD81C_0 *)entity)->unk_46.u;
                    saved_y = ((S_819AD81C_0 *)entity)->unk_3C.at02u.v;
                    hits_left -= 1;
                    ((S_819AD81C_0 *)entity)->unk_46.s = hits_left;
                    ((S_819AD81C_0 *)entity)->unk_40.at00u.v = saved_x;
                    ((S_819AD81C_0 *)entity)->unk_40.at02.v = saved_y;
                    if ((hits_left << 0x10) <= 0) {
                        ((S_819AD81C_0 *)entity)->unk_30 = 4;
                        ((S_819AD81C_0 *)entity)->unk_2C.s = (s16) ((u16) ((S_819AD81C_0 *)entity)->unk_2C.s + 1);
                    }
                    goto cleanup;
                }
                goto cleanup;
            }
cleanup:
            func_80025FCC(((S_819AD81C_2 *)motion)->unk_00.at02.v, ((S_819AD81C_2 *)motion)->unk_04.at02.v, ((S_819AD81C_2 *)motion)->unk_08.at02.v, ((S_819AD81C_0 *)entity)->unk_34);
            func_80025B78(entity, motion, gfx);
            return;
        }
    } else {
        attached = (void *) ((s32) link | 0x80000000);
        if (((S_819AD81C_5 *)attached)->unk_1E & 0x8000) {
remove_object:
            (*(u16 *)((u8 *)entity + -2)) = (u16) (((S_819AD81C_0_pre *)entity)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
            return;
        }
        link = ((S_819AD81C_5 *)attached)->unk_08;
        info = ((S_819AD81C_5 *)attached)->unk_0C;
        ((S_819AD81C_2 *)motion)->unk_00.at02.v = (s16) ((S_819AD81C_6 *)link)->unk_02;
        ((S_819AD81C_2 *)motion)->unk_04.at02.v = (s16) ((S_819AD81C_6 *)link)->unk_06;
        ((S_819AD81C_2 *)motion)->unk_08.at02.v = (s16) ((S_819AD81C_6 *)link)->unk_0A;
        ((S_819AD81C_1 *)gfx)->unk_16 = (u16) ((S_819AD81C_4 *)info)->unk_16;
        ((S_819AD81C_1 *)gfx)->unk_18 = (u16) ((S_819AD81C_4 *)info)->unk_18;
        ((S_819AD81C_1 *)gfx)->unk_1A = (u16) ((S_819AD81C_4 *)info)->unk_1A;
        ((S_819AD81C_1 *)gfx)->unk_1C = (u16) ((S_819AD81C_4 *)info)->unk_1C;
        ((S_819AD81C_1 *)gfx)->unk_1E = (u16) ((S_819AD81C_4 *)info)->unk_1E;
        ((S_819AD81C_1 *)gfx)->unk_20 = (u16) ((S_819AD81C_4 *)info)->unk_20;
        ((S_819AD81C_1 *)gfx)->unk_0C.at00u.v = ((S_819AD81C_4 *)info)->unk_0C;
        want_kind = D_8002758C[((S_819AD81C_0 *)entity)->unk_48];
        node = attached + 0x20;
        if ((want_kind >= 0) && (((S_819AD81C_4 *)info)->unk_04 == want_kind)) {
            func_800649A0(attached);
            func_8002593C(entity, motion, gfx);
            zero_vec.unk0 = 0;
            zero_vec.unk2 = 0;
            zero_vec.unk4 = 0;
            func_80065450(&zero_vec, motion + 0xC, &rotated);
            func_80064A40();
            warp_params.unk2 = (u16) ((S_819AD81C_2 *)motion)->unk_0C.at00.v;
            warp_params.unk6 = (u16) ((S_819AD81C_2 *)motion)->unk_10.at00.v;
            warp_params.unkA = (u16) ((S_819AD81C_2 *)motion)->unk_14;
            warp_params.unkC = func_80064584(((S_819AD81C_3 *)node)->unk_34) * 0x10;
            warp_params.unk10 = func_800644B8(((S_819AD81C_3 *)node)->unk_34) * 0x10;
            warp_params.unk14 = 0;
            func_800B653C(&warp_params, ((S_819AD81C_3 *)node)->unk_34);
        }
        func_8002590C(gfx, ((S_819AD81C_4 *)info)->unk_04);
        func_800257D0(entity, ((S_819AD81C_1 *)gfx)->unk_00);
    }
}
