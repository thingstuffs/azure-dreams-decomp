# Select dungeon spawn tiles and advance staged entity loading.



2 functions (foff 0xBF6CC-0xBFF30) of one original translation unit. Literal-pool ownership (dungeon/engine, g0246): string literals 0x80089000 are each referenced by two or more functions of 0xBC5EC..0xC0DA8; gcc 2.7.2 shares an anonymous literal only inside one translation unit, so every function between the first and last user is one TU.

Definitions retain retail order; declarations are reconciled in `include/dungeon/actor/entity_spawn_load.h`, with explicit caller casts where required, preserving object bytes and relocations (proved by tools/tu/tu_merge.py). String literals stay retail imports until the whole TU and its pool extent are recovered (decision 72(f)).
