#include "shared/object_node.h"
#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"





























extern u8 D_800DEC00[12];
extern B32_818CFB74_PackedTemplate D_80025900;


/* Spawns and follows an entity effect, then completes its delayed cleanup. */
void func_80025374(B32_818CFB74_State *state, B32_818CFB74_Vec12 *position, B32_818CFB74_Graphic *graphic)
{
    B32_818CFB74_ShortVec delta;
    B32_818CFB74_PackedOffsets offsets;
    B32_818CFB74_Entity *entity;
    B32_818CFB74_EntityHeader *header;
    B32_818CFB74_Vec12 *source;
    B32_818CFB74_Spawned *spawn;
    u16 next_state;
    u16 source_z;
    u32 flags;
    u32 variant_bits;
    s32 advance;
    s32 state_index;
    B32_818CFB74_Vec12 *spawn_position;
    u32 flags_or_result;

    entity = state->entity0;
    offsets = D_80024004;
    state_index = state->stateA;
    header = (B32_818CFB74_EntityHeader *)((u8 *)entity - 0x20);
    source = header->source8;
    switch (state_index) {
    case 0:
        graphic->flagsC = 0x00808080;
        graphic->scale1E = 0x1000;
        graphic->scale1C = 0x1000;
        func_8003DB94(graphic, D_800DEC00, 0);
        flags = *(u16 *)((u8 *)entity + 0x2A);
        D_80025924[0] = 1;
        next_state = *(u16 *)&state->stateA;
        variant_bits = (flags >> 9) & 7;
        next_state++;
        state->variant7E = variant_bits;
        state->stateA = next_state;

    case 1:
        flags_or_result = func_8003DF74(header->componentC->unk8,
            header->componentC, &delta, 0);
        if (flags_or_result == 0) {
            if (!(header->componentC->flags14 & 0x8000)) {
                break;
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
        if (advance != 0) {
            state->counter84 = 0;
            state->stateA++;
        }
        break;

    case 2:
    {
        B32_818CFB74_RoomData *room;
        B32_818CFB74_SpawnData *data;
        s32 coord_or_variant;
        s32 offset_x;
        s32 offset_y;
        s16 steps;
        s32 *path_position;
        s32 path_z;

        spawn = (B32_818CFB74_Spawned *)func_8003FC64(0x12);
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

            room = (B32_818CFB74_RoomData *)((B32_818CFB74_EntityHeader *)((u8 *)entity - 0x20))->componentC;
            state->valueA0 = room->x24 + ((B32_818CFB74_ByteEntry *)dirStepX)[(s16)state->variant7E].value;
            coord_or_variant = (s16)state->variant7E;
            state->valueA1 = room->y25 + ((B32_818CFB74_ByteEntry *)dirStepY)[coord_or_variant].value;

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

                path_position = (s32 *)((B32_818CFB74_EntityHeader *)((u8 *)entity->path60 - 0x20))->source8;
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
        break;
    }

    case 3:
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

        if (advance != 0) {
            state->counter84 = 0;
            state->stateA++;
        }
        break;

    case 4:
    {
        s32 pending;
        s32 ticks;

        ticks = *(u16 *)&state->counter84;
        state->counter84 = ticks + 1;
        if ((s16)(ticks + 1) >= 11) {
            pending = D_80025924[0];
            state->counter84 = ticks;
            if (pending == 0) {
                dungeonStatus.unk_0C = 0;
                ((u16 *)state)[-1] |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
            } else {
                D_80025924[0] = 0;
            }
        }
        break;
    }

    }
}
