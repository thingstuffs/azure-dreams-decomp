/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

void func_800353F4(void *);                   /* extern */
void func_80047738(void *, u8, s8);              /* extern */
void func_800478B8(void *);                      /* extern */
void func_800A020C(s32, void *);                 /* extern */
void func_800A1D4C(void *, s32);             /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
void func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
void func_8016A908(void *);                         /* extern */
extern u8 D_80013610[0x3612];
extern s16 D_80013714[5];
extern u8 D_8006CCF8[256];
extern s32 D_800814A0[3];
extern s16 D_80083228[5];
extern u8 D_80083460[0x100];
extern u16 D_80083462[5];
extern u32 D_800835E4[64];
extern u8 *D_800E3D7C[3];
extern u8 D_800F927E[16];
extern void D_8016B778(void);
extern void (*D_80174728[256])(void *, void *, void *, void *);


typedef struct S_8016B0E8_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x6];
    u32 unk_18;
    u8 pad_1C[0x70];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    s8 unk_9D;
    u8 pad_9E[0x6];
    void * unk_A4;
    u8 pad_A8[0x8];
    union { u8 n; volatile u8 v; } unk_B0;   /* accessed as both */
    u8 unk_B1;
    u8 pad_B2[0x2];
    u8 unk_B4;
} S_8016B0E8_0;   /* arg0 in func_8016B0E8 */

typedef struct S_8016B0E8_1 {
    u8 pad_00[0x3610];
    u8 unk_3610;
    u8 unk_3611;
} S_8016B0E8_1;   /* page_8001 in func_8016B0E8 */

typedef struct S_8016B0E8_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    volatile s32 unk_14;
    u32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8016B0E8_2;   /* obj in func_8016B0E8 */

typedef struct S_8016B0E8_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
} S_8016B0E8_3;   /* state_83460 in func_8016B0E8 */

typedef struct S_8016B0E8_4 {
    u8 pad_00[0x3D7C];
    s32 unk_3D7C;
} S_8016B0E8_4;   /* page_e in func_8016B0E8 */

typedef struct S_8016B0E8_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_5;   /* entry_base in func_8016B0E8 */

typedef struct S_8016B0E8_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016B0E8_6;   /* temp_v1_2 in func_8016B0E8 */


typedef struct S_8016B0E8_8 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016B0E8_8;   /* var_a0 in func_8016B0E8 */

typedef struct S_8016B0E8_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016B0E8_9_pre;   /* the 0x14 bytes before temp_v0_2 in func_8016B0E8, addressed as temp_v0_2[-1] */

typedef struct S_8016B0E8_10 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016B0E8_10;   /* temp_v1_3 in func_8016B0E8 */

typedef struct S_8016B0E8_11 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016B0E8_11;   /* late_state_83460 in func_8016B0E8 */

typedef struct S_8016B0E8_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8016B0E8_12;   /* temp_v1_4 in func_8016B0E8 */

typedef struct S_8016B0E8_13 {
    u8 pad_00[0x3462];
    u16 unk_3462;
} S_8016B0E8_13;   /* var_v0_2 in func_8016B0E8 */

typedef struct S_8016B0E8_14 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    s32 unk_2C;
} S_8016B0E8_14;   /* arg2 in func_8016B0E8 */

typedef struct S_8016B0E8_15 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016B0E8_15;   /* arg1 in func_8016B0E8 */

typedef struct S_8016B0E8_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016B0E8_16;   /* (temp_s1 + ((S_8016B0E8_4 *)page_e)->unk_3D7C) in func_8016B0E8 */

/* Update actor state, animation, movement, and terrain height. */
void func_8016B0E8(void *entity, void *motion, void *sprite) {
    register M2C_UNK (*update_callback)(void *, void *, void *, void *);
    register M2C_UNK (*paused_callback)(void *, void *, void *, void *);
    register s16 base_height;
    register s32 view_direction;
    register s32 direction_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 prior_direction;
    s16 floor_height;
    s16 height_delta;
    register s32 linked_actor;
    register s32 animation_id;
    s32 motion_position;
    s32 motion_delta;
    u16 motion_flags;
    register s32 lookup_offset ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 level_seed;
    register u8 * direction_animations;
    register s32 actor_flags;
    s32 actor_index;
    register s32 actors_left ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 level_index;
    u16 facing_flags;
    register s16 prior_state;
    u16 *flags_page;
    register u16 height_bits;
    u16 sprite_flags;
    u16 display_flags;
    u32 mode_bits;
    register u32 initial_exp;
    register u32 scaled_level;
    register u8 countdown;
    register u8 facing_flip;
    register u8 fall_ticks;
    register u32 *exp_table;
    register u32 *exp_limits;
    register u32 *level_limits;
    register u8 *scene_state;
    register u8 *countdown_state;
    u8 *message;
    register void *actor_slot ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *linked_entry;
    register void *actor_header;
    register void *linked_sprite;
    register void *status_record;
    register void *slot_cursor;
    S_8016B0E8_1 *seed_page;
    void *entity_ref = entity;
    void *motion_ref = motion;
    register void *sprite_ref = sprite;
    register void *actor ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *actors_page ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 inactive_mask;
#define entity entity_ref
#define motion motion_ref
#define sprite sprite_ref

    actor = entity;
    if (((S_8016B0E8_0 *)entity)->unk_18 == 0) {
        seed_page = (void *)0x80010000;
        level_seed = seed_page->unk_3611 | (seed_page->unk_3610 << 8);
        scaled_level = (u32) level_seed >> 2;
        if (level_seed < 0) {
            scaled_level = (u32) (level_seed + 3) >> 2;
        }
        if (scaled_level < 0x1AU) {
            level_index = scaled_level & 0xFFFF;
        } else {
            scaled_level = 0x19;
            ASM_KEEP_NV(scaled_level);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            level_index = scaled_level & 0xFFFF;
        }
        exp_table = D_800835E4;
        exp_limits = exp_table + 1;
        initial_exp = exp_table[level_index] + 1;
        ((S_8016B0E8_0 *)entity)->unk_18 = initial_exp;
        if (initial_exp >= (u32) exp_limits[((S_8016B0E8_0 *)entity)->unk_11]) {
            level_limits = exp_limits;
            do {
                func_800A1D4C(actor, 0);
            } while (!((u32) level_limits[((S_8016B0E8_2 *)actor)->unk_11] > (u32) ((S_8016B0E8_2 *)actor)->unk_18));
        }
    }
    if (((S_8016B0E8_0 *)entity)->unk_B4 != 0) {
        scene_state = D_80083460;
        if ((((S_8016B0E8_3 *)scene_state)->unk_0C != 0) || (((S_8016B0E8_3 *)scene_state)->unk_0A != 1)) {
            goto done;
        }
        if (((S_8016B0E8_0 *)entity)->unk_B4 == ((S_8016B0E8_3 *)scene_state)->unk_0A) {
            message = D_800F927E;
            ASM_KEEP(message);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            actor_index = 0;
            actors_page = (u8 *)0x800E0000;
            (*(s16 *)D_80013714) = (s16) ((*(u16 *)D_80013714) | 8);
            inactive_mask = 0x80000000;
            func_800353F4(message);
            ((S_8016B0E8_2 *)actor)->unk_6D = 0U;
            ((S_8016B0E8_0 *)entity)->unk_9B = 0;
            ((S_8016B0E8_0 *)entity)->unk_B4 = 0U;
            do {
                lookup_offset = actor_index * 4;
                linked_actor = ((S_8016B0E8_16 *)((lookup_offset + ((S_8016B0E8_4 *)actors_page)->unk_3D7C)))->unk_AC;
                if (linked_actor != 0) {
                    func_8016A908(linked_actor);
                    actor_slot = (void *)(lookup_offset + ((S_8016B0E8_4 *)actors_page)->unk_3D7C);
                    actor_header = ((S_8016B0E8_5 *)actor_slot)->unk_AC - 0x20;
                    ((S_8016B0E8_6 *)actor_header)->unk_10 = (s32) (((S_8016B0E8_6 *)actor_header)->unk_10 | inactive_mask);
                }
                actor_index += 1;
            } while (actor_index < 2);
        }
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if ((*(u16 *)D_80013714) & 8) {
        actors_left = 1;
        slot_cursor = ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_s32.v + 4;
        do {
            linked_entry = ((S_8016B0E8_8 *)slot_cursor)->unk_AC;
            if (linked_entry != NULL) {
                linked_sprite = ((S_8016B0E8_9_pre *)linked_entry)[-1].unk_00;
                ((S_8016B0E8_10 *)linked_sprite)->unk_14 = (u16) (((S_8016B0E8_10 *)linked_sprite)->unk_14 & 0xFFBF);
            }
            actors_left -= 1;
            slot_cursor -= 4;
        } while (actors_left >= 0);
    }
    if (((S_8016B0E8_0 *)entity)->unk_B0.n != 0) {
        countdown = ((S_8016B0E8_0 *)entity)->unk_B1 - 1;
        ((S_8016B0E8_0 *)entity)->unk_B1 = countdown;
        if (!(countdown & 0xFF)) {
            ((S_8016B0E8_2 *)actor)->unk_14 = (s32) (((S_8016B0E8_2 *)actor)->unk_14 & 0xFFEFFFFF);
            ((S_8016B0E8_0 *)entity)->unk_B0.v = 0U;
            countdown_state = D_80083460;
            ((S_8016B0E8_11 *)countdown_state)->unk_0A = (s16) ((u16) ((S_8016B0E8_11 *)countdown_state)->unk_0A - 1);
            status_record = ((S_8016B0E8_0 *)entity)->unk_A4;
            ((S_8016B0E8_12 *)status_record)->unk_1E = (u16) (((S_8016B0E8_12 *)status_record)->unk_1E | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }
    flags_page = (u16 *)0x80080000;
    ASM_KEEP_NV(flags_page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if (((S_8016B0E8_13 *)flags_page)->unk_3462 & 0x2000) {
        paused_callback = ((S_8016B0E8_0 *)entity)->unk_8C;
        if (paused_callback == &D_8016B778) {
            paused_callback(entity, motion, sprite, actor);
            goto done;
        }
        ((S_8016B0E8_2 *)actor)->unk_71 = (u8) (((S_8016B0E8_2 *)actor)->unk_71 & 0x7F);
        goto done;
    }
    prior_state = (s8) ((S_8016B0E8_2 *)actor)->unk_6D;
    if (func_800A9E70(entity, motion, sprite, actor) == 0) {
        update_callback = ((S_8016B0E8_0 *)entity)->unk_8C;
        if (update_callback != NULL) {
            update_callback(entity, motion, sprite, actor);
        }
        D_80174728[((S_8016B0E8_0 *)entity)->unk_9A](entity, motion, sprite, actor);
        if ((s16) prior_state != (s8) ((S_8016B0E8_2 *)actor)->unk_6D) {
            func_800AA36C(entity, motion, sprite, actor);
        }
        sprite_flags = ((S_8016B0E8_14 *)sprite)->unk_14.n;
        mode_bits = sprite_flags & 0x8000;
        if (!mode_bits) {
            view_direction = ((s32) (D_80083228[0] + ((S_8016B0E8_2 *)actor)->unk_2A + 0x100) >> 9) & 7;
            prior_direction = ((S_8016B0E8_0 *)entity)->unk_94;
            ASM_USE_NV(prior_direction);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            direction_index = view_direction;
            ASM_KEEP_NV(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            lookup_offset = view_direction;
            if (prior_direction != direction_index) {
                direction_animations = ((S_8016B0E8_14 *)sprite)->unk_2C;
                if (direction_animations != 0) {
                    animation_id = *(direction_animations + direction_index);
                    ASM_USE_NV(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    func_80047738(sprite, animation_id, ((S_8016B0E8_14 *)sprite)->unk_04);
                }
                ((S_8016B0E8_0 *)entity)->unk_94 = view_direction;
            }
            facing_flip = D_8006CCF8[lookup_offset];
            ASM_USE_NV(lookup_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (facing_flip != 0) {
                facing_flags = ((S_8016B0E8_14 *)sprite)->unk_14.n | 1;
            } else {
                facing_flags = ((S_8016B0E8_14 *)sprite)->unk_14.v & 0xFFFE;
            }
            ((S_8016B0E8_14 *)sprite)->unk_14.v = facing_flags;
            if (!(((S_8016B0E8_2 *)actor)->unk_1C & 0x20)) {
                if (((S_8016B0E8_14 *)sprite)->unk_14.v & 0x40) {
                    goto update_sprite;
                }
                func_800478B8(sprite);
                goto update_sprite;
            }
            ((S_8016B0E8_14 *)sprite)->unk_14.n = (u16) (((S_8016B0E8_14 *)sprite)->unk_14.n | 0x7000);
update_sprite:
            func_800A020C(((S_8016B0E8_2 *)actor)->unk_1C, sprite + 0xC);
        } else {
            mode_bits = sprite_flags & 0x800;
            if (mode_bits) {
                display_flags = sprite_flags & 0x8FFF;
            } else {
                display_flags = sprite_flags | 0x7000;
            }
            ((S_8016B0E8_14 *)sprite)->unk_14.n = display_flags;
        }
        ((S_8016B0E8_15 *)motion)->unk_00.at00.v = (s32) (((S_8016B0E8_15 *)motion)->unk_00.at00.v + ((S_8016B0E8_15 *)motion)->unk_0C);
        ((S_8016B0E8_15 *)motion)->unk_04.at00.v = (s32) (((S_8016B0E8_15 *)motion)->unk_04.at00.v + ((S_8016B0E8_15 *)motion)->unk_10);
        if (!(((S_8016B0E8_0 *)entity)->unk_98 & 8)) {
            goto apply_gravity;
        }
        ((S_8016B0E8_0 *)entity)->unk_9D = 0;
        goto integrate_height;
apply_gravity:
        ((S_8016B0E8_15 *)motion)->unk_14 = (s32) (((S_8016B0E8_15 *)motion)->unk_14 + (((S_8016B0E8_0 *)entity)->unk_9D * 0x14000));
        fall_ticks = (u8) ((S_8016B0E8_0 *)entity)->unk_9D + 1;
        ((S_8016B0E8_0 *)entity)->unk_9D = (s8) fall_ticks;
integrate_height:
        motion_position = ((S_8016B0E8_0 *)entity)->unk_90.at00.v;
        motion_delta = ((S_8016B0E8_15 *)motion)->unk_14;
        motion_flags = ((S_8016B0E8_0 *)entity)->unk_98;
        motion_position += motion_delta;
        ((S_8016B0E8_0 *)entity)->unk_90.at00.v = motion_position;
        if (!(motion_flags & 4)) {
            floor_height = func_800BCB04(((S_8016B0E8_15 *)motion)->unk_00.at02.v, ((S_8016B0E8_15 *)motion)->unk_04.at02.v, (s16) (((S_8016B0E8_2 *)actor)->unk_88.u - 0x20));
            if (floor_height < 0x200) {
                base_height = ((S_8016B0E8_2 *)actor)->unk_88.s;
                if ((((S_8016B0E8_0 *)entity)->unk_90.at02.v + base_height) < floor_height) {
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C & 0xF7FFFFFF);
                } else {
                    height_bits = ((S_8016B0E8_2 *)actor)->unk_88.u;
                    if (floor_height >= base_height) {
                        ((S_8016B0E8_0 *)entity)->unk_90.at00.v = 0;
                    } else {
                        height_delta = floor_height - height_bits;
                        ((S_8016B0E8_0 *)entity)->unk_90.at02.v = height_delta;
                    }
                    ((S_8016B0E8_15 *)motion)->unk_14 = 0;
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C | 0x08000000);
                    ((S_8016B0E8_0 *)entity)->unk_9D = 0;
                }
                actor_flags = ((S_8016B0E8_2 *)actor)->unk_1C;
                if (actor_flags & 0x40000000) {
                    ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (actor_flags & 0xBFFFFFFF);
                    floor_height = func_800BCB04((((S_8016B0E8_14 *)sprite)->unk_24 << 6) | 0x20, (((S_8016B0E8_14 *)sprite)->unk_25 << 6) | 0x20, (s16) (((S_8016B0E8_2 *)actor)->unk_88.u - 0x20));
                    ((S_8016B0E8_0 *)entity)->unk_90.at02.v = (s16) ((u16) ((S_8016B0E8_0 *)entity)->unk_90.at02.v + (((S_8016B0E8_2 *)actor)->unk_88.u - floor_height));
                    ((S_8016B0E8_2 *)actor)->unk_88.s = floor_height;
                }
                goto update_height;
            }
        }
        ((S_8016B0E8_2 *)actor)->unk_1C = (s32) (((S_8016B0E8_2 *)actor)->unk_1C & 0xF7FFFFFF);
update_height:
        ((S_8016B0E8_15 *)motion)->unk_0A = (s16) (((S_8016B0E8_2 *)actor)->unk_88.u + (u16) ((S_8016B0E8_0 *)entity)->unk_90.at02.v);
        ((S_8016B0E8_14 *)sprite)->unk_14.n = (u16) (((S_8016B0E8_14 *)sprite)->unk_14.n | 0x40);
    }
done:
    return;
}
