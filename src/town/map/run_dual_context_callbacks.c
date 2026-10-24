#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(s32 *);

typedef struct S_func_800A496C_0 {
    u8 pad_00[0x24];
    Callback unk_24;
    Callback unk_28;
} S_func_800A496C_0;

typedef struct S_func_800A496C_1 {
    u8 pad_00[0x1C];
    Callback unk_1C;
    Callback unk_20;
} S_func_800A496C_1;

typedef struct S_func_800A496C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_func_800A496C_2;

extern void update_view_gray_level(void);
extern s16 map_scene_selector_alias;
extern s8 map_wide_culling;
extern s32 D_80100D90;
extern s32 town_secondary_callback_state[];
extern s32 town_camera_chase_state[];

/* Run both contexts' callbacks, then update the flag from the current mode and threshold. */
void run_dual_context_callbacks(void)
{
    S_func_800A496C_0 *primary_context;
    S_func_800A496C_1 *secondary_context;
    Callback callback;

    primary_context = (S_func_800A496C_0 *)town_camera_chase_state;
    secondary_context = (S_func_800A496C_1 *)town_secondary_callback_state;

    callback = primary_context->unk_24;
    if (callback != NULL) {
        callback((s32 *)primary_context);
    }
    if (secondary_context->unk_1C != NULL) {
        secondary_context->unk_1C((s32 *)secondary_context);
    }
    if (primary_context->unk_28 != NULL) {
        primary_context->unk_28((s32 *)primary_context);
    }
    if (secondary_context->unk_20 != NULL) {
        secondary_context->unk_20((s32 *)secondary_context);
    }

    update_view_gray_level();
    if (map_scene_selector_alias != 0xC) {
        if (((S_func_800A496C_2 *)D_80100D90)->unk_06 < 0x600) {
            map_wide_culling = 1;
            return;
        }
        map_wide_culling = 0;
    }
}
