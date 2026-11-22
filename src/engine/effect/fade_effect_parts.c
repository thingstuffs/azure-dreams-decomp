#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/menu/selection_menu.h"
#include "engine/effect.h"
#include "engine/item.h"

typedef struct S_80050CDC_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80050CDC_0;   /* arg2 in fade_effect_parts */

typedef struct S_80050CDC_1 {
    u8 unk_00;
    u8 unk_01;
    union { u16 u16; u8 u8; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
} S_80050CDC_1;   /* part in fade_effect_parts */

extern s32 D_800814A0;

/* Update and fade the effect parts, then signal completion when the timer expires. */
void fade_effect_parts(MenuSelectionBody *effect, void *unused, void *parts_arg)
{
    S_80050CDC_0 *parts = parts_arg;
    s32 ticks_left;
    u8 color;
    S_80050CDC_1 *part;

    part = parts->unk_08;
    part->unk_02.u16 -= 0x40;
    part = parts->unk_04;
    part->unk_0C += 0x20;
    part = parts->unk_04;
    part->unk_08 -= 0x40;
    part = parts->unk_04;
    color = part->unk_02.u8 - 0x20;
    part->unk_02.u8 = color;
    part->unk_01 = color;
    part->unk_00 = color;

    ticks_left = effect->fade_ticks - 1;
    effect->fade_ticks = ticks_left;
    if (ticks_left == -1) {
        u16 *flags;
        release_null_terminated_entries(effect->buffers);
        flags = &NODE_HEADER(effect)->flags;
        *flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
