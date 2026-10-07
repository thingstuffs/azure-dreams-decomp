#include "common.h"
#include "shared/dungeon_floor.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Obj12 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void *unk_10;
} Obj12;

typedef struct Obj12Child {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Obj12Child;

typedef struct Obj12Render {
    u8 pad_00[0x8];
    void *unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} Obj12Render;

typedef struct Obj12ConfigPage {
    u8 pad_00[0x3638];
    u16 unk_3638;
    u16 unk_363A;
    u16 unk_363C;
} Obj12ConfigPage;

typedef struct Obj12State {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
} Obj12State;


void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
struct ConfigWord { s32 value; };
extern u8 D_8009E038[];
extern u8 D_8009E798[];
extern u8 D_800DD7E0[];

/* Create and initialize the type 0x12 object if it is not already active. */
void func_8009ED30(void) {
    Obj12 *object;

    if (!(D_800E296C & 0x80)) {
        object = func_8003FC64(0x12);
        if (object != NULL) {
            object->unk_10 = D_8009E038;
            func_8004491C(object, D_8009E798);
            {
                u16 field_value;
                u16 field_value_2;
                u16 field_z;
                Obj12State *object_state;
                Obj12Child *child;
                s32 color;
                void *config_value;
                s32 config_word;
                s32 config_word2;
                s32 flags;
                void *render_data;

                child = object->unk_08;
                child->unk_0A = -1;
                render_data = object->unk_0C;
                ((Obj12Render *)render_data)->unk_14 = 0xC;
                ((Obj12Render *)render_data)->unk_08 = D_800DD7E0;
                config_value = (void *) 0x80010000;
                ((Obj12Render *)render_data)->unk_1E = 0;
                ((Obj12Render *)render_data)->unk_1C = 0;
                field_value_2 = ((Obj12ConfigPage *)config_value)->unk_363C;
                object_state = (Obj12State *)((u8 *)object + 0x20);
                object_state->unk_1E = field_value_2;
                field_value = ((Obj12ConfigPage *)config_value)->unk_3638;
                child->unk_02 = field_value;
                object_state->unk_14 = field_value;
                field_z = ((Obj12ConfigPage *)config_value)->unk_363A;
                child->unk_06 = field_z;
                object_state->unk_16 = field_z;
                object_state->unk_1A = 0x10;
                object_state->unk_1C = 8;
                color = 0x808080;
                ((Obj12Render *)render_data)->unk_0C = color;
                config_word = ((struct ConfigWord *)0x80013630)->value;
                ((Obj12Render *)render_data)->unk_18 = 0;
                ((Obj12Render *)render_data)->unk_16 = 0;
                ((Obj12Render *)render_data)->unk_18 = 0;
                ((Obj12Render *)render_data)->unk_16 = 0;
                object_state->unk_04 = (s32) config_word;
                object_state->unk_0C = (s32) config_word;
                config_word2 = ((struct ConfigWord *)0x80013634)->value;
                (*(s32 *)((u8 *)object_state + 8)) = (s32) config_word2;
                (*(s32 *)((u8 *)object_state + 0x10)) = (s32) config_word2;
                flags = D_800E296C;
                object_state->unk_1C = 4;
                object_state->unk_18 = 0;
                D_800E296C = flags | 0x80;
            }
        }
    }
}

/* MECHANISM: Direct D_800E296C RMW holds its page in s1, producing the 0x20 frame and retail save order.
   Post-call caller-register roles hold the 0x8001 page in v0, child/secondary/subobject in a2/v1/a0,
   and color in a3; reusing dead v0/v1 for the two globals, literal 4, and flag reload removes the tail nop. */
