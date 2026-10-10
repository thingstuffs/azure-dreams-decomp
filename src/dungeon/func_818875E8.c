#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

ObjectNodeHeader *func_8003FC64(s32 flags);
extern void func_80024D70();
extern M2C_UNK D_800CEEFC;

/* One 4-byte slot of the fade record: only the second halfword is used. */
typedef struct FadeChannel {
    u16 unused;
    u16 value;
} FadeChannel;

typedef struct FadeDelta {
    u16 unused;
    s16 value;
} FadeDelta;

/* The fade's working record (the object header's unk_08 payload). */
typedef struct FadeTransition {
    FadeChannel start[3];
    FadeDelta delta[3];     /* start - end per channel */
} FadeTransition;

/* Start values followed by end values, one FadeChannel each. */
typedef struct FadeEndpoints {
    FadeChannel start[3];
    FadeChannel end[3];
} FadeEndpoints;

/* Settings block: copied field by field into the object's own settings record (the header's unk_0C payload). */
typedef struct FadeSettings {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} FadeSettings;

/* Retail 818875E8 (func_80024DE8): creates a fade object (updated each frame by func_80024D70) with its start
 * values, per-channel start - end differences and a copy of the settings. */
ObjectNodeHeader *func_80024DE8(FadeEndpoints *endpoints, FadeSettings *settings) {
    FadeTransition *transition;
    ObjectNodeHeader *object;
    FadeSettings *object_settings;

    object = func_8003FC64(0x202);
    if (object != NULL) {
        object->unk_10 = (void *)func_80024D70;
        func_8004491C(object, (s32)&D_800CEEFC);
        transition = object->unk_08;
        transition->start[0].value = endpoints->start[0].value;
        transition->start[1].value = endpoints->start[1].value;
        transition->start[2].value = endpoints->start[2].value;
        transition->delta[0].value = endpoints->start[0].value - endpoints->end[0].value;
        transition->delta[1].value = endpoints->start[1].value - endpoints->end[1].value;
        transition->delta[2].value = endpoints->start[2].value - endpoints->end[2].value;
        object_settings = object->unk_0C;
        object_settings->unk_1C = settings->unk_1C;
        object_settings->unk_1E = settings->unk_1E;
        object_settings->unk_0C = settings->unk_0C;
        object_settings->unk_08 = settings->unk_08;
        object_settings->unk_14 = settings->unk_14;
    }
    return object;
}
