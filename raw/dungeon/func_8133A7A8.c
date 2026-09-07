#include "common.h"

typedef struct {
    u8 pad_00[0x12];
    s16 state;
    u8 pad_14[4];
    s16 timer;
    u8 pad_1A[2];
    s16 phase;
} Entity;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[2];
    u16 z;
} Actor;

typedef struct {
    s16 values[8];
} __attribute__((packed)) PhaseHeights;

extern PhaseHeights D_80164A54;
extern void *D_80164A68[];
extern u8 *D_80175D50;
extern u16 D_800DCE60[4];
extern s16 D_801760E0[4];
extern s16 D_801760E8[4];
extern u8 D_80083160[];
extern s16 D_80083780[];

extern void func_8004D294(void *, void *, s32);
extern void func_8004D7A8(s32);
extern s16 func_8016F4FC(void *);

void func_801717A8(Entity *arg0) {
    PhaseHeights heights = D_80164A54;
    Actor *actor = *(Actor **)(D_80175D50 + 8);
    s16 slot;
    s16 n;
    s32 state = arg0->state;
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    u16 next_state;
    register s32 sum ASM_REG("$2");
    register s32 mode ASM_REG("$4");
    register s16 *case0_e0 ASM_REG("$17");
    register s16 *case0_e8 ASM_REG("$16");
    register s32 case0_y ASM_REG("$2");
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_exit,
        &&jt_c4, &&jt_exit, &&jt_c6, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_c20, &&jt_exit
    };

    (void)jt_keep;
    if ((u32)state < 22) {
        goto *D_80164A68[state];
    }
    goto jt_exit;

jt_c0: {
    u16 e0_0;
    u16 e0_1;
    u16 e0_2;

    mode = 1;
    ASM_KEEP(mode);
    arg0->timer = 0;
    arg0->phase = 2;
    arg0->state++;
    do {
    } while (0);
    e0_0 = D_800DCE60[0];
    *(volatile s16 *)&D_801760E0[0] = e0_0;
    ASM_SCHED_BARRIER();
    e0_1 = D_800DCE60[1];
    e0_2 = D_800DCE60[2];
    ASM_SCHED_BARRIER();
    case0_e0 = D_801760E0;
    case0_e0[1] = e0_1;
    case0_e0[2] = e0_2 - 0x600;
    D_801760E8[0] = actor->x;
    case0_e8 = D_801760E8;
    case0_y = (u16)actor->y - 0x100;
    goto jt_case0_tail;
}

jt_c1:
    arg0->timer++;
    if (arg0->timer < 0x28) {
        goto jt_exit;
    }
    call_a0 = D_801760E8;
    call_a1 = D_801760E0;
    next_state = arg0->state;
    call_a2 = 0x14;
    goto jt_call_common;

jt_c2:
    arg0->timer++;
    if (arg0->timer < 0x28) {
        goto jt_exit;
    }
    call_a0 = 0;
    call_a1 = D_800DCE60;
    next_state = arg0->state;
    call_a2 = 0xA;

jt_call_common:
    arg0->timer = 0;
    ASM_KEEP(call_a2);
    arg0->state = next_state + 1;
    func_8004D294(call_a0, call_a1, call_a2);
    goto jt_exit;

jt_c4: {
    s16 *camera;
    s16 *height_frame;
    s16 *height;
    u8 *globals;

    arg0->timer = 0;
    arg0->state++;
    slot = func_8016F4FC(actor);
    n = slot + 3;
    D_801760E0[0] = D_800DCE60[0];
    D_801760E0[1] = D_800DCE60[1];
    if (n >= 8) {
        n = slot - 5;
    }
    case0_e0 = D_801760E0;
    height_frame = heights.values - 8;
    height = &height_frame[n];
    ASM_KEEP_NV(height);
    mode = 1;
    ASM_KEEP(mode);
    case0_e0[2] = height[8] * 0x200;
    camera = D_80083780;
    sum = actor->x;
    sum += camera[1];
    ASM_KEEP_NV(sum);
    D_801760E8[0] = sum / 2;
    case0_y = actor->y;
    case0_y += camera[3];
    case0_e8 = D_801760E8;
    ASM_KEEP_NV(case0_y);
    case0_y /= 2;
jt_case0_tail:
    *(volatile s16 *)&case0_e8[1] = case0_y;
    case0_e8[2] = actor->z;
    globals = D_80083160;
    *(s32 *)(globals + 0x154) = 0;
    *(s32 *)(globals + 0xCC) = 0;
    func_8004D7A8(mode);
    func_8004D7A8(0);
    func_8004D294(case0_e8, case0_e0, 0xA);
    goto jt_exit;
}

jt_c6: {
    s16 *camera;
    s16 *height_frame;
    s16 *height;
    u8 *globals;

    arg0->timer = 0;
    arg0->state++;
    slot = func_8016F4FC(actor);
    n = slot + 2;
    D_801760E0[0] = D_800DCE60[0];
    D_801760E0[1] = D_800DCE60[1];
    if (n >= 8) {
        n = slot - 6;
    }
    height_frame = heights.values - 8;
    height = &height_frame[n];
    ASM_KEEP_NV(height);
    mode = 1;
    ASM_KEEP(mode);
    D_801760E0[2] = height[8] * 0x200;
    camera = D_80083780;
    sum = actor->x;
    sum += camera[1];
    ASM_KEEP_NV(sum);
    D_801760E8[0] = sum / 2;
    sum = actor->y;
    sum += camera[3];
    ASM_KEEP_NV(sum);
    D_801760E8[1] = sum / 2;
    D_801760E8[2] = actor->z;
    globals = D_80083160;
    *(s32 *)(globals + 0x154) = 0;
    *(s32 *)(globals + 0xCC) = 0;
    func_8004D7A8(mode);
    func_8004D7A8(0);
    func_8004D294(D_801760E8, D_801760E0, 2);
    goto jt_exit;
}

jt_c20: {
    s16 *camera;
    s16 *height_frame;
    s16 *height;
    register s16 selected_slot ASM_REG("$6");
    u8 *globals;

    if ((arg0->timer & 0xF) == 0) {
        n = func_8016F4FC(actor);
        D_801760E0[0] = D_800DCE60[0];
        D_801760E0[1] = D_800DCE60[1];
        arg0->phase++;
        slot = n + arg0->phase;
        selected_slot = slot;
        if (slot >= 8) {
            selected_slot = slot - 8;
        }
        height_frame = heights.values - 8;
        height = &height_frame[selected_slot];
        ASM_KEEP_DEP_NV(height, selected_slot);
        mode = 1;
        ASM_KEEP(mode);
        D_801760E0[2] = height[8] * 0x200;
        camera = D_80083780;
        sum = actor->x;
        sum += camera[1];
        ASM_KEEP_NV(sum);
        D_801760E8[0] = sum / 2;
        sum = actor->y;
        sum += camera[3];
        ASM_KEEP_NV(sum);
        D_801760E8[1] = sum / 2;
        D_801760E8[2] = actor->z;
        globals = D_80083160;
        *(s32 *)(globals + 0x154) = 0;
        *(s32 *)(globals + 0xCC) = 0;
        func_8004D7A8(mode);
        func_8004D7A8(0);
        func_8004D294(D_801760E8, D_801760E0, 4);
    }
}

jt_progress:
    arg0->timer++;
    if (arg0->timer >= 0x79) {
        arg0->timer = 0;
        arg0->phase = 0;
        arg0->state++;
    }

jt_exit:
    return;
}
