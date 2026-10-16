#ifndef DUNGEON_OVL_7F469800_P06_H
#define DUNGEON_OVL_7F469800_P06_H
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct T_80174C44_S_80174C44_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} T_80174C44_S_80174C44_0;   /* arg0 in func_80174C44 */


typedef struct T_80174C44_S_80174C44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} T_80174C44_S_80174C44_4;   /* global in func_80174C44 */




extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern void func_800AD4D0(void *);
extern u8 D_80175E3C[];
extern u8 D_80175E44[];
extern u8 D_80175E4C[];
void func_80174C44(T_80174C44_S_80174C44_0 *controller, EntityRec *transform, Rec_D_80082E80 *entity, void *actor);
extern void func_801724BC();
#endif
