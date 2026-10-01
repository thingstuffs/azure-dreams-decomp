#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

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
} PackedOffsets;

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
    Spawned *spawnA8;
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

extern PackedOffsets D_80024004;
extern void *D_80024028[];
extern s16 D_80025924;
extern u8 D_800DEC00[12];
extern PackedTemplate D_80025900;

extern void func_8003DB94(Graphic *, void *, s32);
extern s32 func_8003DF74(void *, Component *, ShortVec *, s32);
extern Spawned *func_8003FC64(s32);
extern void func_8004491C(Spawned *, void (*)(void));
extern void func_80045340(void);
extern void func_800248E8(void);

/* Spawns and follows an entity effect, then completes its delayed cleanup. */
void func_80025374(State *state, Vec12 *position, Graphic *graphic)
{
    ShortVec delta;
    PackedOffsets offsets;
    Entity *entity;
    EntityHeader *header;
    Vec12 *source;
    Spawned *spawn;
    u32 dispatch;
    s32 advance;
    s32 state_index;
    static void *const state_labels[] = {
        &&initialize, &&create_spawn, &&follow_spawn, &&wait_finish, &&inactive
    };
    Vec12 *spawn_position;
    u32 flags_or_result;

    entity = state->entity0;
    offsets = D_80024004;
    state_index = state->stateA;
    header = (EntityHeader *)((u8 *)entity - 0x20);
    dispatch = (u32)state_index < 5;
    source = header->source8;
    if (!dispatch) {
        goto done;
    }
    goto *D_80024028[state_index];

initialize:
    {
        u16 next_state;
        u16 source_z;
        u32 flags;
        u32 variant_bits;

        graphic->flagsC = 0x00808080;
        graphic->scale1E = 0x1000;
        graphic->scale1C = 0x1000;
        func_8003DB94(graphic, D_800DEC00, 0);
        flags = *(u16 *)((u8 *)entity + 0x2A);
        D_80025924 = 1;
        next_state = *(u16 *)&state->stateA;
        variant_bits = (flags >> 9) & 7;
        next_state++;
        state->variant7E = variant_bits;
        state->stateA = next_state;

        flags_or_result = func_8003DF74(header->componentC->unk8,
            header->componentC, &delta, 0);
        if (flags_or_result == 0) {
            if (!(header->componentC->flags14 & 0x8000)) {
                goto done;
            }
        }
        position->x = source->x;
        position->y = source->y;
        source_z = source->z;
        position->z = source_z;

        if (!(header->componentC->flags14 & 0x8000)) {
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
        SpawnData *data;
        s32 coord_or_variant;
        s32 offset_x;
        s32 offset_y;
        s16 steps;
        s32 *path_position;
        s32 path_z;

        spawn = func_8003FC64(0x12);
        if (spawn != 0) {
            offset_x = offsets.entry[(s16)state->variant7E].x;
            offset_x <<= 16;
            data = &spawn->data20;
            data->x4C = offset_x;
            offset_y = offsets.entry[(s16)state->variant7E].y;
            data->owner2C = entity;
            data->y50 = offset_y << 16;
            data->path30 = entity->path60;
            data->state34 = state;
            data->ownerIndex15 = state->index9;
            data->variant16 = state->variant7E;

            room = (RoomData *)((EntityHeader *)((u8 *)entity - 0x20))->componentC;
            state->valueA0 = room->x24 + ((ByteEntry *)dirStepX)[(s16)state->variant7E].value;
            coord_or_variant = (s16)state->variant7E;
            state->valueA1 = room->y25 + ((ByteEntry *)dirStepY)[coord_or_variant].value;

            if (entity->path60 != 0) {
                s32 target_coord;
                data->startX38 = (s8)entity->startX72;
                data->startY3A = (s8)entity->startY73;
                data->targetX3C = room->x24;
                data->targetY3E = room->y25;
                data->active8 = 1;

                flags_or_result = (u32)((s8)entity->startX72);
                target_coord = room->x24;
                if ((s32)flags_or_result != target_coord) {
                    flags_or_result = (u32)(((s32)flags_or_result) - (target_coord));
                } else {
                    flags_or_result = (u32)((s8)entity->startY73);
                    target_coord = room->y25;
                    flags_or_result = (u32)(((s32)flags_or_result) - (target_coord));
                }
                if ((s32)flags_or_result < 0) {
                    data->step2 = -(s32)flags_or_result * 2;
                } else {
                    data->step2 = (s32)flags_or_result * 2;
                }

                path_position = (s32 *)((EntityHeader *)((u8 *)entity->path60 - 0x20))->source8;
                steps = data->step2;
                if (steps != 0) {
                    path_z = path_position[2];
                    data->dx54 =
                        (path_z - ((s32 *)position)[2] + (s32)0xFF800000) /
                        (steps - 1);
                }
            } else {
                data->step2 = 0x20;
                data->step4 = 0x20;
                data->active8 = 0;
            }

            state->advance86 = 0;
            spawn->update10 = func_800248E8;
            func_8004491C(spawn, func_80045340);
            graphic = spawn->graphicC;
            graphic->field10 = 0;
            graphic->flags14 |= 0xC;
            spawn_position = spawn->position8;
            ((s32 *)spawn_position)[0] = ((s32 *)position)[0];
            ((s32 *)spawn_position)[1] = ((s32 *)position)[1];
            ((s32 *)spawn_position)[2] = ((s32 *)position)[2];
            graphic = spawn->graphicC;
            ((u8 *)graphic)[0xE] = 0x80;
            ((u8 *)graphic)[0xD] = 0x80;
            ((u8 *)graphic)[0xC] = 0x80;
            graphic->scale1E = 0x1000;
            graphic->scale1C = 0x1000;
            data->template20 = D_80025900;
            graphic->unk8 = &data->template20;
            state->spawnA8 = spawn;
            state->savedPositionAC = spawn_position;
            state->sentinel88 = 99;
        }
        state->stateA++;
        goto done;
    }

follow_spawn:
    {

        if (state->sentinel88 == 99) {
            spawn = state->spawnA8;
            spawn_position = state->savedPositionAC;
            if (spawn->flags1E & 0x8000) {
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
        s32 pending;
        s32 ticks;

        ticks = *(u16 *)&state->counter84;
        state->counter84 = ticks + 1;
        if ((s16)(ticks + 1) >= 11) {
            pending = D_80025924;
            state->counter84 = ticks;
            if (pending == 0) {
                dungeonStatus.unk_0C = 0;
                ((u16 *)state)[-1] |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
            } else {
                D_80025924 = 0;
            }
        }
        goto done;
    }

inactive:
done:
    (void)state_labels;
}
