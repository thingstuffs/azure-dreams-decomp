#include "common.h"

typedef struct S_80813AB0_0 {
    u8 pad_00[0x8];
    union { u32 * p; void * p2; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    void * unk_24;
    union { void * p; u32 i; } unk_28;   /* accessed as both */
    union { struct { void * v; } at00; struct { volatile s16 v; } at00u; struct { u8 pad[0x2]; volatile s16 v; } at02; } unk_2C;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; volatile s16 v; } at02; } unk_30;   /* overlapping accesses */
    s16 unk_34;
    union { s16 n; volatile u16 v; } unk_36;   /* accessed as both */
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x30];
    void * unk_6C;
    u8 pad_70[0x6];
    s16 unk_76;
} S_80813AB0_0;   /* obj in func_80813AB0 */

typedef struct S_80813AB0_1 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80813AB0_1;   /* part in func_80813AB0 */

typedef struct S_80813AB0_2 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80813AB0_2;   /* (u8 *)y in func_80813AB0 */



typedef struct RootPair {
    void *first;
    void *second;
} RootPair;

extern s32 func_80034A1C();
extern s32 func_800351A8();
extern u8 *func_800373DC();
extern u8 *func_800374FC();
extern s32 func_8003BC18();
extern s32 func_80071494();
extern s32 func_8023FA58();
extern s32 func_8052E968(void) __attribute__((noreturn));
extern s32 func_8052FE94();

extern u8 D_8003C558[];
extern u8 D_8005860C[];
extern u8 D_8005888C[];
extern u8 D_801328C8[];
extern u8 D_8028E194[];
extern RootPair D_80526790;
extern RootPair D_805267A0;
extern u8 D_805267A8[];
extern u8 D_805267AC[];
extern u8 D_8052EA14[];
extern u8 D_8052EDB8[];
extern u8 D_8052FD0C[];
extern u8 D_8052FD60[];
extern u8 D_8052FDF8[];
extern u8 D_805301F0[];

s32 func_80813AB0(void)
{
    RootPair roots[2];
    u8 *base;
    u8 *obj;
    void **slot;
    u8 *copy_src;
    s32 i;
    s32 scale;
    s32 y;
    u8 value;

    base = 0;
    roots[0] = D_80526790;
    roots[1] = D_805267A0;
    func_8052FE94(0x5A);
    func_800351A8(0x3B, 0);

    obj = func_800373DC(2);
    copy_src = D_805267A8;
    i = 2;
    if (obj != 0) {
        base = obj + 0x20;
        ((S_80813AB0_0 *)obj)->unk_10 = D_8052EDB8;
        ((S_80813AB0_0 *)obj)->unk_38 = func_80071494() & 1;
    }

    scale = 0x1000;
    slot = (void **)(base + 8);
    do {
        obj = func_800373DC(0x136);
        *slot = obj;
        if (obj != 0) {
            u8 *part;
            u32 *packet;

            ((S_80813AB0_0 *)obj)->unk_10 = D_8052EA14;
            func_8003BC18(obj, D_8003C558);
            part = ((S_80813AB0_0 *)obj)->unk_0C;
            packet = ((S_80813AB0_0 *)obj)->unk_08.p;
            packet[0] = 0x05600000;
            packet[1] = (i << 22) + 0x03E00000;
            packet[2] = 0x00800000;
            packet[5] = 0xFFFC0000;
            ((S_80813AB0_0 *)obj)->unk_20 = base;
            ((S_80813AB0_0 *)obj)->unk_76 = i;
            ((S_80813AB0_1 *)part)->unk_1E = scale;
            ((S_80813AB0_1 *)part)->unk_1C = scale;
            func_80034A1C(part, D_8028E194, 0, packet);
            ((S_80813AB0_1 *)part)->unk_0C = 0x00808080;
            ((S_80813AB0_0 *)obj)->unk_6C = D_805267AC;
            func_8023FA58(obj + 0x24, ((S_80813AB0_0 *)obj)->unk_08.p2, D_805301F0);
        }
        i--;
        slot--;
    } while (i >= 0);

    i = 1;
    y = 0x2C;
    do {
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            ((S_80813AB0_0 *)obj)->unk_10 = D_8052FD0C;
            func_8003BC18(obj, D_8005860C);
            ((S_80813AB0_0 *)obj)->unk_34 = 0x20;
            ((S_80813AB0_0 *)obj)->unk_38 = 3;
            ((S_80813AB0_0 *)obj)->unk_3A = 0x7C80;
            ((S_80813AB0_0 *)obj)->unk_36.n = y;
            ((S_80813AB0_0 *)obj)->unk_30.at00.v = 0x00808080;
            ((S_80813AB0_0 *)obj)->unk_24 = ((void **)roots)[i];
            ((S_80813AB0_0 *)obj)->unk_2C.at00.v = base;
        }
        i--;
        y -= 0xC;
    } while (i >= 0);

    i = 1;
    {
        u8 *copy_ptr;

        copy_ptr = copy_src + 1;
        do {
            u8 *dst_first;
            u8 *dst_second;

            value = *copy_ptr;
            copy_ptr--;
            dst_first = ((void **)roots)[2];
            dst_second = ((void **)roots)[3];
            dst_first += i;
            dst_second += i;
            i--;
            *dst_second = value;
            *dst_first = value;
        } while (i >= 0);
    }

    i = 1;
    slot = (void **)0x2C;
    do {
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            ((S_80813AB0_0 *)obj)->unk_10 = D_8052FD60;
            func_8003BC18(obj, D_8005860C);
            ((S_80813AB0_0 *)obj)->unk_34 = 0x50;
            ((S_80813AB0_0 *)obj)->unk_38 = 3;
            ((S_80813AB0_0 *)obj)->unk_3A = 0x7C80;
            ((S_80813AB0_0 *)obj)->unk_36.n = (s32)slot;
            ((S_80813AB0_0 *)obj)->unk_30.at00.v = 0x00808080;
            ((S_80813AB0_0 *)obj)->unk_24 = ((void **)roots)[i + 2];
            y = (s32)(obj + 0x20);
            if (i != 0) {
                if (i != 1) {
                    ASM_KEEP(y);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    ((S_80813AB0_2 *)((u8 *)y))->unk_0C = base;
                    return func_8052E968();
                }
                ((S_80813AB0_0 *)obj)->unk_28.p = base + 0x14;
            } else {
                ((S_80813AB0_0 *)obj)->unk_28.p = base + 0x12;
            }
            ((S_80813AB0_2 *)((u8 *)y))->unk_0C = base;
        }
        i--;
        slot = (void **)((u8 *)slot - 0xC);
    } while (i >= 0);

    obj = func_800374FC(1, D_801328C8);
    if (obj != 0) {
        register s32 final_dim ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        u32 final_color;

        ((S_80813AB0_0 *)obj)->unk_10 = D_8052FDF8;
        func_8003BC18(obj, D_8005888C);
        final_color = 0x00404040;
        final_dim = 0x1C;
        ((S_80813AB0_0 *)obj)->unk_2C.at00u.v = final_dim;
        ((S_80813AB0_0 *)obj)->unk_2C.at02.v = final_dim;
        ((S_80813AB0_0 *)obj)->unk_30.at02.v = final_dim;
        ((S_80813AB0_0 *)obj)->unk_30.at00u.v = 0x48;
        ((S_80813AB0_0 *)obj)->unk_34 = 2;
        ((S_80813AB0_0 *)obj)->unk_28.i = final_color;
        ((S_80813AB0_0 *)obj)->unk_24 = base;
        ((S_80813AB0_0 *)obj)->unk_36.v |= 1;
    }
    return 0;
}
/* MECHANISM: The 0x40 frame comes from two sibling RootPair stack locals and the s0-s6 held roles.
   Reusing slot as the second y carrier and y as part preserves retail's s3/s0 lifetime handoffs.
   Explicit copy pointers, the noreturn-edge store, and volatile final fields reproduce CFG scheduling.
   A held a0 color plus a guarded short-lived v1 dimension closes the final four-word role swap. */
