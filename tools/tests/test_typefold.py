"""T0 view folding, union resolution, record shims, and guarded delivery."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT/'tools/consolidate'))
from typefold import Catalog, Expressions, Parser, Refuse, canon, constant, fold_one, layout_map, sha
from typefold_cli import emit_package, rename_record
from guarded_apply import apply


class FoldTests(unittest.TestCase):
    def fold(self, src, dest, body):
        p = Parser(); p.parse(dest, 'shared/demo.h'); p.parse(src)
        source=p.types['S_80000000_0']; target=p.types['Demo']
        mp,_=layout_map(source,target)
        return fold_one(src+'\n'+body,p.types,source,target,mp)

    def test_pointer_cast_renames_members_preserves_trivia(self):
        src='typedef struct S_80000000_0 { s16 unk_00; s16 unk_02; } S_80000000_0;'
        dest='typedef struct Demo { short x; short y; } Demo;'
        out=self.fold(src,dest,'/* S_80000000_0 unk_00 */\nint f(void *p) { return ((S_80000000_0 *)p)->unk_02; }\nchar *s="unk_00 S_80000000_0";')
        self.assertIn('((Demo *)p)->y',out)
        self.assertIn('/* S_80000000_0 unk_00 */',out)
        self.assertIn('"unk_00 S_80000000_0"',out)
        self.assertNotIn('typedef struct',out)

    def test_typed_pointer_and_dynamic_outer_index(self):
        out=self.fold('typedef struct S_80000000_0 { s32 unk_00; } S_80000000_0;',
                      'typedef struct Demo { int value; } Demo;',
                      'int f(S_80000000_0 *p, int i) { return p[i].unk_00 + p->unk_00 + (*p).unk_00; }')
        self.assertIn('Demo *p',out)
        self.assertIn('p[i].value + p->value + (*p).value',out)

    def test_const_outer_pointer_is_preserved(self):
        out=self.fold('typedef struct S_80000000_0 { int x; } S_80000000_0;',
                      'typedef struct Demo { int x; } Demo;',
                      'int f(const S_80000000_0 *p) { return p->x; }')
        self.assertIn('const Demo *p',out)

    def test_tagged_cast(self):
        out=self.fold('typedef struct S_80000000_0 { int a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'int f(void *p) { return ((struct S_80000000_0 *)p)->a; }')
        # A typedef target can be anonymous: never manufacture `struct Demo`.
        self.assertIn('((Demo *)p)->b',out)

    def test_tag_alias_different_from_typedef_name(self):
        out=self.fold('typedef struct LegacyTag { int a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'int f(void *p) { return ((struct LegacyTag *)p)->a; }')
        self.assertIn('((Demo *)p)->b',out)
        self.assertNotIn('LegacyTag',out)

    def test_resolve_union_used_arm_into_true_field(self):
        out=self.fold('typedef struct S_80000000_0 { union { s32 s; u32 u; } unk_00; } S_80000000_0;',
                      'typedef struct Demo { int value; } Demo;',
                      'int f(void *p) { return ((S_80000000_0 *)p)->unk_00.s; }')
        self.assertIn('((Demo *)p)->value',out)
        self.assertNotIn('.s;',out)

    def test_union_incompatible_used_arm_refused(self):
        with self.assertRaisesRegex(Refuse,'union alternative'):
            self.fold('typedef struct S_80000000_0 { union { s32 s; u32 u; } a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'int f(void *p) { return ((S_80000000_0 *)p)->a.u; }')

    def test_whole_union_refused(self):
        with self.assertRaisesRegex(Refuse,'whole aggregate'):
            self.fold('typedef struct S_80000000_0 { union { int s; unsigned int u; } a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'void f(S_80000000_0 *p) { consume(p->a); }')

    def test_nested_target_path(self):
        out=self.fold('typedef struct S_80000000_0 { int a; } S_80000000_0;',
                      'typedef struct Demo { union { int value; unsigned int flags; } word; } Demo;',
                      'int f(void *p) { return ((S_80000000_0 *)p)->a; }')
        self.assertIn('->word.value',out)

    def test_array_shape_and_dynamic_index_preserved(self):
        out=self.fold('typedef struct S_80000000_0 { s16 a[3]; } S_80000000_0;',
                      'typedef struct Demo { short xyz[3]; } Demo;',
                      'int f(S_80000000_0 *p, int i) { return p->a[i]; }')
        self.assertIn('p->xyz[i]',out)

    def test_shadowing_refused(self):
        with self.assertRaisesRegex(Refuse,'shadowed'):
            self.fold('typedef struct S_80000000_0 { int a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'int f(S_80000000_0 *p) { { int *p; p=0; } return p->a; }')

    def test_unresolved_conditional_member_base_refused(self):
        with self.assertRaisesRegex(Refuse,'unresolved member base'):
            self.fold('typedef struct S_80000000_0 { int a; } S_80000000_0;',
                      'typedef struct Demo { int b; } Demo;',
                      'int f(S_80000000_0 *p, int b) { return (b ? p : p)->a; }')

    def test_primitive_mismatches_do_not_fold(self):
        cases=[('int a;', 'unsigned int b;'),('float a;','int b;'),('void *a;','int *b;'),
               ('volatile int a;','int b;'),('const int *a;','int *b;'),
               ('int a[2];','int b; int c;'),('long a;','int b;'),('int (*a)(int);','int (*b)(void *);')]
        for src,dest in cases:
            with self.subTest(src=src), self.assertRaises(Refuse):
                self.fold('typedef struct S_80000000_0 { '+src+' } S_80000000_0;',
                          'typedef struct Demo { '+dest+' } Demo;',
                          'int f(void *p) { return ((S_80000000_0 *)p)->a; }')

    def test_size_and_alignment_are_not_just_access_width(self):
        with self.assertRaisesRegex(Refuse,'size/alignment'):
            self.fold('typedef struct S_80000000_0 { char pad_00[2]; short a; } S_80000000_0;',
                      'typedef struct Demo { int value; } Demo;', 'void f(void) {}')

    def test_safe_integer_bounds_and_abi(self):
        self.assertEqual(constant('0x20 - 4'),28)
        self.assertEqual(constant('0'),0)
        for expr in ('__import__("os").system("false")','1/0','1<<100','-1'):
            with self.subTest(expr=expr),self.assertRaises((Refuse,SyntaxError)): constant(expr)
        p=Parser(); p.parse('typedef struct Demo { char c; double d; } Demo;')
        self.assertEqual((p.types['Demo'].fields['d'][0],p.types['Demo'].align),(8,8))

    def test_padding_can_be_view_hole_but_not_accessed(self):
        src='typedef struct S_80000000_0 { char pad_00[4]; int a; } S_80000000_0;'
        dest='typedef struct Demo { int x; int y; } Demo;'
        with self.assertRaisesRegex(Refuse,'extra named leaf'):
            self.fold(src,dest,'int f(S_80000000_0 *p) { return p->a; }')
        dest='typedef struct Demo { char pad_00[4]; int y; } Demo;'
        self.assertIn('->y',self.fold(src,dest,'int f(S_80000000_0 *p) { return p->a; }'))
        with self.assertRaisesRegex(Refuse,'unmapped member'):
            self.fold(src,dest,'int f(S_80000000_0 *p) { return p->pad_00[0]; }')

    def test_union_destination_cannot_name_padding_only_regions(self):
        with self.assertRaisesRegex(Refuse,'extra named leaf'):
            self.fold('typedef struct S_80000000_0 { char pad_00[4]; int a; } S_80000000_0;',
                      'typedef struct Demo { union { int v; unsigned int u; } word; int b; } Demo;',
                      'int f(S_80000000_0 *p) { return p->a; }')

    def test_conditional_duplicate_and_conditional_member_refused(self):
        p=Parser()
        text='typedef struct S_80000000_0 { int a; } S_80000000_0;'
        p.parse('#if X\n'+text+'\n#else\n'+text+'\n#endif')
        self.assertNotIn('S_80000000_0',p.types)
        self.assertTrue(any('duplicate' in e['reason'] for e in p.errors))
        p=Parser();p.parse('typedef struct S_80000000_0 {\n#if X\nint a;\n#endif\n} S_80000000_0;')
        self.assertNotIn('S_80000000_0',p.types)

    def test_byvalue_and_unsupported_declarations_refused(self):
        for body in ('void f(void) { S_80000000_0 a; }','void f(void) { S_80000000_0 *a, *b; }'):
            with self.subTest(body=body),self.assertRaises(Refuse):
                self.fold('typedef struct S_80000000_0 { int a; } S_80000000_0;',
                          'typedef struct Demo { int b; } Demo;',body)
        p=Parser();p.parse('typedef struct S_80000000_0 { unsigned flags:1; } S_80000000_0;')
        self.assertTrue(p.errors)


class PackageTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(); self.addCleanup(self.tmp.cleanup)
        self.base=Path(self.tmp.name); self.root=self.base/'root'; self.root.mkdir()
        (self.root/'file.c').write_text('before\n')
        (self.root/'guard.h').write_text('unchanged\n')
        self.package=self.base/'package'

    def emit(self):
        emit_package(self.root,self.package,{'file.c':'after\n','new.h':'new\n'}, {},['guard.h'])

    def test_dry_run_wins_and_live_is_idempotent(self):
        self.emit(); r=apply(self.package,self.root,live=True,dry_run=True)
        self.assertEqual(r['mode'],'dry-run'); self.assertEqual((self.root/'file.c').read_text(),'before\n')
        self.assertFalse((self.root/'new.h').exists())
        self.assertEqual(apply(self.package,self.root,live=True)['changed'],2)
        self.assertEqual(apply(self.package,self.root,live=True)['changed'],0)
        self.assertEqual((self.root/'file.c').read_text(),'after\n')

    def test_all_guards_checked_before_any_mutation(self):
        self.emit();(self.root/'guard.h').write_text('stale')
        with self.assertRaisesRegex(ValueError,'dependency hash'): apply(self.package,self.root,live=True)
        self.assertEqual((self.root/'file.c').read_text(),'before\n');self.assertFalse((self.root/'new.h').exists())

    def test_payload_and_before_guard(self):
        self.emit();(self.root/'file.c').write_text('stale')
        with self.assertRaisesRegex(ValueError,'before hash'): apply(self.package,self.root,live=True)
        (self.root/'file.c').write_text('before\n');(self.package/'payload/file.c').write_text('corrupt')
        with self.assertRaisesRegex(ValueError,'payload hash'): apply(self.package,self.root,live=True)

    def test_path_escape_and_symlink_refused(self):
        self.emit();m=json.loads((self.package/'manifest.json').read_text())
        m['files'][0]['path']='../escape';(self.package/'manifest.json').write_text(json.dumps(m))
        with self.assertRaisesRegex(ValueError,'unsafe path'): apply(self.package,self.root,live=True)
        m['files'][0]['path']='file.c';(self.package/'manifest.json').write_text(json.dumps(m))
        (self.root/'file.c').unlink();(self.root/'file.c').symlink_to(self.root/'guard.h')
        with self.assertRaisesRegex(ValueError,'symlink'): apply(self.package,self.root,live=True)

    def test_cli_generates_a_reviewed_fold_package(self):
        inc=self.root/'include/shared';inc.mkdir(parents=True)
        (inc/'demo.h').write_text('typedef struct Demo { int value; } Demo;\n')
        src=self.root/'src/town';src.mkdir(parents=True)
        code='typedef struct S_80000000_0 { int a; } S_80000000_0;\nint f(S_80000000_0 *p) { return p->a; }\n'
        (src/'f.c').write_text(code)
        (self.root/'ledger').mkdir()
        (self.root/'ledger/rows.jsonl').write_text(json.dumps({'id':'town/f'})+'\n')
        select=self.base/'select.json';select.write_text(json.dumps({'town/f|S_80000000_0':'Demo'}))
        proc=subprocess.run([sys.executable,str(ROOT/'tools/consolidate/consolidate.py'),'--root',str(self.root),
                             'generate','--row','town/f','--select',str(select),'--out',str(self.package)],capture_output=True,text=True)
        self.assertEqual(proc.returncode,0,proc.stderr)
        self.assertEqual(json.loads(proc.stdout)['rows'],['town/f'])
        apply(self.package,self.root,live=True,dry_run=True)
        self.assertEqual((src/'f.c').read_text(),code)
        apply(self.package,self.root,live=True)
        self.assertIn('Demo *p',(src/'f.c').read_text())
        self.assertIn('p->value',(src/'f.c').read_text())

    def test_cli_accepts_live_and_dryrun_together(self):
        self.emit()
        proc=subprocess.run([sys.executable,str(self.package/'apply.py'),'--root',str(self.root),'--live','--dry-run'],capture_output=True,text=True)
        self.assertEqual(proc.returncode,0,proc.stderr)
        self.assertEqual(json.loads(proc.stdout)['mode'],'dry-run')

    def test_record_semantic_name_shim_compiles_both_include_orders(self):
        inc=self.root/'include/records';inc.mkdir(parents=True)
        (inc/'Rec_D_80000000.h').write_text('#ifndef REC_D_80000000_H\n#define REC_D_80000000_H\ntypedef struct Rec_D_80000000 { int value; } Rec_D_80000000;\n#endif\n')
        (self.root/'knowledge').mkdir();(self.root/'knowledge/role.md').write_text('Fixture evidence')
        c=Catalog(self.root)
        args=argparse.Namespace(old='Rec_D_80000000',name='Demo',evidence='knowledge/role.md',confidence='medium',out=self.package)
        rename_record(c,args);apply(self.package,self.root,live=True)
        for order in [('Demo','Rec_D_80000000'),('Rec_D_80000000','Demo')]:
            code=''.join('#include "records/'+n+'.h"\n' for n in order)
            code+='struct Rec_D_80000000 *old_tag; Rec_D_80000000 *old_type; Demo *new_type;\nint f(void) { new_type=old_type; old_tag=new_type; return sizeof(Demo)==sizeof(Rec_D_80000000); }\n'
            proc=subprocess.run(['cc','-x','c','-fsyntax-only','-Werror','-I',str(self.root/'include'),'-'],input=code,text=True,capture_output=True)
            self.assertEqual(proc.returncode,0,proc.stderr)
        self.assertIn('knowledge/role.md', (self.root/'ledger/type_unification.jsonl').read_text())
        self.assertEqual(Catalog(self.root).targets['Demo'].size,4)

    def test_rollback_on_write_failure(self):
        from unittest.mock import patch
        import guarded_apply
        self.emit();real=guarded_apply.write_atomic;calls=[]
        def fail_second(path,data):
            calls.append(path)
            if len(calls)==2: raise OSError('injected write failure')
            real(path,data)
        with patch.object(guarded_apply,'write_atomic',fail_second),self.assertRaisesRegex(OSError,'injected'):
            apply(self.package,self.root,live=True)
        self.assertEqual((self.root/'file.c').read_text(),'before\n')
        self.assertFalse((self.root/'new.h').exists())

    def test_generator_preserves_semantic_record_and_rejects_stale_metadata(self):
        from record_names import preserved_records
        inc=self.root/'include/records';inc.mkdir(parents=True)
        (inc/'Rec_D_80000000.h').write_text('#ifndef REC_D_80000000_H\n#define REC_D_80000000_H\ntypedef struct Rec_D_80000000 { int x; } Rec_D_80000000;\n#endif\n')
        (self.root/'knowledge').mkdir();(self.root/'knowledge/evidence.md').write_text('fixture')
        args=argparse.Namespace(old='Rec_D_80000000',name='Demo',evidence='knowledge/evidence.md',confidence='high',out=self.package)
        rename_record(Catalog(self.root),args);apply(self.package,self.root,live=True)
        records=json.loads((self.root/'ledger/records.json').read_text())
        retained=preserved_records(self.root,records)
        self.assertEqual(retained['Rec_D_80000000']['canonical_type'],'Demo')
        (inc/'Demo.h').write_text('edited')
        with self.assertRaisesRegex(ValueError,'reconcile'):preserved_records(self.root,records)

    def test_record_population_includes_transitive_header_consumers(self):
        from typefold_cli import record_consumers
        inc=self.root/'include/shared';inc.mkdir(parents=True)
        (inc/'via.h').write_text('#include "records/Rec_D_80000000.h"\n')
        src=self.root/'src/town';src.mkdir(parents=True)
        (src/'f.c').write_text('#include "shared/via.h"\n')
        (src/'unregistered.c').write_text('#include "shared/via.h"\n')
        (self.root/'ledger').mkdir()
        (self.root/'ledger/rows.jsonl').write_text(json.dumps({'id':'town/f'})+'\n')
        rows,unregistered,modules=record_consumers(Catalog(self.root),'Rec_D_80000000')
        self.assertEqual(rows,['town/f']);self.assertEqual(unregistered,['town/unregistered'])

    def test_generation_refuses_a_changed_consumed_source(self):
        with self.assertRaisesRegex(Refuse,'source changed during generation'):
            emit_package(self.root,self.package,{'file.c':'after\n'}, {},expected_before={'file.c':sha(b'earlier\n')})
        self.assertEqual((self.root/'file.c').read_text(),'before\n')

    def test_catalog_ambiguous_targets_and_class_conflicts(self):
        inc=self.root/'include/records';inc.mkdir(parents=True)
        shared=self.root/'include/shared';shared.mkdir()
        (shared/'demo.h').write_text('typedef struct Demo { int x; } Demo; typedef struct Other { int x; } Other;')
        (inc/'Rec_D_80000000.h').write_text('typedef struct Rec_D_80000000 { int x; } Rec_D_80000000;')
        (self.root/'ledger').mkdir()
        (self.root/'ledger/struct_census_structs.json').write_text(json.dumps({'town/f|S_80000000_0':{'class':'global:D_80000004'}}))
        (self.root/'ledger/records.json').write_text(json.dumps({'Rec_D_80000000':{'class':'global:D_80000000'}}))
        c=Catalog(self.root);src='typedef struct S_80000000_0 { int x; } S_80000000_0;\nint f(S_80000000_0 *p) { return p->x; }'
        item=c.analyze(src,'town/f')[0]
        self.assertEqual({x['type'] for x in item['candidates']},{'Demo','Other'})
        new,notes,holds=c.fold(src,'town/f')
        self.assertEqual(src,new);self.assertEqual(holds[0]['reason'],'layout match requires explicit semantic selection')
        new,notes,holds=c.fold(src,'town/f',{'S_80000000_0':'Demo'})
        self.assertIn('Demo *p',new);self.assertEqual(len(notes),1)

if __name__ == '__main__': unittest.main()
