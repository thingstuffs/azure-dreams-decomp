#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad[0x29C];
    void *table[1];
} D_80010000_T;

typedef struct {
    s32 words[35];
} CreatureSave;

typedef struct S_func_800B1364_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x20];
    u8 *unk_BC;
    u8 *unk_C0;
} S_func_800B1364_1;

typedef struct S_func_800B1364_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800B1364_2;

typedef struct S_func_800B1364_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 *unk_2C;
} S_func_800B1364_3;

typedef struct S_func_800B1364_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void *unk_60;
    u8 pad_64[0x24];
    u16 unk_88;
    s16 unk_8A;
} S_func_800B1364_4;

typedef struct S_func_800B1364_5 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    s32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x6];
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x19];
    u8 unk_43;
    u8 pad_44[0x1C];
    void *unk_60;
    u8 pad_64[0x4];
    u8 unk_68;
    u8 unk_69;
    u8 pad_6A[0x1E];
    s16 unk_88;
    u8 pad_8A[0xE];
    u16 unk_98;
} S_func_800B1364_5;

typedef struct S_func_800B1364_6 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_func_800B1364_6;

typedef struct S_func_800B1364_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_800B1364_7;

typedef struct S_func_800B1364_9 {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    union {
        s8 s8;
        u8 u8;
    } unk_03;
} S_func_800B1364_9;

typedef struct S_func_800B1364_10 {
    u8 pad_00[0xCC];
    s16 unk_CC;
} S_func_800B1364_10;

typedef struct S_func_800B1364_11 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_func_800B1364_11;

typedef struct S_func_800B1364_12 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_func_800B1364_12;

typedef struct S_func_800B1364_13 {
    s32 unk_00;
} S_func_800B1364_13;

typedef struct S_func_800B1364_14 {
    u16 unk_00;
} S_func_800B1364_14;

typedef struct S_func_800B1364_15 {
    s32 unk_00;
} S_func_800B1364_15;

typedef struct S_func_800B1364_16 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_func_800B1364_16;

typedef struct S_func_800B1364_17 {
    u8 pad_00[0x4];
    void *unk_04;
} S_func_800B1364_17;

typedef struct S_func_800B1364_18 {
    void *unk_00;
    void *unk_04;
} S_func_800B1364_18;

typedef struct S_func_800B1364_19 {
    u16 unk_00;
} S_func_800B1364_19;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8003C06C();
s32 func_8003DE58();
M2C_UNK func_8003E188();
void func_800424E0();
M2C_UNK func_80042640();
void func_80048A44();
M2C_UNK func_80069E78();
void func_80093C70();
void func_80093D8C();
void func_80098B38();
void *func_80098CF8();
s16 func_8009904C();
s32 func_80099090();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099254();
void *func_80099290();
s32 func_8009929C();
s32 func_80099734();
void func_80099F04();
void func_80099F70();
void func_8009A028();
void func_8009A3D0();
void func_8009F644();
void *func_8009F868();
s32 func_8009F988();
void *(*func_800A0B94())(M2C_UNK, u8, u8, s16);
s32 func_800A1618();
s32 func_800A1D4C();
s32 func_800A56E0();
s32 func_800A5720();
s32 func_800A6D30();
void func_800A90E8();
void func_800B1768();
void *func_800B4C7C();
void func_800B8024();
#define D_80010000_PTR ((D_80010000_T *)0x80010000)
extern s32 D_8007359C;
extern s32 D_80081484;
extern u32 D_800835E4[];
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800B69DC;
extern s8 D_800DCF4F;
extern u8 D_800DD108[];
extern u8 D_800DD110[];
extern u8 D_800DD118[];
extern u8 D_800DD130[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DDC40;
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E0A2A;
extern M2C_UNK D_800E0A33;
extern s8 D_800E2968;
extern u8 D_800E3544;
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

/* Advances the item interaction, spawning, initializing, and saving a linked creature. */
void func_800B6AC4(S_func_800B1364_1 *action, S_func_800B1364_2 *position, S_func_800B1364_3 *sprite,
    S_func_800B1364_4 *actor) {
    s16 spawn_offset[3];
    register u8 *direction_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 spawn_height;
    s32 creature_variant;
    s32 message_start;
    s32 wear;
    s32 event_flags;
    s32 item_word;
    s32 use_item;
    s16 use_item_test;
    s32 message_end;
    s32 save_slot;
    u8 command;
    u16 sound_timer;
    u16 wait_timer;
    u16 sprite_flags;
    u16 final_flags;
    u32 experience;
    S_func_800B1364_12 *used_item;
    u8 *spawn_item;
    S_func_800B1364_12 *worn_item;
    u8 *direction_anim;
    u8 *view_base;
    u8 state;
    u8 species;
    u8 next_state;
    S_func_800B1364_2 *creature_pos;
    DungeonGlobalStatus *summon_state;
    S_func_800B1364_9 *item_entry;
    S_func_800B1364_5 *stored_creature;
    S_func_800B1364_5 *finished_creature;
    S_func_800B1364_5 *saved_creature;
    S_func_800B1364_11 *input_command;
    S_func_800B1364_10 *item_effect;
    S_func_800B1364_5 *creature;
    S_func_800B1364_3 *creature_sprite;
    S_func_800B1364_5 *linked_creature;
    u32 *level_thresholds;
    u32 *level_table;
    void *save_data;
    S_func_800B1364_5 *hidden_creature;
    register void *release_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_func_800B1364_3 *anim_sprite ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_func_800B1364_7 *global_state = (S_func_800B1364_7 *)((M2C_UNK *)&gameWork.unk_000);

    state = action->unk_9B;
    switch ((u32)(state)) {
    case 0:
    {
        view_base = (u8 *)&gameWork;
        if ((((s32) (((S_func_800B1364_6 *)view_base)->unk_C8 + actor->unk_2A + 0x100) >> 9) & 7) == 2) {
            sprite->unk_2C = D_800DD108;
            func_80048A44(sprite, D_800DD108[((s32) (((S_func_800B1364_6 *)view_base)->unk_C8 + actor->unk_2A
                + 0x100) >> 9) & 7], 0, 1);
            next_state = action->unk_9B;
            action->unk_96 = 0x12U;
            action->unk_9B = (u8) (next_state + 1);
            return;
        }
    }
        actor->unk_2A = (s16) ((u16) actor->unk_2A + 0x200);
        return;
    case 1:
        sound_timer = action->unk_96 - 1;
        action->unk_96 = sound_timer;
        if ((sound_timer << 0x10) == 0) {
            func_800A56E0(0x701);
        }
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        *(u8 **)((u8 *)sprite + 0x2C) = D_800DD110;
        func_80048A44(sprite, D_800DD110[((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        action->unk_9B = (u8) (action->unk_9B + 1);
        if (!(((S_func_800B1364_14 *)&D_80013714)->unk_00 & 1)) {
            func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
            func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
        }
        {
            u8 *item;
            S_func_800B1364_13 *saved_item;
            void *callback;
            item = action->unk_BC;
            action->unk_C0 = item;
            saved_item = (S_func_800B1364_13 *)action->unk_BC;
            item_word = saved_item->unk_00;
            callback = &D_800B69DC;
            action->unk_8C = callback;
            D_80081484 = item_word;
            return;
        }
    case 2:
        sprite_flags = sprite->unk_14;
        if (!(sprite_flags & 0xE000)) {
            DungeonGlobalStatus *control_state = &dungeonStatus;
            control_state->flags = (u16) (control_state->flags | 4);
        } else {
            sprite->unk_14 = (u16) (sprite_flags | 0x6800);
        }
        if (dungeonStatus.flags & 4) {
            return;
        }
        use_item = 0;
        if (((S_func_800B1364_14 *)0x80013714)->unk_00 & 1) {
            input_command = func_8009F868();
            if (input_command == NULL) {
                func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
                func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
                return;
            }
            command = input_command->unk_01 & 0xF8;
            D_800E3544 = command;
            if (command != 0x60) {
                func_8009F988();
                *(u8 **)((u8 *)sprite + 0x2C) = D_800DD118;
                func_80048A44(sprite, D_800DD118[((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
                    0, 1);
                sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
                action->unk_8C = NULL;
                action->unk_9B = 4U;
                return;
            }
            use_item = 1;
        } else if (global_state->unk_08 & 0x40) {
            use_item = 1;
        }
        use_item_test = use_item;
        if (use_item_test != 0) {
            func_8009F644(actor, 0x60, 0, 0);
            func_800A56E0(0x500);
            sprite->unk_14 = (u16) (sprite->unk_14 & 0x97FF);
            action->unk_9B = 3U;
            wear = (func_800A6D30() & 3) + 1;
            used_item = (S_func_800B1364_12 *)action->unk_BC;
            used_item->unk_02 = (s8) (used_item->unk_02 - wear);
            worn_item = (S_func_800B1364_12 *)action->unk_BC;
            if ((s8) worn_item->unk_02 <= 0) {
                worn_item->unk_02 = 0U;
                *(u8 **)((u8 *)sprite + 0x2C) = D_800DD118;
                func_80048A44(sprite, D_800DD118[((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7],
                    0, 1);
                sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
                action->unk_9B = 5U;
                actor->unk_8A = func_8009904C(action->unk_BC);
            }
            func_800B4C7C(0xA4, actor, (s16) (0x64 - (s8) ((S_func_800B1364_12 *)action->unk_BC)->unk_02), 0);
            return;
        }
        {
            s32 cancel_test;
            cancel_test = ((S_func_800B1364_14 *)&D_80013714)->unk_00 & 1;
            if (cancel_test) {
                return;
            }
            cancel_test = global_state->unk_10 & 0x20;
            if (cancel_test == 0) {
                return;
            }
        }
        func_8009F644(actor, 0xA8, 0, 0);
        *(u8 **)((u8 *)sprite + 0x2C) = D_800DD118;
        func_80048A44(sprite, D_800DD118[((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xF7FF);
        func_800A56E0(0x515);
        action->unk_8C = NULL;
        action->unk_9B = 4U;
        return;
    case 3:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        global_state = (S_func_800B1364_7 *)&dungeonStatus.unk_00;
        if (!(global_state->unk_02 & 2)) {
            func_80099F70(actor->unk_5C);
            func_80099F04(actor->unk_5C);
            global_state->unk_02 = (u16) (global_state->unk_02 | 0x812);
        }
        action->unk_9B = 2U;
        return;
    case 4:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        func_80098B38(&D_80081484);
        {
            void *callback = &D_8008ACDC;
            event_flags = ((S_func_800B1364_15 *)&D_800E296C)->unk_00 & 0xFFDFFFFF;
            action->unk_8C = callback;
            (*(s32 *)&D_800E296C) = event_flags;
        }
        return;
    case 5:
        item_effect = func_80098CF8(action, position, sprite, &D_80081484);
        if (item_effect == NULL) {
            return;
        }
        item_effect->unk_CC = 2;
        action->unk_9A = 0x22;
        action->unk_9B = 6U;
        return;
    case 6:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        if (func_8003DE58(sprite->unk_08, sprite, spawn_offset, 0) == 0) {
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
            spawn_offset[2] = 0 - D_800DDC40;
        }
        func_800B8024(position->unk_02 + spawn_offset[0], position->unk_06 + spawn_offset[1],
            position->unk_0A + spawn_offset[2]);
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 7:
        spawn_item = action->unk_C0;
        D_800E2968 = 1;
        creature_variant = func_800A1618(*spawn_item, 2);
        creature = func_800A0B94(*action->unk_C0, creature_variant, 1)(2, sprite->unk_24, sprite->unk_25,
            (s16) (actor->unk_88 - 0x20));
        if (creature == NULL) {
            return;
        }
        func_8003E188(creature->unk_13, 0);
        func_800A90E8(action->unk_C0);
        creature_sprite = ((S_func_800B1364_18 *)((u8 *)creature - 0x18))->unk_04;
        func_8009A3D0(creature_sprite->unk_24, creature_sprite->unk_25, 0x300);
        if (func_8003DE58(sprite->unk_08, sprite, spawn_offset, 0) == 0) {
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
            spawn_offset[2] = 0 - D_800DDC40;
        }
        creature_pos = ((S_func_800B1364_18 *)((u8 *)creature - 0x18))->unk_00;
        creature_pos->unk_02 = (s16) ((u16) position->unk_02 + (u16) spawn_offset[0]);
        creature_pos->unk_06 = (s16) ((u16) position->unk_06 + (u16) spawn_offset[1]);
        spawn_height = (u16) position->unk_0A + (u16) spawn_offset[2];
        creature_pos->unk_0A = spawn_height;
        creature->unk_88 = spawn_height;
        actor->unk_60 = creature;
        func_80042640(creature, creature->unk_13);
        func_800424E0(creature, creature->unk_13, 0);
        creature->unk_43 = 0xFF;
        creature->unk_60 = actor;
        creature->unk_1C = (s32) (creature->unk_1C | 0x80000);
        creature->unk_14 = (s32) (creature->unk_14 | 0x104000);
        linked_creature = actor->unk_60;
        linked_creature->unk_98 = (u16) (linked_creature->unk_98 | 0xC);
        func_80069E78((u8 *)creature + 0x34, func_8003C06C(creature->unk_13));
        experience = D_800835E4[(*(u8 *)((u8 *)&D_800E3D7C->unk_10 + 1))];
        level_thresholds = D_800835E4 + 1;
        creature->unk_18 = experience;
        if (experience >= level_thresholds[creature->unk_11]) {
            level_table = level_thresholds;
            do {
                func_800A1D4C(creature, 0);
            } while (level_table[creature->unk_11] <= (u32) creature->unk_18);
        }
        creature->unk_28 = (u8) creature->unk_29;
        creature->unk_26 = (u8) creature->unk_68;
        creature->unk_27 = (u8) creature->unk_69;
        if (!(((S_func_800B1364_14 *)&D_80013714)->unk_00 & 1)) {
            u16 summon_count;
            DungeonGlobalStatus *summon_control;
            D_800DCF4F = 1;
            summon_control = &dungeonStatus;
            summon_count = ((u16)summon_control->unk_0A);
            summon_control->unk_0A = (u16) (summon_count + 1);
        }
        message_start = func_800990FC();
        message_end = func_80099194(&D_800E0A33, func_80099734(creature, func_80099194(&D_800E0A2A,
            func_80099194(((S_func_800B1364_17 *)((creature->unk_13 * 0x14) + D_8007359C))->unk_04,
            func_8009929C(8, message_start)))));
        if (!((*(u16 *)(&D_80013714)) & 1)) {
            message_end = func_80099254(&D_800E0458, func_8009929C(0x4C, func_8009929C(0x11, message_end)));
        }
        func_80099290(message_end);
        func_800A5720(message_start);
        *(u16 *)((u8 *)action + 0x96) = 0x20U;
        action->unk_9B = (u8) (action->unk_9B + 1);
        if (!((*(u16 *)(&D_80013714)) & 1)) {
            summon_state = &dungeonStatus;
            if ((s16) ((u16)summon_state->unk_0A) < 2) {
                return;
            }
            summon_state->unk_0A = (u16) (((u16)summon_state->unk_0A) - 1);
            return;
        }
        summon_state = &dungeonStatus;
        if (summon_state->unk_0A <= 0) {
            return;
        }
        summon_state->unk_0A = (s16) ((u16) summon_state->unk_0A - 1);
        return;
    case 8:
        if (dungeonStatus.unk_0A != 0) {
            return;
        }
        wait_timer = action->unk_96 - 1;
        action->unk_96 = wait_timer;
        anim_sprite = sprite;
        if ((wait_timer << 0x10) > 0) {
            if (!(sprite->unk_14 & 0x8000)) {
                if (global_state->unk_10 == 0) {
                    return;
                }
            }
        }
        direction_base = D_800DD130;
        *(u8 **)((u8 *)anim_sprite + 0x2C) = direction_base;
        direction_anim = (u8 *) ((u32) (((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7)
            + (u32) direction_base);
        copy_src = NULL;
        goto play_direction_anim;
    case 9:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        *(u8 **)((u8 *)sprite + 0x2C) = D_800DD138;
        func_80048A44(sprite, D_800DD138[((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7], 0, 1);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x200);
        func_80093C70(action, position, sprite);
        func_80093D8C(action, position, sprite);
        save_slot = func_80099090();
        item_entry = D_80010000_PTR->table[actor->unk_8A];
        item_entry->unk_01 = 0x13;
        species = (u8) *action->unk_C0;
        item_entry->unk_03.s8 = save_slot;
        item_entry->unk_02 = 0;
        item_entry->unk_00 = species;
        D_800E3DF0[save_slot] = save_data = (save_slot * 0x8C) + D_800E3E48;
        *(CreatureSave *)save_data = *(CreatureSave *)actor->unk_60;
        stored_creature = actor->unk_60;
        stored_creature->unk_1C = (s32) (stored_creature->unk_1C | 0x400000);
        hidden_creature = actor->unk_60;
        hidden_creature->unk_14 = (s32) (hidden_creature->unk_14 & 0xFFEFFFFF);
        func_800A56E0(0x704);
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 10:
        finished_creature = actor->unk_60;
        if (!(finished_creature->unk_1C & 0x800000)) {
            return;
        }
        func_8009A028(finished_creature);
        copy_src = NULL;
        item_entry = D_80010000_PTR->table[actor->unk_8A];
        saved_creature = D_800E3DF0[item_entry->unk_03.u8 & 0x1F];
        saved_creature->unk_14 = (s32) (saved_creature->unk_14 & ~0x4000);
        release_value = actor->unk_60;
        {
            S_func_800B1364_16 *flags_page;
            flags_page = (S_func_800B1364_16 *)0x80080000;
            ((S_func_800B1364_19 *)((u8 *)release_value - 2))->unk_00 =
                (u16) (((S_func_800B1364_19 *)((u8 *)release_value - 2))->unk_00 | 0x8000);
            release_value = (void *) flags_page->unk_14A0;
            release_value = (void *) ((s32) release_value | 0x8000);
            direction_base = D_800DD140;
            anim_sprite = sprite;
            *(u8 **)((u8 *)anim_sprite + 0x2C) = direction_base;
            direction_anim = direction_base + (((s32) (gameWork.view.viewAngle + actor->unk_2A + 0x100) >> 9) & 7);
            flags_page->unk_14A0 = (s32) release_value;
        }
play_direction_anim:
        func_80048A44(anim_sprite, *direction_anim, copy_src, 1);
read_next_state:
        action->unk_9B = (u8) (action->unk_9B + 1);
        return;
    case 11:
        final_flags = sprite->unk_14;
        if (!(final_flags & 0xE000)) {
            return;
        }
        sprite->unk_14 = (u16) (final_flags & 0xFDFF);
        action->unk_8C = &D_8008ACDC;
        return;
    default:
        return;
    }
}
