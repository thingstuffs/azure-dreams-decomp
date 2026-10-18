#include "common.h"

typedef struct S_80083160_ctx
{
    u8 pad[0x8AC];
    s32 ot[9];
    void *cur;
}
S_80083160_ctx;
extern S_80083160_ctx *D_80083160[3];
extern u8 D_801C9E40[];
typedef struct S_80081480
{
    s32 field_0;
    s8 pad[8];
}
S_80081480;
typedef struct S_8008148C
{
    s32 field_0;
    s8 pad[8];
}
S_8008148C;
extern S_80081480 D_80081480;
extern S_8008148C D_8008148C;
extern u8 D_80080A84[16];
extern u8 D_80080A85[16];
extern void PutDispEnv(void *a0);
extern void PutDrawEnv(void *a0);
extern void DrawOTag(s32 *a0);
extern void ClearOTagR(s32 *a0, s32 a1);
extern void DrawSync(s32 a0);
extern void VSync(s32 a0);
extern void run_runtime_callbacks(void);
extern void dispatch_and_clear_four_pointer_slots(void);
extern void func_8003E758(void);
extern void func_800542BC(void);
extern void update_controller_buttons_and_triggers(void);
extern void tick_screen_fade_slots(void);
extern void func_800400B8(void);
/* Draw the current frame, swap draw buffers, and wait for optional vertical synchronization. */
void render_object_scene_frame(void)
{
    void *next_buffer;
    s32 saved_value;
    u32 skip_vsync;
    u32 vsync_mode;

    PutDispEnv(((u8 *) D_80083160[0]) + 0x5C);
    PutDrawEnv(D_80083160[0]);
    DrawOTag(&D_80083160[0]->ot[8]);
    func_8003E758();
    func_800542BC();
    saved_value = D_8008148C.field_0;
    *(s32 *)0x80081480 = saved_value;
    run_runtime_callbacks();
    update_controller_buttons_and_triggers();
    next_buffer = D_801C9E40;
    if (D_80083160[0] == ((S_80083160_ctx *) next_buffer)) {
        next_buffer = next_buffer + 0x108D4;
    }
    else {
        next_buffer = D_801C9E40;
    }
    D_80083160[0] = (S_80083160_ctx *) next_buffer;
    ClearOTagR((s32 *) (((u8 *) next_buffer) + 0x70), 0x218);
    D_80083160[0]->cur = ((u8 *) D_80083160[0]) + 0x8D4;
    tick_screen_fade_slots();
    func_800400B8();
    dispatch_and_clear_four_pointer_slots();
    DrawSync(0);
    skip_vsync = D_80080A85[0];
    if (skip_vsync == 0) {
        skip_vsync = 0x80080000;
        vsync_mode = skip_vsync;
        vsync_mode = *(u8 *)(vsync_mode + 0xA84);
        VSync((vsync_mode != 1) ? (2) : (0));
    }
}
