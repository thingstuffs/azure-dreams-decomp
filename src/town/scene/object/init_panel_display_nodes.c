#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/scene/flags.h"
#include "shared/vector.h"

typedef struct S_8080C324_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xB8];
    void * unk_CC;
} S_8080C324_0;   /* node in init_panel_display_nodes */

typedef struct S_8080C324_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080C324_1;   /* root in init_panel_display_nodes */

typedef struct S_8080C324_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8080C324_2;   /* inner in init_panel_display_nodes */

   /* ((S_8080C324_0 *)node)->unk_08 in init_panel_display_nodes */

typedef struct {
    s16 f0;
    s16 f2;
    void *f4;
    s32 f8;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    s16 f14;
    u16 f16;
    u8 pad18[0x10];
} Record28;

typedef struct {
    s16 f0;
    s16 f2;
    s32 f4;
    u8 pad8[4];
    void *fC;
    s32 f10;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s16 f1C;
    u8 pad1E[0x12];
} Record30;

extern void func_80034A1C(void *, void *, s32);
extern void func_800351A8(s32, s32);
extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern void func_80058F88(s32);
extern void func_8023FAE8(void *, void *, void *);
extern void allocate_record_and_store_three_blocks(void *, void *);
extern void create_object_payload_registers_callback(void *, void *);

extern u8 score_sprite_draw_callback_address[];
extern u8 D_80289454[];

extern u8 D_805268D4[];
extern u8 D_80526970[];

extern u8 D_80527250[];
extern u8 D_80527D5C[];
extern u8 D_8052FF84[];
extern s32 D_805300BC[];
extern s16 D_80530666[];
extern s16 D_805306D6[];
extern s32 D_805306D8[];

/* Initializes the town display nodes, panel lines, and content entries. */
s32 init_panel_display_nodes(void) {
    Record30 content_record;
    Record28 rect_record;
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
    void *node;
    S_8080C324_1 *root;
    S_8080C324_2 *render_state;

    root = 0;
    func_80058F88(0x704);
    func_800351A8(0x3C, 0);
    func_800351A8(0x3D, 0);
    node = func_800374FC(1, &scene_object_factory_data);
    if (node != 0) {
        root = (u8 *)node + 0x20;
        ((S_8080C324_0 *)node)->unk_10 = (s32)D_80527D5C;
    }
    node = func_800374FC(0x136, &scene_object_factory_data);
    root->unk_04 = node;
    if (node != 0) {
        ((S_8080C324_0 *)node)->unk_10 = (s32)D_80527250;
        func_8003BC18(node, score_sprite_draw_callback_address);
        render_state = ((S_8080C324_0 *)node)->unk_0C;
        ((IntVector3 *)(((S_8080C324_0 *)node)->unk_08))->x = 0x03A00000;
        ((IntVector3 *)(((S_8080C324_0 *)node)->unk_08))->y = 0x01E00000;
        ((IntVector3 *)(((S_8080C324_0 *)node)->unk_08))->z = 0x00200000;
        ((S_8080C324_0 *)node)->unk_CC = root;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        func_80034A1C(render_state, D_80289454, 0);
        render_state->unk_0C = 0x00808080;
        func_8023FAE8((u8 *)node + 0x20, ((S_8080C324_0 *)node)->unk_08, D_8052FF84);
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
    rect_record.f8 = color_or_flags;
    color_or_flags = rect_record.f16;
    initial_state = 0x3020;
    state_page = 0x80530000;
    *(s32 *)(state_page + 0x6D8) = initial_state;
    rect_record.fC = 0x30;
    rect_record.fE = 0xA0;
    panel_width = 0xE0;
    rect_record.f10 = panel_width;
    rect_record.f12 = 0x22;
    rect_record.f14 = 2;
    rect_record.f0 = 0;
    rect_record.f2 = 0x10;
    rect_record.f4 = root;
    color_or_flags |= 3;
    rect_record.f16 = color_or_flags;
    create_object_payload_registers_callback(fade_panel_after_linked_flag, &rect_record);

    rect_record.fE = 0xA2;
    rect_record.f10 = 1;
    rect_record.f12 = 0x1E;
    rect_record.f14 = 0;
    rect_record.f8 = 0x00808080;
    rect_record.f0 = 0;
    rect_record.f4 = root;
    rect_record.f16 |= 0xFFFD;
    remaining = 8;
    line_x = 0xE0;
    do {
        rect_record.fC = line_x;
        create_object_payload_registers_callback(D_805268D4, &rect_record);
        remaining--;
        line_x -= 0x10;
    } while (remaining >= 0);

    rect_record.fC = 0x32;
    rect_record.fE = 0xB0;
    rect_record.f10 = 0xDC;
    rect_record.f12 = 1;
    create_object_payload_registers_callback(D_805268D4, &rect_record);

    {
        s32 *content_ptr;
        s16 content_x;
        s32 color_or_content;
        s32 content;

        color_or_content = 0x00808080;
        content_record.f10 = color_or_content;
        color_or_content = (s32)0x80530000;
        color_or_content = *(s32 *)(color_or_content + 0xC0);
        content_record.f14 = 0x34;
        content_record.f16 = 0xB6;
        content_record.f18 = 3;
        content_record.f1C = 2;
        content_record.f1A = 0x7C80;
        content_record.f0 = 0;
        content_record.f2 = 0x10;
        content_record.fC = root;
        content_record.f4 = color_or_content;
        allocate_record_and_store_three_blocks(D_80526970, &content_record);

        content_record.f16 = 0xA4;
        clear_addr = 8;
        content_x = 0xE4;
        content_ptr = D_805300BC;
        do {
            {
                void *entry_template;
                void *entry_record;

                entry_template = D_80526970;
                content = *content_ptr;
                content_record.f14 = content_x;
                content_record.f4 = content;
                allocate_record_and_store_three_blocks(entry_template, (&content_record));
                content_x -= 0x10;
                content_ptr--;
                clear_addr--;
            }
        } while (clear_addr >= 0);

        content_record.f14 = 0xF4;
        content_record.f16 = 0xB6;
        content_record.f4 = (s32)D_805306D8;
        allocate_record_and_store_three_blocks(update_panel_aggregate_value, &content_record);
    }
    return 0;
}
