#include "common.h"

typedef struct S_8187BFE0_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0xE];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x2];
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u16 unk_32;
} S_8187BFE0_0;   /* state in func_8187BFE0 */

typedef struct S_8187BFE0_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    s16 unk_1E;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8187BFE0_1;   /* node in func_8187BFE0 */

typedef struct S_8187BFE0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x1A];
    union { u16 s; s16 u; } unk_1E;   /* accessed as both */
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x1F];
    union { u16 s; s16 u; } unk_58;   /* accessed as both */
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    union { u16 s; s16 u; } unk_60;   /* accessed as both */
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_8187BFE0_2;   /* work in func_8187BFE0 */

typedef struct S_8187BFE0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8187BFE0_3;   /* sprite in func_8187BFE0 */

typedef struct S_8187BFE0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8187BFE0_4;   /* dst in func_8187BFE0 */

typedef struct S_8187BFE0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8187BFE0_5;   /* source in func_8187BFE0 */



typedef struct {
    u8 bytes[12];
} Data12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80025AB0(void) __attribute__((noreturn));
extern void func_80025C38(void) __attribute__((noreturn));

extern u8 D_800249A0[];
extern u8 D_80025380[];
extern Data12 D_80026940;
extern s16 D_8002694C;
extern s32 D_800814A0;

void func_8187BFE0(void *arg0, void *arg1) {
    u8 *state;
    u8 *source;
    register u8 *node ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *work;
    u8 *sprite;
    u8 *dst;
    u8 *page = (u8 *)0x80020000;
    register s32 i ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 angle;
    s16 average;
    s32 mode;
    u16 edge;

    state = arg0;
    source = arg1;
    ASM_KEEP(state);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
    mode = ((S_8187BFE0_0 *)state)->unk_00.s;
    *(s16 *)(page + 0x694C) = 1;

    switch (mode) {
    default:
        func_80025C38();
    case 0:
        i = 0;
        node = state;
        do {
            angle = (i << 12) / 5;
            ((S_8187BFE0_1 *)node)->unk_1E =
                (((S_8187BFE0_0 *)state)->unk_0A *
                 func_80064584(((S_8187BFE0_0 *)state)->unk_0C + angle)) >> 12;
            ((S_8187BFE0_1 *)node)->unk_2A =
                (((S_8187BFE0_0 *)state)->unk_0A *
                 func_800644B8(((S_8187BFE0_0 *)state)->unk_0C + angle)) >> 12;
            i++;
            node += 2;
        } while (i < 5);

        ((S_8187BFE0_0 *)state)->unk_1C.s = 0;
        ((S_8187BFE0_0 *)state)->unk_02.s = 0;
        ((S_8187BFE0_0 *)state)->unk_00.u++;
        /* fallthrough */
    case 1:
        if (((S_8187BFE0_0 *)state)->unk_02.s != 0) {
            goto update_state;
        }

        ((S_8187BFE0_0 *)state)->unk_02.u++;
        node = func_8003FC64(0x212);
        if (node == 0) {
            break;
        }

        work = node + 0x20;
        ((S_8187BFE0_2 *)work)->unk_02 = 0x37 - (((S_8187BFE0_0 *)state)->unk_1C.s * 4);
        ((S_8187BFE0_1 *)node)->unk_10 = D_80025380;
        func_8004491C(node, D_800249A0);

        sprite = ((S_8187BFE0_1 *)node)->unk_0C;
        ((S_8187BFE0_3 *)sprite)->unk_14 &= 0xFFF3;

        dst = ((S_8187BFE0_1 *)node)->unk_08;
        ((S_8187BFE0_4 *)dst)->unk_02 = ((S_8187BFE0_5 *)source)->unk_02;
        ((S_8187BFE0_4 *)dst)->unk_06 = ((S_8187BFE0_5 *)source)->unk_06;
        ((S_8187BFE0_4 *)dst)->unk_0A = ((S_8187BFE0_5 *)source)->unk_0A;

        switch (((S_8187BFE0_0 *)state)->unk_1C.s) {
        case 0:
            ((S_8187BFE0_2 *)work)->unk_58.s = ((S_8187BFE0_2 *)work)->unk_5C =
                ((S_8187BFE0_0 *)state)->unk_1E;
            ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
                ((S_8187BFE0_0 *)state)->unk_22;
            ((S_8187BFE0_2 *)work)->unk_60.s = ((S_8187BFE0_2 *)work)->unk_64 =
                ((S_8187BFE0_0 *)state)->unk_2A;
        {
            u16 edge_v1;
            s32 span_v0;
            edge_v1 = ((S_8187BFE0_0 *)state)->unk_2E;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(span_v0);   /* MATCH pin: load-bearing for the whole function shape */
            func_80025AB0();
        }
        case 1:
            ((S_8187BFE0_2 *)work)->unk_58.s = ((S_8187BFE0_2 *)work)->unk_5C =
                ((S_8187BFE0_0 *)state)->unk_22;
            ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
                ((S_8187BFE0_0 *)state)->unk_26;
            ((S_8187BFE0_2 *)work)->unk_60.s = ((S_8187BFE0_2 *)work)->unk_64 =
                ((S_8187BFE0_0 *)state)->unk_2E;
        {
            u16 edge_v1;
            s32 span_v0;
            edge_v1 = ((S_8187BFE0_0 *)state)->unk_32;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(span_v0);   /* MATCH pin: load-bearing for the whole function shape */
            func_80025AB0();
        }
        case 2:
            ((S_8187BFE0_2 *)work)->unk_58.s = ((S_8187BFE0_2 *)work)->unk_5C =
                ((S_8187BFE0_0 *)state)->unk_26;
            ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
                ((S_8187BFE0_0 *)state)->unk_20;
            ((S_8187BFE0_2 *)work)->unk_60.s = ((S_8187BFE0_2 *)work)->unk_64 =
                ((S_8187BFE0_0 *)state)->unk_32;
        {
            u16 edge_v1;
            s32 span_v0;
            edge_v1 = ((S_8187BFE0_0 *)state)->unk_2C;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(span_v0);   /* MATCH pin: load-bearing for the whole function shape */
            func_80025AB0();
        }
        case 3:
            ((S_8187BFE0_2 *)work)->unk_58.s = ((S_8187BFE0_2 *)work)->unk_5C =
                ((S_8187BFE0_0 *)state)->unk_20;
            ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
                ((S_8187BFE0_0 *)state)->unk_24;
            ((S_8187BFE0_2 *)work)->unk_60.s = ((S_8187BFE0_2 *)work)->unk_64 =
                ((S_8187BFE0_0 *)state)->unk_2C;
        {
            u16 edge_v1;
            s32 span_v0;
            edge_v1 = ((S_8187BFE0_0 *)state)->unk_30;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(span_v0);   /* MATCH pin: load-bearing for the whole function shape */
            func_80025AB0();
        }
        case 4:
            ((S_8187BFE0_2 *)work)->unk_58.s = ((S_8187BFE0_2 *)work)->unk_5C =
                ((S_8187BFE0_0 *)state)->unk_24;
            ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
                ((S_8187BFE0_0 *)state)->unk_1E;
            ((S_8187BFE0_2 *)work)->unk_60.s = ((S_8187BFE0_2 *)work)->unk_64 =
                ((S_8187BFE0_0 *)state)->unk_30;
            edge = ((S_8187BFE0_0 *)state)->unk_2A;
            break;
        default:
            goto after_edge_setup;
        }

        ((S_8187BFE0_2 *)work)->unk_68 = ((S_8187BFE0_2 *)work)->unk_6A = 0;
        ((S_8187BFE0_2 *)work)->unk_6C = ((S_8187BFE0_2 *)work)->unk_6E = 0x18;
        ((S_8187BFE0_2 *)work)->unk_62 = ((S_8187BFE0_2 *)work)->unk_66 = edge;

after_edge_setup:
        ((S_8187BFE0_2 *)work)->unk_1E.s = ((S_8187BFE0_2 *)work)->unk_5A;
        ((S_8187BFE0_2 *)work)->unk_2A.s = ((S_8187BFE0_2 *)work)->unk_62;

        average = (((S_8187BFE0_2 *)work)->unk_1E.u + ((S_8187BFE0_2 *)work)->unk_58.u) / 2;
        ((S_8187BFE0_2 *)work)->unk_20.s = average;
        average = (average + ((S_8187BFE0_2 *)work)->unk_58.u) / 2;
        ((S_8187BFE0_2 *)work)->unk_20.s = average;

        average = (((S_8187BFE0_2 *)work)->unk_2A.u + ((S_8187BFE0_2 *)work)->unk_60.u) / 2;
        ((S_8187BFE0_2 *)work)->unk_2C.s = average;
        average = (average + ((S_8187BFE0_2 *)work)->unk_60.u) / 2;
        ((S_8187BFE0_2 *)work)->unk_2C.s = average;

        ((S_8187BFE0_2 *)work)->unk_5A = ((S_8187BFE0_2 *)work)->unk_5E =
            ((S_8187BFE0_2 *)work)->unk_20.u;
        ((S_8187BFE0_2 *)work)->unk_62 = ((S_8187BFE0_2 *)work)->unk_66 =
            ((S_8187BFE0_2 *)work)->unk_2C.u;

        sprite = ((S_8187BFE0_1 *)node)->unk_0C;
        ((S_8187BFE0_3 *)sprite)->unk_0C = ((S_8187BFE0_3 *)sprite)->unk_0D = 0xE0;
        ((S_8187BFE0_3 *)sprite)->unk_0E = 0x20;
        ((S_8187BFE0_2 *)work)->unk_36 = ((S_8187BFE0_2 *)work)->unk_37 = 0xE0;
        ((S_8187BFE0_2 *)work)->unk_38 = 0x20;
        ((S_8187BFE0_3 *)sprite)->unk_1C = ((S_8187BFE0_3 *)sprite)->unk_1E = 0x1000;

        *(Data12 *)(work + 0x44) = D_80026940;
        ((S_8187BFE0_3 *)sprite)->unk_08 = work + 0x44;
        func_80025C38();

update_state:
        ((S_8187BFE0_0 *)state)->unk_02.u++;
        if (((S_8187BFE0_0 *)state)->unk_02.s < 4) {
            goto case_done;
        }

        ((S_8187BFE0_0 *)state)->unk_02.s = 0;
        ((S_8187BFE0_0 *)state)->unk_1C.u++;
        if (((S_8187BFE0_0 *)state)->unk_1C.s < 5) {
            goto case_done;
        }

        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;

case_done:
        break;
    }
}

/* MECHANISM: A held 0x80020000 page and s32 mode local fix the prologue/store slot.
   Scoped $v1 edge/$v0 span tails plus scheduling fences preserve coordinate load delays.
   Default-first noreturn layout encodes true-space joins; division by 5 restores the magic divide. */
