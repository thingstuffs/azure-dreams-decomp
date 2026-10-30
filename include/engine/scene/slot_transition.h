#ifndef SLUS_SLOT_TRANSITION_H
#define SLUS_SLOT_TRANSITION_H
#include "common.h"
typedef struct { s32 field0; s32 pad4; s32 pad8; } SlotTransitionWords3;
#include "shared/transition_slots.h"
#include "shared/runtime_dispatch.h"
extern volatile s32 gpu_scratch_write_pointer;
extern volatile s32 gpu_scratch_buffer_base;
extern s16 transition_runtime_slot_index;
extern u8 D_80082E6E[];
extern void update_controller_buttons_and_triggers(void);
extern void upload_dispatch_entry_images(s32);
extern void upload_dispatch_entry_vram_rows(s32);
extern void load_dispatch_entry_files(s32);
extern s32 run_dispatch_entry_callbacks(u16 entry_id);
extern void scene_save_previous_mode_and_reset_callbacks(void);
extern s16 reserve_runtime_slot(s16, s16);
extern void set_scene_phase_callback(s32);
extern void render_scene_frame_with_timing(void);
extern void update_shoulder_button_angle(void);
extern void func_8003D92C(void);
void load_scene_dispatch_resources(void);
void render_scene_until_runtime_slot_idle(void);
void await_scene_confirmation_and_reserve_slot(void);
void finish_scene_when_runtime_slot_idle(void);
extern s16 secondary_transition_slot_index;
extern void render_object_scene_frame(void);
void load_object_scene_dispatch_resources(void);
void render_object_scene_until_slot_idle(void);
void await_object_scene_confirmation(void);
void finish_object_scene_when_slot_idle(void);
#endif
