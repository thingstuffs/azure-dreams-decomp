#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80088A58[];
s32 func_8003E4FC(); /* extern */
void func_800424E0();          /* extern */
void func_80042560();                      /* extern */
M2C_UNK func_80042640();                  /* extern */
void func_80043914();                      /* extern */
M2C_UNK func_80047FF4();                     /* extern */
s32 func_80048118();                   /* extern */
void func_80048A44(); /* extern */
M2C_UNK func_80093C70();      /* extern */
M2C_UNK func_80093D8C();      /* extern */
M2C_UNK func_80093E74(); /* extern */
s32 func_800990FC();                         /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A028();                      /* extern */
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16); /* extern */
M2C_UNK func_800A152C();                 /* extern */
s32 func_800A1618();                     /* extern */
M2C_UNK func_800A18E8();                 /* extern */
s32 func_800A2BDC();                         /* extern */
M2C_UNK func_800A31D0();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern M2C_UNK D_8008149C;
extern M2C_UNK D_800814A0;
extern void *D_80082EB0[];
extern s16 D_80083228;
extern u16 D_80083460[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DD260;
extern M2C_UNK D_800DD262;
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E06FA;
extern M2C_UNK D_800E0714;
extern s32 D_800E3D74[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

typedef union ScratchS1 {
    s32 value;
    void **base;
} ScratchS1;


typedef struct S_8009345C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8009345C_0;   /* actor in func_8009345C */

typedef struct S_8009345C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009345C_1;   /* entity in func_8009345C */

typedef struct S_8009345C_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8009345C_2;   /* ctx in func_8009345C */

typedef struct S_8009345C_3 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009345C_3;   /* ((temp_idx * 4) + actor) in func_8009345C */

typedef struct S_8009345C_4 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_8009345C_4;   /* &D_800DD262 in func_8009345C */

typedef struct S_8009345C_5_pre {
    u16 unk_00;
} S_8009345C_5_pre;   /* the 0x2 bytes before temp_v1_2 in func_8009345C, addressed as temp_v1_2[-1] */

typedef struct S_8009345C_6 {
    s32 unk_00;
} S_8009345C_6;   /* &D_800814A0 in func_8009345C */

typedef struct S_8009345C_7 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_7;   /* *scratch_s1.base in func_8009345C */

typedef struct S_8009345C_8 {
    u8 unk_00;
} S_8009345C_8;   /* &D_800E3E40 in func_8009345C */

typedef struct S_8009345C_9 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_9;   /* D_80082EB0[0] in func_8009345C */

typedef struct S_8009345C_10_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_8009345C_10_pre;   /* the 0x18 bytes before temp_v0_5 in func_8009345C, addressed as temp_v0_5[-1] */

typedef struct S_8009345C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_10;   /* temp_v0_5 in func_8009345C */

typedef struct S_8009345C_11 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009345C_11;   /* temp_v1_3 in func_8009345C */

typedef struct S_8009345C_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009345C_12;   /* temp_v1_4 in func_8009345C */

typedef struct S_8009345C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009345C_13;   /* map in func_8009345C */

typedef struct S_8009345C_14 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_8009345C_14;   /* ((temp_slot * 4) + actor) in func_8009345C */

typedef struct S_8009345C_15 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_15;   /* ((S_8009345C_2 *)ctx)->unk_60 in func_8009345C */

typedef struct S_8009345C_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8009345C_16;   /* ((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor) in func_8009345C */

/* Advances the object replacement sequence, including animation, messages, and cleanup. */
void func_8009345C(void *actor_arg, void *map_arg, void *entity_arg, void *context_arg) {
    void *actor = actor_arg;
    void *map = map_arg;
    void *entity = entity_arg;
    register void *context ASM_REG("$19") = context_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *remove_text;
    M2C_UNK *create_text;
    s32 remove_message;
    s32 load_id;
    s32 create_id;
    s32 object_flags;
    s32 cleanup_slot;
    s32 create_message;
    u16 start_ticks;
    u16 end_ticks;
    u16 entity_flags;
    u16 slot_bits;
    s16 selected_slot;
    s32 object_slot;
    u8 state;
    register u8 next_state ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    void *new_object;
    void *selected_object;
    void *old_object;
    void *removed_object;
    void *object_scale;
    void *object_position;
    ScratchS1 message_or_list;

    state = ((S_8009345C_0 *)actor)->unk_9B;
    if (state >= 0xAU) {
        goto done;
    }
    (void)state_labels; goto *D_80088A58[(u32)(state)];
jt_c0:
    if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
        goto done;
    }
    (*(void **)((u8 *)entity + (0x2C))) = D_800DD138;
    func_80048A44(entity, D_800DD138[((s32) (D_80083228 + ((S_8009345C_2 *)context)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    func_80093C70(actor, map, entity);
    func_80093D8C(actor, map, entity);
    entity_flags = ((S_8009345C_1 *)entity)->unk_14;
    D_800DD260 = 0;
    ((S_8009345C_1 *)entity)->unk_14 = (u16) (entity_flags | 0x200);
    ((S_8009345C_0 *)actor)->unk_96 = 0x10U;
    selected_slot = ((S_8009345C_2 *)context)->unk_8A.s;
    slot_bits = ((S_8009345C_2 *)context)->unk_8A.u;
    selected_object = (void *) ((S_8009345C_3 *)(((selected_slot * 4) + actor)))->unk_AC;
    ((S_8009345C_4 *)(&D_800DD262))->unk_00.u = slot_bits;
    ((S_8009345C_2 *)context)->unk_60 = selected_object;
    goto advance_state;
jt_c1:
    start_ticks = ((S_8009345C_0 *)actor)->unk_96 - 1;
    ((S_8009345C_0 *)actor)->unk_96 = start_ticks;
    if ((start_ticks << 0x10) > 0) {
        goto done;
    }
    if (((S_8009345C_2 *)context)->unk_60 == NULL) {
        goto skip_removal;
    }
    func_80093E74(actor, map, entity, context);
    goto advance_state;
skip_removal:
    next_state = ((S_8009345C_0 *)actor)->unk_9B + 2;
    goto set_state;
jt_c2:
    if (!(((S_8009345C_15 *)(((S_8009345C_2 *)context)->unk_60))->unk_1C & 0x800000)) {
        goto done;
    }
    message_or_list.value = func_800990FC();
    remove_message = func_8009929C(8, message_or_list.value);
    if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s == 0) {
        goto remove_first_slot;
    }
    remove_text = &D_800E05F0;
    goto show_removal;
remove_first_slot:
    remove_text = &D_800E05E1;
show_removal:
    func_80099290(func_80099194(&D_800E06FA, func_80099734(((S_8009345C_2 *)context)->unk_60, func_80099194(remove_text, remove_message))));
    func_800A5720(message_or_list.value);
    old_object = ((S_8009345C_2 *)context)->unk_60;
    D_800DD260 = 1;
    func_800A31D0(old_object);
    ((S_8009345C_16 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)))->unk_AC = 0;
    func_800A18E8(((S_8009345C_15 *)(((S_8009345C_2 *)context)->unk_60))->unk_13, 3);
    func_8009A028(((S_8009345C_2 *)context)->unk_60);
    removed_object = ((S_8009345C_2 *)context)->unk_60;
    ((S_8009345C_5_pre *)removed_object)[-1].unk_00 = (u16) (((S_8009345C_5_pre *)removed_object)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_8009345C_6 *)(&D_800814A0))->unk_00 | 0x8000);
    if (D_80082EB0[0] != NULL) {
        goto advance_state;
    }
    ((S_8009345C_0 *)actor)->unk_96 = 0U;
    next_state = ((S_8009345C_0 *)actor)->unk_9B + 4;
    goto set_state;
jt_c3:
    message_or_list.base = D_80082EB0;
    if ((func_800A2BDC(0) << 0x10) != 0) {
        goto done;
    }
    load_id = func_800A1618(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
    if (load_id == 0) {
        goto advance_state;
    }
    D_80081488 = func_80048118(((S_8009345C_7 *)(*message_or_list.base))->unk_00, &D_8008149C);
    func_800A0B94(((S_8009345C_7 *)(*message_or_list.base))->unk_00, load_id, 0);
    (*(s8 *)&D_800E3E40) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_800E3E40);
    goto advance_state;
jt_c4:
    if (((S_8009345C_8 *)(&D_800E3E40))->unk_00 == 0) {
        goto done;
    }
    if (D_80081488 == 0) {
        goto advance_state;
    }
    func_80047FF4(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, D_80081488);
    goto advance_state;
jt_c5:
    message_or_list.base = D_80082EB0;
    create_id = func_800A1618(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
    if (create_id == 0) {
        goto start_end_delay;
    }
    func_80043914(*message_or_list.base);
    new_object = func_800A0B94(((S_8009345C_7 *)(*message_or_list.base))->unk_00, create_id, 1)(1, ((S_8009345C_2 *)context)->unk_72, ((S_8009345C_2 *)context)->unk_73, (s16) (((S_8009345C_2 *)context)->unk_88 - 0x20));
    if (new_object == NULL) {
        goto start_end_delay;
    }
    (*(void **)((u8 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)) + (0xAC))) = new_object;
    D_800E3DF0[((S_8009345C_7 *)(*message_or_list.base))->unk_03 & 0x1F] = new_object;
    object_scale = ((S_8009345C_10_pre *)new_object)[-1].unk_04;
    ((S_8009345C_11 *)object_scale)->unk_1E = 0x800;
    ((S_8009345C_11 *)object_scale)->unk_1C = 0x800;
    object_position = ((S_8009345C_10_pre *)new_object)[-1].unk_00;
    ((S_8009345C_12 *)object_position)->unk_02 = (u16) ((S_8009345C_13 *)map)->unk_02;
    ((S_8009345C_12 *)object_position)->unk_06 = (u16) ((S_8009345C_13 *)map)->unk_06;
    ((S_8009345C_12 *)object_position)->unk_0A = (s16) (((S_8009345C_13 *)map)->unk_0A - 0x10);
    func_80042640(new_object, ((S_8009345C_10 *)new_object)->unk_13);
    func_800424E0(new_object, ((S_8009345C_10 *)new_object)->unk_13, *message_or_list.base);
    object_flags = ((S_8009345C_10 *)new_object)->unk_1C;
    object_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
    ((S_8009345C_10 *)new_object)->unk_1C = object_flags | 0x02000000;
    ((S_8009345C_14 *)(((object_slot * 4) + actor)))->unk_D0 = D_80082EB0[0];
    ((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 = (u8) (((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 | 0x20);
    message_or_list.value = func_800990FC(0x02000000);
    create_message = message_or_list.value;
    if (D_800DD260 != 0) {
        goto select_create_text;
    }
    create_message = func_8009929C(8, create_message);
select_create_text:
    if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s == 0) {
        goto create_first_slot;
    }
    create_text = &D_800E05F0;
    goto show_creation;
create_first_slot:
    create_text = &D_800E05E1;
show_creation:
    func_80099290(func_80099194(&D_800E0714, func_80099734(new_object, func_80099194(create_text, create_message))));
    func_800A5720(message_or_list.value);
    cleanup_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
    D_800E3D74[cleanup_slot] = 0;
    func_800A152C(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, 3);
    func_80042560(new_object);
    func_800A56E0(0x704);
start_end_delay:
    next_state = ((S_8009345C_0 *)actor)->unk_9B;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
    ((S_8009345C_0 *)actor)->unk_96 = 0x10U;
    goto increment_state;
jt_c7:
    end_ticks = ((S_8009345C_0 *)actor)->unk_96 - 1;
    ((S_8009345C_0 *)actor)->unk_96 = end_ticks;
    if ((end_ticks << 0x10) > 0) {
        goto done;
    }
    (*(void **)((u8 *)entity + (0x2C))) = D_800DD140;
    func_80048A44(entity, D_800DD140[((s32) (D_80083228 + ((S_8009345C_2 *)context)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    goto advance_state;
jt_c8:
    if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
        goto done;
    }
    ((S_8009345C_0 *)actor)->unk_8C = &D_8008ACDC;
    func_80099F70(((S_8009345C_2 *)context)->unk_5C);
    func_80099F04(((S_8009345C_2 *)context)->unk_5C);
    D_80083460[1] = (u16) (D_80083460[1] | 0x812);
    ((S_8009345C_1 *)entity)->unk_14 = (u16) (((S_8009345C_1 *)entity)->unk_14 & 0xFDFF);
jt_c6:
advance_state:
    next_state = ((S_8009345C_0 *)actor)->unk_9B;
increment_state:
    next_state = next_state + 1;
set_state:
    ((S_8009345C_0 *)actor)->unk_9B = next_state;
done:
    return;
}
