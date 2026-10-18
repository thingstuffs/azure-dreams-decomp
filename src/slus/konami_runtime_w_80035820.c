#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035820_0 {
    s32 unk_00;
    u8 pad_04[0x4C];
    u16 unk_50;
    u8 pad_52[0x22];
    s32 unk_74;
} S_80035820_0;   /* arg0 in func_80035820 */


void runtime_clear_value();                         /* extern */
void func_80034EB4();                         /* extern */
void runtime_unlink_doubly_linked_node();                      /* extern */
void unlink_active_node();                      /* extern */
void func_80044A50();                      /* extern */

/* Cleans up a type-0x101 record and unlinks its enclosing object. */
void func_80035820(void *record) {
    void *object_base;

    if (((S_80035820_0 *)record)->unk_50 == 0x101) {
        func_80034EB4(((S_80035820_0 *)record)->unk_74);
        runtime_clear_value(((S_80035820_0 *)record)->unk_00);
        runtime_unlink_doubly_linked_node(record + 0x54);
        object_base = record - 0x20;
        func_80044A50(object_base);
        unlink_active_node(object_base);
    }
}
