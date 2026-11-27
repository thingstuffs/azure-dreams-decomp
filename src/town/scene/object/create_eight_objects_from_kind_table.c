#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/scene/score_sprite_data.h"
#include "town/devkit/old_minigame_imports.h"

typedef struct Object Object;

typedef struct Owner {
    u8 pad_00[8];
    Object *objects[8];
    u8 pad_28[0xC];
    s16 kind;
} Owner;

typedef struct ObjectData {
    u8 pad_00[2];
    u16 x;
    u8 pad_04[2];
    u16 y;
} ObjectData;

typedef struct Primitive {
    u8 pad_00[0xC];
    s32 color;
    u16 tpage_abr;
    u8 pad_12[2];
    u16 flags;
    u8 pad_16[6];
    u16 scale_x;
    u16 scale_y;
} Primitive;

struct Object {
    u8 pad_00[8];
    ObjectData *data;
    Primitive *primitive;
    void *update_callback;
    u8 pad_14[0xC];
    Owner *owner;
};

typedef struct TableEntry {
    u16 x;
    u16 y;
} TableEntry;

extern u8 D_80528B94[];
extern TableEntry D_8052FF9C[][8];
extern u8 D_80288EE0[];


/* Create and initialize the owner's eight objects using its kind-specific table. */
void create_eight_objects_from_kind_table(void *owner_data)
{
    Owner *owner = owner_data;
    s32 slot;

    for (slot = 7; slot >= 0; slot--) {
        Object *object = func_800374FC(0x136, &scene_object_factory_data);
        owner->objects[slot] = object;
        if (object != 0) {
            ObjectData *data;
            Primitive *primitive;

            object->update_callback = D_80528B94;
            func_8003BC18(object, score_sprite_draw_callback_address);
            object->owner = owner;
            data = object->data;
            primitive = object->primitive;
            data->x = D_8052FF9C[owner->kind][slot].x;
            data->y = D_8052FF9C[owner->kind][slot].y;
            primitive->tpage_abr = 0x60;
            primitive->color = 0;
            primitive->scale_y = 0x1000;
            primitive->scale_x = 0x1000;
            primitive->flags |= 0xC;
            func_80034A1C(primitive, D_80288EE0, 0);
        }
    }
}
