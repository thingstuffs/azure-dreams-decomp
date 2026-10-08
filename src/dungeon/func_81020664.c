#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
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
extern s16 D_8008146E;
extern M2C_UNK D_80159058;
extern u8 D_8015C888[];
extern u8 D_8015C8F0[];
extern u8 D_8015C8F8[];

/* Updates paired actor movement, tile placement, animations, and restored flags. */
void func_8015BE64(S_func_81008664_1 *actor, S_func_81008664_5 *motion, S_func_81008664_4 *sprite, void *entity) {
    S_func_81008664_5 *partner_motion;
    s16 saved_x;
    s16 saved_y;
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
    s32 tile_blocked;
    s32 reverse_angle;
    s32 attempts;
    u16 partner_height;
    u32 state;
    u32 angle;
    u32 partner_flags;
    u32 entity_flags;
    u32 actor_flags;
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
    u32 active_count;
    u32 height_value;
    u32 height_offset;
    s32 entity_height;
    u32 height_adjust;
    s32 world_coord;
    u8 *anim_table0;
    u8 *anim_table1;
    u8 *anim_table2;
    u8 *anim_table3;
    u32 launch_anim;
    u32 fall_anim;
    u32 rise_anim;
    u32 idle_anim;
    s16 *angle_or_count;
    void *tile_x_ptr;
    S_func_81008664_4 *partner_sprite;
    S_func_81008664_2 *partner;
    S_func_81008664_11 *partner_actor;

    partner = actor->unk_A8;
    state = actor->unk_9B;
    partner_actor = (S_func_81008664_11 *) partner;
    partner_motion = ((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_00;
    partner_sprite = ((S_func_81008664_6 *) ((u8 *) partner - 0x18))->unk_04;
    switch (state) {
    case 0:
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
        if (partner_flags) {
            partner_tile_mask = 0x300;
        }
        func_8009A3D0(partner_x, partner_y, partner_tile_mask);
        sprite_x = sprite->unk_24;
        entity_flags = ((S_func_81008664_3 *)entity)->unk_1C;
        entity_flags &= 0x2000;
        tile_mask = 0x3000;
        sprite_y = sprite->unk_25;
        if (entity_flags) {
            tile_mask = 0x300;
        }
        func_8009A3D0(sprite_x, sprite_y, tile_mask);
        angle = 0xFFFB0000;
        cleared_flags = ((S_func_81008664_3 *)entity)->unk_1C;
        angle |= 0xFFFF;
        cleared_flags &= angle;
        ((S_func_81008664_3 *)entity)->unk_1C = cleared_flags;
        actor_flags = (*(u16 *)((u8 *)actor + 0x98));
        angle = ((S_func_81008664_3 *)entity)->unk_2A;
        actor_flags |= 0xC;
        angle >>= 9;
        actor->unk_98 = actor_flags;
        sprite_grounded = sprite->unk_14;
        sprite_grounded &= 0x8000;
        direction = angle & 7;
        if (!sprite_grounded) {
            actor->unk_96 = 0xC;
        } else if (!(partner_sprite->unk_14 & 0x8000)) {
            actor->unk_96 = 0xC;
        } else {
            actor->unk_96 = 0;
            actor->unk_9B = 2;
            return;
        }
        x_step_table = ((u8 *)dirStepX);
        step_offset = direction * 2;
        x_step_table = (u8 *) (step_offset + (u32) x_step_table);
        x_velocity = * (s16 *) x_step_table;
        launch_duration = 0xC;
        x_velocity <<= 0x16;
        x_velocity = x_velocity / launch_duration;
        motion->unk_0C = x_velocity;
        y_step_table = ((u8 *)dirStepY);
        y_step_ptr = (s16 *) (step_offset + (u32) y_step_table);
        y_velocity = *y_step_ptr;
        y_velocity <<= 0x16;
        y_velocity = y_velocity / (s16) actor->unk_96;
        motion->unk_14 = 0;
        motion->unk_10 = y_velocity;
        partner->unk_1C = (s32) (partner->unk_1C & 0xFFFBFFFF);
        partner_actor->unk_98 = (u16) (partner_actor->unk_98 | 0xC);
        anim_table0 = D_8015C8F0;
        angle_or_count = &gameWork.view.viewAngle;
        *(u8 **)((u8 *)sprite + 0x2C) = anim_table0;
        launch_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)entity)->unk_2A + 0x100) >> 9) & 7;
        launch_anim = launch_anim + (u32) anim_table0;
        func_80047784(sprite, ((S_func_81008664_9 *) launch_anim)->unk_00, 0);
        actor->unk_9B = (u8) (actor->unk_9B + 1);
    case 1:
        launch_ticks = (u16) actor->unk_96 - 1;
        actor->unk_96 = launch_ticks;
        if (launch_ticks == 8) {
            height_offset = D_800DDC40[partner->unk_13];
            height_value = ((S_func_81008664_12 *) partner_motion)->unk_0A;
            entity_height = (*(s16 *)((u8 *)entity + 0x88));
            motion->unk_14 = (s32) ((s32) ((((height_value - entity_height) - height_offset) + 0x10)
                << 0x10) / launch_ticks);
            partner_actor->unk_90.unk_92.unk_92 = (u16) (partner_actor->unk_90.unk_92.unk_92 + partner->unk_88);
            partner->unk_88 = 0U;
        }
        if (actor->unk_96 > 0) {
            return;
        }
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        motion->unk_14 = -0x40000;
        func_800A56E0(0x802);
        {
            fall_anim = 0x10;
            anim_table1 = D_8015C8F8;
            actor->unk_96 = fall_anim;
        }
        angle_or_count = &gameWork.view.viewAngle;
        *(u8 **)((u8 *)sprite + 0x2C) = anim_table1;
        fall_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)entity)->unk_2A + 0x100) >> 9) & 7;
        fall_anim = fall_anim + (u32) anim_table1;
        func_80047784(sprite, ((S_func_81008664_9 *) fall_anim)->unk_00, 0);
        actor->unk_9B = actor->unk_9B + 1;
        return;
    case 2:
        motion->unk_14 = (s32) (motion->unk_14 + 0xFFFE0000);
        height_adjust = D_800DDC40[partner->unk_13];
        partner_actor->unk_90.unk_92.unk_92 = (u16) ((motion->unk_08.unk_0A.unk_0A + height_adjust) - 0x10);
        fall_ticks = (u16) actor->unk_96 - 1;
        actor->unk_96 = fall_ticks;
        if ((fall_ticks << 0x10) > 0) {
            if (!(partner_sprite->unk_14 & 0x8000)) {
                return;
            }
        }
        saved_x = partner_sprite->unk_24;
        attempts = 0x40;
        reverse_angle = (s16) ((S_func_81008664_3 *)entity)->unk_2A;
        saved_y = partner_sprite->unk_25;
        reverse_angle = (reverse_angle + 0x800) & 0xFFF;
        direction = reverse_angle >> 9;
        for (;;) {
            attempts -= 1;
            tile_x_ptr = &partner_sprite->unk_24;
            if (attempts <= 0) {
                partner_sprite->unk_24 = saved_x;
                partner_sprite->unk_25 = saved_y;
                goto place_actors;
            }
            tile_type = (s16) func_800A4E2C(tile_x_ptr, &partner_sprite->unk_25);
            if (tile_type < 0) {
                continue;
            }
            if (tile_type == D_80082E80.unk_026) {
                angle_or_count = &D_8008146E;
                if (*angle_or_count >= 2) {
                    continue;
                }
            }
            tile_blocked = func_8009A2B8(partner_sprite->unk_24, partner_sprite->unk_25, direction);
            if ((tile_blocked << 0x10) != 0) {
                continue;
            }
            partner_sprite->unk_26 = (s8) tile_type;
            sprite->unk_26 = (s8) tile_type;
            sprite->unk_24 = partner_sprite->unk_24 + dirStepX[direction];
            sprite->unk_25 = partner_sprite->unk_25 + dirStepY[direction];
            landing_height = func_800BCB04((sprite->unk_24 << 6) | 0x20, (sprite->unk_25 << 6) | 0x20,
                (s16) (motion->unk_08.unk_0A.unk_0A - 0x80));
            ((S_func_81008664_3 *)entity)->unk_88 = landing_height;
            if (landing_height >= 0x201) {
                continue;
            }
            partner_height = func_800BCB04((partner_sprite->unk_24 << 6) | 0x20, (partner_sprite->unk_25 << 6) | 0x20,
                (s16) (motion->unk_08.unk_0A.unk_0A - 0x80));
            partner->unk_88 = partner_height;
            if ((s16) partner_height >= 0x201) {
                continue;
            }
            if (((S_func_81008664_3 *)entity)->unk_88 == (s16) partner_height) {
                break;
            }
        }
place_actors:
        world_coord = partner_sprite->unk_24;
        world_coord = ((world_coord << 6) + 0x20) << 0x10;
        partner_motion->unk_00 = world_coord;
        motion->unk_00 = world_coord;
        world_coord = partner_sprite->unk_25;
        world_coord = ((world_coord << 6) + 0x20) << 0x10;
        partner_motion->unk_04 = world_coord;
        motion->unk_04 = world_coord;
        motion->unk_08.unk_08 = (s32) (((s16) partner->unk_88 - 0x100) << 0x10);
        partner_actor->unk_90.unk_90 = (s32) actor->unk_90.unk_90;
        *(s16 *)((u8 *)actor + 0x96) = 8;
        motion->unk_14 = (s32) ((s32) ((((S_func_81008664_3 *)entity)->unk_88 << 0x10)
            - motion->unk_08.unk_08) / (s16) actor->unk_96);
        anim_table2 = D_8015C8F8;
        angle_or_count = &gameWork.view.viewAngle;
        *(u8 **)((u8 *)sprite + 0x2C) = anim_table2;
        rise_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)entity)->unk_2A + 0x100) >> 9) & 7;
        rise_anim = rise_anim + (u32) anim_table2;
        func_80047784(sprite, ((S_func_81008664_9 *) rise_anim)->unk_00, 0);
        func_800AA53C(entity);
        func_800AA53C(partner);
        actor->unk_9B = actor->unk_9B + 1;
        return;
    case 3:
        partner_actor->unk_90.unk_92.unk_92 = (u16) (actor->unk_90.unk_92.unk_92 + 0x40);
        if ((s16) actor->unk_90.unk_92.unk_92 < 0) {
            rise_ticks = (u16) actor->unk_96 - 1;
            actor->unk_96 = rise_ticks;
            if ((rise_ticks << 0x10) > 0) {
                return;
            }
            if (!(sprite->unk_14 & 0x8000)) {
                return;
            }
        }
        actor->unk_90.unk_90 = 0;
        partner_actor->unk_90.unk_90 = 0;
        if (actor->unk_98 & 0x1000) {
            partner->unk_1C = (s32) (partner->unk_1C | 0x40000);
        }
        if (!(actor->unk_98 & 0x4000)) {
            partner_actor->unk_98 = (u16) (partner_actor->unk_98 & 0xFFF7);
        }
        if (!(actor->unk_98 & 0x2000)) {
            partner_actor->unk_98 = (u16) (partner_actor->unk_98 & 0xFFFB);
        }
        ((S_func_81008664_3 *)entity)->unk_1C = (s32) (((S_func_81008664_3 *)entity)->unk_1C | 0x40000000);
        partner->unk_1C = (s32) (partner->unk_1C | 0x40000000);
        {
            s16 angle_or_duration;
            s32 return_step_offset;

            angle_or_duration = ((S_func_81008664_3 *)entity)->unk_2A;
            motion->unk_14 = 0;
            actor->unk_96 = 8;
            direction = angle_or_duration >> 8;
            return_step_offset = direction & 0xE;
            angle_or_duration = 8;
            motion->unk_0C = -(((S_func_81008664_10 *)((u8 *)dirStepX + return_step_offset))->unk_00 << 0x16) / angle_or_duration;
            motion->unk_10 = -(((S_func_81008664_10 *)((u8 *)dirStepY + return_step_offset))->unk_00 << 0x16) / actor->unk_96;
            partner_motion->unk_14 = 0;
            motion->unk_14 = 0;
            actor->unk_9B = actor->unk_9B + 1;
            return;
        }
    case 4:
        return_ticks = (u16) actor->unk_96 - 1;
        actor->unk_96 = return_ticks;
        if ((return_ticks << 0x10) > 0) {
            if (!(partner_sprite->unk_14 & 0x8000)) {
                return;
            }
        }
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
        next_handler = &D_80159058;
        actor->unk_8C = next_handler;
        active_count = ((u16)dungeonStatus.unk_0A);
        finish_entity = entity;
        active_count -= 1;
        dungeonStatus.unk_0A = active_count;
        func_800A4ACC(finish_entity);
        *(u16 *)((u8 *)actor + 0x98) = (u16) (actor->unk_98 & 0xFFF3);

        {
            u32 restore_flags;
            u32 restore_mask;
            u32 restore_x;
            u32 restore_y;

            restore_flags = ((S_func_81008664_3 *)entity)->unk_1C;
            restore_mask = 0x40000;
            restore_flags |= restore_mask;
            ((S_func_81008664_3 *)entity)->unk_1C = restore_flags;
            restore_flags &= 0x2000;
            restore_x = sprite->unk_24;
            restore_y = sprite->unk_25;
            restore_tile_mask = 0x3000;
            if (restore_flags) {
                restore_tile_mask = 0x300;
            }
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
            if (restore_flags) {
                restore_partner_mask = 0x300;
            }
            func_8009A21C(restore_x, restore_y, restore_partner_mask);
        }
        anim_table3 = D_8015C888;
        angle_or_count = &gameWork.view.viewAngle;
        *(u8 **)((u8 *)sprite + 0x2C) = anim_table3;
        idle_anim = ((s32) (*angle_or_count + (s16) ((S_func_81008664_3 *)entity)->unk_2A + 0x100) >> 9) & 7;
        idle_anim = idle_anim + (u32) anim_table3;
        func_80047784(sprite, ((S_func_81008664_9 *) idle_anim)->unk_00, 0);
        ((S_func_81008664_3 *)entity)->unk_6D = 0;
        ((S_func_81008664_3 *)entity)->unk_46 = (u16) (((S_func_81008664_3 *)entity)->unk_46 & 0x7FFF);
        actor->unk_9B = actor->unk_9B + 1;
    default:
        return;
    }
}
