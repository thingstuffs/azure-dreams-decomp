#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad[0x29C];
    void *table[1];
} D_80010000_T;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[3];
} Copy12;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089310[];
s32 func_8003C06C();
s32 func_8003DE58();
M2C_UNK func_8003E188();
void func_800424E0();
M2C_UNK func_80042640();
void func_80048A44();
M2C_UNK func_80069E78();
M2C_UNK func_80093C70();
M2C_UNK func_80093D8C();
void func_80098B38();
void *func_80098CF8();
s16 func_8009904C();
s32 func_80099090();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099254();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_8009F644();
void *func_8009F868();
s32 func_8009F988();
void *(*func_800A0B94())(M2C_UNK, u8, u8, s16);
s32 func_800A1618();
M2C_UNK func_800A1D4C();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5720();
s32 func_800A6D30();
M2C_UNK func_800A90E8();
M2C_UNK func_800B1768();
M2C_UNK func_800B4C7C();
M2C_UNK func_800B8024();
extern M2C_UNK D_80013714;
#define D_80010000_PTR ((D_80010000_T *)0x80010000)
extern s32 D_8007359C;
extern s32 D_80081484;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern s16 D_8008346A;
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
extern M2C_UNK D_800E296C;
extern u8 D_800E3544;
extern void *D_800E3D7C;
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

/* Advances the item interaction, spawning, initializing, and saving a linked creature. */
void func_800B6AC4(void *action, void *position, void *sprite, void *actor) {
    static void *const state_labels[] = { &&align_actor, &&wait_open_anim, &&handle_item_input, &&wait_use_anim, &&finish_cancel, &&create_item_effect, &&show_spawn_effect, &&spawn_creature, &&wait_spawn, &&save_creature, &&finish_creature, &&restore_idle };
    s16 spawn_offset[3];
    register u8 *direction_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 spawn_height;
    s32 creature_variant;
    s32 message_start;
    s32 wear;
    s32 event_flags;
    s32 item_word;
    s32 use_item;
    register s32 use_item_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 message_end;
    s32 save_slot;
    u8 command;
    u16 sound_timer;
    u16 wait_timer;
    u16 sprite_flags;
    u16 final_flags;
    u32 experience;
    u8 *used_item;
    u8 *spawn_item;
    u8 *worn_item;
    u8 *direction_anim;
    u8 state;
    u8 species;
    register u8 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *creature_pos;
    void *summon_state;
    void *item_entry;
    void *stored_creature;
    void *finished_creature;
    void *saved_creature;
    void *copy_end;
    void *input_command;
    void *item_effect;
    void *creature;
    void *creature_sprite;
    void *linked_creature;
    u32 *level_thresholds;
    u32 *level_table;
    void *save_data;
    void *hidden_creature;
    register void *release_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *anim_sprite ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register void *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *copy_dst;
    M2C_UNK *global_state = (M2C_UNK *)&D_80083160;

    state = M2C_FIELD(action, u8 *, 0x9B);
    if (state >= 0xCU) {
        goto done;
    }
    (void)state_labels; goto *D_80089310[(u32)(state)];
align_actor: {
    register u8 *input_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    input_page = (u8 *)0x80080000;
    ASM_KEEP_NV(input_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    direction_base = input_page + 0x3160;
    if ((((s32) (M2C_FIELD(direction_base, s16 *, 0xC8) + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7) != 2) {
        goto turn_actor;
    }
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD108;
    func_80048A44(sprite, D_800DD108[((s32) (M2C_FIELD(direction_base, s16 *, 0xC8) + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    next_state = M2C_FIELD(action, u8 *, 0x9B);
    M2C_FIELD(action, u16 *, 0x96) = 0x12U;
    goto advance_state;
}
turn_actor:
    M2C_FIELD(actor, s16 *, 0x2A) = (s16) ((u16) M2C_FIELD(actor, s16 *, 0x2A) + 0x200);
    return;
wait_open_anim:
    sound_timer = M2C_FIELD(action, u16 *, 0x96) - 1;
    M2C_FIELD(action, u16 *, 0x96) = sound_timer;
    if ((sound_timer << 0x10) != 0) {
        goto check_open_anim;
    }
    func_800A56E0(0x701);
check_open_anim:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD110;
    func_80048A44(sprite, D_800DD110[((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(action, u8 *, 0x9B) = (u8) (M2C_FIELD(action, u8 *, 0x9B) + 1);
    if (M2C_FIELD(&D_80013714, u16 *, 0) & 1) {
        goto save_item;
    }
    func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
    func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
save_item: {
    u8 *item;
    u8 *saved_item;
    void *callback;
    item = M2C_FIELD(action, u8 **, 0xBC);
    saved_item = item;
    ASM_KEEP_NV(saved_item);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(action, u8 **, 0xC0) = item;
    item_word = M2C_FIELD(saved_item, s32 *, 0);
    callback = &D_800B69DC;
    M2C_FIELD(action, void **, 0x8C) = callback;
    D_80081484 = item_word;
    return;
}
handle_item_input:
    sprite_flags = M2C_FIELD(sprite, u16 *, 0x14);
    if (sprite_flags & 0xE000) {
        goto set_input_anim_flags;
    }
    {
        void *control_state = &D_80083460;
        M2C_FIELD(control_state, u16 *, 2) = (u16) (M2C_FIELD(control_state, u16 *, 2) | 4);
    }
    goto check_input_ready;
set_input_anim_flags:
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (sprite_flags | 0x6800);
check_input_ready:
    if (D_80083462 & 4) {
        goto done;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    use_item = 0;
    if (!(M2C_FIELD(&D_80013714, u16 *, 0) & 1)) {
        goto check_use_button;
    }
    input_command = func_8009F868();
    if (input_command != NULL) {
        goto read_command;
    }
    func_800B1768(0x22, 0xF2, 0xBA, 0x105, 0, 8);
    func_800B1768(0x23, 0xE0, 0xCE, 0x104, 1, 8);
    return;
read_command:
    command = M2C_FIELD(input_command, u8 *, 1) & 0xF8;
    D_800E3544 = command;
    if (command == 0x60) {
        goto request_item_use;
    }
    func_8009F988();
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD118;
    func_80048A44(sprite, D_800DD118[((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0xF7FF);
    goto start_cancel;
check_use_button:
    if (!(M2C_FIELD(global_state, s32 *, 8) & 0x40)) {
        goto check_item_use;
    }
request_item_use:
    use_item = 1;
check_item_use:
    use_item_test = use_item;
    if (use_item_test == 0) {
        goto check_cancel;
    }
    func_8009F644(actor, 0x60, 0, 0);
    func_800A56E0(0x500);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0x97FF);
    M2C_FIELD(action, u8 *, 0x9B) = 3U;
    wear = (func_800A6D30() & 3) + 1;
    used_item = M2C_FIELD(action, u8 **, 0xBC);
    M2C_FIELD(used_item, u8 *, 2) = (s8) (M2C_FIELD(used_item, u8 *, 2) - wear);
    worn_item = M2C_FIELD(action, u8 **, 0xBC);
    if ((s8) M2C_FIELD(worn_item, u8 *, 2) > 0) {
        goto show_item_progress;
    }
    M2C_FIELD(worn_item, u8 *, 2) = 0U;
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD118;
    func_80048A44(sprite, D_800DD118[((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(action, u8 *, 0x9B) = 5U;
    M2C_FIELD(actor, s16 *, 0x8A) = func_8009904C(M2C_FIELD(action, u8 **, 0xBC));
show_item_progress:
    func_800B4C7C(0xA4, actor, (s16) (0x64 - (s8) M2C_FIELD(M2C_FIELD(action, u8 **, 0xBC), u8 *, 2)), 0);
    return;
check_cancel:
    {
        register s32 cancel_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        cancel_test = M2C_FIELD(&D_80013714, u16 *, 0) & 1;
        if (cancel_test) {
            goto done;
        }
        cancel_test = M2C_FIELD(global_state, s32 *, 0x10) & 0x20;
        if (cancel_test == 0) {
            goto done;
        }
    }
    func_8009F644(actor, 0xA8, 0, 0);
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD118;
    func_80048A44(sprite, D_800DD118[((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0xF7FF);
    func_800A56E0(0x515);
start_cancel:
    M2C_FIELD(action, M2C_UNK **, 0x8C) = NULL;
    M2C_FIELD(action, u8 *, 0x9B) = 4U;
    return;
wait_use_anim:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    global_state = &D_80083460;
    if (M2C_FIELD(global_state, u16 *, 2) & 2) {
        goto resume_input;
    }
    func_80099F70(M2C_FIELD(actor, s32 *, 0x5C));
    func_80099F04(M2C_FIELD(actor, s32 *, 0x5C));
    M2C_FIELD(global_state, u16 *, 2) = (u16) (M2C_FIELD(global_state, u16 *, 2) | 0x812);
resume_input:
    M2C_FIELD(action, u8 *, 0x9B) = 2U;
    return;
finish_cancel:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    func_80098B38(&D_80081484);
    {
        void *callback = &D_8008ACDC;
        event_flags = M2C_FIELD(&D_800E296C, s32 *, 0) & 0xFFDFFFFF;
        M2C_FIELD(action, void **, 0x8C) = callback;
        (*(s32 *)&D_800E296C) = event_flags;
    }
    return;
create_item_effect:
    item_effect = func_80098CF8(action, position, sprite, &D_80081484);
    if (item_effect == NULL) {
        goto done;
    }
    M2C_FIELD(item_effect, s16 *, 0xCC) = 2;
    M2C_FIELD(action, s8 *, 0x9A) = 0x22;
    M2C_FIELD(action, u8 *, 0x9B) = 6U;
    return;
show_spawn_effect:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    if (func_8003DE58(M2C_FIELD(sprite, s32 *, 8), sprite, spawn_offset, 0) != 0) {
        goto place_spawn_effect;
    }
    spawn_offset[1] = 0;
    spawn_offset[0] = 0;
    spawn_offset[2] = 0 - D_800DDC40;
place_spawn_effect:
    func_800B8024(M2C_FIELD(position, s16 *, 2) + spawn_offset[0], M2C_FIELD(position, s16 *, 6) + spawn_offset[1], M2C_FIELD(position, s16 *, 0xA) + spawn_offset[2]);
    goto read_next_state;
spawn_creature:
    spawn_item = M2C_FIELD(action, u8 **, 0xC0);
    D_800E2968 = 1;
    creature_variant = func_800A1618(*spawn_item, 2);
    creature = func_800A0B94(*M2C_FIELD(action, u8 **, 0xC0), creature_variant, 1)(2, M2C_FIELD(sprite, u8 *, 0x24), M2C_FIELD(sprite, u8 *, 0x25), (s16) (M2C_FIELD(actor, u16 *, 0x88) - 0x20));
    if (creature == NULL) {
        goto done;
    }
    func_8003E188(M2C_FIELD(creature, u8 *, 0x13), 0);
    func_800A90E8(M2C_FIELD(action, u8 **, 0xC0));
    creature_sprite = M2C_FIELD(creature, void **, -0x14);
    func_8009A3D0(M2C_FIELD(creature_sprite, u8 *, 0x24), M2C_FIELD(creature_sprite, u8 *, 0x25), 0x300);
    if (func_8003DE58(M2C_FIELD(sprite, s32 *, 8), sprite, spawn_offset, 0) != 0) {
        goto place_creature;
    }
    spawn_offset[1] = 0;
    spawn_offset[0] = 0;
    spawn_offset[2] = 0 - D_800DDC40;
place_creature:
    creature_pos = M2C_FIELD(creature, void **, -0x18);
    M2C_FIELD(creature_pos, s16 *, 2) = (s16) ((u16) M2C_FIELD(position, s16 *, 2) + (u16) spawn_offset[0]);
    M2C_FIELD(creature_pos, s16 *, 6) = (s16) ((u16) M2C_FIELD(position, s16 *, 6) + (u16) spawn_offset[1]);
    spawn_height = (u16) M2C_FIELD(position, s16 *, 0xA) + (u16) spawn_offset[2];
    M2C_FIELD(creature_pos, s16 *, 0xA) = spawn_height;
    M2C_FIELD(creature, s16 *, 0x88) = spawn_height;
    M2C_FIELD(actor, void **, 0x60) = creature;
    func_80042640(creature, M2C_FIELD(creature, u8 *, 0x13));
    func_800424E0(creature, M2C_FIELD(creature, u8 *, 0x13), 0);
    M2C_FIELD(creature, u8 *, 0x43) = 0xFF;
    M2C_FIELD(creature, void **, 0x60) = actor;
    M2C_FIELD(creature, s32 *, 0x1C) = (s32) (M2C_FIELD(creature, s32 *, 0x1C) | 0x80000);
    M2C_FIELD(creature, s32 *, 0x14) = (s32) (M2C_FIELD(creature, s32 *, 0x14) | 0x104000);
    linked_creature = M2C_FIELD(actor, void **, 0x60);
    M2C_FIELD(linked_creature, u16 *, 0x98) = (u16) (M2C_FIELD(linked_creature, u16 *, 0x98) | 0xC);
    func_80069E78(creature + 0x34, func_8003C06C(M2C_FIELD(creature, u8 *, 0x13)));
    experience = D_800835E4[M2C_FIELD(D_800E3D7C, u8 *, 0x11)];
    level_thresholds = D_800835E4 + 1;
    M2C_FIELD(creature, u32 *, 0x18) = experience;
    if (experience < level_thresholds[M2C_FIELD(creature, u8 *, 0x11)]) {
        goto init_creature_stats;
    }
    level_table = level_thresholds;
level_up_creature:
    func_800A1D4C(creature, 0);
    if (level_table[M2C_FIELD(creature, u8 *, 0x11)] <= (u32) M2C_FIELD(creature, u32 *, 0x18)) {
        goto level_up_creature;
    }
init_creature_stats:
    M2C_FIELD(creature, u8 *, 0x28) = (u8) M2C_FIELD(creature, u8 *, 0x29);
    M2C_FIELD(creature, u8 *, 0x26) = (u8) M2C_FIELD(creature, u8 *, 0x68);
    M2C_FIELD(creature, u8 *, 0x27) = (u8) M2C_FIELD(creature, u8 *, 0x69);
    if (M2C_FIELD(&D_80013714, u16 *, 0) & 1) {
        goto build_spawn_message;
    }
    {
        u16 summon_count;
        u8 *summon_control;
        D_800DCF4F = 1;
        summon_control = (u8 *)&D_80083460;
        summon_count = M2C_FIELD(summon_control, u16 *, 0xA);
        M2C_FIELD(summon_control, u16 *, 0xA) = (u16) (summon_count + 1);
    }
build_spawn_message:
    message_start = func_800990FC();
    message_end = func_80099194(&D_800E0A33, func_80099734(creature, func_80099194(&D_800E0A2A, func_80099194(M2C_FIELD(((M2C_FIELD(creature, u8 *, 0x13) * 0x14) + D_8007359C), M2C_UNK **, 4), func_8009929C(8, message_start)))));
    if ((*(u16 *)&D_80013714) & 1) {
        goto show_spawn_message;
    }
    message_end = func_80099254(&D_800E0458, func_8009929C(0x4C, func_8009929C(0x11, message_end)));
show_spawn_message:
    func_80099290(message_end);
    func_800A5720(message_start);
    M2C_FIELD(action, u16 *, 0x96) = 0x20U;
    M2C_FIELD(action, u8 *, 0x9B) = (u8) (M2C_FIELD(action, u8 *, 0x9B) + 1);
    if ((*(u16 *)&D_80013714) & 1) {
        goto decrement_summon_count;
    }
    summon_state = &D_80083460;
    if ((s16) M2C_FIELD(summon_state, u16 *, 0xA) < 2) {
        goto done;
    }
    M2C_FIELD(summon_state, u16 *, 0xA) = (u16) (M2C_FIELD(summon_state, u16 *, 0xA) - 1);
    return;
decrement_summon_count:
    summon_state = &D_80083460;
    if (M2C_FIELD(summon_state, s16 *, 0xA) <= 0) {
        goto done;
    }
    M2C_FIELD(summon_state, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(summon_state, s16 *, 0xA) - 1);
    return;
wait_spawn:
    if (D_8008346A != 0) {
        goto done;
    }
    wait_timer = M2C_FIELD(action, u16 *, 0x96) - 1;
    M2C_FIELD(action, u16 *, 0x96) = wait_timer;
    anim_sprite = sprite;
    if ((wait_timer << 0x10) <= 0) {
        goto start_store_anim;
    }
    if (M2C_FIELD(sprite, u16 *, 0x14) & 0x8000) {
        goto start_store_anim;
    }
    if (M2C_FIELD(global_state, s32 *, 0x10) == 0) {
        goto done;
    }
start_store_anim:
    direction_base = D_800DD130;
    M2C_FIELD(anim_sprite, M2C_UNK **, 0x2C) = direction_base;
    direction_anim = (u8 *) ((u32) (((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7) + (u32) direction_base);
    copy_src = NULL;
    goto play_direction_anim;
save_creature:
    if (!(M2C_FIELD(sprite, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    M2C_FIELD(sprite, u8 **, 0x2C) = D_800DD138;
    func_80048A44(sprite, D_800DD138[((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) | 0x200);
    func_80093C70(action, position, sprite);
    func_80093D8C(action, position, sprite);
    save_slot = func_80099090();
    item_entry = D_80010000_PTR->table[M2C_FIELD(actor, s16 *, 0x8A)];
    M2C_FIELD(item_entry, s8 *, 1) = 0x13;
    species = (u8) *M2C_FIELD(action, u8 **, 0xC0);
    M2C_FIELD(item_entry, s8 *, 3) = save_slot;
    M2C_FIELD(item_entry, s8 *, 2) = 0;
    M2C_FIELD(item_entry, u8 *, 0) = species;
    D_800E3DF0[save_slot] = save_data = (save_slot * 0x8C) + D_800E3E48;
    copy_src = M2C_FIELD(actor, void **, 0x60);
    copy_dst = save_data;
    copy_end = copy_src + 0x80;
copy_creature:
    *(Copy16 *)copy_dst = *(Copy16 *)copy_src;
    copy_src += 0x10;
    copy_dst += 0x10;
    if (copy_src != copy_end) {
        goto copy_creature;
    }
    ASM_KEEP_NV(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    *(Copy12 *)copy_dst = *(Copy12 *)copy_src;
    stored_creature = M2C_FIELD(actor, void **, 0x60);
    M2C_FIELD(stored_creature, s32 *, 0x1C) = (s32) (M2C_FIELD(stored_creature, s32 *, 0x1C) | 0x400000);
    hidden_creature = M2C_FIELD(actor, void **, 0x60);
    M2C_FIELD(hidden_creature, s32 *, 0x14) = (s32) (M2C_FIELD(hidden_creature, s32 *, 0x14) & 0xFFEFFFFF);
    func_800A56E0(0x704);
    goto read_next_state;
finish_creature:
    finished_creature = M2C_FIELD(actor, void **, 0x60);
    if (!(M2C_FIELD(finished_creature, s32 *, 0x1C) & 0x800000)) {
        goto done;
    }
    func_8009A028(finished_creature);
    copy_src = NULL;
    item_entry = D_80010000_PTR->table[M2C_FIELD(actor, s16 *, 0x8A)];
    saved_creature = D_800E3DF0[M2C_FIELD(item_entry, u8 *, 3) & 0x1F];
    M2C_FIELD(saved_creature, s32 *, 0x14) = (s32) (M2C_FIELD(saved_creature, s32 *, 0x14) & ~0x4000);
    release_value = M2C_FIELD(actor, void **, 0x60);
    {
        u8 *flags_page;
        flags_page = (u8 *)0x80080000;
        M2C_FIELD(release_value, u16 *, -2) = (u16) (M2C_FIELD(release_value, u16 *, -2) | 0x8000);
        release_value = (void *) M2C_FIELD(flags_page, s32 *, 0x14A0);
        release_value = (void *) ((s32) release_value | 0x8000);
        direction_base = D_800DD140;
        anim_sprite = sprite;
        M2C_FIELD(anim_sprite, u8 **, 0x2C) = direction_base;
        direction_anim = direction_base + (((s32) (D_80083228 + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7);
        M2C_FIELD(flags_page, s32 *, 0x14A0) = (s32) release_value;
    }
play_direction_anim:
    func_80048A44(anim_sprite, *direction_anim, copy_src, 1);
read_next_state:
    next_state = M2C_FIELD(action, u8 *, 0x9B);
advance_state:
    M2C_FIELD(action, u8 *, 0x9B) = (u8) (next_state + 1);
    return;
restore_idle:
    final_flags = M2C_FIELD(sprite, u16 *, 0x14);
    if (!(final_flags & 0xE000)) {
        goto done;
    }
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (final_flags & 0xFDFF);
    M2C_FIELD(action, M2C_UNK **, 0x8C) = &D_8008ACDC;
    ASM_USE2(action, action);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
done:
    return;
}
