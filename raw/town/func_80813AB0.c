#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
        FIELD(obj, void *, 0x10) = D_8052EDB8;
        FIELD(obj, s16, 0x38) = func_80071494() & 1;
    }

    scale = 0x1000;
    slot = (void **)(base + 8);
    do {
        obj = func_800373DC(0x136);
        *slot = obj;
        if (obj != 0) {
            u8 *part;
            u32 *packet;

            FIELD(obj, void *, 0x10) = D_8052EA14;
            func_8003BC18(obj, D_8003C558);
            part = FIELD(obj, u8 *, 0xC);
            packet = FIELD(obj, u32 *, 8);
            packet[0] = 0x05600000;
            packet[1] = (i << 22) + 0x03E00000;
            packet[2] = 0x00800000;
            packet[5] = 0xFFFC0000;
            FIELD(obj, void *, 0x20) = base;
            FIELD(obj, s16, 0x76) = i;
            FIELD(part, s16, 0x1E) = scale;
            FIELD(part, s16, 0x1C) = scale;
            func_80034A1C(part, D_8028E194, 0, packet);
            FIELD(part, u32, 0xC) = 0x00808080;
            FIELD(obj, void *, 0x6C) = D_805267AC;
            func_8023FA58(obj + 0x24, FIELD(obj, void *, 8), D_805301F0);
        }
        i--;
        slot--;
    } while (i >= 0);

    i = 1;
    y = 0x2C;
    do {
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            FIELD(obj, void *, 0x10) = D_8052FD0C;
            func_8003BC18(obj, D_8005860C);
            FIELD(obj, s16, 0x34) = 0x20;
            FIELD(obj, s16, 0x38) = 3;
            FIELD(obj, s16, 0x3A) = 0x7C80;
            FIELD(obj, s16, 0x36) = y;
            FIELD(obj, u32, 0x30) = 0x00808080;
            FIELD(obj, void *, 0x24) = ((void **)roots)[i];
            FIELD(obj, void *, 0x2C) = base;
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
            FIELD(obj, void *, 0x10) = D_8052FD60;
            func_8003BC18(obj, D_8005860C);
            FIELD(obj, s16, 0x34) = 0x50;
            FIELD(obj, s16, 0x38) = 3;
            FIELD(obj, s16, 0x3A) = 0x7C80;
            FIELD(obj, s16, 0x36) = (s32)slot;
            FIELD(obj, u32, 0x30) = 0x00808080;
            FIELD(obj, void *, 0x24) = ((void **)roots)[i + 2];
            y = (s32)(obj + 0x20);
            if (i != 0) {
                if (i != 1) {
                    ASM_KEEP(y);
                    FIELD((u8 *)y, void *, 0xC) = base;
                    return func_8052E968();
                }
                FIELD(obj, void *, 0x28) = base + 0x14;
            } else {
                FIELD(obj, void *, 0x28) = base + 0x12;
            }
            FIELD((u8 *)y, void *, 0xC) = base;
        }
        i--;
        slot = (void **)((u8 *)slot - 0xC);
    } while (i >= 0);

    obj = func_800374FC(1, D_801328C8);
    if (obj != 0) {
        register s32 final_dim ASM_REG("$3");
        u32 final_color;

        FIELD(obj, void *, 0x10) = D_8052FDF8;
        func_8003BC18(obj, D_8005888C);
        final_color = 0x00404040;
        final_dim = 0x1C;
        FIELD(obj, volatile s16, 0x2C) = final_dim;
        FIELD(obj, volatile s16, 0x2E) = final_dim;
        FIELD(obj, volatile s16, 0x32) = final_dim;
        ASM_KEEP(final_dim);
        FIELD(obj, s16, 0x30) = 0x48;
        FIELD(obj, s16, 0x34) = 2;
        FIELD(obj, u32, 0x28) = final_color;
        FIELD(obj, void *, 0x24) = base;
        FIELD(obj, volatile u16, 0x36) |= 1;
    }
    return 0;
}
/* MECHANISM: The 0x40 frame comes from two sibling RootPair stack locals and the s0-s6 held roles.
   Reusing slot as the second y carrier and y as part preserves retail's s3/s0 lifetime handoffs.
   Explicit copy pointers, the noreturn-edge store, and volatile final fields reproduce CFG scheduling.
   A held a0 color plus a guarded short-lived v1 dimension closes the final four-word role swap. */
