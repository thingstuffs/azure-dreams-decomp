#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"

void register_node(void *, void *);                /* extern */
s32 rsin(s32);                           /* extern */
s32 rcos(s32);                           /* extern */
extern M2C_UNK D_80025528;
extern u8 D_800C95C0[12];

typedef struct S_81959E04_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 unk_30;
} S_81959E04_2;   /* info in spawn_ring_sparks */

/* Spawn a ring of 32 spark objects around (x, y, z), each with the velocity of its angle step. */
void *spawn_ring_sparks(s16 x, s16 y, s16 z) {
    ObjectPosition *part;
    ObjectNodeHeader *obj;
    s32 i;
    s32 scale;
    s32 sign_bits;
    S_81959E04_2 *info;

    i = 0;
    sign_bits = -0x800;
    scale = 0x20;
    do {
        obj = allocate_flagged_object_node(0x212);
        if (obj != NULL) {
            obj->unk_10 = &D_80025528;
            register_node(obj, D_800C95C0);
            part = obj->position;
            part->x.w.i = x;
            part->y.w.i = y;
            part->z.w.i = z;
            part->velocity_x = ((rcos(i * 0x80) & 0x800) ? (rcos(i * 0x80)
                | sign_bits) : (rcos(i * 0x80) & 0x7FF)) << 0xB;
            part->velocity_y = ((rsin(i * 0x80) & 0x800) ? (rsin(i * 0x80)
                | sign_bits) : (rsin(i * 0x80) & 0x7FF)) << 0xB;
            part->velocity_z = 0xFFFE0000;
            info = ((void *)obj) + 0x20;
            (*(s16 *)((u8 *)obj + 0x20)) = scale;
            info->unk_02 = scale;
            info->unk_04 = 1;
            info->unk_06 = 0;
            info->unk_30 = scale;
        }
        i += 1;
    } while (i < 0x20);
    return obj;
}
