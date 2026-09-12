#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


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

extern s32 D_80045340;
extern LocalItemInfo D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
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

typedef struct S_801731C8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801731C8_7;   /* global in func_801731C8 */

/* Updates an item-use action, its animation, and its particle effects. */
void func_801731C8(void *action, void *motion, void *sprite, void *actor)
{
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *item_slot;
    s16 is_special;
    s32 next_state;
    s32 state;
    void *target;

    is_special = 0;
    state = ((S_801731C8_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        u32 kind_index;

        kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        if (kind_index >= 7) {
            goto kind_default;
        }
        (void)kind_labels;
        goto *D_80170850[kind_index];

kind_5:
        is_special = 1;
        goto kind_3;
kind_6:
        is_special = 1;
        goto kind_2;
kind_7:
        is_special = 1;
        goto kind_1;
    }

    {
        s32 action_kind;

        action_kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        if (action_kind == 2) {
            goto kind_2;
        }
        if (action_kind < 3) {
            item_slot = 0;
            if (action_kind == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (action_kind != 3) {
            item_slot = 0;
            goto selection_ready;
        }
    }

kind_3:
    item_slot = (u8 *)actor + 0xE;
    goto selection_ready;
kind_2:
    item_slot = (u8 *)actor + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    item_slot = (u8 *)actor + 8;
    goto selection_ready;
kind_default:
    item_slot = 0;

selection_ready:
    if (*item_slot == 0) {
        goto empty_selection;
    }
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
        if (D_8006DE24[item_id].kind == 2) {
            target = (*(void * *)((u8 *)actor + 0x60));
            if (target != 0) {
                register u8 *target_sprite ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                target_sprite = ((S_801731C8_1_pre *)target)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = ((S_801731C8_2 *)target_sprite)->unk_24;
                (*(u8 *)((u8 *)actor + 0x73)) = ((S_801731C8_2 *)target_sprite)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            target = func_800A05A4(
                actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)actor + 0x60)) = target;
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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

invoke_item:
    if (func_800A94A0(actor, item_slot, is_special, (u8 *)action + 0x98) == 0) {
        goto end;
    }
    ((S_801731C8_0 *)action)->unk_96.u = 0x11;
    {
        u8 *animations;
        s32 direction;

        animations = D_801755CC;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = animations;
        direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(sprite, animations[direction], 0);
    }
    next_state = ((S_801731C8_0 *)action)->unk_9B + 1;
    ((S_801731C8_0 *)action)->unk_9B = next_state;
    goto state_1_done;

empty_selection:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_801731C8_0 *)action)->unk_8C = D_801716F4;
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
state_1_done:
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((S_801731C8_0 *)action)->unk_9B++;
    func_800A56E0(0x703);

state_2:
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
            direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, animations[direction], 0);
        }
        if (((S_801731C8_0 *)action)->unk_96.s < 2) {
            goto end;
        }
    }

    {
        s16 particle_count;
        s16 next_count;
        u8 *particle_script;
        s32 low_color;
        s32 high_color;

        particle_count = 0;
        particle_script = D_80171030;
        low_color = 0x20;
        high_color = 0xE0;
        do {
            void *particle;

            particle = func_8003FC64(0x212);
            if (particle == 0) {
                goto null_counter;
            }
            ASM_KEEP(particle);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            {
                void *particle_part;
                s32 color_roll;
                s16 color_choice;

                ((S_801731C8_5 *)particle)->unk_22 = 8;
                ((S_801731C8_5 *)particle)->unk_10 = particle_script;
                func_8004491C(particle, &D_80045340);
                particle_part = ((S_801731C8_5 *)particle)->unk_0C;
                ((S_801731C8_6 *)particle_part)->unk_10 = low_color;
                ((S_801731C8_6 *)particle_part)->unk_14 |= 0xC;

                particle_part = ((S_801731C8_5 *)particle)->unk_08;
                {
                    s32 position_roll;
                    s32 position_base;

                    position_roll = func_80069EF8();
                    position_base = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
                    position_base -= 0x20;
                    ((S_801731C8_6 *)particle_part)->unk_02 = position_base + (position_roll & 0x3F);
                }
                {
                    s32 position_roll;
                    s32 position_base;

                    position_roll = func_80069EF8();
                    position_base = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
                    position_base -= 0x20;
                    ((S_801731C8_6 *)particle_part)->unk_06 = position_base + (position_roll & 0x3F);
                }
                ((S_801731C8_6 *)particle_part)->unk_08.at02.v =
                    ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v - (func_80069EF8() & 0x1F) - 0x30;

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
                    goto null_counter;
                }
                ASM_KEEP(particle_part);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
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
            next_count = particle_count + 1;
            goto assign_counter;
null_counter:
            next_count = particle_count + 1;
assign_counter:
            particle_count = next_count;
            ASM_KEEP(next_count);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
counter_test:
            ;
        } while ((s16)next_count < 1);
    }
    goto end;

state_3:
    {
        u8 *effect_state;
        s16 timer;

        effect_state = (u8 *)&D_80083460;
        if (((S_801731C8_7 *)effect_state)->unk_0C == 0) {
            ((S_801731C8_0 *)action)->unk_96.u = 0;
        }
        timer = ((S_801731C8_0 *)action)->unk_96.u - 1;
        ((S_801731C8_0 *)action)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_801731C8_0 *)action)->unk_96.u = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80175554) {
            u8 *animations;
            s32 direction;

            animations = D_80175554;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = animations;
            direction = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(sprite, animations[direction], 0);
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_801731C8_7 *)effect_state)->unk_0C != 0) {
            goto end;
        }
        ((S_801731C8_7 *)effect_state)->unk_0A--;
        ((S_801731C8_0 *)action)->unk_8C = D_801716F4;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
