#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
typedef struct S_801745F0_0 S_801745F0_0;

typedef struct S_80047784 S_80047784;

typedef struct S_80174690_4 {
    u8 pad_00[0x18];
    void * unk_18;
} S_80174690_4;

typedef struct S_80174690_5 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80174690_5;


void *func_8003FD64();               /* extern */
s32 func_8004491C();           /* extern */
void func_80047784(S_80047784 *object, s16 table_index, s16 entry_index);    /* extern */
void copy_linked_position_and_check_status(void *object, S_801745F0_0 *dest, Rec_D_80082E80 *status);

typedef struct S_80174690_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
} S_80174690_0;

typedef struct S_80174690_1 {
    u8 pad_00[0x18];
    void * unk_18;
    s32 unk_1C;
} S_80174690_1;

typedef struct S_80174690_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_80174690_2;   /* arg0 in create_action_sprite_effect */

typedef struct S_80174690_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174690_3;

/* Creates an effect from the source and initializes its sprite and callbacks. */
void create_action_sprite_effect(S_80174690_2 *source) {
    S_80174690_3 *sprite;
    S_80174690_1 *effect_data;
    void *effect;

    effect = func_8003FD64(0x112, source);
    if (effect != 0) {
        sprite = ((S_80174690_0 *)effect)->unk_0C;
        ((S_80174690_0 *)effect)->unk_10 = &copy_linked_position_and_check_status;
        effect_data = effect + 0x20;
        effect_data->unk_18 = (void *) source->unk_0C;
        effect_data->unk_1C = (s32) source->unk_08;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C = 0x808080;
        sprite->unk_12 = (u16) (sprite->unk_12 - 0x80);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        sprite->unk_28 = (s32) ((S_80174690_5 *)(((S_80174690_4 *)effect_data)->unk_18))->unk_28;
        func_80047784(sprite, 0x44, 0);
        func_8004491C(effect, func_80045340);
    }
}
