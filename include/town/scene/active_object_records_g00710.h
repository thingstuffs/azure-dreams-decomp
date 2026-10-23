#ifndef TOWN_SCENE_ACTIVE_OBJECT_RECORDS_G00710_H
#define TOWN_SCENE_ACTIVE_OBJECT_RECORDS_G00710_H
/* Build and submit active object records (G00710). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80470EB8, CL:town/func_80470F3C, PD:town/image_3ef000:8001B318. */

/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "script_symbols.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"

typedef struct S_80017EB8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80017EB8_3;

typedef struct S_80017EB8_4 {
    s16 unk_00;
} S_80017EB8_4;

typedef struct S_80017EB8_0 {
    u8 unk_00;
    u8 unk_01;
} S_80017EB8_0;

typedef struct {
    u8 bytes[4];
} __attribute__((packed)) Copy4;

typedef struct S_80018174_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80018174_0;

extern s32 func_8001A510(s32 flag_id);
extern u8 D_8001B1C0[];
/* extern */
void func_80018914(void *);
extern s32 D_8001B31C;

extern s8 *func_80018824(s8 *buffer, s32 length);
extern S_80018174_0 *scene_registered_event_handle;

/* Functions defined in this translation unit. */
s32 check_selected_entry_8(S_80017EB8_0 *position);
u8 *record_check_returned(void *unused);
void prepare_passes_active_object_callback(void);
void prepare_active_object_callback(void);
s32 cache_value_at_offset_0x24(void);

#endif
