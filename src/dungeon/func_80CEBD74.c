#include "common.h"

typedef struct S_80175574_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80175574_0;   /* arg0 in func_80175574 */

typedef struct S_80175574_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    void * unk_2C;
} S_80175574_1;   /* arg2 in func_80175574 */

typedef struct S_80175574_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175574_2;   /* counter_base in func_80175574 */

typedef struct S_80175574_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x1B];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80175574_3;   /* arg3 in func_80175574 */

typedef struct S_80175574_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80175574_4;   /* D_800814A8 in func_80175574 */



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

void func_80175574(Obj0 *arg0, void *arg1, Obj2 *arg2, Obj3 *arg3)
{
    register Obj0 *p0 ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *p1;
    Obj2 *p2;
    register Obj3 *p3 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    s32 kind;
    unsigned long table_index;
    register u8 *counter_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    ASM_KEEP_NV(p2);   /* MATCH pin: load-bearing for the whole function shape */
    p3 = arg3;
#ifndef __mips__
#endif
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    switch (((S_80175574_0 *)arg0)->unk_9B) {
    case 0:
        if (!(((S_80175574_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A--;
        }
        {
            register u8 *table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

            switch (((S_80175574_3 *)arg3)->unk_48) {
            default:
                goto increment_state;
            case 13:
                table = D_80175E54;
                break;
            case 14:
                table = D_80175E5C;
                break;
            case 15:
                table = D_80175E64;
                break;
            }
            (*(void * *)((u8 *)arg2 + 0x2C)) = table;
            table_index = ((D_80083228 + ((S_80175574_3 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            table_index += (unsigned long)table;
            func_80047784(arg2,
                *(u8 *)table_index,
                0);
        }
        goto increment_state;

    case 1:
        {
            u8 *table;
            void *current;

            switch (((S_80175574_3 *)arg3)->unk_48) {
            default:
                break;
            case 13:
                current = ((S_80175574_1 *)arg2)->unk_2C;
                table = D_80175E54;
                goto check_first_table;
            case 14:
                current = ((S_80175574_1 *)arg2)->unk_2C;
                table = D_80175E5C;
                goto check_first_table;
            case 15:
                current = ((S_80175574_1 *)arg2)->unk_2C;
                table = D_80175E64;
                goto check_first_table;
check_first_table:
                if (current != table) {
                    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                    table_index = ((D_80083228 + ((S_80175574_3 *)arg3)->unk_2A + 0x100) >> 9) & 7;
                    table_index += (unsigned long)table;
                    func_80047784(arg2,
                        *(u8 *)table_index,
                        0);
                }
                break;
            }
        }

        if (((S_80175574_3 *)arg3)->unk_25 != 0) {
            {
                register u8 *table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

                kind = ((S_80175574_3 *)arg3)->unk_48;
                if (kind == 14) {
                    goto early_second_table_14;
                }
                if (kind < 15) {
                    if (kind != 13) {
                        goto increment_counter;
                    }
                    goto early_second_table_13;
                } else {
                    goto check_second_kind_15;
                }
early_second_table_13:
                table = D_80175E64 + 8;
                goto second_table_call;
early_second_table_14:
                table = D_80175E6C + 8;
second_table_call:
                (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                table_index = ((D_80083228 + ((S_80175574_3 *)arg3)->unk_2A + 0x100) >> 9) & 7;
                table_index += (unsigned long)table;
                func_80047784(arg2,
                    *(u8 *)table_index,
                    0);
            }
            goto increment_counter;
        }
        if (D_80083462 & 0x1000) {
            return;
        }
        if (((S_80175574_3 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                return;
            }
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            return;
        }
        {
            s32 flags = ((S_80175574_3 *)arg3)->unk_1C;

            if (flags & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }
            if (flags & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_801759A0(arg0, arg1, arg2, arg3);
                return;
            }
        }
        if (((S_80175574_3 *)arg3)->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)((S_80175574_4 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }
        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (((S_80175574_3 *)arg3)->unk_25 == 0) {
            return;
        }

select_second_table:
        kind = ((S_80175574_3 *)arg3)->unk_48;
        {
            register u8 *table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

            if (kind == 14) {
                goto second_table_14;
            }
            if (kind < 15) {
                if (kind == 13) {
                    goto second_table_13;
                }
                goto increment_counter;
            }
check_second_kind_15:
            if (kind == 15) {
                goto second_table_15;
            }
            goto increment_counter;
second_table_13:
            table = D_80175E6C;
            goto selected_second_table;
second_table_14:
            table = D_80175E74;
            goto selected_second_table;
second_table_15:
            table = D_80175E7C;
selected_second_table:
            (*(void * *)((u8 *)arg2 + 0x2C)) = table;
            table_index = ((D_80083228 + ((S_80175574_3 *)arg3)->unk_2A + 0x100) >> 9) & 7;
            table_index += (unsigned long)table;
            func_80047784(arg2,
                *(u8 *)table_index,
                0);
        }

increment_counter:
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A++;
        }
increment_state:
        ((S_80175574_0 *)arg0)->unk_9B++;
        return;

    case 2:
        if (!(((S_80175574_1 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
        {
            counter_base = (u8 *)&D_80083460;

            ((S_80175574_2 *)counter_base)->unk_0A--;
        }
        ((S_80175574_0 *)arg0)->unk_8C = D_801724BC;
        return;

    default:
        return;
    }
}
