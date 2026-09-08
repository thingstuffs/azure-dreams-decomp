#include "common.h"
#include "m2c_compat.h"

typedef struct Sprite Sprite;
typedef struct Object Object;

struct Sprite {
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

struct Object {
    u8 pad0[8];
    u16 *dst;
    Sprite *sprite;
    u8 *callback;
    u8 pad14[0x44];
    s16 unk58;
    s16 unk5A;
};

M2C_UNK func_8003DB94();
Object *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_80024AB4[];
extern u8 D_80045340[];
extern u8 D_800DECF8[];

typedef struct S_819715D4_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
} S_819715D4_0;   /* temp_v1 in func_819715D4 */

typedef struct S_819715D4_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_819715D4_1;   /* temp_a0 in func_819715D4 */

typedef struct S_819715D4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819715D4_2;   /* temp_s0 in func_819715D4 */

/* Creates a sprite object with randomized offsets from the source position. */
void func_819715D4(u16 *source, s32 unused_1, s32 unused_2, s32 base_x, s32 base_y, s32 base_z) {
    s32 random_value;
    Sprite *sprite;
    Sprite *render_sprite;
    u16 *position;
    Object *object;
    u8 *object_data;

    object = func_8003FC64(0x212);
#ifdef NON_MATCHING
#endif
    if (object != NULL) {
        object_data = (u8 *)object + 0x20;
        ((S_819715D4_0 *)object_data)->unk_38 = 0x14;
        ((S_819715D4_0 *)object_data)->unk_3A = 0x14;
        object->callback = D_80024AB4;
        func_8004491C(object, D_80045340);
        sprite = object->sprite;
        sprite->flags10 = 0x20;
        ((S_819715D4_1 *)sprite)->unk_06 = 0;
        sprite->flags14 |= 0xC;
        position = object->dst;
        position[1] = base_x;
        position[3] = (u16)base_y;
        position[5] = (u16)base_z;
        {
            s32 x;
            s32 offset = source[62];
            ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            x = base_x;
            ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            x += offset;
            position[1] = (u16)x;
        }
        {
            s32 y;
            s32 offset = source[63];
            ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            y = base_y;
            ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            y += offset;
            position[3] = (u16)y;
        }
        {
            s32 z;
            register s32 offset ASM_REG("$3") = source[64];   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            z = base_z;
            ASM_KEEP(z);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            z += offset;
            position[5] = (u16)z;
        }
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

/* MECHANISM: A guarded s1 object-result pin makes arg0 fall naturally into s2,
   closing the 0x30 frame/save contract; byte-scaled +0x20 and scoped v0/v1 accumulators fill load delays.
   Split random-result accumulations keep each -7 as addiu, removing the shared-register +1-word drift. */
