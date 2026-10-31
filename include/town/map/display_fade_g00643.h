#ifndef TOWN_MAP_DISPLAY_FADE_G00643_H
#define TOWN_MAP_DISPLAY_FADE_G00643_H
/* Display fade (G00643). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BEA7C, PD:town/engine:80111FB0. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct TimedColorFadeObject {
    /* 0x00 */ union { s16 s; u16 u; } state;
    /* 0x02 */ union { u16 u; s16 s; } timer;
} TimedColorFadeObject;

/* Body advanced by advance_timed_state_and_set_completion. */
typedef struct BuildTwoDisplayEntriesBody {
    /* 0x00 */ union { s16 s; u16 u; } state;
    /* 0x02 */ union { u16 u; s16 s; } timer;
    /* 0x04 */ u8 pad_04[4];
    /* 0x08 */ s32 decay_value;
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ s16 completion_state;
} BuildTwoDisplayEntriesBody;

/* arg0 in advance_color_fade_and_set_completion */

/* arg0 in advance_color_fade_and_set_completion */

typedef struct {
    u32 word0;
    u32 word4;
} __attribute__((packed)) Copy8;

/* arg2 in advance_color_fade_and_set_completion */
extern void noop_release_notification(void *);
extern u8 D_80111FB0[8];
extern void register_node(void *entry, void *registration_id);
extern void noop_display_setup_hook(void);
extern void create_positioned_callback_object(void *position, void *object_value, void *data_value);
extern s32 display_registration_tag;
extern u8 D_800782EC[8];
extern Copy8 D_8008961C;
extern u8 D_800BC290[8];
extern u8 D_800BC390[8];

/* Functions defined in this translation unit. */
void advance_color_fade_and_set_completion(TimedColorFadeObject *fade_state, s32 unused, SpriteFrameState *visual);
void advance_timed_state_and_set_completion(BuildTwoDisplayEntriesBody *object);
void build_two_display_entries(void *data_id, s32 position_offset);

#endif
