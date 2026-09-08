#include "common.h"


typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Vec3s;

typedef struct {
    void *object;
    u8 pad4[6];
    s16 state;
    u8 padC[0xC];
    s16 timer;
    u16 ticks;
} EffectState;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorObject;

typedef struct {
    u8 pad0[0x1C];
    u32 flags;
} Object;

extern u16 D_80026324;
extern u16 D_80026326;
extern s16 D_80026328[];
extern void *D_80024050[5];
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80080A87[];
extern s32 D_800814A0;

extern void func_80024A9C(void) __attribute__((noreturn));
extern void func_80024AA0(void) __attribute__((noreturn));
extern void func_80024C54(void) __attribute__((noreturn));
extern void func_8002596C(s32, s32, s32);
extern void func_80026010(void);
extern s32 func_80069EF8(void);

/* Advances the effect through color buildup, flicker, and fade, then restores the object color. */
void func_81887004(EffectState *effect, Vec3s *pos)
{
    Object *object;
    ColorObject *color;
    s32 burst_index;
    s32 state;
    s32 channel_value;
    static void *const state_labels[] = {
        &&jt_0, &&jt_1, &&jt_2, &&jt_3, &&jt_4,
    };


    D_80026326++;
    (void)state_labels;
    state = effect->state;
    if ((u32)state >= 5) {
        goto end;
    }
    goto *D_80024050[(u32)state];

jt_0:
    object = effect->object;
    object->flags |= 0x10000000;
    effect->state++;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    color = *(ColorObject **)((u8 *)effect->object - 0x14);
    channel_value = color->r - 1;
    color->r = channel_value;
    if ((u8)channel_value < 0x40) {
        color->r = 0x40;
    }
    channel_value = color->g - 1;
    color->g = channel_value;
    if ((u8)channel_value < 0x40) {
        color->g = 0x40;
    }
    channel_value = color->b + 1;
    color->b = channel_value;
    if ((u8)channel_value >= 0xC1) {
        color->b = 0xC0;
    }
    if (D_80026328[0] != 0) {
        s32 next_state;

        next_state = ((volatile u16 *)effect)[5] + 1;
        ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024AA0();
    }
    goto end;

jt_1: {
    register s32 next_timer ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 *primary_rgb;
    u8 *secondary_rgb;

    effect->timer++;
    D_80026470[0] = effect->timer * 2;
    primary_rgb = D_80026470;
    primary_rgb[1] = effect->timer * 4;
    primary_rgb[2] = effect->timer * 14;
    D_80026474[0] = effect->timer * 10;
    secondary_rgb = D_80026474;
    secondary_rgb[1] = effect->timer * 11;
    secondary_rgb[2] = effect->timer * 14;

    for (burst_index = 0; burst_index < 4; burst_index++) {
        func_8002596C(pos->x, pos->y, pos->z);
    }
    next_timer = 0xA0;
    if (effect->timer >= 0x10) {
        ((volatile u16 *)effect)[5];
        effect->timer = next_timer;
        func_80024A9C();
    }
    goto end;
}

jt_2: {
    u8 *random_rgb;

    D_80026474[0] = (func_80069EF8() % 0x3F) - 0x80;
    random_rgb = D_80026474;
    random_rgb[1] = (func_80069EF8() % 0x3F) - 0x80;
    effect->timer -= D_80080A87[0];
    if (effect->timer <= 0) {
        func_80026010();
        effect->timer = 0x10;
        effect->state++;
        func_80024C54();
    }
    goto end;
}

jt_3: {
    u8 *primary_rgb;
    u8 *secondary_rgb;

    D_80026470[0] += -(s32)D_80026470[0] / effect->timer;
    primary_rgb = D_80026470;
    primary_rgb[1] += -(s32)primary_rgb[1] / effect->timer;
    primary_rgb[2] += -(s32)primary_rgb[2] / effect->timer;
    D_80026474[0] += -(s32)D_80026474[0] / effect->timer;
    secondary_rgb = D_80026474;
    secondary_rgb[1] += -(s32)secondary_rgb[1] / effect->timer;
    secondary_rgb[2] += -(s32)secondary_rgb[2] / effect->timer;
}

jt_4: {
    s32 neutral_level;
    s32 effect_count;
    u32 flags;
    u32 clear_effect_mask;
    register u8 *counter_base ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *status_base ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    Object *fade_object;

    color = *(ColorObject **)((u8 *)effect->object - 0x14);
    neutral_level = 0x80;
    color->r += (neutral_level - color->r) / effect->timer;
    color->g += (neutral_level - color->g) / effect->timer;
    color->b += (neutral_level - color->b) / effect->timer;
    effect->timer--;
    if (effect->timer <= 0) {
        clear_effect_mask = 0xEFFFFFFF;
        color->r = neutral_level;
        color->g = neutral_level;
        color->b = neutral_level;
        fade_object = effect->object;
        counter_base = (u8 *)0x80020000;
        effect_count = *(u16 *)(counter_base + 0x6324);
        flags = fade_object->flags;
        effect_count--;
        *(u16 *)(counter_base + 0x6324) = effect_count;
        flags &= clear_effect_mask;
        fade_object->flags = flags;
        ((u16 *)effect)[-1] |= 0x8000;
        status_base = (u8 *)0x80080000;
        *(volatile s32 *)(status_base + 0x14A0) |= 0x8000;
    }
    goto end;
}

end:
    effect->ticks++;
}
