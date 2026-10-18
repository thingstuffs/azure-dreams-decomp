#include "common.h"

typedef struct {
    char pad[0x16];
    u16 unk16;
} Struct_80819920;

/* Decrease the object's unk16 field by 0x20. */
void rotate_gym_mesh_x(s32 unused_0, s32 unused_1, Struct_80819920 *object) {
    object->unk16 -= 0x20;
}
