# Format compared object statistics and populate display rows.



7 functions (foff 0x37CEC-0x38368) of one original translation unit. Literal-pool ownership (town/engine, g1058): string literals 0x800892C0, 0x800892C8, 0x800892CC, 0x800892F0, 0x800892FC, 0x80089304, 0x80089324, 0x8008933C (+1) are each referenced by two or more functions of 0x37B94..0x388D0; gcc 2.7.2 shares an anonymous literal only inside one translation unit, so every function between the first and last user is one TU.

Definitions retain retail order; declarations are reconciled in `include/town/shop/stat_display.h`, with explicit caller casts where required, preserving object bytes and relocations (proved by tools/tu/tu_merge.py). String literals stay retail imports until the whole TU and its pool extent are recovered (decision 72(f)).
