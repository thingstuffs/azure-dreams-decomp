#include "common.h"
#include "records/Rec_D_80082E80.h"


extern s32 func_8003DE58();
extern void func_80048A44();
extern void func_80091934();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern s32 func_8009965C();
extern s32 func_80099734();
extern void func_80099F04();
extern void func_80099F70();
extern void func_800A5720();
extern void *func_800A8608(void *, void *, s32, s32, s32);

extern s16 D_80083228[12];
extern u8 D_80083460[12];
extern u8 D_8008ACDC[12];
extern u8 D_8008D470[12];
extern u8 D_800DD0B8[8];
extern u8 D_800E06EE[9];
extern u8 D_800E06F7[9];


typedef struct S_800927E4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x74];
    void * unk_110;
} S_800927E4_0;   /* arg0 in func_800927E4 */

typedef struct S_800927E4_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_1;   /* callArg in func_800927E4 */

typedef struct S_800927E4_2 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_800927E4_2;   /* hitBase in func_800927E4 */

typedef struct S_800927E4_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x30];
    s32 unk_5C;
    u8 pad_60[0x28];
    u16 unk_88;
} S_800927E4_3;   /* arg3 in func_800927E4 */

typedef struct S_800927E4_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800927E4_4;   /* page in func_800927E4 */

typedef struct S_800927E4_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_5;   /* (void *)coordUnsigned in func_800927E4 */


typedef struct S_800927E4_7 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    u8 * unk_10;
} S_800927E4_7;   /* obj in func_800927E4 */

typedef struct S_800927E4_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800927E4_8;   /* prim in func_800927E4 */

typedef struct S_800927E4_9 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
    u8 pad_AC[0x2];
    s16 unk_AE;
} S_800927E4_9;   /* effect in func_800927E4 */

typedef struct S_800927E4_10 {
    u8 pad_00[0x1];
    u8 unk_01;
    s8 unk_02;
} S_800927E4_10;   /* entity in func_800927E4 */

typedef struct S_800927E4_11 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800927E4_11;   /* flagsBase in func_800927E4 */

/* Advances a directional animation, spawns its effect and message, and handles completion. */
void func_800927E4(void *action, s32 actor_id, Rec_D_80082E80 *sprite, S_800927E4_3 *actor) {
    u16 offset[3];
    void *effect_obj;
    S_800927E4_8 *effect_prim;
    S_800927E4_9 *effect;
    S_800927E4_10 *entity;
    s32 text;
    s32 text_root;
    s32 state_or_text;
    u16 timer;
    u8 *angle_hi;
    s16 *angle_page;
    s32 tail_value; /* MATCH: keep the shared-tail store value in retail's v0. */
    u8 *flags_base;

    state_or_text = ((S_800927E4_0 *)action)->unk_9B;
    if (state_or_text == 1) {
        goto state_one;
    }
    if (state_or_text < 2) {
        ASM_CLOBBER("$2");   /* Pin: removal changes a delay-slot fill. */
        if (state_or_text == 0) {
            goto state_zero;
        }
        goto done;
    } else if (state_or_text == 2) {
        goto state_two;
    }
done:
    return;

state_zero:
    if (((S_800927E4_0 *)action)->unk_9A == 0x2C) {
        register void *anim_sprite ASM_REG("$4") = sprite;   /* Pin: removal reorders the instructions (same instructions, different order). */
        u8 *anim_table = D_800DD0B8;
        u8 *angle_base;

        ASM_CLOBBER("$2");   /* Pin: removal changes a delay-slot fill. */
        angle_base = (u8 *)0x80080000;
        ASM_KEEP(angle_base);   /* Pin: removal reorders the instructions (same instructions, different order). */
        ((S_800927E4_1 *)anim_sprite)->unk_2C = anim_table;
        func_80048A44(
            anim_sprite,
            anim_table[((((S_800927E4_2 *)angle_base)->unk_3228 +
                    actor->unk_2A.s + 0x100) >> 9) & 7],
            0,
            1);
        ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
        return;
    }

    angle_hi = (u8 *)0x80080000;
    ASM_KEEP(angle_hi);   /* Pin: removal changes the whole function shape. */
    angle_page = (s16 *)(angle_hi + 0x3160);
    ASM_KEEP(angle_page);   /* Pin: removal changes a delay-slot fill. */
    {
        s32 base_angle = ((S_800927E4_4 *)angle_page)->unk_C8;
        s32 signed_angle = actor->unk_2A.s;
        s32 angle_or_sprite;
        s32 next_angle;

        ASM_MEM_BARRIER();   /* Pin: removal changes the callee-saved set / frame layout. */
        angle_or_sprite = actor->unk_2A.u;
        if ((((base_angle + signed_angle + 0x100) >> 9) & 7) == 2) {
            angle_or_sprite = (s32)sprite;
            {
                register u8 *anim_table ASM_REG("$3") = D_800DD0B8;   /* Pin: removal changes the instruction count (a copy retail keeps is dropped or added). */

                ((S_800927E4_5 *)((void *)angle_or_sprite))->unk_2C = anim_table;
                func_80048A44(
                    (void *)angle_or_sprite,
                    anim_table[((((S_800927E4_4 *)angle_page)->unk_C8 +
                            actor->unk_2A.s + 0x100) >> 9) & 7],
                    0,
                    1);
                ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
                return;
            }
        }

        next_angle = angle_or_sprite + 0x200;
        actor->unk_2A.u = next_angle;
    }
    return;

state_one:
    if (func_8003DE58(sprite->unk_08, sprite, offset, 0) == 0 &&
        !(sprite->unk_14.at00_u16.v & 0x8000)) {
        return;
    }

    if (!(actor->unk_1C & 0x100000)) {
        void *owner_obj = (u8 *)action - 0x20;
        register s32 zero ASM_REG("$6") = 0;   /* Pin: removal changes the whole function shape. */
        ASM_KEEP_NV(owner_obj);   /* Pin: removal reorders the instructions (same instructions, different order). */
        ASM_KEEP_NV(zero);   /* Pin: removal changes the register colouring. */
        effect_obj = func_800A8608(
            owner_obj, ((S_800927E4_0 *)action)->unk_110, zero, zero, 0);
        if (effect_obj != 0) {
            u8 *handler = (u8 *)0x80090000;

            ASM_KEEP(handler);   /* Pin: removal rematerialises a constant retail keeps in a register. */
            handler -= 0x2B90;
            ((S_800927E4_7 *)effect_obj)->unk_10 = handler;
            effect_prim = ((S_800927E4_7 *)effect_obj)->unk_08;
            effect_prim->unk_02 = (sprite->unk_24 << 6) + 0x20;
            effect_prim->unk_06 = (sprite->unk_25 << 6) + 0x20;

            if (sprite->unk_14.at00_u16.v & 0x8000) {
                effect = (u8 *)effect_obj + 0x20;
                effect_prim->unk_0A = actor->unk_88 - 0x50;
            } else {
                effect = (u8 *)effect_obj + 0x20;
                ASM_KEEP(effect);   /* Pin: removal changes the address form (%hi/%lo vs base+offset). */
                effect_prim->unk_02 += offset[0];
                effect_prim->unk_06 += offset[1];
                tail_value = offset[2];
                tail_value += actor->unk_88;
                effect_prim->unk_0A = tail_value;
            }
            effect->unk_A8 = 0x1E;
            effect->unk_AA = 2;
            effect->unk_90 = sprite;
            effect->unk_8C = actor_id;
            effect->unk_9C = (u8 *)action + 0x108;

            entity = ((S_800927E4_0 *)action)->unk_110;
            if (entity != 0 && entity->unk_01 == 4 &&
                entity->unk_02 != 0) {
                effect->unk_AE = 1;
                effect->unk_A8 = 0x3C;
            }
        }

        text_root = func_800990FC();
        state_or_text = func_80099734(actor, func_8009929C(8, text_root));
        state_or_text = func_80099194(D_800E06EE, state_or_text);
        state_or_text = func_80099368(((S_800927E4_0 *)action)->unk_110, state_or_text);
        text = func_80099194(D_800E06F7, state_or_text);
        entity = ((S_800927E4_0 *)action)->unk_110;
        if (entity->unk_01 != 4) {
            text = func_8009965C(entity, text);
        }
        func_80099290(text);
        func_800A5720(text_root);
    }

    ((S_800927E4_0 *)action)->unk_96 = 0x1E;
    ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
    return;

state_two:
    if ((sprite->unk_14.at00_u16.v & 0x8000) ||
        (timer = ((S_800927E4_0 *)action)->unk_96 - 1,
         ((S_800927E4_0 *)action)->unk_96 = timer,
         (s32)(timer << 16) <= 0)) {
        if (((S_800927E4_0 *)action)->unk_110 != 0) {
            func_80091934(action, actor_id, sprite, actor);
            return;
        }
        func_80099F70(actor->unk_5C);
        func_80099F04(actor->unk_5C);
        flags_base = D_80083460;
        ASM_KEEP(flags_base);   /* Pin: removal changes the whole function shape. */
        ((S_800927E4_11 *)flags_base)->unk_02 |= 0x812;
        ((S_800927E4_0 *)action)->unk_8C = D_8008ACDC;
    }
    return;
}
