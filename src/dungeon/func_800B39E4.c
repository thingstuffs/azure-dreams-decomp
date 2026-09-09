#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define VU8(p, o) (*(volatile u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define VU16(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define P32(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0x8D0];
    u8 *record;
} Root;

typedef struct {
    u8 pad70[0x70];
    u16 h70;
    u16 h72;
    u16 h74;
    u16 h76;
    u16 h78;
    u16 h7A;
    u16 h7C;
    u16 h7E;
    u16 h80;
    u16 h82;
    u16 h84;
    u16 h86;
    u16 h88;
    u16 h8A;
    u8 pad8C[8];
    s32 w94;
    s32 w98;
    s32 wA0;
    s32 wA8;
    s32 wB0;
} Scratch;

typedef struct {
    u8 bytes[12];
} Record;

extern Root *D_80083160[];

extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064B90(void *, void *, s32, s32);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(s32, void *);
extern void func_80067EF4();

void func_800B9144(void *arg0, void *arg1, s32 arg2, s16 arg3)
{
    s32 (*callback)(void *, s32, void *, void *, void *);
    Scratch *scratch = (Scratch *)0x1F800000;
    u8 *s3 = P32(arg1, -0x14);
    s32 s6 = S32(arg1, -0x18);
    register s16 saved_arg3 ASM_REG("$23") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Root *root = D_80083160[0];
    Record *s2 = P32(s3, 8);
    Root **global_slot = D_80083160;
    u8 *scratch_base;
    u8 *s1;
    s32 flags;

    VU16(scratch, 0x8C) = 0;
    VU16(scratch, 0x84) = 0;
    VU16(scratch, 0x7C) = 0;
    VU16(scratch, 0x74) = 0;
    s1 = root->record;
    flags = arg3 << 16;
    S32(scratch, 0x20) = arg2;
    S32(scratch, 0xC0) = 0;
    if (flags != 0) {
        func_80067EF4(s1, 0, 0, flags);
        func_8006658C(S32(scratch, 0x20), s1);
        s1 += 12;
    }
    func_800649A0();

    {
        u16 *input = arg0;
        register s32 x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 y ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 temp0;
        register s32 temp1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        x = U16(input, 0);
        S16(scratch, 0x00) = x;
        y = U16(input, 2);
        x = (s16)x;
        S16(scratch, 0x02) = y;
        scratch_base = (u8 *)0x1F800000;
        temp0 = U16(s3, 0x1C);
        y = (s16)y;
        S32(scratch, 0x30) = temp0;
        temp1 = U16(s3, 0x1E);
        temp0 = 0x1000;
        S32(scratch, 0x38) = temp0;
        S32(scratch, 0x34) = temp1;
        temp0 = U16(s3, 0x20);
        U16(scratch, 0x108) = temp0;
        temp0 = (s16)temp0;
        temp1 = U16(s3, 0x22);
        x += temp0;
        S32(scratch, 0x40) = x;
        S32(scratch, 0x48) = 0;
        U16(scratch, 0x10A) = temp1;
        temp1 = (s16)temp1;
        y += temp1;
        S32(scratch, 0x44) = y;
        func_80064B90((u8 *)scratch + 0x50, (u8 *)scratch + 0x40,
                      x, y);
        func_80065820(s3 + 0x16, scratch_base + 0x50);
        func_80064BC0(scratch_base + 0x50, (u8 *)scratch + 0x30);
        func_80064CF0(scratch_base + 0x50);
        func_80064D80(scratch_base + 0x50);
        U16(scratch, 0x24) = U16(s3, 0x14);
        scratch_base += 0x94;
    }

loop:
    if (!(U8(s2, 0) & 0x20)) {
        S32(scratch, 8) = U8(s2, 8);
        S32(scratch, 0xC) = U8(s2, 9);
        S32(scratch, 0x10) = U8(s2, 0xA);
        S32(scratch, 0x14) = U8(s2, 0xB);

        {
            register s32 v ASM_REG("$2"); /* MATCH: Both coordinate arms merge in retail v0. */
            if (((U8(s2, 0) ^ U16(scratch, 0x24)) & 1) != 0) {
                register s32 width ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                s32 addend;

                v = VU8(s2, 2);
                width = U16(scratch, 0x108);
                addend = U16(scratch, 0x10);
                v = (s8)v;
                v = -v - width;
                U16(scratch, 0x80) = v;
                U16(scratch, 0x70) = v;
                v -= addend;
            } else {
                s32 width;
                s32 addend;

                v = VU8(s2, 2);
                width = U16(scratch, 0x108);
                addend = U16(scratch, 0x10);
                v = (s8)v;
                v -= width;
                U16(scratch, 0x80) = v;
                U16(scratch, 0x70) = v;
                v += addend;
            }
            U16(scratch, 0x88) = v;
            U16(scratch, 0x78) = v;
        }

        {
            register s32 v ASM_REG("$2"); /* MATCH: Both coordinate arms merge in retail v0. */
            if (((U8(s2, 0) ^ U16(scratch, 0x24)) & 2) != 0) {
                register s32 height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                s32 addend;

                v = VU8(s2, 3);
                height = U16(scratch, 0x10A);
                addend = U16(scratch, 0x14);
                v = (s8)v;
                v = -v - height;
                U16(scratch, 0x7A) = v;
                U16(scratch, 0x72) = v;
                v -= addend;
            } else {
                s32 height;
                s32 addend;

                v = VU8(s2, 3);
                height = U16(scratch, 0x10A);
                addend = U16(scratch, 0x14);
                v = (s8)v;
                v -= height;
                U16(scratch, 0x7A) = v;
                U16(scratch, 0x72) = v;
                v += addend;
            }
            U16(scratch, 0x8A) = v;
            U16(scratch, 0x82) = v;
        }

        ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        func_80065320((u16 *)scratch + 0x38, (u16 *)scratch + 0x4C, scratch_base);
        func_80065320((u16 *)scratch + 0x3C, (u16 *)scratch + 0x50, scratch_base);
        func_80065320((u16 *)scratch + 0x40, (u16 *)scratch + 0x54, scratch_base);
        func_80065320((u16 *)scratch + 0x44, (u16 *)scratch + 0x58, scratch_base);

        {
            s32 out0;
            register s32 out1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            out0 = S32(scratch, 0x98);
            S32(s1, 8) = out0;
            out0 = S32(scratch, 0xA0);
            S32(s1, 0x10) = out0;
            out0 = S32(scratch, 0xA8);
            S32(s1, 0x18) = out0;
            out1 = S32(scratch, 0xB0);
            out0 = 9;
            U8(s1, 3) = out0;
            S32(s1, 0x20) = out1;
        }

        {
            s32 v0;
            register s32 v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            v0 = S32(scratch, 0x10);
            v1 = S32(scratch, 8);
            v0 -= 1;
            v1 = v0 + v1;
            S32(scratch, 0x10) = v1;
            if (v1 & 0x100) {
                v0 = v1 - 1;
                S32(scratch, 0x10) = v0;
            }
        }
        {
            s32 v0;
            register s32 v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            v0 = S32(scratch, 0x14);
            v1 = S32(scratch, 0xC);
            v0 -= 1;
            v1 = v0 + v1;
            S32(scratch, 0x14) = v1;
            if (v1 & 0x100) {
                v0 = v1 - 1;
                S32(scratch, 0x14) = v0;
            }
        }

        S32(scratch, 0x14) <<= 8;
        S32(scratch, 0xC) <<= 8;

        {
            register s32 tail_value ASM_REG("$2"); /* MATCH: Retain retail operand order in the merged addition. */
            s32 count = U16(s3, 0x12);
            if (count != 0) {
                if (U16(scratch, 0x24) & 0x100) {
                    U16(s1, 0x0E) = count;
                } else {
                    tail_value = U16(s2, 6);
                    tail_value = count + tail_value;
                    U16(s1, 0x0E) = tail_value;
                }
            } else {
                tail_value = U16(s2, 6);
                U16(s1, 0x0E) = tail_value;
            }
        }

        S16(s1, 0x0C) = U16(scratch, 0xC) + U16(scratch, 8);
        S16(s1, 0x14) = U16(scratch, 0xC) + U16(scratch, 0x10);

        {
            register s32 tail_value ASM_REG("$2"); /* MATCH: Retain retail operand order in the merged addition. */
            s32 count = U16(s3, 0x10);
            if (count != 0) {
                tail_value = U16(s2, 4);
                tail_value &= 0xFF9F;
                tail_value = count + tail_value;
            } else {
                tail_value = U16(s2, 4);
            }
            U16(s1, 0x16) = tail_value;
        }
        {
            register s32 v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 v1;
            register s32 a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            v0 = U16(scratch, 0x14);
            v1 = U16(scratch, 8);
            a1 = S16(s1, 8);
            v0 |= v1;
            S16(s1, 0x1C) = v0;
            v1 = U16(scratch, 0x14);
            a0 = U16(scratch, 0x10);
            v0 = S16(s1, 0x20);
            v1 |= a0;
            v0 = v0 < a1;
            S16(s1, 0x24) = v1;
            if (v0 != 0) {
                v1 = U8(s1, 0x24);
                v0 = v1 + 0xFF;
                U8(s1, 0x24) = v0;
                U8(s1, 0x14) = v1;
            }
        }
        {
            s32 v0;
            s32 v1;
            v1 = S16(s1, 0x0A);
            v0 = S16(s1, 0x22);
            if (v0 < v1) {
                v1 = U8(s1, 0x25);
                v0 = v1 + 0xFF;
                U8(s1, 0x25) = v0;
                U8(s1, 0x1D) = v1;
            }
        }

        {
            register s32 v ASM_REG("$4") = U8(s2, 1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 result;
            s32 bits;
            U8(s3, 0x0F) = v;
            bits = U16(scratch, 0x24);
            result = bits & 8;
            if (result != 0) {
                result = bits & 4;
                if (result == 0) {
                    result = v & 0xFD;
                } else {
                    result = v | 2;
                }
                U8(s3, 0x0F) = result;
            }
        }

        {
            u8 *call_record;
            s32 stored;
            stored = S32(s3, 0x0C);
            call_record = s1;
            S32(s1, 4) = stored;
            func_8006658C(S32(scratch, 0x20), call_record);
            s1 += 40;
            ASM_KEEP(s1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        }
    } else {
        callback = P32(s2, 8);
        if (callback != 0) {
            register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            result = callback(arg1, s6, s3, s2, s1);
            if (result > 0) {
                u32 tag = 0x80000000;
                s2 = (Record *)(result | tag);
            } else {
                s1 = (u8 *)result;
            }
        }
    }

    if ((s8)U8(s2++, 0) >= 0) {
        goto loop;
    }
    {
        register s32 tail_flags ASM_REG("$2") = saved_arg3 << 16;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (tail_flags != 0) {
            func_80067EF4(s1, 0, 1);
            func_8006658C(S32(scratch, 0x20), s1);
            s1 += 12;
        }
    }
    func_80064A40();
    (*global_slot)->record = s1;
    return;
}
