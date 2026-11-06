#include "slus/jtbl_80052144.h"
#include "script_symbols.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/effect/data.h"
#include "engine/audio.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/object.h"

/* The controller body follows the standard object-node header. */

struct CdCueEffectNode;
extern void init_fade_in_out_effect(struct CdCueEffectNode *, struct Controller *);
extern void init_color_fade_effect(struct CdCueEffectNode *, struct Controller *);

typedef struct CdCueControllerNode {
    ObjectNodeHeader header;
    Controller body;
} CdCueControllerNode;

/* Allocates and initializes a node, then attaches up to five slots. */
void create_cd_cue_effect(void)
{
    CdCueControllerNode *node;
    Controller *slots;
    void *slot0;
    void *slot1;
    void *slot2;
    void *slot3;
    void *slot4;

    node = allocate_flagged_object_node(0);
    if (node != 0) {
        slots = &node->body;
        node->header.update_callback = update_scene_effect_controller;
        node->body.state = 0;
        slots->timer = 0;
        slots->attached = 0;
        slots->finished = 0;
        slots->script = cd_cue_effect_visual_data;
        slots->child0 = 0;
        slots->child1 = 0;
        slots->child2 = 0;
        slots->child3 = 0;
        slots->group = 0;
        sound_set_cd_cue_parameters(0, 0x15B7C, 0, 0x10093C8);
        SD_Call(0x300);

        slot0 = allocate_list_node(0x212, &node->header.next);
        if (slot0 != 0) {
            scene_initialize_arc_motion_sprite(slot0, slots);
            slots->child0 = slot0;
            slots->attached++;
        }
        if (test_resident_bitmap_bit(F_qyun_misuteta) == 0) {
            slot1 = allocate_list_node(0x212, &node->header.next);
            if (slot1 != 0) {
                scene_initialize_orbit_motion_sprite(slot1, slots);
                slots->child1 = slot1;
                slots->attached++;
            }
        }
        slot2 = allocate_list_node(0x212, &node->header.next);
        if (slot2 != 0) {
            init_fade_in_out_effect(slot2, slots);
            slots->child2 = slot2;
            slots->attached++;
        }
        slot3 = allocate_list_node(0x212, &node->header.next);
        if (slot3 != 0) {
            init_color_fade_effect(slot3, slots);
            slots->child3 = slot3;
            slots->attached++;
        }
        slot4 = allocate_list_node(0x212, &node->header.next);
        if (slot4 != 0) {
            scene_initialize_sixteen_sprite_sequence(slot4, slots);
            slots->group = slot4;
            slots->attached++;
        }
    }
}
