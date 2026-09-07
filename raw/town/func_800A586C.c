#include "common.h"

typedef struct {
    u16 h[4];
} Coord8;

typedef struct {
    u32 w0;
    u32 w1;
} __attribute__((packed)) Packed8;

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_800A130C();
extern s32 func_800A1330();
extern s32 func_800A2E30(Coord8, Coord8, Packed8, Packed8, s32);

void func_800A2FCC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Coord8 base;
    Coord8 sample_a;
    Coord8 sample_b;
    Coord8 work_a;
    Coord8 work_b;
    register Coord8 *initial_a ASM_REG("$17");
    Coord8 *initial_b;
    register Coord8 *loop_a;
    register Coord8 *loop_b ASM_REG("$17");
    register s32 final_arg ASM_REG("$23") = arg3;
    register s32 angle;
    register s32 count ASM_REG("$19");
    register s32 product;
    register s32 shifted ASM_REG("$3");

    func_800A130C(&base, arg0);
    initial_a = &work_a;
    func_800A1330(initial_a, &base);
    initial_b = &work_b;
    func_800A1330(initial_b, &base);
    product = func_800644B8(0) * arg1;
    shifted = product >> 16;
    work_a.h[0] += shifted;
    product = func_80064584(0) * arg1;
    shifted = product >> 16;
    work_a.h[1] += shifted;
    product = func_800644B8(0) * arg2;
    shifted = product >> 16;
    work_b.h[0] += shifted;
    product = func_80064584(0) * arg2;
    shifted = product >> 16;
    work_b.h[1] += shifted;
    angle = 0;
    count = 0;
    loop_a = initial_a;
    loop_b = initial_b;

    {
        register s32 upper_mask ASM_REG("$16") = 0xFFFF0000;

        ASM_USE(upper_mask);

        do {
            func_800A1330(&sample_a, loop_a);
            func_800A1330(&sample_b, loop_b);
            angle += 0x100;
            func_800A1330(loop_a, &base);
            func_800A1330(loop_b, &base);
            product = func_800644B8(angle) * arg1;
            shifted = product >> 16;
            work_a.h[0] += shifted;
            product = func_80064584(angle) * arg1;
            shifted = product >> 16;
            work_a.h[1] += shifted;
            product = func_800644B8(angle) * arg2;
            shifted = product >> 16;
            work_b.h[0] += shifted;
            count++;
            product = func_80064584(angle) * arg2;
            shifted = product >> 16;
            work_b.h[1] += shifted;
            func_800A2E30(sample_a, sample_b,
                          *(Packed8 *)&work_a,
                          *(Packed8 *)&work_b,
                          (s16)final_arg);
        } while (count < 0x10);
    }
}
