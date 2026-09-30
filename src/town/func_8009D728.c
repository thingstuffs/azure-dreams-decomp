#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s32 unk0;
    void *unk4;
    u16 unk8;
    s16 unkA;
    u8 padC[4];
    s16 unk10;
} Entity;

extern void func_80094984(void *arg0, Entity *arg1);

extern u8 D_800D0190[];
extern u8 D_800D0088[];
extern s32 D_800D0620;
extern u8 D_8009B0EC[];
extern u8 D_8009B014[];


/* Update the entity state and handler from global flags and the signed counter. */
void func_8009AE88(Entity *entity, s32 unused_1, s32 unused_2) {
    GameWork *state = &gameWork;
    s32 adjustment;

    if (((u32)state->unk_010) & 0x40) {
        entity->unkA = 4;
        func_80094984(D_800D0190, entity);
        entity->unk4 = D_8009B0EC;
    } else if ((((u32)state->unk_010) & 0x1000) && ((adjustment = D_800D0620) >= 0)) {
        D_800D0620 = adjustment - 1;
        entity->unk10 = 0x800;
        entity->unkA = 4;
        func_80094984(D_800D0088, entity);
        entity->unk4 = D_8009B014;
    } else if ((((u32)state->unk_010) & 0x4000) && ((adjustment = D_800D0620) <= 0)) {
        D_800D0620 = adjustment + 1;
        entity->unk10 = 0;
        entity->unkA = 4;
        func_80094984(D_800D0088, entity);
        entity->unk4 = D_8009B014;
    }
}
