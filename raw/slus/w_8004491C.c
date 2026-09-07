#include "common.h"

typedef struct RegistrationNode {
    u8 pad00[0x14];
    struct RegistrationNode *prev;
    struct RegistrationNode *next;
    u16 type;
} RegistrationNode;

extern s32 D_80083360[0x20];
extern RegistrationNode *D_800833E0[0x20];
extern s32 D_8006E7B4[];

s32 func_8004491C(RegistrationNode *arg0, s32 arg1)
{
    RegistrationNode *node;
    s32 i;
    s32 first_free;
    s32 last_free;
    s32 sentinel;
    RegistrationNode *head;
    s32 result;

    node = arg0;
    first_free = -1;
    last_free = 0;
    i = last_free;
    sentinel = first_free;

    for (; i < 0x20; i++) {
        if (D_80083360[i] == arg1) {
            head = D_800833E0[i];
            node->next = head;
            if (head != 0) {
                head->prev = node;
            }
            D_800833E0[i] = node;
            ASM_USE(&D_800833E0[i]);
            result = 1;
            node->prev = (RegistrationNode *)&D_800833E0[i];
            node->type = i;
            return result;
        }
        if (D_80083360[i] == 0) {
            if (first_free == sentinel) {
                first_free = i;
            }
            last_free = i;
        }
    }

    if (first_free >= 0) {
        node->next = 0;
        if (D_8006E7B4[0] != 0) {
            s32 j = 0;
            do {
                if (D_8006E7B4[j] == arg1) {
                    D_80083360[first_free] = arg1;
                    D_800833E0[first_free] = node;
                    result = 1;
                    node->prev = (RegistrationNode *)&D_800833E0[first_free];
                    node->type = first_free;
                    return result;
                }
                j++;
            } while (D_8006E7B4[j] != 0);
        }

        D_80083360[last_free] = arg1;
        D_800833E0[last_free] = node;
        result = 1;
        node->prev = (RegistrationNode *)&D_800833E0[last_free];
        node->type = last_free;
        return result;
    }
    return 0;
}
