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

void func_81887004(EffectState *effect, Vec3s *pos)
{
    Object *object;
    ColorObject *color;
    s32 i;
    s32 state;
    s32 value;
    static void *const jt_keep[] = {
        &&jt_0, &&jt_1, &&jt_2, &&jt_3, &&jt_4,
    };


    D_80026326++;
    (void)jt_keep;
    state = effect->state;
    if ((u32)state >= 5) {
        goto end;
    }
    goto *D_80024050[(u32)state];

jt_0:
    object = effect->object;
    object->flags |= 0x10000000;
    effect->state++;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    color = *(ColorObject **)((u8 *)effect->object - 0x14);
    value = color->r - 1;
    color->r = value;
    if ((u8)value < 0x40) {
        color->r = 0x40;
    }
    value = color->g - 1;
    color->g = value;
    if ((u8)value < 0x40) {
        color->g = 0x40;
    }
    value = color->b + 1;
    color->b = value;
    if ((u8)value >= 0xC1) {
        color->b = 0xC0;
    }
    if (D_80026328[0] != 0) {
        s32 dead_tick;

        dead_tick = ((volatile u16 *)effect)[5] + 1;
        ASM_TAILSLOT_PIN(dead_tick);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024AA0();
    }
    goto end;

jt_1: {
    register s32 next_timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *rgb0;
    u8 *rgb1;

    effect->timer++;
    D_80026470[0] = effect->timer * 2;
    rgb0 = D_80026470;
    rgb0[1] = effect->timer * 4;
    rgb0[2] = effect->timer * 14;
    D_80026474[0] = effect->timer * 10;
    rgb1 = D_80026474;
    rgb1[1] = effect->timer * 11;
    rgb1[2] = effect->timer * 14;

    for (i = 0; i < 4; i++) {
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
    u8 *rgb0;
    u8 *rgb1;

    D_80026470[0] += -(s32)D_80026470[0] / effect->timer;
    rgb0 = D_80026470;
    rgb0[1] += -(s32)rgb0[1] / effect->timer;
    rgb0[2] += -(s32)rgb0[2] / effect->timer;
    D_80026474[0] += -(s32)D_80026474[0] / effect->timer;
    rgb1 = D_80026474;
    rgb1[1] += -(s32)rgb1[1] / effect->timer;
    rgb1[2] += -(s32)rgb1[2] / effect->timer;
}

jt_4: {
    s32 limit;
    s32 page_value;
    u32 flags;
    u32 mask;
    register u8 *page2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u8 *page8 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    Object *fade_object;

    color = *(ColorObject **)((u8 *)effect->object - 0x14);
    limit = 0x80;
    color->r += (limit - color->r) / effect->timer;
    color->g += (limit - color->g) / effect->timer;
    color->b += (limit - color->b) / effect->timer;
    effect->timer--;
    if (effect->timer <= 0) {
        mask = 0xEFFFFFFF;
        color->r = limit;
        color->g = limit;
        color->b = limit;
        fade_object = effect->object;
        page2 = (u8 *)0x80020000;
        page_value = *(u16 *)(page2 + 0x6324);
        flags = fade_object->flags;
        page_value--;
        *(u16 *)(page2 + 0x6324) = page_value;
        flags &= mask;
        fade_object->flags = flags;
        ((u16 *)effect)[-1] |= 0x8000;
        page8 = (u8 *)0x80080000;
        *(volatile s32 *)(page8 + 0x14A0) |= 0x8000;
    }
    goto end;
}

end:
    effect->ticks++;
}
