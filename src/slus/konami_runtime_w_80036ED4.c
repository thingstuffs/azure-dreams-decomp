#include "common.h"

#include "common.h"

typedef struct S_80036ED4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80036ED4_0;   /* arg0 in func_80036ED4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80036D4C(s32 node_addr, void *record, s32 *config, s16 initial_mode,
                          s32 initial_value, s32 setup_id);
extern void func_80036F24(void *input, void *unused, void *output);

/* Initialize the display object and update its initial appearance. */
void func_80036ED4(void *object, void *display, s32 *data, s16 data_index,
                   s16 table_offset, s32 list_head) {
    func_80036D4C((s32)object, display, data, data_index, table_offset, list_head);
    func_80036F24((s8 *)object + 0x20,
                  ((S_80036ED4_0 *)object)->unk_08,
                  ((S_80036ED4_0 *)object)->unk_0C);
}
