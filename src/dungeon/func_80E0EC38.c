#include "common.h"

typedef struct S_80172438_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_80172438_0;   /* arg3 in func_80172438 */

typedef struct S_80172438_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172438_1;   /* arg2 in func_80172438 */

typedef struct S_80172438_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x16];
    u16 unk_B2;
} S_80172438_2;   /* arg0 in func_80172438 */



extern s32 func_800A44E0(s32, s32, s16, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_8009B4B0(void *, u16, u16);
extern s32 func_800A2CB8(void *);
extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, void *, s32, s32);
extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801764A0[];

/* Searches up to four tiles ahead for a target and starts the actor's action. */
s32 func_80172438(void *action_state, void *action_context, void *sprite, void *actor) {
    s32 attempt;
    s32 tile_x;
    s32 tile_y;
    s32 direction;
    s32 step_offset;
    s32 next_x;
    s32 next_y;
    u16 call_direction;
    s16 *x_step;
    s16 *y_step;
    s16 floor_height;
    register s32 target ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

    ((S_80172438_0 *)actor)->unk_71 &= 0x7F;
    if (D_80083462 & 0x2000) {
        return -1;
    }

    attempt = 0;
    direction = ((u16)((S_80172438_0 *)actor)->unk_2A.s >> 9) & 7;
    step_offset = direction << 1;
    tile_x = ((S_80172438_1 *)sprite)->unk_24;
    tile_y = ((S_80172438_1 *)sprite)->unk_25;
    x_step = (s16 *)((u8 *)&D_8006CCD8 + step_offset);
    ((S_80172438_2 *)action_state)->unk_B2 = 0;
    call_direction = direction;

    do {
        s32 try_x = (s16)tile_x;
        s32 try_y = (s16)tile_y;
        s32 floor_x;
        s32 floor_y;
        register s16 *y_steps ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

        ((S_80172438_2 *)action_state)->unk_B2++;
        if ((func_800A44E0((try_x << 6) & 0xFFC0,
                           (try_y << 6) & 0xFFC0,
                           ((S_80172438_0 *)actor)->unk_88.s, call_direction << 9)
             << 16) != 0) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 2;
        }

        y_steps = (s16 *)&D_8006CCE8;
        floor_x = (((try_x + *x_step) << 6) + 0x20) & 0xFFE0;
        y_step = (s16 *)(step_offset + (u8 *)y_steps);
        floor_y = (((try_y + *y_step) << 6) + 0x20) & 0xFFE0;
        floor_height = func_800BCB04(floor_x,
                              floor_y,
                              (s16)(((S_80172438_0 *)actor)->unk_88.u - 0x20));
        if (floor_height >= 0x201) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }
        if ((u16)(floor_height - ((S_80172438_0 *)actor)->unk_88.u + 0x3F) >= 0x7F) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }

        next_x = tile_x + *(u16 *)x_step;
        next_y = tile_y + *(u16 *)y_step;
        target = func_8009B4B0(actor, (u16)next_x, (u16)next_y);
        ((S_80172438_0 *)actor)->unk_60 = target;
        if (target != 0) {
            break;
        }

        attempt++;
        tile_x += *(u16 *)x_step;
        tile_y += *(u16 *)y_step;
    } while (attempt < 4);

    if (attempt >= 4) {
        return 3;
    }
    if ((func_800A2CB8(actor) << 16) == 0) {
        return 0;
    }
    if (D_80083462 & 0x2000) {
        return -1;
    }
    if (!(((S_80172438_0 *)actor)->unk_46 & 0x8000) && (D_80083462 & 8)) {
        return -1;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    ((S_80172438_2 *)action_state)->unk_9B = 0;
    ((S_80172438_2 *)action_state)->unk_8C = 0;
    ((S_80172438_2 *)action_state)->unk_9A = 0x17;
    (*(void * *)((u8 *)sprite + 0x2C)) = D_801764A0;
    func_80047784(sprite,
                  D_801764A0[((D_80083228 + ((S_80172438_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
                  0);
    func_800A4ACC(actor);
    ((S_80172438_0 *)actor)->unk_6D--;
    return 1;
}
