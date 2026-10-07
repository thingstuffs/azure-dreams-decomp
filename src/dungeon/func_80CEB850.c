#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef s32 M2C_UNK;

typedef struct S_80175050_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80175050_0;   /* arg0 in func_80175050 */

typedef struct S_80175050_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80175050_1;   /* arg2 in func_80175050 */

typedef struct S_80175050_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x1B];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80175050_2;   /* arg3 in func_80175050 */

typedef struct S_80175050_3 {
    u8 unk_00;
    u8 pad_01[0x9];
    u16 unk_0A;
} S_80175050_3;   /* var_v0 in func_80175050 */

typedef struct S_80175050_4 {
    u8 pad_00[0x9B];
    u8 unk_9B;
} S_80175050_4;   /* state0_arg0 in func_80175050 */




s32 func_80042900();
void func_80042B68();
void func_80047784();
s32 func_8009A180();
s16 func_8009FD40();
s32 func_800A2C34();
s32 func_800A6D30();
M2C_UNK func_800A9A04();
void func_800A9A0C();
void func_800AA258();
s32 func_800AA6B4();
s32 func_800AA79C();
void func_800AA888();
void func_80171BEC();
#define func_80171BEC_returning func_80171BEC
void func_801759A0();

extern u8 D_801724BC[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern u8 D_80175E6C[];
extern u8 D_80175E74[];
extern u8 D_80175E7C[];

/* Updates actor state, directional animations, and the shared activity count. */
void func_80175050(void *task, s32 task_id, void *sprite_in, void *actor_in) {
    u8 *next_anim_table;
    u8 *old_anim_table;
    void *starting_task;
    void *actor;
    s32 flags;
    s32 state;
    s32 kind;
    s8 floor;

    actor = actor_in;
    state = ((S_80175050_0 *)task)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_80175050_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        kind = ((S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E54;
            func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E54))->unk_00, 0);
            break;
        case 14:
            ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E5C;
            func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E5C))->unk_00, 0);
            break;
        case 15:
            ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E64;
            func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E64))->unk_00, 0);
            break;
        }
        starting_task = task;
        ((S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A--;
        ((S_80175050_4 *)starting_task)->unk_9B++;
        func_80171BEC_returning(starting_task, task_id, sprite_in);
        return;

    case 1:
        kind = ((S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            old_anim_table = ((S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E54;
            if (old_anim_table != next_anim_table) {
                ((S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 14:
            old_anim_table = ((S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E5C;
            if (old_anim_table != next_anim_table) {
                ((S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 15:
            old_anim_table = ((S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E64;
            if (old_anim_table != next_anim_table) {
                ((S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        }

        if ((func_80042900(actor, 1) << 16) == 0) {
            kind = ((S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C + 8;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C + 8))->unk_00, 0);
                break;
            case 15:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
                break;
            }
        } else {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if (((S_80175050_2 *)actor)->unk_64 != 0 && func_800AA6B4(task, task_id, sprite_in, 0) != 0) {
                return;
            }
            if (((S_80175050_2 *)actor)->unk_25 == 0) {
                if (dungeonStatus.flags & 0x2008) {
                    return;
                }
                func_800AA79C(task, task_id, sprite_in, actor);
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }
            flags = ((S_80175050_2 *)actor)->unk_1C;
            if (flags & 0x100) {
                func_800AA258(task, task_id, sprite_in, actor);
                return;
            }
            if (flags & 0x80000) {
                func_800AA888(task, task_id, sprite_in, actor);
                func_801759A0(task, task_id, sprite_in, actor);
                return;
            }
            if (((S_80175050_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                if ((func_8009A180(actor, *(u8 **)(((u8 *)D_800814A8) + 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *player;
                player = &D_80082E80;
                floor = ((S_80175050_1 *)sprite_in)->unk_26;
                if ((floor == player->unk_026 && floor >= 0) || func_8009FD40(player, sprite_in) < 2) {
                    if (!(func_800A6D30() & 7)) {
                        func_80042B68(actor, 1);
                    }
                }
            }

            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
            kind = ((S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E74;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E74))->unk_00, 0);
                break;
            case 15:
                ((S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                func_80047784(sprite_in, ((S_80175050_3 *)((((gameWork.view.viewAngle + ((S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
                break;
            }
        }

        if (((S_80175050_1 *)sprite_in)->unk_14 & 0x8000) {
            ((S_80175050_0 *)task)->unk_8C = D_801724BC;
            return;
        }
        ((S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A++;
        ((S_80175050_0 *)task)->unk_9B++;

        return;

    case 2:
        if (((S_80175050_1 *)sprite_in)->unk_14 & 0xE000) {
            ((S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A--;
            ((S_80175050_0 *)task)->unk_8C = D_801724BC;
        }
        return;

    default:
        return;
    }

    return;
}
