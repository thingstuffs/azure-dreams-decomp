#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 rand(void);

extern s32 D_80045340;
extern u8 D_80083160[];
extern LocalTable D_80170874;
extern u8 D_80174C70[12];
extern LocalPacket D_80175A0C;

/* Spawn an object near the origin with randomized position and directional motion. */
void func_80174F24(s32 unused, void *origin)
{
    LocalVector direction;
    LocalTable directions;
    s16 angle;
    s32 jitter;
    s32 coordinate;
    s32 x_offset;
    u8 *globals;
    u8 *direction_entry;
    void *object;
    void *state;
    void *transform;
    void *display;

    directions = D_80170874;
    object = func_8003FC64(0x212);
    state = (u8 *)object + 0x20;
    if (object != 0) {
        FIELD(state, s16, 0x1A) = 0;
        angle = 0;
        globals = D_80083160;
        do {
            if (((FIELD(globals, s16, 0xC8) + angle + 0x100) >> 9 & 7) == 2) {
                FIELD(state, s16, 0x18) = angle;
            }
            angle += 0x200;
        } while (angle < 0x1000);

        FIELD(object, void *, 0x10) = D_80174C70;
        func_8004491C(object, &D_80045340);

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x10) = 0x20;
        FIELD(display, u16, 0x14) |= 0xC;

        transform = FIELD(object, void *, 8);
        jitter = rand() & 0x1F;
        coordinate = FIELD(origin, u16, 2) - 0x10;
        coordinate += jitter;
        FIELD(transform, s16, 2) = coordinate;
        jitter = rand() & 0x1F;
        coordinate = FIELD(origin, u16, 6) - 0x10;
        coordinate += jitter;
        FIELD(transform, s16, 6) = coordinate;
        jitter = (rand() & 0x1F) - 0x70;
        coordinate = FIELD(origin, u16, 0xA);
        coordinate += jitter;
        FIELD(transform, s16, 0xA) = coordinate;

        direction_entry = (u8 *)&directions;
        direction.x = FIELD(direction_entry, u16,
            ((FIELD(state, s16, 0x18) - 0x400) >> 7) & 0x1C);
        direction_entry +=
            ((FIELD(state, s16, 0x18) - 0x400) >> 7) & 0x1C;
        direction.y = FIELD(direction_entry, u16, 2);
        x_offset = direction.x << 19;
        FIELD(transform, s32, 0xC) = x_offset;
        FIELD(transform, s32, 0x10) = direction.y << 19;
        FIELD(transform, s32, 0) += x_offset;
        FIELD(transform, s32, 4) += FIELD(transform, s32, 0x10);

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x1E) = 0x200;
        FIELD(display, s16, 0x1C) = 0x200;
        FIELD(display, s8, 0xE) = 0x20;
        FIELD(display, s8, 0xD) = 0x20;
        FIELD(display, s8, 0xC) = 0x20;
        FIELD(display, s16, 0x12) = 0x7DCF;
        FIELD(display, u16, 0x14) |= 0x100;
        *(LocalPacket *)((u8 *)state + 0x28) = D_80175A0C;
        FIELD(display, void *, 8) = (u8 *)state + 0x28;
    }
}
