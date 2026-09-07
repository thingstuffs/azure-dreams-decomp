#include "common.h"

typedef struct Node {
    u8 pad0[4];
    struct Node *next;
    s32 field8;
    s32 fieldC;
    u8 pad10[4];
    u8 type;
    u8 active;
    s16 angle;
} Node;

extern s32 func_8008FD9C();
extern s32 func_8008FE78();

Node *func_8008FE90(Node *arg0) {
    register s32 temp_s1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    Node *var_s0;

    var_s0 = arg0->next;
    temp_s5 = arg0->fieldC;
    temp_s4 = arg0->field8;
    if (var_s0 != arg0) {
loop:
        temp_s3 = var_s0->field8;
        temp_s1 = var_s0->fieldC;
        if (var_s0->active != 0) {
            if (((u32)(var_s0->type - 2) >= 2U) ||
                (func_8008FE78(var_s0->angle, arg0->angle) != 0)) {
                if (func_8008FD9C(temp_s5, temp_s4, temp_s1, temp_s3) != 0) {
                    return var_s0;
                }
            }
        }
        var_s0 = var_s0->next;
        if (var_s0 != arg0) {
            goto loop;
        }
    }
    return 0;
}
