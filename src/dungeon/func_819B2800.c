#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
extern u8 D_80083498[];
extern u8 D_80082E80[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_80082E94;
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
s32 func_8003DE58();     /* extern */
u8 *func_8003FD64();                   /* extern */
M2C_UNK func_8004491C();             /* extern */
M2C_UNK func_8009CE1C(); /* extern */
void *func_800A3F28();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80024440;
extern M2C_UNK D_8002466C;
extern M2C_UNK D_80024B48;
extern M2C_UNK D_80024C14;

typedef struct S_func_819B2800_0 {
    void *unk_00;
    u16 *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 unk_0A; u16 unk_A; } unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    union { s16 unk_052; u16 unk_52; } unk_52;
} S_func_819B2800_0;

typedef struct S_func_819B2800_1 {
    s32 unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        struct { u8 pad_08[2]; u16 unk_0A; } unk_0A;
    } unk_08;
} S_func_819B2800_1;

typedef struct S_func_819B2800_2 {
    u8 pad_00[0x10];
    M2C_UNK *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
    u8 pad_24[6];
    s16 unk_2A;
} S_func_819B2800_2;

typedef struct S_func_819B2800_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
} S_func_819B2800_3;

typedef struct S_func_819B2800_4 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
} S_func_819B2800_4;

typedef struct S_func_819B2800_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0xA];
    s8 unk_102;
} S_func_819B2800_5;

typedef struct S_func_819B2800_6 {
    u8 pad_00[8];
    s32 unk_08;
} S_func_819B2800_6;

typedef struct S_func_819B2800_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_func_819B2800_7;

typedef struct S_func_819B2800_8 {
    u16 unk_00;
} S_func_819B2800_8;

#ifdef __mips__
/* Existing-identity DATA-BANK composite: the row owns these seven retail words;
 * the C body begins at the true interior entry 0x819B281C. */
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C, 0x00000000, 0x80024080, 0x800240E8,
    0x800241E8, 0x80024224, 0x80024310
};
__asm__(".globl func_80024000\n.type func_80024000,@function\n.size func_80024000,1088\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(S_func_819B2800_0 *effect, S_func_819B2800_1 *position) BODY_ATTR;
/* Advances a timed effect, spawns its visuals, and applies it to nearby targets. */
BODY_STORAGE void BODY_NAME(S_func_819B2800_0 *effect, S_func_819B2800_1 *position) {
    static void *const phase_labels[] = { &&init_effect, &&wait_trigger, &&start_effect, &&spawn_visual, &&apply_effect };
    s16 offset[3];
    u16 next_phase;
    u16 timer;
    M2C_UNK effect_code;
    s16 direction;
    s32 phase_or_delay;
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    s32 target;
    S_func_819B2800_4 *visual;
    u8 *data_bytes;
    S_func_819B2800_6 *model;
    S_func_819B2800_5 *actor;
    S_func_819B2800_7 *effect_state;
    S_func_819B2800_2 *object_data;
    S_func_819B2800_3 *location;

    timer = ((volatile S_func_819B2800_0 *) effect)->unk_50;
    object_data = ((volatile S_func_819B2800_0 *) effect)->unk_00;
    phase_or_delay = effect->unk_0A.unk_0A;
    effect->unk_50 = (u16) (timer - 1);
    location = (S_func_819B2800_3 *) ((u8 *) object_data - 0x20);
    if ((u32) phase_or_delay >= 5U) {
        goto done;
    }
    (void)phase_labels;
    goto *D_80024008[(u32)(phase_or_delay)];
init_effect:
    ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_102 = 1;
    ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_F4 = 0;
    position->unk_00 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_00;
    position->unk_04 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_04;
    position->unk_08.unk_08 = (s32) ((S_func_819B2800_1 *) location->unk_08)->unk_08.unk_08;
    effect->unk_0A.unk_0A = (s16) ((u16) effect->unk_0A.unk_0A + 1);
wait_trigger:
    if (!(*effect->unk_04 & 0x80)) {
        goto done;
    }
    actor = (void *) ((s32*)&D_800814A8)[0];
    effect->unk_50 = 0xAU;
    actor->unk_A6 = (u16) (actor->unk_A6 - 1);
    actor->unk_A8 = (u8) effect->unk_08;
    object_data = (S_func_819B2800_2 *) func_8003FD64(0x302, D_80083498);
    if (object_data == NULL) {
        goto advance_phase;
    }
    model = location->unk_0C;
    if (func_8003DE58(model->unk_08, model, offset, 0) != 0) {
        goto place_visual;
    }
    offset[2] = 0;
    offset[1] = 0;
    offset[0] = 0;
place_visual:
    visual = (S_func_819B2800_4 *) ((u8 *) object_data + 0x20);
    object_data->unk_10 = &D_8002466C;
    func_8004491C(object_data, &D_80024440);
    pos_x = ((S_func_819B2800_1 *) location->unk_08)->unk_00 + (offset[0] << 0x10);
    position->unk_00 = pos_x;
    visual->unk_1C = pos_x;
    pos_y = ((S_func_819B2800_1 *) location->unk_08)->unk_04 + (offset[1] << 0x10);
    position->unk_04 = pos_y;
    visual->unk_20 = pos_y;
    pos_z = ((S_func_819B2800_1 *) location->unk_08)->unk_08.unk_08 + (offset[2] << 0x10);
    position->unk_08.unk_08 = pos_z;
    visual->unk_24 = pos_z;
    object_data->unk_20 = effect;
advance_phase:
    next_phase = effect->unk_0A.unk_A;
    next_phase++;
    goto store_phase;
start_effect:
    if ((s16) effect->unk_50 > 0) {
        goto done;
    }
    if (func_80053EF0(4) != 2) {
        effect_code = 0x300;
    } else {
        effect_code = 0x4300;
    }
    func_800A56E0(effect_code);
    next_phase = effect->unk_0A.unk_A;
    phase_or_delay = 0xD;
    goto set_timer;
spawn_visual:
    if ((s16) effect->unk_50 != 2) {
        goto wait_visual;
    }
    func_800419EC(0x18, 0x10);
wait_visual:
    if ((s16) effect->unk_50 > 0) {
        goto done;
    }
    object_data = (S_func_819B2800_2 *) func_8003FD64(0x302, D_80083498);
    data_bytes = (u8 *) object_data;
    if (object_data == NULL) {
        goto set_apply_delay;
    }
    visual = (S_func_819B2800_4 *) ((u8 *) object_data + 0x20);
    object_data->unk_10 = &D_80024B48;
    func_8004491C(data_bytes, &D_80024C14);
    data_bytes = D_80082E80;
    direction = ((u16) ((S_func_819B2800_5 *) ((s32*)&D_800814A8)[0])->unk_2A >> 9) & 7;
    offset[0] = direction;
    visual->unk_0C = (s16) (((S_func_819B2800_3 *) D_80082E80)->unk_24 + D_8006CCD8[direction]);
    visual->unk_0E = (s16) (((S_func_819B2800_3 *) D_80082E80)->unk_25 + D_8006CCE8[offset[0]]);
    visual->unk_10 = (u16) position->unk_08.unk_0A.unk_0A;
    object_data->unk_20 = effect;
set_apply_delay:
    next_phase = effect->unk_0A.unk_A;
    phase_or_delay = 0x10;
set_timer:
    effect->unk_50 = phase_or_delay;
    next_phase++;
store_phase:
    effect->unk_0A.unk_A = next_phase;
    goto done;
apply_effect:
    if ((s16) effect->unk_50 != 8) {
        goto check_completion;
    }
    target = ((s32*)&D_800814A8)[0];
    position = (void *) target;
    if (target == 0) {
        goto check_completion;
    }
    location = (S_func_819B2800_3 *) D_80082E80;
next_target:
    target = func_800A3F28(location->unk_24, location->unk_25, position, (void *) target);
    if (target == 0) {
        goto check_completion;
    }
    if (((S_func_819B2800_5 *) target)->unk_1C & 0x2000) {
        goto next_target;
    }
    func_8009CE1C((void *) target, 0x10, effect->unk_09, 0xC, (s32) object_data->unk_2A, object_data, 2);
    goto next_target;
check_completion:
    if (D_80082E94 & 0x8000) {
        goto check_hold;
    }
    if ((s16) effect->unk_50 >= 0) {
        goto done;
    }
check_hold:
    if (!(effect->unk_52.unk_052 & 0x8000)) {
        goto finish_effect;
    }
    effect->unk_52.unk_52 = (u16) (effect->unk_52.unk_52 & 0x7FFF);
    goto done;
finish_effect:
    effect_state = (S_func_819B2800_7 *) D_80083460;
    effect_state->unk_0C = 0;
    effect_state->unk_0A = (u16) (effect_state->unk_0A - 1);
    ((S_func_819B2800_8 *) ((u8 *) effect - 2))->unk_00 = (u16) (((S_func_819B2800_8 *) ((u8 *) effect - 2))->unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
done:
    return;
}
