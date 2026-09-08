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

/* Registers a node under an existing or newly allocated registration ID. */
s32 func_8004491C(RegistrationNode *entry, s32 registration_id)
{
    RegistrationNode *node;
    s32 slot;
    s32 first_free;
    s32 last_free;
    s32 no_slot;
    RegistrationNode *head;
    s32 success;

    node = entry;
    first_free = -1;
    last_free = 0;
    slot = last_free;
    no_slot = first_free;

    for (; slot < 0x20; slot++) {
        if (D_80083360[slot] == registration_id) {
            head = D_800833E0[slot];
            node->next = head;
            if (head != 0) {
                head->prev = node;
            }
            D_800833E0[slot] = node;
            ASM_USE(&D_800833E0[slot]);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
            success = 1;
            node->prev = (RegistrationNode *)&D_800833E0[slot];
            node->type = slot;
            return success;
        }
        if (D_80083360[slot] == 0) {
            if (first_free == no_slot) {
                first_free = slot;
            }
            last_free = slot;
        }
    }

    if (first_free >= 0) {
        node->next = 0;
        if (D_8006E7B4[0] != 0) {
            s32 preferred_index = 0;
            do {
                if (D_8006E7B4[preferred_index] == registration_id) {
                    D_80083360[first_free] = registration_id;
                    D_800833E0[first_free] = node;
                    success = 1;
                    node->prev = (RegistrationNode *)&D_800833E0[first_free];
                    node->type = first_free;
                    return success;
                }
                preferred_index++;
            } while (D_8006E7B4[preferred_index] != 0);
        }

        D_80083360[last_free] = registration_id;
        D_800833E0[last_free] = node;
        success = 1;
        node->prev = (RegistrationNode *)&D_800833E0[last_free];
        node->type = last_free;
        return success;
    }
    return 0;
}
