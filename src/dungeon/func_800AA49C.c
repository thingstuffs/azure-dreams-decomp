#include "common.h"

typedef struct State_80083160 {
    char pad0[0x8d0];
    s32 value;
} State_80083160;

typedef struct D_80083160_t {
    State_80083160 *state;
    char pad4[0xa8];
    u16 angle0;
    u16 angle1;
    char padb0[0x18];
    u16 angle2;
} D_80083160_t;

typedef struct Arg0_800AFBFC {
    char pad0[6];
    u8 value;
} Arg0_800AFBFC;

typedef struct Arg2_800AFBFC {
    char pad0[8];
    void *temp;
    char padc[3];
    u8 byte;
    char pade[4];
    u16 flags;
} Arg2_800AFBFC;

extern State_80083160 *D_80083160[3];
extern u8 D_80083160_bytes[] __asm__("D_80083160");
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value);
extern s32 func_800AFD04(void);
extern s32 func_800AFE54(void);
extern s32 func_800AFFB4(void *arg0, void *arg2, s16 *scratch, s32 previous, s32 side);

s32 func_800AFBFC(Arg0_800AFBFC *arg0, s32 unused, Arg2_800AFBFC *arg2) {
    register s32 previous ASM_REG("$21") = 0;   /* MATCH pin: retail delay-slot contents depend on it */
    s32 result;
    register s32 pos ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register s32 next_pos ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 pos_hold ASM_REG("$22");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 x0;
    s32 y1;
    register s16 *scratch ASM_REG("$18") = (s16 *)0x1F800000;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *view ASM_REG("$8");   /* MATCH pin: keeps a constant in a register as retail does */
    register State_80083160 *state ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *page_color;
    volatile s16 initial_pos;
    void *temp;
    s32 angle2;
    u16 flags;
    s32 byte;
    s32 next_byte;
    s32 angle0;
    register s32 angle1 ASM_REG("$23");   /* MATCH pin: keeps a statement from moving across a call/branch */

    state = D_80083160[0];
    ASM_KEEP_MEMDEP(state, page_color, D_80083160[0]);   /* MATCH pin: load-bearing for the whole function shape */
    previous = state->value;
    *(void **)((u8 *)scratch + 0x20) = (u8 *)state + 0x8b0;
    ASM_SET(view);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    view = arg2;
    ASM_KEEP_NV(view);   /* MATCH pin: retail register colouring depends on it */
    temp = ((Arg2_800AFBFC *)view)->temp;
    ASM_SET(view);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    view = D_80083160_bytes;
    *(void **)((u8 *)scratch + 0x118) = temp;
    angle0 = ((D_80083160_t *)view)->angle0;
    angle1 = ((D_80083160_t *)view)->angle1;
    view = arg2;
    byte = ((u8 *)temp)[1];
    flags = ((Arg2_800AFBFC *)view)->flags;
    ((Arg2_800AFBFC *)view)->byte = byte;
    if (flags & 8) {
        next_byte = flags & 4;
        if (next_byte == 0) {
            view = arg2;
            next_byte = byte & 0xfd;
        } else {
            next_byte = byte | 2;
        }
        ((Arg2_800AFBFC *)view)->byte = next_byte;
    }

    view = arg0;
    ASM_KEEP_NV(view);   /* MATCH pin: retail register colouring depends on it */
    pos = ((Arg0_800AFBFC *)view)->value;
    ASM_KEEP(pos);   /* MATCH pin: keeps a statement from moving across a call/branch */
    view = D_80083160_bytes;
    ASM_KEEP_NV(view);   /* MATCH pin: retail register colouring depends on it */
    angle2 = ((D_80083160_t *)view)->angle2;
    pos += 0xc00;
    pos -= (angle2 + 0x80) & 0xf00;
    pos_hold = pos;
    initial_pos = pos;
    ASM_KEEP(pos);   /* MATCH pin: keeps a statement from moving across a call/branch */
    pos = (s16)pos;
    {
    register s32 axis ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 raw_axis;
    s32 raw_y;
    register s32 call_pos ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_arg1;
    register s16 *call_arg2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_arg3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 scaled_y ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 work_x ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    x0 = func_80064584(pos) * 6 - angle0;
    scaled_y = func_800644B8(pos) * 6;
    axis = scaled_y - angle1;
    next_pos = pos_hold + 0x80;
    ASM_KEEP(next_pos);   /* MATCH pin: load-bearing for the whole function shape */
    pos = (s16)next_pos;
    scratch[0x80 / 2] = x0;
    scratch[0x70 / 2] = x0;
    scratch[0x82 / 2] = axis;
    scratch[0x72 / 2] = axis;
    raw_axis = func_80064584(pos);
    call_pos = pos;
    scaled_y = raw_axis * 6;
    axis = scaled_y - angle0;
    raw_y = func_800644B8(call_pos);
    call_arg2 = scratch;
    call_arg3 = previous;
    scaled_y = raw_y * 6;
    call_pos = (s32)arg0;
    call_arg1 = arg2;
    y1 = scaled_y - angle1;
    scratch[0x88 / 2] = axis;
    scratch[0x78 / 2] = axis;
    scratch[0x8a / 2] = y1;
    scratch[0x7a / 2] = y1;
    result = func_800AFFB4((void *)call_pos, call_arg1, call_arg2, call_arg3, 0);
    next_pos += 0x80;
    if (result != 0) {
        previous = result;
        pos_hold = next_pos;
        ASM_KEEP(pos_hold);   /* MATCH pin: keeps a statement from moving across a call/branch */
        next_pos = (s16)next_pos;
        scratch[0x80 / 2] = axis;
        scratch[0x70 / 2] = axis;
        scratch[0x82 / 2] = y1;
        scratch[0x72 / 2] = y1;
        work_x = func_80064584(next_pos) * 6 - angle0;
        x0 = work_x;
        ASM_KEEP(x0);   /* MATCH pin: retail basic-block layout depends on it */
        scaled_y = func_800644B8(next_pos) * 6 - angle1;
        axis = scaled_y;
        ASM_KEEP(axis);   /* MATCH pin: retail basic-block layout depends on it */
        scratch[0x88 / 2] = work_x;
        scratch[0x78 / 2] = work_x;
        scratch[0x8a / 2] = scaled_y;
        scratch[0x7a / 2] = scaled_y;
        result = func_800AFFB4(arg0, arg2, scratch, previous, 1);
        if (result != 0) {
            previous = result;
            ASM_TAILSLOT_PIN(previous);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800AFD04();
        }
    }
    }

    {
    register u16 raw_pos ASM_REG("$8");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 axis;
    s32 raw_axis;
    s32 raw_y;
    register s32 call_pos ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call_arg1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s16 *call_arg2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_arg3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 scaled_y;
    s32 work_x;
    raw_pos = initial_pos;
    pos = (s16)raw_pos;
    ASM_KEEP(raw_pos);   /* MATCH pin: load-bearing for the whole function shape */
    x0 = func_80064584(pos) * 6 - angle0;
    axis = func_800644B8(pos) * 6 - angle1;
    ASM_KEEP(axis);   /* MATCH pin: retail basic-block layout depends on it */
    raw_pos = initial_pos;
    next_pos = raw_pos - 0x80;
    ASM_KEEP(next_pos);   /* MATCH pin: load-bearing for the whole function shape */
    pos = (s16)next_pos;
    scratch[0x88 / 2] = x0;
    scratch[0x78 / 2] = x0;
    scratch[0x8a / 2] = axis;
    scratch[0x7a / 2] = axis;
    raw_axis = func_80064584(pos);
    call_pos = pos;
    axis = raw_axis * 6 - angle0;
    raw_y = func_800644B8(call_pos);
    call_arg2 = scratch;
    call_arg3 = previous;
    scaled_y = raw_y * 6;
    y1 = scaled_y - angle1;
    call_pos = (s32)arg0;
    call_arg1 = arg2;
    scratch[0x80 / 2] = axis;
    scratch[0x70 / 2] = axis;
    scratch[0x82 / 2] = y1;
    scratch[0x72 / 2] = y1;
    result = func_800AFFB4((void *)call_pos, call_arg1, call_arg2, call_arg3, 1);
    next_pos -= 0x80;
    if (result != 0) {
        previous = result;
        initial_pos = next_pos;
        next_pos = (s16)next_pos;
        scratch[0x88 / 2] = axis;
        scratch[0x78 / 2] = axis;
        scratch[0x8a / 2] = y1;
        scratch[0x7a / 2] = y1;
        work_x = func_80064584(next_pos) * 6 - angle0;
        x0 = work_x;
        ASM_KEEP(x0);   /* MATCH pin: retail basic-block layout depends on it */
        scaled_y = func_800644B8(next_pos) * 6 - angle1;
        axis = scaled_y;
        ASM_KEEP(axis);   /* MATCH pin: retail basic-block layout depends on it */
        call_arg2 = scratch;
        ASM_KEEP(call_arg2);   /* MATCH pin: retail register colouring depends on it */
        call_pos = (s32)arg0;
        call_arg1 = arg2;
        call_arg3 = previous;
        scratch[0x80 / 2] = work_x;
        scratch[0x70 / 2] = work_x;
        scratch[0x82 / 2] = scaled_y;
        scratch[0x72 / 2] = scaled_y;
        result = func_800AFFB4((void *)call_pos, call_arg1, call_arg2, call_arg3, 0);
        if (result != 0) {
            previous = result;
            ASM_TAILSLOT_PIN(previous);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800AFE54();
        }
    }
    }
    view = D_80083160_bytes;
    ASM_KEEP_NV(view);   /* MATCH pin: retail register colouring depends on it */
    {
        State_80083160 *final_state;
        final_state = ((D_80083160_t *)view)->state;
        final_state->value = previous;
    }
    return 0;
}
