#include "common.h"

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 x;
    UnalignedS32 y;
    UnalignedS32 z;
} PackedVec;

typedef struct {
    u8 pad0[8];
    s32 *position;
    u8 *sprite;
    void *callback;
    u8 pad14[0x38];
    PackedVec data;
} Object;

extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern u8 D_80045340[];
extern PackedVec D_80077818[];
extern s32 *D_80174704[3];
extern Object *D_80174CC8[3];
extern u8 D_8016E300[];

/* Creates and initializes a sprite object offset from the first source position. */
void func_8016E434(void) {
    s32 *source_pos;
    Object *obj;
    s32 *position;
    u8 *sprite;

    source_pos = (s32 *)D_80174704[0][2];
    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_8016E300;
        func_8004491C(obj, D_80045340);
        position = obj->position;
        position[0] = source_pos[0] + (s32)0xFFC00000;
        position[1] = source_pos[1];
        position[2] = source_pos[2];
        sprite = obj->sprite;
        *(s16 *)(sprite + 0x1E) = 0x1000;
        *(s16 *)(sprite + 0x1C) = 0x1000;
        sprite[0xE] = 0x80;
        sprite[0xD] = 0x80;
        sprite[0xC] = 0x80;
        obj->data = D_80077818[0];
        *(PackedVec **)(sprite + 8) = &obj->data;
        D_80174CC8[0] = obj;
    }
}
