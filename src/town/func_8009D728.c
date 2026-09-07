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
extern void func_8009AF4C(void) __attribute__((noreturn));
extern void func_8009AF5C(void) __attribute__((noreturn));

extern u8 D_80083160[];
extern u8 D_800D0190[];
extern u8 D_800D0088[];
extern s32 D_800D0620;
extern u8 D_8009B0EC[];
extern u8 D_8009B014[];

void func_8009AE88(Entity *arg0, s32 arg1, s32 arg2) {
    Entity *entity = arg0;
    GlobalState *state = (GlobalState *)D_80083160;
    register s32 dead ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 value ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    if (state->flags & 0x40) {
        Entity *call_a1 = entity;
        ASM_KEEP(call_a1);   /* MATCH pin: keeps a statement from moving across a call/branch */
        {
            void *call_a0 = D_800D0190;
            ASM_KEEP(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
            entity->unkA = 4;
            func_80094984(call_a0, call_a1);
        }
#ifdef NON_MATCHING
        dead = (s32)D_8009B0EC;
#else
        dead = (s32)0x800A0000;
        ASM_KEEP(dead);   /* MATCH pin: load-bearing for the whole function shape */
        dead += -0x4F14;
#endif
        ASM_TAILSLOT_PIN(dead);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8009AF5C();
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    if ((state->flags & 0x1000) && ((value = D_800D0620) >= 0)) {
        register void *tail_a0 ASM_REG("$4") = D_800D0088;   /* MATCH pin: keeps a statement from moving across a call/branch */
        register Entity *tail_a1 ASM_REG("$5") = entity;   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(tail_a0);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_KEEP(tail_a1);   /* MATCH pin: retail delay-slot contents depend on it */
        value--;
        D_800D0620 = value;
        value = 0x800;
        entity->unk10 = value;
        dead = 4;
        ASM_TAILSLOT_PIN(dead);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8009AF4C();
    }

    if ((state->flags & 0x4000) && ((value = D_800D0620) <= 0)) {
        D_800D0620 = value + 1;
        entity->unk10 = 0;
        entity->unkA = 4;
        func_80094984(D_800D0088, entity);
        entity->unk4 = D_8009B014;
    }
}
