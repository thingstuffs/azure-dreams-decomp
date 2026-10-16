#include "common.h"

extern void markRecordIfIndirectValueZero(void *a0, void *a1);
extern void tableHandleDecrementsCounterSetsPrecedingHalfwordGlobalFlagBitHex8000Remains(unsigned short *entry_data, int *counter);

/* Passes both pointers through markRecordIfIndirectValueZero and tableHandleDecrementsCounterSetsPrecedingHalfwordGlobalFlagBitHex8000Remains in order. */
void func_8004B324(void *first_ptr, void *second_ptr)
{
    markRecordIfIndirectValueZero(first_ptr, second_ptr);
    tableHandleDecrementsCounterSetsPrecedingHalfwordGlobalFlagBitHex8000Remains(first_ptr, second_ptr);
}
