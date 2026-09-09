#include "common.h"

#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

extern void func_800252B8();
extern void func_800267DC();
extern void func_80026978();
extern void *func_8003FC64();
extern void func_8004491C();
extern void SD_Call();
extern s32 rand();

extern u8 D_80026748[];
extern u8 D_80045340[];
extern s32 D_800814A0;
extern u8 D_80082E80[16];
extern s32 D_80083784;
extern u8 D_800F7950[];
extern u8 D_800F795C[];

/* Updates object movement, proximity reactions, and particle effects through each phase. */
void func_8002614C(void *state_data, void *position_data, void *sprite_data)
{
    u8 *state = state_data;
    s32 *position = position_data;
    u8 *sprite = sprite_data;
    register u8 *object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *owner;
    s32 remaining;
    s32 next_x;
    s32 particle_x;
    s32 rebound_x;
    s32 burst_x;
    s32 y_distance;
    s32 x_jitter;
    s32 burst_velocity;
    u16 type_index;
    u8 *effect;
    u8 *effect_state;
    u8 *effect_position;
    u8 *effect_sprite;
    u8 *color_state;

    ASM_KEEP_NV(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    object = PTR(state, 0);
    U16(object, 0x58) |= 1;
    owner = PTR(object, 0);

    if (S16(object, 0x54) == 9 && S16(state, 0xC) == 1 && *position <= 0x4DFFFFF) {
        switch (S16(object, 0x56)) {
        case 0:
            U8(sprite, 0xC) = 0xFF;
            remaining = 3;
            do {
                func_800267DC(position);
                remaining--;
            } while (remaining >= 0);
            break;
        case 1:
            U16(sprite, 0x14) |= 0xC;
            remaining = 2;
            do {
                func_80026978(position);
                remaining--;
            } while (remaining >= 0);
            break;
        case 2:
            U16(sprite, 0x1E) += 0x200;
            U16(sprite, 0x1C) = U16(sprite, 0x1E);
            break;
        }
    }

    switch (S16(state, 0xC)) {
    case 0:
        if (S16(state, 0xE) == 0x10) {
            U16(object, 0x58) |= 4;
        } else {
            U16(object, 0x58) &= 0xFFFB;
        }
        U16(state, 0xE)--;
        if (S16(state, 0xE) > 0) {
            break;
        }
        SD_Call(0x518);
        U16(PTR(object, 0), 0x12)++;
        S16(state, 0xC) = 1;
        U16(sprite, 0x14) &= 0xFF7F;
        break;

    case 1:
        S32(state, 4) += S32(state, 8);
        next_x = *position + S32(state, 4);
        *position = next_x;
        if (next_x <= 0x427FFFF) {
            S16(state, 0xE) = 6;
            color_state = D_80082E80;
            if (U8(color_state, 0xC) >= 9) {
                S32(color_state, 0xC) -= 0x80808;
            }
            U16(sprite, 0x14) |= 0x80;
            SD_Call(0x506);
            S16(state, 0xC) = 2;
            break;
        }
        y_distance = D_80083784 - position[1];
        if (y_distance < 0) {
            y_distance = -y_distance;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (y_distance > 0x200000 || next_x > 0x43FFFFF || (U16(state, 0x10) & 4)) {
            break;
        }
        type_index = U16(owner, 0x16) - 3;
        if ((u32)type_index < 3) {
            SD_Call(0x513);
            S32(state, 4) = 0x180000;
            S16(state, 0xC) = 3;
            U16(state, 0x10) |= 4;
            U16(object, 0x54)++;
            U16(PTR(object, 0), 0x14) += 2;
            if (S16(object, 0x54) == 10) {
                U16(PTR(object, 0), 0x14) += 10;
            }
            break;
        }
        if ((u32)type_index >= 7) {
            break;
        }

        SD_Call(0x510);
        remaining = 1;
        U16(state, 0x10) |= 4;
        U16(PTR(object, 0), 0x14)++;
        do {
            effect = func_8003FC64(0x136);
            if (effect != 0) {
                PTR(effect, 0x10) = D_80026748;
                func_8004491C(effect, D_80045340);
                effect_position = PTR(effect, 8);
                effect_sprite = PTR(effect, 0xC);
                S32(effect_position, 0) = position[0];
                S32(effect_position, 4) = position[1];
                S32(effect_position, 8) = position[2];
                effect_state = effect + 0x20;
                S32(effect_state, 4) = S32(state, 4);
                ASM_KEEP(effect_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                PTR(effect, 0x20) = object;
                S16(effect_sprite, 0x1E) = 0x1000;
                S16(effect_sprite, 0x1C) = 0x1000;
                if (remaining != 0) {
                    PTR(effect_sprite, 8) = D_800F795C;
                    S32(effect_position, 0x10) = 0x80000;
                } else {
                    PTR(effect_sprite, 8) = D_800F7950;
                    S32(effect_position, 0x10) = 0xFFF80000;
                }
                U8(effect_sprite, 4) = 0;
                U8(effect_sprite, 5) = 0;
                S32(effect_sprite, 0xC) = 0x00808080;
            }
            remaining--;
        } while (remaining >= 0);
        S16(state, 0xC) = 0xFF;
        break;

    case 2:
        remaining = 7;
        do {
            x_jitter = (rand() & 0xFF) - 0x80;
            particle_x = *position + (x_jitter << 14);
            func_800252B8(0, particle_x, position[1] + 0x80000,
                ((rand() % 80) << 16) + 0xFFB00000);
            remaining--;
        } while (remaining >= 0);
        goto common_countdown;

    case 3:
        U16(object, 0x58) |= 2;
        rebound_x = *position + S32(state, 4);
        *position = rebound_x;
        if (rebound_x > 0x55FFFFF) {
            S16(state, 0xE) = 5;
            SD_Call(0x50C);
            S16(state, 0xC) = 4;
        }
        break;

    case 4:
        remaining = 7;
        U16(object, 0x58) |= 2;
        do {
            burst_x = (((rand() & 0xFF) - 0x80) << 14) + 0x5600000;
            burst_velocity = ((rand() & 0x3F) << 16) | 0xFFC00000;
            func_800252B8(0, burst_x, position[1] + 0x80000, burst_velocity);
            remaining--;
        } while (remaining >= 0);
common_countdown:
        U16(state, 0xE)--;
        if (S16(state, 0xE) <= 0) {
            S16(state, 0xC) = 0xFF;
        }
        break;

    case 0xFF:
        U16(object, 0x58) &= 0xFFFE;
        U16(state, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}
