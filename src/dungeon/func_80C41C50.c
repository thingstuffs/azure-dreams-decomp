#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173450_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173450_0;   /* arg0 in func_80173450 */


typedef struct S_80173450_2 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173450_2;   /* arg2 in func_80173450 */

typedef struct S_80173450_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80173450_3;   /* global in func_80173450 */



extern s32 D_800814A0;
extern s32 D_80083460;
extern u8 D_8008346A;

void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);

/* Fade the entity sprite, then remove the entity and update its tile flags. */
void func_80173450(void *action, void *unused, void *sprite, void *entity)
{
    s32 state;
    s32 entity_flags;
    u16 fade_delay;
    s32 *entity_globals;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;

    state = ((S_80173450_0 *)action)->unk_9B;
    if (state == 1) {
        goto process;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto end;

state_ge_2:
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto update;
    }
    goto end;

state_zero:
    if (*(s16 *)&D_8008346A != 0) {
        goto end;
    }
    ((S_80173450_0 *)action)->unk_9B = 1;

process:
    entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_s32.v;
    if (entity_flags & 0x4000) {
        if (!(entity_flags & 0x20000000)) {
            func_800ACF88(entity);
        }
    }
    func_800A56E0(0x805);
    ((S_80173450_0 *)action)->unk_96 = 4;
    ((S_80173450_0 *)action)->unk_9B++;
    ((S_80173450_2 *)sprite)->unk_12 -= 0x80;

update:
    ((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v |= 0x10000000;
    fade_delay = ((S_80173450_0 *)action)->unk_96 - 1;
    ((S_80173450_0 *)action)->unk_96 = fade_delay;
    if ((s16)fade_delay <= 0) {
        if (((S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            ((S_80173450_2 *)sprite)->unk_0C.s32 += 0xFFEFEFF0;
        }
        ((S_80173450_2 *)sprite)->unk_10 = 0x20;
        ((S_80173450_2 *)sprite)->unk_14 |= 0xC;
    } else {
        ((S_80173450_2 *)sprite)->unk_0C.s32 = 0x808080;
    }

    if (!(((S_80173450_2 *)sprite)->unk_14 & 0x8000)) {
        if (((S_80173450_2 *)sprite)->unk_0C.u8 >= 0x10) {
            goto end;
        }
    }

    entity_globals = &D_80083460;
    tracked_entity = ((S_80173450_3 *)entity_globals)->unk_10;
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        ((S_80173450_3 *)entity_globals)->unk_10 = tracked_entity & 0x7FFFFFFF;
    }
    func_800A2FE0(entity);
    func_800A32A4(entity);

    tile_x = ((S_80173450_2 *)sprite)->unk_24;
    tile_y = ((S_80173450_2 *)sprite)->unk_25;
    tile_mask = 0x3000;
    if (((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(tile_x, tile_y, tile_mask);
    func_8009A028(entity);
    (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}
