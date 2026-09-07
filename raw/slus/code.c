#include "common.h"


/* Globals accessed directly via %hi/%lo (not $gp small-data). Declared with a
 * size > -G (8) so gcc/as emit %hi/%lo rather than $gp-relative access; the
 * element type reflects the access width, the array length is provisional. */
extern int   D_80084130[3];
extern short D_80073828[5];
extern short D_80084778[5];
extern int   D_80086D4C[3];



void func_8003D56C(void) {
    InitCARD();
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}


void func_8003DB4C(int *p, int n) {
    while (n != 0) {
        *p = 0;
        n--;
        p++;
    }
}

void func_8003DB6C(int *a0, int *a1, int a2) {
    while (a2 != 0) {
        *a0 = *a1;
        a1++;
        a2--;
        a0++;
    }
}

struct Elem {
    unsigned char b0;
    unsigned char pad1;
    unsigned char pad2;
    unsigned char pad3;
    int f4;
};

struct Dst {
    struct Elem *f0;
    unsigned char f4;
    unsigned char f5;
    unsigned char pad6;
    unsigned char pad7;
    int f8;
    int fc;
    int f10;
    unsigned short f14;
};

void func_8003DB94(struct Dst *a0, struct Elem *a1, short a2) {
    a0->f0 = a1 + a2;
    a0->f4 = a2;
    a0->f5 = a1->b0;
    a0->f14 &= 0x9FFF;
    a0->f8 = a0->f0->f4;
}


void func_8003E12C(int *a0, int *a1)
{
    int t = *a0;
    *a0 = *a1;
    *a1 = t;
}

/* Set the byte pointed to by a0 to 1 (constant-value flag setter). */
void func_8003E140(unsigned char *a0)
{
    *a0 = 1;
}




int func_8003F52C(int a0)
{
    return a0;
}

/* returns the address of global D_8006CE34 (declared >8B so codegen uses %hi/%lo instead of $gp-relative) */
extern int D_8006CE34[4];

int *func_8003F534(void) {
    return D_8006CE34;
}


int func_8003F5D4(void)
{
    return D_800814C8;
}

void func_8003F5E0(int a0)
{
    D_800814C8 = a0;
}

void func_8003F5EC(void) {
    int i;
    for (i = 0x200; i > 0; i--) {
        VSync(0);
    }
}

/* Packs a0 (shifted into bits 31:23) with the low 23 bits of a1 into *a2, and stores a3 into *(a2+1) */
void func_8003F6D4(int a0, int a1, int *a2, int a3)
{
    a1 &= 0x7FFFFF;
    a0 <<= 23;
    a1 |= a0;
    a2[0] = a1;
    a2[1] = a3;
}

/* Push node a0 onto the freelist headed by D_80081490: read the old head,
   store a0 as the new freelist head, clear a0's field at offset 4, and
   link a0's field at offset 0 to the previous head. */

typedef struct {
    void *head;
    int pad1;
    int pad2;
} FreelistHead; /* real D_80081490 is >8B so hi/lo addressing is used */

void func_80040044(void *a0)
{
    void *v0;
    {
        extern void *D_80081490;
        v0 = D_80081490;
    }
    {
        extern FreelistHead D_80081490;
        D_80081490.head = a0;
    }
    *(int *)((char *)a0 + 4) = 0;
    *(void **)a0 = v0;
}

/* Linked-list node with a next pointer at offset 0x0 and a 16-bit flags/state
 * field at offset 0x1E. Iterates a global singly-linked list, OR-ing 0xC00
 * into that field of every node. */

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    Node *head;
    int pad[2];
} D_80081498;

void func_80040418(void)
{
    Node *v1 = D_80081498.head;

    if (v1 != 0) {
        do {
            v1->field_1E |= 0xC00;
            v1 = v1->next;
        } while (v1 != 0);
    }
}



/* Counts the number of leading non-NULL pointer-sized entries in an array,
 * where the array is considered empty (count 0) if the first entry is NULL.
 * Returns the index of the first NULL entry found while scanning forward. */
int func_80040F00(void **arr)
{
    int count;

    count = 0;
    if (arr[0] != 0) {
        do {
            arr++;
            count++;
        } while (*arr != 0);
    }
    return count;
}


/* Appends a value to an int list pointed by D_800814E0, advances the
   end pointer, and writes a zero sentinel/terminator after the new
   entry. */
extern int *D_800814E0;

void func_80041110(int a0)
{
    *D_800814E0 = a0;
    D_800814E0++;
    *D_800814E0 = 0;
}


short func_800422A8(unsigned int a0, unsigned int a1, unsigned short a2, unsigned short a3)
{
    unsigned int q = (a0 - a1) / a2;
    if (q >= a3) {
        return -1;
    }
    return (short)q;
}

/* extern decls: callees only need to match the args actually supplied here */
extern void func_800423C0(void *a0, short a1);
extern void func_80042984(void *a0);

/* Wrapper: reconfigure something at a0 with a truncated-to-s16 parameter,
 * then run a follow-up update pass on the same object. */
void func_800424E0(void *a0, int a1)
{
    func_800423C0(a0, (short)a1);
    func_80042984(a0);
}




/* Variadic stub: gcc 2.7.2's o32 varargs prologue unconditionally spills
 * all four incoming register arguments (a0-a3) into the caller's argument
 * save area because of the trailing `...`, even though none are read; the
 * body itself just returns 0. */
s32 func_80043FB8(s32 arg0, ...)
{
    return 0;
}


/* Forwards its 4 incoming args to func_8003F540, then invokes func_80053DA8
   with a fixed flag value (0x300). Return value of neither call is used. */
extern void func_8003F540(int a0, int a1, int a2, int a3);
extern short func_80053DA8(int a0);

void func_80044234(int a0, int a1, int a2, int a3)
{
    func_8003F540(a0, a1, a2, a3);
    func_80053DA8(0x300);
}


/* Compute a modified game-time / clock-tick style value: masks the low 24 bits of one word from the D_8006CE34 status block, subtracts 0x20, and adds an adjacent word. */
extern int *func_8003F534(void);

int func_800445E0(void)
{
    int *p = func_8003F534();
    int v1 = p[2] & 0xFFFFFF;
    v1 = v1 - 0x20;
    return v1 + p[1];
}




/* Walks a linked list of Node46398 structs starting at *a2, calling func_800463EC(cur, a1, node, node->field6) for each, then advancing via node->field8/fieldC (next a1/a2) and a node-relative back-pointer at s0-8 until it is NULL; returns 0. */
extern void func_800463EC(void *a0, int a1, void *a2, short a3);

typedef struct Node46398 {
    char pad0[6];
    short field6;
    int field8;
    void *fieldC;
} Node46398;

int func_80046398(void *a0, int a1, void *a2)
{
    void *s0 = a0;
    Node46398 *n;

    do {
        n = (Node46398 *)a2;
        func_800463EC(s0, a1, a2, n->field6);
        a2 = *(void **)((char *)s0 - 8);
        s0 = (char *)a2 + 0x20;
        if (a2 == 0)
            break;
        n = (Node46398 *)a2;
        a1 = n->field8;
        a2 = n->fieldC;
    } while (1);

    return 0;
}


/* Calls func_80044BB0 and returns its result sign-extended from 16 bits. */
extern int func_80044BB0(void);

short func_80047714(void)
{
    return (short)func_80044BB0();
}


extern void func_800477F4(void *arg0);
extern void func_80047694(void *arg0);

/* Runs two per-entity update steps back to back on the same entity pointer. */
void func_800478B8(void *arg0)
{
    func_800477F4(arg0);
    func_80047694(arg0);
}


/* Zero the 0x30-byte struct/array at D_80083D08 (init/reset routine). */
extern void bzero(void *dst, int n);
extern unsigned char D_80083D08[0x30];

void func_800479AC(void)
{
    bzero(D_80083D08, 0x30);
}


/* Element size is 0xD000 (53248) bytes; base array of these structs lives at D_800FC000. */
typedef struct {
    u8 unk[0xD000];
} Struct_800FC000;

extern Struct_800FC000 D_800FC000[];

/* Returns a pointer to the a0'th element of the D_800FC000 struct array (element size 0xD000). */
void *func_80047A44(s32 a0)
{
    return &D_800FC000[a0];
}


int func_80047AA4(int a0)
{
    return a0 + 0x8000;
}

/* Element size is 0xD000 (53248) bytes; base array_47C60 of these structs lives at D_800FC000. */

extern Struct_800FC000 D_800FC000[];

/* Given a raw address, compute its index into the D_800FC000 struct array_47C60 (element size 0xD000)
 * via plain integer division (not pointer arithmetic) so the compiler emits a full truncating
 * division rather than the exact-division-by-constant shortcut used for real pointer subtraction. */
s32 func_80047C60(void *a0)
{
    return ((s32)a0 - (s32)D_800FC000) / 0xD000;
}


/* Sets bit 0x400 in the struct's 0x14 halfword flags field, then forwards to
 * func_80047784 with the (short-truncated) a1/a2 arguments. */

typedef struct {
    unsigned char pad[0x14];
    unsigned short unk14;
} Struct_80048374;

extern void func_80047784(Struct_80048374 *a0, short a1, short a2);

void func_80048374(Struct_80048374 *a0, short a1, short a2) {
    a0->unk14 |= 0x400;
    func_80047784(a0, a1, a2);
}


/* wrapper: calls func_80048500(a0, 0) */
extern int func_80048500(short a0, int a1);

void func_80048568(short a0)
{
    func_80048500(a0, 0);
}


/* Thin wrapper: sign-extends its 16-bit argument and forwards it to func_80048500
 * along with a fixed table index of 1; passes the callee's return value through. */
extern int func_80048500(short a0, int a1);

int func_80048590(short a0)
{
    return func_80048500(a0, 1);
}


/* wrapper: calls func_80048500(a0, 2) */
extern int func_80048500(short a0, int a1);

void func_800485B8(short a0)
{
    func_80048500(a0, 2);
}


/* Calls func_80048C3C(0) and returns its result */
extern int func_80048C3C(int a0);

int func_80048D00(void)
{
    return func_80048C3C(0);
}

/* Calls func_80048C3C(1) and returns its result. */
extern int func_80048C3C(int a0);

int func_80048D20(void)
{
    return func_80048C3C(1);
}

/* Calls func_80048C3C(2) and returns its result */
extern int func_80048C3C(int);

int func_80048D40(void)
{
    return func_80048C3C(2);
}

/* Returns the a0-th element of the D_80071250 volatile int array */

int func_80048DCC(int a0)
{
    return D_80071250[a0];
}

unsigned char func_80048DE8(int arg0) {
    volatile unsigned char *p = D_80071298;
    return p[arg0];
}

/* Counts leading non-NULL entries in a pointer array, up to a1 entries. */
s32 func_80048F8C(s32 *a0, s32 a1)
{
    s32 v1 = 0;

    if (a1 > 0) {
        do {
            if (*a0 == 0) {
                break;
            }
            v1++;
            a0++;
        } while (v1 < a1);
    }
    return v1;
}


/* Walk a singly-linked list (next pointer at offset 0xC) to its tail node,
 * then append a1 onto the tail's next pointer. */

typedef struct Struct_C_next Struct_C_next;
struct Struct_C_next {
    unsigned char pad[0xC];
    Struct_C_next *next;
};

void func_80049250(Struct_C_next *a0, Struct_C_next *a1) {
    while (a0->next != 0) {
        a0 = a0->next;
    }
    a0->next = a1;
}


int func_80049280(int a0)
{
    return a0 == 0x14;
}

/* Wrapper: extracts a 5-bit field from byte offset 3 of the input struct and
 * forwards it to func_80049280 (which just tests the value against 0x14). */
extern int func_80049280(int arg0);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Struct8004928C;

int func_8004928C(Struct8004928C *arg0)
{
    return func_80049280(arg0->unk3 & 0x1F);
}


/* extern decls */
extern int D_800713FC[4]; /* >8B forces hi/lo addressing (matches target's lui/addiu) */

extern int func_80049374(void *a0, int *a1);

/* Trivial wrapper: forwards a0 unchanged, appends &D_800713FC as second arg,
 * tail-calls func_80049374 and returns its result untouched. */
int func_80049490(void *a0) {
    return func_80049374(a0, D_800713FC);
}


/* extern: some status/flags query, bit 0x400 tested by caller */
extern int func_80042A80(void);

/* Returns bit 0x400 of func_80042A80()'s result (masked flag check). */
int func_800494FC(void) {
    return func_80042A80() & 0x400;
}


/* Maps a bitmask (bit0/bit1/bit2) to a priority code: bit0->0, bit1->1, bit2->2, none->3 */
int func_80049944(int a0) {
    int v1 = 3;

    if (a0 & 1) {
        v1 = 0;
    } else if (a0 & 2) {
        v1 = 1;
    } else if (a0 & 4) {
        v1 = 2;
    }

    return v1;
}

/* extern decls */

/* Maps a bitmask (bit0/bit1/bit2) to a priority code: bit0->0, bit1->1, bit2->2, none->3 */
extern int func_80049944(int a0);

typedef struct {
    unsigned char pad[0x13];
    unsigned char unk13;
    int unk14;
} Struct80049984;

/* If unk13 flag is set, look up priority code for the bitmask at unk14 via
 * func_80049944; otherwise default to 3 (no priority). */
int func_80049984(Struct80049984 *a0)
{
    int v1 = 3;

    if (a0->unk13 != 0) {
        v1 = func_80049944(a0->unk14);
    }

    return v1;
}


int func_800499DC(int *a0)
{
    *a0 = 1;
    return 1;
}


/* Trivial wrapper that forwards to func_80049CF4 with no arguments. */
extern void func_80049CF4(void);

void func_80049DC8(void)
{
    func_80049CF4();
}


/* Wrap an index by a single step of delta within [0, limit): given a current
 * index (a0), a signed step delta (a1), and a size/limit (a2), add the delta
 * and correct for at most one wraparound in either direction (assumes
 * |delta| <= limit). Used for circular-buffer/ring-index style advancement. */
int func_80049DE8(int a0, int a1, int a2) {
    a0 = a0 + a1;
    if (a1 > 0) {
        if (a0 < a2) {
        } else {
            a0 = a0 - a2;
        }
    } else {
        a0 = (a0 >= 0) ? a0 : (a2 + a0);
    }
    return a0;
}


/* Returns the int value stored at index a0 in global array D_800712B4 */

int func_80049E6C(int a0)
{
    volatile int *p = D_800712B4;
    return p[a0];
}

/* stub for callee — only argument setup / call site matters for this wrapper */
extern int func_800438E4(void *a1);

/* Trivial wrapper: forwards a1 to func_800438E4 and returns its result untouched */
int func_8004A4C4(void *a0, void *a1) {
    return func_800438E4(a1);
}


/* Returns the computed item value, or the callback's result when one runs. */
extern s32 func_8004A574(u8 *item, s32 flag);

/* Trivial wrapper: forwards its argument to func_8004A574 with a fixed flag=1 */
s32 func_8004A618(void *arg0)
{
    return func_8004A574(arg0, 1);
}

/* Trivial wrapper: forwards its item pointer to func_8004A574 with flag=0. */
s32 func_8004A638(void *item)
{
    return func_8004A574(item, 0);
}


/* func_8004A918: zero-fill the 0x50-byte (20-entry) table at fixed address
 * 0x80013564 (an array of {short,short} entries used elsewhere as D_80013564/
 * D_80013566 via %hi/%lo folded loads/stores). Original source referenced the
 * address as a raw integer literal cast (not a named extern) -- confirmed by
 * gcc emitting `lui;ori` (generic 32-bit constant synthesis) here, matching
 * the retail bytes exactly, whereas a symbolic `&D_80013564` always compiles
 * to `lui;addiu` (or the `la` pseudo, which GNU as also expands to addiu) on
 * every pinned gcc version. */
extern void bzero(void *ptr, int len);

void func_8004A918(void) {
    bzero((void *)0x80013564, 0x50);
}


int func_8004AA34(int *a0, int *a1)
{
    return *a0 - *a1;
}

/* Count leading non-NULL entries in a NULL-terminated pointer array.
 * Returns 0 if the first entry is already NULL, otherwise returns the
 * index of the first NULL entry found while scanning forward. */
s32 func_8004AE3C(void **arg0)
{
    void **list;
    s32 count;

    list = arg0;
    count = 0;
    if (*list != 0) {
        do {
            list++;
            count++;
        } while (*list != 0);
    }
    return count;
}


/* Comparator callback: orders two elements (each a pointer to a string) by
 * looking up the first character of each string in a translation/order table
 * pointed to by D_80081540, and returning the difference of the looked-up
 * values (used as a qsort-style compare function). */

extern unsigned char *D_80081540;

int func_8004AE98(unsigned char **a0, unsigned char **a1)
{
    unsigned char *s0 = *a0;
    unsigned char *s1 = *a1;

    return D_80081540[*s0] - D_80081540[*s1];
}

/* trivial wrapper: saves $ra, calls func_8004AEC4, restores, returns */
extern void func_8004AEC4(void);

void func_8004AFC8(void)
{
    func_8004AEC4();
}


/* extern/typedef decls */
extern void func_8004B364(int a0, int a1, void *a2);

/* Trivial wrapper: forwards a0 as the third arg to func_8004B364(0, 1, a0). */
void func_8004B3DC(void *a0) {
    func_8004B364(0, 1, a0);
}


/* Walks the singly-linked list headed by D_80081498 looking for node a0;
   returns the matching node, or NULL if the list is empty or exhausted.
   (Reuses the Node typedef + D_80081498 decl from func_80040418 above.) */
Node *func_8004B4A8(Node *a0)
{
    Node *v0 = D_80081498.head;

    while (v0 != 0) {
        if (v0 == a0) {
            break;
        }
        v0 = v0->next;
    }

    return v0;
}


/* Walk an array of 12-byte-stride records starting at a0, counting records
 * until (and including) one whose first byte has the 0x80 bit set; return
 * that 1-based count. */

typedef struct {
    /* 0x0 */ unsigned char unk0;
    /* 0x1 */ unsigned char pad[11];
} Unk8004B4DC; /* size 0xC */

int func_8004B4DC(Unk8004B4DC *a0) {
    int v1 = 0;

    do {
        v1++;
    } while ((a0++->unk0 & 0x80) == 0);

    return v1;
}


/* trivial wrapper - invokes func_8003E4FC(6, &D_80080B48, 0) */
/* v5-recovered decl */ extern int D_80080B48[4];
void func_8004B634(void)
{
    func_8003E4FC(6, D_80080B48, 0);
}


extern void func_8004B634(void);

/* Trivial wrapper: saves $ra, calls func_8004B634, restores $ra, returns. */
void func_8004B834(void)
{
    func_8004B634();
}


/* trivial wrapper - invokes func_8004B854(a0, a1, 0) */
extern int func_8004B854(int a0, int a1, int a2);

int func_8004B8BC(int a0, int a1)
{
    return func_8004B854(a0, a1, 0);
}




extern unsigned char D_80080A84[16];

struct S8004CBFC_a1 {
    unsigned short f0;
    unsigned short pad2;
    int f4;
};

struct S8004CBFC_a0 {
    int f0;
    int *f4;
    struct S8004CBFC_a1 *f8;
};

/* Initialize a0: store a1 pointer, divide a1->f0 by a global rate byte,
   store the quotient, remember a2, and if a2 is non-null, copy a1->f4 into *a2. */
void func_8004CBFC(struct S8004CBFC_a0 *a0, struct S8004CBFC_a1 *a1, int *a2) {
    a0->f8 = a1;
    a0->f0 = a1->f0 / D_80080A84[0];
    a0->f4 = a2;
    if (a2 != 0) {
        *a2 = a1->f4;
    }
}



/* Given a pointer to an object, return a pointer to a sub-structure that
 * depends on the upper nibble of the byte at offset 1: type 0x30 selects
 * the field at offset 0x18, all other types (including 0x20) select the
 * field at offset 0xC. */
void *func_8004D064(void *arg) {
    unsigned char type = *((unsigned char *)arg + 1) & 0xF0;

    switch (type) {
        case 0x30:
            arg = (char *)arg + 0x18;
            break;
        case 0x20:
        default:
            arg = (char *)arg + 0xC;
            break;
    }
    return arg;
}


/* Packs a byte value into a 4-byte record: out[0] = low-nibble*8,
 * out[1] = (high-nibble bits) - 0x20, out[2] = 8 (constant), out[3] = 0x10 (constant). */
void func_8004D8F0(u32 a0, u8 *a1) {
    a1[0] = (a0 & 0xF) << 3;
    a1[1] = (a0 & 0xF0) - 0x20;
    a1[2] = 8;
    a1[3] = 0x10;
}


void func_8004D9E0(signed char *a0, int a1, int a2, int a3, int a4)
{
    int q = (a1 * a3) / 2 - 0x80;
    a0[2] = a1 * 4 + q;
    a0[3] = a2 * (a4 + 0x10) - 0x80;
}

void func_8004DCE0(int a0)
{
    D_80081550 = a0;
}

void func_8004DDB4(void)
{
    D_80081554 = 0;
    D_80081558 = 0;
}

extern void func_80033AE8(int);

/* Trivial wrapper: invoke func_80033AE8 with a fixed argument of 2. */
void func_8004DDC4(void) {
    func_80033AE8(2);
}


/* packs low bits of a1 into a 16-bit field at offset 6 of the struct pointed to by a0 */
void func_8004E264(void *a0, int a1)
{
    short v0 = (a1 & 0xF) + 0x7C80;
    v0 = v0 + ((a1 & 0x10) << 3);
    *(short *)((char *)a0 + 6) = v0;
}

unsigned char *func_8004E280(unsigned char *a0, int *a1) {
    *a1 = *a0 - 0x30;
    return a0 + 1;
}




/* extern: number-to-padded-string helper (unmatched sibling) */
extern void func_8004E4C0(int value, unsigned short width, char *buf, int pad);

/* Wrapper: format `value` into `buf` right-justified in `width` columns, space-padded. */
void func_8004E57C(int value, unsigned short width, char *buf)
{
    func_8004E4C0(value, width, buf, ' ');
}



void func_8004E994(void) {
}

/* Call func_8004B1A4 with the same argument, only if it is non-NULL. */
extern void func_8004B1A4(void *a0);

void func_8004E99C(void *a0)
{
    if (a0 != 0) {
        func_8004B1A4(a0);
    }
}


/* Wrapper: if arg0 is non-NULL, forward it to func_8004B1A4 (which sets a
 * flag bit at offset -2 in the object and mirrors it into a global). */
extern void func_8004B1A4(void *arg0);

void func_8004E9C0(void *arg0) {
    if (arg0 != 0) {
        func_8004B1A4(arg0);
    }
}


void func_8004E9E4(void) {
}

void func_8004EB30(void) {
    D_80084130[0] = 0;
}

/* Trivial trampoline: forwards a0 through to func_8004EDA8 with a1 forced to 0. */
extern void *func_8004EDA8(void *arg0, int arg1);

void func_8004EE30(void *a0)
{
    func_8004EDA8(a0, 0);
}


/* Trivial wrapper: forwards its own first argument to func_8004EDA8 along with constant 1. */
extern void *func_8004EDA8(void *arg0, int arg1);

void func_8004EE50(int arg0) {
    func_8004EDA8(arg0, 1);
}


/* Trivial wrapper: forwards its pointer argument to func_8004EDA8 with a constant second arg (2). */
extern void *func_8004EDA8(void *arg0, int arg1);

void *func_8004EE70(void *arg0)
{
    return func_8004EDA8(arg0, 2);
}


extern void func_8004EF90(void *a0);
extern void func_8004EFF4(void *a0);
extern void func_8004F068(void *a0);
extern void func_8004F1E8(void *a0);
extern void func_8004F0DC(void *a0);

/* Dispatches initialization to several sub-structures at fixed offsets from a0 */
void func_8004F2BC(void *a0)
{
    func_8004EF90((char *)a0 + 0x8);
    func_8004EFF4((char *)a0 + 0x80);
    func_8004F068((char *)a0 + 0xF8);
    func_8004F1E8((char *)a0 + 0x170);
    func_8004F0DC(a0);
}

extern unsigned char D_80071684[16];

extern void func_800491F4(void *a0, void *a1, int a2);

/* Forwards a0 to func_800491F4 along with a fixed config table and limit 7 */
void func_8004F308(void *a0)
{
    func_800491F4(a0, D_80071684, 7);
}


void func_8004F3D0(int *a0, int a1)
{
    *a0 = a1;
}

void func_8004F67C(void) {
}

/* Chain of pointer dereferences down to a s16 field, then subtract the two
 * results. a0/a1 each hold a pointer at offset 0x0 to a struct that holds a
 * pointer at 0xC to a struct that holds a pointer at 0x4 to a struct that
 * finally holds the s16 value at offset 0xC. */

typedef struct {
    char pad0[0xC];
    short val;
} Level3;

typedef struct {
    char pad0[0x4];
    Level3 *l3;
} Level2;

typedef struct {
    char pad0[0xC];
    Level2 *l2;
} Level1;

typedef struct {
    Level1 *l1;
} Level0;

int func_8004F85C(Level0 *a0, Level0 *a1) {
    return a0->l1->l2->l3->val - a1->l1->l2->l3->val;
}



typedef struct {
    u8 pad[0x10];
    u8 unk10[0x14]; /* sub-object passed by address to func_80021448 */
    s32 unk24;
} Struct_8004FC68;

extern s32 func_80021448(void *arg0);

/* Calls func_80021448 on the sub-object at offset 0x10 and stores the
 * returned value into the field at offset 0x24. */
void func_8004FC68(Struct_8004FC68 *arg0) {
    arg0->unk24 = func_80021448(&arg0->unk10);
}


/* Advances a0 by 0x20 bytes to reach an embedded sub-object, reads an index
 * field at offset 0x30 within it, then returns the int stored at offset
 * 0x10 + idx*4 within that same sub-object (an indexed array access). */
int func_8004FF00(char *a0)
{
    int idx;
    a0 = a0 + 0x20;
    idx = *(int *)(a0 + 0x30);
    return *(int *)(a0 + idx * 4 + 0x10);
}

extern int func_8004FF00(char *a0);
extern void func_80021300(int a0);

/* Forwards its pointer arg through func_8004FF00 to compute an index/value,
 * then passes that result to func_80021300. */
void func_800502E0(char *a0)
{
    func_80021300(func_8004FF00(a0));
}


extern void func_80050308(void *a0);

/* Thin wrapper that forwards its single pointer argument to func_80050308. */
void func_80050494(void *a0)
{
    func_80050308(a0);
}

/* Generic vtable-style dispatcher: given a pointer to an object whose
 * first word is a function pointer, invoke that function, forwarding
 * the original argument registers (a0..a3) unchanged. */

struct VtableObj {
    void (*func)();
};

void func_80050694(struct VtableObj *a0)
{
    a0->func(a0);
}

/* Forwards a0 to func_800491F4 along with a fixed config table and limit 0x11 */
extern unsigned char D_800717BC[16];

extern void func_800491F4(void *a0, void *a1, int a2);

void func_80050B7C(void *a0)
{
    func_800491F4(a0, D_800717BC, 0x11);
}



/* extern decls */
extern int D_80080B94;
extern int D_80080B98;
extern void func_80050BA4(int a0);

/* If D_80080B94 is nonzero, pass D_80080B98 as the argument; otherwise pass 0. */
void func_80050CAC(void) {
    int a0 = 0;
    if (D_80080B94 != 0) {
        a0 = D_80080B98;
    }
    func_80050BA4(a0);
}


extern void func_8003AEF8(void *a0);
extern unsigned char D_800717D0[16];

/* summary: trivial wrapper that forwards the address of a large global struct/buffer to func_8003AEF8 */
void func_80050F84(void)
{
    func_8003AEF8(&D_800717D0);
}


extern void func_8003AEF8(void *a0);

extern char D_800717E8[12];

/* Thin wrapper that forwards the address of D_800717E8 to func_8003AEF8. */
void func_80050FA8(void)
{
    func_8003AEF8(D_800717E8);
}


/* Trivial wrapper: forwards a pointer to a fixed global struct/buffer. */
extern char D_80080C1C[];
extern void func_80041284(void *arg);

void func_80051500(void)
{
    func_80041284(D_80080C1C);
}


/* Sets a status/flag field to 1 if an object's callback function pointer
 * (at offset 0x10) equals func_80051548. */

extern void func_80051548(void);

typedef struct {
    unsigned char pad0[0x10];
    void (*func)(void);
    unsigned char pad1[0x2C - 0x14];
    short field2C;
} Struct_80051528;

void func_80051528(Struct_80051528 *a0) {
    if (a0->func == func_80051548) {
        a0->field2C = 1;
    }
}



/* If this object's update-function pointer (offset 0x10) is func_800517CC,
   set its state flag (offset 0x2C) to 1. */

extern void func_800517CC(void);

typedef struct {
    char pad_00[0x10];
    void (*update_func)(void);
    char pad_14[0x2C - 0x14];
    unsigned short flag_2C;
} Entity;

void func_800517AC(Entity *a0)
{
    if (a0->update_func == func_800517CC) {
        a0->flag_2C = 1;
    }
}


/* Check whether an object's update-function pointer (offset 0x10) is
 * func_80051CC4, and if so set its flag/state field at offset 0x2C to 1. */
extern void func_80051CC4(void);

typedef struct {
    unsigned char pad_00[0x10];
    void (*update_func)(void);
    unsigned char pad_14[0x2C - 0x14];
    short field_2C;
} Obj;

void func_80051CA4(Obj *a0) {
    if (a0->update_func == func_80051CC4) {
        a0->field_2C = 1;
    }
}


/* Object update-callback checker: if this object's update function pointer
 * (at offset 0x10) equals func_80051F58, mark flag at offset 0x2C. */

typedef struct {
    char pad0[0x10];
    void (*update_func)(void);
    char pad1[0x2C - 0x14];
    short flag_2C;
} Obj80051F38;

extern void func_80051F58(void);

void func_80051F38(Obj80051F38 *a0)
{
    if (a0->update_func == func_80051F58) {
        a0->flag_2C = 1;
    }
}






typedef void (*StateFunc)(void *);

typedef struct {
    u8 pad_00[0x10];
    StateFunc unk10;
    u8 pad_14[0x2A - 0x14];
    u16 unk2A;
} Entity1;

extern void func_8005313C(void *a0);

/* If the entity's state function pointer is func_8005313C, mark unk2A. */
void func_800530A4(Entity1 *a0) {
    if (a0->unk10 == func_8005313C) {
        a0->unk2A = 1;
    }
}



/* trivial wrapper: func_8003E4FC(6, a0, 0); func_8003F320(); */
extern int func_8003E4FC(int a0, void *a1, int a2);
extern void func_8003F320(void);

void func_80053C3C(void *a0)
{
    func_8003E4FC(6, a0, 0);
    func_8003F320();
}


/* func_80055778 returns an int (0 or -1) that only matters as its low 16 bits;
   only call site of this helper. */
extern int func_80055778(unsigned short a0);

/* summary: masks the argument to 16 bits, forwards it to func_80055778, then
   sign-extends the 16-bit result back to a full word (i.e. returns a short). */
short func_80053DA8(int a0)
{
    return func_80055778((unsigned short)a0);
}


/* Stashes arg0 into D_8008480C[0], then calls func_80054D64 (no args). The %hi
   lui for the store is hoisted above the ra-save by the maspsx delay-slot lui-hoist. */
extern short D_8008480C[8];
extern void func_80054D64(void);

void func_80053DCC(short arg0)
{
    D_8008480C[0] = arg0;
    func_80054D64();
}

/* stores a0 into global halfword D_80084808 */
void func_80053E14(short a0)
{
    D_80084808[0] = a0;
}

int func_800542A4(void)
{
    return 0;
}

int func_80054AF0(int arg0)
{
    if (arg0 == 1) {
        return 0x5F;
    }
    return 0x7F;
}



void func_800555FC(void) {
}

void func_80055604(void) {
}

/* Trivial wrapper that forwards to func_8005BAB0 with no arguments/return value used. */
extern void func_8005BAB0(void);

void func_80055730(void)
{
    func_8005BAB0();
}


void func_800557BC(void) {
    D_80084778[0] = 0;
}

/* Initializes a small task/timer-like object embedded in a larger struct:
   sets field at 0x10 to 0x80, field at 0xC to 3, field at 0x4 to 0, and
   fields at 0x16/0x18 both to 0xA. */

typedef struct {
    char pad0[4];      /* 0x0 */
    int field4;        /* 0x4 */
    char pad8[4];      /* 0x8 */
    int fieldC;        /* 0xC */
    short field10;     /* 0x10 */
    char pad12[4];     /* 0x12 */
    short field16;     /* 0x16 */
    short field18;     /* 0x18 */
} D_80055990_Struct;

void func_80055990(D_80055990_Struct *a0) {
    a0->field10 = 0x80;
    a0->fieldC = 3;
    a0->field4 = 0;
    a0->field16 = 0xA;
    a0->field18 = 0xA;
}


void func_80055CEC(void) {
}

void func_80055E6C(void) {
}

void func_80055E74(void) {
}

void func_80055E7C(void) {
}


void func_80056D3C(void) {
}



void func_80057A48(void) {
}


void func_8005848C(void) {
}

/* D_800737A4: hi/lo access (lui/lw with %hi/%lo, not gp_rel) -> size must be > 8 bytes */
extern int D_800737A4[4];
extern void func_80059BC4(void);

/* If the flag/pointer at D_800737A4 is set, call func_80059BC4(). */
void func_800584E4(void) {
    if (D_800737A4[0]) {
        func_80059BC4();
    }
}


void func_800587F8(void) {
}

/* Packs four byte-sized values into a single 32-bit word via sequential shift/mask/combine. */
unsigned int func_80058A7C(int a0, int a1, int a2, int a3)
{
    unsigned int v0;

    v0 = a0 & 0xFF;
    v0 = v0 << 8;
    v0 = v0 + (a1 & 0xFF);
    v0 = v0 << 8;
    v0 = v0 + (a2 & 0xFF);
    v0 = v0 << 8;
    v0 = v0 | (a3 & 0xFF);
    return v0;
}


int func_80058AA8(int a0, int a1)
{
    return ((a0 & 0xFF) << 8) | (a1 & 0xFF);
}

int func_80058E50(int *a0, int a1)
{
    *a0 += a1;
    return *a0;
}

void func_80058E64(void) {
}




/* Trivial wrapper: calls func_8005A33C with no arguments. */
extern void func_8005A33C(void);

void func_8005A37C(void)
{
    func_8005A33C();
}


void func_8005A39C(int arg0) {
    D_80086D4C[0] = arg0;
}

/* extern/typedef decls */
/* D_80073824 is accessed via hi/lo (not gp_rel) in neighboring functions
 * (func_8005A33C, func_80058510), so declare it >8 bytes to force hi/lo codegen. */
extern s32 D_80073824[4];

extern void func_80058700(void);

/* If the flag/counter at D_80073824 is set, run func_80058700(). */
void func_8005A3A8(void)
{
    if (D_80073824[0])
    {
        func_80058700();
    }
}


/* Zero out a single byte flag/global at D_8007382A. */
extern unsigned char D_8007382A[16];

void func_8005A3D4(void) {
    D_8007382A[0] = 0;
}


void func_8005A420(void) {
}

/* Calls three subroutines in sequence with no arguments. */
extern void func_80056C30(void);
extern void func_8005A26C(void);
extern void func_8005D7BC(void);

void func_8005A4B8(void)
{
    func_80056C30();
    func_8005A26C();
    func_8005D7BC();
}



void func_8005ACD0(short arg0) {
    D_80073828[0] = arg0;
}

/* Trivial wrapper: forwards to func_8005ACDC() and returns. */
extern void func_8005ACDC(void);

void func_8005B300(void)
{
    func_8005ACDC();
}


/* extern declarations */
extern void func_8005E450(int a0);
extern void func_8005D88C(int a0);

/* Calls two initialization/setup routines, each with constant argument 1. */
void func_8005B320(void) {
    func_8005E450(1);
    func_8005D88C(1);
}


extern int func_8005DA88(void *arg);

/* Message/event record passed to func_8005DA88; only the fields this
 * caller sets (type, x, y) are laid out here, the rest is padding to
 * keep offsets/size matching the retail stack frame. */
struct Msg8005B3D8 {
    int type;   /* 0x00 */
    int f4;     /* 0x04 */
    short x;    /* 0x08 */
    short y;    /* 0x0A */
    int fc;     /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
};

/* summary: builds a type-6 message with x/y scaled to 1/256 units
 * (a0/a1 << 8) on the stack and forwards it to func_8005DA88 */
int func_8005B3D8(short a0, short a1) {
    struct Msg8005B3D8 msg;
    int t0 = a0;
    int t1 = a1;

    msg.type = 6;
    t0 = t0 << 8;
    t1 = t1 << 8;
    msg.x = t0;
    msg.y = t1;
    return func_8005DA88(&msg);
}




/* Returns the current value of global D_80085FCC (simple accessor). */
extern int D_80085FCC[4];

int func_8005C808(void) {
    return D_80085FCC[0];
}


extern void func_80057D20(short a0, int a1, int a2);

/* Wrapper: forwards the item/entity index (a1) to func_80057D20 with a
 * fixed opcode of 7, passing the value argument masked to 7 bits. */
void func_8005C88C(int a0, short a1, int a2)
{
    func_80057D20(a1, 7, a2 & 0x7F);
}


extern void func_80057D20(short a0, int a1, int a2);

/* Wrapper: forwards the item/entity index (a1) to func_80057D20 with a
 * fixed opcode of 10, passing the value argument masked to 7 bits. */
void func_8005C8EC(int a0, short a1, int a2)
{
    func_80057D20(a1, 10, a2 & 0x7F);
}


void func_8005C980(void) {
}

void func_8005C988(void) {
}

void func_8005C990(void) {
}

void func_8005C998(void) {
}

void func_8005C9A0(void) {
}

/* Sign-extends both 16-bit args to 32-bit and forwards them unchanged to func_8005A5C8. */
extern void func_8005A5C8(s16 arg0, s16 arg1);

void func_8005C9A8(s16 arg0, s16 arg1) {
    func_8005A5C8(arg0, arg1);
}


extern void func_8005A428(void);

/* Trivial wrapper/trampoline that calls func_8005A428 with no argument setup. */
void func_8005C9D4(void)
{
    func_8005A428();
}


/* extern: takes three byte-sized args */
extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);

/* Trivial wrapper: masks each arg to a byte and forwards to func_8005A4E8. */
void func_8005C9F4(s32 arg0, s32 arg1, s32 arg2)
{
    func_8005A4E8(arg0, arg1, arg2);
}


/* Byte-mask/short-sign-extend trampoline forwarding to func_8005A56C. */
extern void func_8005A56C(unsigned char a0, short a1, short a2);

void func_8005CA1C(unsigned char a0, short a1, short a2)
{
    func_8005A56C(a0, a1, a2);
}


extern void func_8005B418(s16 arg0);

/* Sign-extends the low 16 bits of the argument to a short and forwards it. */
void func_8005CA4C(s32 arg0)
{
    func_8005B418((s16)arg0);
}


/* Trivial wrapper: calls func_8005CA90 with argument 0. */
extern void func_8005CA90(int arg0);

void func_8005CA70(void)
{
    func_8005CA90(0);
}





/* declared with size > 8 bytes so this TU emits %hi/%lo (lui/lw) addressing
   for D_8007996C instead of %gp_rel; only element 0 (a pointer) is used here */
extern int *D_8007996C[4];

/* Clears bits 0x0F000000 and sets bit 0x20000000 in the word pointed to by
   the global pointer D_8007996C[0]. */
void func_8005D6D8(void)
{
    volatile int *p = D_8007996C[0];

    *p = (*p & 0xF0FFFFFF) | 0x20000000;
}

/* declared with size > 8 bytes so this TU emits %hi/%lo (lui/lw) addressing
   for D_8007996C instead of %gp_rel; only element 0 (a pointer) is used here */
extern int *D_8007996C[4];

/* Clears bits 0x0F000000 and sets bits 0x22000000 in the word pointed to by
   the global pointer D_8007996C[0]. */
void func_8005D704(void)
{
    volatile int *p = D_8007996C[0];

    *p = (*p & 0xF0FFFFFF) | 0x22000000;
}


extern void DMACallback(int a0, int a1);

/* Trampoline: calls DMACallback(4, a0), discarding the return value */
void func_8005D798(int a0)
{
    DMACallback(4, a0);
}


typedef struct {
    u8 pad[0x1AA];
    u16 field_1AA;
} TargetStruct;

typedef struct {
    TargetStruct *ptr;
    u32 pad2[2]; /* keep total size > 8 bytes so hi/lo addressing (not gp_rel) is used */
} D_80079958_t;

extern D_80079958_t D_80079958;

/* Return whether bit 0x80 of the halfword at offset 0x1AA of *D_80079958.ptr is set */
s32 func_8005DA68(void) {
    if (D_80079958.ptr->field_1AA & 0x80)
        return 1;
    return 0;
}



/* Trivial wrapper: forwards a0,a1 and calls func_8005E4C4 with fixed
 * constants 0xCC/0xCD as the last two args, returning its result untouched. */
extern s32 func_8005E4C4(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_8005E4A0(s32 a0, s32 a1) {
    return func_8005E4C4(a0, a1, 0xCC, 0xCD);
}



/* extern decl for the callee */
extern void func_8005E7B0(int a0, int a1);

/* summary: calls func_8005E7B0(0xCC, 0xCD) */
void func_8005E78C(void)
{
    func_8005E7B0(0xCC, 0xCD);
}




/* extern decls for callees */
extern void func_8005F134(void *a0);
extern void func_8005E97C(int a0, int a1);

/* summary: forwards a0 to func_8005F134, then reads the struct's first
 * word field and passes it (with mode=1) to func_8005E97C. */
void func_8005EC0C(void *a0)
{
    void *s0 = a0;

    func_8005F134(a0);
    func_8005E97C(1, *(int *)s0);
}






