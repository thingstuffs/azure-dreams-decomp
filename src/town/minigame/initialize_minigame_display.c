#include "shared/object_node.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022290_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80022290_1;   /* data1 in initialize_minigame_display */

typedef struct S_80022290_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_80022290_3;   /* data2 in initialize_minigame_display */

typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

extern void register_node(void *, void *);
extern void *decode_fullwidth_text(void *, void *, s32);
extern void create_positioned_callback_object(void *, void *, void *);

extern Packed8 D_8002021C;
extern u8 D_800223D8[8];
extern u8 D_800223E0[8];
extern u8 D_800223E8[8];
extern void *D_80024468;
extern void *D_8002446C;
extern s32 text_sprite_builder_address[4];
extern s32 display_registration_tag;
extern u8 D_800782EC[8];

/* Initializes display resources and creates rectangle and image objects. */
void initialize_minigame_display(void *context)
{
    Packed8 setup_words;
    ObjectNodeHeader *rect_obj;
    S_80022290_1 *rect_data;
    ObjectNodeHeader *image_obj;
    S_80022290_3 *image_data;
    void *image_resource;

    setup_words = D_8002021C;
    create_positioned_callback_object(&setup_words, D_800223D8,
                  decode_fullwidth_text(context, D_8002446C, 0));
    create_positioned_callback_object((u8 *)&setup_words + 4, D_800223D8, D_800782EC);

    rect_obj = allocate_flagged_object_node(1);
    if (rect_obj != NULL) {
        rect_data = ((void *)rect_obj) + 0x20;
        rect_obj->update_callback = D_800223E0;
        register_node(rect_obj, &display_registration_tag);
        rect_data->unk_0C = 0xB8;
        rect_data->unk_0E = 0x14;
        rect_data->unk_10 = 0x7C;
        rect_data->unk_12 = 0x18;
        rect_data->unk_16 = 1;
        rect_data->unk_08 = 0x402020;
    }

    image_obj = allocate_flagged_object_node(1);
    if (image_obj != NULL) {
        image_data = ((void *)image_obj) + 0x20;
        image_obj->update_callback = D_800223E8;
        register_node(image_obj, text_sprite_builder_address);
        image_data->unk_14 = 0xF0;
        image_data->unk_16 = 0x20;
        image_data->unk_18 = 3;
        image_resource = D_80024468;
        image_data->unk_1A = 0x7C80;
        image_data->unk_10 = 0x808080;
        image_data->unk_04 = image_resource;
    }
}
