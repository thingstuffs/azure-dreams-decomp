#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    u32 words[8];
} __attribute__((packed)) LocalTable;

typedef struct {
    u32 words[3];
} __attribute__((packed)) LocalPacket;

typedef struct S_func_80AF3724_0 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
    u8 pad_08[2];
    u16 unk_0A;
} S_func_80AF3724_0;

typedef struct S_func_80AF3724_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_func_80AF3724_1;

typedef struct S_func_80AF3724_2 {
    u16 unk_00;
    u16 unk_02;
} S_func_80AF3724_2;

typedef struct S_func_80AF3724_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_80AF3724_3;

typedef struct S_func_80AF3724_4 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0xC];
    LocalPacket unk_28;
} S_func_80AF3724_4;

typedef struct S_func_80AF3724_5 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            s16 unk_02;
        } unk_02;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            s16 unk_06;
        } unk_06;
    } unk_04;
    u8 pad_08[2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_func_80AF3724_5;

typedef struct S_func_80AF3724_6 {
    u8 pad_00[8];
    void *unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_80AF3724_6;

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 rand(void);

extern s32 D_80045340;
extern u8 D_80083160[];
extern LocalTable D_80170874;
extern u8 D_80174C70[12];
extern LocalPacket D_80175A0C;

/* Spawn an object near the origin with randomized position and directional motion. */
void func_80174F24(s32 unused, S_func_80AF3724_0 *origin)
{
    LocalVector direction;
    LocalTable directions;
    s16 angle;
    s32 jitter;
    s32 coordinate;
    s32 x_offset;
    S_func_80AF3724_1 *globals;
    S_func_80AF3724_2 *direction_entry;
    S_func_80AF3724_3 *object;
    S_func_80AF3724_4 *state;
    S_func_80AF3724_5 *transform;
    S_func_80AF3724_6 *display;

    directions = D_80170874;
    object = func_8003FC64(0x212);
    state = (S_func_80AF3724_4 *)((u8 *)object + 0x20);
    if (object != 0) {
        state->unk_1A = 0;
        angle = 0;
        globals = (S_func_80AF3724_1 *)D_80083160;
        do {
            if (((globals->unk_C8 + angle + 0x100) >> 9 & 7) == 2) {
                state->unk_18 = angle;
            }
            angle += 0x200;
        } while (angle < 0x1000);

        object->unk_10 = D_80174C70;
        func_8004491C(object, &D_80045340);

        display = object->unk_0C;
        display->unk_10 = 0x20;
        display->unk_14 |= 0xC;

        transform = object->unk_08;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_02 - 0x10;
        coordinate += jitter;
        transform->unk_00.unk_02.unk_02 = coordinate;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_06 - 0x10;
        coordinate += jitter;
        transform->unk_04.unk_06.unk_06 = coordinate;
        jitter = (rand() & 0x1F) - 0x70;
        coordinate = origin->unk_0A;
        coordinate += jitter;
        transform->unk_0A = coordinate;

        direction_entry = (S_func_80AF3724_2 *)&directions;
        direction.x = ((S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C)))->unk_00;
        direction_entry = (S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C));
        direction.y = direction_entry->unk_02;
        x_offset = direction.x << 19;
        transform->unk_0C = x_offset;
        transform->unk_10 = direction.y << 19;
        transform->unk_00.unk_00 += x_offset;
        transform->unk_04.unk_04 += transform->unk_10;

        display = object->unk_0C;
        display->unk_1E = 0x200;
        display->unk_1C = 0x200;
        display->unk_0E = 0x20;
        display->unk_0D = 0x20;
        display->unk_0C = 0x20;
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
        state->unk_28 = D_80175A0C;
        display->unk_08 = &state->unk_28;
    }
}
