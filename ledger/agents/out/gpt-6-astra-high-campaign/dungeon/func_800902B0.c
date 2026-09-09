#include "common.h"
#include "m2c_compat.h"

typedef struct S_80095A10_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80095A10_0;   /* arg0 in func_80095A10 */

typedef struct S_80095A10_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80095A10_1;   /* arg2 in func_80095A10 */

typedef struct S_80095A10_2 {
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
} S_80095A10_2;   /* arg3 in func_80095A10 */

typedef struct S_80095A10_3 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_80095A10_3;   /* temp_s1 in func_80095A10 */

typedef struct S_80095A10_4 {
    u8 unk_00;
} S_80095A10_4;   /* &D_800E3E40 in func_80095A10 */

typedef struct S_80095A10_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80095A10_5_pre;   /* the 0x18 bytes before temp_v0_3 in func_80095A10, addressed as temp_v0_3[-1] */

typedef struct S_80095A10_5 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80095A10_5;   /* temp_v0_3 in func_80095A10 */

typedef struct S_80095A10_6 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_80095A10_6;   /* temp_v1 in func_80095A10 */

typedef struct S_80095A10_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80095A10_7;   /* temp_v1_2 in func_80095A10 */

typedef struct S_80095A10_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80095A10_8;   /* arg1 in func_80095A10 */

typedef struct S_80095A10_9 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80095A10_9;   /* temp_v1_4 in func_80095A10 */

typedef struct S_80095A10_10 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80095A10_10;   /* ((S_80095A10_2 *)arg3)->unk_60 in func_80095A10 */


extern void *D_80088AF8[];
s32 Control_CD();
void func_800424E0();
void func_80042560();
M2C_UNK func_80042640();
void func_80042B68();
void func_80043914();
s32 func_80047DB8();
void func_80047DF0();
void func_80048A44();
M2C_UNK func_80093C70();
M2C_UNK func_80093D8C();
M2C_UNK func_800956B8();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16);
s32 func_800A1618();
M2C_UNK func_800A56E0();
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern u8 *D_80082EB0;
extern s16 D_80083228;
extern u8 D_80083460[12];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

/* Advances the resource loading, object creation, and animation sequence. */
void func_80095A10(u8 *actor_in, void *position_in, void *animation_in, u8 *context_in) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    u8 *actor = actor_in;
    void *position = position_in;
    void *animation = animation_in;
    register u8 *context ASM_REG("$19") = context_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *animation_table;
    s32 load_resource;
    s32 spawn_resource;
    u32 object_flags;
    u16 ticks_left;
    u16 animation_flags;
    u8 *resource_info;
    u32 state;
    u32 previous_state;
    void *object;
    void *object_scale;
    void *object_position;
    u8 *status;

    state = ((S_80095A10_0 *)actor)->unk_9B;
    resource_info = D_80082EB0;
    if (state >= 7U) {
        goto done;
    }
    (void)state_labels; goto *D_80088AF8[(u32)(state)];
jt_c0:
    if (!(((S_80095A10_1 *)animation)->unk_14 & 0xE000)) {
        goto done;
    }
    (*(M2C_UNK **)((u8 *)animation + 0x2C)) = D_800DD138;
    func_80048A44(animation, *((((s32) (D_80083228 + ((S_80095A10_2 *)context)->unk_2A + 0x100) >> 9) & 7) + D_800DD138), 0, 1);
    ((S_80095A10_1 *)animation)->unk_14 = (u16) (((S_80095A10_1 *)animation)->unk_14 | 0x200);
    func_80093C70(actor, position, animation);
    func_80093D8C(actor, position, animation);
    goto advance_state;
jt_c1:
    load_resource = func_800A1618(((S_80095A10_3 *)resource_info)->unk_00, 2);
    if (load_resource == 0) {
        goto advance_state;
    }
    D_80081488 = func_80047DB8(((S_80095A10_3 *)resource_info)->unk_00);
    func_800A0B94(((S_80095A10_3 *)resource_info)->unk_00, load_resource, 0);
    (*(s8 *)&D_800E3E40) = 0;
    Control_CD(0xFF, &D_8003E140, &D_800E3E40);
    goto advance_state;
jt_c2:
    if (((S_80095A10_4 *)(&D_800E3E40))->unk_00 == 0) {
        goto done;
    }
    func_80047DF0(state);
    goto advance_state;
jt_c3:
    spawn_resource = func_800A1618(((S_80095A10_3 *)resource_info)->unk_00, 2);
    if (spawn_resource == 0) {
        goto done;
    }
    func_80043914(D_80082EB0);
    object = func_800A0B94(((S_80095A10_3 *)resource_info)->unk_00, spawn_resource, 1)(6, ((S_80095A10_2 *)context)->unk_72, ((S_80095A10_2 *)context)->unk_73, (s16) (((S_80095A10_2 *)context)->unk_88 - 0x20));
    if (object == NULL) {
        goto start_delay;
    }
    ((S_80095A10_2 *)context)->unk_60 = object;
    D_800E3DF0[((S_80095A10_3 *)resource_info)->unk_03 & 0x1F] = object;
    object_scale = ((S_80095A10_5_pre *)object)[-1].unk_04;
    ((S_80095A10_6 *)object_scale)->unk_1E = 0x800;
    ((S_80095A10_6 *)object_scale)->unk_1C = 0x800;
    object_position = ((S_80095A10_5_pre *)object)[-1].unk_00;
    ((S_80095A10_7 *)object_position)->unk_02 = (u16) ((S_80095A10_8 *)position)->unk_02;
    ((S_80095A10_7 *)object_position)->unk_06 = (u16) ((S_80095A10_8 *)position)->unk_06;
    ((S_80095A10_7 *)object_position)->unk_0A = (s16) (((S_80095A10_8 *)position)->unk_0A - 0x10);
    func_80042640(object, ((S_80095A10_5 *)object)->unk_13);
    func_800424E0(object, ((S_80095A10_5 *)object)->unk_13, resource_info);
    object_flags = ((S_80095A10_5 *)object)->unk_1C;
    object_flags |= 0x02000000;
    object_flags |= 0x20000;
    ((S_80095A10_5 *)object)->unk_1C = object_flags;
    func_80042560(object);
    func_800A56E0(0x704);
    func_80042B68(object, 3);
    func_80042B68(object, 1);
    if (((S_80095A10_5 *)object)->unk_25 != 0) {
        goto start_delay;
    }
    ((S_80095A10_5 *)object)->unk_25 = 1U;
start_delay:
    previous_state = ((S_80095A10_0 *)actor)->unk_9B;
    {
        register u16 timer ASM_REG("$3") = 0x10U;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ((S_80095A10_0 *)actor)->unk_96 = timer;
        goto store_next_state;
    }
jt_c4:
    ticks_left = ((S_80095A10_0 *)actor)->unk_96 - 1;
    ((S_80095A10_0 *)actor)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        goto done;
    }
    (*(M2C_UNK **)((u8 *)animation + 0x2C)) = D_800DD140;
    func_80048A44(animation, *((((s32) (D_80083228 + ((S_80095A10_2 *)context)->unk_2A + 0x100) >> 9) & 7) + D_800DD140), 0, 1);
    goto advance_state;
jt_c5:
    animation_flags = ((S_80095A10_1 *)animation)->unk_14;
    if (!(animation_flags & 0x6000)) {
        goto done;
    }
    animation_table = D_800DCFB0;
    ((S_80095A10_1 *)animation)->unk_14 = (u16) (animation_flags & 0xFDFF);
set_animation:
    (*(M2C_UNK **)((u8 *)animation + 0x2C)) = animation_table;
    func_80048A44(animation, *((((s32) (D_80083228 + ((S_80095A10_2 *)context)->unk_2A + 0x100) >> 9) & 7) + animation_table), 0, 1);
advance_state:
    previous_state = ((S_80095A10_0 *)actor)->unk_9B;
store_next_state:
    ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
    return;
jt_c6:
    if (((S_80095A10_10 *)(((S_80095A10_2 *)context)->unk_60))->unk_14 & 0x100000) {
        goto done;
    }
    func_800956B8(actor, position, animation, resource_info);
    ((S_80095A10_0 *)actor)->unk_8C = &D_8008ACDC;
    func_80099F70(((S_80095A10_2 *)context)->unk_5C);
    func_80099F04(((S_80095A10_2 *)context)->unk_5C);
    status = D_80083460;
    ((S_80095A10_9 *)status)->unk_02 = (u16) (((S_80095A10_9 *)status)->unk_02 | 0x812);
done:
    return;
}
