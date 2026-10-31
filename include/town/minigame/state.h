#ifndef TOWN_MINIGAME_STATE_H
#define TOWN_MINIGAME_STATE_H
/* Prototypes of the functions defined in src/town/minigame/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "shared/sprite_frame_state.h"

struct Arg1;
struct Arg2;
struct Obj;
struct ObjectPosition;

/* Casino slot-machine state and its three reel objects. */
typedef struct State8081FF68 {
    /* 0x00 */ u8 pad_00[0x48];
    /* 0x48 */ void *parent;
    /* 0x4C */ void *slot[3];
    /* 0x58 */ s32 work;
    /* 0x5C */ union { u16 u; s16 s; } mode;
    /* 0x5E */ union { u16 u; s16 s; } timer;
    /* 0x60 */ union { u16 u; s16 s; } timer2;
    /* 0x62 */ u16 flags;
    /* 0x64 */ u16 count;
} State8081FF68;

/* Body of the terminal-phase scene-text node. */
typedef struct TerminalSceneTextObject {
    /* 0x00 */ union { s16 s; u16 u; } state;
    /* 0x02 */ u8 pad_02[0xA];
    /* 0x0C */ void *owner;
    /* 0x10 */ u8 pad_10[0xC];
    /* 0x1C */ u16 flags;
} TerminalSceneTextObject;

/* Body of a linked line effect retired when its owner reaches phase eight. */
typedef struct RetiringLineEffectObject {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ void *linked_object;
} RetiringLineEffectObject;

/* Body shared by the zero-state text callback and its creator. */
typedef struct TextEntryObject {
    /* 0x00 */ s16 state;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ char *text;
    /* 0x08 */ s16 *value;
    /* 0x0C */ void *configuration;
    /* 0x10 */ s32 field_10;
    /* 0x14 */ s16 field_14;
    /* 0x16 */ s16 field_16;
    /* 0x18 */ s16 field_18;
    /* 0x1A */ s16 field_1A;
} TextEntryObject;

/* advance_actor_state_nearby_activation.c */
void advance_actor_state_nearby_activation(Rec_D_80082D58 *actor, s32 *position, s32 check_param, s32 check_mode);

/* advance_interaction_state_animating_cursor.c */
void advance_interaction_state_animating_cursor(struct Obj *self, struct Arg1 *position, struct Arg2 *cursor_data);

/* process_slot_machine_state.c */
void process_slot_machine_state(State8081FF68 *state, void *position);

/* propagate_linked_flag_if_clear.c */
void propagate_linked_flag_if_clear(void *record);

/* propagate_linked_flag_to_record.c */
void propagate_linked_flag_to_record(void *record);

/* retire_line_effect_at_phase_eight.c */
void retire_line_effect_at_phase_eight(RetiringLineEffectObject *record);

/* retire_scene_label_after_completion_flag.c */
void retire_scene_label_after_completion_flag(void *object);

/* retire_scene_text_after_terminal_phase.c */
void retire_scene_text_after_terminal_phase(TerminalSceneTextObject *context);

/* submit_text_zero_state_entry.c */
void submit_text_zero_state_entry(TextEntryObject *text_entry);

/* toggle_gym_sprite_by_scene_phase.c */
void toggle_gym_sprite_by_scene_phase(s16 **value_ptr, struct ObjectPosition *unused, SpriteFlagsView *object);

/* update_derived_value_and_flag.c */
void update_derived_value_and_flag(void *object);

/* update_object_state_and_size.c */
void update_object_state_and_size(void *object);

#endif
