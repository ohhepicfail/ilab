#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE       8
#define NAME( name )    #name

typedef struct
{
    int     * data;
    int     size;
    int     cur;
}Stack_t;


Stack_t     * init_stack    (int stack_size);
void        erase_stack     (Stack_t ** stack);
int         stack_is_ok     (Stack_t * stack);
void        stack_dump      (Stack_t * stack, char * obj_name, char * file, int line);



int main()
{
    Stack_t * stack = init_stack (INIT_SIZE);

    stack -> cur = -440;

    if ( ! stack_is_ok (stack))
        stack_dump (stack, NAME (stack), __FILE__, __LINE__);

    erase_stack (&stack);
    return 0;
}



Stack_t * init_stack (int stack_size)
{
    assert (stack_size >= 0);

    Stack_t * new_stack = (Stack_t *) calloc (1, sizeof (Stack_t));
    new_stack -> data   = (int *) calloc (stack_size, sizeof (int));
    new_stack -> size   = stack_size;
    new_stack -> cur    = 0;

    assert (new_stack);
    assert (new_stack -> data);
    return new_stack;
}



void erase_stack (Stack_t ** stack)
{
    int i = 0;
    for (i = 0; i < (*stack) -> cur; i++)
        (*stack) -> data[i] = 0xBADF00D;

    (*stack) -> cur  = -1;
    (*stack) -> size = -1;

    free ((*stack) -> data);
    free (*stack);
}



int stack_is_ok (Stack_t * stack)
{
    return (stack != NULL) && (stack -> size >= 0) && (stack -> cur >= 0);
}



void stack_dump (Stack_t * stack, char * obj_name, char * file, int line)
{
    fprintf (stderr,    "\n\n********   ERROR   ********\n\n");
    fprintf (stderr,    "ERROR:\t\tStack_t_dump\n"\
                        "In file:\t%s\n"\
                        "Line:\t\t%d\n"\
                        "Object:\t\t%s\n\n", file, line, obj_name);
    fprintf (stderr,    "stack (ptr):\t%d\n"\
                        "stack -> cur:\t%d\n"\
                        "stack -> size:\t%d\n", stack, stack -> cur, stack -> size);
    fprintf (stderr,    "\n\n***************************\n\n");

    abort ();
}
