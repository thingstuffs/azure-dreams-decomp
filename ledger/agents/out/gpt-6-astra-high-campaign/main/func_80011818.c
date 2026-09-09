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

/* Builds status text and assigns it to two or three display nodes. */
void func_80024818(void *context)
{
    u8 text_buf[0x40];
    u8 number_buf[0x10];
    u8 *root;
    register s32 mode_one ASM_REG("$18");
    s32 state;
    s32 below_three;
    register s32 selection ASM_REG("$2");
    s32 node_count;
    void *first_buffer;
    void *text_buffer;
    void *text;

    root = context;
    selection = ((S_80024818_0 *)root)->unk_80;
    mode_one = selection == 1;
    state = func_80022138();
    if (mode_one != 0) {
        if (func_80022160() == 0) {
            func_8004DA74(root + 0x84, D_800283EC[0], 1);
            text_buffer = root + 0x204;
            text = D_800283EC[1];
            goto write_second;
        }
        below_three = state < 3;
    } else {
        below_three = state < 3;
    }

    first_buffer = root + 0x84;
    if (below_three != 0) {
        void **table;
        void *text_buffer;

        func_8004DA74(first_buffer, D_800283C4, 1);
        text_buffer = root + 0x204;
        ASM_USE_NV(text_buffer);
        table = D_800283B8;
        ASM_USE_NV(table);
        selection = mode_one << 2;
        func_8004DA74(text_buffer, *(void **)((u8 *)table + selection), 1);
        func_8004DA74(root + 0x384, table[2], 1);
        node_count = 3;
        goto update_nodes;
    }

    {
        void **table;

        table = D_800283F4;
        ASM_USE_NV(table);
        selection = mode_one << 2;
        func_8004DA74(first_buffer, *(void **)((u8 *)table + selection), 1);
    }
    func_8003AD08(state / 3, number_buf);
    strcpy(text_buf, number_buf);
    strcat(text_buf, D_800283FC);
    text_buffer = root + 0x204;
    text = text_buf;
write_second:
    func_8004DA74(text_buffer, text, 1);
    node_count = 2;
update_nodes:
    {
        register s32 node_index ASM_REG("$5");
        register s32 buffer_offset;
        register s16 node_value;
        register u8 *cursor;
        s32 node_kind;

        node_index = 0;
        if (node_count != 0) {
            node_kind = 0xA9;
            node_value = 0x110;
            buffer_offset = 0x84;
            cursor = root;
            do {
                Node *node;

                node = ((S_80024818_1 *)cursor)->unk_B4C;
                node->field0 = root + buffer_offset;
                node->field4->field8 = node_kind;
                node->field4->fieldA = node_value;
                buffer_offset += 0x180;
                cursor += 4;
                node_index += 1;
                node_value += 0x10;
            } while (node_index < node_count);
        }
    }
}
