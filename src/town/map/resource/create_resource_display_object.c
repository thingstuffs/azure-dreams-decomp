#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_effect_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A47A8_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800A47A8_4;


s32 register_node();
extern s32 D_800A3918[];
extern s32 D_800A3B1C[];
extern s32 D_800D0C40[];
typedef struct {
    s16 value;
    u8 pad[10];
} LargeS16;
extern LargeS16 D_80100D88;
extern LargeS16 D_80100D8A;

typedef struct S_800A47A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A47A8_0;

typedef struct S_800A47A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A47A8_1;

typedef struct S_800A47A8_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A47A8_2;

typedef struct S_800A47A8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x8];
    s16 unk_0C;
    u8 pad_0E[0x4];
    s16 unk_12;
    s16 unk_14;
} S_800A47A8_3;

/* Creates an object with the selected resource and initializes its display and state. */
void create_resource_display_object(s16 resource_index) {
    void *object;
    S_800A47A8_3 *object_state;
    S_800A47A8_1 *component;
    S_800A47A8_2 *scale;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        ((S_800A47A8_0 *)object)->unk_10 = D_800A3918;
        register_node(object, D_800A3B1C);
        ((EffectPrimitiveValueView *)(((S_800A47A8_4 *)object)->unk_0C))->unk_08 = D_800D0C40[resource_index];
        component = ((S_800A47A8_0 *)object)->unk_0C;
        component->unk_0E = 0xE0;
        component->unk_0D = 0xE0;
        component->unk_0C = 0xE0;
        scale = ((S_800A47A8_0 *)object)->unk_0C;
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        component = ((S_800A47A8_0 *)object)->unk_08;
        D_80100D88.value = 0;
        component->unk_02 = 0;
        component = ((S_800A47A8_0 *)object)->unk_08;
        D_80100D8A.value = 0;
        component->unk_06 = 0;
        component = ((S_800A47A8_0 *)object)->unk_08;
        component->unk_0A = 0x4000;
        object_state = object + 0x20;
        object_state->unk_0C = resource_index;
        object_state->unk_02 = 0;
        object_state->unk_12 = 0;
        object_state->unk_14 = 0x80;
    }
}
