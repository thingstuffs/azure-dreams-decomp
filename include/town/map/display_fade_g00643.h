#ifndef TOWN_MAP_DISPLAY_FADE_G00643_H
#define TOWN_MAP_DISPLAY_FADE_G00643_H
/* Display fade (G00643). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BEA7C, PD:town/engine:80111FB0. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct S_800BC290_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
} S_800BC290_0;

/* arg0 in advance_color_fade_and_set_completion */
typedef struct S_800BC290_1 {
    u8 pad_00[0xC];
    union { s32 s32; u8 u8; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    s16 unk_14;
} S_800BC290_1;

typedef struct {
    u32 word0;
    u32 word4;
} __attribute__((packed)) Copy8;

/* arg2 in advance_color_fade_and_set_completion */
extern void func_8004E994(void *);
extern u8 D_80111FB0[8];
extern void register_node(void *entry, void *registration_id);
extern void *decode_note_text(void *entries, void *text, s32 initial_octave);
extern void func_8004E9E4(void);
extern void create_positioned_callback_object(void *position, void *object_value, void *data_value);
extern s32 D_80053A88;
extern u8 D_800782EC[8];
extern Copy8 D_8008961C;
extern u8 D_800BC290[8];
extern u8 D_800BC390[8];

/* Functions defined in this translation unit. */
void advance_color_fade_and_set_completion(void *fade_state, s32 unused, void *visual);
void advance_timed_state_and_set_completion(void *object);
void build_two_display_entries(s32 data_id, s32 position_offset);

#endif
