#include "modules/dungeon_ovl_190081c.h"

void func_8002401C(EntityRec *effect_arg, void *motion_arg, Row_818E0800_S_818E0800_10 *actor_state)
{
    void *actor;
    void *actor_base;
    void *entity;
    void *target;
    void *render_state;
    void *particle;
    register void *sprite_set;
    s32 particles_left;
    register void *actor_data;
    register s32 timer;
    s32 initial_state;
    s32 dispatch_state;
    s32 ground_z;
    s32 found_target;
    s32 hit_effect;

    actor = ((void *)effect_arg->x.v);
    timer = effect_arg->unk_50;
    actor_data = ((Row_818E0800_S_818E0800_1_pre *)actor)[-1].unk_00;
    timer -= 1;
    initial_state = effect_arg->z.w.i;
    effect_arg->unk_50 = timer;
    actor_base = (u8 *)actor - 0x20;

    if (initial_state == 2) {
        target = ((Row_818E0800_S_818E0800_1 *)actor)->unk_60;
        if (target == 0) {
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v =
                ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_00.at00.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v =
                ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_04.at00.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v =
                ((Row_818E0800_S_818E0800_13 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_08;
        } else {
            entity = (u8 *)target - 0x20;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v = ((Row_818E0800_S_818E0800_13 *)(((Row_818E0800_S_818E0800_4 *)entity)->unk_08))->unk_00;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v = ((Row_818E0800_S_818E0800_13 *)(((Row_818E0800_S_818E0800_4 *)entity)->unk_08))->unk_04;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v = ((Row_818E0800_S_818E0800_13 *)(((Row_818E0800_S_818E0800_4 *)entity)->unk_08))->unk_08;
        }

        particles_left = 5;
        sprite_set = D_800DEC28;
        do {
            entity = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (entity != 0) {
                func_8004491C(entity, func_80045340);
                render_state = ((Row_818E0800_S_818E0800_4 *)entity)->unk_0C;
                ((Row_818E0800_S_818E0800_4 *)entity)->unk_10 = func_80024594;
                particle = (u8 *)entity + 0x20;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_0C = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_0E = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v;
                {
                    s32 particle_z;
                    particle_z = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_48 = 0;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_16 = 0;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_14 = 0;
                    particle_z += 0x10;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_10 = particle_z;
                }
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_18 = func_80069EF8();
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_1E = 0x1000;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_1C = 0x1000;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_10 = 0x60;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_00 = sprite_set;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_14 |= 0xC;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_08 = ((Row_818E0800_S_818E0800_7 *)sprite_set)->unk_04;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_04 = 0;
                ((Row_818E0800_S_818E0800_6 *)render_state)->unk_05 = 0;
                ((Row_818E0800_S_818E0800_4 *)entity)->unk_20 = effect_arg;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_4C = 0;
            }
            particles_left -= 1;
        } while (particles_left >= 0);
    }

    dispatch_state = effect_arg->z.w.i;
    switch (dispatch_state) {
    case 0:
        if (!(((Row_818E0800_S_818E0800_14 *)(((void *)effect_arg->y.v)))->unk_00 & 0x80)) {
            return;
        }
        found_target = (s32)dungeonScanMonsterAlongHeading(
            actor, ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_24, ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_25,
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_2A,
            (s16)dungeonGetDefinitionEntryByte13(0x23));
        ((Row_818E0800_S_818E0800_1 *)actor)->unk_60 = found_target;
        if (found_target == 0) {
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.s = ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_24;
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.s = ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_25;
        } else {
            render_state = ((Row_818E0800_S_818E0800_9_pre *)found_target)[-1].unk_00;
            if (((Row_818E0800_S_818E0800_6 *)render_state)->unk_14 & 0x8000) {
                if (actor_state->unk_14 & 0x8000) {
                    effect_arg->z.w.i = 0xF0;
                    return;
                }
            }
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.s = ((Row_818E0800_S_818E0800_6 *)render_state)->unk_24;
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.s = ((Row_818E0800_S_818E0800_6 *)render_state)->unk_25;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_00.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_04.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_0A;
        effect_arg->unk_50 = 8;

        {
            s32 delta_x = ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.u;
            s32 origin_x = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v;
            delta_x <<= 6;
            origin_x -= 0x20;
            delta_x -= origin_x;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at02.v = delta_x;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at00.v /= ((s16)effect_arg->unk_50);
        {
            s32 delta_y = ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.u;
            s32 origin_y = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v - 0x20;
            delta_y <<= 6;
            delta_y -= origin_y;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at02.v = delta_y;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at00.v /= ((s16)effect_arg->unk_50);
        ground_z = (s16)(((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_0A - 0x30);
        ground_z = func_800BCB04(((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v,
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v, ground_z);
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at02.v = ground_z - ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at00.v /= ((s16)effect_arg->unk_50);
        func_800A56E0(0x300);
        (*(u16 *)&effect_arg->z.w.i) += 1;
        return;
    case 1:
    {
        s32 next_timer;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at00.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at00.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at00.v;
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        if (((Row_818E0800_S_818E0800_1 *)actor)->unk_60 != 0) {
            next_timer = 24;
        } else {
            next_timer = 10;
        }
        effect_arg->unk_50 = next_timer;
        (*(u16 *)&effect_arg->z.w.i) += 1;
        return;
    }
    case 2:
    {
        s32 sound_id;
        void *active_target;
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        active_target = ((Row_818E0800_S_818E0800_1 *)actor)->unk_60;
        sound_id = 8;
        if (active_target == 0) {
            effect_arg->unk_50 = 10;
            effect_arg->z.w.i = 0xFF;
            return;
        }
        func_800419EC(sound_id, 0x10);
        effect_arg->unk_50 = 6;
        effect_arg->z.w.i = 0xF0;
        return;
    }
    case 0xF0:
        func_80024784(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, ((s16)effect_arg->unk_50));
        if (((s16)effect_arg->unk_50) == 2 &&
            !dungeonTryTriggerTargetRecordEffect(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, 2, actor)) {
            if (((Row_818E0800_S_818E0800_15 *)(((Row_818E0800_S_818E0800_1 *)actor)->unk_60))->unk_14 & 1) {
                if (((Row_818E0800_S_818E0800_1 *)actor)->unk_60 != 0) {
                    hit_effect = (((Row_818E0800_S_818E0800_11 *)D_800E3D68)->unk_00 == 0xFF) ? 0xFF : 0x10;
                    func_800C8900(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, hit_effect, 2);
                }
            }
        }
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        effect_arg->z.w.i = 0xFF;
        return;
    case 0xFF:
        if (((s16)effect_arg->unk_52) & 0x8000) {
            effect_arg->unk_52 &= 0x7FFF;
            return;
        }
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        dungeonStatus.unk_0C = 0;
        ((Row_818E0800_S_818E0800_0_pre *)effect_arg)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
}
