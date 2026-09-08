#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void func_80048A44(void *a0, s16 a1, s16 a2, s32 a3);
extern void *func_800A8608(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern void func_800A56E0(s32 a0);

extern s16 D_80083228;
extern u8 D_800DD0B8[8];
extern s32 D_8008D470;
extern s32 D_8008ACDC;

/* Create an effect at the target and initialize its state and sound. */
void func_8008D7D0(u8 *actor, s32 effect_arg, u8 *target, u8 *source) {
    u16 flags;
    s32 direction;
    u8 *effect;
    u8 *transform;
    u8 *effect_state;
    s32 sound_id;

    *(s8 *)(actor + 0x9A) = 0x23;
    *(s8 *)(actor + 0x9B) = 0;
    *(void **)(actor + 0x8C) = NULL;

    flags = *(u16 *)(actor + 0xA2);
    *(u16 *)(actor + 0xA2) = flags & 0xFF7F;

    *(u8 **)(target + 0x2C) = &D_800DD0B8[0];

    direction = ((D_80083228 + *(s16 *)(source + 0x2A) + 0x100) >> 9) & 7;
    func_80048A44(target, D_800DD0B8[direction], 0, 1);

    effect = func_800A8608(actor - 0x20, *(void **)(actor + 0xBC), 0, 0, 0);
    *(void **)(actor + 0x124) = effect;
    if (effect != NULL) {
        *(void **)(effect + 0x10) = &D_8008D470;
        transform = *(u8 **)(effect + 8);
        *(s16 *)(transform + 2) = (s16)((target[0x24] << 6) + 0x20);
        *(s16 *)(transform + 6) = (s16)((target[0x25] << 6) + 0x20);
        effect_state = effect + 0x20;
        *(u16 *)(transform + 0xA) = *(u16 *)(source + 0x88);
        *(s16 *)(effect_state + 0xAA) = 1;
        *(s16 *)(effect_state + 0xA8) = 0x1E;
        *(u8 **)(effect_state + 0x90) = target;
        *(s32 *)(effect_state + 0x8C) = effect_arg;
        *(u8 **)(effect_state + 0x9C) = effect + 0xB8;

        sound_id = 0x505;
        if (*(u8 *)(*(u8 **)(actor + 0xBC) + 1) == 0xE) {
            sound_id = 0x516;
        }
        func_800A56E0(sound_id);

        *(s16 *)(effect_state + 0xAE) = (s16)(*(u16 *)(source + 0x46) == 1);
        *(u16 *)(actor + 0x46) = 0;
        return;
    }
    *(void **)(actor + 0x8C) = &D_8008ACDC;
}
