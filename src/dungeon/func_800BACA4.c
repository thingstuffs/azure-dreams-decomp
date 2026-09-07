#include "common.h"

typedef struct {
    u8 pad0[0x8D0];
    void *nextPrim;
} RenderState;

typedef struct {
    u8 pad0[0x3160];
    RenderState *state;
} DungeonGlobals;

typedef struct {
    u8 pad0[4];
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
} Primitive;

typedef struct {
    u8 pad0[0x4A];
    s16 phase;
    u16 counter;
    u8 pad50[4];
    s16 count;
    u8 pad54[0x14];
    u8 *handle;
} DungeonObject;

typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    s32 field14;
} MotionState;

typedef struct {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
} EffectState;

typedef struct {
    s32 field18;
    s32 field1C;
    s16 field20;
    s16 field22;
} StackData;

extern RenderState *D_80083160;
extern u8 D_801C9E40[16];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern void *D_800E3D7C[];
extern u8 D_800DD0F8[];
extern s16 D_80083228[5];
extern s16 D_800814E8;
extern u8 D_80083120[];
extern u16 D_80082E76;

extern void func_8006658C();
extern void func_800667BC();
extern void func_80067E2C();
extern s32 func_80069EF8();
extern void func_80091934();
extern s32 func_8003F794();
extern void func_80048A44();
extern void func_800945E8();
extern void func_800948BC();
extern void func_800B8FC8();
extern void func_80041094();

void func_800C0404(DungeonObject *obj, MotionState *motion, EffectState *effect) {
    StackData stack;
    s32 useAlt;
    u32 stateDiff;
    RenderState **stateSlot;
    RenderState *state;
    RenderState *callState;
    Primitive *prim;
    u8 *list;
    s32 i;
    register s32 firstConst ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register Primitive *firstCallArg ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

    firstConst = 0x01800340;
    stack.field18 = firstConst;
    stack.field1C = 0x00400040;
    stateSlot = &D_80083160;
    state = *stateSlot;
    do {
        prim = (Primitive *)state->nextPrim;
    } while (0);
    list = (u8 *)state + 0x8B0;
    firstCallArg = prim;
    state->nextPrim = (u8 *)prim + 0xC;
    stateDiff = (u32)state ^ (u32)D_801C9E40;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
    callState = *(RenderState *volatile *)&D_80083160;
    useAlt = stateDiff != 0;
    func_80067E2C(firstCallArg, callState, state);
    func_8006658C(list, prim);
    ASM_USE_NV(list);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    if (obj->count > 0) {
        i = 0;
        do {
            RenderState *iterState;
            iterState = *stateSlot;
            prim = (Primitive *)iterState->nextPrim;
            iterState->nextPrim = (u8 *)prim + 0x10;
            prim->fieldC = (func_80069EF8() & 0x3F) + 0x340;
            prim->field8 = prim->fieldC;
            {
                s32 r = func_80069EF8() & 0x3F;
                s32 edge;
                prim->fieldA = 0x180 - r;
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
                edge = 0x1BF - r;
                prim->fieldE = edge;
                if (useAlt) {
                    edge -= 0xE0;
                    prim->fieldE = edge;
                    prim->fieldA -= 0xE0;
                }
                ASM_USE_NV(useAlt);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            }
            prim->field4 = 0;
            func_800667BC(prim);
            func_8006658C(list, prim);
            i += 1;
        } while (i < obj->count);
    }

    if (obj->count < 0x60) {
        obj->count = (u16)obj->count + 1;
    }

    {
        RenderState *postState;
        postState = *stateSlot;
        prim = (Primitive *)postState->nextPrim;
        postState->nextPrim = (u8 *)prim + 0xC;
        func_80067E2C(prim, &stack.field18);
        func_8006658C(list, prim);
    }
    stack.field20 = 0x360;
    stack.field22 = 0x1B8;
    func_800B8FC8(obj->handle, &stack.field18, &stack.field20, 1, 0);

    {
        u16 counter = obj->counter + 1;
        i = (s16)obj->phase;
        obj->counter = counter;
        if (i == 0) {
            if ((s16)counter >= 0x21) {
                if (obj->handle[0x13] == 0) {
                    u8 *dungeonState;
                    func_80091934(obj->handle, D_80083780, D_80082E80, 0);
                    ((u8 *)D_800E3D7C[0])[0x9B] = 0x11;
                    dungeonState = *(u8 *volatile *)D_800E3D7C;
                    *(u8 * volatile *)(D_80082E80 + 0x2C) = D_800DD0F8;
                    func_80048A44(
                        D_80082E80,
                        D_800DD0F8[((s32)(*D_80083228 + *(s16 *)(dungeonState + 0x2A)) + 0x100 >> 9) & 7],
                        1,
                        1);
                }
                obj->phase = (u16)obj->phase + 1;
            } else {
                return;
            }
        } else if (i == 1) {
            MotionState *parent;
            effect->fieldC = effect->fieldC - (effect->fieldC >> 3);
            effect->fieldD = effect->fieldD - (effect->fieldD >> 3);
            effect->fieldE = effect->fieldE - (effect->fieldE >> 3);
            effect->field1C = effect->field1C + ((0x400 - effect->field1C) >> 2);
            parent = *(MotionState **)((u8 *)obj - 0x18);
            motion->field8 = motion->field8 + motion->field14;
            parent->field8 = motion->field8;
            motion->field14 = motion->field14 + 0xFFFC0000;
            if (obj->handle[0x13] == 0 &&
                (*(u16 *)(*(u8 **)((u8 *)D_800E3D7C[0] - 0x14) + 0x14) & 0x6000)) {
                s16 value = func_8003F794(6, 0x20);
                u8 *table = D_80083120;
                s16 *slot;
                void *callArg;
                D_800814E8 = value;
                slot = (s16 *)(table + (((s32)(value << 16)) >> 0xD) + 6);
                callArg = D_800E3D7C[0];
                *slot = i;
                func_800945E8(callArg);
                func_800948BC();
                D_80082E76 = 0x8000;
                func_80041094(6, 0, 0, 0, 0x8000);
                obj->phase = (u16)obj->phase + 1;
            }
        }
    }
}
