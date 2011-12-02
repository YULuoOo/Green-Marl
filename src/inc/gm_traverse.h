#ifndef GM_TRAVERSE
#define GM_TRAVERSE

// codes for traverse
#include "gm_ast.h"
#include "gm_typecheck.h"
#include <vector>

class gm_apply {
    public:
        gm_apply() : for_id (false), for_symtab(false), for_sent(false), for_expr(false), separate_post_apply(false) {}

    virtual bool apply(gm_symtab* e, int symtab_type){ return true;}      // SYMTAB_ARG, SYMTAB_FIELD, SYMTAB_VAR, SYMTAB_PROC
    virtual bool apply(gm_symtab_entry* e, int symtab_type){ return true;}
    virtual bool apply(ast_id* e){ return true;}
    virtual bool apply(ast_sent* s) {return true;}
    virtual bool apply(ast_expr* e) {return true;}
    virtual bool apply(ast_procdef* s) {return true;}
    virtual void begin_context(ast_node* n) {return;}
    virtual void end_context(ast_node* n) {return ;}

    virtual bool apply2(gm_symtab* e, int symtab_type){ return true;}      // SYMTAB_ARG, SYMTAB_FIELD, SYMTAB_VAR, SYMTAB_PROC
    virtual bool apply2(gm_symtab_entry* e, int symtab_type){ return true;}
    virtual bool apply2(ast_id* e){ return true;}
    virtual bool apply2(ast_sent* s) {return true;}
    virtual bool apply2(ast_expr* e) {return true;}
    virtual bool apply2(ast_procdef* s) {return true;}

    protected:
        bool for_id;
        bool for_symtab;
        bool for_sent;
        bool for_expr;
        bool separate_post_apply;

    public:
        bool is_for_id() {return for_id;}
        bool is_for_symtab() {return for_symtab;}
        bool is_for_sent() {return for_sent;}
        bool is_for_expr() {return for_expr;}
        void set_for_id(bool b) {for_id =b;}
        void set_for_symtab(bool b) {for_symtab=b;}
        void set_for_sent(bool b) {for_sent=b;}
        void set_for_expr(bool b) {for_expr=b;}

        bool has_separate_post_apply() {return separate_post_apply;}
        void set_separate_post_apply(bool b)  {separate_post_apply = b;}

        /*
        void get_all(bool &b1, bool &b2, bool&b3, bool &b4) { b1 = for_id; b2 = for_symtab; b3 = for_sent; b4 = for_expr}
        void set_all(bool b1, bool b2, bool b3, bool b4) { for_id = b1; for_symtab = b2;for_sent=b3;for_expr = b4;}
        */
        void set_all(bool b) {for_id = for_sent = for_expr = for_symtab = b;}

};

// [todo make stop traverse]

#define GM_POST_APPLY   true
#define GM_PRE_APPLY    false

//--------------------------------------------------------------------
// traverse all the ids in the procedure ast and apply operation 
// (except ids in the symtab)
// This should be called after type-check is finished.
//--------------------------------------------------------------------
static void gm_traverse_ids(ast_procdef* top, gm_apply* a, bool is_post_apply=false) 
{
    a->set_all(false);
    a->set_for_id(true);
    top->traverse(a, is_post_apply, !is_post_apply);
}

//--------------------------------------------------------------------
// traverse all the sentences in the procedure and apply operation
//--------------------------------------------------------------------
static void gm_traverse_sents(ast_procdef* top, gm_apply *a, bool is_post_apply=false)
{ 
    a->set_all(false);
    a->set_for_sent(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}
static void gm_traverse_sents(ast_sent* top, gm_apply *a, bool is_post_apply=false)
{ 
    a->set_all(false);
    a->set_for_sent(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}

static void gm_traverse_sents_pre_post(ast_procdef* top, gm_apply *a)
{ 
    a->set_all(false);
    a->set_for_sent(true);
    a->set_separate_post_apply(true);
    top->traverse(a, true, true);
}

// traverse and apply two times (pre/post)
static void gm_traverse_sents_pre_post(ast_sent* top, gm_apply *a)
{ 
    a->set_all(false);
    a->set_for_sent(true);
    a->set_separate_post_apply(true);
    top->traverse(a, true, true);
}

//--------------------------------------------------------------------
// traverse all the symtabs in the procedure ast
//--------------------------------------------------------------------
static void gm_traverse_symtabs(ast_procdef* top, gm_apply* a, bool is_post_apply=false)
{ 
    a->set_all(false);
    a->set_for_symtab(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}
static void gm_traverse_symtabs(ast_sent* top, gm_apply* a, bool is_post_apply=false)
{ 
    a->set_all(false);
    a->set_for_symtab(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}

//--------------------------------------------------------------------
// traverse all the exprs in the procedure ast
//--------------------------------------------------------------------
static void gm_traverse_exprs(ast_procdef* top, gm_apply* a, bool is_post_apply=false)
{ 
    a->set_all(false); a->set_for_expr(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}
static void gm_traverse_exprs(ast_expr* top, gm_apply* a, bool is_post_apply=false)
{ 
    a->set_all(false); a->set_for_expr(true);
    top->traverse( a, is_post_apply, !is_post_apply);
}

//-------------------------------------------------------------
// travese up the nodes and apply a to every sent in place
// return true, if it reached to the top 'null'
// return false, if traverse stopped in the middle by apply
//-------------------------------------------------------------
extern bool gm_traverse_up_sent(ast_node* n, gm_apply *a);

#endif