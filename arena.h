#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

Arena *arena_init(size_t capacity)
{
    Arena *arena;
    arena = malloc(sizeof(Arena));

    if (arena == NULL)
    {
        return NULL;
    }

    arena->capacity = capacity;
    arena->used = 0;
    arena->buffer = malloc(capacity);

    if (arena->buffer == NULL)
    {
        free(arena);
        return NULL;
    }

    return arena;
}

void *arena_alloc(Arena *arena, size_t size)
{
    if (arena == NULL || arena->used + size > arena->capacity)
    {
        return NULL;
    }

    void *block = arena->buffer + arena->used;
    arena->used += size;

    return block;
}

void* arena_alloc_aligned(Arena *arena, size_t size, size_t alignment)
{
    if (arena == NULL || alignment == 0 || (alignment & (alignment - 1)) != 0)
    {
        return NULL;
    }

    size_t offset = -(size_t)(arena->buffer + arena->used) & (alignment - 1);
    if (arena->used + offset + size > arena->capacity)
    {
        return NULL;
    }

    arena->used += offset;
    void *block = arena->buffer + arena->used;
    arena->used += size;

    return block;
}

void *arena_calloc(Arena *arena, size_t size)
{
    if (arena == NULL || arena->used + size > arena->capacity)
    {
        return NULL;
    }

    void *block = arena->buffer + arena->used;
    arena->used += size;

    memset(block, 0, size);

    return block;
}

void arena_clear(Arena *arena)
{
    if (arena != NULL)
    {
        arena->used = 0;
    }
}

void arena_free(Arena *arena)
{
    if (arena != NULL)
    {
        free(arena->buffer);
        free(arena);
    }
}

#endif
