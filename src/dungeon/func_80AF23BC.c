#include "modules/dungeon_resource10_slot0.h"

void func_80173BBC(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759E8);
        func_80047784(sprite_in,
            ((u8 *)D_801759E8)[((gameWork.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &dungeonStatus;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(actor_in, 1) << 16) != 0) {
            status = &dungeonStatus;
            if (status->flags & 0x1000) {
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (func_800AA6B4(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                func_800AA79C(action, context, sprite_in, actor_in);
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                func_800AA258(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(action, context, sprite_in, actor_in);
                func_80174258(action, context, sprite_in, actor_in);
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                if ((func_8009A180(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor_in);
            func_800A9A04(actor_in);
            if ((func_80042900(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = ((s16)func_8009FD40(origin, sprite_in));
                    actor_to_check = actor_in;
                    if (probe_result >= 2) {
                        goto final_check_call;
                    }
                    if (!(func_800A6D30(actor_in) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                } else {
                    if (!(func_800A6D30(origin) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                }
            }

            actor_to_check = actor_in;
final_check_call:
            if ((func_80042900(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759F0);
            func_80047784(sprite_in,
                ((u8 *)D_801759F0)[((gameWork.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);
                return;
            }
            dungeonStatus.unk_0A++;

            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759F0);
        func_80047784(sprite_in,
            ((u8 *)D_801759F0)[((gameWork.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);
            return;
        }
        dungeonStatus.unk_0A++;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        dungeonStatus.unk_0A--;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);

        return;
    }
}
