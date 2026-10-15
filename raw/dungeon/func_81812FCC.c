#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct ListNode ListNode;
extern ListNode *func_800491F4(ListNode **nodes, u8 *indices, s32 limit);
extern u8 D_80029544[];
ListNode *func_80027FCC(ListNode **nodes) { return func_800491F4(nodes, D_80029544, 15); }
