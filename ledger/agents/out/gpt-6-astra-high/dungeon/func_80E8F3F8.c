#include "common.h"
#include "records/Rec_D_800E3D7C.h"


#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
#else
#define LEGACY_ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern void func_80047784(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D48(void *, void *, void *);

extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801710F4[];
extern u8 D_80174F00[];


typedef struct S_80174BF8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BF8_0;   /* arg0 in func_80174BF8 */


typedef struct S_80174BF8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_80174BF8_2;   /* arg2 in func_80174BF8 */

typedef struct S_80174BF8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174BF8_3;   /* counter in func_80174BF8 */

/* Initialize a timed action, then restore animation and clear the entity flags. */
void func_80174BF8(S_80174BF8_0 *action, void *context, S_80174BF8_2 *animation, Rec_D_800E3D7C *entity)
{
    void *entity_arg;
    u8 *active_count;
    u16 ticks_left;
    u8 state;

    state = action->unk_9B;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_800A56E0(0x50C);
    action->unk_96 = 10;
    func_80174D48(context, animation, entity);
    entity->unk_48.at00_s8.v = 0;
    entity->unk_48.at01_s8.v = 0;
    action->unk_9B++;

active:
    if (!(animation->unk_14 & 0x8000)) {
        ticks_left = action->unk_96;
        action->unk_96 = ticks_left - 1;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    entity_arg = entity;
    LEGACY_ASM_KEEP(entity_arg);
    active_count = D_80083460;
    LEGACY_ASM_KEEP(active_count);
    ((S_80174BF8_3 *)active_count)->unk_0A--;
    animation->unk_2C = D_80174F00;
    func_800AD594(entity_arg, 0x200);
    func_80047784(animation,
        animation->unk_2C[((D_80083228[0] + entity->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    action->unk_8C = D_801710F4;
    func_800A4ACC(entity);
    entity->unk_6D.as_s8 = 0;
    entity->unk_44.at02_u16.v &= 0x7FFF;
}
