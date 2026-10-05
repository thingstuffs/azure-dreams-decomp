#include "common.h"
#include "shared/game_work.h"

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

extern u8 D_80083160_bytes[] __asm__("D_80083160");
typedef struct ScratchHeader_800AFBFC {
    u8 pad0[0x20];
    void *state_data;
    u8 pad24[0xf4];
    void *segment_data;
} ScratchHeader_800AFBFC;

extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value);
extern s32 func_800AFFB4(void *origin, void *unused, s16 *scratch, s32 previous, s32 side);

/* Processes circular segments in both directions and saves the last successful result. */
s32 func_800AFBFC(Arg0_800AFBFC *shape, s32 unused, Arg2_800AFBFC *segment) {
    s32 last_result = 0;
    s32 result;
    s16 angle;
    s16 next_angle;
    s16 angle_step;
    s16 start_x;
    s32 end_y;
    s16 coord;
    s16 *scratch = (s16 *)0x1F800000;
    D_80083160_t *gw = (D_80083160_t *)D_80083160_bytes;
    State_80083160 *state;
    s16 start_angle;
    void *segment_data;
    s32 rotation;
    u16 flags;
    s32 segment_byte;
    s32 offset_x;
    s32 offset_y;

    state = gw->state;
    last_result = state->value;
    ((ScratchHeader_800AFBFC *)scratch)->state_data = (u8 *)state + 0x8b0;
    segment_data = segment->temp;
    ((ScratchHeader_800AFBFC *)scratch)->segment_data = segment_data;
    offset_x = gw->angle0;
    offset_y = gw->angle1;
    segment_byte = ((u8 *)segment_data)[1];
    flags = segment->flags;
    segment->byte = segment_byte;
    if (flags & 8) {
        if (flags & 4) {
            segment->byte = segment_byte | 2;
        } else {
            segment->byte = segment_byte & 0xfd;
        }
    }

    angle = shape->value;
    rotation = gw->angle2;
    angle += 0xc00;
    angle -= (rotation + 0x80) & 0xf00;
    angle_step = angle;
    start_angle = angle;

    {
        s32 raw_x;
        s32 raw_y;
        s32 call_value;
        void *call_segment;
        s16 *call_scratch;
        s32 scaled_coord;
        s32 end_x;
        start_x = func_80064584(angle) * 6 - offset_x;
        scaled_coord = func_800644B8(angle) * 6;
        coord = scaled_coord - offset_y;
        for (;;) {
            next_angle = angle_step;
            next_angle += 0x80;
            angle = next_angle;
            scratch[0x80 / 2] = start_x;
            scratch[0x70 / 2] = start_x;
            scratch[0x82 / 2] = coord;
            scratch[0x72 / 2] = coord;
            raw_x = func_80064584(angle);
            call_value = angle;
            coord = (raw_x * 6) - offset_x;
            raw_y = func_800644B8(call_value);
            call_scratch = scratch;
            last_result = last_result;
            call_value = (s32)shape;
            call_segment = segment;
            end_y = (raw_y * 6) - offset_y;
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = end_y;
            scratch[0x7a / 2] = end_y;
            result = func_800AFFB4((void *)call_value, call_segment, call_scratch, last_result, 0);
            next_angle += 0x80;
            if (result == 0)
                break;
            last_result = result;
            angle_step = next_angle;
            scratch[0x80 / 2] = coord;
            scratch[0x70 / 2] = coord;
            scratch[0x82 / 2] = end_y;
            scratch[0x72 / 2] = end_y;
            end_x = func_80064584(next_angle) * 6 - offset_x;
            start_x = end_x;
            scaled_coord = func_800644B8(next_angle) * 6 - offset_y;
            coord = scaled_coord;
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
        s32 raw_x;
        s32 raw_y;
        s32 call_value;
        void *call_segment;
        s16 *call_scratch;
        s32 call_previous;
        s32 scaled_coord;
        s32 end_x;
        angle = start_angle;
        start_x = func_80064584(angle) * 6 - offset_x;
        coord = func_800644B8(angle) * 6 - offset_y;

        for (;;) {
            s32 end_y;
            next_angle = start_angle;
            next_angle -= 0x80;
            angle = next_angle;
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
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = end_y;
            scratch[0x7a / 2] = end_y;
            end_x = func_80064584(next_angle) * 6 - offset_x;
            start_x = end_x;
            scaled_coord = func_800644B8(next_angle) * 6 - offset_y;
            coord = scaled_coord;
            call_scratch = scratch;
            call_value = (s32)shape;
            call_segment = segment;
            call_previous = last_result;
            scratch[0x80 / 2] = end_x;
            scratch[0x70 / 2] = end_x;
            scratch[0x82 / 2] = scaled_coord;
            scratch[0x72 / 2] = scaled_coord;
            next_angle = 0;
            result = func_800AFFB4((void *)call_value, call_segment, call_scratch, call_previous, next_angle);
            if (result == 0)
                break;
            last_result = result;
        }
    }
    {
        State_80083160 *final_state;
        final_state = gw->state;
        result = 0;
        final_state->value = last_result;
    }
    return result;
}
