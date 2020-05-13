#include <cstdlib>
#include <Windows.h>
#include "stdio.h"
#include "\MyLib\Assert.h"
#include "\MyLib\MyLib.h"
#include "tree.h"


const char* s       = nullptr;
const char namein[] = "fac.txt";

int Rewrite (struct node* tree);
int WriteElem (struct node* node, FILE* out, int deep);
node* GetG (const char* str);
node* GetOp ();
node* GetE ();
node* GetT ();
node* GetP ();
node* GetN ();

int main (int argc, const char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //const char* namein = (argc >= 2 ? argv[1] : "text.txt");
    printf ("\n%s\n", namein);
    FILE* in = fopen (namein, "r");

    char* str = BufferMaker (namein);
    char* str_copy = str;
    for (int i = 0; str_copy[i] != '\0'; i++)
        if (str_copy[i] == '\n')
        {
            str_copy[i] = ' ';
        }

    node* head = GetG (str);
    //Dump (head);
    Rewrite (head);
}



int WriteElem (struct node* node, FILE* out, int deep)
{
    NullPTRRRRRR_YA_SGOREL (node)

    for (int i = 0; i< deep; i++)       fprintf (out, "\t");
    fprintf (out, "{\n");

    for (int i = 0; i<= deep; i++)      fprintf (out, "\t");

    fprintf (out, "%c ", node->what);

    if (node->what == NUMBER || node->what == PRINTF_TEXT)
        fprintf (out, "%d", node->number);

    if (node->what == ID || node->what == PRINTF_FROM || node->what == SCANF || node->what == FUNC_CALL || node->what == FUNC)
        fprintf (out, "%s", node->name);

    fprintf (out, "\n", node->what);

    int tmp = deep;

    if (node->left != nullptr)
    {
        deep ++;
        WriteElem (node->left, out, deep);
    }

    if (node->right != nullptr)
    {
        WriteElem (node->right, out, deep);
    }

    for (int i = 0; i < tmp; i++)       fprintf (out, "\t");
    fprintf (out, "}\n");
}

int Rewrite (struct node* tree)
{
    NullPTRRRRRR_YA_SGOREL (tree)
    FILE* out = fopen ("C:\\Users\\dunka\\CLionProjects\\language\\code.txt", "w");

    int deep = 0;

    WriteElem (tree, out, deep);

    fclose (out);
}








node* GetId ()
{
    int size = 0;

    char* name = (char*) calloc (100, sizeof (char));
    sscanf (s, " %[^ ,)] %n", name, &size);

    s += size;

    return CreateElement (ID, NOTHING, name);
}


node* GetN ()
{
    int val = 0;
    int skip = 0;

    if (sscanf (s, " %d %n", &val, &skip) == 0)
    {
        printf ("Syntax Error");
        exit (3);
    }

    s += skip;

    node* result = CreateElement (NUMBER, val);

    return result;
}

node* GetP ()
{
    node* val = nullptr;

    int skip = 0;

    char tmp[100] = {};
    sscanf (s, " %[(] %n", tmp, &skip);

    if (strcmp (tmp, "(") == 0)
    {
        printf ("\n\ntut");
        s += skip;
        val = GetE ();

        sscanf (s, " %s %n", tmp, &skip);
        printf ("\n----------%s", tmp);
        if (strcmp (tmp, ")") == 0)
            s += skip;
        else
        {
            printf ("Syntax Error");
            exit (3);
        }
    }
    else
    {
        sscanf (s, " %s %n", tmp, &skip);
        printf ("\n%s\n", tmp);
        if ((tmp[0] >= '0' && tmp[0] <= '9') || (tmp[0] == '-'))
        {
            val = GetN ();
        }
        else
        {
            val = GetId ();
        }
    }

    return val;
}

node* GetK ()
{
    node* val = nullptr;

    int skip = 0;

    char tmp[100] = {};
    sscanf (s, " %s %n", tmp, &skip);


    val = GetP ();

    return val;
}

node* GetT ()
{
    node* val = nullptr;
    node* operation = nullptr;

    val = GetK ();

    int skip = 0;

    char tmp[100] = {};
    sscanf (s, " %s %n", tmp, &skip);


    while (strcmp (tmp, "*") == 0 || strcmp(tmp, "/") == 0)
    {
        s += skip;
        node* val2 = GetP ();

        if (strcmp (tmp, "*") == 0)
            operation = CreateElement (MUL);
        else
        if (strcmp(tmp, "/") == 0)
            operation = CreateElement (DIV);
        else
        {
            printf ("Syntax Error");
            exit (3);
        }

        node* tmp_ = CreateElement (NOTHING);

        Merge (CopyNode (val, tmp_), operation, LEFT);
        Merge (val2, operation, RIGHT);

        val = operation;
        sscanf (s, " %s %n", tmp, &skip);
    }

    return val;
}

node* GetE ()
{
    node* val = nullptr;
    node* operation = nullptr;

    val = GetT ();


    int skip = 0;

    char tmp[100] = {};
    sscanf (s, " %s %n", tmp, &skip);


    while (strcmp (tmp, "+") == 0 || strcmp(tmp, "-") == 0)
    {
        s += skip;

        node* val2 = GetT ();

        if (tmp[0] == '+')
            operation = CreateElement (PLUS);
        else
            if (tmp[0] == '-')
                operation = CreateElement (MINUS);
            else
            {
                printf ("Syntax Error");
                exit (3);
            }

        Merge (val, operation, LEFT);
        Merge (val2, operation, RIGHT);

        val = operation;
        sscanf (s, " %s %n", tmp, &skip);
    }

    return val;
}

node* GetScanf ()
{
    int skip = 0;
    char* tmp = (char*) calloc (100, sizeof (char));
    sscanf (s, "%s %n", tmp, &skip);
    s += skip;
    char* name = strdup (tmp);
    free (tmp);
    node* scanf = CreateElement (SCANF, 0, name);
    return scanf;
}

node* GetIf ()
{
    node* operation = CreateElement (IF);

    node* left_equlement = GetE ();

    int skip = 0;
    char tmp[100] = {};
    sscanf (s, " %s %n", tmp, &skip);

    node* compare = nullptr;

    if  (strcmp (tmp, "—¬≈–—“¿Õ") == 0)
        compare = CreateElement (CMP_RAVNO);
    if  (strcmp (tmp, "¬ﬂŸ≈") == 0)
        compare = CreateElement (CMP_BIGGER);
    if  (strcmp (tmp, "ƒŒÀ”") == 0)
        compare = CreateElement (CMP_UNDER);
    if (compare == nullptr)
    {
        printf ("Syntax Error");
        exit (3);
    }

    s += skip;

    Merge (compare, operation, LEFT);
    Merge (left_equlement, compare, LEFT);
    Merge (GetE (), compare, RIGHT);

    node* else_ = Merge (GetOp (), CreateElement (ELSE), LEFT);
    Merge (else_, operation, RIGHT);
    sscanf (s, " %s %n", tmp, &skip);
    if (strcmp (tmp, "¿ÕŒ") == 0)
    {
        s += skip;

        Merge (GetOp (), else_, RIGHT);
    }
    return operation;
}

node* GetAssn ()
{
    int skip = 0;

    char tmp[100] = {};
    sscanf (s, " %s %n", tmp, &skip);
    char* name = strdup (tmp);

    s += skip;

    node* operation = CreateElement (EQUAL);
    Merge (CreateElement (ID, 0, name), operation, LEFT);

    sscanf (s, " %s %n", tmp, &skip);

    if (strcmp (tmp, "¬≈–—“¿“»") != 0)
    {
        printf ("Syntax Error");
        exit (3);
    }

    s += skip;

    Merge (GetE (), operation, RIGHT);

    printf ("%s", s);

    return operation;
}

node* GetFunc ()
{
    int skip = 0;

    char* tmp = (char*) calloc (100, sizeof (char));
    sscanf (s, " %s %n", tmp, &skip);
    printf ("%s-------------", tmp);
    s += skip;

    char* name = strdup (tmp);
    node* operation = CreateElement (FUNC_CALL, 0, name);
    node* node_     = operation;

    sscanf (s, "%*[ (] %n", &skip);
    s += skip;
    //printf ("\n\n\n\n%s", s);

    while (tmp[0] != ')')
    {
        Merge (GetId (), node_, LEFT);

        node_ = node_->left;



        //printf ("\n\n\n\n\n str - %s", s);
        skip = 0;
        sscanf (s, ",%n", &skip);
        printf ("\n skip - %d", skip);
        s += skip;
        //printf ("\nstr - %s", s);
        sscanf (s, " %[^ !] %n", tmp, &skip);
        printf ("\n\n%s\n\n", tmp);
    }

    s += skip;
    printf ("\n-----%s", s);


    sscanf (s, "%s %n", tmp, &skip);
    printf (")))))-%s", tmp);


    if (strcmp (tmp, "^-^") == 0)
    {
        operation->what = FUNC;
        sscanf (s, " %s ", tmp);


        //DeleteTree (operation->left);
        //operation->left = nullptr;


        Merge (GetOp (), operation, RIGHT);


    }
    else
    {
        s += skip;
        if (strcmp (tmp, "!") != 0)
        {
            printf ("Syntax Error");
            exit (3);
        }
    }

    return operation;
}

node* GetPrintf ()
{
    int skip = 0;
    char* tmp = (char*) calloc (100, sizeof (char));
    char tmp_ = 0;
    sscanf (s, " %c %n", &tmp_, &skip);



    node* printf_ = nullptr;

    printf ("%c", tmp_);
    if (tmp_ == '/')
    {
        int this_ = 0;
        sscanf (s, " / %d \ %n", &this_, &skip);
        printf ("\n\n%d\n", skip);

        printf_ = CreateElement (PRINTF_TEXT, this_);
    }
    else
    {
        sscanf (s, " %s %n", tmp, &skip);
        char* print = strdup (tmp);
        printf_ = CreateElement (PRINTF_FROM, 0, print);
    }
    free (tmp);
    s += skip;
    printf ("fvs- %s", s);
    return printf_;
}

node* GetOp ()
{
    node* operation = nullptr;
    int skip = 0;

    char* tmp = (char*) calloc (100, sizeof (char));
    sscanf (s, " %s %n", tmp, &skip);
    printf ("\nGetOp -%s-", tmp);

    if (strcmp (tmp, "¿∆≈") == 0)
    {
        s += skip;
        operation = GetIf ();
    }
    else
        if (strcmp (tmp, "^-^") == 0)
        {
            s += skip;
            printf ("\n\n\n\n\n\n\n%s\n\n\n\n\n\n\n\n", s);
            operation = CreateElement (NODE);
            node* node_ = operation;

            sscanf (s, " %s %n", tmp, &skip);
            while (strcmp (tmp, "^-^") != 0)
            {

                Merge (GetOp (), node_, LEFT);

                Merge (CreateElement (NODE), node_, RIGHT);
                node_ = node_->right;

                sscanf (s, " %s %n", tmp, &skip);
                printf ("\n\n%s\n\n", tmp);
            }

            DeleteNode (node_);
            s += skip;
        }
        else
        if (strcmp (tmp, "»—œŒ¬≈ƒ¿“»") == 0)
        {

            s += skip;

            operation = GetScanf ();
        }
        else
            if (strcmp (tmp, "MEOW") == 0)
            {
                s += skip;
                operation = GetPrintf ();
            }
            else
                if (*s < '0' || *s > '9')
                {
                    char* tmp_copy = tmp;

                    const char* s_new = s + skip;
                    sscanf (s_new, " %s ", tmp);



                    if (tmp[0] == '(')
                    {

                        operation = GetFunc ();
                    }
                    else
                    {
                        operation = GetAssn ();
                    }
                }
                else
                {
                    printf ("Syntax Error");
                    exit (3);
                }

    return operation;
}

node* GetG (const char* str)
{
    s = str;

    char tmp[100] = {};

    node* val_copy = CreateElement (NODE);
    node* node_     = val_copy;
    node* val       = nullptr;

    while (true)
    {
        printf ("\n in GetG - %s", s);
        sscanf (s, " %s ", tmp);
        if (strcmp (tmp, "”—œ≈Õ»≈") != 0)
            Merge (GetOp (), node_, LEFT);
        else
            break;

        Merge (CreateElement (NODE), node_, RIGHT);
        node_ = node_->right;
    }
    DeleteNode (node_);
        return val_copy;
}