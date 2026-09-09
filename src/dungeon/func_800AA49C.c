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
extern s32 func_800AFFB4(void *arg0, void *arg2, s16 *scratch, s32 previous, s32 side);

/* Processes circular segments in both directions and saves the last successful result. */
s32 func_800AFBFC(Arg0_800AFBFC *shape, s32 unused, Arg2_800AFBFC *segment) {
    s32 last_result = 0;
    s32 result;
    register s32 angle ASM_REG("$16");
    register s32 next_angle ASM_REG("$17");
    register s32 angle_step ASM_REG("$22");
    s32 start_x;
    s32 end_y;
    register s16 *scratch ASM_REG("$18") = (s16 *)0x1F800000;
    register void *view ASM_REG("$8");
    register State_80083160 *state ASM_REG("$2");
    void *state_dep;
    volatile s16 start_angle;
    void *segment_data;
    s32 rotation;
    u16 flags;
    s32 segment_byte;
    s32 updated_byte;
    s32 offset_x;
    s32 offset_y;

    state = D_80083160[0];
    ASM_KEEP_MEMDEP(state, state_dep, D_80083160[0]);
    last_result = state->value;
    *(void **)((u8 *)scratch + 0x20) = (u8 *)state + 0x8b0;
    ASM_SET(view);
    view = segment;
    ASM_KEEP_NV(view);
    segment_data = ((Arg2_800AFBFC *)view)->temp;
    ASM_SET(view);
    view = D_80083160_bytes;
    *(void **)((u8 *)scratch + 0x118) = segment_data;
    offset_x = ((D_80083160_t *)view)->angle0;
    offset_y = ((D_80083160_t *)view)->angle1;
    view = segment;
    segment_byte = ((u8 *)segment_data)[1];
    flags = ((Arg2_800AFBFC *)view)->flags;
    ((Arg2_800AFBFC *)view)->byte = segment_byte;
    if (flags & 8) {
        updated_byte = flags & 4;
        if (updated_byte == 0) {
            view = segment;
            updated_byte = segment_byte & 0xfd;
        } else {
            updated_byte = segment_byte | 2;
        }
        ((Arg2_800AFBFC *)view)->byte = updated_byte;
    }

    view = shape;
    ASM_KEEP_NV(view);
    angle = ((Arg0_800AFBFC *)view)->value;
    ASM_KEEP(angle);
    view = D_80083160_bytes;
    ASM_KEEP_NV(view);
    rotation = ((D_80083160_t *)view)->angle2;
    angle += 0xc00;
    angle -= (rotation + 0x80) & 0xf00;
    angle_step = angle;
    start_angle = angle;
    ASM_KEEP(angle);
    angle = (s16)angle;
    {
        s32 coord;
        s32 raw_x;
        s32 raw_y;
        register s32 call_value ASM_REG("$4");
        void *call_segment;
        register s16 *call_scratch ASM_REG("$6");
        register s32 call_previous ASM_REG("$7");
        register s32 scaled_coord ASM_REG("$3");
        register s32 end_x ASM_REG("$16");
        start_x = func_80064584(angle) * 6 - offset_x;
        scaled_coord = func_800644B8(angle) * 6;
        coord = scaled_coord - offset_y;
        for (;;) {
            next_angle = angle_step + 0x80;
            ASM_KEEP(next_angle);
            angle = (s16)next_angle;
            scratch[0x80 / 2] = start_x;
            scratch[0x70 / 2] = start_x;
            scratch[0x82 / 2] = coord;
            scratch[0x72 / 2] = coord;
            raw_x = func_80064584(angle);
            call_value = angle;
            scaled_coord = raw_x * 6;
            coord = scaled_coord - offset_x;
            raw_y = func_800644B8(call_value);
            call_scratch = scratch;
            call_previous = last_result;
            scaled_coord = raw_y * 6;
            call_value = (s32)shape;
            call_segment = segment;
            end_y = scaled_coord - offset_y;
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = end_y;
            scratch[0x7a / 2] = end_y;
            result = func_800AFFB4((void *)call_value, call_segment, call_scratch, call_previous, 0);
            next_angle += 0x80;
            if (result == 0)
                break;
            last_result = result;
            angle_step = next_angle;
            ASM_KEEP(angle_step);
            next_angle = (s16)next_angle;
            scratch[0x80 / 2] = coord;
            scratch[0x70 / 2] = coord;
            scratch[0x82 / 2] = end_y;
            scratch[0x72 / 2] = end_y;
            end_x = func_80064584(next_angle) * 6 - offset_x;
            start_x = end_x;
            scaled_coord = func_800644B8(next_angle) * 6 - offset_y;
            coord = scaled_coord;
            ASM_KEEP(coord);
            scratch[0x88 / 2] = end_x;
            scratch[0x78 / 2] = end_x;
            scratch[0x8a / 2] = scaled_coord;
            scratch[0x7a / 2] = scaled_coord;
            result = func_800AFFB4(shape, segment, scratch, last_result, 1);
            if (result == 0)
                break;
            last_result = result;
        }
    }

    {
        register u16 saved_angle ASM_REG("$8");
        s32 coord;
        s32 raw_x;
        s32 raw_y;
        register s32 call_value ASM_REG("$4");
        void *call_segment;
        register s16 *call_scratch ASM_REG("$6");
        register s32 call_previous ASM_REG("$7");
        s32 scaled_coord;
        s32 end_x;
        saved_angle = start_angle;
        angle = (s16)saved_angle;
        ASM_KEEP(saved_angle);
        start_x = func_80064584(angle) * 6 - offset_x;
        coord = func_800644B8(angle) * 6 - offset_y;

        for (;;) {
            saved_angle = start_angle;
            next_angle = saved_angle - 0x80;
            ASM_KEEP(next_angle);
            angle = (s16)next_angle;
            scratch[0x88 / 2] = start_x;
            scratch[0x78 / 2] = start_x;
            scratch[0x8a / 2] = coord;
            scratch[0x7a / 2] = coord;
            raw_x = func_80064584(angle);
            call_value = angle;
            coord = raw_x * 6 - offset_x;
            raw_y = func_800644B8(call_value);
            call_scratch = scratch;
            call_previous = last_result;
            scaled_coord = raw_y * 6;
            end_y = scaled_coord - offset_y;
            call_value = (s32)shape;
            call_segment = segment;
            scratch[0x80 / 2] = coord;
            scratch[0x70 / 2] = coord;
            scratch[0x82 / 2] = end_y;
            scratch[0x72 / 2] = end_y;
            result = func_800AFFB4((void *)call_value, call_segment, call_scratch, call_previous, 1);
            next_angle -= 0x80;
            if (result == 0)
                break;
            last_result = result;
            start_angle = next_angle;
            next_angle = (s16)next_angle;
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = end_y;
            scratch[0x7a / 2] = end_y;
            end_x = func_80064584(next_angle) * 6 - offset_x;
            start_x = end_x;
            ASM_KEEP(start_x);
            scaled_coord = func_800644B8(next_angle) * 6 - offset_y;
            coord = scaled_coord;
            ASM_KEEP(coord);
            call_scratch = scratch;
            call_value = (s32)shape;
            call_segment = segment;
            call_previous = last_result;
            scratch[0x80 / 2] = end_x;
            scratch[0x70 / 2] = end_x;
            scratch[0x82 / 2] = scaled_coord;
            scratch[0x72 / 2] = scaled_coord;
            result = func_800AFFB4((void *)call_value, call_segment, call_scratch, call_previous, 0);
            if (result == 0)
                break;
            last_result = result;
        }
    }
    view = D_80083160_bytes;
    ASM_KEEP_NV(view);
    {
        State_80083160 *final_state;
        final_state = ((D_80083160_t *)view)->state;
        result = 0;
        ASM_KEEP_NV(result);
        final_state->value = last_result;
    }
    return result;
}
