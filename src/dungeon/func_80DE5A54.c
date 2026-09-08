#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80174520[];
extern u8 D_80174538[];


typedef struct S_80173254_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173254_0;   /* arg0 in func_80173254 */



typedef struct S_80173254_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173254_3;   /* system_base in func_80173254 */


typedef struct S_80173254_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173254_5;   /* origin in func_80173254 */

/* Updates the entity action state and selects its directional animation. */
void func_80173254(void *action, void *context, void *sprite, void *entity)
{
    void *saved_context;
    void *saved_sprite;
    u8 state;

    saved_context = context;
    saved_sprite = sprite;
#define context saved_context
#define sprite saved_sprite

    state = ((S_80173254_0 *)action)->unk_9B;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        u8 *direction_anims;
        u8 *system_base;

        direction_anims = D_80174538;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        ((S_80173254_3 *)system_base)->unk_0A--;
        ((S_80173254_0 *)action)->unk_9B++;
    }
    return;

state_one:
    {
        u8 *system_base;

        if ((func_80042900(entity, 1) << 16) != 0) {
            s32 entity_flags;

            system_base = (u8 *)&D_80083460;
            if (((S_80173254_3 *)system_base)->unk_02 & 0x1000) {
                return;
            }

            if ((((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) &&
                (func_800AA6B4(action, context, sprite, 0) != 0)) {
                return;
            }

            if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
                if (((S_80173254_3 *)system_base)->unk_02 & 0x2008) {
                    return;
                }
                func_800AA79C(action, context, sprite, entity);
                return;
            }

            if ((func_800A2C34(entity) << 16) != 0) {
                return;
            }

            entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
            if (entity_flags & 0x100) {
                func_800AA258(action, context, sprite, entity);
                return;
            }

            if (entity_flags & 0x80000) {
                func_800AA888(action, context, sprite, entity);
                func_801737DC(action, context, sprite, entity);
                return;
            }

            if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 == 0) {
                return;
            }

            if ((func_800A2C34(entity) << 16) != 0) {
                if ((func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }

            func_800A9A0C(entity);
            func_800A9A04(entity);

            if ((func_80042900(entity, 1) << 16) != 0) {
                u8 *origin;
                s8 coordinate;

                origin = D_80082E80;
                coordinate = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;
                if ((((coordinate == ((S_80173254_5 *)origin)->unk_26) &&
                            (coordinate >= 0)) ||
                        (func_8009FD40(origin, sprite) < 2)) &&
                    ((func_800A6D30() & 7) == 0)) {
                    func_80042B68(entity, 1);
                }
            }

            if ((func_80042900(entity, 1) << 16) != 0) {
                return;
            }
        }
    }

    {
        u8 *direction_anims;

        direction_anims = D_80174520;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 &= ~0x200;
        ((S_80173254_0 *)action)->unk_8C = D_80170E5C;
    }
    ASM_KEEP(saved_sprite);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
