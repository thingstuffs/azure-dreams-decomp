#include "common.h"

#include "common.h"

typedef struct RuntimeTail {
    u8 pad00[0x85];
    u8 field85;
    u8 field86;
    u8 field87;
} RuntimeTail;

typedef struct RuntimeState {
    u8 pad00[3];
    u8 field03;
    u8 pad04[0x34];
    s32 field38;
    u8 pad3C[0x0C];
    s32 field48[16];
    void *field88;
    RuntimeTail field8C;
} RuntimeState;

typedef struct RuntimeBlock {
    s32 field00;
    s32 field04;
} RuntimeBlock;

typedef struct RuntimeLinks {
    RuntimeTail *field00;
    RuntimeState *field04;
} RuntimeLinks;

typedef struct RuntimeTask {
    u8 pad00[0x10];
    void (*field10)(RuntimeLinks *);
    u8 pad14[0x0C];
    RuntimeLinks field20;
} RuntimeTask;

extern u8 D_80082BC0[9];
extern RuntimeBlock D_80082660[107];
extern RuntimeState D_80082A38;
extern u8 D_800809C0[9];
extern u8 D_80012D6E[9];

extern void *func_8003FE78(s32 arg0, void *arg1, s16 arg2);
extern void func_80037F70(RuntimeLinks *arg0);
extern void func_80037D9C(RuntimeState *arg0, u8 arg1);
extern void *memset(void *arg0, s32 arg1, u32 arg2);

void func_80037E58(void)
{
    RuntimeTask *task;
    RuntimeLinks *links;
    RuntimeState *state;
    RuntimeState *input;
    void *address;
    s32 i;

    task = func_8003FE78(0, D_80082BC0, 0x49);
    links = &task->field20;
    task->field10 = func_80037F70;
    links->field04 = &D_80082A38;
    links->field00 = &D_80082A38.field8C;

    for (i = 0; i < 107; i++) {
        memset(&D_80082660[i], 0, sizeof(RuntimeBlock));
    }

    for (i = 15; i >= 0; i--) {
        D_80082A38.field48[i] = 0;
    }

    do {
        state = &D_80082A38;
    } while (0);
    address = D_800809C0;
    state->field88 = address;
    state->field38 = 0;
    do {
        input = links->field04;
    } while (0);
    input->field03 = D_80012D6E[0];
    func_80037D9C(links->field04, 3);
    links->field00->field87 = 0;
    links->field00->field85 = 0;
    links->field00->field86 = links->field00->field85;
}
