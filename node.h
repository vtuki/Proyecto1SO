#ifndef NODE_H
#define NODE_H

enum node_type_e
{
    NODE_COMMAND,           // comando simple
    NODE_VAR,               // nombre de variable (o simplemente, una palabra)
};

enum val_type_e
{
    VAL_SINT = 1,       // entero con signo
    VAL_UINT,           // entero sin signo
    VAL_SLLONG,         // long long con signo
    VAL_ULLONG,         // long long sin signo
    VAL_FLOAT,          // punto flotante
    VAL_LDOUBLE,        // long double
    VAL_CHR,            // carácter
    VAL_STR,            // cadena (puntero a char)
};

union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};

struct node_s
{
    enum   node_type_e type;    // tipo de este nodo
    enum   val_type_e val_type; // tipo del campo val de este nodo
    union  symval_u val;        // valor de este nodo
    int    children;            // número de nodos hijos
    struct node_s *first_child; // primer nodo hijo
    struct node_s *next_sibling, *prev_sibling; 
                                // si este es un nodo hijo, mantener punteros a hermanos anterior/siguiente
};

struct  node_s *new_node(enum node_type_e type);
void    add_child_node(struct node_s *parent, struct node_s *child);
void    free_node_tree(struct node_s *node);
void    set_node_val_str(struct node_s *node, char *val);

#endif
