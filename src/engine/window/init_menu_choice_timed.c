#include "common.h"
#include "engine/window.h"

typedef struct Child {
    u8 unk00[0x22];
    s16 unk22;
    u8 unk24[2];
    u8 unk26;
    u8 unk27;
    u8 unk28[0x58];
    u32 unk80;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4d];
    u8 unk4d;
    u8 unk4e[0x16];
    s16 unk64;
    u8 unk66[2];
    void (*unk68)(Object *);
    u8 unk6c[8];
    Child *child;
};

extern u8 menu_choice_display_data[9];
extern u8 menu_choice_cursor_storage[9];

/* Initializes the object from its child and sets a 90-tick delay and next callback. */
void init_menu_choice_timed(Object *object) {
    s16 adjusted_value;

    adjusted_value = object->child->unk22 - (object->child->unk26 - 1);
    object->unk4d = object->child->unk27;
    init_cursor_color_object(menu_choice_cursor_storage, menu_choice_display_data, object, 1, adjusted_value,
                  object->child->unk80);
    object->unk64 = 0x5a;
    object->unk68 = update_menu_choice_timed;
}
