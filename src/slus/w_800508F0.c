#include "slus/entry_words.h"

void *func_800508F0(S_800508F0 *entry, u8 *template)
{
    entry->field4 = D_80080B84;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];

    entry = entry + 1;
    entry->field4 = D_80080B80;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];
    entry->field0 = 3;

    return entry + 1;
}
