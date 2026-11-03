# TOWN diagnostic devkit reconstruction

The target census at the lane base found exactly one address-declared function without C, `func_80700188`, and six relocation-masked copy candidates. Data declarations are excluded from the function totals. The recorded regions and the internal calls establish linked addresses, not retail execution. The six existing 0x80700000 link-list views were sparse: most home rows were absent. This change gathers same-delta narrow entries and adds registered home entries, retaining distinct KSEG aliases in their existing views. Six complete diagnostic gate windows allow reproduction against the retail slices.

## Recovered flag propagation

TOWN file `0x832988..0x832A1C`, runtime `0x80700188..0x8070021C`, is `propagate_devkit_flag_pair(s32 index)`. It tests the signed flag ID in `D_A0700F1C[index]`, sets or clears the flag ID in `D_A0700F24[index]` accordingly, then sets the first flag. The bitmap helpers make the flag behavior explicit: zero is always clear, one is always set, setting zero and clearing one are suppressed. Its caller selects page zero before redrawing and scanning.

Ordinary array indexing, an if/else and three direct calls compile to all 148 retail bytes at stock GCC 2.6.3 -G0, linked at the true address. No register pins, goto, volatile or assembly are needed. The two table declarations preserve signed halfword loads. Registration records this as a new reconstruction, not an archived first-pass source.

## Shared C placements

Each candidate was checked against the current home object: every nonrelocation byte agrees, every relocation yields one consistent destination per symbol, and an independent GNU ld link with those bindings equals the complete destination function. Two additional helpers were exposed by the recovered function's calls; three more copies were found while retrying import floors. All eleven placements were checked in the same way.

| Destination | File offset | Bytes | Shared home source | Retail SHA-256 |
| --- | --- | ---: | --- | --- |
| func_8070021C | 0x832a1c | 136 | `src/town/devkit/check_devkit_secondary_condition.c` | `6e4ea97857169ee3d6e94c3f668c72301b4ed438a487c0824975114650ffbcf2` |
| func_80700C7C | 0x80347c | 96 | `src/town/shop/state/shop_test_indexed_flag.c` | `767953293570435b06a50bc3834ba0d20e110554ea4a9661628d07bb3d213bd7` |
| func_80700CD0 | 0x8014d0 | 80 | `src/town/shop/state/shop_set_indexed_flag.c` | `a93fc0c1dd48dd0e765915683744989703e7935cdabdc96aec45570a00ecb4f3` |
| func_80700CE8 | 0x7ffce8 | 112 | `src/town/scene/is_next_entry_zero_after_skipping_b.c` | `c9e8f0004b73119152a51a6c0a6110de91eaca4baee38dd687c218d437ac2f71` |
| func_80700D20 | 0x801520 | 84 | `src/town/scene/flags/clear_indexed_flag_bit_unless_index_one.c` | `414b50bb9f292f7ac7a4e5d2f8a0a9683a6c9d4162fb91506fd0469423557264` |
| func_80701134 | 0x800134 | 96 | `src/town/shop/state/shop_test_indexed_flag.c` | `6f08d1703735069606204c99996ec2f4699785814958299f09a3892fe4e55c43` |
| func_80700D1C | 0x83351c | 80 | `src/town/shop/state/shop_set_indexed_flag.c` | `919e973d82e31a9bd548390e9cdfb3142bf623dbba9f4a1fb6b7bc247587e1d2` |
| func_80700DC0 | 0x8335c0 | 96 | `src/town/shop/state/shop_test_indexed_flag.c` | `8c9b0d0ea661b120a835bc53a91741f46a000db70877e13db9b3a0b25d350aa9` |
| func_80000C6C | 0x83b46c | 96 | `src/town/shop/state/shop_test_indexed_flag.c` | `8845c1562c20e127e8ad99d2a25054219e01ada35d2eea072abffb396ce130ef` |
| func_A0700244 | 0x839244 | 148 | `src/town/scene/flags/dispatch_entry_test_flag.c` | `16583970f47d90ec2856cb6067704b6d7f78e7f5ac34dfb9594b596e11b59cce` |
| func_80700C54 | 0x7ffc54 | 148 | `src/town/scene/flags/dispatch_entry_test_flag.c` | `4ef5eaed0c7ac2434b4ade0347d833879d7135e9bb3cfa67ffc2b93217d296f2` |

Call sites use behavior names qualified by the runtime address for these distinct foreign builds. Names lower to their original destination address; placement objects still come from the existing home implementation. No copy-link opt-ins are added: the production same-image rule excludes these diagnostic devkit views, and several different programs occupy the same runtime window. This preserves the distinction between shared compiled C and an established runtime owner.

The complete windows import unreconstructed gaps from the user's disc; a full-window match is not a claim that those gaps have C bodies. The KSEG aliases at file 0x833104 and 0x833374 retain their separately evidenced views.

## Verification

The lane handoff records final integration commands and results. Before registration, an independent exact link proved the recovered 148-byte function; the same method proved all eleven placements (1172 bytes). Final make, decoded-image, native, debt, row-database, layout and graph results are recorded with the delivery.

Adding the home entries exposed 33 pre-existing placeholder split addresses. Each is promoted to its recorded region's true base, with a per-row proven rowbase record and the readable name lowered at that base. The complete diagnostic windows independently check these promotions.

The view-local mapping resolves three foreign-import floor names at four sites: `func_80700590` in the 0x832800 program is `dispatch_by_leading_id_flags`; `func_80700D84` in the 0x7F4000 program is `find_devkit_callback_value_index`; and both no-argument calls to `func_80701060` there are `dispatch_devkit_callback_by_run_length`. Other builds' same-address imports retain their separate declarations. The resolved floor records are retired from the active ledger.


The low-image floor `func_80000C6C` is a fourth resolved name: the body at file 0x83B46C is the full-width flag test, so a signed halfword argument can use the correct `s32` prototype without the old header's `u16` narrowing. Four callers use its qualified name; the recorded floor at `is_next_entry_zero_after_skipping` is retired.

Two other floor names now have C owners: the entry-pair dispatch copies at file 0x7FFC54 and 0x839244. Their callers now pass only the table index and include the owning flags header. The outer wrapper parameters remain for its callers, but the placed dispatcher never reads those surplus arguments. Removing their forwarding is byte-neutral at both production recipes; both floor records are retired. This closes all six flag-test floor names at seven sites.

The 0x839244 body links at 0xA0700244 in the uncached view. Its qualified call name preserves the callers' 0x80700244 cached spelling. These KSEG addresses name the same physical bytes and encode the same jump word; the body placement and caller checks are proved separately. No live execution claim follows from that alias relationship.

All seven remaining old-minigame import floors were retried at nine sites. Every control compile is calibrated against the current production compile. The shared prototype is rejected for argument count at all nine sites (seven too-many-argument sites and two too-few-argument sites). Direct one-argument call probes resolve the two dispatch sites without adding a variadic ABI. The external-import floors remain under their foreign-program header; the views in this change supply no body for those other executable/engine builds.

The two externally identified callees also received ordinary call-cleanup probes: removing the surplus `rand` arguments changes text bytes; removing the surplus sound-call arguments changes the caller section from 2396 to 2400 bytes. Those candidates are rejected and the original byte-sensitive declarations and calls remain.


## Final validation

- `make configure`, `make -j6`, `make -j6 check`: **1530/1530 images SHA-1 MATCH**, including SLUS; 8423 overlay recipes checked. The baseline's 1518 checks grow by twelve diagnostic row checks. All 21761 baseline rows remain; the registry now has 21773.
- Eight standalone diagnostic gates: **67732 bytes exact** (six complete 0x80700000 programs, the 0x83A800 low image and the 148-byte 0xA0700244 placement window).
- Decoded check: **1 image, 15 functions**, physical rows unchanged.
- Natcheck with the authorized native port and a private cache: **6083 units checked, zero contract, adaptation or unit failures** (6028 game, 2 decoded, 45 runtime, 8 fixtures).
- Row database, source layout, per-function debt ratchet and regenerated link-graph validation: **PASS**.
- Refreshed declared-function target census: **1087 targets, zero MISSING, zero DEV_COPY**. The required seven entries are diagnostic C (`C_STALE_ROW` under this tool's production-image classification).

The link graph was captured through its producer, preserving the recorded base, after registry and module-graph regeneration. No graph shard was hand-edited. No new goto, volatile, assembly, register pin, M2C construct or cast is used by the recovered function.
