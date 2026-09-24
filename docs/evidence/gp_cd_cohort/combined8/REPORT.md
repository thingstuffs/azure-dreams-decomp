# Private eight-function CD owner

`probe.py` assembles one CDK 2.7.2 `-G32` translation unit from the eight
frozen cohort inputs below. It keeps the eleven identical initialized globals
once, removes only duplicate declarations of the observed
`D_800814D3[2]` view, and preserves every function body. F240 comes from the
unchanged `code2` body and appears between E758 and F2A4 in the generated
source and generic object's function sections.

After projection through the eleven `data_pieces`, private generic and genuine
ASPSX 2.79 match all eight retail functions exactly: 1041 words, zero masks,
zero unmasked differences. Their 1041 function tokens agree. Stock is exact
for six functions; E758 emits 667 of 698 words and F368 emits 109 of 113.

| Function | Retail words | Stock exact | Generic exact | Genuine exact |
| --- | ---: | --- | --- | --- |
| E34C | 20 | yes | yes | yes |
| E4FC | 132 | yes | yes | yes |
| E758 | 698 | no | yes | yes |
| F240 | 12 | yes | yes | yes |
| F2A4 | 31 | yes | yes | yes |
| F368 | 113 | no | yes | yes |
| F5AC | 10 | yes | yes | yes |
| F624 | 25 | yes | yes | yes |

`module.json` is the proposed `cd_command_state` entry: seven whole members,
`src/cd_command_state_owned.c`, eleven named data pieces, and the common CDK
`-G32` recipe. `candidate_manifest.json` retains all 23 existing modules and
adds this entry. `candidate_partitions.json` retains both existing collector
parents and adds `func_8003F240` from `code2` to this module. The unchanged
`src/slus/code2.c` partition renderer emits exactly
`code2__cd_command_state.c` (SHA-256 below). `cd_command_state_owned.c` is the
production-shaped include aggregator; `members/w_*.c` are the seven canonical
member candidates. The standalone compiler proof uses the self-contained
`combined8.c`. The include-based generated build and full-image placement
remain to be measured after manifest review.

Frozen input SHA-256 values:

| Cohort source | SHA-256 |
| --- | --- |
| `e34c_driver_view.c` | `b2a0831df16e197f6cee9c1f7a3ee15f86869c80c8f536677402547d6f16e94f` |
| `w_8003E4FC_owned.c` | `291f05e79942228e2219617cc795198af24ec62e446bad1284c7e8e7e5542d84` |
| `e758_prefix_view.c` | `e46b83cfbf0560c0d32e961ea372ef32495ff33cf28fcac9bf57b0a52857fb85` |
| `f240_owned.c` | `fd2520894739effd99a2ae2ca6299bb9681902bab774d8713c6852f779e17cdf` |
| `f2a4_queue_view.c` | `5895816a752092e590e939803e08d5f60b47902bf4e73922277a76b1e0c30ec3` |
| `f368_address_views.c` | `07730fff2eacf4bb404cb50bac85ee106ede6da1f9b4f7d08a5b05f66ddeeed4` |
| `f5ac_driver_view.c` | `60405d53a746ac7d50f25d794090c1c706039e6fb4a38b68f36d489936562e3e` |
| `w_8003F624_owned.c` | `6935c3fdcaceaaa5446570f075c1f358843d18283dd7a4ab5f49d62a5c239952` |

The source and proposal hashes are `combined8.c`
`d535e5b06ad2757f49f5cbeda655a0964e52a8da7fc5c715cb3701839877fc63`,
`cd_command_state_owned.c`
`3a1a47fdaca76973cef226a7fb9acdc5d7cfe46cdb2cb62eee65da28aa716f6b`,
`module.json`
`ab3901f5cb82692d19bd98921f58268085b2aa0344d067dbc1933df31e7ba0a4`,
`candidate_partitions.json`
`f7161d7e42f1c8eb32c8b0d806d0642069d38e2edb21ef004e133e4675522e87`,
and `code2__cd_command_state.c`
`1a29119de5c8fc22122be81c0a307f993a7ef17cf8e324afab1c11a091b731ee`.
The complete measured function table and object hashes are in `receipt.json`.

Run `python3 work/native_lane/gp_cd_contract/combined8/probe.py` from the
repository root to regenerate the private proposal and measurement. No
production source, manifest, partition plan, or build was changed.
