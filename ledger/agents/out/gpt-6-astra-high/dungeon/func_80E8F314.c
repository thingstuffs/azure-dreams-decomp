#include "common.h"

typedef struct {
    u8 pad00[0x8C];
    s32 unk8C;
    u8 pad90[0x0A];
    s8 unk9A;
    s8 unk9B;
} Entity;

typedef struct {
    u8 pad00[0x2C];
    u8 *unk2C;
} Object;

typedef struct {
    u8 pad00[0x2A];
    s16 unk2A;
    u8 pad2C[0x41];
    u8 unk6D;
    u8 pad6E[3];
    u8 unk71;
} State;

extern s32 func_800A2BDC(State *state);
extern void func_80047784(Object *object, u8 value, s32 arg2);
extern s16 D_80083228[];
extern u16 D_80083460[];
extern u8 D_80174F08[];

/* Clears the state flag and, when allowed, resets the entity and selects a directional object value. */
void func_80174B14(Entity *entity, s32 unused, Object *object, State *state) {
    u16 *flags = D_80083460;

    state->unk71 &= 0x7F;
    if (!(flags[1] & 0x2000) && ((func_800A2BDC(state) << 16) == 0)) {
        entity->unk9A = 0x18;
        entity->unk8C = 0;
        entity->unk9B = 0;
        object->unk2C = D_80174F08;
        func_80047784(object,
                      D_80174F08[((D_80083228[0] + state->unk2A + 0x100) >> 9) & 7],
                      0);
        state->unk6D--;
        flags[5]++;
    }
}
