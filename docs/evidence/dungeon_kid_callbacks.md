# Kid movement completion in Dungeon resource 4

The three 56-byte entries in each resource 4 slot call resident movement
steps in order: `interpolate_actor_to_terrain_tile`,
`update_spinning_actor_fall`, and `update_actor_fade_in`. Each tests the
step's return value and, on completion, stores the slot's Kid updater at
actor offset `0x8c`. The resident call targets are `0x800ac480`,
`0x800ac5c8`, and `0x800ace34` respectively. The fade-in step reads three
arguments. The other two steps read the fourth argument as well.

| Slot | DUNGEON bank offset | Load address | Constructor loads updater | Kid updater offset / address | First completion entry |
|---|---|---|---|---|---|
| 0 | `0xa13000` | `0x80170800` | `0xa13274` | `0xa13c00` / `0x80171400` | `0xa16b44` |
| 1 | `0xa19000` | `0x8016a800` | `0xa19274` | `0xa19c00` / `0x8016b400` | `0xa1cb44` |
| 2 | `0xa1f000` | `0x80164800` | `0xa1f274` | `0xa1fc00` / `0x80165400` | `0xa22b44` |
| 3 | `0xa25000` | `0x8015e800` | `0xa25274` | `0xa25c00` / `0x8015f400` | `0xa28b44` |
| 4 | `0xa2b000` | `0x80158800` | `0xa2b274` | `0xa2bc00` / `0x80159400` | `0xa2eb44` |
| 5 | `0xa31000` | `0x80152800` | `0xa31274` | `0xa31c00` / `0x80153400` | `0xa34b44` |
| 6 | `0xa37000` | `0x8014c800` | `0xa37274` | `0xa37c00` / `0x8014d400` | `0xa3ab44` |

The loader transfers twelve sectors per slot. The diagnostic views named
`bank_a20000` and `bank_a32000` begin two sectors into slots 2 and 5. Their
callback addresses point into the earlier sectors of the same transfer.
See the resource 4 slot rows in `config/census/cd_bank_map.json` and the
`bank_a1f000_prefix` and `bank_a31000_prefix` proven rowbase records.

Each 1,376-byte updater matches the slot 0 updater after masking address
relocations. Every changed address follows the corresponding slot's load
delta. The three source homes are in slot 0. Across all 21 entries only
the updater address moves relative to its source home. The resident step
addresses stay fixed, and the complete links reproduce the retail words.
