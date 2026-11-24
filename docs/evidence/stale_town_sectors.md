# Stale Town code in DUNGEON.BIN

These fragments are tails of TOWN.BIN code at the same physical offsets. Their
bytes remain in the retail image as stale sector contents.

| DUNGEON offset | Size | Equal words in TOWN at the same offset |
|---|---:|---:|
| `0x16ae8` | 32 | 8 of 8 |
| `0x1e0f4` | 148 | 35 of 37 |
| `0x20e20` | 404 | 101 of 101 |
| `0x4dae0` | 60 | 15 of 15 |

The fragment at `0x1e0f4` ends in the return from the TOWN function
`func_8009E0C8`. The words at `0x1e0f4` and `0x1e0f8` differ. The
following 35 words, through the return and its delay slot at `0x1e184`,
match the Town bytes. The fragment has no independent function entry. The
game-code census records it as stale sector contents.
