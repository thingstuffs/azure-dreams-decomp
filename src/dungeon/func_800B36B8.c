#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad0[2];
    s16 field2;
} Object;

typedef struct {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
    u16 field1E;
} Effect;


/* Attenuates an effect and sets object and global flags when its byte level reaches zero. */
void func_800B8E18(Object *object, s32 unused, Effect *effect) {
    u16 magnitude;
    u8 level;
    ObjectFlagBlock *state_flags = &objectFlagBlock;

    magnitude = effect->field1E;
    magnitude = magnitude - ((magnitude * object->field2) / 24);
    effect->field1E = magnitude;
    effect->field1C = magnitude;
    level = effect->fieldE - (object->field2 * 8);
    effect->fieldE = level;
    effect->fieldD = level;
    effect->fieldC = level;
    if (!(level & 0xFF)) {
        *(u16 *)((u8 *)object - 2) = (u16)(*(u16 *)((u8 *)object - 2) | 0x8000);
        state_flags->flags = state_flags->flags | 0x8000;
    }
}
