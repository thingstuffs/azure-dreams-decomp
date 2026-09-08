#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80045CC4_0_pre {
    s8 unk_00;
} S_80045CC4_0_pre;   /* the 0x1 bytes before poly in func_80045CC4, addressed as poly[-1] */

typedef struct S_80045CC4_0 {
    u8 pad_00[0x4];
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
    union { struct { s16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
} S_80045CC4_0;   /* poly in func_80045CC4 */

typedef struct S_80045CC4_1_pre {
    u16 unk_00;
    u16 unk_02;
} S_80045CC4_1_pre;   /* the 0x4 bytes before data in func_80045CC4, addressed as data[-1] */

typedef struct S_80045CC4_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80045CC4_2;   /* arg2 in func_80045CC4 */


#define SP_S32(offset) (*(s32 *)(spad + (offset)))
#define SP_U16(offset) (*(u16 *)(spad + (offset)))
#define SP_S16(offset) (*(s16 *)(spad + (offset)))
#define SP_S32_VOL(offset) (*(volatile s32 *)(spad + (offset)))
#define SP_S16_VOL(offset) (*(volatile s16 *)(spad + (offset)))

typedef struct {
    u8 pad00[2];
    s16 unk02;
    u8 pad04[2];
    s16 unk06;
    u8 pad08[2];
    s16 unk0A;
} S_80045CC4_Arg1;

typedef struct {
    u8 pad00[8];
    u8 *unk08;
    s32 unk0C;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
} S_80045CC4_Arg2;

extern void *D_80083160[3];

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *r, void *m);
extern void ReadRotMatrix(void *m);
extern void CompMatrix(void *m0, void *m1, void *m2);
extern void ScaleMatrix(void *m, void *v);
extern void SetTransMatrix(void *m);
extern void SetRotMatrix(void *m);
extern s32 RotAverage4(
    void *v0, void *v1, void *v2, void *v3,
    void *sxy0, void *sxy1, void *sxy2, void *sxy3,
    void *p, void *flag);

void func_80045CC4(void *arg0, s32 arg1, S_80045CC4_Arg2 *arg2, s16 arg3)
{
    void (*callback)(void *, s32, S_80045CC4_Arg2 *, u8 *);
    s32 x;
    s32 y;
    s32 *ot;
    s32 *poly;
    s32 depth;
    s32 inside0;
    s32 inside1;
    s32 inside2;
    s32 inside3;
    s32 acc;
    register u32 addr_mask ASM_REG("$22");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u16 flags;
    u16 tex;
    u8 *desc;
    u8 *data;
    u8 *spad;
    void **root;
    void *global_base;
    u8 b;
    register u8 value ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    root = D_80083160;
    global_base = root[0];
    spad = (u8 *)0x1F800000;
    SP_S32_VOL(0x20) = (s32)((u8 *)global_base + 0xB0);
    {
        s32 initial;
        initial = ((S_80045CC4_Arg1 *)arg1)->unk02;
        SP_S32_VOL(0xE4) = initial;
        initial = ((S_80045CC4_Arg1 *)arg1)->unk06;
        SP_S32_VOL(0xE8) = initial;
        initial = ((S_80045CC4_Arg1 *)arg1)->unk0A;
        SP_S16_VOL(0x8C) = 0;
        SP_S16_VOL(0x84) = 0;
        SP_S16_VOL(0x7C) = 0;
        SP_S16_VOL(0x74) = 0;
        SP_S32_VOL(0xEC) = initial;
    }
    ot = *(s32 **)((u8 *)global_base + 0x8D0);
    arg2->unk14 |= 0x8000;
    addr_mask = 0xFFFFFF;
    PushMatrix();

    SP_U16(0x108) = arg2->unk20;
    SP_U16(0x10A) = arg2->unk22;
    SP_S32(0x30) = arg2->unk1C * 2;
    SP_S32(0x34) = arg2->unk1E * 2;
    SP_S32(0x38) = 0x2000;
    SP_U16(0x100) = arg2->unk16;
    SP_U16(0x104) = arg2->unk1A;
    SP_U16(0x102) = arg2->unk18;

    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);
    ReadRotMatrix((void *)0x1F80011C);
    CompMatrix((void *)0x1F80011C, (void *)0x1F8000D0, (void *)0x1F800050);
    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);

    poly = ot + 1;
    desc = arg2->unk08;
    data = desc + 8;
    SP_U16(0x24) = arg2->unk14;

loop:
    if (!(desc[0] & 0x20)) {
        u8 x0;
        u8 x1;
        u8 y0;
        u8 y1;

        x0 = data[0];
        SP_S32(0x08) = x0;
        x1 = data[2];
        SP_S32(0x10) = x1;
        if ((x0 + x1 >= 0x100) || arg2->unk1A != 0) {
            SP_S32(0x10) = x1 - 1;
        }

        y0 = data[1];
        SP_S32(0x0C) = y0;
        y1 = data[3];
        SP_S32(0x14) = y1;
        if ((y0 + y1 >= 0x100) || arg2->unk1A != 0) {
            SP_S32(0x14) = y1 - 1;
        }

        if ((desc[0] ^ SP_U16(0x24)) & 1) {
            s32 raw = data[-6];
            u16 center = SP_U16(0x108);
            s32 extent = SP_U16(0x10);
            ASM_KEEP_DEP_NV(raw, center);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(raw, extent);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            x = -((raw << 24) >> 24) - center;
            SP_S16(0x80) = x;
            SP_S16(0x70) = x;
            x = x - extent;
        } else {
            s32 raw = data[-6];
            u16 center = SP_U16(0x108);
            s32 extent = SP_U16(0x10);
            ASM_KEEP_DEP_NV(raw, center);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(raw, extent);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            x = ((raw << 24) >> 24) - center;
            SP_S16(0x80) = x;
            SP_S16(0x70) = x;
            x = x + extent;
        }
        SP_S16(0x88) = x;
        SP_S16(0x78) = x;

        if ((desc[0] ^ SP_U16(0x24)) & 2) {
            s32 raw = data[-5];
            u16 center = SP_U16(0x10A);
            s32 extent = SP_U16(0x14);
            ASM_KEEP_DEP_NV(raw, center);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(raw, extent);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            y = -((raw << 24) >> 24) - center;
            SP_S16(0x7A) = y;
            SP_S16(0x72) = y;
            y = y - extent;
        } else {
            s32 raw = data[-5];
            u16 center = SP_U16(0x10A);
            s32 extent = SP_U16(0x14);
            ASM_KEEP_DEP_NV(raw, center);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(raw, extent);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            y = ((raw << 24) >> 24) - center;
            SP_S16(0x7A) = y;
            SP_S16(0x72) = y;
            y = y + extent;
        }
        SP_S16(0x8A) = y;
        SP_S16(0x82) = y;

        ASM_KEEP(spad);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        depth = RotAverage4(
            spad + 0x70, spad + 0x78,
            spad + 0x80, spad + 0x88,
            ot + 2, ot + 4, ot + 6, ot + 8,
            spad + 0x90, spad + 0x94);
        depth = depth - arg3 - 8;
        SP_S32(0xC0) = depth;

        if ((u32)depth < 0x1E0U) {
            inside0 = 0;
            if ((u32)((((S_80045CC4_0 *)poly)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 m = (((S_80045CC4_0 *)poly)->unk_06.u + 0x20) & 0xFFFF;
                    inside0 = m < 0x121U;
                }
            }
            inside1 = 0;
            if ((u32)((((S_80045CC4_0 *)poly)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 m = (((S_80045CC4_0 *)poly)->unk_0E + 0x20) & 0xFFFF;
                    inside1 = m < 0x121U;
                }
            }
            inside2 = 0;
            inside0 |= inside1;
            if ((u32)((((S_80045CC4_0 *)poly)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 m = (((S_80045CC4_0 *)poly)->unk_16 + 0x20) & 0xFFFF;
                    ASM_USE_NV(inside2);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    inside2 = m < 0x121U;
                }
            }
            inside3 = 0;
            acc = inside0 | inside2;
            if ((u32)((((S_80045CC4_0 *)poly)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 m = (((S_80045CC4_0 *)poly)->unk_1E.u + 0x20) & 0xFFFF;
                    ASM_USE_NV(inside3);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    inside3 = m < 0x121U;
                }
            }

            if (acc | inside3) {
                ((S_80045CC4_0_pre *)poly)[-1].unk_00 = 9;
                *(volatile u16 *)&arg2->unk14 &= 0x7FFF;

                {
                    register s32 sum_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    s32 base_x;
                    s32 old_y;

                    sum_x = SP_S32(0x10);
                    base_x = SP_S32(0x08);
                    old_y = SP_S32(0x0C);
                    sum_x += base_x;
                    base_x = old_y;
                    ASM_KEEP_NV(base_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    SP_S32(0x10) = sum_x;
                    sum_x = SP_S32(0x14);
                    SP_S32(0x0C) = base_x << 8;
                    sum_x = sum_x + old_y;
                    SP_S32_VOL(0x14) = sum_x;
                    SP_S32(0x14) = sum_x << 8;
                }

                if (SP_U16(0x24) & 0x100) {
                    ((S_80045CC4_0 *)poly)->unk_0A = arg2->unk12;
                } else {
                    ((S_80045CC4_0 *)poly)->unk_0A = arg2->unk12 + ((S_80045CC4_1_pre *)data)[-1].unk_02;
                }

                ((S_80045CC4_0 *)poly)->unk_08 = SP_U16(0x0C) + SP_U16(0x08);
                ((S_80045CC4_0 *)poly)->unk_10.s16 = SP_U16(0x0C) + SP_U16(0x10);
                {
                    u16 tex_out;
                    tex = arg2->unk10;
                    if (tex != 0) {
                        tex_out = tex + (((S_80045CC4_1_pre *)data)[-1].unk_00 & 0xFF9F);
                    } else {
                        tex_out = ((S_80045CC4_1_pre *)data)[-1].unk_00;
                    }
                    ((S_80045CC4_0 *)poly)->unk_12 = tex_out;
                }
                ((S_80045CC4_0 *)poly)->unk_18.at00.v = SP_U16(0x14) + SP_U16(0x08);
                ((S_80045CC4_0 *)poly)->unk_20.at00.v = SP_U16(0x14) + SP_U16(0x10);

                {
                    s32 raw50 = SP_U16(0x50);
                    ASM_KEEP_NV(raw50);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    if (((raw50 << 16) >> 16) >= 0x1800) {
                        b = ((S_80045CC4_0 *)poly)->unk_20.at00u.v;
                        ((S_80045CC4_0 *)poly)->unk_20.at00u.v = b + 0xFF;
                        ((S_80045CC4_0 *)poly)->unk_10.u8 = b;
                    }
                }
                {
                    s32 raw58 = SP_U16(0x58);
                    ASM_KEEP_NV(raw58);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    if (((raw58 << 16) >> 16) >= 0x1800) {
                        b = ((S_80045CC4_0 *)poly)->unk_20.at01.v;
                        ((S_80045CC4_0 *)poly)->unk_20.at01.v = b + 0xFF;
                        ((S_80045CC4_0 *)poly)->unk_18.at01.v = b;
                    }
                }
                if (((S_80045CC4_0 *)poly)->unk_04.s > ((S_80045CC4_0 *)poly)->unk_1C.s) {
                    ((S_80045CC4_0 *)poly)->unk_10.u8--;
                    ((S_80045CC4_0 *)poly)->unk_20.at00u.v--;
                }
                if (((S_80045CC4_0 *)poly)->unk_06.s > ((S_80045CC4_0 *)poly)->unk_1E.s) {
                    ((S_80045CC4_0 *)poly)->unk_18.at01.v--;
                    ((S_80045CC4_0 *)poly)->unk_20.at01.v--;
                }

                value = data[-7];
                ((S_80045CC4_2 *)arg2)->unk_0F = value;
                flags = SP_U16(0x24);
                if (flags & 8) {
                    register u32 flag_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    if (flags & 4) {
                        flag_value = value | 2;
                    } else {
                        flag_value = value & 0xFD;
                    }
                    ((S_80045CC4_2 *)arg2)->unk_0F = flag_value;
                }

                {
                    s32 old_addr = (u32)ot & addr_mask;
                    s32 *bucket;

                    poly[0] = arg2->unk0C;
                    poly += 10;
                    *ot = (*ot & 0xFF000000) |
                        (*(s32 *)(SP_S32(0xC0) * 4 + SP_S32(0x20)) & addr_mask);
                    bucket = (s32 *)(SP_S32(0xC0) * 4 + SP_S32(0x20));
                    ot += 10;
                    *bucket = (*bucket & 0xFF000000) | old_addr;
                }
            }
        }
    } else {
        callback = *(void (**)(void *, s32, S_80045CC4_Arg2 *, u8 *))data;
        if (callback != NULL) {
            callback(arg0, arg1, arg2, desc);
        }
    }

    data += 0xC;
    if ((s8)desc[0] >= 0) {
        desc += 0xC;
        goto loop;
    }

    PopMatrix();
    *(s32 **)((u8 *)root[0] + 0x8D0) = ot;
}
