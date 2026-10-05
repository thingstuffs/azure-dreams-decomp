#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad_00[0x12];
    s16 state;
    u8 pad_14[4];
    s16 timer;
    u8 pad_1A[2];
    s16 phase;
} Entity;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[2];
    u16 z;
} Actor;

typedef struct {
    s16 values[8];
} __attribute__((packed)) PhaseHeights;

extern PhaseHeights D_80164A54;
extern u8 *D_80175D50;
extern u16 D_800DCE60[4];
extern s16 D_801760E0[4];
extern s16 D_801760E8[4];

extern void func_8004D294(void *, void *, s32);
extern void func_8004D7A8(s32);
extern s16 func_8016F4FC(void *);

/* Update camera focus and height through timed entity states and phases. */
void func_801717A8(Entity *entity) {
    PhaseHeights heights = D_80164A54;
    Actor *actor = *(Actor **)(D_80175D50 + 8);
    s16 phase_slot;
    s16 height_slot;
    s32 state = entity->state;
    void *focus_arg;
    void *offset_arg;
    s32 transition_ticks;
    u16 previous_state;

    switch (state) {
    case 0:
    {
        u8 *globals;

        entity->timer = 0;
        entity->phase = 2;
        entity->state++;
        D_801760E0[0] = D_800DCE60[0];
        D_801760E0[1] = D_800DCE60[1];
        D_801760E0[2] = D_800DCE60[2] - 0x600;
        D_801760E8[0] = actor->x;
        D_801760E8[1] = actor->y - 0x100;
        D_801760E8[2] = actor->z;
        globals = ((u8 *)(&gameWork));
        *(s32 *)(globals + 0x154) = 0;
        *(s32 *)(globals + 0xCC) = 0;
        func_8004D7A8(1);
        func_8004D7A8(0);
        func_8004D294(D_801760E8, D_801760E0, 0xA);
        return;
    }

    case 1:
        entity->timer++;
        if (entity->timer < 0x28) {
            return;
        } else {
            focus_arg = D_801760E8;
            offset_arg = D_801760E0;
            previous_state = entity->state;
            transition_ticks = 0x14;
            entity->timer = 0;
            entity->state = previous_state + 1;
            func_8004D294(focus_arg, offset_arg, transition_ticks);
            return;
        }

    case 2:
        entity->timer++;
        if (entity->timer < 0x28) {
            return;
        }
        focus_arg = 0;
        offset_arg = D_800DCE60;
        previous_state = entity->state;
        transition_ticks = 0xA;

        entity->timer = 0;
        entity->state = previous_state + 1;
        func_8004D294(focus_arg, offset_arg, transition_ticks);
        return;

    case 4:
    {
        s32 y_sum;
        u8 *globals;

        entity->timer = 0;
        entity->state++;
        phase_slot = func_8016F4FC(actor);
        height_slot = phase_slot + 3;
        D_801760E0[0] = D_800DCE60[0];
        D_801760E0[1] = D_800DCE60[1];
        if (height_slot >= 8) {
            height_slot = phase_slot - 5;
        }
        D_801760E0[2] = heights.values[height_slot] * 0x200;
        D_801760E8[0] = ((s32)(actor->x + D_80083780.x.w.i)) / 2;
        y_sum = actor->y + D_80083780.y.w.i;
        D_801760E8[1] = y_sum / 2;
        D_801760E8[2] = actor->z;
        globals = ((u8 *)(&gameWork));
        *(s32 *)(globals + 0x154) = 0;
        *(s32 *)(globals + 0xCC) = 0;
        func_8004D7A8(1);
        func_8004D7A8(0);
        func_8004D294(D_801760E8, D_801760E0, 0xA);
        return;
    }

    case 6:
    {
        s32 y_sum;
        u8 *globals;

        entity->timer = 0;
        entity->state++;
        phase_slot = func_8016F4FC(actor);
        height_slot = phase_slot + 2;
        D_801760E0[0] = D_800DCE60[0];
        D_801760E0[1] = D_800DCE60[1];
        if (height_slot >= 8) {
            height_slot = phase_slot - 6;
        }
        D_801760E0[2] = heights.values[height_slot] * 0x200;
        D_801760E8[0] = ((s32)(actor->x + D_80083780.x.w.i)) / 2;
        y_sum = actor->y + D_80083780.y.w.i;
        D_801760E8[1] = y_sum / 2;
        D_801760E8[2] = actor->z;
        globals = ((u8 *)(&gameWork));
        *(s32 *)(globals + 0x154) = 0;
        *(s32 *)(globals + 0xCC) = 0;
        func_8004D7A8(1);
        func_8004D7A8(0);
        func_8004D294(D_801760E8, D_801760E0, 2);
        break;
    }

    case 20:
    {
        s32 y_sum;
        u8 *globals;

        if ((entity->timer & 0xF) == 0) {
            height_slot = func_8016F4FC(actor);
            D_801760E0[0] = D_800DCE60[0];
            D_801760E0[1] = D_800DCE60[1];
            entity->phase++;
            height_slot += entity->phase;
            if (height_slot >= 8) {
                height_slot -= 8;
            }
            D_801760E0[2] = heights.values[height_slot] * 0x200;
            D_801760E8[0] = ((s32)(actor->x + D_80083780.x.w.i)) / 2;
            y_sum = actor->y + D_80083780.y.w.i;
            D_801760E8[1] = y_sum / 2;
            D_801760E8[2] = actor->z;
            globals = ((u8 *)(&gameWork));
            *(s32 *)(globals + 0x154) = 0;
            *(s32 *)(globals + 0xCC) = 0;
            func_8004D7A8(1);
            func_8004D7A8(0);
            func_8004D294(D_801760E8, D_801760E0, 4);
        }
    }

        entity->timer++;
        if (entity->timer >= 0x79) {
            entity->timer = 0;
            entity->phase = 0;
            entity->state++;
        }

    case 21:
    default:
        break;
    }
}
