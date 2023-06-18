#include <stdio.h>
#include <stdlib.h>
#include "bin_tree.h"
#include "graphs.h"

void mcp(char *dest, const char *buf, int n) {
    if (n == 0)
        return;
    for (int i = 0; i < n; i++)
        dest[i] = buf[i];
}

int mylen(const char *st) {
    char c = st[0];
    int i = 0;
    while (c != 0) {
        i++;
        c = st[i];
    }
    return i;
}

char *in_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            return NULL;
        } else if (n > 0) {
            int chunk_len = mylen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, sizeof(char) * (str_len + 1));
            mcp(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = (char *) calloc(1, sizeof(char));
    }

    return res;
}
int main() {
    Graph* graph= calloc(1,sizeof(Graph));
    add_Vertex(graph,"s");
    add_Vertex(graph,"t");
    add_Vertex(graph,"x");
    add_Vertex(graph,"y");
    add_Vertex(graph,"z");
    add_Edge(graph,"s","t",6);
    add_Edge(graph,"t","x",5);
    add_Edge(graph,"x","t",-2);
    add_Edge(graph,"z","x",7);
    add_Edge(graph,"y","z",9);
    add_Edge(graph,"s","y",7);
    add_Edge(graph,"t","y",8);
    add_Edge(graph,"t","z",-4);
    add_Edge(graph,"y","x",-3);
    int *arr= Bellman_Ford_Algorithm(graph,"s");
    for (int i = 0; i < graph->vertexCount; ++i) {
        printf("%d ",arr[i]);
    }
    return 0;
}
