#include "common.h"

#define FIELD(type, base, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad;
} ColorEntry;

typedef struct {
    u8 pad[0x74];
    u16 out1[2][3];
    u16 out2[2][3];
} ObjectPayload;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_800814A0;
extern u8 D_800DEAE0[];
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern s16 D_80175DD8[][8][2][3];

/* Spawn seven colored segments from interpolated vertices and advance the effect lifetime. */
void func_80168914(u8 *state, s32 *position, u8 *colors)
{
    s32 step;
    s32 vertex_index;
    s32 axis;
    s32 segment_index;
    u8 *object;
    u8 *payload;
    u8 *sprite;
    u8 *object_position;
    volatile ColorEntry *vertex_color;
    u16 ticks_left;

    if ((FIELD(s16, state, 0x12) == 0) &&
        (FIELD(s16, state, 0x18) < 12)) {
        FIELD(u16, state, 0x12)++;
    }

    step = 1;
    do {
        vertex_index = 0;
        do {
            axis = 0;
            do {
                D_80175DD8[FIELD(s16, state, 0x1C)][step][vertex_index][axis] =
                    D_80175DD8[FIELD(s16, state, 0x1C)][0][vertex_index][axis] +
                    (D_80175DD8[FIELD(s16, state, 0x1C)][7][vertex_index][axis] -
                     D_80175DD8[FIELD(s16, state, 0x1C)][0][vertex_index][axis]) *
                    step / 7;
                axis++;
            } while (axis < 3);
            vertex_index++;
        } while (vertex_index < 2);
        step++;
    } while (step < 7);

    segment_index = 0;
    do {
        object = func_8003FC64(0x212);
        if (object != 0) {
            payload = object + 0x20;
            FIELD(s16, payload, 0x18) = 1;
            FIELD(s16, payload, 0x1A) = 1;
            FIELD(void *, object, 0x10) = D_80167C30;
            func_8004491C(object, D_80166914);

            sprite = FIELD(u8 *, object, 0xC);
            FIELD(u16, sprite, 0x10) = 0x20;
            FIELD(u16, sprite, 0x14) |= 0xC;

            object_position = FIELD(u8 *, object, 8);
            FIELD(s32, object_position, 0) = position[0];
            FIELD(s32, object_position, 4) = position[1];
            step = 0;
            vertex_color = (volatile ColorEntry *)payload;
            FIELD(s32, object_position, 8) = position[2];

            sprite = FIELD(u8 *, object, 0xC);
            FIELD(s16, sprite, 0x1C) = FIELD(s16, sprite, 0x1E) = 0x1000;
            sprite[0xC] = sprite[0xD] = sprite[0xE] = 0x80;

            do {
                vertex_color->red = colors[0xC];
                vertex_color->green = colors[0xD];
                vertex_color->blue = colors[0xE];
                step++;
                vertex_color++;
            } while (step < 4);

            if (segment_index == 0) {
                payload[0] = payload[1] = payload[2] =
                payload[4] = payload[5] = payload[6] = 0;
            }
            if (segment_index == 6) {
                payload[8] = payload[9] = payload[0xA] =
                payload[0xC] = payload[0xD] = payload[0xE] = 0;
            }

            FIELD(s16, sprite, 6) = 0;
            func_8003DB94(sprite, D_800DEAE0, 0);

            vertex_index = 0;
            do {
                axis = 0;
                do {
                    ((ObjectPayload *)payload)->out1[vertex_index][axis] =
                        D_80175DD8[FIELD(s16, state, 0x1C)][segment_index][vertex_index][axis];
                    ((ObjectPayload *)payload)->out2[vertex_index][axis] =
                        D_80175DD8[FIELD(s16, state, 0x1C)][segment_index + 1][vertex_index][axis];
                    axis++;
                } while (axis < 3);
                vertex_index++;
            } while (vertex_index < 2);
        }
        segment_index++;
    } while (segment_index < 7);

    ticks_left = FIELD(u16, state, 0x18) - 1;
    FIELD(u16, state, 0x18) = ticks_left;
    if ((s16)ticks_left <= 0) {
        FIELD(u16, state, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
