#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Node {
    void *field0;
    struct Node *field4;
    u16 field8;
    s16 fieldA;
} Node;

extern s32 func_80022138(void);
extern s32 func_80022160(void);
extern void func_8002493C(void *arg0, void *arg1);
extern void func_80024948(void);
extern void func_8003AD08(s32 arg0, void *arg1);
extern void func_8004DA74(void *arg0, void *arg1, s32 arg2);
extern void strcat(void *arg0, void *arg1);
extern void strcpy(void *arg0, void *arg1);
extern void *D_800283B8[];
extern u8 D_800283C4[];
extern void *D_800283EC[];
extern void *D_800283F4[];
extern u8 D_800283FC[];

void func_80024818(void *arg0)
{
    u8 sp10[0x40];
    u8 sp50[0x10];
    register u8 *root ASM_REG("$19");
    register s32 is_one ASM_REG("$18");
    s32 state;
    s32 small;
    register s32 index ASM_REG("$2");
    register s32 limit ASM_REG("$9");
    void *first;

    root = arg0;
    index = FIELD(root, s32, 0x80);
    is_one = index == 1;
    state = func_80022138();
    if (is_one != 0) {
        if (func_80022160() == 0) {
            func_8004DA74(root + 0x84, D_800283EC[0], 1);
            return func_8002493C(root + 0x204, D_800283EC[1]);
        }
        small = state < 3;
    } else {
        small = state < 3;
    }

    first = root + 0x84;
    if (small != 0) {
        register void **table ASM_REG("$16");
        void *dest;

        func_8004DA74(first, D_800283C4, 1);
        dest = root + 0x204;
        ASM_USE_NV(dest);
        table = D_800283B8;
        ASM_USE_NV(table);
        index = is_one << 2;
        func_8004DA74(dest, *(void **)((u8 *)table + index), 1);
        func_8004DA74(root + 0x384, table[2], 1);
        limit = 3;
        ASM_TAILSLOT_PIN_TIED(limit);
        return func_80024948();
    }

    {
        register void **table ASM_REG("$3");

        table = D_800283F4;
        ASM_USE_NV(table);
        index = is_one << 2;
        func_8004DA74(first, *(void **)((u8 *)table + index), 1);
    }
    func_8003AD08(state / 3, sp50);
    strcpy(sp10, sp50);
    strcat(sp10, D_800283FC);
    func_8004DA74(root + 0x204, sp10, 1);
    {
        register s32 i ASM_REG("$5");
        register s32 offset ASM_REG("$7");
        register s16 value ASM_REG("$8");
        register u8 *cursor ASM_REG("$6");
        register s32 kind ASM_REG("$10");

        limit = 2;
        ASM_KEEP(limit);
        i = 0;
        if (limit != 0) {
            kind = 0xA9;
            value = 0x110;
            offset = 0x84;
            cursor = root;
            do {
                Node *node;

                node = FIELD(cursor, Node *, 0xB4C);
                node->field0 = root + offset;
                node->field4->field8 = kind;
                node->field4->fieldA = value;
                offset += 0x180;
                cursor += 4;
                i += 1;
                value += 0x10;
            } while (i < limit);
        }
    }
    ASM_USE_NV(is_one);
}
