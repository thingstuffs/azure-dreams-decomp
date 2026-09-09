#include "common.h"


typedef struct Node {
    void *field0;
    struct Node *field4;
    u16 field8;
    s16 fieldA;
} Node;

extern s32 func_80022138(void);
extern s32 func_80022160(void);
extern void func_8003AD08(s32 arg0, void *arg1);
extern void func_8004DA74(void *arg0, void *arg1, s32 arg2);
extern void strcat(void *arg0, void *arg1);
extern void strcpy(void *arg0, void *arg1);
extern void *D_800283B8[];
extern u8 D_800283C4[];
extern void *D_800283EC[];
extern void *D_800283F4[];
extern u8 D_800283FC[];


typedef struct S_80024818_0 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80024818_0;   /* root in func_80024818 */

typedef struct S_80024818_1 {
    u8 pad_00[0xB4C];
    Node * unk_B4C;
} S_80024818_1;   /* cursor in func_80024818 */

void func_80024818(void *arg0)
{
    u8 sp10[0x40];
    u8 sp50[0x10];
    u8 *root;
    register s32 is_one ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 state;
    s32 small;
    register s32 index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 limit;
    void *first;
    void *dest;
    void *text;

    root = arg0;
    index = ((S_80024818_0 *)root)->unk_80;
    is_one = index == 1;
    state = func_80022138();
    if (is_one != 0) {
        if (func_80022160() == 0) {
            func_8004DA74(root + 0x84, D_800283EC[0], 1);
            dest = root + 0x204;
            text = D_800283EC[1];
            goto write_second;
        }
        small = state < 3;
    } else {
        small = state < 3;
    }

    first = root + 0x84;
    if (small != 0) {
        void **table;
        void *dest;

        func_8004DA74(first, D_800283C4, 1);
        dest = root + 0x204;
        ASM_USE_NV(dest);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        table = D_800283B8;
        ASM_USE_NV(table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = is_one << 2;
        func_8004DA74(dest, *(void **)((u8 *)table + index), 1);
        func_8004DA74(root + 0x384, table[2], 1);
        limit = 3;
        goto update_nodes;
    }

    {
        void **table;

        table = D_800283F4;
        ASM_USE_NV(table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = is_one << 2;
        func_8004DA74(first, *(void **)((u8 *)table + index), 1);
    }
    func_8003AD08(state / 3, sp50);
    strcpy(sp10, sp50);
    strcat(sp10, D_800283FC);
    dest = root + 0x204;
    text = sp10;
write_second:
    func_8004DA74(dest, text, 1);
    limit = 2;
update_nodes:
    ASM_KEEP(limit);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    {
        register s32 i ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 offset ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s16 value ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u8 *cursor ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 kind;

        i = 0;
        if (limit != 0) {
            kind = 0xA9;
            value = 0x110;
            offset = 0x84;
            cursor = root;
            do {
                Node *node;

                node = ((S_80024818_1 *)cursor)->unk_B4C;
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
}
