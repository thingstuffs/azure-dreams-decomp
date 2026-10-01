#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C4AFC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x18];
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    s32 unk_28;
} S_800C4AFC_0;   /* state in func_800C4AFC */

typedef struct S_800C4AFC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800C4AFC_1;   /* object in func_800C4AFC */

typedef struct S_800C4AFC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4AFC_2;   /* arg0 in func_800C4AFC */

typedef struct S_800C4AFC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4AFC_3;   /* (void *)temp in func_800C4AFC */


extern void *func_8003FD64(s32, void *);
extern void func_800B835C(void *, s32 *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800C4944(void);

extern u8 D_800DCF78[12];

/* Create an effect object, copy its source components, and initialize its state. */
void func_800C4AFC(S_800C4AFC_2 *source, s32 effect_param, s32 state_param)
{
    s32 effect_init[2];
    void *object;
    s32 init_value;
    S_800C4AFC_3 *components;
    S_800C4AFC_3 *status;
    u8 *state;
    u8 *effect;
    u16 component_x;
    u16 component_y;
    u16 component_z;

    object = func_8003FD64(0x202, ((u8 *)(&D_80083498)));
    if (object == NULL) {
        return;
    }

    *(s32 *)D_800DCF78 = effect_param;
    effect_init[0] = 0x01000340;
    init_value = 0x00200020;
    effect_init[1] = init_value;
    effect = D_800DCF78;
    effect -= 0x10;
    func_800B835C(effect, effect_init, 1, 0);

    state = (u8 *)object + 0x20;
    ((S_800C4AFC_0 *)state)->unk_02 = 0x40;
    ((S_800C4AFC_1 *)object)->unk_10 = (void *)func_800C4944;
    components = ((S_800C4AFC_1 *)object)->unk_08;
    component_x = source->unk_02;
    components->unk_02 = component_x;
    ((S_800C4AFC_0 *)state)->unk_20 = component_x;
    component_y = source->unk_06;
    components->unk_06 = component_y;
    ((S_800C4AFC_0 *)state)->unk_22 = component_y;
    component_z = source->unk_0A;
    components->unk_0A = component_z;
    ((S_800C4AFC_0 *)state)->unk_24 = component_z;
    ((S_800C4AFC_0 *)state)->unk_1C = source;
    ((S_800C4AFC_0 *)state)->unk_28 = state_param;
    func_800A56E0(0x702);
    status = (S_800C4AFC_3 *)&dungeonStatus;
    status->unk_0A++;
}

/* MECHANISM: The 0x30 frame, s1/s2/s3 argument holds, two-word init record, and callee ABIs
   reproduce the retail structure. Moving init[1]'s store immediately before func_800B835C
   schedules move a3,zero at word 25 and the stack store into the jal delay slot at word 28. */
