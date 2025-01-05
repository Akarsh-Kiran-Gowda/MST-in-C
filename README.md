# Dynamic MST in C
The Minimum Spanning Tree (MST) is a fundamental concept in graph theory, widely used in real
world applications such as network design, transportation systems, and resource optimization. An MST 
connects all the vertices of a graph with the minimum possible total edge weight, ensuring no cycles 
are formed. However, in dynamic systems where graphs are subject to frequent updates, recalculating 
the MST from scratch for every change can be computationally expensive. This necessitates the 
development of efficient algorithms capable of maintaining the MST dynamically.

The concept of a Dynamic Minimum Spanning Tree (DMST) addresses this need by enabling the MST 
to adapt to changes in the graph, such as the addition or deletion of edges. By leveraging advanced 
data structures and algorithms, the DMST ensures that updates are handled in a time-efficient manner 
without requiring a complete re-computation. This capability is particularly important in applications 
involving real-time systems, such as telecommunication networks, where changes in topology occur 
frequently. 

This project focuses on implementing a DMST using Kruskal's algorithm in C programming. Kruskal’s 
algorithm is a greedy approach that constructs the MST by iteratively adding the smallest available 
edge that does not form a cycle. To support dynamic operations, the implementation integrates a 
Union-Find data structure, which efficiently manages graph connectivity and supports the merging of 
disjoint sets. 

Additionally, the project introduces an interactive menu-driven interface, allowing users to add or 
remove edges and view the updated MST in real time. This functionality makes the implementation 
accessible and practical for educational and experimental purposes. By achieving this, the project not 
only demonstrates the theoretical principles of graph algorithms but also highlights their relevance in 
solving dynamic and computationally intensive problems. 

Through this project, we aim to provide an efficient and user-friendly solution for maintaining MSTs 
in dynamic graphs, thereby bridging the gap between theoretical concepts and practical applications. 
