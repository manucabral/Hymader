#include "hymader.h"

int main()
{
    struct Node *main = InitHymader();
    append(&main, INIT_HEADER, NULL);
    append(&main, TITLE, "hello");
    append(&main, END_HEADER, NULL);
    export(main, "test.html");
    free(main);
    return 0;
}
