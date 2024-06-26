#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct Arena
{
    size_t capacity;
    size_t used;
    void *buffer;
} Arena;

Arena *arena_init(size_t capacity);

void *arena_alloc(Arena *arena, size_t size);
void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);
void *arena_calloc(Arena *arena, size_t size);
void arena_clear(Arena *arena);
void arena_free(Arena *arena);

#endif