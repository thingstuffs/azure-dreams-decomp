"""Decision 54 precedence, drift, relocation and declaration-insertion checks."""
import copy
from pathlib import Path
from tempfile import TemporaryDirectory
from sdk_contracts import SDK
from contracts import bind
from twins import L

def run():
    sdk=SDK.__new__(SDK)
    address=0x80069EF8
    canonical=dict(row='sdk/rand',source='archive',name='rand',definition='s32 rand(void)',binding='psyq-sdk-matched-header',decision=54,declaration_policy='canonical-PsyQ-dominant-matched')
    sdk.contracts={address:canonical};sdk.symbols={address:dict(object='psyq/libc/C47')}
    with TemporaryDirectory(dir=L/'tmp') as tmp:
        sdk.base=Path(tmp);(sdk.base/'src/dungeon').mkdir(parents=True)
        (sdk.base/'src/dungeon/donor.c').write_text('s16 rand();\n')
        own=dict(row='dungeon/donor',source='src/dungeon/donor.c',name='rand',definition='s16 rand()')
        sdk.local={('dungeon/donor',address):[own]};sdk.authorities={}
        inherited=sdk.get(address,'dungeon/donor')
        assert inherited['definition']=='s16 rand()'
        assert sdk.proof(address,address,inherited)
        assert sdk.get(address,'other')==canonical
        assert sdk.proof(address,address,canonical)
        assert sdk.proof(address+4,address,canonical) is None
        assert sdk.proof(address,address+4,canonical) is None
        drift=dict(inherited,definition='s32 rand(void)')
        assert sdk.proof(address,address,drift) is None
        calls=[dict(source_callee=hex(address),encoded_callee=hex(address),contract=canonical)]
        text=bind('#include "common.h"\ns32 f(void) { return rand(); }\n',calls)
        assert 'extern s32 rand(void);' in text
        alias=bind('s32 f(void) { return func_80069EF8(); }\n',copy.deepcopy(calls))
        assert 'extern s32 func_80069EF8(void);' in alias
        both=bind('s32 f(void) { return rand()+func_80069EF8(); }\n',copy.deepcopy(calls))
        assert 'extern s32 rand(void);' in both and 'extern s32 func_80069EF8(void);' in both
        text='s16 rand();\ns32 f(void) { return rand(); }\n'
        assert bind(text,[dict(source_callee=hex(address),encoded_callee=hex(address),contract=inherited)])==text
        sdk.local[('dungeon/donor',address)].append(dict(own,definition='u32 rand(void)'))
        assert sdk.get(address,'dungeon/donor') is None
    assert SDK.abi(dict(name='RotTransPers',definition='long RotTransPers(SVECTOR *v, long *xy, long *p, long *flag)'))=='s32(void*,void*,void*,void*)'
    d=lambda value:dict(name='f',definition=value)
    votes=SDK.consensus([d('s32 f(s32)')]*2+[d('s32 f()')]*2+[d('void f(s32)')]*3,'s32(s32)')
    assert votes['s32(s32)']==4 and votes['void(s32)']==3
    votes=SDK.consensus([d('s32 f(s32)'),d('s32 f(void *)'),d('s32 f()')],'s32(s32)')
    assert votes['s32(unspecified)']==1
    votes=SDK.consensus([d('s32 f(s16)'),d('s32 f()')],'s32(s16)')
    assert votes['s32(s16)']==1 and votes['s32(unspecified)']==1
    print('decision54: 12 precedence/drift/relocation/declaration checks PASS')
    print('decision54: source/header and C89 consensus checks PASS')

def world_checks(world):
    sdk=world.sdk;checked=0
    for address,contract in sdk.contracts.items():
        assert sdk.proof(address,address,contract)
        assert sdk.proof(address,address+4,contract) is None
        changed=dict(contract,definition=contract['definition']+' invalid')
        assert sdk.proof(address,address,changed) is None
        checked+=1
    assert sdk.get(0x80069EF8)['definition']=='s32 rand(void)'
    assert sdk.get(0x800644B8)['definition']=='s32 rsin(s32)'
    assert len(world.byrow['dungeon/func_80E39504'])==1
    assert len(world.byrow['dungeon/func_818107C0'])==1
    from twins import save,L
    save(L/'evidence/decision54_tests.json',dict(passed=True,bound_symbols_checked=checked,
         checks=['unchanged resident addresses','SDK relocation refused','contract drift refused',
                 'rand/rsin canonical prototypes','true-address named donor definitions']))
    print('decision54: live authority and true-address alias checks PASS',checked,flush=True)

if __name__=='__main__':run()
