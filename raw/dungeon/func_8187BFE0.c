#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register u8 *state ASM_REG("$19");
    register u8 *source ASM_REG("$20");
    register u8 *node ASM_REG("$17");
    u8 *work;
    u8 *sprite;
    u8 *dst;
    u8 *page = (u8 *)0x80020000;
    register s32 i ASM_REG("$18");
    s32 angle;
    s16 average;
    s32 mode;
    u16 edge;

    state = arg0;
    source = arg1;
    ASM_KEEP(state);
    ASM_KEEP(source);
    mode = FIELD(state, s16, 0);
    *(s16 *)(page + 0x694C) = 1;

    switch (mode) {
    default:
        func_80025C38();
    case 0:
        i = 0;
        node = state;
        ASM_KEEP(i);
        ASM_KEEP(node);
        do {
            angle = (i << 12) / 5;
            FIELD(node, s16, 0x1E) =
                (FIELD(state, s16, 0xA) *
                 func_80064584(FIELD(state, s16, 0xC) + angle)) >> 12;
            FIELD(node, s16, 0x2A) =
                (FIELD(state, s16, 0xA) *
                 func_800644B8(FIELD(state, s16, 0xC) + angle)) >> 12;
            i++;
            node += 2;
        } while (i < 5);

        FIELD(state, s16, 0x1C) = 0;
        FIELD(state, s16, 2) = 0;
        FIELD(state, u16, 0)++;
        /* fallthrough */
    case 1:
        if (FIELD(state, s16, 2) != 0) {
            goto update_state;
        }

        FIELD(state, u16, 2)++;
        node = func_8003FC64(0x212);
        ASM_KEEP(node);
        if (node == 0) {
            break;
        }

        work = node + 0x20;
        FIELD(work, s16, 2) = 0x37 - (FIELD(state, s16, 0x1C) * 4);
        FIELD(node, void *, 0x10) = D_80025380;
        func_8004491C(node, D_800249A0);

        sprite = FIELD(node, u8 *, 0xC);
        FIELD(sprite, u16, 0x14) &= 0xFFF3;

        dst = FIELD(node, u8 *, 8);
        FIELD(dst, u16, 2) = FIELD(source, u16, 2);
        FIELD(dst, u16, 6) = FIELD(source, u16, 6);
        FIELD(dst, u16, 0xA) = FIELD(source, u16, 0xA);

        switch (FIELD(state, s16, 0x1C)) {
        case 0:
            FIELD(work, u16, 0x58) = FIELD(work, u16, 0x5C) =
                FIELD(state, u16, 0x1E);
            FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
                FIELD(state, u16, 0x22);
            FIELD(work, u16, 0x60) = FIELD(work, u16, 0x64) =
                FIELD(state, u16, 0x2A);
        {
            register u16 edge_v1 ASM_REG("$3");
            register s32 span_v0 ASM_REG("$2");
            edge_v1 = FIELD(state, u16, 0x2E);
            ASM_SCHED_BARRIER();
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);
            ASM_TAILSLOT_PIN(span_v0);
            func_80025AB0();
        }
        case 1:
            FIELD(work, u16, 0x58) = FIELD(work, u16, 0x5C) =
                FIELD(state, u16, 0x22);
            FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
                FIELD(state, u16, 0x26);
            FIELD(work, u16, 0x60) = FIELD(work, u16, 0x64) =
                FIELD(state, u16, 0x2E);
        {
            register u16 edge_v1 ASM_REG("$3");
            register s32 span_v0 ASM_REG("$2");
            edge_v1 = FIELD(state, u16, 0x32);
            ASM_SCHED_BARRIER();
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);
            ASM_TAILSLOT_PIN(span_v0);
            func_80025AB0();
        }
        case 2:
            FIELD(work, u16, 0x58) = FIELD(work, u16, 0x5C) =
                FIELD(state, u16, 0x26);
            FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
                FIELD(state, u16, 0x20);
            FIELD(work, u16, 0x60) = FIELD(work, u16, 0x64) =
                FIELD(state, u16, 0x32);
        {
            register u16 edge_v1 ASM_REG("$3");
            register s32 span_v0 ASM_REG("$2");
            edge_v1 = FIELD(state, u16, 0x2C);
            ASM_SCHED_BARRIER();
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);
            ASM_TAILSLOT_PIN(span_v0);
            func_80025AB0();
        }
        case 3:
            FIELD(work, u16, 0x58) = FIELD(work, u16, 0x5C) =
                FIELD(state, u16, 0x20);
            FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
                FIELD(state, u16, 0x24);
            FIELD(work, u16, 0x60) = FIELD(work, u16, 0x64) =
                FIELD(state, u16, 0x2C);
        {
            register u16 edge_v1 ASM_REG("$3");
            register s32 span_v0 ASM_REG("$2");
            edge_v1 = FIELD(state, u16, 0x30);
            ASM_SCHED_BARRIER();
            span_v0 = 0x18;
            ASM_KEEP(edge_v1);
            ASM_TAILSLOT_PIN(span_v0);
            func_80025AB0();
        }
        case 4:
            FIELD(work, u16, 0x58) = FIELD(work, u16, 0x5C) =
                FIELD(state, u16, 0x24);
            FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
                FIELD(state, u16, 0x1E);
            FIELD(work, u16, 0x60) = FIELD(work, u16, 0x64) =
                FIELD(state, u16, 0x30);
            edge = FIELD(state, u16, 0x2A);
            break;
        default:
            goto after_edge_setup;
        }

        FIELD(work, u16, 0x68) = FIELD(work, u16, 0x6A) = 0;
        FIELD(work, u16, 0x6C) = FIELD(work, u16, 0x6E) = 0x18;
        FIELD(work, u16, 0x62) = FIELD(work, u16, 0x66) = edge;

after_edge_setup:
        FIELD(work, u16, 0x1E) = FIELD(work, u16, 0x5A);
        FIELD(work, u16, 0x2A) = FIELD(work, u16, 0x62);

        average = (FIELD(work, s16, 0x1E) + FIELD(work, s16, 0x58)) / 2;
        FIELD(work, s16, 0x20) = average;
        average = (average + FIELD(work, s16, 0x58)) / 2;
        FIELD(work, s16, 0x20) = average;

        average = (FIELD(work, s16, 0x2A) + FIELD(work, s16, 0x60)) / 2;
        FIELD(work, s16, 0x2C) = average;
        average = (average + FIELD(work, s16, 0x60)) / 2;
        FIELD(work, s16, 0x2C) = average;

        FIELD(work, u16, 0x5A) = FIELD(work, u16, 0x5E) =
            FIELD(work, u16, 0x20);
        FIELD(work, u16, 0x62) = FIELD(work, u16, 0x66) =
            FIELD(work, u16, 0x2C);

        sprite = FIELD(node, u8 *, 0xC);
        FIELD(sprite, u8, 0xC) = FIELD(sprite, u8, 0xD) = 0xE0;
        FIELD(sprite, u8, 0xE) = 0x20;
        FIELD(work, u8, 0x36) = FIELD(work, u8, 0x37) = 0xE0;
        FIELD(work, u8, 0x38) = 0x20;
        FIELD(sprite, u16, 0x1C) = FIELD(sprite, u16, 0x1E) = 0x1000;

        *(Data12 *)(work + 0x44) = D_80026940;
        FIELD(sprite, void *, 8) = work + 0x44;
        func_80025C38();

update_state:
        FIELD(state, u16, 2)++;
        if (FIELD(state, s16, 2) < 4) {
            goto case_done;
        }

        FIELD(state, s16, 2) = 0;
        FIELD(state, u16, 0x1C)++;
        if (FIELD(state, s16, 0x1C) < 5) {
            goto case_done;
        }

        FIELD(state, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;

case_done:
        break;
    }
}

/* MECHANISM: A held 0x80020000 page and s32 mode local fix the prologue/store slot.
   Scoped $v1 edge/$v0 span tails plus scheduling fences preserve coordinate load delays.
   Default-first noreturn layout encodes true-space joins; division by 5 restores the magic divide. */
