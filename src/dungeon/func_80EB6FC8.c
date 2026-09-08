#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801727C8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
} S_801727C8_0;   /* arg0 in func_801727C8 */


typedef struct S_801727C8_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801727C8_2_pre;   /* the 0x14 bytes before owner in func_801727C8, addressed as owner[-1] */

typedef struct S_801727C8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801727C8_3;   /* temp_v1_3 in func_801727C8 */


typedef struct S_801727C8_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_801727C8_5;   /* temp_s6 in func_801727C8 */



typedef struct S_801727C8_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801727C8_8;   /* var_v0_3 in func_801727C8 */


typedef struct {
    u8 pad_00[0x12];
    u8 type;
    u8 pad_13;
} DungeonEntry;

extern void *D_80170838[];
s32 func_8003F270();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0();
M2C_UNK func_800DB2DC();
extern DungeonEntry D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_801711A4;
extern u8 D_8017418C;
extern u8 D_801741B4;
extern u8 D_801741BC;

/* Updates an actor's action state, target selection, and animation. */
void func_801727C8(void *action, void *motion, void *sprite, void *actor) {
    static void *const case_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *anim_table;
    M2C_UNK *effect_state;
    s32 visual_base;
    s32 special_slot;
    s32 slot;
    s32 is_special;
    s32 target_x;
    s32 target_y;
    u16 ticks_left;
    u8 *entry;
    s32 current_state;
    s32 state;
    void *visual_flags;
    void *effect_sprite;
    void *owner_sprite;
    void *target_owner;

    is_special = 0;
    visual_base = ((S_801727C8_0 *)action)->unk_A4;
    state = ((S_801727C8_0 *)action)->unk_9B;
    visual_flags = visual_base + 0x20;
    effect_sprite = visual_base + 0x28;
    if (state == 1) {
        goto block_37;
    }
    if ((s32) state >= 2) {
        goto block_4;
    }
    if (state == 0) {
        goto block_7;
    }
    return;
block_4:
    if (state == 2) {
        goto block_40;
    }
    if (state == 3) {
        goto block_45;
    }
    return;
block_7:
    if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x2000)) {
        goto block_13;
    }
    special_slot = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (special_slot - 1) >= 7U) {
        goto block_21;
    }
    (void)case_labels; goto *D_80170838[(u32)((special_slot) - 1)];
jt_c7:
    is_special = 1;
    goto block_18;
jt_c6:
    is_special = 1;
    goto block_19;
jt_c5:
    is_special = 1;
    goto block_20;
block_13:
    slot = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
    if (slot == 2) {
        goto block_19;
    }
    if (slot >= 3) {
        goto block_17;
    }
    entry = NULL;
    if (slot == 1) {
        goto block_20;
    }
    goto block_22;
block_17:
    entry = NULL;
    if (slot != 3) {
        goto block_22;
    }
jt_c3:
block_18:
    entry = actor + 0xE;
    goto block_22;
jt_c2:
block_19:
    entry = actor + 0xB;
    goto block_22;
jt_c1:
block_20:
    entry = actor + 8;
    goto block_22;
jt_c4:
block_21:
    entry = NULL;
block_22:
    if (*entry == 0) {
        goto block_36;
    }
    *(volatile u16 *)((s8 *)action + 0x98) = (u16) (((S_801727C8_0 *)action)->unk_98 & 0xFF7F);
    {
        s32 special_check;

        special_check = is_special;
        ASM_KEEP(special_check);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (special_check == 0) {
            goto block_25;
        }
    }
    target_owner = D_800814A8;
    ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = target_owner;
    goto block_27;
block_25:
    if (D_8006DE24[*entry].type != 2) {
        goto block_28;
    }
    target_owner = ((Rec_D_800E3D7C *)actor)->unk_60.as_pv;
    anim_table = (u8 *)0x80170000;
    if (target_owner == NULL) {
        goto block_34;
    }
block_27:
    {
        register void *owner ASM_REG("$2") = target_owner;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        owner_sprite = ((S_801727C8_2_pre *)owner)[-1].unk_00;
        ASM_USE(owner);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = (s8) ((S_801727C8_3 *)owner_sprite)->unk_24;
        ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = (s8) ((S_801727C8_3 *)owner_sprite)->unk_25;
    }
    goto block_33;
block_28:
    {
        void *spawned_owner;

        spawned_owner = func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 0x10);
        ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = spawned_owner;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }
    target_x = ((Rec_D_800E3D7C *)actor)->unk_72.as_s8;
    target_y = ((Rec_D_800E3D7C *)actor)->unk_73.as_s8;
    if (target_x >= 0) {
        goto block_30;
    }
    target_x = 0 - target_x;
block_30:
    if (target_y >= 0) {
        goto block_32;
    }
    target_y = 0 - target_y;
block_32:
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = target_x;
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = target_y;
block_33:
    anim_table = (u8 *)0x80170000;
block_34:
    anim_table += 0x41B4;
    ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 & 0x7FFF);
    (*(M2C_UNK **)((u8 *)effect_sprite + 0x2C)) = anim_table;
    func_80047784(effect_sprite, *((u8 *) ((((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (s32) anim_table)), 0);
    if (func_800A94A0(actor, entry, is_special, action + 0x98) == 0) {
        goto block_54;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    func_800DB2DC(motion, sprite, actor, 0xA);
    func_800A56E0(0x703);
    current_state = ((S_801727C8_0 *)action)->unk_9B;
    {
        register s32 delay_ticks ASM_REG("$3") = 6;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        ((S_801727C8_0 *)action)->unk_96 = (u16)delay_ticks;
    }
    goto block_44_increment;
block_36:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(actor);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
    ((S_801727C8_0 *)action)->unk_8C = &D_801711A4;
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
    return;
block_39:
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801727C8_0 *)action)->unk_9B = (u8) (((S_801727C8_0 *)action)->unk_9B + 1);
block_40:
    ticks_left = ((S_801727C8_0 *)action)->unk_96 - 1;
    ((S_801727C8_0 *)action)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        goto block_42;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
block_42:
    ((S_801727C8_0 *)action)->unk_98 = (u16) (((S_801727C8_0 *)action)->unk_98 | 0x80);
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801741BC;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801741BC), 0);
block_44:
    current_state = ((S_801727C8_0 *)action)->unk_9B;
block_44_increment:
    ((S_801727C8_0 *)action)->unk_9B = (u8) (current_state + 1);
    return;
block_45:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_54;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm == &D_8017418C) {
        effect_state = &D_80083460;
        goto block_50;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto block_49;
    }
    ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 | 0x8000);
    ((S_801727C8_0 *)action)->unk_A8 = 0;
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_8017418C;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_8017418C), 0);
block_49:
    effect_state = &D_80083460;
block_50:
    if (((S_801727C8_8 *)effect_state)->unk_0C != 0) {
        goto block_54;
    }
    ((S_801727C8_8 *)effect_state)->unk_0A = (u16) (((S_801727C8_8 *)effect_state)->unk_0A - 1);
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801727C8_0 *)action)->unk_8C = &D_801711A4;
    func_800A4ACC(actor);
    if ((s8) ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 <= 0) {
        goto block_53;
    }
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
block_53:
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x7FFF);
    func_800A56E0(0xB4);
block_54:
    return;
}
