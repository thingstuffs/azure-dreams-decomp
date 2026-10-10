#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct Bank1990800_19915d4_Sprite Bank1990800_19915d4_Sprite;
typedef struct Bank1990800_19915d4_Object Bank1990800_19915d4_Object;

struct Bank1990800_19915d4_Sprite {
    u8 pad0[12];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    u16 flags10;
    s16 angle;
    u16 flags14;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
};

struct Bank1990800_19915d4_Object {
    u8 pad0[8];
    u16 *dst;
    Bank1990800_19915d4_Sprite *sprite;
    u8 *callback;
    u8 pad14[0x44];
    s16 unk58;
    s16 unk5A;
};

M2C_UNK func_8003DB94();
s32 rand();
extern u8 D_800DECF8[];

typedef struct S_819715D4_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
} S_819715D4_0;   /* temp_v1 in func_80024DD4 */

typedef struct S_819715D4_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_819715D4_1;   /* temp_a0 in func_80024DD4 */

typedef struct S_819715D4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819715D4_2;   /* temp_s0 in func_80024DD4 */

/* Creates a sprite object with randomized offsets from the source position. */
void func_80024DD4(u16 *source, s32 unused_1, s32 unused_2, s16 base_x, s16 base_y, s16 base_z) {
    s32 random_value;
    Bank1990800_19915d4_Sprite *sprite;
    Bank1990800_19915d4_Sprite *render_sprite;
    u16 *position;
    Bank1990800_19915d4_Object *object;
    u8 *object_data;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object_data = (u8 *)object + 0x20;
        ((S_819715D4_0 *)object_data)->unk_38 = 0x14;
        ((S_819715D4_0 *)object_data)->unk_3A = 0x14;
        object->callback = (u8 *)func_80024AB4;
        func_8004491C(object, (s32)func_80045340);
        sprite = object->sprite;
        sprite->flags10 = 0x20;
        ((S_819715D4_1 *)sprite)->unk_06 = 0;
        sprite->flags14 |= 0xC;
        position = object->dst;
        position[1] = base_x;
        position[3] = base_y;
        position[5] = base_z;
        position[1] += source[62];
        position[3] += source[63];
        position[5] += source[64];
        random_value = rand(sprite);
        {
            s32 x = position[1];
            x -= 7;
            x += random_value & 0xF;
            position[1] = (u16)x;
        }
        random_value = rand();
        {
            s32 y = position[3];
            y -= 7;
            y += random_value & 0xF;
            position[3] = (u16)y;
        }
        random_value = rand();
        ((S_819715D4_2 *)position)->unk_14 = 0x20000;
        {
            s32 z = position[5];
            z -= 7;
            z += random_value & 0xF;
            position[5] = (u16)z;
        }
        render_sprite = object->sprite;
        render_sprite->scale_y = 0x1000;
        render_sprite->scale_x = 0x1000;
        render_sprite->b = 0x80;
        render_sprite->g = 0x80;
        render_sprite->r = 0x80;
        render_sprite->angle = 0x7DCE;
        render_sprite->flags14 |= 0x100;
        func_8003DB94(render_sprite, D_800DECF8, 0);
    }
}

