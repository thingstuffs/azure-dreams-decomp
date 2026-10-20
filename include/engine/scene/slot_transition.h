#ifndef SLUS_SLOT_TRANSITION_H
#define SLUS_SLOT_TRANSITION_H
#include "common.h"
typedef struct { s32 field0; s32 pad4; s32 pad8; } SlotTransitionWords3;
#include "shared/transition_slots.h"
#include "shared/runtime_dispatch.h"
extern volatile s32 D_80081480;
extern volatile s32 D_8008148C;
extern s16 D_800814E8;
extern u8 D_80082E6E[];
extern void update_controller_buttons_and_triggers(void);
extern void upload_dispatch_entry_images(s32);
extern void upload_dispatch_entry_vram_rows(s32);
extern void load_dispatch_entry_files(s32);
extern s32 run_dispatch_entry_callbacks(s32);
extern void scene_save_previous_mode_and_reset_callbacks(void);
extern s16 reserve_runtime_slot(s16, s16);
extern void set_scene_phase_callback(s32);
extern void render_scene_frame_with_timing(void);
extern void update_shoulder_button_angle(void);
extern void func_8003D92C(void);
void func_80041AE4(void);
void func_80041B98(void);
void func_80041BE4(void);
void func_80041C64(void);
extern s16 D_80081500;
extern void render_object_scene_frame(void);
void func_80043D04(void);
void func_80043DB8(void);
void func_80043E04(void);
void func_80043E60(void);
#endif
