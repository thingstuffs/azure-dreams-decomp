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

void func_80168914(u8 *state, s32 *position, u8 *colors)
{
    s32 step;
    s32 row;
    s32 column;
    s32 object_index;
    u8 *object;
    u8 *data;
    u8 *sprite;
    u8 *out;
    volatile ColorEntry *color_out;
    u16 timer;

    if ((FIELD(s16, state, 0x12) == 0) &&
        (FIELD(s16, state, 0x18) < 12)) {
        FIELD(u16, state, 0x12)++;
    }

    step = 1;
    do {
        row = 0;
        do {
            column = 0;
            do {
                D_80175DD8[FIELD(s16, state, 0x1C)][step][row][column] =
                    D_80175DD8[FIELD(s16, state, 0x1C)][0][row][column] +
                    (D_80175DD8[FIELD(s16, state, 0x1C)][7][row][column] -
                     D_80175DD8[FIELD(s16, state, 0x1C)][0][row][column]) *
                    step / 7;
                column++;
            } while (column < 3);
            row++;
        } while (row < 2);
        step++;
    } while (step < 7);

    object_index = 0;
    do {
        object = func_8003FC64(0x212);
        if (object != 0) {
            data = object + 0x20;
            FIELD(s16, data, 0x18) = 1;
            FIELD(s16, data, 0x1A) = 1;
            FIELD(void *, object, 0x10) = D_80167C30;
            func_8004491C(object, D_80166914);

            sprite = FIELD(u8 *, object, 0xC);
            FIELD(u16, sprite, 0x10) = 0x20;
            FIELD(u16, sprite, 0x14) |= 0xC;

            out = FIELD(u8 *, object, 8);
            FIELD(s32, out, 0) = position[0];
            FIELD(s32, out, 4) = position[1];
            step = 0;
            color_out = (volatile ColorEntry *)data;
            FIELD(s32, out, 8) = position[2];

            sprite = FIELD(u8 *, object, 0xC);
            FIELD(s16, sprite, 0x1C) = FIELD(s16, sprite, 0x1E) = 0x1000;
            sprite[0xC] = sprite[0xD] = sprite[0xE] = 0x80;

            do {
                color_out->red = colors[0xC];
                color_out->green = colors[0xD];
                color_out->blue = colors[0xE];
                step++;
                color_out++;
            } while (step < 4);

            if (object_index == 0) {
                data[0] = data[1] = data[2] =
                data[4] = data[5] = data[6] = 0;
            }
            if (object_index == 6) {
                data[8] = data[9] = data[0xA] =
                data[0xC] = data[0xD] = data[0xE] = 0;
            }

            FIELD(s16, sprite, 6) = 0;
            func_8003DB94(sprite, D_800DEAE0, 0);

            row = 0;
            do {
                column = 0;
                do {
                    ((ObjectPayload *)data)->out1[row][column] =
                        D_80175DD8[FIELD(s16, state, 0x1C)][object_index][row][column];
                    ((ObjectPayload *)data)->out2[row][column] =
                        D_80175DD8[FIELD(s16, state, 0x1C)][object_index + 1][row][column];
                    column++;
                } while (column < 3);
                row++;
            } while (row < 2);
        }
        object_index++;
    } while (object_index < 7);

    timer = FIELD(u16, state, 0x18) - 1;
    FIELD(u16, state, 0x18) = timer;
    if ((s16)timer <= 0) {
        FIELD(u16, state, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
