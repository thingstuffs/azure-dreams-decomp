#include "town/paired_indicators.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
extern int abs(int);

#ifndef NULL
#define NULL 0
#endif

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);

extern u8 score_sprite_draw_callback_address[16];
extern u8 D_8028DFD8[16];
extern u8 D_8052E40C[0x2000];

/* Per-frame portrait step: lay out the panel on first entry, blink its tint and ease it toward its target. */
void animate_paired_threshold_indicators(PairedIndicators *hud) {
    u8 frame_pad[32];
    IndicatorChildNode *obj;
    SpriteFrameState *part;
    s32 i;
    s32 value;
    s32 table_index;
    s32 init_kind;
    s32 state;
    u16 counter;

    state = hud->state;
    switch (state) {
    case 0:
        hud->second_x = 0x410;
        hud->first_x = 0x340;
        hud->second_y = 0x348;
        hud->first_y = 0x348;
        hud->second_z = -0x60;
        hud->first_z = -0x60;

        init_kind = hud->kind;
        switch (init_kind) {
        case 0:
            value = -0x60;
            hud->second_target_z = value;
            hud->first_target_z = value;
            break;
        case 1:
            value = -0x98;
            hud->second_target_z = value;
            hud->first_target_z = value;
            break;
        case 2:
            value = -0x30;
            hud->second_target_z = value;
            hud->first_target_z = value;
            break;
        case 3:
            value = -0xB0;
            hud->first_target_z = value;
            value = -0x10;
            hud->second_target_z = value;
            break;
        case 4:
            value = -0x10;
            hud->first_target_z = value;
            value = -0xB0;
            hud->second_target_z = value;
        }

        for (i = 1; i >= 0; i--) {
            obj = func_800373DC(0x136);
            if (obj != NULL) {
                obj->header.update_callback = D_8052E40C;
                func_8003BC18(obj, score_sprite_draw_callback_address);
                part = obj->header.sprite;
                part->scale_y = 0x800;
                part->scale_x = 0x800;
                part->source = D_8028DFD8;
                part->unk_04 = 0;
                part->frame_ticks = 0;
                part->color.word = 0x00808080;
                obj->work.source = hud;
                obj->work.use_first = i;
            }
        }
        hud->state = 1;
        /* State zero continues with the per-frame update. */
    case 1:
        break;
    default:
        return;
    }

    counter = hud->blink_ticks + 1;
    hud->blink_ticks = counter;
    if ((counter >> 2) & 1) {
        table_index = hud->kind;
        if ((hud->owner->blink_flags &
             *(u16 *)(D_8052E40C + 0x1DD8 + (table_index * 2))) != 0) {
            hud->blink_color = 0x00FFFFFF;
        } else {
            hud->blink_color = 0;
        }
    } else {
        hud->blink_color = 0;
    }

    if (hud->owner->value >= hud->threshold) {
        s32 tx, x, ty, y;
        tx = hud->first_target_z;
        x = hud->first_z;
        ty = hud->second_target_z;
        y = hud->second_z;
        hud->first_z = x + ((tx - x) >> 1);
        hud->second_z = y + ((ty - y) >> 1);
        hud->flags &= ~1;
    } else {
        s32 x, y;
        x = hud->first_z;
        y = hud->second_z;
        x += (-0x60 - x) >> 1;
        y += (-0x60 - y) >> 1;
        hud->first_z = x;
        hud->second_z = y;
        if (abs(hud->second_z + 0x60) < 2) {
            hud->flags |= 1;
        }
    }
}
