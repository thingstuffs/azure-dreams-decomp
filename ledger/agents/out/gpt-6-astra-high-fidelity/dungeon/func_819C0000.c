#include "common.h"

typedef struct {
    u16 x;
    u16 y;
} LocalPoint;

typedef struct {
    LocalPoint point[3][3];
} LocalPoints;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;

typedef struct {
    s32 words[4];
} Aligned16;

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define PACKED_AT(p, o) (((PackedWord *)((u8 *)(p) + (o)))->value)

extern void func_80025648(void *, s32, s32, s32, s32);
extern void func_80025710(void *, u32, u32, s32, s32);
extern void func_80025FB0(void *, s32);
extern void func_80026060(void *, void *, s32, s32);
extern void func_8002612C(void *, s32);

extern LocalPoints D_80024004;
extern s32 D_80028630;
extern s16 D_8002992C;
extern s16 D_8002992E[5];
extern s32 D_800814A0;
extern u8 *D_800814A8;

void func_80025800(void *arg0_in, void *arg1_in, void *arg2_in)
{
    register void *arg0 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *arg1 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *arg2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    LocalPoints local;
    register u8 *src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *src_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *end;
    u8 *object;
    u8 *node;
    u8 *tile;
    u8 *world;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 fade;
    s32 thirtytwo;
    u16 flags;
    s32 state;
    s32 sum;
    u32 align;
    s16 outer;
    s16 inner;
    s16 next;
    u16 count30;
    s32 count32;
    LocalPoint *point;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    dst = (u8 *)&local;
#ifdef NON_MATCHING
    src = (u8 *)&D_80024004;
#else
    src_page = (u8 *)0x80020000;
    ASM_KEEP_NV(src_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    src = src_page + 0x4004;
#endif
    ASM_KEEP_NV(src);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    align = (u32)src & 3;
    if (align) {
        end = src + 0x20;
        do {
            w0 = PACKED_AT(src, 0);
            w1 = PACKED_AT(src, 4);
            w2 = PACKED_AT(src, 8);
            w3 = PACKED_AT(src, 0xC);
            PACKED_AT(dst, 0) = w0;
            PACKED_AT(dst, 4) = w1;
            PACKED_AT(dst, 8) = w2;
            PACKED_AT(dst, 0xC) = w3;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            src += 0x10;
            dst += 0x10;
        } while (src != end);
    } else {
        end = src + 0x20;
        do {
            w0 = S32_AT(src, 0);
            w1 = S32_AT(src, 4);
            w2 = S32_AT(src, 8);
            w3 = S32_AT(src, 0xC);
            S32_AT(dst, 0) = w0;
            S32_AT(dst, 4) = w1;
            S32_AT(dst, 8) = w2;
            S32_AT(dst, 0xC) = w3;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            src += 0x10;
            dst += 0x10;
        } while (src != end);
    }
    ASM_KEEP_NV(dst);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    PACKED_AT(dst, 0) = PACKED_AT(src, 0);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    D_8002992E[0] = 1;
    thirtytwo = 0x20;
    S16_AT(arg2, 0x10) = thirtytwo;
    U16_AT(arg2, 0x14) |= 0xC;
    object = PTR_AT(arg0, 0x20);
    world = D_800814A8;

    if (object == 0) {
        state = S16_AT(arg0, 0x2C);
        if (state == 1) {
            goto state_one;
        }
        if (state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            goto function_done;
        }

        ASM_KEEP_NV(state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (state == 2) {
            goto state_two;
        }
        goto function_done;

state_zero:
                count30 = U16_AT(arg0, 0x30);
                count32 = U16_AT(arg0, 0x32);
                ASM_KEEP_NV(count30);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(count32);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                count30--;
                count32++;
                ASM_KEEP_NV(count30);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                VU16_AT(arg0, 0x32) = count32;
                count32 = (count32 << 16) >> 16;
                VU16_AT(arg0, 0x30) = count30;
                if (count32 < 0x19) {
                    fade = count32 << 8;
                    U16_AT(arg2, 0x20) = fade;
                    U16_AT(arg2, 0x1E) = fade;
                    U16_AT(arg2, 0x1C) = fade;
                    S16_AT(arg0, 0x3A) = 0;
                    S16_AT(arg0, 0x38) = 1;
                    S16_AT(arg0, 0x34) = 1;
                    func_80026060(arg2, (u8 *)arg0 + 0x34,
                                  S16_AT(arg0, 0x3A), S16_AT(arg0, 0x38));
                    func_80025FB0(arg0, S32_AT(arg2, 0));
                    goto function_done;
                }
                U16_AT(arg0, 0x30) = 0;
                U16_AT(arg0, 0x32) = 0;
                U16_AT(arg0, 0x2C) = U16_AT(arg0, 0x2C) + 1;
                goto function_done;

state_one:
            next = U16_AT(arg0, 0x32) + 1;
            U16_AT(arg0, 0x32) = next;
            if (next & 1) {
                S16_AT(arg0, 0x3A) = state;
                S16_AT(arg0, 0x38) = 0xF;
                S16_AT(arg0, 0x34) = state;
                func_80026060(arg2, (u8 *)arg0 + 0x34,
                              S16_AT(arg0, 0x3A), S16_AT(arg0, 0x38));
                func_80025FB0(arg0, S32_AT(arg2, 0));
            }
            if (S16_AT(D_800814A8, 0x96) == 0) {
                U16_AT(arg0, 0x30) = 0;
                S32_AT(arg0, 0x50) = 0x200000;
                S32_AT(arg0, 0x5C) = 0;
                U16_AT(arg0, 0x2C) = U16_AT(arg0, 0x2C) + 1;
                goto function_done;
            }
            goto state_done;

state_two:
            {
            s32 xbase;
            register s32 ybase ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 coordx;
            s32 coordy;
            register s32 xadj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 yadj ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            S32_AT(arg1, 0x14) = S32_AT(arg1, 8);
            sum = S32_AT(arg0, 0x50) + S32_AT(arg0, 0x5C);
            S32_AT(arg0, 0x50) = sum;
            S32_AT(arg1, 8) += sum;
            coordx = S16_AT(arg1, 2);
            xadj = coordx - 0x20;
            if (xadj < 0) {
                xadj = coordx + 0x1F;
            }
            coordy = S16_AT(arg1, 6);
            yadj = coordy - 0x20;
            if (yadj < 0) {
                yadj = coordy + 0x1F;
            }
            xbase = (u32)xadj >> 6;
            ybase = (u32)yadj >> 6;

            outer = 0;
            do {
                ASM_SCHED_BARRIER(); /* MATCH: Keep the inner counter reset out of the outer branch delay slot. */
                inner = 0;
                do {
                    s32 pointoff;
                    s32 signedx;
                    register u32 callx ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    register u16 cally ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    pointoff = outer * sizeof(LocalPoint) +
                               inner * 3 * sizeof(LocalPoint);
                    point = (LocalPoint *)((u8 *)&local + pointoff);
                    ASM_KEEP_NV(point);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    callx = point->x;
                    cally = point->y;
                    callx = (xbase + callx) & 0xFFFF;
                    cally = ybase + cally;
                    func_80025710(world,
                                  callx,
                                  cally,
                                  S16_AT(arg1, 0xA),
                                  (s16)(U16_AT(arg1, 0xA) - 0x40));
                    signedx = S16_AT(point, 0);
                    func_80025648((u8 *)arg0 - 0x20,
                                  (s16)(U16_AT(arg1, 2) + (signedx << 6)),
                                  (s16)(U16_AT(arg1, 6) + ((s32)(point->y << 16) >> 10)),
                                  S16_AT(arg1, 0xA), S16_AT(arg1, 0x16));
                    inner++;
                } while (inner < 3);
                outer++;
            } while (outer < 3);

            next = U16_AT(arg0, 0x30) + 1;
            U16_AT(arg0, 0x30) = next;
            if (next >= 0x28) {
                D_8002992C = 0;
                D_80028630 = 0;
                goto object_dead;
            }
            }
state_done:
            ;
    } else {
        if (U16_AT(object, 0x1E) & 0x8000) {
object_dead:
            U16_AT(arg0, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            goto function_done;
        }

        node = PTR_AT(object, 8);
        S16_AT(arg1, 2) = U16_AT(node, 2);
        S16_AT(arg1, 6) = U16_AT(node, 6);
        S16_AT(arg1, 0xA) = U16_AT(node, 0xA);
        object = PTR_AT(arg0, 0x20);
        flags = U16_AT(arg2, 0x14);
        tile = PTR_AT(object, 0xC);
        flags |= 0xC;
        U16_AT(arg2, 0x14) = flags;
        S16_AT(arg2, 0x10) = thirtytwo;
        func_8002612C(arg2, S8_AT(tile, 4));
        func_80025FB0(arg0, S32_AT(arg2, 0));
        U16_AT(arg2, 0x1C) = U16_AT(tile, 0x1C);
        U16_AT(arg2, 0x1E) = U16_AT(tile, 0x1E);
        U16_AT(arg2, 0x20) = U16_AT(tile, 0x20);
        S32_AT(arg2, 0xC) = S32_AT(tile, 0xC);
        U16_AT(arg2, 0x16) = U16_AT(tile, 0x16);
        U16_AT(arg2, 0x18) = U16_AT(tile, 0x18);
        U16_AT(arg2, 0x1A) = U16_AT(tile, 0x1A);
    }
function_done:
    ;
}
