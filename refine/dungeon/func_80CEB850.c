#include "common.h"

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

typedef struct S_80175050_5 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80175050_5;   /* state1_base in func_80175050 */

typedef struct S_80175050_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80175050_6;   /* var_a0 in func_80175050 */


s32 func_80042900();
M2C_UNK func_80042B68();
M2C_UNK func_80047784();
s32 func_8009A180();
s16 func_8009FD40();
s32 func_800A2C34();
s32 func_800A6D30();
M2C_UNK func_800A9A04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
M2C_UNK func_80171BEC();
#ifndef NON_MATCHING
__asm__(".set func_80171BEC_returning, func_80171BEC");
extern M2C_UNK func_80171BEC_returning();
#else
#define func_80171BEC_returning func_80171BEC
#endif
M2C_UNK func_801759A0();

extern u8 *D_800814A8[];
extern u8 D_80082E80[];
extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801724BC[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern u8 D_80175E6C[];
extern u8 D_80175E74[];
extern u8 D_80175E7C[];

/* Updates actor state, directional animations, and the shared activity count. */
void func_80175050(M2C_UNK *task, M2C_UNK task_id, void *sprite_in, M2C_UNK *actor_in) {
    register u8 *anim_table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u8 *next_anim_table;
    u8 *old_anim_table;
    M2C_UNK *starting_task;
    register M2C_UNK *data_ptr ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    M2C_UNK *turn_state;
    M2C_UNK *actor;
    register void *sprite ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 flags;
    s32 state;
    s32 kind;
    s8 floor;

    actor = actor_in;
    sprite = sprite_in;
    ASM_KEEP_NV(sprite);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state = ((S_80175050_0 *)task)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_80175050_1 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        }
        kind = ((S_80175050_2 *)actor)->unk_48;
        if (kind == 14) {
            goto state0_kind_14;
        }
        if (kind < 15) {
            if (kind == 13) {
                goto state0_kind_13;
            }
            goto state0_default_low;
        }
        if (kind == 15) {
            goto state0_kind_15;
        }
        goto state0_default_high;
state0_kind_13:
        anim_table = D_80175E54;
        goto state0_notify;
state0_kind_14:
        anim_table = D_80175E5C;
        goto state0_notify;
state0_kind_15:
        anim_table = D_80175E64;
state0_notify:
        ((S_80175050_1 *)sprite)->unk_2C = anim_table;
        data_ptr = (M2C_UNK *)((((D_80083228[0] + ((S_80175050_2 *)actor)->unk_2A + 0x100) >> 9) & 7) + (unsigned long)anim_table);
        func_80047784(sprite, ((S_80175050_3 *)data_ptr)->unk_00, 0);
        starting_task = task;
        data_ptr = (M2C_UNK *)D_80083460;
        goto state0_decrement;
state0_default_low:
        starting_task = task;
        data_ptr = (M2C_UNK *)D_80083460;
        goto state0_decrement;
state0_default_high:
        starting_task = task;
        data_ptr = (M2C_UNK *)D_80083460;
state0_decrement:
        ((S_80175050_3 *)data_ptr)->unk_0A--;
        ((S_80175050_4 *)starting_task)->unk_9B++;
        func_80171BEC_returning(starting_task, task_id, sprite);
        goto done;

    case 1:
        kind = ((S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            old_anim_table = ((S_80175050_1 *)sprite)->unk_2C;
            next_anim_table = D_80175E54;
            goto state1_maybe_update;
        case 14:
            old_anim_table = ((S_80175050_1 *)sprite)->unk_2C;
            next_anim_table = D_80175E5C;
            goto state1_maybe_update;
        case 15:
            old_anim_table = ((S_80175050_1 *)sprite)->unk_2C;
            next_anim_table = D_80175E64;
            break;
        default:
            goto state1_check;
        }
state1_maybe_update:
        if (old_anim_table != next_anim_table) {
            ((S_80175050_1 *)sprite)->unk_2C = next_anim_table;
            data_ptr = (M2C_UNK *)((((D_80083228[0] + ((S_80175050_2 *)actor)->unk_2A + 0x100) >> 9) & 7) + (unsigned long)next_anim_table);
            func_80047784(sprite, ((S_80175050_3 *)data_ptr)->unk_00, 0);
        }

state1_check:
        if ((func_80042900(actor, 1) << 16) == 0) {
            kind = ((S_80175050_2 *)actor)->unk_48;
            if (kind != 14) {
                if (kind < 15) {
                    if (kind != 13) {
                        goto suffix;
                    }
                    anim_table = D_80175E6C;
                    goto state1_notify;
                }
                goto kind_ge_15;
            } else {
                anim_table = D_80175E6C + 8;
                goto state1_notify;
            }
        }

        turn_state = (M2C_UNK *)D_80083460;
        if (((S_80175050_5 *)turn_state)->unk_02 & 0x1000) {
            goto done;
        }
        if (((S_80175050_2 *)actor)->unk_64 != 0 && func_800AA6B4(task, task_id, sprite, 0) != 0) {
            goto done;
        }
        if (((S_80175050_2 *)actor)->unk_25 == 0) {
            if (((S_80175050_5 *)turn_state)->unk_02 & 0x2008) {
                goto done;
            }
            func_800AA79C(task, task_id, sprite, actor);
            goto done;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            goto done;
        }
        flags = ((S_80175050_2 *)actor)->unk_1C;
        if (flags & 0x100) {
            func_800AA258(task, task_id, sprite, actor);
            goto done;
        }
        if (flags & 0x80000) {
            func_800AA888(task, task_id, sprite, actor);
            func_801759A0(task, task_id, sprite, actor);
            goto done;
        }
        if (((S_80175050_2 *)actor)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor, *(u8 **)(D_800814A8[0] + 0x58) + 0x20) << 16) != 0) {
                goto done;
            }
        }
        func_800A9A0C(actor);
        func_800A9A04(actor);
        if ((func_80042900(actor, 1) << 16) != 0) {
            register unsigned long player_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            register M2C_UNK *player ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
            player_page = 0x80080000;
            ASM_KEEP_NV(player_page);   /* MATCH pin: retail delay-slot fill depends on it */
            player = (M2C_UNK *)(player_page + 0x2E80);
            floor = ((S_80175050_1 *)sprite)->unk_26;
            if (!((floor == ((S_80175050_6 *)player)->unk_26 && floor >= 0) || func_8009FD40(player, sprite) < 2)) {
                goto second_check;
            }
            if (func_800A6D30(player) & 7) {
                goto second_check;
            }
            func_80042B68(actor, 1);
        }

second_check:
        if ((func_80042900(actor, 1) << 16) != 0) {
            goto done;
        }
        kind = ((S_80175050_2 *)actor)->unk_48;
        if (kind != 14) {
            if (kind < 15) {
                if (kind == 13) {
                    goto kind_13;
                }
                goto suffix;
            }
            goto kind_ge_15;
        } else {
            goto kind_14;
        }
kind_ge_15:
        if (kind == 15) {
            goto kind_15;
        }
        goto suffix;
kind_13:
        anim_table = D_80175E6C;
        goto state1_notify;
kind_14:
        anim_table = D_80175E74;
        goto state1_notify;
kind_15:
        anim_table = D_80175E7C;
state1_notify:
        ((S_80175050_1 *)sprite)->unk_2C = anim_table;
        data_ptr = (M2C_UNK *)((((D_80083228[0] + ((S_80175050_2 *)actor)->unk_2A + 0x100) >> 9) & 7) + (unsigned long)anim_table);
        func_80047784(sprite, ((S_80175050_3 *)data_ptr)->unk_00, 0);

suffix:
        if (((S_80175050_1 *)sprite)->unk_14 & 0x8000) {
            ((S_80175050_0 *)task)->unk_8C = D_801724BC;
            goto done;
        }
        data_ptr = (M2C_UNK *)D_80083460;
        ((S_80175050_3 *)data_ptr)->unk_0A++;
        ((S_80175050_0 *)task)->unk_9B++;

        goto done;

    case 2:
        if (((S_80175050_1 *)sprite)->unk_14 & 0xE000) {
            data_ptr = (M2C_UNK *)D_80083460;
            ((S_80175050_3 *)data_ptr)->unk_0A--;
            ((S_80175050_0 *)task)->unk_8C = D_801724BC;
        }
        goto done;

    default:
        goto done;
    }

done:
    return;
}
