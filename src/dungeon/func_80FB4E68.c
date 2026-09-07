#include "common.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80174668_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174668_0;   /* arg0 in func_80174668 */

typedef struct S_80174668_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80174668_1;   /* arg2 in func_80174668 */

typedef struct S_80174668_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * s; u8 * u; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80174668_2;   /* arg3 in func_80174668 */

typedef struct S_80174668_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174668_3;   /* arg1 in func_80174668 */

typedef struct S_80174668_4 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80174668_4;   /* tile in func_80174668 */

typedef struct S_80174668_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80174668_5;   /* alloc in func_80174668 */

typedef struct S_80174668_6 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x7];
    s16 unk_A2;
    s16 unk_A4;
    u16 unk_A6;
    u8 pad_A8[0x4];
    u32 unk_AC;
} S_80174668_6;   /* prim in func_80174668 */

typedef struct S_80174668_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174668_7;   /* state_object in func_80174668 */

typedef struct S_80174668_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80174668_8;   /* inner in func_80174668 */


typedef struct S_80174668_10 {
    s32 unk_00;
} S_80174668_10;   /* D_8008346C in func_80174668 */

typedef struct S_80174668_11_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80174668_11_pre;   /* the 0x14 bytes before ((S_80174668_2 *)arg3)->unk_60.u in func_80174668, addressed as ((S_80174668_2 *)arg3)->unk_60.u[-1] */

typedef struct S_80174668_12 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80174668_12;   /* ((S_80174668_5 *)alloc)->unk_08 in func_80174668 */



typedef struct {
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
} SpawnOffset;

typedef struct {
    s16 x;
    s16 y;
} Position2;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800AD594(void *, s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_800BCB04(u16, u16, s16);
extern void func_800C8CD8(void *, s32, s32);
extern void func_80174AD8(void) __attribute__((noreturn));
extern void func_80174AF0() __attribute__((noreturn));

extern u8 D_80045340[];
extern s16 D_80083228[];
extern u8 D_8008346C[];
extern u8 D_80083498[];
extern u8 D_800DEC50[];
extern u32 D_800E3DE8[];
extern u8 D_8017086C[];
extern u8 D_80170874[];
extern u8 D_80170F6C[];
extern u8 D_80174B20[];
extern u8 D_80174B98[];
extern u8 D_80175174[];
extern u8 D_80175258[];

void func_80174668(S_80174668_0 *arg0, S_80174668_3 *arg1, S_80174668_1 *arg2, void *arg3)
{
    SpawnOffset spawn = *(SpawnOffset *)D_8017086C;
    Position2 pos;
    s32 state;
    u8 *object;
    u8 *state_object;
    u8 *inner;
    u8 *alloc;
    u8 *table;
    u8 *prim;
    u8 *tile;
    void *template;
    s32 saved;
    s32 saved_first;
    s32 random;
    s32 value;
    s32 state_value;

    state = arg0->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    func_80174AF0();

state_0:
    object = func_800A05A4(arg3, arg2->unk_24,
        arg2->unk_25, ((S_80174668_2 *)arg3)->unk_2A, 0x10);
    ((S_80174668_2 *)arg3)->unk_60.s = object;
    table = D_80175258;
    arg2->unk_2C = table;
    func_80047784(arg2,
        table[((D_80083228[0] + ((S_80174668_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    if (arg2->unk_14 & 0x8000) {
        arg0->unk_9B = 2;
        func_80174AF0();
    }

    arg0->unk_9B = 1;
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    if (((S_80174668_2 *)arg3)->unk_60.s == 0) {
        goto done;
    }

    value = func_80099734(arg3, saved = func_800990FC());
    saved_first = saved;
    saved = value;
    value = func_80099194(D_80170874, saved);
    func_80099290(value);
    func_800A5720(saved_first);
    func_800A56E0(0x60A);

    tile = ((S_80174668_11_pre *)(((S_80174668_2 *)arg3)->unk_60.u))[-1].unk_00;
    ((S_80174668_2 *)arg3)->unk_72.s = ((S_80174668_4 *)tile)->unk_24;
    ((S_80174668_2 *)arg3)->unk_73.s = ((S_80174668_4 *)tile)->unk_25;
    pos.x = spawn.x + (spawn.dx >> 1);
    pos.y = spawn.y + (spawn.dy >> 1);
    func_800B8FC8(arg0, &spawn, &pos, 1, 0);

    alloc = func_8003FD64(0x201, D_80083498);
    if (alloc == 0) {
        goto done;
    }
    func_8004491C(alloc, D_80174B98);
    template = D_80174B20;
    ASM_KEEP(template);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_80174668_5 *)alloc)->unk_10 = template;
    prim = alloc + 0x20;
    ((S_80174668_6 *)prim)->unk_A2 = (arg2->unk_24 << 6) + 0x20;
    ((S_80174668_6 *)prim)->unk_A4 = (arg2->unk_25 << 6) + 0x20;
    {
        u32 color;
        s32 countdown;
        u16 arg1_value;
        color = 0x00808080;
        ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
        arg1_value = arg1->unk_0A;
        countdown = 0x3C;
        ((S_80174668_6 *)prim)->unk_AC = color;
        ((S_80174668_6 *)prim)->unk_96 = countdown;
        ((S_80174668_6 *)prim)->unk_A6 = arg1_value;
        arg0->unk_96.s = countdown;
        func_80174AF0(color);
    }

state_1:
    state_object = ((S_80174668_2 *)arg3)->unk_60.s;
    if ((state_object != 0) && (arg0->unk_96.s < 0x34)) {
        ((S_80174668_7 *)state_object)->unk_2A =
            (((S_80174668_7 *)state_object)->unk_2A + 0x200) & 0x3FFF;
        alloc = func_8003FD64(0x312, D_80083498);
        if (alloc == 0) {
            goto state_1_continue;
        }
            func_8004491C(alloc, D_80045340);
            prim = alloc + 0x20;
            tile = ((S_80174668_5 *)alloc)->unk_0C;
            ((S_80174668_5 *)alloc)->unk_10 = D_80175174;

            random = rand();
            {
                s32 coord = ((S_80174668_2 *)arg3)->unk_72.u;
                ((S_80174668_12 *)(((S_80174668_5 *)alloc)->unk_08))->unk_02 =
                    (coord << 6) + (random % 64);
            }
            random = rand();
            {
                s32 coord = ((S_80174668_2 *)arg3)->unk_73.u;
                ((S_80174668_12 *)(((S_80174668_5 *)alloc)->unk_08))->unk_06 =
                    (coord << 6) + (random % 64);
            }
            inner = ((S_80174668_5 *)alloc)->unk_08;
            state_value = func_800BCB04(((S_80174668_8 *)inner)->unk_02,
                ((S_80174668_8 *)inner)->unk_06, -0x400);
            {
                s32 final_random = rand();
                state_value -= final_random % 95;
                state_value -= 0x20;
            }
            ((S_80174668_12 *)(((S_80174668_5 *)alloc)->unk_08))->unk_0A = state_value;

            ((S_80174668_4 *)tile)->unk_1E = 0xC04;
            ((S_80174668_4 *)tile)->unk_1C = 0xC04;
            ((S_80174668_4 *)tile)->unk_10 = 0x60;
            ((S_80174668_4 *)tile)->unk_00 = D_800DEC50;
            ((S_80174668_4 *)tile)->unk_14 |= 0x0C;
            {
                u32 tile_word = ((Rec_D_80016000 *)D_800DEC50)->unk_04.at00_u32.v;
                ((S_80174668_4 *)tile)->unk_04 = 0;
                ((S_80174668_4 *)tile)->unk_05 = 0;
                ((S_80174668_4 *)tile)->unk_0C = 0x00208020;
                ((S_80174668_4 *)tile)->unk_08 = tile_word;
            }
            ((S_80174668_6 *)prim)->unk_9A = 0;
    }
state_1_continue:
    value = arg0->unk_96.u - 1;
    arg0->unk_96.u = value;
    if ((value << 16) > 0) {
        goto done;
    }
    arg0->unk_9B++;
    func_80174AF0();

state_2:
    if (!(arg2->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_80174668_2 *)arg3)->unk_73.s = 0;
    ((S_80174668_2 *)arg3)->unk_72.s = 0;
    func_800AD594(arg3, 0x800);
    {
        void *call_arg;
        call_arg = arg3;
        arg0->unk_8C = D_80170F6C;
        ((S_80174668_10 *)D_8008346C)->unk_00 = 0;
        func_800A4ACC(call_arg);
    }
    if (((S_80174668_2 *)arg3)->unk_6D == 0) {
        ((S_80174668_2 *)arg3)->unk_46 &= 0x7FFF;
        func_80174AD8();
    }
    D_800E3DE8[0] = (u32)((u8 *)arg3 - 0x20);

    object = ((S_80174668_2 *)arg3)->unk_60.u;
    if (object != 0) {
        func_800C8CD8(object, 0x28, 0x10);
    }

done:
    return;
}
