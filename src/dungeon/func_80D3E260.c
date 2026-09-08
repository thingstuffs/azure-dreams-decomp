#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct Copy48 {
    u32 words[12];
} Copy48;

typedef struct ItemInfo {
    u8 pad00[0x12];
    u8 type;
    u8 pad13;
} ItemInfo;

extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_801708B8(void *, void *, void *);

extern s32 D_80045340;
extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D58D8[];
extern s8 D_800DCECC[];
extern u8 D_800E23E0[];
extern u8 D_800E2410[];
extern void *D_80170868[];
extern u8 D_80171A80[];


typedef struct S_80173A60_0 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x60];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173A60_0;   /* arg0 in func_80173A60 */

typedef struct S_80173A60_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80173A60_1_pre;   /* the 0x14 bytes before active in func_80173A60, addressed as active[-1] */



typedef struct S_80173A60_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x14];
    void * unk_AC;
} S_80173A60_4;   /* state in func_80173A60 */

typedef struct S_80173A60_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173A60_5;   /* object in func_80173A60 */

typedef struct S_80173A60_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173A60_6;   /* copy in func_80173A60 */

typedef struct S_80173A60_7 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80173A60_7;   /* direction in func_80173A60 */

typedef struct S_80173A60_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173A60_8;   /* target in func_80173A60 */

typedef struct S_80173A60_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    volatile s32 unk_0C;
} S_80173A60_9;   /* global in func_80173A60 */

/* Advances an actor's item action, spawning its visual effect and restoring idle state. */
void func_80173A60(void *actor_state, void *motion, void *sprite, void *actor)
{
    static void *const kind_labels[] = {
        &&L_kind1, &&L_kind2, &&L_kind3, &&L_kind4,
        &&L_kind5, &&L_kind6, &&L_kind7
    };
    register s32 use_player ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *item_id;

    use_player = 0;
    switch (((S_80173A60_0 *)actor_state)->unk_9B) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            if (kind_index >= 7) {
                goto L_kind4;
            }
            (void)kind_labels;
            goto *D_80170868[kind_index];

L_kind7:
            use_player = 1;
            goto L_kind3;
L_kind6:
            use_player = 1;
            goto L_kind2;
L_kind5:
            use_player = 1;
            goto L_kind1;
        }

        switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
        case 3:
L_kind3:
            item_id = (u8 *)actor + 0xE;
            break;
        case 2:
L_kind2:
            item_id = (u8 *)actor + 0xB;
            break;
        case 1:
L_kind1:
            item_id = (u8 *)actor + 8;
            break;
        default:
L_kind4:
            item_id = 0;
            break;
        }

        if (*item_id != 0) {
            s32 use_player_test;
            void *linked_actor;

            ((S_80173A60_0 *)actor_state)->unk_98 &= 0xFF7F;
            ASM_KEEP(use_player);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            use_player_test = use_player;
            ASM_KEEP(use_player_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (use_player_test != 0) {
                linked_actor = D_800814A8;
                (*(void * *)((u8 *)actor + 0x60)) = linked_actor;
                goto L_copy_linked;
            } else if (D_8006DE24[*item_id].type == 2) {
                linked_actor = (*(void * *)((u8 *)actor + 0x60));
                if (linked_actor != 0) {
                    register u8 *linked_sprite ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

L_copy_linked:
                    linked_sprite = ((S_80173A60_1_pre *)linked_actor)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = linked_sprite[0x24];
                    (*(u8 *)((u8 *)actor + 0x73)) = linked_sprite[0x25];
                }
            } else {
                s32 offset_x;
                s32 offset_y;

                linked_actor = func_800A05A4(actor,
                                       ((Rec_D_80082E80 *)sprite)->unk_24,
                                       ((Rec_D_80082E80 *)sprite)->unk_25,
                                       (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                (*(void * volatile *)((u8 *)actor + 0x60)) = linked_actor;
                ASM_USE(linked_actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                offset_x = (*(s8 *)((u8 *)actor + 0x72));
                offset_y = (*(s8 *)((u8 *)actor + 0x73));
                if (offset_x < 0) {
                    offset_x = -offset_x;
                }
                if (offset_y < 0) {
                    offset_y = -offset_y;
                }
                (*(u8 *)((u8 *)actor + 0x72)) = offset_x;
                (*(u8 *)((u8 *)actor + 0x73)) = offset_y;
            }

            if (func_800A94A0(actor, item_id, use_player,
                              (u16 *)((u8 *)actor_state + 0x98)) == 0) {
                return;
            }
            ((S_80173A60_0 *)actor_state)->unk_96.u = 0;
            ((S_80173A60_0 *)actor_state)->unk_9B++;
            return;
        }

        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_80173A60_0 *)actor_state)->unk_8C = D_80171A80;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80173A60_0 *)actor_state)->unk_9B++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        {
            u16 timer;

            timer = ((S_80173A60_0 *)actor_state)->unk_96.u + 1;
            ((S_80173A60_0 *)actor_state)->unk_96.u = timer;
            if ((s16)timer == 3) {
                u8 *effect;

                effect = func_8003FD64(0x112, D_80083498);
                if (effect != 0) {
                    u8 *effect_state;
                    u8 *effect_sprite;
                    u8 *camera;
                    u8 *effect_pos;
                    u8 *anim_table;
                    u8 *anim_entry;
                    s8 *height_offsets;
                    register s32 direction_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    effect_state = effect + 0x20;
                    ((S_80173A60_4 *)effect_state)->unk_96 = 0x10;
                    ((S_80173A60_5 *)effect)->unk_10 = D_800D58D8;
                    ((S_80173A60_4 *)effect_state)->unk_AC = motion;
                    ((S_80173A60_4 *)effect_state)->unk_94 = (*(u16 *)((u8 *)actor + 0x2A));
                    effect_sprite = ((S_80173A60_5 *)effect)->unk_0C;
                    *(Copy48 *)effect_sprite = *(Copy48 *)sprite;
                    ((S_80173A60_6 *)effect_sprite)->unk_1E = 0x1000;
                    ((S_80173A60_6 *)effect_sprite)->unk_1C = 0x1000;
                    ((S_80173A60_6 *)effect_sprite)->unk_0E = 0x80;
                    ((S_80173A60_6 *)effect_sprite)->unk_0D = 0x80;
                    ((S_80173A60_6 *)effect_sprite)->unk_0C = 0x80;
                    func_8004491C(effect, &D_80045340);

                    anim_table = D_800E2410;
                    ((S_80173A60_6 *)effect_sprite)->unk_2C = anim_table;
                    camera = D_80083160;
                    direction_index = ((((S_80173A60_7 *)camera)->unk_C8 +
                              (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                    anim_entry = (u8 *)((u32)direction_index + (u32)anim_table);
                    func_80047784(effect_sprite, *anim_entry, 0);
                    ((S_80173A60_6 *)effect_sprite)->unk_14 &= 0xFFF3;

                    direction_index = ((((S_80173A60_7 *)camera)->unk_C8 +
                              ((S_80173A60_0 *)actor_state)->unk_2A.s + 0x100) >> 9) & 7;
                    height_offsets = D_800DCECC;
                    ((S_80173A60_6 *)effect_sprite)->unk_06 = -(height_offsets[direction_index] * 4);
                    ((S_80173A60_4 *)effect_state)->unk_94 =
                        (((S_80173A60_0 *)actor_state)->unk_2A.u >> 9) & 7;
                    ((S_80173A60_4 *)effect_state)->unk_2A = ((S_80173A60_0 *)actor_state)->unk_2A.u;

                    effect_pos = ((S_80173A60_5 *)effect)->unk_08;
                    ((S_80173A60_8 *)effect_pos)->unk_02 = ((Rec_D_800E3D7C *)motion)->unk_00.at02_u16.v;
                    ((S_80173A60_8 *)effect_pos)->unk_06 = ((Rec_D_800E3D7C *)motion)->unk_04.at02_u16.v;
                    ((S_80173A60_8 *)effect_pos)->unk_0A = ((Rec_D_800E3D7C *)motion)->unk_08.at02_u16.v;
                }
            }

            if (((S_80173A60_0 *)actor_state)->unk_96.s == 0x10) {
                u8 *anim_table;
                s32 direction_index;

                anim_table = D_800E23E0;
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                direction_index = ((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
                func_80047784(sprite, anim_table[direction_index], 3);
                if (((S_80173A60_0 *)actor_state)->unk_B0 == 0) {
                    func_801708B8(actor_state, motion, sprite);
                }
            }

            if (((S_80173A60_0 *)actor_state)->unk_96.s == 0x13 ||
                (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                ((S_80173A60_0 *)actor_state)->unk_98 |= 0x80;
                func_800A56E0(0x81B);
            }

            if (((S_80173A60_0 *)actor_state)->unk_96.s < 0x19 &&
                !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
            ((S_80173A60_0 *)actor_state)->unk_9B++;
            return;
        }

    case 3:
        {
            u8 *action_status;

            action_status = D_80083460;
            if (((S_80173A60_9 *)action_status)->unk_0C != 0) {
                return;
            }
            ((S_80173A60_0 *)actor_state)->unk_96.u = 0;
            if (((S_80173A60_9 *)action_status)->unk_0C != 0) {
                return;
            }
            ((S_80173A60_9 *)action_status)->unk_0A--;
            ((S_80173A60_0 *)actor_state)->unk_8C = D_80171A80;
            func_800A4ACC(actor);
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u8 *)((u8 *)actor + 0x6D))--;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            func_800A56E0(0xB4);
            return;
        }
    }
}
