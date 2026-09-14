#include "common.h"

typedef struct S_808106E0_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x10];
    union { u16 u16; u32 u32; void * p32; } unk_24;   /* accessed as both */
    union { struct { void * v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_28;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { void * v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; } unk_2C;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_30;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_34;   /* accessed as both */
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
} S_808106E0_0;   /* object in func_808106E0 */

typedef struct S_808106E0_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_808106E0_1;   /* part in func_808106E0 */



typedef struct Triple {
    u32 e[3];
} Triple;

extern Triple D_80526670;
extern Triple D_80526688;
extern u8 D_801328C8[];
extern u8 D_8005860C[];
extern u8 D_8005888C[];
extern u8 D_8052B5A4[];
extern u8 D_8052BAAC[];
extern u8 D_8052BB00[];
extern u8 D_8052BB98[];

extern s32 func_800351A8(s32, s32);
extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern void func_8003F8A8(s32);
extern void func_80050BFC(s32, void *);
extern u32 func_80071494(void);

s32 func_808106E0(void)
{
    u8 *anchor = 0;
    Triple positions0 = D_80526670;
    Triple positions1 = D_80526688;
    u8 *object;
    s32 shared_part_y;
    u8 *selected;
    s32 i;
    s32 y_second;

    func_80050BFC(0x552, &D_80526688);
    func_8003F8A8(7);
    func_800351A8(0x3E, 0);

    object = func_800374FC(0x136, D_801328C8);
    i = 2;
    if (object != 0) {
        anchor = object + 0x20;
        ((S_808106E0_0 *)object)->unk_10 = D_8052B5A4;
        ((S_808106E0_0 *)object)->unk_28.at02.v = 0x1E;
        ((S_808106E0_0 *)object)->unk_24.u16 = func_80071494() & 3;
        ((S_808106E0_0 *)object)->unk_2C.at00.v |= 4;
    }

    shared_part_y = 0xD0;
    do {
        object = func_800374FC(1, D_801328C8);
        if (object != 0) {
            ((S_808106E0_0 *)object)->unk_10 = D_8052BAAC;
            func_8003BC18(object, D_8005860C);
            ((S_808106E0_0 *)object)->unk_36 = 0xB4;
            ((S_808106E0_0 *)object)->unk_38 = 3;
            ((S_808106E0_0 *)object)->unk_3A = 0x7C80;
            ((S_808106E0_0 *)object)->unk_34.s = shared_part_y;
            ((S_808106E0_0 *)object)->unk_30.at00.v = 0x00808080;
            ((S_808106E0_0 *)object)->unk_24.u32 = positions0.e[i];
            ((S_808106E0_0 *)object)->unk_2C.at00u.v = anchor;
        }
        i--;
        shared_part_y -= 0x58;
    } while (i >= 0);

    i = 2;
    y_second = 0xD8;
    do {
        object = func_800374FC(1, D_801328C8);
        if (object != 0) {
            ((S_808106E0_0 *)object)->unk_10 = D_8052BB00;
            func_8003BC18(object, D_8005860C);
            ((S_808106E0_0 *)object)->unk_36 = 0xC4;
            ((S_808106E0_0 *)object)->unk_38 = 3;
            ((S_808106E0_0 *)object)->unk_3A = 0x7C80;
            ((S_808106E0_0 *)object)->unk_34.s = y_second;
            ((S_808106E0_0 *)object)->unk_30.at00.v = 0x00808080;
            ((S_808106E0_0 *)object)->unk_24.u32 = positions1.e[i];

            shared_part_y = (s32)object + 0x20;
            switch (i) {
            case 0:
                selected = anchor + 6;
                break;
            case 2:
                selected = anchor + 10;
                break;
            case 1:
                selected = anchor + 8;
                break;
            default:
                goto store_anchor;
            }
            ((S_808106E0_0 *)object)->unk_28.at00.v = selected;
        store_anchor:
            ((S_808106E0_1 *)shared_part_y)->unk_0C = anchor;
        }
        i--;
        y_second -= 0x58;
    } while (i >= 0);

    i = 2;
    shared_part_y = 0xCC;
    do {
        object = func_800374FC(1, D_801328C8);
        i--;
        if (object != 0) {
            ((S_808106E0_0 *)object)->unk_10 = D_8052BB98;
            func_8003BC18(object, D_8005888C);
            ((S_808106E0_0 *)object)->unk_2C.at02.v = 0xB0;
            ((S_808106E0_0 *)object)->unk_30.at00u.v = 0x50;
            ((S_808106E0_0 *)object)->unk_30.at02.v = 0x20;
            ((S_808106E0_0 *)object)->unk_2C.at00p.v = shared_part_y;
            ((S_808106E0_0 *)object)->unk_34.u = 2;
            ((S_808106E0_0 *)object)->unk_28.at00u.v = 0x00404040;
            ((S_808106E0_0 *)object)->unk_24.p32 = anchor;
            ((S_808106E0_0 *)object)->unk_36 |= 1;
        }
        shared_part_y -= 0x58;
    } while (i >= 0);

    return 0;
}

/* MECHANISM: Declare the held s3 anchor before two independent 12-byte stack locals to match the 0x48 prologue.
   The three-way selection is a switch: gcc 2.7.2 emits the balanced tree (beq ==1, slti 2, beq ==0,
   beq ==2) retail shows, case 1 last so its addiu falls into the join, and the default arm's
   `goto store_anchor` becomes the two `j 0x52b4e8` + thread-filled `sw s3,12(s2)` pairs.
   The switch's default label also ends the fall-through extended block, so shared_part_y stays
   s2+0xC instead of CSE-folding to s0+0x2C - no keep needed. */
