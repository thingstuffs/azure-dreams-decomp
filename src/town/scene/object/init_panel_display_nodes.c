#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/dialogue.h"
#include "town/scene/object.h"
#include "town/scene/score_sprite_data.h"
#include "town/scene/flags.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/devkit/old_minigame_imports.h"




extern u8 D_80289454[];

extern void D_805268D4(TownCollectionPanel *);

extern u8 D_80527250[];
extern u8 D_80527D5C[];
extern u8 D_8052FF84[];
extern char *D_805300BC[];
extern s16 D_80530666[];
extern s16 D_805306D6[];
extern char D_805306D8[4];

/* Initializes the town display nodes, panel lines, and content entries. */
s32 init_panel_display_nodes(void) {
    TownCollectionText content_record;
    TownCollectionPanel rect_record;
    s16 *clear_entry;
    s16 *offset_entry;
    s32 remaining;
    s32 initial_offset;
    u8 * offset_addr;
    s32 clear_addr;
    s32 state_page;
    s32 initial_state;
    s16 line_x;
    s32 color_or_flags;
    s32 panel_width;
    ObjectNodeHeader *node;
    TownCollectionSequence *root;
    SpriteFrameState *render_state;
    TownCollectionActor *actor;

    root = 0;
    func_80058F88(0x704);
    func_800351A8(0x3C, 0);
    func_800351A8(0x3D, 0);
    node = func_800374FC(1, &scene_object_factory_data);
    if (node != 0) {
        root = NODE_BODY(node);
        node->update_callback = D_80527D5C;
    }
    node = func_800374FC(0x136, &scene_object_factory_data);
    root->owner = node;
    if (node != 0) {
        node->update_callback = D_80527250;
        func_8003BC18(node, score_sprite_draw_callback_address);
        render_state = node->sprite;
        node->position->x.v = 0x03A00000;
        node->position->y.v = 0x01E00000;
        node->position->z.v = 0x00200000;
        actor = NODE_BODY(node);
        actor->sequence = root;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        func_80034A1C(render_state, D_80289454, 0);
        render_state->color.word = 0x00808080;
        func_8023FAE8(NODE_BODY(node), node->position, D_8052FF84);
    }

    remaining = 7;
    initial_offset = 0x30;
    offset_addr = (u8 *)D_805306D6;
    offset_entry = (s16 *)offset_addr;
    clear_addr = (s32)&D_80530666;
    clear_entry = (s16 *)clear_addr;
    do {
        {
            *clear_entry = 0;
            *offset_entry = initial_offset;
            offset_entry--;
            remaining--;
            clear_entry--;
        }
    } while (remaining >= 0);

    color_or_flags = 0x00404040;
    rect_record.color = color_or_flags;
    color_or_flags = rect_record.flags;
    initial_state = 0x3020;
    state_page = 0x80530000;
    *(s32 *)(state_page + 0x6D8) = initial_state;
    rect_record.x = 0x30;
    rect_record.y = 0xA0;
    panel_width = 0xE0;
    rect_record.width = panel_width;
    rect_record.height = 0x22;
    rect_record.style = 2;
    rect_record.state = 0;
    rect_record.timer = 0x10;
    rect_record.sequence = root;
    color_or_flags |= 3;
    rect_record.flags = color_or_flags;
    create_object_payload_registers_callback(fade_panel_after_linked_flag, &rect_record);

    rect_record.y = 0xA2;
    rect_record.width = 1;
    rect_record.height = 0x1E;
    rect_record.style = 0;
    rect_record.color = 0x00808080;
    rect_record.state = 0;
    rect_record.sequence = root;
    rect_record.flags |= 0xFFFD;
    remaining = 8;
    line_x = 0xE0;
    do {
        rect_record.x = line_x;
        create_object_payload_registers_callback(D_805268D4, &rect_record);
        remaining--;
        line_x -= 0x10;
    } while (remaining >= 0);

    rect_record.x = 0x32;
    rect_record.y = 0xB0;
    rect_record.width = 0xDC;
    rect_record.height = 1;
    create_object_payload_registers_callback(D_805268D4, &rect_record);

    {
        char **content_ptr;
        s16 content_x;
        s32 color_or_content;
        char *content;

        color_or_content = 0x00808080;
        content_record.color = color_or_content;
        /* The word at 0x805300C0 points to the SCORE label. */
        color_or_content = *(s32 *)0x805300C0;
        content_record.x = 0x34;
        content_record.y = 0xB6;
        content_record.style = 3;
        content_record.flags = 2;
        content_record.field_1A = 0x7C80;
        content_record.state = 0;
        content_record.timer = 0x10;
        content_record.sequence = root;
        content_record.text = (char *)color_or_content;
        allocate_record_and_store_three_blocks(retire_older_panel_text_on_completion, &content_record);

        content_record.y = 0xA4;
        clear_addr = 8;
        content_x = 0xE4;
        content_ptr = D_805300BC;
        do {
            {
                TownCollectionTextUpdate entry_template;

                entry_template = retire_older_panel_text_on_completion;
                content = *content_ptr;
                content_record.x = content_x;
                content_record.text = content;
                allocate_record_and_store_three_blocks(entry_template, &content_record);
                content_x -= 0x10;
                content_ptr--;
                clear_addr--;
            }
        } while (clear_addr >= 0);

        content_record.x = 0xF4;
        content_record.y = 0xB6;
        content_record.text = D_805306D8;
        allocate_record_and_store_three_blocks(update_panel_aggregate_value, &content_record);
    }
    return 0;
}
