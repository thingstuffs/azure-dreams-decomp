#include "common.h"

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad;
} ColorEntry;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[1];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[1];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 pad_0B[1];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[9];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    u16 out1[2][3];
    u16 out2[2][3];
} ObjectPayload;

typedef struct S_func_81331914_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;
    u8 pad_14[4];
    union { s16 s; u16 u; } unk_18;
    u8 pad_1A[2];
    s16 unk_1C;
} S_func_81331914_0;

typedef struct S_func_81331914_1 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_81331914_1;

typedef struct S_func_81331914_2 {
    u8 pad_00[6];
    s16 unk_06;
    u8 pad_08[4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[1];
    u16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_81331914_2;

typedef struct S_func_81331914_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_func_81331914_3;

typedef struct S_func_81331914_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_func_81331914_4;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_800814A0;
extern u8 D_800DEAE0[];
extern u8 D_80166914[];
extern u8 D_80167C30[];
extern s16 D_80175DD8[][8][2][3];

/* Spawn seven colored segments from interpolated vertices and advance the effect lifetime. */
void func_80168914(S_func_81331914_0 *state, s32 *position, S_func_81331914_4 *colors)
{
    s32 step;
    s32 vertex_index;
    s32 axis;
    s32 segment_index;
    S_func_81331914_1 *object;
    ObjectPayload *payload;
    S_func_81331914_2 *sprite;
    S_func_81331914_3 *object_position;
    volatile ColorEntry *vertex_color;
    u16 ticks_left;

    if ((state->unk_12.s == 0) &&
        (state->unk_18.s < 12)) {
        state->unk_12.u++;
    }

    step = 1;
    do {
        vertex_index = 0;
        do {
            axis = 0;
            do {
                D_80175DD8[state->unk_1C][step][vertex_index][axis] =
                    D_80175DD8[state->unk_1C][0][vertex_index][axis] +
                    (D_80175DD8[state->unk_1C][7][vertex_index][axis] -
                     D_80175DD8[state->unk_1C][0][vertex_index][axis]) *
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
            payload = (ObjectPayload *)((u8 *)object + 0x20);
            payload->unk_18 = 1;
            payload->unk_1A = 1;
            object->unk_10 = D_80167C30;
            func_8004491C(object, D_80166914);

            sprite = object->unk_0C;
            sprite->unk_10 = 0x20;
            sprite->unk_14 |= 0xC;

            object_position = object->unk_08;
            object_position->unk_00 = position[0];
            object_position->unk_04 = position[1];
            step = 0;
            vertex_color = (volatile ColorEntry *)payload;
            object_position->unk_08 = position[2];

            sprite = object->unk_0C;
            sprite->unk_1C = sprite->unk_1E = 0x1000;
            sprite->unk_0C = sprite->unk_0D = sprite->unk_0E = 0x80;

            do {
                vertex_color->red = colors->unk_0C;
                vertex_color->green = colors->unk_0D;
                vertex_color->blue = colors->unk_0E;
                step++;
                vertex_color++;
            } while (step < 4);

            if (segment_index == 0) {
                payload->unk_00 = payload->unk_01 = payload->unk_02 =
                payload->unk_04 = payload->unk_05 = payload->unk_06 = 0;
            }
            if (segment_index == 6) {
                payload->unk_08 = payload->unk_09 = payload->unk_0A =
                payload->unk_0C = payload->unk_0D = payload->unk_0E = 0;
            }

            sprite->unk_06 = 0;
            func_8003DB94(sprite, D_800DEAE0, 0);

            vertex_index = 0;
            do {
                axis = 0;
                do {
                    ((ObjectPayload *)payload)->out1[vertex_index][axis] =
                        D_80175DD8[state->unk_1C][segment_index][vertex_index][axis];
                    ((ObjectPayload *)payload)->out2[vertex_index][axis] =
                        D_80175DD8[state->unk_1C][segment_index + 1][vertex_index][axis];
                    axis++;
                } while (axis < 3);
                vertex_index++;
            } while (vertex_index < 2);
        }
        segment_index++;
    } while (segment_index < 7);

    ticks_left = state->unk_18.u - 1;
    state->unk_18.u = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
