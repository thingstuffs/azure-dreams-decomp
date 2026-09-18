#include "common.h"
typedef long long s64;
typedef s32 M2C_UNK;

typedef struct S_func_81008664_1 {
    u8 pad_00[0x8C];
    M2C_UNK *unk_8C;
    union {
        s32 unk_90;
        struct {
            u8 pad_90[2];
            u16 unk_92;
        } unk_92;
    } unk_90;
    u8 pad_94[2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    void *unk_A8;
    s32 unk_AC;
} S_func_81008664_1;
typedef struct S_func_81008664_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[8];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_func_81008664_2;
typedef struct S_func_81008664_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_func_81008664_3;
typedef struct S_func_81008664_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[5];
    u8 *unk_2C;
} S_func_81008664_4;
typedef struct S_func_81008664_5 {
    s32 unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        struct {
            u8 pad_08[2];
            u16 unk_0A;
        } unk_0A;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81008664_5;
typedef struct S_func_81008664_6 {
    void *unk_00;
    void *unk_04;
} S_func_81008664_6;
typedef struct S_func_81008664_7 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_func_81008664_7;
typedef struct S_func_81008664_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_81008664_8;
typedef struct S_func_81008664_9 {
    u8 unk_00;
} S_func_81008664_9;
typedef struct S_func_81008664_10 {
    s16 unk_00;
} S_func_81008664_10;
typedef struct S_func_81008664_11 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    union {
        s32 unk_90;
        struct {
            u8 pad_90[2];
            u16 unk_92;
        } unk_92;
    } unk_90;
    u8 pad_94[4];
    u16 unk_98;
} S_func_81008664_11;
typedef struct S_func_81008664_12 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_func_81008664_12;


extern void *const D_80170878[];
void func_80047784();
void func_8009A21C();
s32 func_8009A2B8();
void func_8009A3D0();
s32 func_800A4ACC();
s32 func_800A4E2C();
s32 func_800A56E0();
void func_800AA53C();
void func_800AD594();
s16 func_800BCB04();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_8008146E;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_800DDC40[];
extern M2C_UNK D_80171058;
extern u8 D_80174888[];
extern u8 D_801748F0[];
extern u8 D_801748F8[];

/* Updates paired actor movement, tile placement, animations, and restored flags. */
void func_81008664(void *actor_arg, void *motion_arg, void *sprite_arg, void *volatile entity) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    struct {
        void *sp10;
        s16 sp14;
        s16 sp16;
        s32 sp18;
        u8 *sp1C;
    } locals;
    M2C_UNK partner_tile_mask;
    M2C_UNK tile_mask;
    M2C_UNK restore_tile_mask;
    M2C_UNK restore_partner_mask;
    s16 launch_ticks;
    s16 fall_ticks;
    s32 tile_type;
    s16 landing_height;
    s16 rise_ticks;
    s16 return_ticks;
    s32 step_offset;
    s32 direction;
    register s32 search_step_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 tile_blocked;
    s32 reverse_angle;
    register s32 attempts ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 partner_height;
    u32 state;
    u32 angle;
    u32 partner_flags;
    u32 entity_flags;
    u32 actor_flags;
    u32 clear_mask;
    u32 cleared_flags;
    u32 sprite_grounded;
    u32 partner_x;
    u32 partner_y;
    u32 sprite_x;
    u32 sprite_y;
    s32 launch_duration;
    s32 x_velocity;
    s32 y_velocity;
    u8 *x_step_table;
    u8 *y_step_table;
    s16 *y_step_ptr;
    u32 final_x;
    u32 final_y;
    void *reset_entity;
    void *finish_entity;
    u32 saved_handler;
    M2C_UNK *next_handler;
    S_func_81008664_8 *dungeon_state;
    u32 active_count;
    register u32 height_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 height_offset;
    s32 entity_height;
    u32 height_adjust;
    u8 *search_x_steps;
    u32 y_step_value;
    u32 landing_y;
    u32 landing_x;
    s32 world_coord;
    u8 next_state;
    register u8 *animation_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u32 launch_anim;
    u32 fall_anim;
    u32 rise_anim;
    u32 idle_anim;
    s16 *angle_or_count;
    void *tile_x_ptr;
    S_func_81008664_4 *partner_sprite;
    register S_func_81008664_2 *partner ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register S_func_81008664_11 *partner_actor ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_func_81008664_1 *actor = actor_arg;
    S_func_81008664_5 *motion = motion_arg;
    register S_func_81008664_4 *sprite = sprite_arg;

    partner = actor->unk_A8;
    ASM_KEEP(partner);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state = actor->unk_9B;
    ASM_KEEP_NV(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    partner_actor = (S_func_81008664_11 *) partner;
    partner_sprite = ((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_04;
    search_step_offset = (s32)(((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_00);
    locals.sp10 = (S_func_81008664_5 *)search_step_offset;
    if (state >= 5U) {
        goto done;
    }
    (void) state_labels;
    goto *D_80170878[state];
jt_c0:
    actor->unk_AC = (s32) partner_actor->unk_8C;
    if (partner->unk_1C & 0x40000) {
        actor->unk_98 = (u16) (actor->unk_98 | 0x1000);
    } else {
        actor->unk_98 = (u16) (actor->unk_98 & 0xEFFF);
    }
    if (partner_actor->unk_98 & 8) {
        actor->unk_98 = (u16) (actor->unk_98 | 0x4000);
    } else {
        actor->unk_98 = (u16) (actor->unk_98 & 0xBFFF);
    }
    if (partner_actor->unk_98 & 4) {
        actor->unk_98 = (u16) (actor->unk_98 | 0x2000);
        partner_actor->unk_8C = 0;
        partner_flags = partner->unk_1C;
        partner_sprite = ((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_04;
    } else {
        actor->unk_98 = (u16) (actor->unk_98 & 0xDFFF);
        partner_actor->unk_8C = 0;
        partner_flags = partner->unk_1C;
        partner_sprite = ((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_04;
    }
    partner_flags &= 0x2000;
    partner_x = partner_sprite->unk_24;
    partner_y = partner_sprite->unk_25;
    partner_tile_mask = 0x3000;
    if (!partner_flags) {
        goto clear_partner_tile;
    }
    partner_tile_mask = 0x300;
clear_partner_tile:
    func_8009A3D0(partner_x, partner_y, partner_tile_mask);
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    ASM_KEEP_NV(search_step_offset);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    sprite_x = sprite->unk_24;
    ASM_KEEP_NV(sprite_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    entity_flags = ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C;
    entity_flags &= 0x2000;
    tile_mask = 0x3000;
    sprite_y = sprite->unk_25;
    if (!entity_flags) {
        goto clear_sprite_tile;
    }
    tile_mask = 0x300;
clear_sprite_tile:
    func_8009A3D0(sprite_x, sprite_y, tile_mask);
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    clear_mask = 0xFFFB0000;
    cleared_flags = ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C;
    clear_mask |= 0xFFFF;
    cleared_flags &= clear_mask;
    ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C = cleared_flags;
    actor_flags = (*(u16 *)((u8 *)actor + 0x98));
    ASM_KEEP(actor_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    angle = ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A;
    ASM_KEEP_NV(angle);
    actor_flags |= 0xC;
    angle >>= 9;
    actor->unk_98 = actor_flags;
    sprite_grounded = sprite->unk_14;
    sprite_grounded &= 0x8000;
    direction = angle & 7;
    if (!sprite_grounded) {
        goto start_launch;
    }
    if (!(partner_sprite->unk_14 & 0x8000)) {
        goto start_launch;
    }
    next_state = 2;
    actor->unk_96 = 0;
    goto store_state;
start_launch:
    actor->unk_96 = 0xC;
    ASM_SCHED_BARRIER();
    x_step_table = D_8006CCD8;
    step_offset = direction * 2;
    x_step_table = (u8 *) (step_offset + (u32) x_step_table);
    x_velocity = * (s16 *) x_step_table;
    launch_duration = 0xC;
    x_velocity <<= 0x16;
    x_velocity = x_velocity / launch_duration;
    motion->unk_0C = x_velocity;
    y_step_table = D_8006CCE8;
    y_step_ptr = (s16 *) (step_offset + (u32) y_step_table);
    y_velocity = *y_step_ptr;
    y_velocity <<= 0x16;
    y_velocity = y_velocity / (s16) actor->unk_96;
    motion->unk_14 = 0;
    motion->unk_10 = y_velocity;
    partner->unk_1C = (s32) (partner->unk_1C & 0xFFFBFFFF);
    partner_actor->unk_98 = (u16) (partner_actor->unk_98 | 0xC);
    animation_table = D_801748F0;
    angle_or_count = &D_80083228;
    *(u8 **)((u8 *)sprite + 0x2C) = animation_table;
    {
        u32 anim_flags;

        search_step_offset = (s32)((S_func_81008664_5 *)(entity));
        launch_anim = (s16) *angle_or_count;
        angle = (s16) ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A;
        anim_flags = 0;
        launch_anim = ((s32) (launch_anim + angle + 0x100) >> 9) & 7;
        launch_anim = launch_anim + (u32) animation_table;
        func_80047784(sprite, (*(u8 *)((u8 *)launch_anim + 0)), anim_flags);
    }
    actor->unk_9B = (u8) (actor->unk_9B + 1);
jt_c1:
    launch_ticks = (u16) actor->unk_96 - 1;
    actor->unk_96 = launch_ticks;
    if (launch_ticks != 8) {
        goto check_launch_end;
    }
    height_value = (u32) D_800DDC40;
    height_offset = partner->unk_13;
    search_step_offset = (s32)((u32) locals.sp10);
    height_offset += height_value;
    height_value = ((S_func_81008664_12 *) (u32)search_step_offset)->unk_0A;
    search_step_offset = (s32)((u32) entity);
    entity_height = (*(s16 *)((u8 *)(u32)search_step_offset + 0x88));
    height_offset = ((S_func_81008664_9 *) height_offset)->unk_00;
    motion->unk_14 = (s32) ((s32) ((((height_value - entity_height) - height_offset) + 0x10) << 0x10) / launch_ticks);
    partner_actor->unk_90.unk_92.unk_92 = (u16) (partner_actor->unk_90.unk_92.unk_92 + partner->unk_88);
    partner->unk_88 = 0U;
check_launch_end:
    if (actor->unk_96 > 0) {
        goto done;
    }
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    motion->unk_14 = -0x40000;
    func_800A56E0(0x802, launch_ticks);
    {
        s32 fall_duration;
        fall_duration = 0x10;
        ASM_KEEP_NV(fall_duration);
        animation_table = D_801748F8;
        actor->unk_96 = fall_duration;
    }
    angle_or_count = &D_80083228;
    *(u8 **)((u8 *)sprite + 0x2C) = animation_table;
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    fall_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A + 0x100) >> 9) & 7;
    fall_anim = fall_anim + (u32) animation_table;
    func_80047784(sprite, ((S_func_81008664_9 *) fall_anim)->unk_00, 0);
    goto advance_state;
restore_tile:
    search_step_offset = (s32)((u8) locals.sp14);
    partner_sprite->unk_24 = (u32)search_step_offset;
    search_step_offset = (s32)((u8) locals.sp16);
    partner_sprite->unk_25 = (u32)search_step_offset;
    goto place_actors;
jt_c2:
    motion->unk_14 = (s32) (motion->unk_14 + 0xFFFE0000);
    height_adjust = D_800DDC40[partner->unk_13];
    partner_actor->unk_90.unk_92.unk_92 = (u16) ((motion->unk_08.unk_0A.unk_0A + height_adjust) - 0x10);
    fall_ticks = (u16) actor->unk_96 - 1;
    actor->unk_96 = fall_ticks;
    if ((fall_ticks << 0x10) <= 0) {
        goto prepare_tile_search;
    }
    if (!(partner_sprite->unk_14 & 0x8000)) {
        goto done;
    }
prepare_tile_search:
    search_step_offset = (s32)(partner_sprite->unk_24);
    ASM_KEEP_NV(search_step_offset);
    locals.sp14 = (s16) (u32)search_step_offset;
    search_step_offset = (s32)(entity);
    ASM_KEEP_NV(search_step_offset);
    attempts = 0x40;
    ASM_KEEP(attempts);
    reverse_angle = (s16) ((S_func_81008664_3 *)search_step_offset)->unk_2A;
    search_step_offset = (s32)(partner_sprite->unk_25);
    reverse_angle = (reverse_angle + 0x800) & 0xFFF;
    direction = reverse_angle >> 9;
    ASM_KEEP(direction);
    search_x_steps = D_8006CCD8;
    locals.sp16 = (s16) (u32)search_step_offset;
    search_step_offset = direction * 2;
    locals.sp18 = search_step_offset;
    search_x_steps = (u8 *) (search_step_offset + (u32) search_x_steps);
    locals.sp1C = search_x_steps;
    ASM_SCHED_BARRIER();
search_tile:
    attempts -= 1;
check_attempts: do {
    tile_x_ptr = &partner_sprite->unk_24;
    if (attempts <= 0) {
        goto restore_tile;
    }
    tile_type = (s16) func_800A4E2C(tile_x_ptr, &partner_sprite->unk_25);
    attempts -= 1;
    if (tile_type < 0) {
        goto check_attempts;
    }
    attempts += 1;
    ASM_KEEP(attempts);
    search_step_offset = (s32)((u32)((S_func_81008664_7 *) D_80082E80));
    ASM_KEEP_NV(search_step_offset);
    if (tile_type != ((S_func_81008664_7 *)(u32)search_step_offset)->unk_26) {
        goto check_tile_path;
    }
    angle_or_count = &D_8008146E;
    attempts -= 1;
    if (*angle_or_count >= 2) {
        goto check_attempts;
    }
    attempts += 1;
check_tile_path:
    tile_blocked = func_8009A2B8(partner_sprite->unk_24, partner_sprite->unk_25, direction);
    attempts -= 1;
    if ((tile_blocked << 0x10) != 0) {
        goto check_attempts;
    }
    attempts += 1;
    ASM_KEEP(attempts);
    partner_sprite->unk_26 = (s8) tile_type;
    sprite->unk_26 = (s8) tile_type;
    search_step_offset = (s32)((u32)(locals.sp1C));
    sprite->unk_24 = (u8) (partner_sprite->unk_24 + *(u8 *)(u32)search_step_offset);
    ASM_SCHED_BARRIER();
    y_step_value = (u32) D_8006CCE8;
    search_step_offset = (s32)((u32)((u8 *)((u32) locals.sp18)));
    ASM_KEEP_NV(search_step_offset);
    landing_y = partner_sprite->unk_25;
    ASM_KEEP_NV(landing_y);
    landing_x = sprite->unk_24;
    ASM_KEEP_NV(landing_x);
    y_step_value = (u32)(u8 *)(u32)search_step_offset + y_step_value;
    landing_x <<= 6;
    y_step_value = ((S_func_81008664_9 *) y_step_value)->unk_00;
    landing_x |= 0x20;
    landing_y += y_step_value;
    sprite->unk_25 = (u8) landing_y;
    landing_height = func_800BCB04(landing_x, (sprite->unk_25 << 6) | 0x20, (s16) (motion->unk_08.unk_0A.unk_0A - 0x80));
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_88 = landing_height;
    attempts -= 1;
    if (landing_height >= 0x201) {
        goto check_attempts;
    }
    attempts += 1;
    partner_height = func_800BCB04((partner_sprite->unk_24 << 6) | 0x20, (partner_sprite->unk_25 << 6) | 0x20, (s16) (motion->unk_08.unk_0A.unk_0A - 0x80));
    partner->unk_88 = partner_height;
    attempts -= 1;
    if ((s16) partner_height >= 0x201) {
        goto check_attempts;
    }
    attempts += 1;
    ASM_KEEP(attempts);
    attempts -= 1;
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    } while (((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_88 != (s16) partner_height);
place_actors:
    world_coord = partner_sprite->unk_24;
    search_step_offset = (s32)(locals.sp10);
    world_coord = ((world_coord << 6) + 0x20) << 0x10;
    ((S_func_81008664_5 *)search_step_offset)->unk_00 = world_coord;
    motion->unk_00 = world_coord;
    world_coord = partner_sprite->unk_25;
    world_coord = ((world_coord << 6) + 0x20) << 0x10;
    ((S_func_81008664_5 *)search_step_offset)->unk_04 = world_coord;
    motion->unk_04 = world_coord;
    motion->unk_08.unk_08 = (s32) (((s16) partner->unk_88 - 0x100) << 0x10);
    partner_actor->unk_90.unk_90 = (s32) actor->unk_90.unk_90;
    *(s16 *)((u8 *)actor + 0x96) = 8;
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    motion->unk_14 = (s32) ((s32) ((((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_88 << 0x10) - motion->unk_08.unk_08) / (s16) actor->unk_96);
    animation_table = D_801748F8;
    angle_or_count = &D_80083228;
    *(u8 **)((u8 *)sprite + 0x2C) = animation_table;
    rise_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A + 0x100) >> 9) & 7;
    rise_anim = rise_anim + (u32) animation_table;
    func_80047784(sprite, ((S_func_81008664_9 *) rise_anim)->unk_00, 0);
    func_800AA53C(entity);
    func_800AA53C(partner);
    goto advance_state;
jt_c3:
    partner_actor->unk_90.unk_92.unk_92 = (u16) (actor->unk_90.unk_92.unk_92 + 0x40);
    if ((s16) actor->unk_90.unk_92.unk_92 >= 0) {
        goto start_return;
    }
    rise_ticks = (u16) actor->unk_96 - 1;
    actor->unk_96 = rise_ticks;
    if ((rise_ticks << 0x10) > 0) {
        goto done;
    }
    if (!(sprite->unk_14 & 0x8000)) {
        goto done;
    }
start_return:
    actor->unk_90.unk_90 = 0;
    partner_actor->unk_90.unk_90 = 0;
    if (!(actor->unk_98 & 0x1000)) {
        goto restore_partner_flags;
    }
    partner->unk_1C = (s32) (partner->unk_1C | 0x40000);
restore_partner_flags:
    if (actor->unk_98 & 0x4000) {
        goto restore_partner_flag;
    }
    partner_actor->unk_98 = (u16) (partner_actor->unk_98 & 0xFFF7);
restore_partner_flag:
    if (actor->unk_98 & 0x2000) {
        goto set_return_motion;
    }
    partner_actor->unk_98 = (u16) (partner_actor->unk_98 & 0xFFFB);
set_return_motion:
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C = (s32) (((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C | 0x40000000);
    partner->unk_1C = (s32) (partner->unk_1C | 0x40000000);
    {
        s16 angle_or_duration;
        s32 return_step_offset;

        angle_or_duration = ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A;
        height_value = (u32)(8);
        motion->unk_14 = 0;
        actor->unk_96 = (s32)height_value;
        height_value = (u32)((u32) D_8006CCD8);
        direction = angle_or_duration >> 8;
        return_step_offset = direction & 0xE;
        height_value = (u32)(return_step_offset + (s32)height_value);
        height_value = (u32)(((S_func_81008664_10 *) (s32)height_value)->unk_00);
        angle_or_duration = 8;
        height_value = (u32)(((s32)height_value) << (0x16));
        height_value = (u32)(0 - (s32)height_value);
        height_value = (u32)(((s32)height_value) / ((s32) angle_or_duration));
        motion->unk_0C = (s32)height_value;
        height_value = (u32)((u32) D_8006CCE8);
        return_step_offset += (s32)height_value;
        height_value = (u32)(((S_func_81008664_10 *) return_step_offset)->unk_00);
        angle_or_duration = actor->unk_96;
        height_value = (u32)(((s32)height_value) << (0x16));
        height_value = (u32)(0 - (s32)height_value);
        height_value = (u32)(((s32)height_value) / ((s32) angle_or_duration));
        motion->unk_10 = (s32)height_value;
        search_step_offset = (s32)((S_func_81008664_5 *)((S_func_81008664_3 *)((u32) locals.sp10)));
        ((S_func_81008664_5 *) (u32)(S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_14 = 0;
        motion->unk_14 = 0;
        goto advance_state;
    }
jt_c4:
    return_ticks = (u16) actor->unk_96 - 1;
    actor->unk_96 = return_ticks;
    if ((return_ticks << 0x10) <= 0) {
        goto finish_movement;
    }
    if (!(partner_sprite->unk_14 & 0x8000)) {
        goto done;
    }
finish_movement:
    final_x = sprite->unk_24;
    final_x = ((final_x << 6) + 0x20) << 0x10;
    motion->unk_00 = final_x;
    final_y = sprite->unk_25;
    reset_entity = entity;
    *(s32 *)((u8 *)motion + 0x10) = 0;
    motion->unk_0C = 0;
    final_y = ((final_y << 6) + 0x20) << 0x10;
    motion->unk_04 = final_y;
    saved_handler = actor->unk_AC;
    partner_actor->unk_8C = saved_handler;
    func_800AD594(reset_entity, 0x100);
    next_handler = &D_80171058;
    dungeon_state = (S_func_81008664_8 *) D_80083460;
    actor->unk_8C = next_handler;
    active_count = dungeon_state->unk_0A;
    finish_entity = entity;
    active_count -= 1;
    dungeon_state->unk_0A = active_count;
    func_800A4ACC(finish_entity);
    *(u16 *)((u8 *)actor + 0x98) = (u16) (actor->unk_98 & 0xFFF3);
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));

    {
        u32 restore_flags;
        u32 restore_mask;
        u32 restore_x;
        u32 restore_y;

        restore_flags = ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C;
        restore_mask = 0x40000;
        restore_flags |= restore_mask;
        ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_1C = restore_flags;
        restore_flags &= 0x2000;
        restore_x = sprite->unk_24;
        restore_y = sprite->unk_25;
        restore_tile_mask = 0x3000;
        if (!restore_flags) {
            goto restore_sprite_tile;
        }
        restore_tile_mask = 0x300;
restore_sprite_tile:
        func_8009A21C(restore_x, restore_y, restore_tile_mask);
    }
    {
        u32 restore_flags;
        u32 restore_x;
        u32 restore_y;

        restore_flags = partner->unk_1C;
        restore_x = (*(u8 *)((u8 *)partner_sprite + 0x24));
        restore_y = partner_sprite->unk_25;
        restore_flags &= 0x2000;
        restore_partner_mask = 0x3000;
        if (!restore_flags) {
            goto restore_partner_tile;
        }
        restore_partner_mask = 0x300;
restore_partner_tile:
        func_8009A21C(restore_x, restore_y, restore_partner_mask);
    }
    animation_table = D_80174888;
    angle_or_count = &D_80083228;
    *(u8 **)((u8 *)sprite + 0x2C) = animation_table;
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    idle_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_2A + 0x100) >> 9) & 7;
    idle_anim = idle_anim + (u32) animation_table;
    func_80047784(sprite, ((S_func_81008664_9 *) idle_anim)->unk_00, 0);
    search_step_offset = (s32)((S_func_81008664_5 *)(entity));
    ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_6D = 0;
    ((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_46 = (u16) (((S_func_81008664_3 *)(S_func_81008664_5 *)search_step_offset)->unk_46 & 0x7FFF);
advance_state:
    next_state = actor->unk_9B + 1;
store_state:
    actor->unk_9B = next_state;
done:
    return;
}
