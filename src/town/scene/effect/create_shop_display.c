#include "common.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"
#include "town/scene/effect.h"
#include "town/scene/object.h"
#include "town/data.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/score_sprite_data.h"
#define AZ_FOREIGN_LOCAL_FUNC_80034A1C
#include "town/devkit/old_minigame_imports.h"
#undef AZ_FOREIGN_LOCAL_FUNC_80034A1C

typedef struct S_80813AB0_0 {
    u8 pad_00[0x8];
    union { u32 * p; void * p2; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    void * unk_24;
    union { void * p; u32 i; } unk_28;   /* accessed as both */
    union {
        struct { void * v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_2C;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_30;   /* overlapping accesses */
    s16 unk_34;
    u16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x30];
    void * unk_6C;
    u8 pad_70[0x6];
    s16 unk_76;
} S_80813AB0_0;   /* obj in func_80813AB0 */

typedef struct RootPair {
    char *entries[2];
} RootPair;

extern s32 func_80034A1C(); /* Unprototyped: this site's argument count or types differ from the foreign program's import prototype */

extern u8 menu_entry_draw_callback_address[];
extern u8 menu_cursor_object_template[];
extern RootPair D_80526790;
extern RootPair D_805267A0;
extern u8 D_805267A8[];
extern u8 D_805267AC[];
extern u8 D_8052EA14[];
extern u8 D_8052EDB8[];
extern u8 D_8052FD0C[];
extern u8 D_8052FD60[];

extern u8 D_805301F0[];

/* Build the shop display: the root object plus three item panels and their sprites. */
s32 create_shop_display(void)
{
    RootPair roots[2];
    TownScoreCounterView *base;
    ObjectNodeHeader *obj;
    RisingScorePanelNode **slot;
    s32 label_y;
    RisingScorePanel *panel;
    RisingScoreTextDisplay *label;
    RisingScoreFade *fade;
    u8 *copy_src;
    s32 i;
    s32 scale;
    s32 y;
    u8 value;

    base = 0;
    roots[0] = D_80526790;
    roots[1] = D_805267A0;
    func_8052FE94(0x5A);
    func_800351A8(0x3B, 0);

    obj = func_800373DC(2);
    copy_src = D_805267A8;
    i = 2;
    if (obj != 0) {
        base = NODE_BODY(obj);
        obj->update_callback = D_8052EDB8;
        base->area = func_80071494() & 1;
    }

    scale = 0x1000;
    slot = &base->panels[2];
    do {
        obj = func_800373DC(0x136);
        *slot = (RisingScorePanelNode *)obj;
        if (obj != 0) {
            SpriteFrameState *part;
            ObjectPosition *position;

            obj->update_callback = D_8052EA14;
            func_8003BC18(obj, score_sprite_draw_callback_address);
            part = obj->sprite;
            position = obj->position;
            panel = NODE_BODY(obj);
            position->x.v = 0x05600000;
            position->y.v = (i << 22) + 0x03E00000;
            position->z.v = 0x00800000;
            position->velocity_z = 0xFFFC0000;
            panel->score = base;
            panel->column = i;
            part->scale_y = scale;
            part->scale_x = scale;
            func_80034A1C(part, shop_panel_sprite_entries, 0, position);
            part->color.word = 0x00808080;
            panel->resource = D_805267AC;
            func_8023FA58(panel->work, obj->position, D_805301F0);
        }
        i--;
        slot--;
    } while (i >= 0);

    i = 1;
    y = 0x2C;
    do {
        obj = func_800374FC(1, &scene_object_factory_data);
        if (obj != 0) {
            label = NODE_BODY(obj);
            obj->update_callback = D_8052FD0C;
            func_8003BC18(obj, menu_entry_draw_callback_address);
            label->x = 0x20;
            label->field_18 = 3;
            label->field_1A = 0x7C80;
            label->y = y;
            label->color = 0x00808080;
            label->text = roots[0].entries[i];
            label->controller = base;
        }
        i--;
        y -= 0xC;
    } while (i >= 0);

    i = 1;
    {
        u8 *copy_ptr;

        copy_ptr = copy_src + 1;
        do {
            char *dst_first;
            char *dst_second;

            value = *copy_ptr;
            copy_ptr--;
            dst_first = roots[1].entries[0];
            dst_second = roots[1].entries[1];
            dst_first += i;
            dst_second += i;
            i--;
            *dst_second = value;
            *dst_first = value;
        } while (i >= 0);
    }

    i = 1;
    label_y = 0x2C;
    do {
        obj = func_800374FC(1, &scene_object_factory_data);
        if (obj != 0) {
            label = NODE_BODY(obj);
            obj->update_callback = D_8052FD60;
            func_8003BC18(obj, menu_entry_draw_callback_address);
            label->x = 0x50;
            label->field_18 = 3;
            label->field_1A = 0x7C80;
            label->y = label_y;
            label->color = 0x00808080;
            label->text = roots[1].entries[i];
            switch (i) {
            case 0:
                label->value = &base->completed;
                break;
            case 1:
                label->value = &base->score;
                break;
            }
            label->controller = base;
        }
        i--;
        label_y -= 0xC;
    } while (i >= 0);

    obj = func_800374FC(1, &scene_object_factory_data);
    if (obj != 0) {
        s32 final_dim;
        u32 final_color;

        fade = NODE_BODY(obj);
        obj->update_callback = fade_effect_color_until_done;
        func_8003BC18(obj, menu_cursor_object_template);
        final_color = 0x00404040;
        final_dim = 0x1C;
        fade->field_0C = final_dim;
        fade->field_0E = final_dim;
        fade->field_10 = 0x48;
        fade->field_12 = final_dim;
        fade->field_14 = 2;
        fade->color = final_color;
        fade->controller = base;
        fade->flags |= 1;
    }
    return 0;
}
/* The two RootPair copies account for four pointers on the stack. The body
 * stores the number pointer in each switch arm before storing the controller. */
