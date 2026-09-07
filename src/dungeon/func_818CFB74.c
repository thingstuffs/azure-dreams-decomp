#include "common.h"

typedef struct {
    u16 unk0;
    u16 x;
    u16 unk4;
    u16 y;
    u16 unk8;
    u16 z;
} Vec12;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} ShortVec;

typedef struct {
    s16 x;
    u16 y;
} OffsetPair;

typedef struct {
    OffsetPair entry[8];
} __attribute__((packed)) PackedOffsets;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) PackedChunk12;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) PackedChunk8;

typedef struct {
    PackedChunk12 first;
    PackedChunk12 second;
    PackedChunk8 third;
} __attribute__((packed)) PackedOffsetChunks;

typedef union {
    PackedOffsets values;
    PackedOffsetChunks chunks;
} PackedOffsetLocal;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) PackedTemplate;

typedef struct {
    u8 pad0[8];
    void *unk8;
    u8 padC[8];
    u16 flags14;
} Component;

typedef struct {
    u8 pad0[8];
    void *unk8;
    u32 flagsC;
    u16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    u16 scale1C;
    u16 scale1E;
} Graphic;

typedef struct {
    u8 pad0[2];
    s16 step2;
    s16 step4;
    u8 pad6[2];
    s16 active8;
    u8 padA[0xB];
    u8 ownerIndex15;
    u16 variant16;
    u8 pad18[8];
    PackedTemplate template20;
    void *owner2C;
    void *path30;
    void *state34;
    s16 startX38;
    s16 startY3A;
    s16 targetX3C;
    s16 targetY3E;
    u8 pad40[0xC];
    s32 x4C;
    s32 y50;
    s32 dx54;
} SpawnData;

typedef struct Spawned {
    u8 pad0[8];
    Vec12 *position8;
    Graphic *graphicC;
    void (*update10)(void);
    u8 pad14[0xA];
    u16 flags1E;
    SpawnData data20;
} Spawned;

typedef struct {
    void *entity0;
    u16 *flags4;
    u8 unk8;
    u8 index9;
    s16 stateA;
    u8 padC[0x72];
    u16 variant7E;
    u8 pad80[4];
    s16 counter84;
    s16 advance86;
    s16 sentinel88;
    u8 pad8A[0x16];
    u8 valueA0;
    u8 valueA1;
    u8 padA2[6];
    Spawned *volatile spawnA8;
    Vec12 *savedPositionAC;
} State;

typedef struct {
    u8 pad0[8];
    Vec12 *source8;
    Component *componentC;
} EntityHeader;

typedef struct {
    u8 pad0[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    void *path60;
    u8 pad64[0xE];
    u8 startX72;
    u8 startY73;
} Entity;

typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} RoomData;

typedef struct {
    u8 value;
    u8 pad;
} ByteEntry;

typedef struct {
    s16 value;
    s16 pad[5];
} LargeShort;

typedef struct {
    u8 pad0[0x5924];
    s16 flag5924;
} D_80020000Page;

extern PackedOffsets D_80024004;
extern void *D_80024028[];
extern D_80020000Page D_80020000;
extern u8 D_800DEC00[12];
extern PackedTemplate D_80025900;
extern ByteEntry D_8006CCD8[];
extern ByteEntry D_8006CCE8[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

extern void func_8003DB94(Graphic *, void *, s32);
extern s32 func_8003DF74(void *, Component *, ShortVec *, s32);
extern Spawned *func_8003FC64(s32);
extern void func_8004491C(Spawned *, void (*)(void));
extern void func_80045340(void);
extern void func_800248E8(void);

void func_80025374(State *arg0, Vec12 *arg1, Graphic *arg2)
{
    ShortVec delta;
    PackedOffsetLocal offsets;
    State *state;
    Vec12 *position;
    register Graphic *graphic ASM_REG("$7");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register Entity *entity ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *base ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *object ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *copyReserve;
    register PackedOffsetChunks *offsetSource ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u32 dispatch;
    s32 advanceValue;
    s32 stateNumber;
    static void *const keepalive[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4
    };

    state = arg0;
    position = arg1;
    graphic = arg2;
    copyReserve = (u8 *)0x80020000;
    ASM_KEEP_NV(copyReserve);   /* MATCH pin: keeps a statement from moving across a call/branch */
    entity = state->entity0;
    ASM_KEEP4(state, position, graphic, entity);   /* MATCH pin: keeps a statement from moving across a call/branch */
    offsetSource = (PackedOffsetChunks *)(copyReserve + 0x4004);
    ASM_KEEP_DEP_NV(offsetSource, copyReserve);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    offsets.chunks.first = offsetSource->first;
    offsets.chunks.second = offsetSource->second;
    offsets.chunks.third = offsetSource->third;
    ASM_KEEP(copyReserve);   /* MATCH pin: retail register colouring depends on it */
    stateNumber = state->stateA;
    ASM_KEEP(stateNumber);   /* MATCH pin: retail schedule: same instructions, different order without it */
    base = (u8 *)entity - 0x20;
    ASM_KEEP_NV(base);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    dispatch = (u32)stateNumber < 5;
    object = ((EntityHeader *)base)->source8;
    if (!dispatch) {
        goto done;
    }
    dispatch = 0x80020000;
    ASM_KEEP_NV(dispatch);   /* MATCH pin: load-bearing for the whole function shape */
    dispatch += 0x4028;
    ASM_KEEP_NV(dispatch);   /* MATCH pin: load-bearing for the whole function shape */
    goto *((void **)dispatch)[stateNumber];

case0:
    {
    D_80020000Page *page;
    register s32 temp ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register u32 work ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 sourceZ;

    graphic->flagsC = 0x00808080;
    graphic->scale1E = 0x1000;
    graphic->scale1C = 0x1000;
    func_8003DB94(graphic, D_800DEC00, 0);
    page = (D_80020000Page *)0x80020000;
    ASM_KEEP_NV(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    work = entity->flags2A;
    temp = 1;
    page->flag5924 = temp;
    temp = *(u16 *)&state->stateA;
    work = (work >> 9) & 7;
    temp++;
    state->variant7E = work;
    state->stateA = temp;

    work = func_8003DF74(((EntityHeader *)base)->componentC->unk8,
                        ((EntityHeader *)base)->componentC, &delta, 0);
    if (work != 0) {
        goto case0_found;
    }
    if (!(((EntityHeader *)base)->componentC->flags14 & 0x8000)) {
        goto done;
    }

case0_found:
    position->x = ((Vec12 *)object)->x;
    position->y = ((Vec12 *)object)->y;
    sourceZ = ((Vec12 *)object)->z;
    position->z = sourceZ;

    if (!(((EntityHeader *)base)->componentC->flags14 & 0x8000)) {
        position->x += delta.x;
        position->y += delta.y;
        position->z += delta.z;
    } else {
        position->z = sourceZ - 64;
    }

    advanceValue = *state->flags4 & 0x80;
    goto advance_check;
    }

case1:
    {
    RoomData *room;
    ByteEntry *table;
    register Graphic *spawnGraphic ASM_REG("$7");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register Vec12 *savedPosition ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register PackedOffsets *offsetBase ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u8 *copyPage;
    register PackedTemplate *templateSource ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 roomCoord ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 firstOffset;
    s32 secondOffset;
    s16 steps;

    object = func_8003FC64(0x12);
    offsetBase = &offsets.values;
    if (object != 0) {
        firstOffset = offsetBase->entry[(s16)state->variant7E].x;
        ASM_KEEP(firstOffset);   /* MATCH pin: retail schedule: same instructions, different order without it */
        base = (u8 *)&((Spawned *)object)->data20;
        ASM_KEEP(base);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((SpawnData *)base)->x4C = firstOffset << 16;
        secondOffset = offsetBase->entry[(s16)state->variant7E].y;
        ((SpawnData *)base)->owner2C = entity;
        ((SpawnData *)base)->y50 = secondOffset << 16;
        ((SpawnData *)base)->path30 = entity->path60;
        ((SpawnData *)base)->state34 = state;
        ((SpawnData *)base)->ownerIndex15 = state->index9;
        ((SpawnData *)base)->variant16 = state->variant7E;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */

        room = (RoomData *)((EntityHeader *)((u8 *)entity - 0x20))->componentC;
        table = D_8006CCD8;
        ASM_KEEP_NV(table);   /* MATCH pin: retail immediate-load split depends on it */
        state->valueA0 = room->x24 + table[(s16)state->variant7E].value;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
        table = (ByteEntry *)0x80070000;
        ASM_KEEP(table);   /* MATCH pin: retail immediate-load split depends on it */
        roomCoord = (s16)state->variant7E;
        ASM_KEEP(roomCoord);   /* MATCH pin: retail basic-block layout depends on it */
        table = (ByteEntry *)((u8 *)table - 0x3318);
        ASM_KEEP(table);   /* MATCH pin: retail immediate-load split depends on it */
        state->valueA1 = room->y25 + table[roomCoord].value;

        if (entity->path60 != 0) {
            ((SpawnData *)base)->startX38 = (s8)entity->startX72;
            ((SpawnData *)base)->startY3A = (s8)entity->startY73;
            ((SpawnData *)base)->targetX3C = room->x24;
            ((SpawnData *)base)->targetY3E = room->y25;
            ((SpawnData *)base)->active8 = 1;

            value = (s8)entity->startX72;
            roomCoord = room->x24;
            if (value != roomCoord) {
                value -= roomCoord;
            } else {
                value = (s8)entity->startY73;
                roomCoord = room->y25;
                value -= roomCoord;
            }
            if (value < 0) {
                value = -value;
            }
            ((SpawnData *)base)->step2 = value * 2;
            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

            value = *(s32 *)((u8 *)entity->path60 - 0x18);
            steps = ((SpawnData *)base)->step2;
            if (steps != 0) {
                value = *(volatile s32 *)((u8 *)value + 8);
                ((SpawnData *)base)->dx54 =
                    (value - ((s32 *)position)[2] + (s32)0xFF800000) /
                    (steps - 1);
            }
        } else {
            ((SpawnData *)base)->step2 = 0x20;
            ((SpawnData *)base)->step4 = 0x20;
            ((SpawnData *)base)->active8 = 0;
        }

        state->advance86 = 0;
        ((Spawned *)object)->update10 = func_800248E8;
        func_8004491C(object, func_80045340);
        spawnGraphic = ((Spawned *)object)->graphicC;
        spawnGraphic->field10 = 0;
        spawnGraphic->flags14 |= 0xC;
        savedPosition = ((Spawned *)object)->position8;
        ((s32 *)savedPosition)[0] = ((s32 *)position)[0];
        ((s32 *)savedPosition)[1] = ((s32 *)position)[1];
        ((s32 *)savedPosition)[2] = ((s32 *)position)[2];
        spawnGraphic = ((Spawned *)object)->graphicC;
        ((u8 *)spawnGraphic)[0xE] = 0x80;
        ((u8 *)spawnGraphic)[0xD] = 0x80;
        ((u8 *)spawnGraphic)[0xC] = 0x80;
        spawnGraphic->scale1E = 0x1000;
        spawnGraphic->scale1C = 0x1000;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
        copyPage = (u8 *)0x80020000;
        ASM_KEEP_NV(copyPage);   /* MATCH pin: retail delay-slot fill depends on it */
        templateSource = (PackedTemplate *)(copyPage + 0x5900);
        ASM_KEEP_DEP_NV(templateSource, copyPage);   /* MATCH pin: retail delay-slot fill depends on it */
        ((SpawnData *)base)->template20 = *templateSource;
        ASM_KEEP(copyPage);   /* MATCH pin: retail register colouring depends on it */
        spawnGraphic->unk8 =
            (u8 *)&((Spawned *)object)->data20.template20 +
            ((u8 *)base - (u8 *)&((Spawned *)object)->data20);
        ASM_KEEP(base);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        state->spawnA8 = object;
        state->savedPositionAC = savedPosition;
        state->sentinel88 = 99;
    }
    state->stateA++;
    goto done;
    }

case2:
    {
    register Vec12 *savedPosition ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

    if (state->sentinel88 == 99) {
        object = state->spawnA8;
        savedPosition = state->savedPositionAC;
        if (((Spawned *)object)->flags1E & 0x8000) {
            state->sentinel88 = 0;
        } else {
            ((s32 *)position)[0] = ((s32 *)savedPosition)[0];
            ((s32 *)position)[1] = ((s32 *)savedPosition)[1];
            ((s32 *)position)[2] = ((s32 *)savedPosition)[2];
        }
    }
    advanceValue = state->advance86;
    }

advance_check:
    if (advanceValue != 0) {
        state->counter84 = 0;
        state->stateA++;
    }
    goto done;

case3:
    {
    D_80020000Page *page;
    u8 *page8a;
    u8 *page8b;
    u16 objectFlags;
    s32 pageFlag;
    s32 value;

    value = *(u16 *)&state->counter84;
    state->counter84 = value + 1;
    if ((s16)(value + 1) >= 11) {
        page = (D_80020000Page *)0x80020000;
        ASM_KEEP_NV(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        pageFlag = page->flag5924;
        state->counter84 = value;
        if (pageFlag == 0) {
            page8a = (u8 *)0x80080000;
            ASM_KEEP_NV(page8a);   /* MATCH pin: keeps a statement from moving across a call/branch */
            *(s32 *)(page8a + 0x346C) = 0;
            objectFlags = ((u16 *)state)[-1];
            ASM_KEEP(objectFlags);   /* MATCH pin: load-bearing for the whole function shape */
            page8b = (u8 *)0x80080000;
            ASM_KEEP(page8b);
            objectFlags |= 0x8000;
            ((u16 *)state)[-1] = objectFlags;
            *(s32 *)(page8b + 0x14A0) |= 0x8000;
        } else {
            page->flag5924 = 0;
        }
    }
    goto done;
    }

case4:
    goto done;

done:
    (void)keepalive;
}
