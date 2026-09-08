#include "common.h"

extern int   D_80084130[3];
extern short D_80073828[5];
extern short D_80084778[5];
extern int   D_80086D4C[3];

/* Initialize memory card services and disable automatic pad interrupt clearing. */
void func_8003D56C(void) {
    InitCARD();
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
}

/* Clear count words starting at dst. */
void func_8003DB4C(int *dst, int count) {
    while (count != 0) {
        *dst = 0;
        count--;
        dst++;
    }
}

/* Copy count words from src to dst. */
void func_8003DB6C(int *dst, int *src, int count) {
    while (count != 0) {
        *dst = *src;
        src++;
        count--;
        dst++;
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

/* Select an entry and reset the state's entry flags and value. */
void func_8003DB94(struct Dst *state, struct Elem *entries, short index) {
    state->f0 = entries + index;
    state->f4 = index;
    state->f5 = entries->b0;
    state->f14 &= 0x9FFF;
    state->f8 = state->f0->f4;
}

/* Swap two words. */
void func_8003E12C(int *left, int *right)
{
    int saved = *left;
    *left = *right;
    *right = saved;
}

/* Set the pointed-to flag. */
void func_8003E140(unsigned char *flag)
{
    *flag = 1;
}

/* Return the supplied value. */
int func_8003F52C(int value)
{
    return value;
}

extern int D_8006CE34[4];

/* Return the global status block. */
int *func_8003F534(void) {
    return D_8006CE34;
}

/* Return the saved global value. */
int func_8003F5D4(void)
{
    return D_800814C8;
}

/* Store the global value. */
void func_8003F5E0(int value)
{
    D_800814C8 = value;
}

/* Wait for 512 vertical synchronization intervals. */
void func_8003F5EC(void) {
    int frames_left;
    for (frames_left = 0x200; frames_left > 0; frames_left--) {
        VSync(0);
    }
}

/* Pack a tag and 23-bit ID into a record and store its accompanying value. */
void func_8003F6D4(int tag, int id, int *record, int value)
{
    id &= 0x7FFFFF;
    tag <<= 23;
    id |= tag;
    record[0] = id;
    record[1] = value;
}

typedef struct {
    void *head;
    int pad1;
    int pad2;
} FreelistHead; /* real D_80081490 is >8B so hi/lo addressing is used */

/* Push a node onto the free list and clear its second word. */
void func_80040044(void *node)
{
    void *old_head;
    {
        extern void *D_80081490;
        old_head = D_80081490;
    }
    {
        extern FreelistHead D_80081490;
        D_80081490.head = node;
    }
    *(int *)((char *)node + 4) = 0;
    *(void **)node = old_head;
}

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern struct {
    Node *head;
    int pad[2];
} D_80081498;

/* Set flag bits 0xC00 on every node in the global list. */
void func_80040418(void)
{
    Node *node = D_80081498.head;

    if (node != 0) {
        do {
            node->field_1E |= 0xC00;
            node = node->next;
        } while (node != 0);
    }
}

/* Count entries in a NULL-terminated pointer array. */
int func_80040F00(void **entries)
{
    int count;

    count = 0;
    if (entries[0] != 0) {
        do {
            entries++;
            count++;
        } while (*entries != 0);
    }
    return count;
}

extern int *D_800814E0;

/* Append a value to the global word list and restore its zero terminator. */
void func_80041110(int value)
{
    *D_800814E0 = value;
    D_800814E0++;
    *D_800814E0 = 0;
}

/* Return the stride index relative to base, or -1 when it reaches the limit. */
short func_800422A8(unsigned int value, unsigned int base, unsigned short stride, unsigned short limit)
{
    unsigned int index = (value - base) / stride;
    if (index >= limit) {
        return -1;
    }
    return (short)index;
}

extern void func_800423C0(void *a0, short a1);
extern void func_80042984(void *a0);

/* Configure an entity with a signed halfword value and update its status. */
void func_800424E0(void *entity, int value)
{
    func_800423C0(entity, (short)value);
    func_80042984(entity);
}

/* Return zero for any argument list. */
s32 func_80043FB8(s32 unused, ...)
{
    return 0;
}

extern void func_8003F540(int a0, int a1, int a2, int a3);
extern short func_80053DA8(int a0);

/* Forward four values and trigger status event 0x300. */
void func_80044234(int first, int second, int third, int fourth)
{
    func_8003F540(first, second, third, fourth);
    func_80053DA8(0x300);
}

extern int *func_8003F534(void);

/* Combine the status block's low 24-bit tick value with its base adjustment. */
int func_800445E0(void)
{
    int *status = func_8003F534();
    int ticks = status[2] & 0xFFFFFF;
    ticks = ticks - 0x20;
    return ticks + status[1];
}

extern void func_800463EC(void *a0, int a1, void *a2, short a3);

typedef struct Node46398 {
    char pad0[6];
    short field6;
    int field8;
    void *fieldC;
} Node46398;

/* Process linked objects using each node's value, record pointer, and halfword parameter. */
int func_80046398(void *object, int value, void *record)
{
    void *current = object;
    Node46398 *node;

    do {
        node = (Node46398 *)record;
        func_800463EC(current, value, record, node->field6);
        record = *(void **)((char *)current - 8);
        current = (char *)record + 0x20;
        if (record == 0)
            break;
        node = (Node46398 *)record;
        value = node->field8;
        record = node->fieldC;
    } while (1);

    return 0;
}

extern int func_80044BB0(void);

/* Return the query result as a signed halfword. */
short func_80047714(void)
{
    return (short)func_80044BB0();
}

extern void func_800477F4(void *arg0);
extern void func_80047694(void *arg0);

/* Run both update steps on an entity. */
void func_800478B8(void *entity)
{
    func_800477F4(entity);
    func_80047694(entity);
}

extern void bzero(void *dst, int n);
extern unsigned char D_80083D08[0x30];

/* Clear the global 0x30-byte buffer. */
void func_800479AC(void)
{
    bzero(D_80083D08, 0x30);
}

typedef struct {
    u8 unk[0xD000];
} Struct_800FC000;

extern Struct_800FC000 D_800FC000[];

/* Return the indexed 0xD000-byte global block. */
void *func_80047A44(s32 index)
{
    return &D_800FC000[index];
}

/* Add 0x8000 to the supplied value. */
int func_80047AA4(int value)
{
    return value + 0x8000;
}

extern Struct_800FC000 D_800FC000[];

/* Compute a block index from a raw address using signed division by 0xD000. */
s32 func_80047C60(void *address)
{
    return ((s32)address - (s32)D_800FC000) / 0xD000;
}

typedef struct {
    unsigned char pad[0x14];
    unsigned short unk14;
} Struct_80048374;

extern void func_80047784(Struct_80048374 *a0, short a1, short a2);

/* Set entity flag 0x400 and reselect its entry. */
void func_80048374(Struct_80048374 *entity, short index, short offset) {
    entity->unk14 |= 0x400;
    func_80047784(entity, index, offset);
}

extern int func_80048500(short a0, int a1);

/* Load the indexed entry from table zero. */
void func_80048568(short index)
{
    func_80048500(index, 0);
}

extern int func_80048500(short a0, int a1);

/* Load the indexed entry from table one and return the result. */
int func_80048590(short index)
{
    return func_80048500(index, 1);
}

extern int func_80048500(short a0, int a1);

/* Load the indexed entry from table two. */
void func_800485B8(short index)
{
    func_80048500(index, 2);
}

extern int func_80048C3C(int a0);

/* Return the result of query zero. */
int func_80048D00(void)
{
    return func_80048C3C(0);
}

extern int func_80048C3C(int a0);

/* Return the result of query one. */
int func_80048D20(void)
{
    return func_80048C3C(1);
}

extern int func_80048C3C(int);

/* Return the result of query two. */
int func_80048D40(void)
{
    return func_80048C3C(2);
}

/* Return the indexed global table value. */
int func_80048DCC(int index)
{
    return D_80071250[index];
}

/* Read the indexed byte from the volatile global table. */
unsigned char func_80048DE8(int index) {
    volatile unsigned char *values = D_80071298;
    return values[index];
}

/* Count nonzero entries up to the supplied limit. */
s32 func_80048F8C(s32 *entries, s32 limit)
{
    s32 count = 0;

    if (limit > 0) {
        do {
            if (*entries == 0) {
                break;
            }
            count++;
            entries++;
        } while (count < limit);
    }
    return count;
}

typedef struct Struct_C_next Struct_C_next;
struct Struct_C_next {
    unsigned char pad[0xC];
    Struct_C_next *next;
};

/* Append a node to the end of a linked list. */
void func_80049250(Struct_C_next *tail, Struct_C_next *node) {
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = node;
}

/* Test whether the type equals 0x14. */
int func_80049280(int type)
{
    return type == 0x14;
}

extern int func_80049280(int arg0);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Struct8004928C;

/* Test whether the record's low five type bits equal 0x14. */
int func_8004928C(Struct8004928C *record)
{
    return func_80049280(record->unk3 & 0x1F);
}

extern int D_800713FC[4]; /* >8B forces hi/lo addressing (matches target's lui/addiu) */

extern int func_80049374(void *a0, int *a1);

/* Process an object using the fixed global table. */
int func_80049490(void *object) {
    return func_80049374(object, D_800713FC);
}

extern int func_80042A80(void);

/* Return flag bit 0x400 from the status query. */
int func_800494FC(void) {
    return func_80042A80() & 0x400;
}

/* Map the first set low flag bit to priority 0, 1, or 2, defaulting to 3. */
int func_80049944(int flags) {
    int priority = 3;

    if (flags & 1) {
        priority = 0;
    } else if (flags & 2) {
        priority = 1;
    } else if (flags & 4) {
        priority = 2;
    }

    return priority;
}

extern int func_80049944(int a0);

typedef struct {
    unsigned char pad[0x13];
    unsigned char unk13;
    int unk14;
} Struct80049984;

/* Return the record's flag priority, or 3 when its enabling byte is clear. */
int func_80049984(Struct80049984 *record)
{
    int priority = 3;

    if (record->unk13 != 0) {
        priority = func_80049944(record->unk14);
    }

    return priority;
}

/* Set the pointed-to flag and return one. */
int func_800499DC(int *flag)
{
    *flag = 1;
    return 1;
}

extern void func_80049CF4(void *packets, void *record);

/* Initialize a pair of packets from a source record. */
void func_80049DC8(void *packets, void *record)
{
    func_80049CF4(packets, record);
}

/* Advance an index by delta and correct a single wrap in either direction. */
int func_80049DE8(int index, int delta, int limit) {
    index = index + delta;
    if (delta > 0) {
        if (index < limit) {
        } else {
            index = index - limit;
        }
    } else {
        index = (index >= 0) ? index : (limit + index);
    }
    return index;
}

/* Read the indexed word from the volatile global table. */
int func_80049E6C(int index)
{
    volatile int *values = D_800712B4;
    return values[index];
}

extern int func_800438E4(void *a1);

/* Forward the second argument to the object query. */
int func_8004A4C4(void *unused, void *object) {
    return func_800438E4(object);
}

extern s32 func_8004A574(u8 *item, s32 flag);

/* file_load_com: process the item with mode one. */
s32 func_8004A618(void *item)
{
    return func_8004A574(item, 1);
}

/* func_koya_mon_talk_pal_ld: process the item with mode zero. */
s32 func_8004A638(void *item)
{
    return func_8004A574(item, 0);
}

extern void bzero(void *ptr, int len);

/* Clear the 0x50-byte table at address 0x80013564. */
void func_8004A918(void) {
    bzero((void *)0x80013564, 0x50);
}

/* Compare two signed words by subtraction. */
int func_8004AA34(int *left, int *right)
{
    return *left - *right;
}

/* Count entries in a NULL-terminated pointer array. */
s32 func_8004AE3C(void **entries)
{
    void **list;
    s32 count;

    list = entries;
    count = 0;
    if (*list != 0) {
        do {
            list++;
            count++;
        } while (*list != 0);
    }
    return count;
}

extern unsigned char *D_80081540;

/* Compare strings by their first characters' translated ordering values. */
int func_8004AE98(unsigned char **left, unsigned char **right)
{
    unsigned char *left_text = *left;
    unsigned char *right_text = *right;

    return D_80081540[*left_text] - D_80081540[*right_text];
}

extern void func_8004AEC4(void);

/* Invoke func_8004AEC4. */
void func_8004AFC8(void)
{
    func_8004AEC4();
}

extern void func_8004B364(int a0, int a1, void *a2);

/* Forward an object with fixed leading arguments zero and one. */
void func_8004B3DC(void *object) {
    func_8004B364(0, 1, object);
}

/* Find the target node in the global linked list. */
Node *func_8004B4A8(Node *target)
{
    Node *node = D_80081498.head;

    while (node != 0) {
        if (node == target) {
            break;
        }
        node = node->next;
    }

    return node;
}

typedef struct {
    /* 0x0 */ unsigned char unk0;
    /* 0x1 */ unsigned char pad[11];
} Unk8004B4DC; /* size 0xC */

/* Count 12-byte records through the first record with bit 0x80 set. */
int func_8004B4DC(Unk8004B4DC *record) {
    int count = 0;

    do {
        count++;
    } while ((record++->unk0 & 0x80) == 0);

    return count;
}

 extern int D_80080B48[4];
/* Process the fixed global record with command six. */
void func_8004B634(void)
{
    func_8003E4FC(6, D_80080B48, 0);
}

extern void func_8004B634(void);

/* jyotyu_set_reserve_nyul: process the fixed reserve record. */
void func_8004B834(void)
{
    func_8004B634();
}

extern int func_8004B854(int a0, int a1, int a2);

/* Forward an object and value with a zero event parameter. */
int func_8004B8BC(int object, int value)
{
    return func_8004B854(object, value, 0);
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

/* Initialize entry state, compute its rate, and optionally copy its value to the cursor. */
void func_8004CBFC(struct S8004CBFC_a0 *state, struct S8004CBFC_a1 *entry, int *cursor) {
    state->f8 = entry;
    state->f0 = entry->f0 / D_80080A84[0];
    state->f4 = cursor;
    if (cursor != 0) {
        *cursor = entry->f4;
    }
}

/* Select the embedded record at offset 0x18 for type 0x30, or 0xC otherwise. */
void *func_8004D064(void *object) {
    unsigned char type = *((unsigned char *)object + 1) & 0xF0;

    switch (type) {
        case 0x30:
            object = (char *)object + 0x18;
            break;
        case 0x20:
        default:
            object = (char *)object + 0xC;
            break;
    }
    return object;
}

/* Encode the value's nibbles and fixed dimensions into a four-byte record. */
void func_8004D8F0(u32 value, u8 *record) {
    record[0] = (value & 0xF) << 3;
    record[1] = (value & 0xF0) - 0x20;
    record[2] = 8;
    record[3] = 0x10;
}

/* Compute and store byte coordinates from dimensions and grid position. */
void func_8004D9E0(signed char *record, int width, int height, int column, int row)
{
    int x_offset = (width * column) / 2 - 0x80;
    record[2] = width * 4 + x_offset;
    record[3] = height * (row + 0x10) - 0x80;
}

/* Store the global value. */
void func_8004DCE0(int value)
{
    D_80081550 = value;
}

/* Clear both global values. */
void func_8004DDB4(void)
{
    D_80081554 = 0;
    D_80081558 = 0;
}

extern void func_80033AE8(int);

/* Invoke func_80033AE8 with mode two. */
void func_8004DDC4(void) {
    func_80033AE8(2);
}

/* Encode the low five index bits into the record's halfword at offset six. */
void func_8004E264(void *record, int index)
{
    short packed = (index & 0xF) + 0x7C80;
    packed = packed + ((index & 0x10) << 3);
    *(short *)((char *)record + 6) = packed;
}

/* Decode one decimal character and advance the text pointer. */
unsigned char *func_8004E280(unsigned char *text, int *digit) {
    *digit = *text - 0x30;
    return text + 1;
}

extern void func_8004E4C0(int value, unsigned short width, char *buf, int pad);

/* Format a value right-justified with space padding. */
void func_8004E57C(int value, unsigned short width, char *buf)
{
    func_8004E4C0(value, width, buf, ' ');
}

/* Return without performing any work. */
void func_8004E994(void) {
}

extern void func_8004B1A4(void *a0);

/* Update the object when its pointer is non-NULL. */
void func_8004E99C(void *object)
{
    if (object != 0) {
        func_8004B1A4(object);
    }
}

extern void func_8004B1A4(void *arg0);

/* Update the object when its pointer is non-NULL. */
void func_8004E9C0(void *object) {
    if (object != 0) {
        func_8004B1A4(object);
    }
}

/* Return without performing any work. */
void func_8004E9E4(void) {
}

/* Clear the first word of the global state. */
void func_8004EB30(void) {
    D_80084130[0] = 0;
}

extern void *func_8004EDA8(void *arg0, int arg1);

/* Create an object task with mode zero. */
void func_8004EE30(void *object)
{
    func_8004EDA8(object, 0);
}

extern void *func_8004EDA8(void *arg0, int arg1);

/* Create an object task with mode one. */
void func_8004EE50(int object) {
    func_8004EDA8(object, 1);
}

extern void *func_8004EDA8(void *arg0, int arg1);

/* Create an object task with mode two and return it. */
void *func_8004EE70(void *object)
{
    return func_8004EDA8(object, 2);
}

extern void func_8004EF90(void *a0);
extern void func_8004EFF4(void *a0);
extern void func_8004F068(void *a0);
extern void func_8004F1E8(void *a0);
extern void func_8004F0DC(void *a0);

/* Initialize four embedded records and then the containing object. */
void func_8004F2BC(void *object)
{
    func_8004EF90((char *)object + 0x8);
    func_8004EFF4((char *)object + 0x80);
    func_8004F068((char *)object + 0xF8);
    func_8004F1E8((char *)object + 0x170);
    func_8004F0DC(object);
}

extern unsigned char D_80071684[16];

extern void func_800491F4(void *a0, void *a1, int a2);

/* Link entries using the fixed index table and limit seven. */
void func_8004F308(void *entries)
{
    func_800491F4(entries, D_80071684, 7);
}

/* Store a word through the supplied pointer. */
void func_8004F3D0(int *dst, int value)
{
    *dst = value;
}

/* Return without performing any work. */
void func_8004F67C(void) {
}

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

/* Compare the signed halfwords reached through two pointer chains. */
int func_8004F85C(Level0 *left, Level0 *right) {
    return left->l1->l2->l3->val - right->l1->l2->l3->val;
}

typedef struct {
    u8 pad[0x10];
    u8 unk10[0x14]; /* sub-object passed by address to func_80021448 */
    s32 unk24;
} Struct_8004FC68;

extern s32 func_80021448(void *arg0);

/* Store the query result for the object's embedded record. */
void func_8004FC68(Struct_8004FC68 *object) {
    object->unk24 = func_80021448(&object->unk10);
}

/* Return the selected word from the embedded record's value array. */
int func_8004FF00(char *object)
{
    int index;
    object = object + 0x20;
    index = *(int *)(object + 0x30);
    return *(int *)(object + index * 4 + 0x10);
}

extern int func_8004FF00(char *a0);
extern void func_80021300(int a0);

/* Pass the object's selected value to func_80021300. */
void func_800502E0(char *object)
{
    func_80021300(func_8004FF00(object));
}

extern void func_80050308(void *a0);

/* Forward the object to func_80050308. */
void func_80050494(void *object)
{
    func_80050308(object);
}

struct VtableObj {
    void (*func)();
};

/* Invoke the object's leading function pointer with the object itself. */
void func_80050694(struct VtableObj *object)
{
    object->func(object);
}

extern unsigned char D_800717BC[16];

extern void func_800491F4(void *a0, void *a1, int a2);

/* Link entries using the fixed index table and limit 0x11. */
void func_80050B7C(void *entries)
{
    func_800491F4(entries, D_800717BC, 0x11);
}

extern int D_80080B94;
extern int D_80080B98;
extern void func_80050BA4(int a0);

/* Pass the saved value when enabled, or zero otherwise. */
void func_80050CAC(void) {
    int value = 0;
    if (D_80080B94 != 0) {
        value = D_80080B98;
    }
    func_80050BA4(value);
}

extern void func_8003AEF8(void *a0);
extern unsigned char D_800717D0[16];

/* Process the global buffer D_800717D0. */
void func_80050F84(void)
{
    func_8003AEF8(&D_800717D0);
}

extern void func_8003AEF8(void *a0);

extern char D_800717E8[12];

/* Process the global buffer D_800717E8. */
void func_80050FA8(void)
{
    func_8003AEF8(D_800717E8);
}

extern char D_80080C1C[];
extern void func_80041284(void *arg);

/* Load the fixed global record D_80080C1C. */
void func_80051500(void)
{
    func_80041284(D_80080C1C);
}

extern void func_80051548(void);

typedef struct {
    unsigned char pad0[0x10];
    void (*func)(void);
    unsigned char pad1[0x2C - 0x14];
    short field2C;
} Struct_80051528;

/* Mark the object when its callback is func_80051548. */
void func_80051528(Struct_80051528 *object) {
    if (object->func == func_80051548) {
        object->field2C = 1;
    }
}

extern void func_800517CC(void);

typedef struct {
    char pad_00[0x10];
    void (*update_func)(void);
    char pad_14[0x2C - 0x14];
    unsigned short flag_2C;
} Entity;

/* Mark the entity when its callback is func_800517CC. */
void func_800517AC(Entity *entity)
{
    if (entity->update_func == func_800517CC) {
        entity->flag_2C = 1;
    }
}

extern void func_80051CC4(void);

typedef struct {
    unsigned char pad_00[0x10];
    void (*update_func)(void);
    unsigned char pad_14[0x2C - 0x14];
    short field_2C;
} Obj;

/* Mark the object when its callback is func_80051CC4. */
void func_80051CA4(Obj *object) {
    if (object->update_func == func_80051CC4) {
        object->field_2C = 1;
    }
}

typedef struct {
    char pad0[0x10];
    void (*update_func)(void);
    char pad1[0x2C - 0x14];
    short flag_2C;
} Obj80051F38;

extern void func_80051F58(void);

/* Mark the object when its callback is func_80051F58. */
void func_80051F38(Obj80051F38 *object)
{
    if (object->update_func == func_80051F58) {
        object->flag_2C = 1;
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

/* Mark the entity when its callback is func_8005313C. */
void func_800530A4(Entity1 *entity) {
    if (entity->unk10 == func_8005313C) {
        entity->unk2A = 1;
    }
}

extern int func_8003E4FC(int a0, void *a1, int a2);
extern void func_8003F320(void);

/* Process a record with command six and finish the update. */
void func_80053C3C(void *record)
{
    func_8003E4FC(6, record, 0);
    func_8003F320();
}

extern int func_80055778(unsigned short a0);

/* Pass the low 16 flag bits to the event handler and return its signed halfword result. */
short func_80053DA8(int flags)
{
    return func_80055778((unsigned short)flags);
}

extern short D_8008480C[8];
extern void func_80054D64(void);

/* Store a halfword and invoke the follow-up handler. */
void func_80053DCC(short value)
{
    D_8008480C[0] = value;
    func_80054D64();
}

/* Store the global halfword value. */
void func_80053E14(short value)
{
    D_80084808[0] = value;
}

/* Return zero. */
int func_800542A4(void)
{
    return 0;
}

/* Return 0x5F for mode one and 0x7F otherwise. */
int func_80054AF0(int mode)
{
    if (mode == 1) {
        return 0x5F;
    }
    return 0x7F;
}

/* Return without performing any work. */
void func_800555FC(void) {
}

/* Return without performing any work. */
void func_80055604(void) {
}

extern void func_8005BAB0(void);

/* Invoke func_8005BAB0. */
void func_80055730(void)
{
    func_8005BAB0();
}

/* Clear the global halfword. */
void func_800557BC(void) {
    D_80084778[0] = 0;
}

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

/* Initialize the state record's values and two counters. */
void func_80055990(D_80055990_Struct *state) {
    state->field10 = 0x80;
    state->fieldC = 3;
    state->field4 = 0;
    state->field16 = 0xA;
    state->field18 = 0xA;
}

/* Return without performing any work. */
void func_80055CEC(void) {
}

/* Return without performing any work. */
void func_80055E6C(void) {
}

/* Return without performing any work. */
void func_80055E74(void) {
}

/* Return without performing any work. */
void func_80055E7C(void) {
}

/* Return without performing any work. */
void func_80056D3C(void) {
}

/* Return without performing any work. */
void func_80057A48(void) {
}

/* Return without performing any work. */
void func_8005848C(void) {
}

extern int D_800737A4[4];
extern void func_80059BC4(void);

/* Invoke func_80059BC4 when the global flag is set. */
void func_800584E4(void) {
    if (D_800737A4[0]) {
        func_80059BC4();
    }
}

/* Return without performing any work. */
void func_800587F8(void) {
}

/* Pack the low bytes of four values into a word, most significant byte first. */
unsigned int func_80058A7C(int byte_3, int byte_2, int byte_1, int byte_0)
{
    unsigned int packed;

    packed = byte_3 & 0xFF;
    packed = packed << 8;
    packed = packed + (byte_2 & 0xFF);
    packed = packed << 8;
    packed = packed + (byte_1 & 0xFF);
    packed = packed << 8;
    packed = packed | (byte_0 & 0xFF);
    return packed;
}

/* Pack two low bytes into a halfword value. */
int func_80058AA8(int high, int low)
{
    return ((high & 0xFF) << 8) | (low & 0xFF);
}

/* Add delta to the pointed-to counter and return its new value. */
int func_80058E50(int *counter, int delta)
{
    *counter += delta;
    return *counter;
}

/* Return without performing any work. */
void func_80058E64(void) {
}

extern void func_8005A33C(void);

/* Invoke func_8005A33C. */
void func_8005A37C(void)
{
    func_8005A33C();
}

/* Store the first word of the global state. */
void func_8005A39C(int value) {
    D_80086D4C[0] = value;
}

extern s32 D_80073824[4];

extern void func_80058700(void);

/* Invoke func_80058700 when the global value is nonzero. */
void func_8005A3A8(void)
{
    if (D_80073824[0])
    {
        func_80058700();
    }
}

extern unsigned char D_8007382A[16];

/* Clear the global byte flag. */
void func_8005A3D4(void) {
    D_8007382A[0] = 0;
}

/* Return without performing any work. */
void func_8005A420(void) {
}

extern void func_80056C30(void);
extern void func_8005A26C(void);
extern void func_8005D7BC(void);

/* Run the three initialization routines in order. */
void func_8005A4B8(void)
{
    func_80056C30();
    func_8005A26C();
    func_8005D7BC();
}

/* Store the global halfword value. */
void func_8005ACD0(short value) {
    D_80073828[0] = value;
}

extern void func_8005ACDC(void);

/* Invoke func_8005ACDC. */
void func_8005B300(void)
{
    func_8005ACDC();
}

extern void func_8005E450(int a0);
extern void func_8005D88C(int a0);

/* Run both setup routines with mode one. */
void func_8005B320(void) {
    func_8005E450(1);
    func_8005D88C(1);
}

extern int func_8005DA88(void *arg);

struct Msg8005B3D8 {
    int type;   /* 0x00 */
    int f4;     /* 0x04 */
    short x;    /* 0x08 */
    short y;    /* 0x0A */
    int fc;     /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
};

/* Send a type-six message with coordinates scaled by 256. */
int func_8005B3D8(short x, short y) {
    struct Msg8005B3D8 msg;
    int scaled_x = x;
    int scaled_y = y;

    msg.type = 6;
    scaled_x = scaled_x << 8;
    scaled_y = scaled_y << 8;
    msg.x = scaled_x;
    msg.y = scaled_y;
    return func_8005DA88(&msg);
}

extern int D_80085FCC[4];

/* Return the first word of the global state. */
int func_8005C808(void) {
    return D_80085FCC[0];
}

extern void func_80057D20(short a0, int a1, int a2);

/* Send command seven for the indexed entity with a seven-bit value. */
void func_8005C88C(int unused, short index, int value)
{
    func_80057D20(index, 7, value & 0x7F);
}

extern void func_80057D20(short a0, int a1, int a2);

/* Send command ten for the indexed entity with a seven-bit value. */
void func_8005C8EC(int unused, short index, int value)
{
    func_80057D20(index, 10, value & 0x7F);
}

/* Return without performing any work. */
void func_8005C980(void) {
}

/* Return without performing any work. */
void func_8005C988(void) {
}

/* Return without performing any work. */
void func_8005C990(void) {
}

/* Return without performing any work. */
void func_8005C998(void) {
}

/* Return without performing any work. */
void func_8005C9A0(void) {
}

extern void func_8005A5C8(s16 arg0, s16 arg1);

/* Forward two signed halfword values to func_8005A5C8. */
void func_8005C9A8(s16 first, s16 second) {
    func_8005A5C8(first, second);
}

extern void func_8005A428(void);

/* Invoke func_8005A428. */
void func_8005C9D4(void)
{
    func_8005A428();
}

extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);

/* Forward the low bytes of three values to func_8005A4E8. */
void func_8005C9F4(s32 first, s32 second, s32 third)
{
    func_8005A4E8(first, second, third);
}

extern void func_8005A56C(unsigned char a0, short a1, short a2);

/* Forward a byte code and two signed halfword values to func_8005A56C. */
void func_8005CA1C(unsigned char code, short first, short second)
{
    func_8005A56C(code, first, second);
}

extern void func_8005B418(s16 arg0);

/* Forward the value as a signed halfword to func_8005B418. */
void func_8005CA4C(s32 value)
{
    func_8005B418((s16)value);
}

extern void func_8005CA90(int arg0);

/* Invoke func_8005CA90 with mode zero. */
void func_8005CA70(void)
{
    func_8005CA90(0);
}

extern int *D_8007996C[4];

/* Clear bits 0x0F000000 and set bit 0x20000000 in the global target word. */
void func_8005D6D8(void)
{
    volatile int *flags = D_8007996C[0];

    *flags = (*flags & 0xF0FFFFFF) | 0x20000000;
}

extern int *D_8007996C[4];

/* Clear bits 0x0F000000 and set bits 0x22000000 in the global target word. */
void func_8005D704(void)
{
    volatile int *flags = D_8007996C[0];

    *flags = (*flags & 0xF0FFFFFF) | 0x22000000;
}

extern void DMACallback(int a0, int a1);

/* Install the callback for DMA channel four. */
void func_8005D798(int callback)
{
    DMACallback(4, callback);
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

/* Test bit 0x80 in the global target's halfword at offset 0x1AA. */
s32 func_8005DA68(void) {
    if (D_80079958.ptr->field_1AA & 0x80)
        return 1;
    return 0;
}

extern s32 func_8005E4C4(s32 a0, s32 a1, s32 a2, s32 a3);

/* Forward two values with fixed trailing arguments 0xCC and 0xCD. */
s32 func_8005E4A0(s32 first, s32 second) {
    return func_8005E4C4(first, second, 0xCC, 0xCD);
}

extern void func_8005E7B0(int a0, int a1);

/* Invoke func_8005E7B0 with values 0xCC and 0xCD. */
void func_8005E78C(void)
{
    func_8005E7B0(0xCC, 0xCD);
}

extern void func_8005F134(void *a0);
extern void func_8005E97C(int a0, int a1);

/* Update an object and pass its first word to the mode-one handler. */
void func_8005EC0C(void *object)
{
    void *current = object;

    func_8005F134(object);
    func_8005E97C(1, *(int *)current);
}

