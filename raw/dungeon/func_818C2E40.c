#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_8003FC64(s32 arg0);
extern void func_800246F4() __attribute__((noreturn));
extern void func_8004491C(void *arg0, void *arg1);
extern u8 D_800240C0[9];
extern u8 D_800241D4[9];

void *func_818C2E40(s32 arg0, void *arg1)
{
    void *node;
    void *fields;
    void *display;
    void *dst;

    node = func_8003FC64(0x212);
    {
        register void *dispatch_arg ASM_REG("$4") = node;

        if (node == 0) {
            register void *dispatch_result ASM_REG("$2") = 0;

            ASM_KEEP(dispatch_arg);
            ASM_TAILSLOT_PIN(dispatch_result);
            func_800246F4(dispatch_arg);
        }
    }

    FIELD(node, void *, 0x10) = D_800240C0;
    func_8004491C(node, D_800241D4);
    fields = (u8 *)node + 0x20;
    FIELD(node, s32, 0x20) = arg0;
    FIELD(fields, s16, 4) = 0;
    FIELD(fields, s16, 6) = 0;
    FIELD(fields, s16, 8) = 0x7DCF;
    FIELD(fields, s8, 0xA) = 0;

    display = FIELD(node, void *, 0xC);
    FIELD(display, s16, 0x1E) = 0x1000;
    FIELD(display, s16, 0x1C) = 0x1000;

    dst = FIELD(node, void *, 8);
    *(Copy24 *)dst = *(Copy24 *)arg1;
    return node;
}

/* MECHANISM: The 0x20 frame follows from node/arg0/arg1 held in s0/s1/s2 and
   the 24-byte struct assignment emits retail's grouped six-word copy.
   A guarded a0 lifetime defeats null-edge CSE; ASM_TAILSLOT_PIN sinks v0=0
   into the converted noreturn j delay slot at 2.7.2-cdk-G0. */
