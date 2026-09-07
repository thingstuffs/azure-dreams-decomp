#include "common.h"

/* --- gcc 2.8.x translation unit (address-caching CSE; see PLAN.md multi-compiler finding) --- */

/* stores a0 into D_80082E60.field_4 and clears field_D and field_C */
struct S_80082E60 {
    char pad0[4];
    int field_4;
    char pad8[3];
    char field_B;
    char field_C;
    char field_D;
    char pad_E[0xA];
    char field_18;
};

extern struct S_80082E60 D_80082E60;

void func_80040A88(int a0) {
    struct S_80082E60 *p = &D_80082E60;

    p->field_4 = a0;
    p->field_D = 0;
    p->field_C = 0;
}

/* Stores four arguments into consecutive fields of the global struct D_8006CE34 */
extern struct {
    int f0;
    int f1;
    int f2;
    int f3;
} D_8006CE34;

void func_8003F540(int a0, int a1, int a2, int a3)
{
    struct { int f0; int f1; int f2; int f3; } *p = &D_8006CE34;
    p->f0 = a0;
    p->f1 = a1;
    p->f2 = a2;
    p->f3 = a3;
}

/* func_800410FC — gcc 2.8.1 */
/* Points D_800814E0 at D_80083C68 and clears the first word of D_80083C68 */
extern int D_80083C68[8];
extern void *D_800814E0;

void func_800410FC(void) {
    D_800814E0 = D_80083C68;
    D_80083C68[0] = 0;
}

/* func_8004D0C8 — gcc 2.8.1 */
/* Registers a struct/state pointer and a default callback function pointer into
   the global state table D_80083178 (stores at offsets 0xD8 and 0xB4). */

void func_8004D09C(void);

void func_8004D0C8(void *a0)
{
    D_80083178.ptr = a0;
    D_80083178.callback = func_8004D09C;
}

/* func_800419EC — gcc 2.8.1 */
/* Struct at D_80083CA8 (also referenced elsewhere as D_80083CAE at offset 6):
 * offset 0: int  (rate/quotient, decremented each tick by other code)
 * offset 4: int  (accumulator, used by func_80041900)
 * offset 6: short (aka D_80083CAE - value copied from a1)
 * offset 8: short (countdown counter, copied from a0)
 * Declared >8 bytes so hi/lo addressing is used. */
extern struct {
    int field0;
    short pad4;
    short field6;
    short field8;
} D_80083CA8;

void func_800419EC(unsigned short a0, unsigned int a1) {
    D_80083CA8.field8 = a0;
    D_80083CA8.field6 = a1;
    D_80083CA8.field0 = a1 / a0;
}

/* func_8004D110 — gcc 2.8.1 */
/* func_8004D110 -- gcc 2.8.1
 * Registers a pointer and the default callback func_8004D0E4 into the
 * global state table D_80083178 (stores at offsets 0xB8 and 0xB4). */

void func_8004D0E4(void);

void func_8004D110(void *a0)
{
    D_80083178.field_B8 = a0;
    D_80083178.callback = func_8004D0E4;
}

extern unsigned char D_8007382A[16];

/* Sets a global flag byte to 1 and returns 1. */
int func_8005A3E0(void) {
    unsigned char *p = &D_8007382A[0];
    int v = 1;
    *p = v;
    return v;
}

extern int D_800869B4[3];

typedef struct {
    char pad_00[0x20];
    int field_20;
    int field_24;
    char pad_28[0x50 - 0x28];
} Struct80085FA8;

extern Struct80085FA8 D_80085FA8[];

/* For each of the D_800869B4[0] active entries in D_80085FA8, set fields at
 * offset 0x20 and 0x24 to the given value (unused parameter is passed in $a0
 * but never read). */
void func_8005C818(int unused, int value) {
    unsigned int i;
    unsigned int count;

    if (D_800869B4[0] != 0) {
        i = 0;
        count = D_800869B4[0];
        do {
            D_80085FA8[i].field_24 = value;
            D_80085FA8[i].field_20 = value;
            i++;
        } while (i < count);
    }
}

/* --- wave-60 (gcc 2.8.1) --- */

typedef struct {
    u8 pad[0x18];
    s32 unk18;
    s32 unk1C;
} Struct_80050F74;

/* Stores arg1 into two fields (offsets 0x38, 0x3C from arg0) of the struct/sub-object at arg0+0x20 */
void func_80050F74(void *arg0, s32 arg1) {
    Struct_80050F74 *temp = (Struct_80050F74 *)((u8 *)arg0 + 0x20);
    temp->unk1C = arg1;
    temp->unk18 = arg1;
}

/* extern data: force %hi/%lo addressing (not $gp-relative) by giving it size > 8 bytes */
extern short D_800847F6[8];

/* summary: sets D_800847F6 to -1 (sentinel/disable flag) and returns -1 */
int func_800542AC(void) {
    short *p = &D_800847F6[0];
    int v;
    v = -1;
    *p = v;
    return v;
}

/* Reset four 16-bit fields (at byte offsets 0,4,8,0xC) of a global struct to -1 */
typedef struct {
    short a;
    short pad0;
    short b;
    short pad1;
    short c;
    short pad2;
    short d;
} D_80083D78_t;

extern D_80083D78_t D_80083D78;

void func_800499BC(void) {
    D_80083D78.a = -1;
    D_80083D78.b = -1;
    D_80083D78.c = -1;
    D_80083D78.d = -1;
}

/* D_8007359C: a pointer-sized global that (per the target's lui/lw access pattern) is
 * itself a pointer stored inside a larger (>8 byte) data object, forcing gcc to emit
 * a %hi/%lo access rather than a $gp-relative one. It points to an array of 0x14 (20)
 * byte structs; this function indexes that array and returns the word at offset 4. */

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
} Entry8007359C; /* size 0x14 */

/* declared as a small array (size > 8 bytes) purely to force hi/lo addressing for
 * element 0, matching the target's lui/lw access to the pointer value itself. */
extern Entry8007359C *D_8007359C[4];

int func_8004AC18(int arg0)
{
    Entry8007359C *p = D_8007359C[0];
    return p[arg0].unk4;
}

/* Zero the first 0x200 bytes (128 words) of the D_80082EC0 array, counting down. */
extern int D_80082EC0[128];

void func_8003F7E4(void) {
    s32 i;

    for (i = 0x7F; i >= 0; i--) {
        D_80082EC0[i] = 0;
    }
}

/* --- v6 (LEAD 1: maspsx un-fills jr-delay sp-restore at 2+ callee-saved) --- */
typedef struct { short unk0, unk2, flags4, id6; } D8Elem;
extern D8Elem D_80083D08[6];
extern int func_80047BC0(short);

struct Target_827C { char pad[0x28]; void *entry; };
struct Source_827C { char pad[0xC]; struct Target_827C *target; };

struct Source_827C *func_8004827C(struct Source_827C *a0, short a1) {
    a0->target->entry = &D_80083D08[func_80047BC0(a1)];
    return a0;
}

/* --- v6 (maspsx LEAD 2 %lo-fold) --- */
/* Zeroes both shorts of D_80013564[func_8004A6C0()] when the index < 0x14.
   (maspsx LEAD 2 folds %lo into the two stores; retail keeps one %hi base.) */
extern struct { short a, b; } D_80013564[];
extern int func_8004A6C0(void);

void func_8004A8D8(void)
{
    int i = func_8004A6C0();
    if (i < 0x14) {
        D_80013564[i].a = 0;
        D_80013564[i].b = 0;
    }
}


/* shared D_80084960 table (0x9C stride) */
typedef struct {
    int unk00; int unk04; char pad08[4]; int unk0C;
    char pad10[0xC]; int unk1C; char pad20[0x9C-0x20];
} Entry80084960;
extern Entry80084960 D_80084960[];

extern void func_80040BB4(void);

/* Copies D_80082E60.field_B into D_80082E60.field_18, then invokes func_80040BB4. */
void func_80040B88(void)
{
    D_80082E60.field_18 = D_80082E60.field_B;
    func_80040BB4();
}

extern u8 D_80080B18[16];
extern u8 D_80080B1B;
extern u8 D_80080B1C;

/* Stashes two derived byte counters from arg1 into small globals, then indexes
   a fixed byte table (D_80080B18) by arg0 and returns the looked-up byte. */
u8 func_80048DA0(s32 arg0, s32 arg1)
{
    u8 *p;

    D_80080B1B = arg1 + 5;
    p = D_80080B18;
    D_80080B1C = (arg1 * 2) + 5;
    return p[arg0];
}

extern char D_8006ADC0[16]; /* >8B forces hi/lo addressing (pointer stored at offset 0) */
extern char D_800812C8[16]; /* >8B forces hi/lo addressing (address-of target) */

extern void func_80053C6C(void);

/* Stashes the address of D_800812C8 into D_8006ADC0 (as a pointer slot at its
 * start), then calls func_80053C6C(). The store lands in the jal delay slot
 * (maspsx delay-slot-store idiom fires before jal too, not just before jr/j). */
void func_80053CA4(void)
{
    char **dst = (char **)D_8006ADC0;
    *dst = D_800812C8;
    func_80053C6C();
}

/* Ring buffer of 32 history entries, each 0x18 (24) bytes; only offset 0 is
 * accessed here so the rest of the layout is left as padding. */
typedef struct {
    u8 unk00;
    u8 pad[0x17];
} Struct80083968;

extern u8 D_800814D0;
extern Struct80083968 D_80083968[32];

/* Returns the tag/type byte of the history entry immediately BEFORE the
 * current ring-buffer head (D_800814D0), wrapping mod 32. */
u8 func_8003F240(void) {
    return D_80083968[(D_800814D0 + 0x1F) & 0x1F].unk00;
}

/* Resets D_8007382B to 0, then calls two initialization/reset routines with arg 0. */
extern unsigned char D_8007382B[9];

extern void func_8005D88C(int arg0);
extern void func_8005E450(int arg0);

void func_8005B348(void)
{
    D_8007382B[0] = 0;
    func_8005D88C(0);
    func_8005E450(0);
}

/* Struct array entry accessor: returns the 32-bit field at offset 0x4
 * of D_80084960[a1] (element size 0x9C / 156 bytes). a0 is unused. */

int func_8005C8B8(int a0, short a1)
{
    return D_80084960[a1].unk04;
}

/* Entry struct in the D_80084960 table is 0x9C (156) bytes; this getter
 * returns the 32-bit field at offset 0x1C for entry index a1. */
int func_8005C918(int a0, short a1) {
    return D_80084960[a1].unk1C;
}

/* D_80084960 is an array of structs, each 0x9C (156) bytes; offset 0x1C
   holds a 32-bit field (getter func_8005C918 does a plain lw from +0x1C). */
typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[0x9C - 0x1C - 4];
} EntryStruct; /* size 0x9C */

/* Sets D_80084960[index].unk1C = value & 0x7F. First argument is unused. */
void func_8005C94C(s32 unused, s16 index, s32 value) {
    D_80084960[index].unk1C = value & 0x7F;
}

/* D_8006ADBC is a 3-word global; splat separately names word[1] as
   D_8006ADC0 elsewhere, but this function addresses it via D_8006ADBC+4
   directly (single base materialised, +4 literal offset), so treat it here
   as one >8B struct so gcc emits %hi/%lo (not $gp-rel). */
typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
} StructADBC;

extern StructADBC D_8006ADBC;

extern void func_80053C3C(s32 a0);

/* Read D_8006ADBC.field4, mirror it into field0, and if nonzero forward it
   to func_80053C3C. */
void func_80053C6C(void) {
    s32 a0 = D_8006ADBC.field4;

    D_8006ADBC.field0 = a0;
    if (a0 != 0) {
        func_80053C3C(a0);
    }
}
