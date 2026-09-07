#include "common.h"

typedef struct {
    u8 *field0;
    u8 pad04[0x10];
    s16 field14;
} DungeonState;

typedef struct {
    s32 field0;
    u16 flags;
} DungeonCell;

typedef struct {
    u8 pad00[0x10];
    s16 field10;
    s16 field12;
    s16 field14;
    u16 field16;
} GlobalState;

extern DungeonState D_8008333C;
extern GlobalState D_80082E60;
extern s8 D_800DCF5B[9];
extern s32 D_800E296C[3];

extern void func_80043B4C(void);

void func_807AF2F4(void)
{
    DungeonState *state;
    u8 *base;
    GlobalState *global;
    s32 i;

    state = &D_8008333C;
    base = state->field0;

    i = 0x10;
    do {
        ((DungeonCell *)(base + (i + (0x11 << state->field14)) * 6))->flags |= 0x8000;
        i++;
    } while (i < 0x1D);

    i = 0x23;
    do {
        ((DungeonCell *)(base + (i + (0x11 << state->field14)) * 6))->flags |= 0x8000;
        i++;
    } while (i < 0x30);

    i = 0x12;
    do {
        ((DungeonCell *)(base + (i << state->field14) * 6 + 0x60))->flags |= 0x8000;
        ((DungeonCell *)(base + (i << state->field14) * 6 + 0x11A))->flags |= 0x8000;
        i++;
    } while (i < 0x20);

    i = 0x10;
    do {
        ((DungeonCell *)(base + (i + (0x20 << state->field14)) * 6))->flags |= 0x8000;
        ((DungeonCell *)(base + (i + (0x21 << state->field14)) * 6))->flags |= 0x8000;
        i++;
    } while (i < 0x30);

    ((DungeonCell *)(base + (0x23 << state->field14) * 6 + 0xBA))->flags |= 0x8000;
    ((DungeonCell *)(base + (0x23 << state->field14) * 6 + 0xC0))->flags |= 0x8000;

    func_80043B4C();

    global = &D_80082E60;
    global->field10 = 0x1F;
    global->field12 = 0x39;
    D_800DCF5B[0] = 1;
    global->field16 |= 1;
    D_800E296C[0] |= 0x10000000;
}
