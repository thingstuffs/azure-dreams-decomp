#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef __SIZE_TYPE__ uptr;

typedef struct S_801728E4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801728E4_0;   /* arg0 in func_801728E4 */

typedef struct S_801728E4_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_801728E4_1;   /* arg3 in func_801728E4 */


typedef struct S_801728E4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728E4_3;   /* entry in func_801728E4 */

typedef struct S_801728E4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801728E4_4;   /* arg2 in func_801728E4 */

typedef struct S_801728E4_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728E4_5;   /* global in func_801728E4 */


typedef struct {
    u8 pad00[0x12];
    u8 field12;
    u8 field13;
} ItemInfo;

extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[0x18];
extern void *D_80170838[5];
extern void *D_80170850[7];
extern u8 D_80170EE4[8];
extern u8 D_801765D8[8];
extern u8 D_80176648[8];
extern u8 D_80176668[8];

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, u16 *);
extern void func_800BB044(void *);

/* Advances an actor's item action through source selection, animation, and cleanup. */
void func_801728E4(void *action, void *item, void *sprite, void *actor)
{
    u8 state;
    register s32 use_global_source ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 action_flags;
    s32 item_kind;
    register u8 *anim_table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    static void *const state_labels[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    static void *const kind_labels[] = {
        &&K8, &&KB, &&KE, &&KNone, &&K8Special, &&KBSpecial, &&KESpecial
    };

    state = ((S_801728E4_0 *)action)->unk_9B;
    use_global_source = 0;
    if ((u32)state >= 5) {
        return;
    }
    goto *D_80170838[state];

L0:
{
    register void *source_entity ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    item = 0;
    if (((S_801728E4_1 *)actor)->unk_1C & 0x2000) {
        s32 kind_index = (((S_801728E4_1 *)actor)->unk_46 & 0x3FFF) - 1;

        if ((u32)kind_index >= 7) {
            goto HaveSource;
        }
        goto *D_80170850[kind_index];

KESpecial:
        use_global_source = 1;
        goto KE;
KBSpecial:
        use_global_source = 1;
        goto KB;
K8Special:
        use_global_source = 1;
        goto K8;
    }

    item_kind = ((S_801728E4_1 *)actor)->unk_46 & 0x3FFF;
    switch (item_kind) {
    case 1:
        goto K8;
    case 2:
        goto KB;
    case 3:
        goto KE;
    default:
        goto HaveSource;
    }

KE:
    item = (u8 *)actor + 0xE;
    goto HaveSource;
KB:
    item = (u8 *)actor + 0xB;
    goto HaveSource;
K8:
    item = (u8 *)actor + 8;
KNone:
HaveSource:
    if (((Rec_D_800E3D7C *)item)->unk_00.at00_u8.v == 0) {
        return;
    }

    {
        s32 global_source_test;

        ((S_801728E4_0 *)action)->unk_98 &= 0xFF7F;
        global_source_test = use_global_source;
        ASM_KEEP(global_source_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (global_source_test) {
            source_entity = D_800814A8;
            ((S_801728E4_1 *)actor)->unk_60 = source_entity;
            goto CopyFacing;
        }
    }

    if (D_8006DE24[((Rec_D_800E3D7C *)item)->unk_00.at00_u8.v].field12 != 2) {
        goto MakeSource;
    }

    source_entity = ((S_801728E4_1 *)actor)->unk_60;
    if (source_entity == 0) {
        goto CallUpdate;
    }

CopyFacing:
    ASM_KEEP(actor);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    {
        u8 *source_sprite = *(u8 **)((u8 *)source_entity - 0x14);
        ASM_KEEP(source_entity);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_801728E4_1 *)actor)->unk_72.s = ((S_801728E4_3 *)source_sprite)->unk_24;
        ((S_801728E4_1 *)actor)->unk_73.s = ((S_801728E4_3 *)source_sprite)->unk_25;
    }
    goto Update;
}

MakeSource:
    {
        s32 target_x;
        s32 target_z;

        ((S_801728E4_1 *)actor)->unk_60 =
            func_800A05A4(actor,
                          ((S_801728E4_4 *)sprite)->unk_24,
                          ((S_801728E4_4 *)sprite)->unk_25,
                          ((S_801728E4_1 *)actor)->unk_2A,
                          0x10);
        ASM_MEM_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        target_x = ((S_801728E4_1 *)actor)->unk_72.u;
        target_z = ((S_801728E4_1 *)actor)->unk_73.u;
        if (target_x < 0) {
            target_x = -target_x;
        }
        if (target_z < 0) {
            target_z = -target_z;
        }
        ((S_801728E4_1 *)actor)->unk_72.u = target_x;
        ((S_801728E4_1 *)actor)->unk_73.u = target_z;
    }

Update:
CallUpdate:
    if (!func_800A94A0(actor, item, use_global_source, (u16 *)((u8 *)action + 0x98))) {
        return;
    }
    func_800BB044(actor);
    goto AdvanceState;

L1:
    if (func_8003F270()) {
        ((S_801728E4_4 *)sprite)->unk_14 |= 0x0800;
        return;
    }
    ((S_801728E4_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_801728E4_0 *)action)->unk_9B++;

L2:
    if (!(((S_801728E4_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    anim_table = D_80176648;
    goto PlayEffect;

L3:
    if (((S_801728E4_4 *)sprite)->unk_04 == 6 && (((S_801728E4_4 *)sprite)->unk_14 & 0x1000)) {
        ((S_801728E4_0 *)action)->unk_98 |= 0x80;
    } else if (((S_801728E4_4 *)sprite)->unk_14 & 0xE000) {
        ((S_801728E4_0 *)action)->unk_98 |= 0x80;
    }
    if (!(((S_801728E4_0 *)action)->unk_98 & 0x80)) {
        return;
    }
    if (!(((S_801728E4_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    anim_table = D_80176668;

PlayEffect:
    (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)((uptr)(((D_80083228 + ((S_801728E4_1 *)actor)->unk_2A + 0x100) >> 9) & 7) +
                (uptr)anim_table),
        0);
AdvanceState:
    ((S_801728E4_0 *)action)->unk_9B++;
    return;

L4:
    if (((S_801728E4_4 *)sprite)->unk_14 & 0xE000) {
        anim_table = D_801765D8;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((D_80083228 + ((S_801728E4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    ((Rec_D_800E3D7C *)item)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)item)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)item)->unk_0C.as_s32 = 0;
    func_800A2B04(item, ((S_801728E4_4 *)sprite)->unk_24, ((S_801728E4_4 *)sprite)->unk_25);
    {
        u8 *action_status = D_80083460;

        if (((S_801728E4_5 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_801728E4_5 *)action_status)->unk_0A--;
    }
    ((S_801728E4_0 *)action)->unk_8C = D_80170EE4;
    func_800A4ACC(actor);
    ((S_801728E4_1 *)actor)->unk_73.s = 0;
    ((S_801728E4_1 *)actor)->unk_72.s = 0;
    ((S_801728E4_1 *)actor)->unk_6D--;
    ((S_801728E4_1 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}
