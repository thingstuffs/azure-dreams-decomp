#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80175574_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80175574_0;   /* arg0 in func_80175574 */


typedef struct S_80175574_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175574_2;   /* counter_base in func_80175574 */





typedef struct {
    u8 pad00[0x8c];
    void *field8c;
    u8 pad90[0x0b];
    u8 state9b;
} Obj0;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0x16];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
    u8 pad49[0x1b];
    s16 value64;
    u8 pad66[7];
    s8 flag6d;
} Obj3;

extern void func_80047784(Obj2 *, u8, s32);
extern s32 func_8009A180(Obj3 *, void *);
extern s32 func_800A2C34(Obj3 *);
extern void func_800A9A04(Obj3 *);
extern void func_800A9A0C(Obj3 *);
extern void func_800AA258(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 func_800AA6B4(Obj0 *, void *, Obj2 *, s32);
extern void func_800AA888(Obj0 *, void *, Obj2 *, Obj3 *);
extern void func_801759A0(Obj0 *, void *, Obj2 *, Obj3 *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_801724BC[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern u8 D_80175E6C[];
extern u8 D_80175E74[];
extern u8 D_80175E7C[];

/* Updates the actor's directional animation and advances its action state. */
void func_80175574(Obj0 *controller_arg, void *context_arg, Obj2 *animation_arg, Obj3 *actor_arg)
{
    register Obj0 *controller ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *context;
    Obj2 *animation;
    Obj3 *actor;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 actor_kind;
    unsigned long table_entry;
    register u8 *counter_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    controller = controller_arg;
    context = context_arg;
    animation = animation_arg;
    ASM_KEEP_NV(animation);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    actor = actor_arg;
#ifndef __mips__
#endif

    switch (((S_80175574_0 *)controller)->unk_9B) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A--;
        }
        {

            switch (((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v) {
            default:
                goto increment_state;
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E54;
                table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E54;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E5C;
                table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E5C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E64;
                table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E64;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        }
        goto increment_state;

    case 1:
        {
            u8 *dir_table;
            void *current_table;

            switch (((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v) {
            default:
                break;
            case 13:
                current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
                dir_table = D_80175E54;
                goto check_first_table;
            case 14:
                current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
                dir_table = D_80175E5C;
                goto check_first_table;
            case 15:
                current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
                dir_table = D_80175E64;
                goto check_first_table;
check_first_table:
                if (current_table != dir_table) {
                    (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                    table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                    table_entry += (unsigned long)dir_table;
                    func_80047784(animation,
                        *(u8 *)table_entry,
                        0);
                }
                break;
            }
        }

        if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v != 0) {
            {
                register u8 *dir_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                actor_kind = ((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v;
                if (actor_kind == 14) {
                    goto early_second_table_14;
                }
                if (actor_kind < 15) {
                    if (actor_kind != 13) {
                        goto increment_counter;
                    }
                    goto early_second_table_13;
                } else {
                    goto check_second_kind_15;
                }
early_second_table_13:
                dir_table = D_80175E64 + 8;
                goto second_table_call;
early_second_table_14:
                dir_table = D_80175E6C + 8;
second_table_call:
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
            }
            goto increment_counter;
        }
        if (D_80083462 & 0x1000) {
            return;
        }
        if (((Rec_D_800E3D7C *)actor)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(controller, context, animation, 0) != 0) {
                return;
            }
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }
        {
            s32 actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;

            if (actor_flags & 0x100) {
                func_800AA258(controller, context, animation, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(controller, context, animation, actor);
                func_801759A0(controller, context, animation, actor);
                return;
            }
        }
        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
            return;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                return;
            }
        }
        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((Rec_D_800E3D7C *)actor)->unk_24.at01_u8.v == 0) {
            return;
        }

select_second_table:
        actor_kind = ((Rec_D_800E3D7C *)actor)->unk_48.at00_u8.v;
        {

            if (actor_kind == 14) {
                goto second_table_14;
            }
            if (actor_kind < 15) {
                if (actor_kind == 13) {
                    goto second_table_13;
                }
                goto increment_counter;
            }
check_second_kind_15:
            if (actor_kind == 15) {
                goto second_table_15;
            }
            goto increment_counter;
second_table_13:
            (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
            table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
            table_entry += (unsigned long)D_80175E6C;
            func_80047784(animation,
                *(u8 *)table_entry,
                0);
            goto increment_counter;
second_table_14:
            (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
            table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
            table_entry += (unsigned long)D_80175E74;
            func_80047784(animation,
                *(u8 *)table_entry,
                0);
            goto increment_counter;
second_table_15:
            (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
            table_entry = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
            table_entry += (unsigned long)D_80175E7C;
            func_80047784(animation,
                *(u8 *)table_entry,
                0);
        }

increment_counter:
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A++;
        }
increment_state:
        ((S_80175574_0 *)controller)->unk_9B++;
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A--;
        }
        ((S_80175574_0 *)controller)->unk_8C = D_801724BC;
        return;

    default:
        return;
    }
}
