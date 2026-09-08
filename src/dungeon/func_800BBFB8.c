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

/* Updates a three-stage visual effect, restoring objects and fading the rendered effect. */
void func_800C1718(DungeonState *state, RenderSource *render_source, u8 *effect_data) {
    s32 object_index;
    s32 step_index;
    RenderSource *source = render_source;
    s16 mode = state->mode;
    s16 frames_left;
    s16 reset_marker;
    u16 grow_angle;
    u16 fade_angle;
    void *object_entry;
    u8 *object;

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
        u16 effect_scale = *(u16 *)(effect_data + 0x1c);
        effect_scale += (u16)((0x800 - effect_scale) / state->count);
        *(u16 *)(effect_data + 0x1c) = effect_scale;
        *(u16 *)(effect_data + 0x1e) = effect_scale;
    }

    frames_left = (u16)state->count - 1;
    state->count = frames_left;
    if ((frames_left << 16) > 0)
        goto done;

    object_index = 0;
    reset_marker = 0xff;
    do {
        object_entry = *(void **)(D_800E3D7C[0] + object_index * 4 + 0xac);
        if (object_entry != NULL) {
            object = object_entry;
            step_index = 1;
            *(u8 *)(object + 0x26) = *(u8 *)(object + 0x68);
            *(u8 *)(object + 0x27) = *(u8 *)(object + 0x69);
            do {
                func_80042B68(object, (s8)step_index);
                step_index += 1;
            } while (step_index < 0x21);
            *(s16 *)(object + 0x64) = reset_marker;
            *(s32 *)(object + 0x1c) &= 0xfbffe107;
            func_800AD568(object);
            *(s8 *)(object + 0x24) = reset_marker;
            *(u8 *)(object + 0x25) = *(u8 *)(object + 0x66);
            func_80041E70(object);
        }
        object_index += 1;
    } while (object_index < 2);

    state->count = 8;
    state->mode += 1;
    goto done;

mode_one:
    state->field50 = (s16)((u16)state->field50 +
        ((0xc0 - state->field50) / state->count));
    step_index = 0;
    do {
        grow_angle = state->field4e + 0x100;
        state->field4e = grow_angle;
        func_800BC0A8(source->x, source->y, source->z, (s16)grow_angle,
                      state->field50, state->field58, 0x802020,
                      state->field48);
        step_index += 1;
    } while (step_index < 4);
    frames_left = (u16)state->count - 1;
    state->count = frames_left;
    if ((frames_left << 16) > 0)
        goto done;
    state->count = 4;
    state->mode += 1;
    goto done;

mode_two:
    state->field50 = (s16)((u16)state->field50 -
        (state->field50 / state->count));
    *(u8 *)(effect_data + 0xc) = (u8)(*(u8 *)(effect_data + 0xc) -
        (*(u8 *)(effect_data + 0xc) / state->count));
    *(u8 *)(effect_data + 0xd) = (u8)(*(u8 *)(effect_data + 0xd) -
        (*(u8 *)(effect_data + 0xd) / state->count));
    *(u8 *)(effect_data + 0xe) = (u8)(*(u8 *)(effect_data + 0xe) -
        (*(u8 *)(effect_data + 0xe) / state->count));
    step_index = 0;
    do {
        fade_angle = state->field4e + 0x100;
        state->field4e = fade_angle;
        func_800BC0A8(source->x, source->y, source->z, (s16)fade_angle,
                      state->field50, state->field58, 0x802020,
                      state->field48);
        step_index += 1;
    } while (step_index < 4);
    frames_left = (u16)state->count - 1;
    state->count = frames_left;
    if ((frames_left << 16) > 0)
        goto done;
    *((u16 *)state - 1) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
