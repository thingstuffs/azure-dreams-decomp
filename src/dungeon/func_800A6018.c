#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800AB778_19 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_19;   /* page4 in func_800AB778 */

typedef struct S_800AB778_20 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_20;   /* page16 in func_800AB778 */

typedef struct S_800AB778_21 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x60];
    s32 unk_110;
} S_800AB778_21;   /* ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v in func_800AB778 */

typedef struct S_800AB778_22 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_22;   /* ((S_800AB778_19 *)page4)->unk_3D7C in func_800AB778 */

typedef struct S_800AB778_23 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_23;   /* ((S_800AB778_20 *)page16)->unk_3D7C in func_800AB778 */

typedef struct S_800AB778_24 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_24;   /* ((S_800AB778_22 *)(((S_800AB778_19 *)page4)->unk_3D7C))->unk_110 in func_800AB778 */

typedef struct S_800AB778_25 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_25;   /* ((S_800AB778_23 *)(((S_800AB778_20 *)page16)->unk_3D7C))->unk_110 in func_800AB778 */


typedef struct S_800AB778_0_pre {
    u16 unk_00;
} S_800AB778_0_pre;   /* the 0x2 bytes before arg3 in func_800AB778, addressed as arg3[-1] */


typedef struct S_800AB778_1 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB778_1;   /* arg0 in func_800AB778 */

typedef struct S_800AB778_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_2;   /* state0 in func_800AB778 */

typedef struct S_800AB778_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_800AB778_3;   /* arg2 in func_800AB778 */

typedef struct S_800AB778_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_4;   /* state4_head in func_800AB778 */


typedef struct S_800AB778_6 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_6;   /* temp_v0_7 in func_800AB778 */

typedef struct S_800AB778_7 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_7;   /* *temp_a1_4 in func_800AB778 */

typedef struct S_800AB778_8 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_8;   /* page4 in func_800AB778 */

typedef struct S_800AB778_9 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_9;   /* page_obj4 in func_800AB778 */

typedef struct S_800AB778_10 {
    s32 unk_00;
} S_800AB778_10;   /* &D_800814A0 in func_800AB778 */

typedef struct S_800AB778_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_800AB778_11;   /* state4_tail in func_800AB778 */

typedef struct S_800AB778_12 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_12;   /* temp_v0_2 in func_800AB778 */

typedef struct S_800AB778_13 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_13;   /* *temp_a1 in func_800AB778 */

typedef struct S_800AB778_14 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_14;   /* page16 in func_800AB778 */

typedef struct S_800AB778_15 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_15;   /* page_obj16 in func_800AB778 */

typedef struct S_800AB778_16 {
    s32 unk_00;
} S_800AB778_16;   /* global16 in func_800AB778 */

typedef struct S_800AB778_17 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AB778_17;   /* state16_tail in func_800AB778 */


typedef struct {
    u8 pad00[0x13];
    s8 field13;
    u8 pad14[0x78];
} D_800E3E48_Entry;

M2C_UNK func_800422DC();
s32 func_80042900();
s32 func_800429E4();
M2C_UNK func_80094E34();
M2C_UNK func_80098B38();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_80099844();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
s16 func_800A1BD0();
s32 func_800A2C78();
M2C_UNK func_800A31D0();
M2C_UNK func_800A5720();
M2C_UNK func_800ACB98();
M2C_UNK func_800C542C();
extern u8 D_80010A80[];
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800DCE68;
extern s16 D_800DCED4[];
extern M2C_UNK D_800E0C34;
extern M2C_UNK D_800E0C58;
extern M2C_UNK D_800E0C67;
extern M2C_UNK D_800E3D7C;
extern void *D_800E3DF0[];
extern D_800E3E48_Entry D_800E3E48[];

/* Advance actor removal, updating its visual effects and clearing its references. */
s32 func_800AB778(S_800AB778_1 *state, void *unused_context, S_800AB778_3 *visual, void *actor) {
    M2C_UNK effect_flags;
    s16 actor_slot16;
    s16 fade_ticks;
    s32 actor_slot4;
    s32 object_id16;
    s32 object_id4;
    s32 event_arg;
    s32 actor_flags;
    s32 event_source;
    u16 scale_x;
    u16 scale_y;
    u16 state4_count;
    u16 state16_count;
    s32 actor_type;
    u8 state_or_type;
    u8 effect_x;
    u8 effect_y;
    void **object_slot16;
    void **object_slot4;
    S_800AB778_12 *actor_entry16;
    S_800AB778_6 *actor_entry4;
    register s32 template_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register u32 template_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *event_actor;
    S_800AB778_8 *globals_page4;
    S_800AB778_14 *globals_page16;
    void *event_script;
    S_800AB778_9 *globals4;
    S_800AB778_15 *globals16;
    u8 *state4_tail;
    u8 *state16_tail;
    s32 *update_flags;
    s32 state4_owner;
    s32 effect_actor_flags;
    register void *state4_event ASM_REG("$4"); /* MATCH: form each event address in the shared call argument register. */
    register s32 state4_result;

    actor_flags = ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v;
    if (actor_flags & 0x20000000) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v = actor_flags | 0x400000;
        func_800ACB98();
        return 0;
    }

    state_or_type = state->unk_9B;
    {
        s32 dispatch_state;

        dispatch_state = state_or_type;
        if (dispatch_state == 3) {
            goto state_case3;
        }
        if (dispatch_state < 4) {
            if (dispatch_state == 0) {
                goto state_case0;
            }
            {
                return 0;
            }
        }
        if (dispatch_state == 4) {
            goto state_case4;
        }
        if (dispatch_state == 16) {
            goto state_case16;
        }
        {
            return 0;
        }
    }

state_case0:
    {
        u8 *state0;
        register s32 next_state;

        if (((Rec_D_80082E80 *)actor)->unk_43 != 0xFD) {
            if ((func_800A2C78(actor) << 0x10) != 0) {
                return 0;
            }
            ASM_SCHED_BARRIER(); /* MATCH: preserve the jump into the shared state update. */
        } else {
            ((S_800AB778_21 *)(((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v))->unk_110 = 0;
        }
        state0 = (u8 *)&D_80083460;
        ((S_800AB778_2 *)state0)->unk_0A++;
        next_state = 3;
        state->unk_9B = next_state;
        goto return_zero;
    }

state_case3:
    if (((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v & 0x80000) {
        func_80094E34();
    }
    if (((Rec_D_80082E80 *)actor)->unk_43 < 0x40U) {
        s32 event_index;
        s32 event_mode;
        register void *script_actor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        event_index = func_800429E4(actor);
        script_actor = actor;
        event_mode = 2;
        ASM_KEEP_NV(event_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800C542C(script_actor,
            D_800DCED4[event_index],
            (s32)script_actor == ((S_800AB778_21 *)(((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v))->unk_AC, event_mode);
        state->unk_96.s = 0;
        state->unk_9B = 0x10;
        goto return_zero;
    }
    if (visual->unk_12 == 0) {
        visual->unk_12 = 0xFF80U;
    }
    visual->unk_10 = 0x20;
    visual->unk_14 |= 0xC;
    state->unk_96.s = 0x10;
    ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v |= 0x10000000;
    state->unk_9B++;
    goto return_zero;

state_case4:
    visual->unk_0C -=
        (s32)visual->unk_0C / state->unk_96.s;
    visual->unk_0D -=
        (s32)visual->unk_0D / state->unk_96.s;
    visual->unk_0E -=
        (s32)visual->unk_0E / state->unk_96.s;
    scale_x = visual->unk_1C;
    visual->unk_1C = scale_x +
        ((s32)(0x400 - scale_x) / state->unk_96.s);
    scale_y = visual->unk_1E;
    visual->unk_1E = scale_y +
        ((s32)(0x400 - scale_y) / state->unk_96.s);
    fade_ticks = state->unk_96.u - 1;
    state->unk_96.s = fade_ticks;
    if (((fade_ticks << 0x10) > 0) &&
        !(visual->unk_14 & 0x8000)) {
        return 0;
    }
    event_source = func_800990FC();
    event_arg = func_8009929C(8, event_source);
    state_or_type = ((Rec_D_80082E80 *)actor)->unk_43;
    if (state_or_type == 0xFF) {
        state4_result = func_80099734(actor, event_arg);
        state4_event = &D_800E0C58;
        goto state4_emit;
    }
    if (state_or_type == 0xFE) {
        state4_result = func_80099734(actor, event_arg);
        state4_event = &D_800E0C67;
state4_emit:
        func_80099290(func_80099194(state4_event, state4_result));
        func_800A5720(event_source);
    } else {
        u8 *state4_head;
        u16 *state4_global;

        state4_global = (u16 *)&D_800DCE68;
        state4_head = (u8 *)&D_80083460;
        (*state4_global)--;
        ((S_800AB778_4 *)state4_head)->unk_0A--;
    }
    func_800A31D0(actor);
    actor_slot4 = func_800A1BD0(actor);
    if (actor_slot4 >= 0) {
        void *actor_base4;

        actor_base4 = ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v;
        actor_entry4 = (void *)((actor_slot4 * 4) + (s32)actor_base4);
        actor_entry4->unk_AC = 0;
        actor_entry4->unk_D0 = 0;
    }
    globals_page4 = (void *)0x800E0000;
    if (((S_800AB778_22 *)(((S_800AB778_19 *)globals_page4)->unk_3D7C))->unk_110 != NULL) {
        func_800A18E8(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
        object_id4 = ((S_800AB778_24 *)(((S_800AB778_22 *)(((S_800AB778_19 *)globals_page4)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
        object_slot4 = &D_800E3DF0[object_id4];
        ((S_800AB778_7 *)(*object_slot4))->unk_13 = 0;
        D_800E3E48[object_id4].field13 = 0;
        globals4 = globals_page4->unk_3D7C;
        *object_slot4 = NULL;
        func_80098B38(globals4->unk_110);
    } else {
        func_800A18E8(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 2);
    }
    if ((func_80042900(actor, 0x1B) << 0x10) == 0) {
        effect_actor_flags = ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v;
        effect_x = visual->unk_24;
        effect_y = visual->unk_25;
        effect_flags = 0x3000;
        if (effect_actor_flags & 0x2000) {
            effect_flags = 0x300;
        }
        func_8009A3D0(effect_x, effect_y, effect_flags);
    }
    func_8009A028(actor);
    ((S_800AB778_0_pre *)actor)[-1].unk_00 |= 0x8000;
    ((S_800AB778_10 *)(&D_800814A0))->unk_00 |= 0x8000;
    state4_tail = (u8 *)&D_80083460;
    state4_count = ((S_800AB778_11 *)state4_tail)->unk_0A;
    state4_owner = ((S_800AB778_11 *)state4_tail)->unk_0C;
    state4_count--;
    ((S_800AB778_11 *)state4_tail)->unk_0A = state4_count;
    if (state4_owner == (s32)actor) {
        ((S_800AB778_11 *)state4_tail)->unk_0C = 0;
        goto return_zero;
    }
    goto return_zero;

state_case16:
    ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v = actor_flags | 0x4000;
    event_actor = actor;
    ASM_KEEP(event_actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    event_script = &D_800E0C34;
    ASM_KEEP(event_script);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    actor_flags &= 0x4000;
    func_80099844(event_actor, event_script);
    if (actor_flags == 0) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v &= ~0x4000;
    }
    func_800A31D0(actor);
    actor_type = ((Rec_D_80082E80 *)actor)->unk_43;
    ((Rec_D_80082E80 *)actor)->unk_44 = 0;
    if ((func_80042900(actor, 0xA) << 0x10) != 0) {
        ((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v = ((Rec_D_80082E80 *)actor)->unk_A8;
    }
    template_base = 0x80010A80;
    template_index = actor_type;
    func_800422DC(&((u8 *)template_base)[template_index * 0x54], actor);
    func_800A18E8(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
    actor_slot16 = func_800A1BD0(actor);
    if (actor_slot16 >= 0) {
        void *actor_base16;

        actor_base16 = ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v;
        actor_entry16 = (void *)((actor_slot16 * 4) + (s32)actor_base16);
        actor_entry16->unk_AC = 0;
        actor_entry16->unk_D0 = 0;
    }
    globals_page16 = (void *)0x800E0000;
    object_id16 = ((S_800AB778_25 *)(((S_800AB778_23 *)(((S_800AB778_20 *)globals_page16)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
    object_slot16 = &D_800E3DF0[object_id16];
    ((S_800AB778_13 *)(*object_slot16))->unk_13 = 0;
    D_800E3E48[object_id16].field13 = 0;
    globals16 = globals_page16->unk_3D7C;
    *object_slot16 = NULL;
    func_80098B38(globals16->unk_110);
    if ((func_80042900(actor, 0x1B) << 0x10) == 0) {
        effect_actor_flags = ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v;
        effect_x = visual->unk_24;
        effect_y = visual->unk_25;
        effect_flags = 0x3000;
        if (effect_actor_flags & 0x2000) {
            effect_flags = 0x300;
        }
        func_8009A3D0(effect_x, effect_y, effect_flags);
    }
    func_8009A028(actor);
    update_flags = (s32 *)&D_800814A0;
    state16_tail = (u8 *)&D_80083460;
    ((S_800AB778_0_pre *)actor)[-1].unk_00 |= 0x8000;
    ((S_800AB778_16 *)update_flags)->unk_00 |= 0x8000;
    state16_count = ((S_800AB778_17 *)state16_tail)->unk_0A;
    state16_count--;
    ((S_800AB778_17 *)state16_tail)->unk_0A = state16_count;
return_zero:
    return 0;
}
