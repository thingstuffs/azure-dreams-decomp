#include "common.h"
#include "town/minigame.h"
#include "town/scene.h"
#include "engine/node.h"
#include "engine/runtime.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "slus.h"
#include "sdk/libgpu.h"

typedef struct CasinoNode CasinoNode;

/* Display root: the betting model and the three payout digits it owns. */
typedef struct CasinoDisplay {
    CasinoNode *main;
    CasinoNode *digit[3];
} CasinoDisplay;

/* Betting model body; its mode-three record ends with the callback data word. */
typedef struct CasinoMainBody {
    CasinoDisplay *owner;
    u8 pad_04[8];
    u8 mode_record[0x48];
    void *callback_data;
    ObjectPosition home_position;
} CasinoMainBody;

/* Payout digit body; index selects the digit's mesh and screen column. */
typedef struct CasinoDigitBody {
    u8 pad_00[4];
    CasinoDisplay *owner;
    u8 mode_record[0x48];
    void *callback_data;
    s16 index;
} CasinoDigitBody;

struct CasinoNode {
    ObjectNodeHeader header;
    union {
        CasinoDisplay display;
        CasinoMainBody main;
        CasinoDigitBody digit;
    } body;
};

/* Builds the casino display: the betting model and three payout digits under
 * one display root, then saves the palette row the digits recolour. */
s32 initialize_casino_minigame(void)
{
    CasinoDisplay *display = 0;
    SceneImageRect rect = D_80020018;
    void *callback_data = D_80020014;
    CasinoNode *node;
    CasinoMainBody *main;
    CasinoDigitBody *digit;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    s32 index;

    noop_display_setup_hook();
    pickup_reward_total[0] = 0;
    initialize_minigame_display(D_80024568);
    set_resident_bit(0xA4);

    node = allocate_flagged_object_node(2);
    if (node != 0) {
        display = &node->body.display;
        node->header.update_callback = update_betting_effect;
    }

    node = allocate_flagged_object_node(0x136);
    display->main = node;
    if (node != 0) {
        main = &node->body.main;
        register_node(&node->header, draw_linked_lit_meshes);
        position = node->header.position;
        sprite = node->header.sprite;
        node->header.update_callback = update_effect_position_spin_phases;
        main->owner = display;
        sprite->scale_x = ONE;
        sprite->scale_y = ONE;
        sprite->offset_x = ONE;
        sprite->depth_bias = 3;
        sprite->source = 45;
        sprite->clut = 0;
        sprite->flags = 0;
        sprite->tpage_abr = 0;
        sprite->angle_x = 0;
        sprite->angle_y = 0;
        sprite->angle_z = 0;
        sprite->unk_00 = 0;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->color.word = 0x00808080;
        position->x.v = 0x03600000;
        position->y.v = 0x03600000;
        position->z.v = 0;
        main->home_position = *position;
        main->callback_data = callback_data;
        configure_the_set_mode_n_3(main->mode_record, &main->home_position, D_80024408);
    }

    index = 2;
    do {
        node = allocate_flagged_object_node(0x136);
        display->digit[index] = node;
        if (node != 0) {
            register_node(&node->header, draw_linked_lit_meshes);
            digit = &node->body.digit;
            position = node->header.position;
            node->header.update_callback = update_minigame_transition;
            digit->owner = display;
            digit->index = index;
            sprite = node->header.sprite;
            sprite->clut = 0;
            sprite->flags = 0;
            sprite->tpage_abr = 0;
            sprite->angle_x = 0;
            sprite->angle_y = 0;
            sprite->angle_z = 0;
            sprite->unk_00 = 0;
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->scale_x = ONE;
            sprite->scale_y = ONE;
            sprite->offset_x = ONE;
            sprite->color.word = 0x00808080;
            sprite->source = D_80024444[digit->index];
            position->x.v = (index << 23) + 0x04600000;
            position->y.v = 0x03600000;
            position->z.v = 0;
            digit->callback_data = callback_data;
            configure_the_set_mode_n_3(digit->mode_record, position, D_800243F0);
        }
        index--;
    } while (index >= 0);

    rect.x = 0x70;
    rect.y = 0x1C1;
    rect.w = 0x30;
    rect.h = 1;
    StoreImage(&rect, D_800245C8);
    DrawSync(0);
    return 0;
}
