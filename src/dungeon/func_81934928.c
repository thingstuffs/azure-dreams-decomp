#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81934928_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    union { u16 s; s16 u; } unk_12;   /* accessed as both */
    u16 unk_14;
} S_81934928_0;   /* self in func_81934928 */

typedef struct S_81934928_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81934928_1;   /* copy_page in func_81934928 */

typedef struct S_81934928_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934928_2;   /* created in func_81934928 */

typedef struct S_81934928_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_81934928_3;   /* part in func_81934928 */

typedef struct S_81934928_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81934928_4;   /* found in func_81934928 */

typedef struct S_81934928_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81934928_5;   /* owner in func_81934928 */

typedef struct S_81934928_6 {
    u16 unk_00;
} S_81934928_6;   /* ((S_81934928_0 *)self)->unk_04 in func_81934928 */


typedef struct {
    s32 word[6];
} Copy24;

extern void func_80024004(void *);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void *func_800A3F28(s32, s32, void *, void *);
extern void func_800A56E0(s32);

extern s32 D_8002445C[];
extern s32 D_80024740[];

/* Spawns a timed particle effect, processes its midpoint target, and marks completion. */
void func_81934928(void *self, void *output)
{
    Copy24 *copy_src;
    void *effect;
    void *output_data;
    void *search_origin;
    void *target;
    void *particle;
    s32 rand_quotient;
    s16 state;
    s32 spawn_index;
    s32 origin_component;
    s32 random_value;
    s32 value;
    s16 countdown;
    s32 page_value;

    state = ((S_81934928_0 *)self)->unk_0A.s;
    effect = ((S_81934928_0 *)self)->unk_00;
    output_data = output;
    switch (state) {
    case 0:
    {
        if ((((S_81934928_6 *)(((S_81934928_0 *)self)->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }
        {
            u8 *copy_page;
            *(Copy24 *)output_data = *(Copy24 *)&D_80083780;
            copy_page = (u8 *)&D_80083780;
            ((S_81934928_0 *)self)->unk_10.s = ((S_81934928_1 *)copy_page)->unk_02;
            ((S_81934928_0 *)self)->unk_12.s = ((S_81934928_1 *)copy_page)->unk_06;
            page_value = ((S_81934928_1 *)copy_page)->unk_0A;
        }
        ((S_81934928_0 *)self)->unk_0C.s = 0x3C;
        ((S_81934928_0 *)self)->unk_0A.u++;
        ((S_81934928_0 *)self)->unk_14 = page_value;
        func_800A56E0(0x300);
    }
        /* fallthrough */
    case 1:
    spawn_index = 0x3C - ((S_81934928_0 *)self)->unk_0C.u;
    if (spawn_index >= 8) {
        spawn_index = 8;
    }
    if (spawn_index >= 0) {
        do {
            particle = func_8003FD64(0x202, ((s32 *)(&D_80083498)));
            if (particle != NULL) {
                ((S_81934928_2 *)particle)->unk_10 = D_8002445C;
                func_8004491C(particle, D_80024740);
                search_origin = (u8 *)particle + 0x20;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_10.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0C = value;
                ((S_81934928_3 *)search_origin)->unk_1E = value;

                rand_quotient = rand();
                random_value = rand_quotient;
                origin_component = ((S_81934928_0 *)self)->unk_12.u;
                rand_quotient = random_value / 512;
                value = origin_component + ((random_value % 512)) - 0x100;
                if (value < 0) {
                    value = 0;
                }
                ((S_81934928_3 *)search_origin)->unk_0E = value;
                ((S_81934928_3 *)search_origin)->unk_22 = value;

                value = ((S_81934928_0 *)self)->unk_14 - 0x100;
                ((S_81934928_3 *)search_origin)->unk_10 = value;
                ((S_81934928_3 *)search_origin)->unk_26 = value;
                ((S_81934928_2 *)particle)->unk_20 = self;
            }
            spawn_index--;
        } while (spawn_index >= 0);
    }

    if (((S_81934928_0 *)self)->unk_0C.u == 0x1E) {
        target = (void *)D_800814A8;
        if (target != NULL) {
            void *lookup_origin = target;
            while ((target = func_800A3F28(D_80082E80.tileX, D_80082E80.tileY, lookup_origin, target)) != NULL) {
                if ((((S_81934928_4 *)target)->unk_1C & 0x2000) == 0) {
                    copy_src = (Copy24 *)(u32)((S_81934928_0 *)self)->unk_09;
                    func_8009CE1C(target, 0x20, (s32)copy_src, 0xA,
                                  ((S_81934928_5 *)effect)->unk_2A, effect, 2);
                }
                func_80024004(target);
            }
        }
    }

    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    ((S_81934928_0 *)self)->unk_0C.s = 8;
    ((S_81934928_0 *)self)->unk_0A.u = 0xFF;
    return;

    case 0xFF:
    countdown = ((S_81934928_0 *)self)->unk_0C.s - 1;
    ((S_81934928_0 *)self)->unk_0C.s = countdown;
    if (countdown > 0) {
        return;
    }
    {
        u16 effect_flags;
        value = ((S_81934928_0 *)self)->unk_0E.s;
        effect_flags = ((S_81934928_0 *)self)->unk_0E.u;
        if ((value & 0x8000) != 0) {
            value = effect_flags & 0x7FFF;
            ((S_81934928_0 *)self)->unk_0E.u = value;
            return;
        }
    }
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)self + -2)) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;

        return;
    default:
        return;
    }
}
