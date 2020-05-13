#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stringapiset.h>
#include "C:\Users\dunka\CLionProjects\TXLib\TX\TXLib.h"

char* LuL = "";

enum tree {
    RIGHT         = 0,
    LEFT          = 1,
    PUT_OK        = 10,
    ADRESS_ERROR  = -1,
    SIDE_ERROR    = - 2,
    POISON        = -91,
    OK            = 111,
    MAX_SIZE_LINE = 100,
    MAX_LENGTH    = 100,
    END           = 4565,
    NOTHING       = -227,

};

enum what {
    NUMBER       = 'N',
    PLUS         = '+',
    MINUS        = '-',
    MUL          = '*',
    DIV          = '/',
    ID           = 'L',
    IF           = '?',
    EQUAL        = '=',
    NODE         = '#',
    FUNC         = 'F',
    FUNC_CALL    = 'C',
    PRINTF_TEXT  = 'T',
    PRINTF_FROM  = 'P',
    SCANF        = 'S',
    CMP_RAVNO    = 'R',
    CMP_UNDER    = 'U',
    CMP_BIGGER   = 'B',
    ELSE         = 'E',
    SQRT         = 'Q',


};


struct node {
    unsigned char    what;
    int    number;
    char*  name = LuL;
    struct node* prev;
    struct node* left;
    struct node* right;
};


#define NullPTRRRRRR_YA_SGOREL(what)                                \
{                                                                   \
    if (what == nullptr)                                            \
    {                                                               \
        printf ("ERRRRORRR NUUUUULPTRRRRRRRR!!!!!!!!!!!");          \
        exit(ADRESS_ERROR);                                         \
    }                                                               \
}



struct node* CreateElement (char what, int number = 0, char* name = nullptr)
{
    struct node* new_elem = (struct node*) calloc (1, sizeof (struct node));

    new_elem->what   = what;
    new_elem->number = number;
    new_elem->name   = name;
    new_elem->prev   = nullptr;
    new_elem->right  = nullptr;
    new_elem->left   = nullptr;

    return new_elem;
}


int PaintTree_s (node* node, FILE* out);

node* Merge (struct node* what, struct node* node, int side)
{
    NullPTRRRRRR_YA_SGOREL (node);
    NullPTRRRRRR_YA_SGOREL (what);

    if ((side != RIGHT) && (side != LEFT))
    {
        printf ("ERROR SIDE IS NOT RIGHT");
        return nullptr;
    }

    struct node* tmp = nullptr;

    what->prev = node;

    if (side == RIGHT)
    {
        node->right = what;
    }

    if (side == LEFT)
    {
        node->left = what;
    }

    return node;
}

int DeleteUnderNode (struct node* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->right != nullptr)
    {
        DeleteUnderNode (node->right);
        node->right->number   = POISON;
        node->right->what     = POISON;
        node->right->name     = nullptr;

        free (node->right);
        node->right = nullptr;
    }

    if (node->left != nullptr)
    {
        DeleteUnderNode (node->left);

        node->left->number   = POISON;
        node->left->what     = POISON;
        node->left->name     = nullptr;

        free (node->left);
        node->left = nullptr;
    }

}

void DeleteNode (struct node* node)
{

    node->number   = POISON;
    node->what     = POISON;
    node->name     = nullptr;
    node->left     = nullptr;
    node->right    = nullptr;

    if (node == node->prev->right)
        node->prev->right = nullptr;
    else
        node->prev->left  = nullptr;



    free (node);
}

void DeleteTree (struct node* node)
{
    if (node->right != nullptr && node->left != nullptr)
        DeleteUnderNode (node);

    node->number   = POISON;
    node->what     = POISON;
    node->name     = nullptr;
    node->left     = nullptr;
    node->right    = nullptr;

    free (node);
}

int Announce (struct node* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    wchar_t textW [_TX_BUFSIZE * sizeof (wchar_t)] = L"";
    char textU[_TX_BUFSIZE] = {};
    if (node->name != nullptr)
    {
        MultiByteToWideChar (_TX_CP, 0, node->name, -1, textW, SIZEARR (textW));
        WideCharToMultiByte (CP_UTF8, 0, textW, -1, textU, _TX_BUFSIZE, 0, 0);
        printf ("here - ");
        printf ("%s\n", textU);
    }

    fprintf (out, "Node%p [shape=record,label=\"{  adress = %p | { type = %c | number = %d} | str = ",
             node, node, node->what, node->number);


    fprintf (out, "%s", textU);

    fprintf (out, " | prev = %p |{ <l%p> left = %p| <r%p> right = %p  }}\"];\n", node->prev, node, node->left, node, node->right);

    if (node->right != nullptr)
    {
        Announce (node->right, out);
    }

    if (node->left != nullptr)
    {
        Announce (node->left, out);
    }
}

int PaintTree (struct node* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->left  != nullptr)         fprintf (out, "Node%p:<l%p> -> Node%p:<%p>;\n", node, node, node->left,  node->left);
    if (node->right != nullptr)         fprintf (out, "Node%p:<r%p> -> Node%p:<%p>;\n", node, node, node->right, node->right);
    if (node->prev  != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->prev);

    if (node->right != nullptr)
    {
        PaintTree (node->right, out);
    }

    if (node->left != nullptr)
    {
        PaintTree (node->left, out);
    }
}

int Dump (struct node* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    FILE* out = fopen ("tree.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=HR;\n");

    Announce (node, out);
    PaintTree (node, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe tree.dot -Gcharset=latin1 -T png -o tree.png");
    system ("tree.png");
}

int Announce_Show (struct node* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)


    if (node->what == MUL || node->what == PLUS || node->what == MINUS || node->what == DIV || node->what == EQUAL)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"%c\"];\n", node, node->what);

    if (node->what == NUMBER)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"%d\"];\n", node, node->number);

    if (node->what == ID)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"%s\"];\n", node, node->name);

    if (node->what == FUNC)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"function %s\"];\n", node, node->name);

    if (node->what == FUNC_CALL)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"call function %s\"];\n", node, node->name);

    if (node->what == NODE)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"#node\"];\n",node);

    if (node->what == PRINTF_TEXT)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"printf text '%d'\"];\n", node, node->number);

    if (node->what == PRINTF_FROM)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"printf from id %s\"];\n", node, node->name);

    if (node->what == SCANF)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"scanf to id %s\"];\n", node, node->name);

    if (node->what == SQRT)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"SQRT\"];\n", node);

    if (node->what == CMP_RAVNO)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"==\"];\n", node);

    if (node->what == CMP_UNDER)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"<\"];\n", node);

    if (node->what == CMP_BIGGER)
        fprintf (out, "Node%p [shape=\"octagon\",label=\">\"];\n", node);

    if (node->what == IF)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"IF\"];\n", node);

    if (node->what == ELSE)
        fprintf (out, "Node%p [shape=\"octagon\",label=\"ELSE\"];\n", node);

    if (node->left != nullptr)
    {
        Announce_Show (node->left, out);
    }

    if (node->right != nullptr)
    {
        Announce_Show (node->right, out);
    }
}

int PaintTree_s (struct node* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)


    if (node->left  != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->left);
    if (node->right != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->right);




    if (node->left != nullptr)
    {
        PaintTree_s (node->left, out);
    }

    if (node->right != nullptr)
    {
        PaintTree_s (node->right, out);
    }
}


int ShowTree (struct node* head)
{
    NullPTRRRRRR_YA_SGOREL (head)

    FILE* out = fopen ("show.dot", "w");



    fprintf (out, "digraph structs {\nrankdir=HR;\n");


    Announce_Show (head, out);

    PaintTree_s (head, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe show.dot -T png -o show.png");
    system ("show.png");

}

node* CopyNode (struct node* node, struct node* where)
{
    ASSERT (node)
    ASSERT (where)

    memcpy (where, node, sizeof (struct node));

    if (node->right != nullptr)
    {
        struct node* copy_right = CreateElement (NOTHING);
        Merge (copy_right, where, RIGHT);
        CopyNode (node->right, copy_right);
        copy_right->prev = where;
    }

    if (node->left != nullptr)
    {
        struct node* copy_left = CreateElement (NOTHING);
        Merge (copy_left, where, LEFT);
        CopyNode (node->left, copy_left);
        copy_left->prev = where;
    }

    return where;
}
