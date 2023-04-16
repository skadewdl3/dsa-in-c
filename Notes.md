# ASD

Defines what functions the data structure performs. Not it's implementation, just the action.

# Data Types

1. Primitive
2. Non-Primitive
   - Linear: LL, Stack, Queue
     - Static: Arrays
     - Dynamic: LL, Stack, Queue
   - Non-Linear: BST, Quadtree, Graph

---

IntStack {

push (int): void {}
pop (): void {}
peek (): int {}
is_empty (): int {} // only for bounded stack
is_full (): int {} // only for bounded stack

}

Uses of Stack:

1. Infix to prefix/postfix and vice-versa.
2. Expression evaluation
3. Delimiter matching
