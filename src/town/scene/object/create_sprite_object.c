#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/vector.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct FiveWords {
    s32 words[5];
} FiveWords;

typedef struct ObjectWithInitialWords {
    ObjectNodeHeader header;
    FiveWords initial_words;
} ObjectWithInitialWords;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern u8 D_8003C558[12];
extern u8 D_8052F2C8[];
extern u8 D_8028E170[];

/* Creates an object and initializes its position and sprite data. */
void create_sprite_object(FiveWords *init_data, s32 y_position)
{
    IntVector3 *position;
    u8 *object;
    SpriteFrameState *sprite;

    object = func_800373DC(0x136);
    if (object != NULL) {
        ((ObjectWithInitialWords *)object)->initial_words = *init_data;
        ((ObjectNodeHeader *)object)->unk_10 = D_8052F2C8;
        func_8003BC18(object, D_8003C558);
        position = ((ObjectNodeHeader *)object)->unk_08;
        sprite = ((ObjectNodeHeader *)object)->unk_0C;
        position->x = 0x05380000;
        position->y = y_position;
        position->z = 0xFFE00000;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->source = (s32)D_8028E170;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->color.word = 0x808080;
        sprite->flags = sprite->flags | 0x80;
    }
}
