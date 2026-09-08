#include "common.h"

typedef struct {
    u8 pad0[0x12];
    s16 state;
    u8 pad14[6];
    u16 timer;
} Entity;

typedef struct {
    u8 pad0[8];
    s32 y;
} Position;

extern u8 *D_80174704[];
extern u8 *D_80174CC8[];
extern u32 D_800814A0[];
extern void func_800A56E0(s32, Position *, u16, u8 *);

/* Lowers the entity in two timed stages, then flags completion and clears the active pointer. */
void func_8016E300(Entity *entity, Position *pos)
{
    u8 *context_base = D_80174704[0];
    s32 state = entity->state;
    register s32 expected_state ASM_REG("$2");
    u16 initial_state;
    u8 *context;

    initial_state = entity->state;
    context = context_base + 0x20;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        expected_state = 0x11;
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    if (*(s16 *)(context + 0xAC) == expected_state) {
        entity->state = initial_state + 1;
        entity->timer = 0;
        return;
    }
    goto epilogue;

state_1:
    pos->y += 0xFFF80000;
    entity->timer++;
    if ((s16)entity->timer >= 11) {
        entity->timer = 0;
        entity->state++;
        func_800A56E0(0x516, pos, initial_state, context);
        return;
    }
    goto epilogue;

state_2:
    pos->y += 0xFFFE0000;
    entity->timer++;
    if ((s16)entity->timer >= 20) {
        u8 *active_context = D_80174CC8[0] + 0x20;
        *(u16 *)(active_context - 2) |= 0x8000;
        D_80174CC8[0] = 0;
        D_800814A0[0] |= 0x8000;
    }

epilogue:
    return;
}
