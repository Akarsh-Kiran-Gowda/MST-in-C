#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_EDGES 1000
#define MAX_NODES 100

// Structure to represent an edge
typedef struct Edge {
    int u, v, weight;  // 'u' and 'v' are the nodes, 'weight' is the edge weight
} Edge;

// Structure to represent the graph
typedef struct Graph {
    Edge edges[MAX_EDGES]; // Array to store edges
    int num_edges;         // Number of edges in the graph
    int num_nodes;         // Number of nodes in the graph
} Graph;

// Structure for Disjoint Set (Union-Find)
typedef struct DisjointSet {
    int parent[MAX_NODES]; // Parent array for Union-Find
    int rank[MAX_NODES];   // Rank array for Union-Find
} DisjointSet;

// Initialize the disjoint set
void init_disjoint_set(DisjointSet *ds, int n) {
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;  // Each node is its own parent initially
        ds->rank[i] = 0;     // Initially, all nodes have rank 0
    }
}

// Find function with path compression
int find(DisjointSet *ds, int x) {
    if (ds->parent[x] != x) {
        ds->parent[x] = find(ds, ds->parent[x]); // Path compression
    }
    return ds->parent[x];
}

// Union function with union by rank
void union_sets(DisjointSet *ds, int x, int y) {
    int root_x = find(ds, x);  // Find the root of x
    int root_y = find(ds, y);  // Find the root of y

    if (root_x != root_y) {  // If they are in different sets
        // Union by rank: attach the smaller tree under the larger tree
        if (ds->rank[root_x] > ds->rank[root_y]) {
            ds->parent[root_y] = root_x;
        } else if (ds->rank[root_x] < ds->rank[root_y]) {
            ds->parent[root_x] = root_y;
        } else {
            ds->parent[root_y] = root_x;
            ds->rank[root_x]++; // Increase rank if both trees are equal in rank
        }
    }
}

// Comparator function to sort edges by weight (for Kruskal's algorithm)
int compare_edges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

// Kruskal's algorithm to find the MST (Minimum Spanning Tree)
int kruskal(Graph *graph, Edge result[]) {
    DisjointSet ds;
    init_disjoint_set(&ds, graph->num_nodes);  // Initialize Union-Find for nodes

    qsort(graph->edges, graph->num_edges, sizeof(Edge), compare_edges);  // Sort edges by weight

    int mst_weight = 0, mst_size = 0;

    // Process each edge and add it to the MST if it doesn't form a cycle
    for (int i = 0; i < graph->num_edges && mst_size < graph->num_nodes - 1; i++) {
        Edge current_edge = graph->edges[i];
        int u_set = find(&ds, current_edge.u);  // Find the set of node u
        int v_set = find(&ds, current_edge.v);  // Find the set of node v

        // If u and v are in different sets, add this edge to the MST
        if (u_set != v_set) {
            result[mst_size++] = current_edge;
            mst_weight += current_edge.weight;
            union_sets(&ds, u_set, v_set);  // Union the sets of u and v
        }
    }

    return (mst_size == graph->num_nodes - 1) ? mst_weight : -1;  // If MST is formed, return the total weight, else return -1
}

// Function to add an edge to the graph
void add_edge(Graph *graph, int u, int v, int weight) {
    graph->edges[graph->num_edges++] = (Edge){u, v, weight};  // Add edge to the graph
    
    // Dynamically update the number of nodes based on the largest node index in the graph
    if (u >= graph->num_nodes) graph->num_nodes = u + 1;
    if (v >= graph->num_nodes) graph->num_nodes = v + 1;
}

// Function to remove an edge from the graph
void remove_edge(Graph *graph, int u, int v) {
    // Find the edge to remove
    for (int i = 0; i < graph->num_edges; i++) {
        if (graph->edges[i].u == u && graph->edges[i].v == v) {
            // Shift all edges after the found edge
            for (int j = i; j < graph->num_edges - 1; j++) {
                graph->edges[j] = graph->edges[j + 1];
            }
            graph->num_edges--;  // Decrease the number of edges
            printf("Edge %d -- %d removed.\n", u, v);
            return;
        }
    }
    printf("Edge %d -- %d does not exist.\n", u, v);  // If edge is not found
}

// Function to print the Minimum Spanning Tree (MST)
void print_mst(Edge mst[], int size, int total_weight) {
    if (total_weight == -1) {
        printf("Graph is disconnected. MST cannot be formed.\n");
        return;
    }
    printf("Minimum Spanning Tree (Weight: %d):\n", total_weight);
    for (int i = 0; i < size; i++) {
        printf("%d -- %d (weight: %d)\n", mst[i].u, mst[i].v, mst[i].weight);  // Print each edge in the MST
    }
}

// Function to display the menu options
void menu() {
    printf("\nMenu:\n");
    printf("1. Add Edge\n");
    printf("2. Remove Edge\n");
    printf("3. Display MST\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Main function to interact with the user
int main() {
    Graph graph = {.num_edges = 0, .num_nodes = 0};  // Start with 0 edges and 0 nodes
    Edge mst[MAX_NODES];  // Array to store the MST edges
    int choice;

    while (1) {
        menu();  // Display the menu
        scanf("%d", &choice);  // Read user's choice
        if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
            break;  // Exit the program
        }

        switch (choice) {
            case 1: {  // Add an edge
                int u, v, weight;
                printf("Enter edge (u v weight): ");
                scanf("%d %d %d", &u, &v, &weight);
                add_edge(&graph, u, v, weight);  // Add the edge to the graph
                printf("Edge %d -- %d (weight: %d) added.\n", u, v, weight);
                break;
            }
            case 2: {  // Remove an edge
                int u, v;
                printf("Enter edge to remove (u v): ");
                scanf("%d %d", &u, &v);
                remove_edge(&graph, u, v);  // Remove the edge from the graph
                break;
            }
            case 3: {  // Display the MST
                int total_weight = kruskal(&graph, mst);  // Run Kruskal's algorithm to find MST
                print_mst(mst, graph.num_nodes - 1, total_weight);  // Print the MST
                break;
            }
            default:
                printf("Invalid choice! Please try again.\n");  // Handle invalid choices
        }
    }

    return 0;
}
