#include "common.h"

#include "common.h"
#include "sdk/libgpu.h"
#include "engine/effect/screen_fade.h"
#include "engine/effect.h"

typedef struct
{
    u32 tag;
    char pad4[8];
}
S_80053604_TPage;
typedef struct
{
    u32 tag;
    u32 rgbc;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
}
S_80053604_PolyF4;
typedef struct
{
    char pad0[0x70];
    u32 otHead;
    char pad1[0x8D0 - 0x74];
    void *nextPrim;
}
S_80053604_RenderState;
typedef struct
{
    S_80053604_RenderState *renderState;
    char pad0[0x1C];
}
S_80053604_Main;
extern S_80053604_Main g_game_work;
/* Draws a full-screen additive or subtractive fade, advances its timer, and reports completion. */
s16 render_screen_fade_increasing_intensity(TransitionSlot *fade)
{
    u32 addr_mask;
    register u32 tag_mask;
    u32 color;
    S_80053604_TPage *tpage;
    S_80053604_PolyF4 *poly;
    S_80053604_Main *main_state;
    s32 blend_mode;
    s32 done;
    s32 elapsed;
    s16 duration;
    s32 scaled_elapsed;
    tpage = (S_80053604_TPage *) g_game_work.renderState->nextPrim;
    g_game_work.renderState->nextPrim = (void *) (((u8 *) tpage) + (sizeof(S_80053604_TPage)));
    done = 0;
    main_state = &g_game_work;
    poly = (S_80053604_PolyF4 *) g_game_work.renderState->nextPrim;
    g_game_work.renderState->nextPrim = (void *) (((u8 *) poly) + (sizeof(S_80053604_PolyF4)));
    blend_mode = 1;
    if (fade->unk_6 == 0) {
        blend_mode = 2;
    }
    SetDrawMode(tpage, 0, 0, GetTPage(0, blend_mode, 0, 0) & 0xFFFF, 0);
    elapsed = fade->unk_2;
    duration = fade->param;
    if (elapsed > duration) {
        done = 1;
    }
    if (elapsed >= duration) {
        color = 0xFFFFFF;
    }
    else {
        scaled_elapsed = elapsed << 8;
        color = scaled_elapsed / duration;
        color = color + ((color << 8) + (color << 16));
    }
    if (!done) {
        fade->unk_2 = ((u16) fade->unk_2) + 1;
    }
    poly->rgbc = color;
    SetPolyF4(poly);
    SetSemiTrans(poly, 1);
    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: slus/w_80053604). */
    do {
        addr_mask = 0x00FFFFFF;
    } while (0);
    poly->x3 = 320;
    poly->x2 = 320;
    poly->x1 = 0;
    poly->x0 = 0;
    poly->y2 = 0;
    poly->y0 = 0;
    tag_mask = 0xFF000000;
    poly->y3 = 224;
    poly->y1 = 224;
    poly->tag = (poly->tag & tag_mask) | (main_state->renderState->otHead & addr_mask);
    main_state->renderState->otHead = (main_state->renderState->otHead & tag_mask) | (((u32) poly) & addr_mask);
    tpage->tag = (tpage->tag & tag_mask) | (main_state->renderState->otHead & addr_mask);
    main_state->renderState->otHead = (main_state->renderState->otHead & tag_mask) | (((u32) tpage) & addr_mask);
    return done;
}
