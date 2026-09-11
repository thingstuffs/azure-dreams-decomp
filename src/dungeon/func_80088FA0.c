#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    s16 fieldA;
} D_80083460_t;

extern void func_80048A44(void *a0, u8 a1, s32 a2, s32 a3);
extern void func_80099F04(s32 a0);
extern void func_80099F70(s32 a0);
extern s16 func_8009AF18(s16 a0, void *a1, void *a2, s32 a3);
extern void func_8009F644(void *a0, s32 a1, s16 a2, s32 a3);
extern void func_800A56E0(s32 a0);

extern u16 D_80013714[5];
extern s32 D_80081484[3];
extern s16 D_80083228[5];
extern D_80083460_t D_80083460;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];
extern u8 D_800DCFD0[8];
extern u8 D_800DD048[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0C8[8];
extern s32 D_800E3540[3];

/* Advance the entity action through its motion, animation, and linked-child effects. */
void func_8008E700(u8 *action, u8 *motion, u8 *sprite, u8 *entity) {
    s16 effect_id;
    s32 entity_flags;
    s32 direction;
    u16 ticks;
    s32 phase;
    u8 *child;

    phase = action[0x9B];
    if (phase == 1) {
        goto update;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto start;
        }
        return;
    }
    if (phase == 2) {
        goto finish;
    }
    return;

start:
    if (*(u16 *)(sprite + 0x14) & 0x6000) {
        u8 *anim_sprite;

        *(s32 *)(motion + 0x14) = 0xFFEA0000;
        if (*(s32 *)(entity + 0x1C) & 0x100000) {
            *(u8 **)(sprite + 0x2C) = D_800DD0C8;
        } else {
            *(u8 **)(sprite + 0x2C) = D_800DD048;
        }
        anim_sprite = sprite;
        direction = ((D_80083228[0] + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7;
        func_80048A44(anim_sprite, (*(u8 **)(anim_sprite + 0x2C))[direction], 0, 1);
        action[0x9B]++;
    }
    return;

update:
    ticks = *(u16 *)(action + 0x96) + 1;
    *(u16 *)(action + 0x96) = ticks;
    if ((*(u16 *)(action + 0xA2) & 0x10) && ((s16)ticks >= 4)) {
        u8 *anim_sprite;
        u8 *animations;
        s32 heading;
        register s32 direction ASM_REG("$2");

        *(s32 *)(motion + 0x14) = 0;
        if (*(s32 *)(entity + 0x1C) & 0x100000) {
            *(u8 **)(action + 0x8C) = D_8008EAC8;
            goto advance_phase;
        }
        anim_sprite = sprite;
        animations = D_800DD060;
        *(u8 **)(anim_sprite + 0x2C) = animations;
        direction = D_80083228[0];
        heading = *(s16 *)(entity + 0x2A);
        direction = ((direction + heading + 0x100) >> 9) & 7;
        func_80048A44(anim_sprite, animations[direction], 0, 1);
    advance_phase:
        action[0x9B]++;
        return;
    }

    if ((*(s32 *)(entity + 0x1C) & 0x300000) == 0x100000) {
        ASM_SCHED_BARRIER();
        if (!(D_80013714[0] & 1)) {
            effect_id = func_8009AF18(*(s16 *)(entity + 0x2A), motion, sprite, 8);
            if ((effect_id << 16) != 0) {
                child = *(u8 **)(action + 0x124);
                *(s32 *)(child + 0x1C) |= 0x200000;
                *(s32 *)(entity + 0x1C) |= 0x200000;
                *(s16 *)(*(u8 **)(action + 0x124) + 0x8A) = effect_id;
                *(u8 *)(*(u8 **)(action + 0x124) + 0x84) = 0x78;
                *(u8 *)(*(u8 **)(action + 0x124) + 0x85) = 2;
                func_8009F644(entity, 0x30, *(s16 *)(action + 0x96), 0);

                {
                    register s32 clear_mask ASM_REG("$3");
                    u8 *anim_sprite;
                    u8 *animations;
                    s32 anim_mode;
                    s32 heading;
                    s32 saved_state;
                    register s32 state_value ASM_REG("$2");
                    D_80083460_t *dungeon_state;

                    clear_mask = 0xFFEFFFFF;
                    anim_sprite = sprite;
                    ASM_KEEP(anim_sprite);
                    state_value = *(s32 *)(entity + 0x1C);
                    saved_state = D_80081484[0];
                    do {
                        anim_mode = 5;
                    } while (0);
                    ASM_KEEP(anim_mode);
                    do {
                        D_80081484[0] = 0;
                    } while (0);
#ifndef NON_MATCHING
                    animations = (u8 *)0x800E0000;
                    ASM_KEEP_NV(animations);
#else
                    animations = D_800DCFD0;
#endif
                    state_value &= clear_mask;
                    dungeon_state = &D_80083460;
                    *(s32 *)(entity + 0x1C) = state_value;
                    state_value = *(u16 *)&dungeon_state->fieldA;
#ifndef NON_MATCHING
                    do {
                        animations -= 0x3030;
                    } while (0);
#endif
                    state_value++;
                    *(u16 *)&dungeon_state->fieldA = state_value;
                    *(u8 **)(anim_sprite + 0x2C) = animations;
                    state_value = D_80083228[0];
                    heading = *(s16 *)(entity + 0x2A);
                    D_800E3540[0] = saved_state;
                    state_value = ((state_value + heading + 0x100) >> 9) & 7;
#ifndef NON_MATCHING
                    state_value += (s32)animations;
                    func_80048A44(anim_sprite, *(u8 *)state_value, anim_mode, 1);
#else
                    func_80048A44(anim_sprite, animations[state_value], anim_mode, 1);
#endif
                }
                func_800A56E0(0x512);
                return;
            }
        }
    }
    return;

finish:
    if ((*(u16 *)(sprite + 0x14) & 0x6000) &&
        (D_80083460.fieldA == 0)) {
        entity_flags = *(s32 *)(entity + 0x1C);
        if (entity_flags & 0x200000) {
            *(s32 *)(entity + 0x1C) = entity_flags & 0xFFDFFFFF;
            D_80083460.field2 |= 0x412;
            func_80099F70(*(s32 *)(entity + 0x5C));
            func_80099F04(*(s32 *)(entity + 0x5C));
        }
        *(s32 **)(action + 0x8C) = &D_8008ACDC;
    }
}
