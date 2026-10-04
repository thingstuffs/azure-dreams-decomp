#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


typedef struct {
    u32 words[3];
} __attribute__((packed)) LocalPacket;

typedef struct {
    u8 bytes[0x12];
    u8 kind;
    u8 pad;
} LocalItemInfo;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern u8 D_80171030[];
extern u8 D_801716F4[];
extern u8 D_80175554[];
extern u8 D_80175594[];
extern u8 D_801755CC[];
extern LocalPacket D_801755D4;


typedef struct S_801731C8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801731C8_0;   /* arg0 in func_801731C8 */

typedef struct S_801731C8_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801731C8_1_pre;   /* the 0x14 bytes before active in func_801731C8, addressed as active[-1] */

typedef struct S_801731C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801731C8_2;   /* linked in func_801731C8 */


typedef struct S_801731C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_801731C8_5;   /* object in func_801731C8 */

typedef struct S_801731C8_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801731C8_6;   /* part in func_801731C8 */

/* Updates an item-use action, its animation, and its particle effects. */
void func_801731C8(void *action, EntityRec *motion, void *sprite, void *actor)
{
    u8 *item_slot;
    s16 is_special;
    s32 next_state;
    s32 state;
    void *target;

    is_special = 0;
    state = ((S_801731C8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_801731C8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 special_flag;

                special_flag = is_special;
                if (special_flag != 0) {
                    target = D_800814A8;
                    (*(void * *)((u8 *)actor + 0x60)) = target;
                    goto copy_active_coords;
                }
            }

            {
                u8 item_id;

                item_id = *item_slot;
                if (((LocalItemInfo *)D_8006DE24)[item_id].kind == 2) {
                    target = (*(void * *)((u8 *)actor + 0x60));
                    if (target != 0) {

    copy_active_coords:
                        state = (s32)(((S_801731C8_1_pre *)target)[-1].unk_00);
                        (*(u8 *)((u8 *)actor + 0x72)) = ((S_801731C8_2 *)((u8 *)state))->unk_24;
                        (*(u8 *)((u8 *)actor + 0x73)) = ((S_801731C8_2 *)((u8 *)state))->unk_25;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)func_800A05A4(
                        actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                        (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                    (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)dx;
                    dx = (*(s8 *)((u8 *)actor + 0x72));
                    dy = (*(s8 *)((u8 *)actor + 0x73));
                    if (dx < 0) {
                        dx = -dx;
                    }
                    if (dy < 0) {
                        dy = -dy;
                    }
                    (*(u8 *)((u8 *)actor + 0x72)) = dx;
                    (*(u8 *)((u8 *)actor + 0x73)) = dy;
                }
            }

            if (func_800A94A0(actor, item_slot, is_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_801731C8_0 *)action)->unk_96.u = 0x11;
            {
                u8 *animations;
                s32 direction;

                animations = D_801755CC;
                (*(u8 * *)((u8 *)sprite + 0x2C)) = animations;
                direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                func_80047784(sprite, animations[direction], 0);
            }
            next_state = ((S_801731C8_0 *)action)->unk_9B + 1;
            ((S_801731C8_0 *)action)->unk_9B = next_state;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_801731C8_0 *)action)->unk_8C = D_801716F4;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((S_801731C8_0 *)action)->unk_9B++;
        func_800A56E0(0x703);

    case 2:
        {
            s16 timer;

            timer = ((S_801731C8_0 *)action)->unk_96.u - 1;
            ((S_801731C8_0 *)action)->unk_96.u = timer;
            if (timer <= 0 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                ((S_801731C8_0 *)action)->unk_98 |= 0x80;
                ((S_801731C8_0 *)action)->unk_9B++;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
                ((S_801731C8_0 *)action)->unk_96.u = 0xF;
            }
            if (((S_801731C8_0 *)action)->unk_96.s == 8) {
                u8 *animations;
                s32 direction;

                animations = D_80175594;
                ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = animations;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
                direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                func_80047784(sprite, animations[direction], 0);
            }
            if (((S_801731C8_0 *)action)->unk_96.s < 2) {
                return;
            }
        }

        {
            s16 particle_count;
            u8 *particle_script;
            s32 low_color;
            s32 high_color;

            particle_count = 0;
            particle_script = D_80171030;
            low_color = 0x20;
            high_color = 0xE0;
            for (; particle_count < 1; particle_count++) {
                void *particle;

                particle = func_8003FC64(0x212);
                if (particle == 0) {
                    continue;
                }
                {
                    void *particle_part;
                    s32 color_roll;
                    s16 color_choice;

                    ((S_801731C8_5 *)particle)->unk_22 = 8;
                    ((S_801731C8_5 *)particle)->unk_10 = particle_script;
                    func_8004491C(particle, func_80045340);
                    particle_part = ((S_801731C8_5 *)particle)->unk_0C;
                    ((S_801731C8_6 *)particle_part)->unk_10 = low_color;
                    ((S_801731C8_6 *)particle_part)->unk_14 |= 0xC;

                    particle_part = ((S_801731C8_5 *)particle)->unk_08;
                    {
                        s32 position_roll;
                        s32 position_base;

                        position_roll = func_80069EF8();
                        position_base = ((u16)motion->x.w.i);
                        position_base -= 0x20;
                        ((S_801731C8_6 *)particle_part)->unk_02 = position_base + (position_roll & 0x3F);
                    }
                    {
                        s32 position_roll;
                        s32 position_base;

                        position_roll = func_80069EF8();
                        position_base = ((u16)motion->y.w.i);
                        position_base -= 0x20;
                        ((S_801731C8_6 *)particle_part)->unk_06 = position_base + (position_roll & 0x3F);
                    }
                    ((S_801731C8_6 *)particle_part)->unk_08.at02.v =
                        ((u16)motion->z.w.i) - (func_80069EF8() & 0x1F) - 0x30;

                    particle_part = ((S_801731C8_5 *)particle)->unk_0C;
                    {
                        s32 initial_color;

                        ((S_801731C8_6 *)particle_part)->unk_1E = 0x200;
                        ((S_801731C8_6 *)particle_part)->unk_1C = 0x200;
                        initial_color = 0x80;
                        ((S_801731C8_6 *)particle_part)->unk_0E = initial_color;
                        ((S_801731C8_6 *)particle_part)->unk_0D = initial_color;
                        ((S_801731C8_6 *)particle_part)->unk_0C = initial_color;
                    }
                    *(LocalPacket *)((u8 *)particle + 0x40) = D_801755D4;
                    ((S_801731C8_6 *)particle_part)->unk_08.at00.v = (u8 *)particle + 0x40;

                    color_roll = func_80069EF8() & 3;
                    color_choice = color_roll;
                    if (color_choice == 0) {
                        continue;
                    }
                    ((S_801731C8_6 *)particle_part)->unk_12 = color_roll + 0x7DC6;
                    ((S_801731C8_6 *)particle_part)->unk_14 |= 0x100;
                    switch (color_choice) {
                    case 1:
                        ((S_801731C8_6 *)particle_part)->unk_0C = high_color;
                        ((S_801731C8_6 *)particle_part)->unk_0E = low_color;
                        ((S_801731C8_6 *)particle_part)->unk_0D = low_color;
                        break;
                    case 2:
                        ((S_801731C8_6 *)particle_part)->unk_0E = high_color;
                        ((S_801731C8_6 *)particle_part)->unk_0C = low_color;
                        ((S_801731C8_6 *)particle_part)->unk_0D = low_color;
                        break;
                    case 3:
                        ((S_801731C8_6 *)particle_part)->unk_0D = high_color;
                        ((S_801731C8_6 *)particle_part)->unk_0E = low_color;
                        ((S_801731C8_6 *)particle_part)->unk_0C = low_color;
                        break;
                    }
                }
            }
        }
        return;

    case 3:
        {
            s16 timer;

            if (((s32)dungeonStatus.unk_0C) == 0) {
                ((S_801731C8_0 *)action)->unk_96.u = 0;
            }
            timer = ((S_801731C8_0 *)action)->unk_96.u - 1;
            ((S_801731C8_0 *)action)->unk_96.u = timer;
            if (timer <= 0) {
                ((S_801731C8_0 *)action)->unk_96.u = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80175554) {
                u8 *animations;
                s32 direction;

                animations = D_80175554;
                (*(u8 * *)((u8 *)sprite + 0x2C)) = animations;
                direction = ((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                func_80047784(sprite, animations[direction], 0);
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
            ((S_801731C8_0 *)action)->unk_8C = D_801716F4;
            func_800A4ACC(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            func_800A56E0(0xB4);
        }

    }
}
