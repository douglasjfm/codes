#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

#define INPUT_MAX_SIZE 256

class Grafo {
    public:
    int n; // num de nos
    int a; // num arestas
    std::vector<std::string> labels;
    std::vector<std::vector<int>> adj;
    Grafo(){n=0;a=0;};
    ~Grafo(){};

    // acha o caminho entre o 1o e o ultimo no da entrada
    void procBFS () {
        std::queue<int> q;
        std::vector<bool> mark(n, false);
        std::vector<int> parent(n, -1);
        std::vector<int> cam;

        mark[0] = true;
        q.push(0);

        while (!q.empty()) {
            int visitado = q.front();
            q.pop();
            mark[visitado] = true;
            
            for (int i=0; i < adj[visitado].size(); i++) {
                int x = adj[visitado][i];
                if (!mark[x]) {
                    parent[x] = visitado;
                    if (x == (n-1)) {
                        while (!q.empty()) q.pop();
                        break;
                    }
                    q.push(x);
                }
            }
        }

        for (int i=0, j = n-1; i < n; i++) {
            int p = parent[j];
            cam.push_back(j);
            if (j==0) break;
            j = p;
        }

        for (int i=cam.size()-1; i >= 0; i--) {
            std::string lb = labels[cam[i]];
            if (i==0) {
                printf("%s\n", lb.c_str());
            } else {
                printf("%s - ", lb.c_str());
            }
        }
    }

    int get_node_index(const char *l) {
        std::string str = l;

        for (int i=0; i < labels.size(); i++) {
            if (str == labels[i]) return i;
        }

        return -1;
    };

    void insert_aresta(int n1, int n2) {
        if (adj.size() == 0) {
            for (int i=0; i < n; i++) {
                std::vector<int> vt;
                adj.push_back(vt);
            }
        }

        if (n1 < 0 || n1 > n) return;
        if (n2 < 0 || n2 > n) return;

        for (int i=0; i < adj[n1].size(); i++) {
            if (n2 == adj[n1][i]) return;
        }

        adj[n1].push_back(n2);
    }
};

bool is_valid_str(const char *s) {
    int traco=0;
    if (!s) return false;
    for (int i=0; i < INPUT_MAX_SIZE && s[i] != '\0'; i++) {
        if (s[i] == '-'){
            traco++;
            if (traco > 1) return false;
            continue;
        }
        if (s[i] < '0') return false;
        if (s[i] > 'z') return false;
        if (s[i] >= '0' && s[i] <= '9') continue;
        if (s[i] >= 'A' && s[i] <= 'Z') continue;
        if (s[i] >= 'a' && s[i] <= 'z') continue;
    }
    return true;
}

bool parse_aresta(Grafo &g, const char *s) {
    char s1[INPUT_MAX_SIZE];
    char *ptr = NULL;
    int n1,n2;
    
    strcpy(s1,s);

    ptr = strtok(s1, "-");
    n1 = g.get_node_index(ptr);
    if (n1<0) return false;

    ptr = strtok(NULL, "-");
    n2 = g.get_node_index(ptr);
    if (n2<0) return false;

    g.insert_aresta(n1, n2);
    g.insert_aresta(n2, n1);
    return true;
}

int main(){
    FILE *f = fopen("input.txt", "r");
    char str[INPUT_MAX_SIZE];
    Grafo g;
    
    if (!f) {
        return -1;
    }
    
    fscanf(f, "%d", &(g.n));

    if (g.n < 0 || g.n > 999999999) {
        return -2;
    }

    for (int i=0; i < g.n; i++) {
        fscanf(f, "%s", str);
        if (!is_valid_str(str)) return -3;
        std::string s = str;
        g.labels.push_back(s);
    }
    
    fscanf(f, "%d", &(g.a));

    if (g.a < 0 || g.a > 999999999) {
        return -4;
    }

    for (int i=0; i < g.a; i++) {
        bool r;
        fscanf(f, "%s", str);
        if (!is_valid_str(str)) return -5;
        r = parse_aresta(g, str);
        if (!r) return -6;
    }

    g.procBFS();

    return 0;

}