#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE               8
#define NAME( name )            #name
#define ASSERT_OBJ( type, obj )   if ( ! (type ## _is_ok(obj)))\
                                {\
                                    fprintf (stderr,    "\n\n********   ERROR   ********\n\n");\
                                    fprintf (stderr,    "ERROR:\t\t"#type"\n"\
                                                        "In file:\t%s\n"\
                                                        "In function:\t%s\n"\
                                                        "Line:\t\t%d\n"\
                                                        "Object:\t\t"#obj"\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);\
                                    fprintf (stderr,    "\n\n***************************\n\n");\
                                    abort ();\
                                }

typedef struct
{
    int     * data;
    int     size;
    int     next;
} Stack_t;



Stack_t     * init_stack    (int stack_size);
void        erase_stack     (Stack_t ** stack);
int         Stack_t_is_ok   (Stack_t * stack);
void        stack_dump      (Stack_t * stack, char * obj_name);
void        resize          (Stack_t * stack);
void        push            (Stack_t * stack, int elem);
int         pop             (Stack_t * stack);



int main()
{
    Stack_t * stack = init_stack (INIT_SIZE);

    push (stack, 20);
    push (stack, 21);
    push (stack, 22);
    push (stack, 23);
    push (stack, 20);
    pop  (stack);
    pop  (stack);
    pop  (stack);
    pop  (stack);
    pop  (stack);
    push (stack, 22);
    push (stack, 23);
    push (stack, 20);
    pop  (stack);
    pop  (stack);
    pop  (stack);

    ASSERT_OBJ(Stack_t, stack)
    stack_dump (stack, NAME (stack));

    erase_stack (&stack);
    ASSERT_OBJ(Stack_t, stack)
    return 0;
}



Stack_t * init_stack (int stack_size)
{
    assert (stack_size >= 0);

    Stack_t * new_stack = (Stack_t *) calloc (1, sizeof (Stack_t));
    new_stack -> data   = (int *) calloc (stack_size, sizeof (int));
    new_stack -> size   = stack_size;
    new_stack -> next    = 0;

    assert (new_stack);
    assert (new_stack -> data);
    return new_stack;
}



void erase_stack (Stack_t ** stack)
{
    int i = 0;
    for (i = 0; i < (*stack) -> next; i++)
        (*stack) -> data[i] = 0xBADF00D;

    (*stack) -> next = -1;
    (*stack) -> size = -1;

    free ((*stack) -> data);
    free (*stack);
    *stack = NULL;
}



int Stack_t_is_ok (Stack_t * stack)
{
    return (stack != NULL) && (stack -> size >= 0) && (stack -> next >= 0);
}



void stack_dump (Stack_t * stack, char * obj_name)
{
    fprintf (stdout,    "\n\n********   DUMP   ********\n\n");
    fprintf (stdout,    "DUMP:\t\t%s\n\n", obj_name);
    fprintf (stdout,    "stack (ptr):\t%d\n"\
            "stack -> next:\t%d\n"\
            "stack -> size:\t%d\n\n", stack, stack -> next, stack -> size);
    fprintf (stdout,    "%s:\t\t", obj_name);
    int i = 0;
    for (i = 0; i < stack -> next; i++) fprintf (stdout, "%d  ", stack -> data[i]);
    fprintf (stderr,    "\n\n**************************\n\n");
}



void push (Stack_t * stack, int elem)
{
    ASSERT_OBJ(Stack_t, stack)

    if (stack -> next == stack -> size)
        resize (stack);

    stack -> data[stack -> next] = elem;
    stack -> next++;
}



void resize (Stack_t * stack)
{
    ASSERT_OBJ(Stack_t, stack)

    stack -> size += INIT_SIZE;
    stack -> data =  realloc (stack -> data, stack -> size * sizeof (stack -> data));

    ASSERT_OBJ(Stack_t, stack)
}



int pop (Stack_t * stack)
{
    ASSERT_OBJ(Stack_t, stack)

    stack -> size--;
    stack -> next--;

    ASSERT_OBJ(Stack_t, stack)

    return stack -> data[stack -> next];
}
