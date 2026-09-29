#include "common.h"
#include "shared/object_flags.h"

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
extern void func_800A56E0(s32, Position *, u16, u8 *);

/* Lowers the entity in two timed stages, then flags completion and clears the active pointer. */
void func_8016E300(Entity *entity, Position *pos)
{
    u8 *context_base = D_80174704[0];
    s32 state = entity->state;
    s32 expected_state;
    u16 initial_state;
    u8 *context;

    initial_state = entity->state;
    context = context_base + 0x20;

    switch (state) {
    case 0:
        if (*(s16 *)(context + 0xAC) == 0x11) {
            entity->state = initial_state + 1;
            entity->timer = 0;
            return;
        }
        return;
    case 1:
        pos->y += 0xFFF80000;
        entity->timer++;
        if ((s16)entity->timer >= 11) {
            entity->timer = 0;
            entity->state++;
            func_800A56E0(0x516, pos, initial_state, context);
            return;
        }
        return;
    case 2:
        pos->y += 0xFFFE0000;
        entity->timer++;
        if ((s16)entity->timer >= 20) {
            u8 *active_context = D_80174CC8[0] + 0x20;
            *(u16 *)(active_context - 2) |= 0x8000;
            D_80174CC8[0] = 0;
            objectFlagBlock.flags |= 0x8000;
        }

        return;
    }
}
