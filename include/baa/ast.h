#ifndef BAA_AST_H
#define BAA_AST_H

#include <stddef.h>

// Node types for AST
typedef enum
{
    // Top-level constructs
    NODE_PROGRAM,  // Program root
    NODE_FUNCTION, // Function declaration
    NODE_STRUCT,   // Structure definition
    NODE_UNION,    // Union definition
    NODE_TYPEDEF,  // Type definition
    NODE_IMPORT,   // Import declaration

    // Declarations
    NODE_VAR_DECL,     // Variable declaration
    NODE_PARAM_DECL,   // Parameter declaration
    NODE_ARRAY_DECL,   // Array declaration
    NODE_POINTER_DECL, // Pointer declaration

    // Statements
    NODE_BLOCK,     // Block of statements
    NODE_IF_STMT,   // If statement
    NODE_WHILE_STMT, // While loop
    NODE_FOR,       // For loop
    NODE_DO_WHILE,  // Do-while loop
    NODE_SWITCH,    // Switch statement
    NODE_CASE,      // Case statement
    NODE_BREAK,     // Break statement
    NODE_CONTINUE,  // Continue statement
    NODE_RETURN,    // Return statement
    NODE_EXPR_STMT, // Expression statement

    // Expressions
    NODE_BINARY_OP,     // Binary operation
    NODE_UNARY_OP,      // Unary operation
    NODE_ASSIGNMENT,    // Assignment
    NODE_CALL,          // Function call
    NODE_SUBSCRIPT,     // Array subscript
    NODE_MEMBER_ACCESS, // Structure member access
    NODE_SIZEOF,        // Sizeof operator

    // Primary expressions
    NODE_IDENTIFIER, // Identifier
    NODE_NUMBER,     // Numeric literal
    NODE_FLOAT,      // Floating-point literal
    NODE_STRING,     // String literal
    NODE_CHAR,       // Character literal
    NODE_VAR_REF,    // Variable reference

    // Types
    NODE_TYPE_INT,     // عدد_صحيح
    NODE_TYPE_FLOAT,   // عدد_حقيقي
    NODE_TYPE_CHAR,    // حرف
    NODE_TYPE_VOID,    // فراغ
    NODE_TYPE_ARRAY,   // Array type
    NODE_TYPE_POINTER, // Pointer type
    NODE_TYPE_STRUCT,  // Structure type
    NODE_TYPE_UNION,   // Union type
} NodeType;

// Node flags
typedef enum
{
    NODE_FLAG_NONE = 0,
    NODE_FLAG_SYSTEM_IMPORT = 1 << 0,
    NODE_FLAG_CONST = 1 << 1,
} NodeFlags;

// Forward declaration of Node structure
typedef struct Node Node;

// AST node structure
// Forward declarations
typedef struct NodeAttributes NodeAttributes;

struct Node
{
    NodeType type;
    wchar_t *value;
    NodeFlags flags;
    Node **children;
    size_t children_count;
    size_t children_capacity;
    NodeAttributes *attributes;
};

// AST core functions
Node *baa_create_node(NodeType type, const wchar_t *value);
void baa_add_child(Node *parent, Node *child);
void baa_free_node(Node *node);

// Tree traversal functions
void baa_visit_node(Node *node, void (*visitor)(Node*, void*), void *data);

// Node attribute functions
void baa_set_node_location(Node *node, size_t line, size_t column, const wchar_t *file);
void baa_set_node_constant(Node *node, bool is_constant);
void baa_set_node_static(Node *node, bool is_static);
void baa_set_node_extern(Node *node, bool is_extern);

#endif /* BAA_AST_H */