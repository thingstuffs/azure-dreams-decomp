#include "common.h"

typedef struct {
    s32 unk0;
    void *unk4;
    u16 unk8;
    s16 unkA;
    u8 padC[4];
    s16 unk10;
} Entity;

typedef struct {
    u8 pad0[0x10];
    u32 flags;
} GlobalState;

extern void func_80094984(void *arg0, Entity *arg1);

extern u8 D_80083160[];
extern u8 D_800D0190[];
extern u8 D_800D0088[];
extern s32 D_800D0620;
extern u8 D_8009B0EC[];
extern u8 D_8009B014[];

/* Update the entity state and handler from global flags and the signed counter. */
void func_8009AE88(Entity *input_entity, s32 unused_1, s32 unused_2) {
    Entity *entity = input_entity;
    GlobalState *state = (GlobalState *)D_80083160;
    register s32 state_or_handler ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 adjustment ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (state->flags & 0x40) {
        Entity *call_entity = entity;
        ASM_KEEP(call_entity);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            void *call_data = D_800D0190;
            ASM_KEEP(call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            entity->unkA = 4;
            func_80094984(call_data, call_entity);
        }
#ifdef NON_MATCHING
        state_or_handler = (s32)D_8009B0EC;
#else
        state_or_handler = (s32)&D_8009B0EC;
#endif
    } else {
        register void *tail_data ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        Entity *tail_entity;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        if ((state->flags & 0x1000) && ((adjustment = D_800D0620) >= 0)) {
            tail_data = D_800D0088;
            tail_entity = entity;

            adjustment--;
            D_800D0620 = adjustment;
            adjustment = 0x800;
            entity->unk10 = adjustment;
            state_or_handler = 4;
        } else if ((state->flags & 0x4000) && ((adjustment = D_800D0620) <= 0)) {
            tail_data = D_800D0088;
            tail_entity = entity;
            adjustment++;
            D_800D0620 = adjustment;
            state_or_handler = 4;
            entity->unk10 = 0;
        } else {
            return;
        }
        entity->unkA = state_or_handler;
        func_80094984(tail_data, tail_entity);
        state_or_handler = (s32)D_8009B014;
    }
    entity->unk4 = (void *)state_or_handler;
}
