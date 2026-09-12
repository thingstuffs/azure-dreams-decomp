#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C90_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172C90_0;   /* arg3 in func_80172C90 */

typedef struct S_80172C90_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
} S_80172C90_1;   /* arg0 in func_80172C90 */

typedef struct S_80172C90_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_14;   /* accessed as both */
} S_80172C90_2;   /* arg1 in func_80172C90 */

typedef struct S_80172C90_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172C90_3_pre;   /* the 0x14 bytes before localOwner in func_80172C90, addressed as localOwner[-1] */

typedef struct S_80172C90_3 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80172C90_3;   /* localOwner in func_80172C90 */

typedef struct S_80172C90_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172C90_4;   /* localLinked in func_80172C90 */


typedef struct S_80172C90_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172C90_6;   /* counter in func_80172C90 */



typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} LookupEntry;

extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800A56E0(s32);
extern void func_800DB2DC(void *, void *, void *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LookupEntry D_8006DE24[];
extern void *D_800814A8[];
extern s16 D_80083228[5];
extern u8 D_80083460[];
extern s32 D_8008346C[3];
extern u8 D_80170838[0x44];
extern u8 D_80170880[0x1C];
extern u8 D_801710F4[];
extern u8 D_80174EF8[];
extern u8 D_80174F00[];

/* Updates the actor action sequence, including movement, landing, and recovery. */
void func_80172C90(void *action, S_80172C90_2 *motion, Rec_D_80082E80 *sprite, void *actor)
{
    u32 dir_offset;
    u16 angle;
    s16 *dir_x_table;
    s32 dir_x;
    s32 dir_y;
    u16 timer;
    u32 state;
    register u8 *selector ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 special;
    s32 tail_state; /* MATCH: the shared state store receives its value in v0. */
    u16 position[3];
    static void *const dispatch_labels[] = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L16,
        &&I1, &&I2, &&I3, &&I4, &&I5, &&I6, &&I7
    };

    ASM_KEEP_DEP_NV(special, actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    dir_x_table = D_8006CCD8;
    angle = ((S_80172C90_0 *)actor)->unk_2A.s;
    dir_offset = angle >> 8;
    ASM_USE2_NV(angle, special);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    dir_offset &= 0xE;
    dir_x = *(s16 *)((u8 *)dir_x_table + dir_offset);
    dir_y = *(s16 *)((u8 *)D_8006CCE8 + dir_offset);
    timer = ((S_80172C90_1 *)action)->unk_96.s;
    state = ((S_80172C90_1 *)action)->unk_9B;
    ((S_80172C90_1 *)action)->unk_96.s = timer - 1;
    special = 0;
    if ((u32)state >= 17U) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    ((S_80172C90_1 *)action)->unk_AC.s = motion->unk_0A.s;
    if (((S_80172C90_0 *)actor)->unk_1C & 0x2000) {
        u16 action_kind;
        u32 action_index;

        action_kind = ((S_80172C90_0 *)actor)->unk_46 & 0x3FFF;
        action_index = action_kind - 1;
        if (action_index >= 7U) {
            goto I4;
        }
        goto *(((void **)D_80170880)[action_index]);
    }
    goto IDirect;

I7:
    special = 1;
    goto I3;
I6:
    special = 1;
    goto I2;
I5:
    special = 1;
    goto I1;

IDirect:
    {
    u16 action_kind;

    action_kind = ((S_80172C90_0 *)actor)->unk_46 & 0x3FFF;
    switch (action_kind) {
    case 1:
        goto I1;
    case 2:
        goto I2;
    case 3:
        goto I3;
    default:
        selector = 0;
        goto IEnd;
    }
    }

I3:
    selector = (u8 *)actor + 0xE;
    goto IEnd;
I2:
    selector = (u8 *)actor + 0xB;
    goto IEnd;
I1:
    selector = (u8 *)actor + 8;
    goto IEnd;
I4:
    selector = 0;

IEnd:
    if (*selector != 0) {
        void *owner;
        s32 use_owner;
        s32 move_result;

        ((S_80172C90_1 *)action)->unk_98 &= 0xFF7F;
        use_owner = special;
        ASM_KEEP_NV(use_owner);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (use_owner) {
            owner = D_800814A8[0];
            ((S_80172C90_0 *)actor)->unk_60 = owner;
            goto OwnerLinked;
        }
        if (D_8006DE24[*selector].type == 2) {
            owner = ((S_80172C90_0 *)actor)->unk_60;
            if (owner != 0) {
OwnerLinked:
                move_result = ((S_80172C90_3_pre *)owner)[-1].unk_00;
                ((S_80172C90_0 *)actor)->unk_72.s = ((S_80172C90_4 *)move_result)->unk_24;
                ((S_80172C90_0 *)actor)->unk_73.s = ((S_80172C90_4 *)move_result)->unk_25;
                goto OwnerDone;
            }
        } else {
            s32 delta_x;
            s32 delta_y;

            ((S_80172C90_0 *)actor)->unk_60 = func_800A05A4(actor,
                sprite->unk_24,
                sprite->unk_25,
                ((S_80172C90_0 *)actor)->unk_2A.u, 16);
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            delta_x = ((S_80172C90_0 *)actor)->unk_72.u;
            delta_y = ((S_80172C90_0 *)actor)->unk_73.u;
            if (delta_x < 0) {
                delta_x = -delta_x;
            }
            if (delta_y < 0) {
                delta_y = -delta_y;
            }
            ((S_80172C90_0 *)actor)->unk_72.u = delta_x;
            ((S_80172C90_0 *)actor)->unk_73.u = delta_y;
OwnerDone:
            {
                void *linked_actor;

                linked_actor = actor;
            }
        }

        {
            void *move_actor;

            move_actor = actor;
            position[0] = motion->unk_02.s;
            position[1] = motion->unk_06.s;
            position[2] = motion->unk_0A.s;
            move_result = func_800A94A0(move_actor, selector, special,
                                      (u8 *)action + 0x98);
        }
        if (!move_result) {
            return;
        }
        sprite->unk_14.at00_u16.v &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DB2DC(motion, sprite, actor, 10);
        ((S_80172C90_1 *)action)->unk_90 = 0;
        ((S_80172C90_1 *)action)->unk_96.s = 2;
        ((S_80172C90_1 *)action)->unk_98 |= 8;
        {
            s32 back_x;
            s32 back_y;

            back_x = -dir_x;
            back_y = -dir_y;
            motion->unk_0C.s =
                (back_x << 18) + (back_x << 19);
            motion->unk_10.s =
                (back_y << 18) + (back_y << 19);
        }
        motion->unk_14.s = (s32)0xFFF30000;
        {
            tail_state = ((S_80172C90_1 *)action)->unk_9B;
            tail_state++;
            ((S_80172C90_1 *)action)->unk_9B = tail_state;
            return;
        }
    }

    motion->unk_14.s = 0;
    motion->unk_10.s = 0;
    motion->unk_0C.s = 0;
    func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
    {
        void *owner;

        owner = D_800814A8[0];
        D_8008346C[0] = 0;
        ((S_80172C90_3 *)owner)->unk_A6--;
    }
    func_800A4ACC(actor);
    ((S_80172C90_0 *)actor)->unk_6D.s--;
    ((S_80172C90_1 *)action)->unk_8C = D_801710F4;
    ((S_80172C90_0 *)actor)->unk_73.s = 0;
    ((S_80172C90_0 *)actor)->unk_72.s = 0;
    ((S_80172C90_0 *)actor)->unk_46 &= 0x7FFF;
    return;

L1:
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        ((S_80172C90_1 *)action)->unk_9B = 16;
        ((S_80172C90_1 *)action)->unk_98 |= 0x80;
        return;
    }
    if (((S_80172C90_1 *)action)->unk_96.u <= 0) {
        motion->unk_0C.u = 0;
        motion->unk_0C.s = dir_x << 18;
        motion->unk_10.u = 0;
        motion->unk_10.s = dir_y << 18;
        motion->unk_14.u = 0;
        motion->unk_14.s = (s32)0xFFF30000;
        {
            ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
            return;
        }
    }
    motion->unk_0C.s *= 2;
    motion->unk_10.s *= 2;
    return;

L2:
    if (func_8003F270()) {
        sprite->unk_14.at00_u16.v |= 0x0800;
        return;
    }
    sprite->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172C90_1 *)action)->unk_9B++;

L3:
    motion->unk_14.s += 0x30000;
    if (sprite->unk_04.as_s8 == 4) {
        if (sprite->unk_14.at00_u16.v & 0x1000) {
            goto L3Activate;
        }
    }
    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
L3Activate:
    {
        u16 tail_flags;
        register u8 tail_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        motion->unk_0C.s = dir_x << 19;
        motion->unk_10.s = dir_y << 19;
        tail_flags = ((S_80172C90_1 *)action)->unk_98;
        tail_state = ((S_80172C90_1 *)action)->unk_9B;
        tail_flags |= 0x80;
        goto UpdateFlags;

L4:
    motion->unk_14.s += 0x20000;
    if (((S_80172C90_0 *)actor)->unk_1C & 0x08000000) {
        if (motion->unk_0A.u <= ((S_80172C90_1 *)action)->unk_AC.u) {
            goto L4Activate;
        }
    }
    if (motion->unk_0A.u <= ((S_80172C90_1 *)action)->unk_AC.u) {
        return;
    }
L4Activate:
    {
    u8 *effect;

    motion->unk_14.s = 0;
    motion->unk_10.s = 0;
    motion->unk_0C.s = 0;
    ((S_80172C90_1 *)action)->unk_96.s = 4;
    sprite->unk_1C.at00_u16.v = 0x1400;
    sprite->unk_1C.at02_u16.v = 0x0C00;
    effect = D_80174F00;
    sprite->unk_2C.as_pu8 = effect;
    func_80047784(sprite,
        effect[((D_80083228[0] + ((S_80172C90_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    tail_flags = ((S_80172C90_1 *)action)->unk_98;
    tail_state = ((S_80172C90_1 *)action)->unk_9B;
    tail_flags &= 0xFFF7;
UpdateFlags:
    tail_state++;
    ((S_80172C90_1 *)action)->unk_98 = tail_flags;
    ((S_80172C90_1 *)action)->unk_9B = tail_state;
    return;
    }
    }

L5:
    {
        s32 ticks;
        s32 ticks_squared;

        ticks = ((S_80172C90_1 *)action)->unk_96.u;
        ticks_squared = ticks * ticks;
        ASM_USE_NV(ticks);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        sprite->unk_1C.at00_u16.v = 0x1000 + ticks_squared * 300;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        sprite->unk_1C.at02_u16.v = 0x1000 - ticks_squared * 200;
    }
    if (((S_80172C90_1 *)action)->unk_96.u > 0) {
        return;
    }
    sprite->unk_2C.as_pu8 = D_80174EF8;
    func_80047784(sprite,
        D_80174EF8[((D_80083228[0] + ((S_80172C90_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    ((S_80172C90_1 *)action)->unk_96.s = 10;
    ((S_80172C90_1 *)action)->unk_9B = ((S_80172C90_1 *)action)->unk_9B + 1;
    return;

L6:
    {
        s32 tile_coord;
        s32 target_coord;
        s32 current_coord;

        tile_coord = sprite->unk_24;
        current_coord = motion->unk_02.u;
        target_coord = tile_coord << 6;
        ASM_USE_NV(target_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        current_coord -= 0x20;
        motion->unk_0C.s =
            (target_coord - current_coord) << 14;
    }
    {
        s32 tile_coord;
        s32 target_coord;
        s32 current_coord;

        tile_coord = sprite->unk_25;
        current_coord = motion->unk_06.u;
        target_coord = tile_coord << 6;
        ASM_USE_NV(target_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        current_coord -= 0x20;
        motion->unk_10.s =
            (target_coord - current_coord) << 14;
    }
    if (((S_80172C90_1 *)action)->unk_96.u > 0) {
        return;
    }
    motion->unk_14.s = 0;
    motion->unk_10.s = 0;
    motion->unk_0C.s = 0;
    sprite->unk_14.at00_u16.v |= 0x6000;
    ((S_80172C90_1 *)action)->unk_9B = 16;
    return;

L16:
    {
    u8 *counter;

    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    motion->unk_14.s = 0;
    motion->unk_10.s = 0;
    motion->unk_0C.s = 0;
    func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
    if (sprite->unk_2C.as_pu8 != D_80174F00) {
        sprite->unk_2C.as_pu8 = D_80174F00;
        func_80047784(sprite,
            D_80174F00[((D_80083228[0] + ((S_80172C90_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
            0);
    }
    counter = D_80083460;
    if (((S_80172C90_6 *)counter)->unk_0C != 0) {
        return;
    }
    ((S_80172C90_6 *)counter)->unk_0A--;
    sprite->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80172C90_1 *)action)->unk_8C = D_801710F4;
    func_800A4ACC(actor);
    if (((S_80172C90_0 *)actor)->unk_6D.u > 0) {
        ((S_80172C90_0 *)actor)->unk_6D.s--;
    }
    ((S_80172C90_0 *)actor)->unk_73.s = 0;
    ((S_80172C90_0 *)actor)->unk_72.s = 0;
    ((S_80172C90_0 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
    }
}
