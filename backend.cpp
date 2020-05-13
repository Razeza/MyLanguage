#include "stdio.h"
#include <Windows.h>
#include "MyLib\Assert.h"
#include "MyLib\MyLib.h"
#include "tree.h"


struct IdNumber
    {
        char* name;
        int number;
    };

const char* namein  = "code.txt";
const char* nameout = "asm_code.asm";

const int MaxNumberId = 100;


int Make_Element (struct element* node, struct Text* code, int deep, struct element* head);
struct node* Make_Tree ();
void AssIt (node* head, FILE* out);
void PreAss (node* head);

node* AssFunctions (node* node, FILE* out);

void WriteEqual (node* node);

int main ()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    node* head = Make_Tree ();
    //Dump (head);
    PreAss (head);
}




int FindId (char* name, struct IdNumber* id, int j)
{
    for (int i = 0; i < j; i++)
    {
        if (strcmp (name, id[i].name) == 0)
            return i;
    }
}

void WriteEqual (node* node, FILE* out, struct IdNumber* id, int j)
{
    if (node->left != nullptr)
    {
        WriteEqual (node->left, out, id, j);
    }

    if (node->what == NUMBER)
        fprintf (out, "push %d\n", node->number);

    if (node->what == ID)
        fprintf (out, "push [%d]\n", FindId (node->name, id, j));


    if (node->right != nullptr)
    {
        WriteEqual (node->right, out, id, j);
    }

    if (node->what == MUL)
        fprintf (out, "mul\n");

    if (node->what == DIV)
        fprintf (out, "div\n");

    if (node->what == PLUS)
        fprintf (out, "add\n");

    if (node->what == MINUS)
        fprintf (out, "sub\n");
}

void AssIt (node* node_, FILE* out, struct IdNumber* id, int j, int* num_if)
{

    if (node_->what == SCANF)
        fprintf (out, "in\npop [%d]\n", FindId (node_->name, id, j));

    if (node_->what == EQUAL)
    {
        WriteEqual (node_->right, out, id, j);
        fprintf (out, "pop [%d]\n", FindId (node_->left->name, id, j));
    }

    if (node_->what == PRINTF_TEXT)
        fprintf (out, "push %d\nout\n", node_->number);

    if (node_->what == PRINTF_FROM)
        fprintf (out, "push [%d]\nout\n", FindId (node_->name, id, j));

    if (node_->what == FUNC_CALL)
        fprintf (out, "call %s\n", node_->name);

    if (node_->what == SQRT)
    {
        fprintf (out, "push [%d]\nsqrt\n", FindId (node_->left->name, id, j));
    }

    if (node_->what == NODE)
    {
        node* head = node_;
        do
        {
            AssIt (head->left, out, id, j, num_if);
            head = head->right;
        }
        while (head != nullptr);
    }

    if (node_->what == IF)
    {
        WriteEqual (node_->left->left, out, id, j);
        WriteEqual (node_->left->right, out, id, j);

        if (node_->left->what == CMP_RAVNO)
            fprintf (out, "jne label%d\n", *num_if);


        if (node_->left->what == CMP_UNDER)
            fprintf (out, "jae label%d\n", *num_if);

        if (node_->left->what == CMP_BIGGER)
            fprintf (out, "jbe label%d\n", *num_if);

        int tmp_if = *num_if;
        (*num_if)++;

        AssIt (node_->right->left, out, id, j, num_if);

        if (node_->right->right != nullptr)
            fprintf (out, "jmp label%d\n", *num_if);

        fprintf (out, "label%d:\n", tmp_if);

        if (node_->right->right != nullptr)
        {
            tmp_if = *num_if;
            *num_if += 1;
            AssIt (node_->right->right, out, id, j, num_if);

            fprintf (out, "label%d:\n", tmp_if);
        }

    }
}



char* FindAllId (node* node, struct IdNumber* id, int* j)
{
    if (node->right != nullptr)
        FindAllId (node->right, id, j);

    if (node->left != nullptr)
        FindAllId (node->left, id, j);

    bool isNew = false;
    if (node->what == ID)
    {
        isNew = true;
        for (int i = 0; i < *j; i++)
        {
            //printf ("\n%s - %s\n", node->name, id[i].name);
            if (strcmp (node->name, id[i].name) == 0)
                isNew = false;
        }
    }

    if (isNew)
    {
        id[*j].name   = strdup (node->name);
        id[*j].number = *j;
        (*j)++;
    }
}

node* AssFunctions (node* node_, FILE* out, struct IdNumber* id, int* j, int* num_if)
{
    if (node_->left->what != FUNC)
        return node_;

    fprintf (out, "%s:\n", node_->left->name);
    node* head = node_->left->right;
    do
    {
        FindAllId (head->left, id, j);
        AssIt (head->left, out, id, *j, num_if);
        head = head->right;
    }
    while (head != nullptr);


    fprintf (out, "ret\n");


    AssFunctions (node_->right, out, id, j, num_if);
}

void PreAss (node* head)
{
    FILE* out = fopen (nameout, "w");

    struct IdNumber* id  = (struct IdNumber*) calloc (MaxNumberId, sizeof (struct IdNumber));
    int j = 0;
    int num_if = 0;

    fprintf (out, "jmp begin\n");
    head = AssFunctions (head, out, id, &j, &num_if);
    node* head_tmp = head;
    fprintf (out, "begin:\n");

    do
    {
        FindAllId (head->left, id, &j);
        head = head->right;
    }
    while (head != nullptr);

    head = head_tmp;


    do
    {
        AssIt (head->left, out, id, j, &num_if);
        head = head->right;
    }
    while (head != nullptr);

    for (int i = 0; i < j; i++)
        printf ("\n------------------------------%d %s", id[i].number, id[i].name);

    fprintf (out, "end\n");

    fclose (out);
}




enum IS_OK {
    OK1 = 7,
    OK2 = 8,
    OK3 = 9,
};

int Make_Element (struct node* node, struct Text* code, int deep, struct node* head)
{
    NullPTRRRRRR_YA_SGOREL (node)
    NullPTRRRRRR_YA_SGOREL (code)

    code++;

    char what = 0;
    sscanf (code->begin, " \t %c ", &what);

    int side = -1;

    if (what == '{')
    {
        deep++;
        side = LEFT;
    }

    if (what == '}')
    {
        side = RIGHT;
    }

    if ((side != RIGHT) && (side != LEFT))      printf ("ERROR SIDE");

    struct node* prev = node;
    if (side == RIGHT)
    {
        while (what == '}')
        {
            deep--;
            if (deep == 0)
                return OK1;

            code++;
            sscanf (code->begin, " %c ", &what);

            prev = prev->prev;
        }
        deep++;
    }

    code++;

    int skip = 0;
    sscanf (code->begin, "%*[\t] %c %n", &what, &skip);

    int number = 0;

    struct node* elem = nullptr;

    if (what == NUMBER || what == PRINTF_TEXT)
    {
        sscanf (code->begin + skip, "%d", &number);
        elem = CreateElement (what, number);
    }
    else
        if (what == ID || what == PRINTF_FROM || what == SCANF || what == FUNC_CALL || what == FUNC)
        {
            char* tmp = (char*) calloc (MAX_LENGTH + 1, sizeof (char));

            sscanf (code->begin + skip, "%s", tmp);

            //printf ("\n%c - %s", what, tmp);
            elem = CreateElement (what, NOTHING, tmp);
        }
        else
            elem = CreateElement (what);

    if (side == LEFT)
    {
        Merge (elem, node, side);
        Make_Element (elem, code, deep, head);

        return OK2;
    }

    if (side == RIGHT)
    {
        Merge (elem, prev, side);
        Make_Element (elem, code, deep, head);

        return OK3;
    }

}

struct node* Make_Tree ()
{
    struct Text * code = nullptr;
    code = Input (namein);


    code++;             ///так работает функция Input, она распарсила всё на строки
                        ///++ делается всвязи синтаксисом исходника
    char what = 0;
    sscanf (code->begin, " %c ", &what);

    struct node* head = CreateElement (0);

    int deep = 1;
    Make_Element (head, code, deep, head);

    return head;
}