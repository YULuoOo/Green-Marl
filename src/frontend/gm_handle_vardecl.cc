#include "gm_frontend.h"
#include "gm_rw_analysis.h"
#include "gm_traverse.h"
#include "gm_transform_helper.h"
#include "gm_typecheck.h"


class remove_vardecl_t : public gm_apply
{
public:
    // POST Apply
    virtual bool apply(ast_sent* b)
    {
        if (b->get_nodetype() != AST_SENTBLOCK) return true;
        ast_sentblock* sb = (ast_sentblock*) b;
        std::list<ast_sent*> sents = sb->get_sents(); // need a copy
        std::list<ast_sent*> stack;
        std::list<ast_sent*>::iterator i,j;

        //--------------------------------------------
        // 1. find all var-decls
        // 2. iterate again and resolve name conflict
        // 3. delete var-decl
        //--------------------------------------------
        for(i = sents.begin(); i!= sents.end(); i++) 
        {
            ast_sent* z = *i;
            if (z->get_nodetype() != AST_VARDECL)
                continue;
            ast_vardecl* v = (ast_vardecl*) z;

            bool is_scalar = !(v->get_type()->is_property());
            //-----------------------------------------
            // 2. iterate from the beginning up to v.
            //    and resolve name conflict
            //-----------------------------------------
            std::list<ast_sent*> sents2 = sb->get_sents(); // need a copy
            for(j = sents.begin(); j!= sents.end(); j++)  {
                ast_sent* s = *j;
                if (s==v) break;
                if (s->get_nodetype() == AST_VARDECL)
                    continue;

                ast_idlist* idl = v->get_idlist();
                for(int i=0;i<idl->get_length();i++) {
                    gm_symtab_entry *e = idl->get_item(i)->getSymInfo();
                    assert(e!=NULL);
                    gm_resolve_name_conflict(s, e, is_scalar);
                }
            }

            stack.push_back(v);
        }

        // 3. delete var-decl
        for(i = stack.begin(); i!= stack.end(); i++) 
        {
            // now delete
            ast_sent* z = *i;
            gm_ripoff_sent(z,false);
            delete z;
        }
    }

public:
    void do_removal(ast_procdef* p) {
        set_all(false); set_for_sent(true);
        gm_traverse_sents(p, this, GM_POST_APPLY);
    }
};

void gm_frontend::remove_vardecl(ast_procdef* p)
{
    vardecl_removed = true; // hack
    remove_vardecl_t T;
    T.do_removal(p);
}




class restore_vardecl_t : public gm_apply
{
public:
    virtual bool apply(ast_sent* b)
    {
        if (b->get_nodetype() != AST_SENTBLOCK) return true;
        ast_sentblock* sb = (ast_sentblock*) b;
        gm_symtab* V = sb->get_symtab_var();
        gm_symtab* F = sb->get_symtab_field();
        std::vector<gm_symtab_entry*> Vs = V->get_entries();
        std::vector<gm_symtab_entry*> Fs = F->get_entries();

        ast_sent* top = NULL;
        //-------------------------------------
        // Add vardecls after any 'NOP'
        //-------------------------------------
        std::list<ast_sent*> &sents = sb->get_sents();
        std::list<ast_sent*>::iterator ii;
        for(ii=sents.begin(); ii !=sents.end(); ii++) 
        {
            if ((*ii)->get_nodetype() != AST_NOP)
                break;
            top = *ii;
        }


        //----------------------------------------
        // Iterate over symtab. 
        // Add vardecl for each symbol
        //----------------------------------------
        std::vector<gm_symtab_entry*>::iterator i;  
        for(i=Vs.begin(); i!=Vs.end();i++) { // scalar
            gm_symtab_entry* e = *i;
            ast_typedecl* type = e->getType()->copy();
            ast_id* id = e->getId()->copy(true);

            ast_vardecl* v = ast_vardecl::new_vardecl(type, id); 
            if (top == NULL) 
                gm_insert_sent_begin_of_sb(sb, v, GM_NOFIX_SYMTAB);
            else {
                gm_add_sent_after(top, v, GM_NOFIX_SYMTAB);
            }
            top = v;
        }

        for(i=Fs.begin(); i!=Fs.end();i++) { // field
            gm_symtab_entry* e = *i;
            ast_typedecl* type = e->getType()->copy();
            ast_id* id = e->getId()->copy(true);

            ast_vardecl* v = ast_vardecl::new_vardecl(type, id); 
            assert(v->get_idlist()->get_item(0)->getSymInfo()!=NULL);
            if (top == NULL) 
                gm_insert_sent_begin_of_sb(sb, v, GM_NOFIX_SYMTAB);
            else {
                gm_add_sent_after(top, v, GM_NOFIX_SYMTAB);
            }
            top = v;
        }
    }

public:
    void do_restore(ast_procdef* p) {
        set_all(false); set_for_sent(true);
        gm_traverse_sents(p, this, GM_POST_APPLY);
    }
};

void gm_frontend::restore_vardecl(ast_procdef* p)
{
    vardecl_removed = false;
    restore_vardecl_t T;
    T.do_restore(p);
}
void gm_frontend::restore_vardecl_all()
{
    std::vector<ast_procdef*>::iterator i;
    for(i=procs.begin();i != procs.end(); i++) 
        restore_vardecl(*i);
}
