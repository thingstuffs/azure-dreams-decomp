"""D0 adversarial token/ELF checks and lane orchestration. No retail data needed."""
import importlib.util
import json
import os
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
KIT = ROOT / 'tools/lanes/lanekit'
sys.path[:0] = [str(ROOT / 'tools'), str(KIT)]


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


R = load('test_rename_core', ROOT / 'tools/rename_proof.py')
P = load('test_rename_lane', KIT / 'rename_proof.py')


def elf(*, code=b'\x00' * 8, data=b'DATA', bss=4, alignment=4,
        target='callee', file='before.c', reloc_type=5, reloc_offset=0,
        reverse_relocs=False, symbol_size=8, binding=1, visibility=0,
        section_flags=6, machine=8, flags=0x1000, text_name='.text.f',
        common_size=0, rela_addend=None):
    """Small independent ELF writer: symbols, HI16/LO16, storage and NOBITS."""
    names = ['', text_name, '.data', '.bss', '.symtab', '.strtab', '.shstrtab',
             '.rela.text.f' if rela_addend is not None else '.rel.text.f']
    strings = b'\0'; symnames = {}
    for name in (file, 'f', target, 'static_value', 'common'):
        symnames[name] = len(strings); strings += name.encode() + b'\0'
    symbols = [(0, 0, 0, 0, 0, 0),
        (symnames[file], 0, 0, 4, 0, 0xfff1),
        (0, 0, 0, 3, 0, 1),
        (symnames['f'], 0, symbol_size, binding * 16 + 2, visibility, 1),
        (symnames[target], 0, 0, 16, 0, 0),
        (symnames['static_value'], 0, len(data), 1, 0, 2),
        (symnames['common'], 4, common_size, 17, 0, 0xfff2)]
    symtab = b''.join(struct.pack('<IIIBBH', *s) for s in symbols)
    shstrings = b'\0'; offsets = {'': 0}
    for name in names[1:]:
        offsets[name] = len(shstrings); shstrings += name.encode() + b'\0'
    rels = [(reloc_offset, 4 * 256 + reloc_type), (4, 4 * 256 + 6)]
    if reverse_relocs: rels.reverse()
    if rela_addend is None:
        rel = b''.join(struct.pack('<II', *x) for x in rels); stride = 8; rtype = 9
    else:
        rel = b''.join(struct.pack('<IIi', *x, rela_addend) for x in rels); stride = 12; rtype = 4
    bodies = [b'', code, data, b'', symtab, strings, shstrings, rel]
    types = [0, 1, 1, 8, 2, 3, 3, rtype]
    secflags = [0, section_flags, 3, 3, 0, 0, 0, 0]
    aligns = [0, alignment, 4, 4, 4, 1, 1, 4]
    links = [0, 0, 0, 0, 5, 0, 0, 4]
    infos = [0, 0, 0, 0, 3, 0, 0, 1]
    ents = [0, 0, 0, 0, 16, 0, 0, stride]
    payload = bytearray(b'\0' * 52); sections = []
    for i, body in enumerate(bodies):
        while len(payload) % max(aligns[i], 1): payload += b'\0'
        off = len(payload); payload += body
        sections.append((offsets[names[i]], types[i], secflags[i], 0, off,
            bss if i == 3 else len(body), links[i], infos[i], aligns[i], ents[i]))
    sections[0] = (0,) * 10
    while len(payload) % 4: payload += b'\0'
    shoff = len(payload)
    payload += b''.join(struct.pack('<IIIIIIIIII', *s) for s in sections)
    payload[:16] = b'\x7fELF\x01\x01\x01' + b'\0' * 9
    struct.pack_into('<HHIIIIIHHHHHH', payload, 16, 1, machine, 1, 0, 0, shoff,
                     flags, 52, 0, 0, 40, len(sections), 6)
    return bytes(payload)


class Tokens(unittest.TestCase):
    def check(self, a, b, mapping=None):
        return R.check_renames(a, b, mapping)

    def test_local_parameter_field_and_type_names(self):
        a = 'typedef struct S { int unk_0; } S; int f(S *p, int n) { int i; for (i=0;i<n;i++) p->unk_0+=i; return p->unk_0; }'
        b = a.replace('unk_0', 'flags').replace('S', 'State').replace(' n', ' count').replace('<n', '<count')
        got = self.check(a, b)
        self.assertEqual(got['renames'], {'S': 'State', 'n': 'count', 'unk_0': 'flags'})

    def test_comments_whitespace_and_identifier_substrings(self):
        a = 'int f(int x) { /* x */ return x + x_other; }'
        b = 'int f(int value) { // explain x\n return value + x_other; }'
        self.assertEqual(self.check(a, b)['renames'], {'x': 'value'})
        self.assertEqual(self.check('int x;', '/* why */ int  x;\n')['renames'], {})

    def test_literals_and_keywords_are_immutable(self):
        for a, b in [('int x=1;', 'int x=2;'), ('int x=0x10;', 'int x=16;'),
            ('int x=1e+2;', 'int x=1e-2;'), ('int x=1.0f;', 'int x=1.0;'),
            ('char *s="x";', 'char *s="value";'), ("int x='a';", "int x='b';"),
            ('int f(){return 1;}', 'int f(){return 1u;}'), ('int x;', 'unsigned x;'),
            ('volatile int x;', 'const int x;'), ('asm("x");', 'asm("y");'),
            ('L"x";', '"x";'), ('int x;', 'int return;')]:
            with self.subTest(a=a), self.assertRaises(R.Refusal): self.check(a,b)

    def test_operators_insert_delete_and_control_flow_refuse(self):
        for a, b in [('x++;','x--;'), ('x += y;','x = y;'), ('x->f;','x.f;'),
            ('if(x) f();','while(x) f();'), ('a + +b;','a++ + b;'),
            ('return x;','return (x);'), ('x; y;','y;'), ('int *x;', 'int x;')]:
            with self.subTest(a=a), self.assertRaises(R.Refusal): self.check(a,b)

    def test_renames_are_consistent_injective_and_capture_free(self):
        for a,b in [('int x; x=x;', 'int y; y=x;'), ('int x,y;', 'int z,z;'),
            ('int x,y;', 'int y,x;'), ('int x,y;', 'int y,z;')]:
            with self.subTest(a=a), self.assertRaises(R.Refusal): self.check(a,b)

    def test_allowlist_must_match_exactly(self):
        self.assertEqual(self.check('int x;', 'int y;', {'x':'y'})['renames'], {'x':'y'})
        for mapping in ({}, {'x':'z'}, {'x':'y','unused':'other'}, {'int':'x'}, {'x':'return'}, {'x':3}, ['x']):
            with self.subTest(mapping=mapping), self.assertRaises(R.Refusal): self.check('int x;', 'int y;', mapping)

    def test_directive_tokens_boundaries_and_macro_adjacency(self):
        for a,b in [('#define X 1\nint x;', '#define X 2\nint x;'),
            ('#define X x\nint x;', '#define X y\nint y;'),
            ('#define F(x) x\n', '#define F (x) x\n'),
            ('#include "a.h"\n','#include "b.h"\n'),
            ('#include <a/b.h>\n','#include <a /b.h>\n'),
            ('#if X\nf();\n#endif\n', '#if Y\nf();\n#endif\n'),
            ('#define F x\nf();', '#define F x f();'),
            ('%:define X 1\n','%:define X 2\n')]:
            with self.subTest(a=a), self.assertRaises(R.Refusal): self.check(a,b)
        self.check('#include "a.h"\nint x;', '#include "a.h"\nint y;')
        self.check('#define X 1\n', '#define X /* why */ 1\n')

    def test_translation_phases_prevent_comment_or_splice_tricks(self):
        self.check('int fo\\\no;', 'int value;')
        self.check('int x; // ignored \\\n x++\n', 'int x; // ignored\n')
        for a,b in [('int x; /* a */ x++;', 'int x; // a x++;'),
            ('int x;', 'int x; /* unfinished'), ('int x;', 'int x; ??/\n'),
            ('#define X /*\n*/ x\n', '#define X /*\n*/ y\n'),
            ('int x;', 'int café;'), ('int x;', 'int \\u1234;')]:
            with self.subTest(a=a), self.assertRaises(R.Refusal): self.check(a,b)


class Objects(unittest.TestCase):
    def test_file_symbol_difference_does_not_change_payload(self):
        a,b=elf(),elf(file='a_different_directory/after.c')
        self.assertNotEqual(a,b)
        self.assertTrue(R.compare_objects(a,b)['equal'])

    def test_storage_geometry_relocations_and_symbols_all_matter(self):
        variants = [dict(code=b'\x01'+b'\0'*7),dict(data=b'FAIL'),dict(bss=8),
            dict(alignment=8),dict(section_flags=2),dict(target='other'),dict(reloc_type=4),
            dict(reloc_offset=1),dict(reverse_relocs=True),dict(symbol_size=4),
            dict(binding=2),dict(visibility=2),dict(flags=0x1001),dict(text_name='.text.g'),
            dict(common_size=8)]
        for variant in variants:
            with self.subTest(variant=variant):
                self.assertFalse(R.compare_objects(elf(),elf(**variant))['equal'])

    def test_rela_addend_is_never_masked(self):
        self.assertFalse(R.compare_objects(elf(rela_addend=0),elf(rela_addend=4))['equal'])

    def test_equality_compares_bytes_in_addition_to_hashes(self):
        with patch.object(R,'sha',return_value='same-hash'):
            self.assertFalse(R.compare_objects(elf(data=b'AAAA'),elf(data=b'BBBB'))['equal'])

    def test_malformed_and_unsupported_objects_fail_closed(self):
        cases=[b'',b'not elf',elf()[:60],elf(machine=62),elf(section_flags=0x202)]
        bad=bytearray(elf());struct.pack_into('<I',bad,32,0x7fffffff);cases.append(bytes(bad))
        for data in cases:
            with self.subTest(size=len(data)),self.assertRaises(R.Refusal):R.object_identity(data)


class Workflow(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.lane=self.root/'lane';(self.lane/'tmp').mkdir(parents=True)
        self.source=self.root/'src/town/f.c';self.source.parent.mkdir(parents=True)
        self.before=self.root/'before.c';self.after=self.root/'after.c'
        self.base='int f(int x) { return x+1; }\n';self.new=self.base.replace('x','count')
        self.source.write_text(self.base);self.before.write_text(self.base);self.after.write_text(self.new)
        self.row=dict(id='town/f',kind='overlay',container='town',c_path='f.c',cfg='2.7.2-G0',cell='2.7.2')
        self.addCleanup(patch.stopall)
        patch.object(P.kitlib,'ROOT',self.root).start()
        import common
        patch.object(common,'clean_path',return_value=self.source).start()
        self.state=patch.object(P,'input_state',return_value={'recipe':'stable'}).start()
        self.compile=patch.object(P,'compile_row',side_effect=self.emit).start()
        self.verify=patch.object(P,'row_verify',return_value={'exact':True}).start()

    def emit(self,row,source,out,inc):
        out.mkdir(parents=True)
        obj=out/'f.o';obj.write_bytes(elf(file=source.as_posix()))
        (out/'dependencies.json').write_text(json.dumps({str(source.relative_to(self.root)):R.sha(source.read_bytes())}))
        return {'f':obj}

    def prove(self,**kw):
        return P.prove(self.row,self.before,self.after,self.lane,**kw)

    def test_success_requires_both_compiles_and_both_row_verifies(self):
        result=self.prove(stage=True)
        self.assertTrue(result['exact']);self.assertTrue(result['neutral'])
        self.assertEqual(self.compile.call_count,2);self.assertEqual(self.verify.call_count,2)
        dest=self.lane/'out/town/f.c'
        self.assertEqual(dest.read_text(),self.new)
        self.assertEqual(dest.with_name('f.c.base_sha').read_text().strip(),R.sha(self.base.encode()))
        receipt=json.loads(dest.with_name('f.c.rename_proof.json').read_text())
        self.assertTrue(receipt['exact']);self.assertEqual(receipt['after_sha256'],R.sha(self.new.encode()))
        self.assertTrue((self.lane/result['artifacts']/'proof.json').exists())

    def test_nonrename_and_stale_base_never_compile_or_stage(self):
        self.after.write_text(self.new.replace('+1','+2'))
        with self.assertRaises(ValueError):self.prove(stage=True)
        self.after.write_text(self.new);self.source.write_text('changed')
        with self.assertRaisesRegex(ValueError,'stale base'):self.prove(stage=True)
        self.assertFalse(self.compile.called);self.assertFalse((self.lane/'out').exists())

    def test_object_drift_prevents_verification_and_staging(self):
        def emit(row,source,out,inc):
            result=self.emit(row,source,out,inc)
            if '/after/' in str(source):result['f'].write_bytes(elf(target='other'))
            return result
        self.compile.side_effect=emit
        result=self.prove(stage=True)
        self.assertFalse(result['exact']);self.assertFalse(result['neutral'])
        self.assertFalse(self.verify.called);self.assertFalse((self.lane/'out').exists())

    def test_compile_failure_and_nonexact_verifier_fail_closed(self):
        self.compile.side_effect=ValueError('no build')
        result=self.prove(stage=True);self.assertFalse(result['exact']);self.assertIn('no build',result['refused'])
        self.compile.side_effect=self.emit;self.verify.return_value={'exact':False}
        result=self.prove(stage=True);self.assertTrue(result['neutral']);self.assertFalse(result['exact'])
        self.assertFalse((self.lane/'out').exists())

    def test_context_or_source_drift_refuses_staging(self):
        self.state.side_effect=[{'recipe':'stable'},{'recipe':'changed'}]
        result=self.prove(stage=True);self.assertFalse(result['exact']);self.assertIn('inputs changed',result['refused'])
        self.state.side_effect=None
        def changed(*args,**kwargs):
            self.after.write_text('different');return {'exact':True}
        self.verify.side_effect=changed
        self.assertFalse(self.prove(stage=True)['exact'])
        self.assertFalse((self.lane/'out').exists())

    def test_different_existing_stage_is_preserved(self):
        dest=self.lane/'out/town/f.c';dest.parent.mkdir(parents=True);dest.write_text('other candidate')
        result=self.prove(stage=True)
        self.assertFalse(result['exact']);self.assertEqual(dest.read_text(),'other candidate')

    def test_receipt_reuse_rechecks_actual_objects_and_source(self):
        result=self.prove()
        receipt=self.lane/result['artifacts']/'proof.json'
        self.assertTrue(P.validate_receipt(self.row,self.before,self.after,self.lane,receipt)['exact'])
        pair=next(iter(result['object_paths'].values()))
        (self.lane/result['artifacts']/pair['after']).write_bytes(elf(target='other'))
        with self.assertRaisesRegex(ValueError,'object evidence changed'):
            P.validate_receipt(self.row,self.before,self.after,self.lane,receipt)
        self.after.write_text('changed')
        with self.assertRaisesRegex(ValueError,'source hashes'):
            P.validate_receipt(self.row,self.before,self.after,self.lane,receipt)

    def test_receipt_refuses_context_drift_and_path_escape(self):
        result=self.prove();receipt=self.lane/result['artifacts']/'proof.json'
        self.state.return_value={'recipe':'new'}
        with self.assertRaisesRegex(ValueError,'inputs are stale'):
            P.validate_receipt(self.row,self.before,self.after,self.lane,receipt)
        self.state.return_value={'recipe':'stable'}
        result['artifacts']='../outside';receipt.write_text(json.dumps(result))
        with self.assertRaisesRegex(ValueError,'escapes'):
            P.validate_receipt(self.row,self.before,self.after,self.lane,receipt)

    def test_header_overlay_checked_on_both_sides(self):
        live=self.root/'include/state.h';live.parent.mkdir();live.write_text('struct State { int unk; };\n')
        old=self.root/'old.h';new=self.root/'new.h';old.write_bytes(live.read_bytes())
        new.write_text('struct State { int flags; };\n')
        headers={'state.h':{'before':str(old),'after':str(new)}}
        result=self.prove(headers=headers)
        self.assertTrue(result['exact']);self.assertEqual(result['headers']['state.h']['renames'],{'unk':'flags'})
        incs=[call.args[3] for call in self.compile.call_args_list]
        self.assertEqual((incs[0]/'state.h').read_bytes(),old.read_bytes())
        self.assertEqual((incs[1]/'state.h').read_bytes(),new.read_bytes())
        new.write_text('struct State { long flags; };\n')
        with self.assertRaises(ValueError):self.prove(headers=headers)

    def test_unsafe_header_and_header_staging_are_refused(self):
        for name in ('../escape.h','/absolute.h','not_a_header.c'):
            with self.subTest(name=name),self.assertRaises(ValueError):P.safe_header(name)


class Adapters(unittest.TestCase):
    def test_header_verifier_uses_snapshot_as_actual_view_include(self):
        import verify
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);standing=root/'standing';standing.mkdir()
            (standing/'include').mkdir();(standing/'include/state.h').write_text('old header')
            (standing/'tools').mkdir();(standing/'tools/match.py').write_text('# view tool')
            (standing/'config').mkdir();(standing/'work').mkdir()
            inc=root/'snapshot';inc.mkdir();(inc/'state.h').write_text('new header')
            candidate=root/'row.c';candidate.write_text('int f();')
            def score(row,cfile,*,include_root,scorer_root):
                self.assertEqual((scorer_root/'include/state.h').read_text(),'new header')
                self.assertEqual((standing/'include/state.h').read_text(),'old header')
                self.assertEqual((scorer_root/'config').resolve(),(standing/'config').resolve())
                self.assertNotEqual((scorer_root/'work').resolve(),(standing/'work').resolve())
                self.assertFalse((scorer_root/'tools/match.py').is_symlink())
                return {'exact':True}
            with patch.object(verify,'gate_root',return_value=standing),patch.object(verify,'verify_overlay',side_effect=score):
                self.assertTrue(P.row_verify({'kind':'overlay'},candidate,inc)['exact'])

    def test_slus_adapter_keeps_every_physical_unit_and_failure(self):
        import verify
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'row.c';source.write_text('int f();')
            units=[dict(source=n,object=root/(n+'.o'),cfile=source,
                        recipe=dict(ccver='2.7.2',ccflags='-G0')) for n in ('one','two')]
            with patch.object(verify,'compile_slus_units',return_value=(units,None)),patch.object(P,'dependency_state',return_value={'fixture':'hash'}):
                self.assertEqual(set(P.compile_row({'kind':'slus'},source,root/'out')),{'one','two'})
            with patch.object(verify,'compile_slus_units',return_value=(None,'plural failure')):
                with self.assertRaisesRegex(ValueError,'plural failure'):
                    P.compile_row({'kind':'slus'},source,root/'error')

    def test_native_adapter_compares_untrimmed_physical_object(self):
        import native_member as N
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'row.c';source.write_text('int f();')
            with patch.object(N,'membership',return_value={'source':'src/module.c'}),patch.object(N,'compile_object') as compile,patch.object(P,'dependency_state',return_value={'fixture':'hash'}):
                result=P.compile_row({'kind':'overlay'},source,root/'out')
                self.assertEqual(result,{'src/module.c':root/'out/module.untrimmed.o'})
                self.assertEqual(compile.call_count,1)
                with self.assertRaisesRegex(ValueError,'complete TU batch'):
                    P.compile_row({'kind':'overlay'},source,root/'overlay',root/'headers')

    def test_install_table_exposes_d0_commands(self):
        import install
        self.assertIn('{kit}/rename_proof.py',install.TEMPLATE)
        self.assertIn('--receipt',install.TEMPLATE)

    def test_dependency_closure_is_bound_and_rechecked(self):
        import verify
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'row.c';source.write_text('int f();')
            header=root/'state.h';header.write_text('int x;')
            output='row.o: '+str(source)+' \\\n '+str(header)+'\n'
            with patch.object(P.kitlib,'ROOT',root),patch.object(P.subprocess,'run',return_value=SimpleNamespace(returncode=0,stdout=output,stderr='')):
                deps=P.dependency_state({'cell':'2.7.2','flags':'-G0'},source,root)
                self.assertEqual(set(deps),{'row.c','state.h'})
                P.dependencies_fresh(deps)
                header.write_text('long x;')
                with self.assertRaisesRegex(ValueError,'dependency changed'):P.dependencies_fresh(deps)

    def test_dependency_outside_checkout_refuses(self):
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'row.c';source.write_text('int f();')
            with patch.object(P.kitlib,'ROOT',root),patch.object(P.subprocess,'run',return_value=SimpleNamespace(returncode=0,stdout='row.o: /outside/header.h\n',stderr='')):
                with self.assertRaisesRegex(ValueError,'outside private checkout'):
                    P.dependency_state({'cell':'2.7.2','flags':''},source,root)


if __name__ == '__main__':
    unittest.main()
