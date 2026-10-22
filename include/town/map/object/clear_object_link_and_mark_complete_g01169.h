#ifndef TOWN_MAP_OBJECT_CLEAR_OBJECT_LINK_AND_MARK_COMPLETE_G01169_H
#define TOWN_MAP_OBJECT_CLEAR_OBJECT_LINK_AND_MARK_COMPLETE_G01169_H
/* Clear object link and mark complete. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01169 - CL:town/func_800BDDA8, CL:town/func_800BDE1C. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_func_800BB508_0 {
    u8 pad_00[0x98];
    void *unk_98;
} S_func_800BB508_0;

typedef struct {
    s32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[6];
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} FuncData;



extern s32 classify_object_against_bounds(void *, void *);
extern void unlink_scene_list_node(void *node);
extern void unlink_node_if_registered(void *object);
extern void register_node(s32, void *);
extern void configure_the_set_mode_n_3(s32, void *, void *);
extern u8 D_80046398[];
extern u8 D_800D1BDC[];
extern u8 D_800BB640[];
extern u8 D_800BB6C4[];

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
void clear_object_link_and_mark_complete(S_func_800BB508_0 *object, void *context);
void initialize_object_state_and_appearance(s32 object_id, void *object, FuncData *state);
void advance_object_state_angle(s32 object, s32 context, void *state);
void initialize_object_appearance_with_delay(void *object, void *context, void *state);
void clear_object_link_and_complete(void *object, s32 value);
void set_handler_variant_b_with_counter_30(void *object, void *context, void *state);
void init_object_with_countdown(void *object, void *context, void *state);
void set_handler_variant_b_with_counter_14(void *object, void *context, void *state);

#endif
