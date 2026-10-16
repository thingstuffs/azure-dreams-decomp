#include "modules/dungeon_resource06_slot0.h"

void func_801734B0(void *in_actor, void *in_context, void *in_sprite, void *in_entity)
{
    void *context = in_context;
    s32 entity_flags;
    u16 stat_value;
    u16 stat_delta;
    u8 *page_base;
    s32 state;

    state = ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
        func_80047784(in_sprite,(u8)(((u8 *)D_80175894)[((gameWork.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_96 = 0;
        {
            u16 counter_value;

            counter_value = ((u16)dungeonStatus.unk_0A);
            counter_value--;
            dungeonStatus.unk_0A = counter_value;
        }
        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(in_entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
            func_80047784(in_sprite,(u8)(((u8 *)D_80175894)[((gameWork.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s |= 0x40000;
            if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0x8000)) {

                state = ((u16)dungeonStatus.unk_0A);
                state++;
                dungeonStatus.unk_0A = state;
                ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
                return;
            }
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)func_8017140C);
            return;
        }
        page_base = (u8 *)0x80080000;

        {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_64 != 0) {
                if (func_800AA6B4(in_actor, context, in_sprite, 0) != 0) {
                    return;
                }
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_25 == 0) {
                if (dungeonStatus.flags & 0x2008) {
                    return;
                }
                func_800AA79C(in_actor, context, in_sprite, in_entity);
                return;
            }
            if ((func_800A2C34(in_entity) << 16) != 0) {
                return;
            }
            entity_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u;
            if (entity_flags & 0x100) {
                func_800AA258(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (entity_flags & 0x80000) {

                func_800AA888(in_actor, context, in_sprite, in_entity);
                stat_value = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92;
                stat_delta = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B8 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92 = stat_value - stat_delta;
                func_80173C34(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(in_entity) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((func_8009A180(in_entity,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(in_entity);
            func_800A9A04(in_entity);
            if ((func_80042900(in_entity, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_26;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)func_8009FD40(origin, in_sprite) < 2)) {
                    if (!(func_800A6D30() & 7)) {
                        func_80042B68(in_entity, 1);
                    }
                }
            }
            if ((func_80042900(in_entity, 1) << 16) != 0) {
                return;
            }
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
        func_80047784(in_sprite,(u8)(((u8 *)D_80175894)[((gameWork.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        {
            u32 updated_flags;

            updated_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s;
            updated_flags |= 0x40000;
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s = updated_flags;
        }
        if (((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0x8000) {
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)func_8017140C);
            return;
        }

        {

            state = ((u16)dungeonStatus.unk_0A);
            state++;
            dungeonStatus.unk_0A = state;
        }

        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 2:
        if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            dungeonStatus.unk_0A--;
        }

        ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;

        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)func_8017140C);

        return;
    }
}
