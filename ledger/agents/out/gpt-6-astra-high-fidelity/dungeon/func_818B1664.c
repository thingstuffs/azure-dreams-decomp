#include "common.h"

typedef union FixedWord {
    s32 word;
    struct {
        u16 lo;
        s16 hi;
    } half;
} FixedWord;

typedef struct Motion {
    FixedWord x;
    FixedWord y;
    FixedWord z;
    FixedWord dx;
    FixedWord dy;
    FixedWord dz;
} Motion;

typedef struct WorkFrame {
    Motion target;
    s16 distance[3];
} WorkFrame;

typedef struct TargetInfo {
    u8 pad0[8];
    void *map;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 tileX;
    u8 tileY;
} TargetInfo;

typedef struct EntityHeader {
    u8 pad0[8];
    Motion *position;
    TargetInfo *info;
} EntityHeader;

typedef struct Child {
    u8 pad0[0x1C];
    u32 flags;
} Child;

typedef struct Entity {
    u8 pad0[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    Child *child;
    u8 pad64[0x24];
    s16 height;
} Entity;

typedef struct EffectInner {
    u8 pad0[0xC];
    s32 value;
} EffectInner;

typedef struct Effect {
    u8 pad0[0xC];
    EffectInner *inner;
    u8 pad10[0xE];
    u16 flags;
} Effect;

typedef struct Resource {
    u16 flags;
} Resource;

typedef struct State {
    Entity *entity;
    Resource *resource;
    u8 pad8;
    u8 id;
    s16 state;
    u16 flags;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field14;
    s16 timer2;
    s16 angleStep;
    s16 angles[8];
    s16 pad2A;
    Effect *effects[10];
} State;

typedef struct DrawInfo {
    u8 pad0[0xC];
    s32 color;
} DrawInfo;

typedef struct LargeScalar {
    s32 value;
    s32 pad[2];
} LargeScalar;

extern void *D_80024028[10];
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LargeScalar D_800814A0;
extern s32 D_8008346C[3];

extern void func_800240EC(u8 *, u8 *, DrawInfo *);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern void func_80024DF4(void);
extern s32 func_800A44E0(s32, s32, s32, s32);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_800241F8(State *, Motion *);
extern void func_800A56E0(s32);
extern Effect *func_8002443C(State *, Motion *, s16, s16);
extern void func_80024050(void *, u8);

#ifdef NON_MATCHING
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

void func_80024E64(State *arg0, Motion *arg1, DrawInfo *arg2)
{
    WorkFrame work;
    volatile s16 savedY;
    State *state = arg0;
    Motion *motion = arg1;
    register DrawInfo *draw ASM_REG("$17") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    Entity *entity;
    register EntityHeader *header ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 dispatchState;
    s32 directionValue;
    register s32 colorValue ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 sourceZ;
    TargetInfo *callInfo;
    Motion *source;
    register Motion *childPosition ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *angleCursorInit ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *angleCursorClear;
    u8 *angleCursorBuild;
    u8 *effectCursorClear;
    register Effect **effectCursorCreate ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Effect **effectCursorGrow;
    Effect **effectCursorShrink;
    register Effect **effectCursorCleanup ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 i;
    register s32 childDelta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 motionCoord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 nextState;
    s32 angleValue;
    s32 effectAngle;
    s32 effectStep;
    s32 value;
    s32 value2;
    Motion *targetPtr;
    s16 *targetCursor;
    s16 *distanceCursor;
    register s32 targetX ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 targetY ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 targetZ;
    u16 angleRaw;
    s32 angleSigned;
    s32 angleAdjusted;
    u16 zResult;
    register s16 *tableBase ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 outIdx;
    s32 offsetXY;
    register s32 tempT0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 tableOffset;
    s32 updateOffset;
    s16 *tableXEntry;
    s16 *tableYEntry;
    u16 *updateXEntry;
    register u16 *updateYEntry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 loopHeight ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 nextX ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 nextY;
    u32 deadPage;
    register s32 accumX ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 accumY ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 gridX;
    s16 gridY;
    s32 finalX;

    static void *const keepalive[] = {
        &&case_0, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9
    };

    i = 7;
    angleCursorInit = (u8 *)state + 14;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    entity = state->entity;
    do {
        angleRaw = *(u16 *)(angleCursorInit + 26) + (u16)state->angleStep;
        angleSigned = (s16)angleRaw;
        angleAdjusted = angleSigned;
        *(u16 *)(angleCursorInit + 26) = angleRaw;
        if (angleSigned < 0) {
            angleAdjusted = angleSigned + 127;
        }
        angleRaw = angleSigned - ((angleAdjusted >> 7) << 7);
        *(u16 *)(angleCursorInit + 26) = angleRaw;
        i--;
        angleCursorInit -= 2;
    } while (i >= 0);
    {
        register u16 counter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        counter = (u16)state->timer;
        counter++;
        state->timer = counter;
        counter = (u16)state->timer2;
        dispatchState = state->state;
        counter++;
        state->timer2 = counter;
    }

    if ((u32)dispatchState >= 10) {
        goto end;
    }
    goto *D_80024028[dispatchState];

case_0:
    state->timer = 0;
    state->timer2 = 0;
    state->angleStep = 4;
    state->state++;
    i = 7;
    angleCursorClear = (u8 *)state + 14;
    do {
        *(s16 *)(angleCursorClear + 26) = 0;
        i--;
        angleCursorClear -= 2;
    } while (i >= 0);
    i = 9;
    effectCursorClear = (u8 *)state + 36;
    do {
        *(Effect **)(effectCursorClear + 44) = 0;
        i--;
        effectCursorClear -= 4;
    } while (i >= 0);
    func_800240EC(angleCursorClear, angleCursorInit, arg2);
    colorValue = 0x00808080;
    directionValue = (entity->flags2A >> 9) & 7;
    state->direction = directionValue;
    draw->color = colorValue;

    header = (EntityHeader *)((u8 *)entity - 0x20);
    callInfo = header->info;
    if (func_8003DE58(callInfo->map, callInfo, work.distance, 0) == 0) {
        if (!(header->info->flags & 0x8000)) {
            goto end;
        }
    }

    source = header->position;
    motion->x.half.hi = source->x.half.hi;
    motion->y.half.hi = source->y.half.hi;
    sourceZ = source->z.half.hi;
    motion->z.half.hi = sourceZ;
    if (!(header->info->flags & 0x8000)) {
        motion->x.half.hi += work.distance[0];
        motion->y.half.hi += work.distance[1];
        motion->z.half.hi += work.distance[2];
    } else {
        zResult = sourceZ - 64;
        motion->z.half.hi = zResult;
    }

    if (!(state->flags & 1)) {
        func_8004491C((u8 *)state - 0x20, func_80024DF4);
        state->flags |= 1;
    }
    if (!(state->resource->flags & 0x80)) {
        goto end;
    }

    i = 0;
    if (entity->child != 0) {
        childPosition = *(Motion **)((u8 *)entity->child - 0x18);

        motionCoord = motion->x.half.hi;
        childDelta = childPosition->x.half.hi;
        childDelta -= motionCoord;
        if (childDelta < 0) {
            childDelta = -childDelta;
        }
        work.distance[0] = childDelta;

        childDelta = childPosition->y.half.hi;
        motionCoord = motion->y.half.hi;
        childDelta -= motionCoord;
        if (childDelta < 0) {
            childDelta = -childDelta;
        }
        work.distance[1] = childDelta;

        if (entity->child->flags & 0x40000) {
            motionCoord = motion->z.half.hi - 16;
            childDelta = childPosition->z.half.hi;
            childDelta -= motionCoord;
        } else {
            childDelta = childPosition->z.half.hi;
            motionCoord = motion->z.half.hi;
            childDelta -= motionCoord;
        }
        if (childDelta < 0) {
            childDelta = -childDelta;
        }
        work.distance[2] = childDelta;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        i = 1;

        state->duration = work.distance[0];
        distanceCursor = &work.target.x.half.hi;
        do {
            if (distanceCursor[12] > state->duration) {
                state->duration = (u16)distanceCursor[12];
            }
            i++;
            distanceCursor++;
        } while (i < 3);
        state->duration >>= 5;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->dx.half.hi =
            (childPosition->x.half.hi - motion->x.half.hi) / state->duration;
        motion->dy.half.hi =
            (childPosition->y.half.hi - motion->y.half.hi) / state->duration;
        if (entity->child->flags & 0x40000) {
            motionCoord = motion->z.half.hi;
            childDelta = childPosition->z.half.hi;
            motionCoord -= 16;
            childDelta -= motionCoord;
            motion->dz.half.hi = childDelta / state->duration;
        } else {
            motion->dz.half.hi =
                (childPosition->z.half.hi - motion->z.half.hi) /
                state->duration;
        }
        nextState = (u16)state->state + 1;
        goto reset_state;
    }

    {
        TargetInfo *tileNode;

        tileNode = header->info;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        deadPage = 0x80070000;
        ASM_KEEP(deadPage);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        accumX = tileNode->tileX;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        accumY = tileNode->tileY;
    }
    finalX = accumX;
    savedY = accumY;

    while (i < 8) {
        gridX = (s16)accumX;
        gridY = (s16)accumY;
        value = func_800A44E0(
            (gridX << 6) & 0xFFC0,
            (gridY << 6) & 0xFFC0,
            entity->height,
            (s16)(state->direction << 9));
        if ((s16)value != 0) {
            break;
        }

        LOAD_TABLE_X_BASE(tempT0);
        ASM_KEEP(tempT0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        tableOffset = (s16)state->direction;
        loopHeight = (u16)entity->height;
        tableOffset *= 2;
        tableXEntry = (s16 *)(tableOffset + tempT0);
        ASM_KEEP(tableXEntry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        loopHeight -= 32;
        loopHeight = (s16)loopHeight;
        LOAD_TABLE_Y_BASE(tempT0);
        tableYEntry = (s16 *)(tableOffset + tempT0);
        ASM_KEEP(tableYEntry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        value2 = func_800BCB04(
            ((gridX + *tableXEntry) << 6) + 32 & 0xFFE0,
            ((gridY + *tableYEntry) << 6) + 32 & 0xFFE0,
            loopHeight);
        if ((s16)value2 >= 513 ||
            (s16)(value2 - entity->height) < -63) {
            break;
        }

        LOAD_TABLE_X_BASE(tempT0);
        updateOffset = (s16)state->direction;
        i++;
        updateOffset *= 2;
        updateXEntry = (u16 *)(updateOffset + tempT0);
        LOAD_TABLE_Y_BASE(tempT0);
        updateYEntry = (u16 *)(updateOffset + tempT0);
        ASM_KEEP(updateYEntry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        nextX = accumX + *updateXEntry;
        accumX = nextX;
        nextY = accumY + *updateYEntry;
        accumY = nextY;
        savedY = nextY;
        ASM_KEEP4_NV(nextX, nextY, accumX, accumY);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        finalX = nextX;
    }

    targetPtr = &work.target;
    ASM_KEEP_NV(targetPtr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    i = 1;
    ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    targetX = (u32)finalX << 16;
    tableBase = D_8006CCD8;
    targetX = (s32)targetX >> 10;
    outIdx = (s16)state->direction;
    ASM_KEEP(outIdx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    targetCursor = &work.target.x.half.hi;
    offsetXY = tableBase[outIdx];
    tableBase = D_8006CCE8;
    targetX = targetX + ((offsetXY + 1) << 5);
    targetPtr->x.half.hi = targetX;
    targetX = (s16)targetX;
    tempT0 = (u16)savedY;
    outIdx = (s16)state->direction;
    ASM_KEEP_DEP_NV(tempT0, outIdx);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    targetY = (u32)(u16)tempT0 << 16;
    offsetXY = tableBase[outIdx];
    targetY = (s32)targetY >> 10;
    targetY += (offsetXY + 1) << 5;
    targetPtr->y.half.hi = targetY;
    targetY = (u32)targetY << 16;
    targetZ = (u16)motion->z.half.hi + 32;
    targetPtr->z.half.hi = targetZ;

    {
        s32 rhs;

        rhs = motion->x.half.hi;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        targetY = (s32)targetY >> 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        targetX -= rhs;
        if (targetX < 0) {
            targetX = -targetX;
        }
        work.distance[0] = targetX;

        rhs = motion->y.half.hi;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        targetZ = (u32)targetZ << 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        targetY -= rhs;
        if (targetY < 0) {
            targetY = -targetY;
        }
        work.distance[1] = targetY;

        rhs = motion->z.half.hi;
        targetZ = (s32)targetZ >> 16;
        targetZ -= rhs;
        if (targetZ < 0) {
            targetZ = -targetZ;
        }
        work.distance[2] = targetZ;
    }

    state->duration = work.distance[0];
    do {
        if (targetCursor[12] > state->duration) {
            state->duration = (u16)targetCursor[12];
        }
        i++;
        targetCursor++;
    } while (i < 3);
    state->duration >>= 5;
    if (state->duration == 0) {
        state->duration = 1;
    }
    motion->dx.word = (targetPtr->x.word - motion->x.word) / state->duration;
    motion->dy.word = (targetPtr->y.word - motion->y.word) / state->duration;
    motion->dz.word = (targetPtr->z.word - motion->z.word) / state->duration;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    nextState = 8;
    goto reset_state;

case_2:
    motion->x.half.hi += motion->dx.half.hi;
    motion->y.half.hi += motion->dy.half.hi;
    motion->z.half.hi += motion->dz.half.hi;
    func_800241F8(state, motion);
    if (state->timer < state->duration) {
        goto end;
    }
    func_800A56E0(0x300);
    goto increment_reset;

case_3:
    if (state->timer < 8) {
        goto end;
    }
    state->timer = 0;
    state->timer2 = 0;
    state->state++;
    childPosition = *(Motion **)((u8 *)entity->child - 0x18);
    motion->x.half.hi = childPosition->x.half.hi;
    motion->y.half.hi = childPosition->y.half.hi;
    if (entity->child->flags & 0x40000) {
        motion->z.half.hi = childPosition->z.half.hi + 16;
    } else {
        motion->z.half.hi = childPosition->z.half.hi;
    }

    i = 7;
    angleValue = 16;
    angleCursorBuild = (u8 *)state + 14;
    do {
        *(s16 *)(angleCursorBuild + 26) = angleValue;
        angleValue += 16;
        i--;
        angleCursorBuild -= 2;
    } while (i > 0);
    state->angles[0] = 0;

    i = 9;
    effectCursorCreate = (Effect **)((u8 *)state + 36);
    effectAngle = (s32)0xFF1F0000;
    do {
        effectCursorCreate[11] =
            func_8002443C(state, motion, effectAngle >> 16, i);
        effectCursorCreate--;
        effectStep = 0x190000;
        ASM_KEEP(effectStep);
        i--;
        effectAngle += effectStep;
    } while (i >= 0);
    state->field14 = 0;
    goto epilogue;

case_4: {
    Effect *effectLoop;
    EffectInner *innerLoop;
    s32 effectDelta;

    i = 9;
    effectDelta = 0x40404;
    effectCursorGrow = (Effect **)((u8 *)state + 36);
    do {
        effectLoop = effectCursorGrow[11];
        innerLoop = effectLoop->inner;
        innerLoop->value += effectDelta;
        effectCursorGrow--;
        i--;
    } while (i >= 0);
    if (state->timer2 < 32) {
        goto end;
    }
    nextState = (u16)state->state;
    state->timer2 = 0;
    goto increment_state;
}

case_5:
    if (state->timer2 < 32) {
        goto end;
    }
    nextState = (u16)state->state;
    state->timer2 = 0;
    goto increment_state;

case_6: {
    Effect *effectLoop;
    EffectInner *innerLoop;
    Effect *cleanupEffect;
    register void *a2Alias ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u16 cleanupFlags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 globalFlags;
    s32 effectDelta;

    i = 9;
    effectDelta = -0x40404;
    effectCursorShrink = (Effect **)((u8 *)state + 36);
    do {
        effectLoop = effectCursorShrink[11];
        innerLoop = effectLoop->inner;
        innerLoop->value += effectDelta;
        effectCursorShrink--;
        i--;
    } while (i >= 0);
    if (state->timer2 < 32) {
        goto end;
    }
    a2Alias = entity;
    ASM_KEEP(a2Alias);
    func_80024050(((Entity *)a2Alias)->child, state->id);
    i = 9;
    a2Alias = (void *)0x80080000;
    nextState = (u16)state->state;
    effectCursorCleanup = (Effect **)((u8 *)state + 36);
    state->timer2 = 0;
    nextState++;
    state->state = nextState;
    do {
        cleanupEffect = effectCursorCleanup[11];
        if (cleanupEffect != 0) {
            cleanupFlags = cleanupEffect->flags;
            globalFlags = *(s32 *)((u8 *)a2Alias + 0x14A0);
            cleanupFlags |= 0x8000;
            globalFlags |= 0x8000;
            cleanupEffect->flags = cleanupFlags;
            *(s32 *)((u8 *)a2Alias + 0x14A0) = globalFlags;
            effectCursorCleanup[11] = 0;
        }
        effectCursorCleanup--;
        i--;
    } while (i >= 0);
    state->field14 = 0;
    goto epilogue;
}

case_7:
    if (state->field14 != 0) {
        goto end;
    }
    D_8008346C[0] = 0;
    *(u16 *)((u8 *)state - 2) |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto end;

case_8:
    motion->x.half.hi += motion->dx.half.hi;
    motion->y.half.hi += motion->dy.half.hi;
    motion->z.half.hi += motion->dz.half.hi;
    func_800241F8(state, motion);
    if (state->timer < state->duration) {
        goto end;
    }

increment_reset:
    nextState = (u16)state->state;
    state->timer = 0;
    state->timer2 = 0;
increment_state:
    nextState++;
    state->state = nextState;
    goto end;

case_9:
    if (state->timer < 8) {
        goto end;
    }
    nextState = 7;
    goto reset_state;

reset_state:
    state->state = nextState;
    state->timer = 0;
    state->timer2 = 0;

end:
    state->field14 = 0;
epilogue:
    return;
}
