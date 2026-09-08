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

/* Spawns and follows an entity effect, then completes its delayed cleanup. */
void func_80025374(State *state_arg, Vec12 *position_arg, Graphic *graphic_arg)
{
    ShortVec delta;
    PackedOffsetLocal offsets;
    State *state;
    Vec12 *position;
    register Graphic *graphic ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register Entity *entity ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *data_base ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *source_or_spawn ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *offset_page;
    register PackedOffsetChunks *offset_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 dispatch;
    s32 advance;
    s32 state_index;
    static void *const state_labels[] = {
        &&initialize, &&create_spawn, &&follow_spawn, &&wait_finish, &&inactive
    };

    state = state_arg;
    position = position_arg;
    graphic = graphic_arg;
    offset_page = (u8 *)0x80020000;
    ASM_KEEP_NV(offset_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    entity = state->entity0;
    ASM_KEEP4(state, position, graphic, entity);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    offset_source = (PackedOffsetChunks *)(offset_page + 0x4004);
    ASM_KEEP_DEP_NV(offset_source, offset_page);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    offsets.chunks.first = offset_source->first;
    offsets.chunks.second = offset_source->second;
    offsets.chunks.third = offset_source->third;
    ASM_KEEP(offset_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    state_index = state->stateA;
    ASM_KEEP(state_index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    data_base = (u8 *)entity - 0x20;
    ASM_KEEP_NV(data_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    dispatch = (u32)state_index < 5;
    source_or_spawn = ((EntityHeader *)data_base)->source8;
    if (!dispatch) {
        goto done;
    }
    dispatch = 0x80020000;
    ASM_KEEP_NV(dispatch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    dispatch += 0x4028;
    ASM_KEEP_NV(dispatch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    goto *((void **)dispatch)[state_index];

initialize:
    {
        D_80020000Page *page;
        register s32 next_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u32 flags_or_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        u16 source_z;

        graphic->flagsC = 0x00808080;
        graphic->scale1E = 0x1000;
        graphic->scale1C = 0x1000;
        func_8003DB94(graphic, D_800DEC00, 0);
        page = (D_80020000Page *)0x80020000;
        ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        flags_or_result = entity->flags2A;
        next_state = 1;
        page->flag5924 = next_state;
        next_state = *(u16 *)&state->stateA;
        flags_or_result = (flags_or_result >> 9) & 7;
        next_state++;
        state->variant7E = flags_or_result;
        state->stateA = next_state;

        flags_or_result = func_8003DF74(((EntityHeader *)data_base)->componentC->unk8,
            ((EntityHeader *)data_base)->componentC, &delta, 0);
        if (flags_or_result != 0) {
            goto position_ready;
        }
        if (!(((EntityHeader *)data_base)->componentC->flags14 & 0x8000)) {
            goto done;
        }

position_ready:
        position->x = ((Vec12 *)source_or_spawn)->x;
        position->y = ((Vec12 *)source_or_spawn)->y;
        source_z = ((Vec12 *)source_or_spawn)->z;
        position->z = source_z;

        if (!(((EntityHeader *)data_base)->componentC->flags14 & 0x8000)) {
            position->x += delta.x;
            position->y += delta.y;
            position->z += delta.z;
        } else {
            position->z = source_z - 64;
        }

        advance = *state->flags4 & 0x80;
        goto advance_check;
    }

create_spawn:
    {
        RoomData *room;
        ByteEntry *table;
        register Graphic *spawn_graphic ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register Vec12 *spawn_position ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register PackedOffsets *offset_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *template_page;
        register PackedTemplate *template_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 path_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register s32 coord_or_variant ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 offset_x;
        s32 offset_y;
        s16 steps;

        source_or_spawn = func_8003FC64(0x12);
        offset_base = &offsets.values;
        if (source_or_spawn != 0) {
            offset_x = offset_base->entry[(s16)state->variant7E].x;
            ASM_KEEP(offset_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            data_base = (u8 *)&((Spawned *)source_or_spawn)->data20;
            ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            ((SpawnData *)data_base)->x4C = offset_x << 16;
            offset_y = offset_base->entry[(s16)state->variant7E].y;
            ((SpawnData *)data_base)->owner2C = entity;
            ((SpawnData *)data_base)->y50 = offset_y << 16;
            ((SpawnData *)data_base)->path30 = entity->path60;
            ((SpawnData *)data_base)->state34 = state;
            ((SpawnData *)data_base)->ownerIndex15 = state->index9;
            ((SpawnData *)data_base)->variant16 = state->variant7E;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

            room = (RoomData *)((EntityHeader *)((u8 *)entity - 0x20))->componentC;
            table = D_8006CCD8;
            ASM_KEEP_NV(table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            state->valueA0 = room->x24 + table[(s16)state->variant7E].value;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            table = (ByteEntry *)0x80070000;
            ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            coord_or_variant = (s16)state->variant7E;
            ASM_KEEP(coord_or_variant);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            table = (ByteEntry *)((u8 *)table - 0x3318);
            ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            state->valueA1 = room->y25 + table[coord_or_variant].value;

            if (entity->path60 != 0) {
                ((SpawnData *)data_base)->startX38 = (s8)entity->startX72;
                ((SpawnData *)data_base)->startY3A = (s8)entity->startY73;
                ((SpawnData *)data_base)->targetX3C = room->x24;
                ((SpawnData *)data_base)->targetY3E = room->y25;
                ((SpawnData *)data_base)->active8 = 1;

                path_value = (s8)entity->startX72;
                coord_or_variant = room->x24;
                if (path_value != coord_or_variant) {
                    path_value -= coord_or_variant;
                } else {
                    path_value = (s8)entity->startY73;
                    coord_or_variant = room->y25;
                    path_value -= coord_or_variant;
                }
                if (path_value < 0) {
                    path_value = -path_value;
                }
                ((SpawnData *)data_base)->step2 = path_value * 2;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

                path_value = *(s32 *)((u8 *)entity->path60 - 0x18);
                steps = ((SpawnData *)data_base)->step2;
                if (steps != 0) {
                    path_value = *(volatile s32 *)((u8 *)path_value + 8);
                    ((SpawnData *)data_base)->dx54 =
                        (path_value - ((s32 *)position)[2] + (s32)0xFF800000) /
                        (steps - 1);
                }
            } else {
                ((SpawnData *)data_base)->step2 = 0x20;
                ((SpawnData *)data_base)->step4 = 0x20;
                ((SpawnData *)data_base)->active8 = 0;
            }

            state->advance86 = 0;
            ((Spawned *)source_or_spawn)->update10 = func_800248E8;
            func_8004491C(source_or_spawn, func_80045340);
            spawn_graphic = ((Spawned *)source_or_spawn)->graphicC;
            spawn_graphic->field10 = 0;
            spawn_graphic->flags14 |= 0xC;
            spawn_position = ((Spawned *)source_or_spawn)->position8;
            ((s32 *)spawn_position)[0] = ((s32 *)position)[0];
            ((s32 *)spawn_position)[1] = ((s32 *)position)[1];
            ((s32 *)spawn_position)[2] = ((s32 *)position)[2];
            spawn_graphic = ((Spawned *)source_or_spawn)->graphicC;
            ((u8 *)spawn_graphic)[0xE] = 0x80;
            ((u8 *)spawn_graphic)[0xD] = 0x80;
            ((u8 *)spawn_graphic)[0xC] = 0x80;
            spawn_graphic->scale1E = 0x1000;
            spawn_graphic->scale1C = 0x1000;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            template_page = (u8 *)0x80020000;
            ASM_KEEP_NV(template_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            template_source = (PackedTemplate *)(template_page + 0x5900);
            ASM_KEEP_DEP_NV(template_source, template_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((SpawnData *)data_base)->template20 = *template_source;
            ASM_KEEP(template_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            spawn_graphic->unk8 =
                (u8 *)&((Spawned *)source_or_spawn)->data20.template20 +
                ((u8 *)data_base - (u8 *)&((Spawned *)source_or_spawn)->data20);
            ASM_KEEP(data_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            state->spawnA8 = source_or_spawn;
            state->savedPositionAC = spawn_position;
            state->sentinel88 = 99;
        }
        state->stateA++;
        goto done;
    }

follow_spawn:
    {
        register Vec12 *spawn_position ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        if (state->sentinel88 == 99) {
            source_or_spawn = state->spawnA8;
            spawn_position = state->savedPositionAC;
            if (((Spawned *)source_or_spawn)->flags1E & 0x8000) {
                state->sentinel88 = 0;
            } else {
                ((s32 *)position)[0] = ((s32 *)spawn_position)[0];
                ((s32 *)position)[1] = ((s32 *)spawn_position)[1];
                ((s32 *)position)[2] = ((s32 *)spawn_position)[2];
            }
        }
        advance = state->advance86;
    }

advance_check:
    if (advance != 0) {
        state->counter84 = 0;
        state->stateA++;
    }
    goto done;

wait_finish:
    {
        D_80020000Page *page;
        u8 *reset_page;
        u8 *flags_page;
        u16 object_flags;
        s32 pending;
        s32 ticks;

        ticks = *(u16 *)&state->counter84;
        state->counter84 = ticks + 1;
        if ((s16)(ticks + 1) >= 11) {
            page = (D_80020000Page *)0x80020000;
            ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            pending = page->flag5924;
            state->counter84 = ticks;
            if (pending == 0) {
                reset_page = (u8 *)0x80080000;
                ASM_KEEP_NV(reset_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                *(s32 *)(reset_page + 0x346C) = 0;
                object_flags = ((u16 *)state)[-1];
                ASM_KEEP(object_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                flags_page = (u8 *)0x80080000;
                ASM_KEEP(flags_page);
                object_flags |= 0x8000;
                ((u16 *)state)[-1] = object_flags;
                *(s32 *)(flags_page + 0x14A0) |= 0x8000;
            } else {
                page->flag5924 = 0;
            }
        }
        goto done;
    }

inactive:
    goto done;

done:
    (void)state_labels;
}
