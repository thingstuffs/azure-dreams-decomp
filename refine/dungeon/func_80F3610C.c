#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_8017390C_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017390C_0;   /* arg0 in func_8017390C */

typedef struct S_8017390C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x28];
    u8 unk_48;
    u8 unk_49;
} S_8017390C_1;   /* saved_arg3 in func_8017390C */

typedef struct S_8017390C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017390C_2;   /* temp_s0 in func_8017390C */

typedef struct S_8017390C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_8017390C_3;   /* saved_arg1 in func_8017390C */

typedef struct S_8017390C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017390C_4;   /* temp_v1 in func_8017390C */

typedef struct S_8017390C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8017390C_5;   /* temp_s1 in func_8017390C */

typedef struct S_8017390C_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017390C_6;   /* arg2 in func_8017390C */

typedef struct {
    s32 value;
} __attribute__((packed)) Unaligned32;


extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 func_8004A658();
extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_800BC26C();

extern s32 D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80173770;
extern s16 D_8008346A;

/* Spawns an object from stored appearance data and advances the actor's state. */
void func_8017390C(S_8017390C_0 *actor, void *transform, S_8017390C_6 *render, void *actor_data)
{
    s32 pos_z;
    s32 pos_x;
    s32 state;
    register void *work_data ASM_REG("$19") = transform;   /* MATCH pin: load-bearing for the whole function shape */
    register void *appearance ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *spawned_obj;
    S_8017390C_5 *spawned_render;
    void *spawned_data;
    void *render_asset;
    S_8017390C_4 *spawned_transform;
    void *update_actor;
    void *init_obj;
    register s32 angle ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */

    appearance = actor_data;
    state = actor->unk_9B;
    if (state == 1) {
        goto active;
    }
    if (state >= 2) {
        goto high_state;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

high_state:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (D_8008346A != 0) {
        goto done;
    }
    actor->unk_9B = 1;

active:
    if (((S_8017390C_1 *)appearance)->unk_49 != 0) {
        spawned_obj = func_8003FC64(0x12);
        if (spawned_obj != 0) {
            init_obj = spawned_obj;
            spawned_transform = ((S_8017390C_2 *)spawned_obj)->unk_08;
            pos_x = ((S_8017390C_3 *)work_data)->unk_00;
            spawned_render = ((S_8017390C_2 *)spawned_obj)->unk_0C;
            spawned_transform->unk_00 = pos_x;
            spawned_transform->unk_04 = ((S_8017390C_3 *)work_data)->unk_04;
            pos_z = ((S_8017390C_3 *)work_data)->unk_08;
            spawned_transform->unk_10 = 0;
            spawned_transform->unk_0C = 0;
            spawned_transform->unk_14 = 0xFFEE0000;
            spawned_transform->unk_08 = pos_z;
            func_8004491C(init_obj, &D_80045340, pos_z);
            spawned_render->unk_0C = 0x808080;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            angle = 0xC90;
            spawned_render->unk_1E = angle;
            spawned_data = (u8 *)spawned_obj + 0x20;
            spawned_render->unk_1C = angle;
            work_data = spawned_data;
            if (((S_8017390C_1 *)appearance)->unk_49 == 0x12) {
                render_asset = &D_8006E240;
            } else {
                render_asset = (void *)func_8004A658(
                    ((S_8017390C_1 *)appearance)->unk_49, ((S_8017390C_1 *)appearance)->unk_48);
            }
            spawned_render->unk_08 = render_asset;
            ASM_KEEP(render_asset);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ((S_8017390C_3 *)work_data)->unk_A8 = render->unk_24;
            ((S_8017390C_3 *)work_data)->unk_AA = render->unk_25;
            *(Unaligned32 *)((u8 *)spawned_data + 0x48) =
                *(Unaligned32 *)((u8 *)appearance + 0x48);
            func_800BC26C(spawned_obj, 0, 0, 0);
            ((S_8017390C_2 *)spawned_obj)->unk_10 = &D_80173770;
        }
        ((S_8017390C_1 *)appearance)->unk_48 = 0;
        ((S_8017390C_1 *)appearance)->unk_49 = 0;
    }

    render->unk_10 = 0x20;
    render->unk_12 -= 0x80;
    render->unk_14 |= 0xC;
    ((S_8017390C_1 *)appearance)->unk_1C |= 0x10000000;
    render->unk_0C = 0x808080;
    actor->unk_96 = 0x10;
    actor->unk_9B++;
    func_800A56E0(0x805);
    goto done;

state_two:
    update_actor = actor;
    ASM_KEEP(update_actor);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(work_data);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800AD058(update_actor, work_data, render, appearance);

done:
    return;
}
