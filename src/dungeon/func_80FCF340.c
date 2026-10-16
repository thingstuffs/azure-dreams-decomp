/* Relinked copy of dungeon/func_809C9228 (func_809C9228.c); retail differs only at relocation sites. */
#include "modules/dungeon_resource03_slot0.h"

/* r121_nodonor relink of dungeon/func_809C9228: symbols this copy binds at other addresses. */
void func_80152F6C(void *controller, void *context, void *entity, EntityRec *actor_state);
extern u8 D_801572A8[];

void func_80152B40(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part)
{
    void *entity_base = entity;
    s16 old_state;
    s32 state_or_direction;
    s16 direction_index;
    s16 direction_copy;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    u32 unused_tail;
    R03_80170A28_EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 entity_flags;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (dungeonStatus.flags & 0x2000) {
        callback = (*(R03_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (R03_80170A28_EntityCallback)((void *)func_80152F6C)) {
            {
                call_self = entity;
                callback(call_self, motion, part, call_self);
            }
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_part = part;
    old_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    call_self = entity;
    if (dungeonRefreshActorFacingAndLifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        R03_80170A28_EntityCallback update_callback;
        update_callback = (*(R03_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    ((R03_80170A28_EntityCallback *)D_801572A8)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    if ((s16)old_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, part, entity);
    }

    part_flags = ((R03_80170A28_S_80170A28_0 *)part)->unk_14;
    if (!(part_flags & 0x8000)) {
        rounded_angle = gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        direction_index = state_or_direction;
        direction_copy = state_or_direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_copy) {
            if (((R03_80170A28_S_80170A28_0 *)part)->unk_2C != 0) {
                selectIndirectTableEntry(part,
                              ((R03_80170A28_S_80170A28_0 *)part)->unk_2C[direction_copy],
                              ((R03_80170A28_S_80170A28_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = dirSpriteFlag[direction_index];
        if (direction_flag != 0) {
            ((R03_80170A28_S_80170A28_0 *)part)->unk_14 |= 1;
        } else {
            ((R03_80170A28_S_80170A28_0 *)part)->unk_14 &= 0xFFFE;
        }
        if (!(((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C & 0x20)) {
            if (!(((R03_80170A28_S_80170A28_0 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((R03_80170A28_S_80170A28_0 *)part)->unk_14 |= 0x7000;
        }
        dungeonApplyMonsterKoyawData(((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((R03_80170A28_S_80170A28_0 *)part)->unk_14 = new_part_flags;
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(s8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(s8 *)((u8 *)entity + 0x9D)) = (u8)(*(s8 *)((u8 *)entity + 0x9D)) + 1;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        ground_height = ((s16)func_800BCB04(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
        if (ground_height < 0x200) {
            base_height = (s16)((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
            } else if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            } else {
                motion->unk_14 = 0;
                ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height - ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88;
            }

            entity_flags = ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = ((s16)func_800BCB04(
                    (((R03_80170A28_S_80170A28_0 *)part)->unk_24 << 6) | 0x20,
                    (((R03_80170A28_S_80170A28_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88 - ground_height;
                ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_88 = ground_height;
            }
        } else {
            ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((R03_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    }

    entity_base = (u8 *)entity_base + 0x88;
    motion->unk_0A =
        *(u16 *)entity_base + (*(u16 *)((u8 *)entity + 0x92));
    ((R03_80170A28_S_80170A28_0 *)part)->unk_14 |= 0x40;

    return;
}
