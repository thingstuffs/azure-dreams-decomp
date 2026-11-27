#ifndef DUNGEON_MONSTER_BELDO_LARGE_DATA_H
#define DUNGEON_MONSTER_BELDO_LARGE_DATA_H

#include "common.h"
#include "shared/object_node.h"

extern u8 encounter_recovery_flag;

/* The encounter callbacks read and write the first halfword at 0x801760D8. */
extern s16 encounter_blink_update_flag;

/* Bytecode cursor shared by the multi-form script writers and interpreter. */
extern u8 *encounter_script_cursor;

/* create_multi_form_actor and create_scripted_encounter_object publish the
 * two allocated node headers separately. Their script controls live in the bodies. */
extern ObjectNodeHeader *beldo_actor_nodes;
extern ObjectNodeHeader *beldo_script_node;

/* The encounter starts the indexed script at +0xAB and sets
 * +0xAF. The transition routine clears that flag and sets its adjacent state bytes. */
typedef struct BeldoScriptControl {
    u8 pad_00[0xAB];
    s8 script_index;
    u8 pad_AC[2];
    u8 action_delay;
    u8 script_active;
    u8 transition_phase;
} BeldoScriptControl;

#endif
