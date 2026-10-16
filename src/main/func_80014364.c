#include "common.h"

typedef struct S_80027364_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80027364_0;   /* base in mainCreateSaveHeading */

typedef struct S_80027364_1 {
    u8 pad_00[0xEC];
    s32 unk_EC;
} S_80027364_1;   /* work in mainCreateSaveHeading */


extern s32 findActiveListNode(void *target_node);
extern void *initializeSceneObjectInBuffer(s32 node_flags, void *node_buffer, s32 word_count);
extern void func_8004491C(void *entry, void *registration_id);
extern void func_80023A00(void *record);
extern void bzero(void *destination, s32 byte_count);
extern void func_8002727C(void *work_state, s32 value);
extern s32 mainLinkSaveHeadingDrawNodes(void *input);
extern void func_80027324(void *work_state, s32 init_value);

extern u8 D_80027DD0[];
extern u8 D_8002B968[];

/* Creates or resets the shared object and initializes its work state. */
void *mainCreateSaveHeading(s32 init_value)
{
    u8 *object;
    u8 *work_state;

    object = D_8002B968;
    work_state = D_8002B968 + 0x20;
    if (findActiveListNode(object) == 0) {
        object = initializeSceneObjectInBuffer(0, object, 0x68);
        func_8004491C(object, D_80027DD0);
    } else {
        func_80023A00(object);
        ((S_80027364_0 *)object)->unk_1E &= 0x7FFF;
        bzero(work_state, 0x180);
    }

    func_8002727C(work_state, 4);
    ((S_80027364_0 *)object)->unk_0C = work_state + 0xE0;
    ((S_80027364_1 *)work_state)->unk_EC = mainLinkSaveHeadingDrawNodes(work_state + 0xF0);
    func_80027324(work_state, init_value);
    return object;
}
