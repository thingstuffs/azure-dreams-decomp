#include "modules/dungeon_ovl_19a332c.h"

void *func_80025F54(s32 x, s32 y, s32 z, s32 angle)
{
    ovl_19a332c_81984754_Object *objects[9];
    u16 spawn_x;
    u16 spawn_y;
    u16 spawn_z;
    s32 spawn_angle;
    EntityRec *target_pos;
    ovl_19a332c_81984754_Object **object_base;
    ovl_19a332c_81984754_Object **object_slot;
    ovl_19a332c_81984754_Pos *pos;
    ovl_19a332c_81984754_Part *part;
    ovl_19a332c_81984754_Entity *entity;
    ovl_19a332c_81984754_Entity *prev_entity;
    s32 object_index;
    s32 history_index;
    s32 target_angle;
    s32 normalized_target;
    s32 signed_target;
    s32 angle_bits;
    s32 angle_delta;
    u8 *allocation_page;
    ovl_19a332c_81984754_Object *prev_object;

    spawn_angle = angle;
    prev_entity = 0;
    spawn_x = x;
    spawn_y = y;
    spawn_z = z;
    if (hasEnoughAvailableRuntimeNodes(9) == 0) {
        return prev_entity;
    }

    object_index = 0;
    object_base = &objects[object_index];
    target_pos = &D_80083780;
    object_slot = object_base;
    do {
        allocation_page = (u8 *)0x80080000;
        if (object_index != 0) {
            prev_object = object_slot[-1];
        } else {
            prev_object = (ovl_19a332c_81984754_Object *)((u8 *)(&D_80083498));
        }
        *object_slot = func_8003FD64(2, prev_object);
        (*object_slot)->state = (void (*)(void *))(void *)dungeonUpdateHomingEffectAndAttachedCopies;
        func_8004491C(*object_slot, func_800C9034);

        pos = (*object_slot)->pos;
        pos->x = spawn_x;
        pos->y = spawn_y;
        pos->z = spawn_z;

        part = (*object_slot)->part;
        part->f16 = 0x400;
        part->f1A = spawn_angle - 0x400;
        part->table = D_80026B2C + (object_index * 0x10);
        part->f10 = 0x60;
        part->flags |= 0xC;

        entity = &(*object_slot)->entity;
        if (object_index != 0) {
            u32 parent_link;
            u32 link_scratch;
            parent_link = (u32)D_80026BBC;
            link_scratch = parent_link + object_index;
            parent_link = *(u8 *)link_scratch;
            if (parent_link != 0) {
                link_scratch = 0x7FFFFFFF;
                entity->parent = (ovl_19a332c_81984754_Object *)((u32)object_base[parent_link - 1] & link_scratch);
            } else {
                entity->parent = object_slot[-1];
            }
        }

        entity->f34 = 0x10;
        entity->angle = spawn_angle + 0x400;
        entity->f44 = ((u32)spawn_angle >> 9) & 7;
        entity->f3C = 0;
        entity->f3A = D_80026BC8[object_index] != 0 ? 0xF : 0;
        entity->f36 = 1;
        entity->index = object_index;

        if (prev_entity != 0) {
            prev_entity->next = *object_slot;
        }

        target_angle = dungeonForwardMonsterCoordinateDelta(pos->x, pos->y,
                              target_pos->x.w.i,
                              target_pos->y.w.i);

        angle_bits = (u16)entity->angle;
        entity->angle = (angle_bits & 0x800)
            ? (angle_bits | 0xF800)
        : (angle_bits & 0x7FF);

        normalized_target = target_angle & 0x800;
        if (normalized_target != 0) {
            normalized_target = target_angle | 0xF800;
        } else {
            normalized_target = target_angle & 0x7FF;
        }
        target_angle = normalized_target;

        angle_bits = (s32)((u32)target_angle << 16);
        signed_target = angle_bits >> 16;
        angle_delta = (s16)entity->angle;
        angle_delta -= signed_target;
        angle_bits = (u16)entity->angle;
        if (angle_delta < 0) {
            angle_delta = -angle_delta;
        }
        if (angle_delta >= 0x801) {
            entity->angle = (target_angle & -0x1000) |
                            (angle_bits & 0xFFF);
        }

        entity->direction = (s16)entity->angle < signed_target;

        history_index = 7;
        do {
            entity->history[history_index].x = pos->x;
            entity->history[history_index].y = pos->y;
            entity->history[history_index].z = pos->z;
            history_index--;
        } while (history_index >= 0);

        inventorySelectEntryAndResetObject(part, 0);
        inventoryCopyAndSignExtendRecordFields(entity, part->unk0);
        prev_entity = entity;
        object_slot++;
        object_index++;
    } while (object_index < 9);

    return objects[0];
}
