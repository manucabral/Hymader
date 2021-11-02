#ifndef HYMADER_H
#define HYMADER_H

#define INIT_HTML 0
#define END_HTML 1
#define INIT_HEADER 2
#define END_HEADER 3
#define TITLE 4
#define END_TITLE 5

#define MAX_TAGS 6
#define TAG_LENGTH 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tag
{
    int type;
    char *value;
};

struct Node
{
    struct Tag tag;
    struct Node *next;
};

const char tagname[MAX_TAGS][TAG_LENGTH] =
    {
        "<html>",
        "</html>",
        "<header>",
        "</header>",
        "<title>",
        "</title>"};

void push(struct Node **head, int type)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->tag.type = type;
    new->next = *head;
    *head = new;
}

void delete (struct Node **head, int type)
{
    struct Node *tmp = *head, *prev;
    if (tmp != NULL && tmp->tag.type == type)
    {
        *head = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp->tag.type != type)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

void append(struct Node **head, int type, char *value)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = *head;
    new->tag.type = type;

    if (type == TITLE)
        new->tag.value = value;

    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new;

    if (type == TITLE)
        append(&*head, END_TITLE, NULL);
    return;
}

void print(struct Node *root)
{
    while (root != NULL)
    {
        printf("%d %s", root->tag.type, root->tag.value);
        root = root->next;
    }
}

void export(struct Node *root, const char *filename)
{
    FILE *file = NULL;
    if (file = fopen(filename, "w"))
    {
        while (root != NULL)
        {
            fprintf(file, "%s", tagname[root->tag.type]);
            if (root->tag.type == TITLE)
                fprintf(file, "%s", root->tag.value);
            root = root->next;
        }
        fprintf(file, "%s", tagname[END_HTML]);
        fclose(file);
        return;
    }
}

struct Node *InitHymader()
{
    struct Node *head = NULL;
    head = (struct Node *)malloc(sizeof(struct Node));
    head->next = NULL;
    head->tag.type = INIT_HTML;
    return head;
}

#endif // HYMADER_H
