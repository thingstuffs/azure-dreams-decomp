#ifndef DUNGEON_ACTOR_ACTION_CONTROL_DISPATCH_G00352_H
#define DUNGEON_ACTOR_ACTION_CONTROL_DISPATCH_G00352_H
/* Action control dispatch shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800DCF4E. */

#include "common.h"

/* Fixed 0x6000-byte memory-card image: the read/write wrappers use 0xC0
 * 128-byte units, and the checksum covers [0x208,0x6000). The resident
 * reset routine clears the two words at +0x208C/+0x2090. This is the
 * serialized object's base and extent, not an inferred address page.
 * See docs/evidence/r121_hardholds.md for the independent retail witnesses. */
typedef struct SaveImage {
    u8 prefix[0x208C];
    s32 pending;
    s32 active;
    u8 suffix[0x3F6C];
} SaveImage;

extern s16 current_dungeon_floor;
extern u8 level_module_read_descriptor_a[];
void request_scene_dispatch_state(s16 requested_state);
extern s32 Control_CD(s32 event_code, void *event_data, s32 payload);
extern void drain_cd_command_queue(void);
extern char level_module_read_descriptor_b[];
extern void func_8003E4FC(s32, char *, s32);
extern void func_8003F320(void);

extern u8 scene_mode_code;
extern u8 sprite_bundle_loaded;

/* Functions defined in this translation unit. */
void request_scene_state_21_or_reload_level_module_a(void);
void request_scene_state_21_or_reload_level_module_b(void);

#endif
