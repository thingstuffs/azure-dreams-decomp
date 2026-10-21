#include "script_symbols.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/object.h"
#include "slus.h"

/* Sub-object embedded at offset 0x20 of the allocated node. */
typedef struct S_800525D4_sub {
    s16 f0;     /* 0x00 */
    s16 f2;     /* 0x02 */
    s16 count;  /* 0x04 - incremented once per successfully attached slot0 */
    s16 f6;     /* 0x06 */
    void *f8;   /* 0x08 - set to &D_80071E44 */
    void *fC;   /* 0x0C - result of scene_initialize_arc_motion_sprite */
    void *f10;  /* 0x10 - result of scene_initialize_orbit_motion_sprite */
    void *f14;  /* 0x14 - result of init_fade_in_out_effect */
    void *f18;  /* 0x18 - result of init_color_fade_effect */
    void *f1C;  /* 0x1C - result of scene_initialize_sixteen_sprite_sequence */
} S_800525D4_sub;

/* Allocated node (from func_8003FC64), size class 0x124 (see S_80081490 in
 * w_8003FC64.c); this function only touches the prefix up through the
 * embedded sub-object at 0x20. */
typedef struct S_800525D4_obj {
    u8 pad00[0x10];               /* 0x00 */
    void (*vtable)(void);         /* 0x10 - set to update_scene_effect_controller */
    u8 pad14[0x20 - 0x14];        /* 0x14 */
    S_800525D4_sub sub;           /* 0x20 */
} S_800525D4_obj;

extern u8 cd_cue_effect_visual_data[0x10];

extern void update_scene_effect_controller(void);
extern void scene_initialize_arc_motion_sprite(void *a0, S_800525D4_sub *a1);
extern void init_fade_in_out_effect(void *a0, S_800525D4_sub *a1);
extern void init_color_fade_effect(void *a0, S_800525D4_sub *a1);

/* Allocates and initializes a node, then attaches up to five slots. */
void create_cd_cue_effect(void)
{
    S_800525D4_obj *node;
    S_800525D4_sub *slots;
    void *slot0;
    void *slot1;
    void *slot2;
    void *slot3;
    void *slot4;

    node = (S_800525D4_obj *)func_8003FC64(0);
    if (node != 0) {
        slots = &node->sub;
        node->vtable = update_scene_effect_controller;
        node->sub.f0 = 0;
        slots->f2 = 0;
        slots->count = 0;
        slots->f6 = 0;
        slots->f8 = cd_cue_effect_visual_data;
        slots->fC = 0;
        slots->f10 = 0;
        slots->f14 = 0;
        slots->f18 = 0;
        slots->f1C = 0;
        sound_set_cd_cue_parameters(0, 0x15B7C, 0, 0x10093C8);
        SD_Call(0x300);

        slot0 = allocate_list_node(0x212, node);
        if (slot0 != 0) {
            scene_initialize_arc_motion_sprite(slot0, slots);
            slots->fC = slot0;
            slots->count++;
        }
        if (test_resident_bitmap_bit(F_qyun_misuteta) == 0) {
            slot1 = allocate_list_node(0x212, node);
            if (slot1 != 0) {
                scene_initialize_orbit_motion_sprite(slot1, slots);
                slots->f10 = slot1;
                slots->count++;
            }
        }
        slot2 = allocate_list_node(0x212, node);
        if (slot2 != 0) {
            init_fade_in_out_effect(slot2, slots);
            slots->f14 = slot2;
            slots->count++;
        }
        slot3 = allocate_list_node(0x212, node);
        if (slot3 != 0) {
            init_color_fade_effect(slot3, slots);
            slots->f18 = slot3;
            slots->count++;
        }
        slot4 = allocate_list_node(0x212, node);
        if (slot4 != 0) {
            scene_initialize_sixteen_sprite_sequence(slot4, slots);
            slots->f1C = slot4;
            slots->count++;
        }
    }
}
