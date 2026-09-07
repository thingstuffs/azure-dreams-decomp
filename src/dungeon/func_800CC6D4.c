#include "common.h"


typedef void (*EntityCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern EntityCallback D_800E21C0[];

extern void func_800478B8(void *arg0);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern void func_800D1F60();
extern void func_800D1FEC();
extern void func_800D2004();
extern void func_800D2084();
extern void func_800D20B8();


typedef struct S_800D1E34_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D1E34_0;   /* ent in func_800D1E34 */

typedef struct S_800D1E34_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D1E34_1;   /* pos in func_800D1E34 */

typedef struct S_800D1E34_2 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    union { u16 n; volatile u16 v; } unk_98;   /* accessed as both */
    u8 pad_9A[0x3];
    union { u8 n; s8 n2; volatile u8 v; } unk_9D;   /* accessed as both */
} S_800D1E34_2;   /* obj in func_800D1E34 */

void func_800D1E34(void *arg0, void *arg1, void *arg2)
{
    void *obj = arg0;
    register void *pos ASM_REG("$18") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    void *ent = arg2;
    register void *work ASM_REG("$16") = obj;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    EntityCallback callback;
    s16 floor;
    u16 flags;
    u16 globalFlags = D_80083462;

    if (globalFlags & 0x2000) {
        (*(u8 *)((u8 *)work + (0x71))) &= 0x7F;
        func_800D20B8();
        return;
    }

    ASM_KEEP(obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(pos);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(ent);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(work);   /* MATCH pin: retail basic-block layout depends on it */

    callback = (*(EntityCallback *)((u8 *)work + (0x8C)));
    if (callback != 0) {
        callback(work, pos, ent, work);
    }
    D_800E21C0[(*(u8 *)((u8 *)work + (0x9A)))](work, pos, ent, work);

    flags = ((S_800D1E34_0 *)ent)->unk_14;
    if (!(flags & 0x8000)) {
        if (!(flags & 0x40)) {
            func_800478B8(ent);
        }
    }

    ((S_800D1E34_1 *)pos)->unk_00.at00.v += ((S_800D1E34_1 *)pos)->unk_0C;
    ((S_800D1E34_1 *)pos)->unk_04.at00.v += ((S_800D1E34_1 *)pos)->unk_10;

    if (((S_800D1E34_2 *)obj)->unk_98.n & 8) {
        ((S_800D1E34_2 *)obj)->unk_9D.n = 0;
        func_800D1F60();
        return;
    }

    ((S_800D1E34_1 *)pos)->unk_14 += ((S_800D1E34_2 *)obj)->unk_9D.n2 * 0x14000;
    ((S_800D1E34_2 *)obj)->unk_9D.v++;
    ((S_800D1E34_2 *)obj)->unk_90.at00.v += ((S_800D1E34_1 *)pos)->unk_14;

    if (!(((S_800D1E34_2 *)obj)->unk_98.v & 4)) {
        floor = func_800BCB04(((S_800D1E34_1 *)pos)->unk_00.at02.v, ((S_800D1E34_1 *)pos)->unk_04.at02.v,
                              (s16)((*(u16 *)((u8 *)work + (0x88))) - 0x20));
        if (floor < 0x200) {
            if (((S_800D1E34_2 *)obj)->unk_90.at02.v + (*(s16 *)((u8 *)work + (0x88))) < floor) {
                (void)((S_800D1E34_2 *)obj)->unk_98.v;
                func_800D2004();
                return;
            }
            if (floor >= (*(s16 *)((u8 *)work + (0x88)))) {
                ((S_800D1E34_2 *)obj)->unk_90.at00.v = 0;
                func_800D1FEC();
                return;
            }

            ((S_800D1E34_2 *)obj)->unk_90.at02.v = floor - (*(u16 *)((u8 *)work + (0x88)));
            ((S_800D1E34_1 *)pos)->unk_14 = 0;
            (*(u32 *)((u8 *)work + (0x1C))) |= 0x08000000;
            ((S_800D1E34_2 *)obj)->unk_9D.n = 0;

            if ((*(u32 *)((u8 *)work + (0x1C))) & 0x40000000) {
                (*(u32 *)((u8 *)work + (0x1C))) &= ~0x40000000;
                floor = func_800BCB04(
                    (((S_800D1E34_0 *)ent)->unk_24 << 6) | 0x20,
                    (((S_800D1E34_0 *)ent)->unk_25 << 6) | 0x20,
                    (s16)((*(u16 *)((u8 *)work + (0x88))) - 0x20));
                ((S_800D1E34_2 *)obj)->unk_90.at02u.v += (*(u16 *)((u8 *)work + (0x88))) - floor;
                (*(u16 *)((u8 *)work + (0x88))) = floor;
                func_800D2084();
                return;
            }
            goto finish;
        }
    }

    (*(u32 *)((u8 *)work + (0x1C))) &= ~0x08000000;

finish:
    ((S_800D1E34_1 *)pos)->unk_0A = (*(u16 *)((u8 *)work + (0x88))) + ((S_800D1E34_2 *)obj)->unk_90.at02u.v;
    ((S_800D1E34_0 *)ent)->unk_14 |= 0x40;
    (*(u32 *)((u8 *)work + (0x1C))) |= 0x200;
}
