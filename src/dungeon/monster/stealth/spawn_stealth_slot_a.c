#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80F2D000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80F2D000_0;   /* object in spawn_effect_object */

typedef struct S_80F2D000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F2D000_1;   /* work in spawn_effect_object */

typedef struct S_80F2D000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F2D000_2;   /* part_a in spawn_effect_object */

typedef struct S_80F2D000_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F2D000_3;   /* part_b in spawn_effect_object */

typedef struct S_80F2D000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80F2D000_4;   /* work_copy in spawn_effect_object */


/* cfail-repair: tf7-phase1-cache-v3 */
void *allocate_list_node();                 /* extern */
s32 register_node();                /* extern */
s16 set_or_clear_actor_status_slot();        /* extern */
s32 generate_random_value();                          /* extern */
void initialize_actor_sprite_and_animation(); /* extern */
s32 try_move_actor_to_valid_position(); /* extern */
void retire_tracked_effect_by_id();                      /* extern */
extern M2C_UNK D_8014CA8C;
extern M2C_UNK D_8014CF74;
extern M2C_UNK D_8014FD30;
extern M2C_UNK D_8014FD78;



void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 unksp20;
    s32 kind;
    s32 variant;
    void *obj_alt;
    S_80F2D000_3 *part_b;
    S_80F2D000_2 *part_a;
    void *work_copy;
    void *object;
    S_80F2D000_1 *work;

    unksp20 = (s32) *(s8 *)-0x149C;
    work = NULL;
    variant = 1;
    object = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (object != NULL) {
        work = object + 0x20;
        ((S_80F2D000_0 *)object)->unk_10 = &D_8014CA8C;
        work->unk_13 = 0x23;
        register_node(object, project_sprite_chain);
        part_a = ((S_80F2D000_0 *)object)->unk_08;
        part_a->unk_0A = attr_c;
        part_b = ((S_80F2D000_0 *)object)->unk_0C;
        part_b->unk_25 = attr_b;
        work_copy = work;
        part_b->unk_2C = &D_8014FD30;
        kind = spawn_flags & 3;
        part_b->unk_24 = attr_a;
        if (kind == 1) {
            work->unk_14 = (s32) (work->unk_14 | 0x6000);
            work->unk_1C = (s32) (work->unk_1C | 0x6000);
        } else if (kind >= 2) {
            work->unk_14 = (s32) (work->unk_14 | 0x2000);
            work->unk_1C = (s32) (work->unk_1C | 0x2000);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    work->unk_1C = (s32) (work->unk_1C | 0x200);
                    set_or_clear_actor_status_slot(work, 1, (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = &D_8014FD78;
                }
            }
            variant = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part_a, part_b, spawn_flags);
        ((S_80F2D000_4 *)work_copy)->unk_9A = 0xFF;
        ((S_80F2D000_4 *)work_copy)->unk_9C = -1;
        ((S_80F2D000_4 *)work_copy)->unk_8C = &D_8014CF74;
        ((S_80F2D000_4 *)work_copy)->unk_A4 = -1;
        if (variant != 0) {
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 0;
        } else {
            obj_alt = work_copy - 0x20;
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 1;
            part_b->unk_10 = 0x60;
            part_b->unk_14 = (u16) (part_b->unk_14 | 0xC);
            part_b->unk_12 = (u16) (part_b->unk_12 - 0x80);
            unlink_node(obj_alt);
            retire_tracked_effect_by_id(obj_alt);
        }
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
    }
    return work;
}
