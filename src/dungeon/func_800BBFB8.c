#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad00[0x1c];
    s32 flags;
    u8 pad20[4];
    s8 byte24;
    u8 byte25;
    u8 byte26;
    u8 byte27;
    u8 pad28[0x20];
    s16 field48;
    s16 mode;
    s16 count;
    u16 field4e;
    s16 field50;
    u8 pad52[6];
    s16 field58;
    u8 pad5a[0xa];
    s16 field64;
    u8 byte66;
    u8 pad67;
    u8 byte68;
    u8 byte69;
} DungeonState;

typedef struct {
    u8 pad00[2];
    s16 x;
    u8 pad04[2];
    s16 y;
    u8 pad08[2];
    s16 z;
} RenderSource;

extern u8 *D_800E3D7C[];
extern s32 D_800814A0;

extern void func_80042B68(void *obj, s8 index);
extern void func_80041E70(void *obj);
extern void func_800AD568(void *obj);
extern void func_800BC0A8(s16 x, s16 y, s16 z, s16 angle,
                          s32 height, s32 depth, s32 color, s32 offset);

void func_800C1718(DungeonState *state, RenderSource *arg1, u8 *arg2) {
    s32 i;
    s32 j;
    RenderSource *source = arg1;
    s16 mode = state->mode;
    s16 count;
    s16 marker;
    u16 angle1;
    u16 angle2;
    void *entry;
    u8 *obj;

    if (mode == 1)
        goto mode_one;
    if (mode < 2) {
        if (mode == 0)
            goto mode_zero;
        goto done;
    }
    if (mode == 2)
        goto mode_two;
    goto done;

mode_zero:
    {
        u16 value = *(u16 *)(arg2 + 0x1c);
        value += (u16)((0x800 - value) / state->count);
        *(u16 *)(arg2 + 0x1c) = value;
        *(u16 *)(arg2 + 0x1e) = value;
    }

    count = (u16)state->count - 1;
    state->count = count;
    if ((count << 16) > 0)
        goto done;

    i = 0;
    marker = 0xff;
    do {
        entry = *(void **)(D_800E3D7C[0] + i * 4 + 0xac);
        if (entry != NULL) {
            obj = entry;
            j = 1;
            *(u8 *)(obj + 0x26) = *(u8 *)(obj + 0x68);
            *(u8 *)(obj + 0x27) = *(u8 *)(obj + 0x69);
            do {
                func_80042B68(obj, (s8)j);
                j += 1;
            } while (j < 0x21);
            *(s16 *)(obj + 0x64) = marker;
            *(s32 *)(obj + 0x1c) &= 0xfbffe107;
            func_800AD568(obj);
            *(s8 *)(obj + 0x24) = marker;
            *(u8 *)(obj + 0x25) = *(u8 *)(obj + 0x66);
            func_80041E70(obj);
        }
        i += 1;
    } while (i < 2);

    state->count = 8;
    state->mode += 1;
    goto done;

mode_one:
    state->field50 = (s16)((u16)state->field50 +
        ((0xc0 - state->field50) / state->count));
    j = 0;
    do {
        angle1 = state->field4e + 0x100;
        state->field4e = angle1;
        func_800BC0A8(source->x, source->y, source->z, (s16)angle1,
                      state->field50, state->field58, 0x802020,
                      state->field48);
        j += 1;
    } while (j < 4);
    count = (u16)state->count - 1;
    state->count = count;
    if ((count << 16) > 0)
        goto done;
    state->count = 4;
    state->mode += 1;
    goto done;

mode_two:
    state->field50 = (s16)((u16)state->field50 -
        (state->field50 / state->count));
    *(u8 *)(arg2 + 0xc) = (u8)(*(u8 *)(arg2 + 0xc) -
        (*(u8 *)(arg2 + 0xc) / state->count));
    *(u8 *)(arg2 + 0xd) = (u8)(*(u8 *)(arg2 + 0xd) -
        (*(u8 *)(arg2 + 0xd) / state->count));
    *(u8 *)(arg2 + 0xe) = (u8)(*(u8 *)(arg2 + 0xe) -
        (*(u8 *)(arg2 + 0xe) / state->count));
    j = 0;
    do {
        angle2 = state->field4e + 0x100;
        state->field4e = angle2;
        func_800BC0A8(source->x, source->y, source->z, (s16)angle2,
                      state->field50, state->field58, 0x802020,
                      state->field48);
        j += 1;
    } while (j < 4);
    count = (u16)state->count - 1;
    state->count = count;
    if ((count << 16) > 0)
        goto done;
    *((u16 *)state - 1) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
