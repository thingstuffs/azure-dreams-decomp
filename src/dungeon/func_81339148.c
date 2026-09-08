#include "common.h"

extern void func_8009A3D0(u8, u8, s32);
extern void func_800A9A0C(void *);
extern void func_8009A028(void *);

typedef struct Entity {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0x76];
    s16 field_96;
    u8 pad_98[2];
    u8 field_9A;
} Entity;

typedef struct Root {
    u8 pad_00[0xC];
    u8 *position;
    u8 *field_10;
    u8 pad_14[0xC];
    Entity entity;
} Root;

extern Root *D_80175D50;
extern u8 D_8016FC4C[];

/* Update the entity at its position and reset its state fields. */
void func_80170148(void)
{
    Root *root = D_80175D50;
    Entity *entity;
    u8 *position;

    entity = &root->entity;

    position = root->position;

    func_8009A3D0(position[0x24], position[0x25],
                  (entity->flags & 0x2000) ? 0x300 : 0x3000);
    func_800A9A0C(entity);
    func_8009A028(entity);
    D_80175D50->field_10 = D_8016FC4C;
    entity->field_9A = 0;
    entity->field_96 = 0;
}
