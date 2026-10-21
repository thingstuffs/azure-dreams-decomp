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
extern u8 D_800DF3CC[];
extern s32 test_resident_bit(s32);
extern void func_80040AA0(s32);
extern void Control_CD();
extern void drain_cd_command_queue(void);
extern char D_800DF3D4[];
extern void func_8003E4FC(s32, char *, s32);
extern void func_8003F320(void);

extern u8 scene_mode_code;
extern u8 D_800DCF4E;

/* Functions defined in this translation unit. */
void invoke_action_21_or_default(void);
void trigger_action_21_or_update_control(void);

#endif
