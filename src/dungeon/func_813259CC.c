#include "common.h"
#include "shared/dungeon_status.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct S_func_813259CC_0 {
    u8 pad_00[0x8C];
    s32 *unk_8C;
} S_func_813259CC_0;

typedef struct S_func_813259CC_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_func_813259CC_1;

typedef struct {
    u8 pad[0xA];
    s16 unk0A;
} State_D_80083460;

extern s32 D_8016B778;

/* Set the object state pointer, decrement the shared count, and clear the target flag. */
void func_8016D1CC(S_func_813259CC_0 *object, void *unused_1, void *unused_2, S_func_813259CC_1 *target) {
    State_D_80083460 *state;

    object->unk_8C = &D_8016B778;
    state = ((State_D_80083460 *)&dungeonStatus);
    state->unk0A--;
    target->unk_46 = (u16)(target->unk_46 & 0x7FFF);
}
