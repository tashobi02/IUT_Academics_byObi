

## Time and Space Complexity Chart

| Algorithm                     | Time             | Space    | Where:                                     |
| ----------------------------- | ---------------- | -------- | ------------------------------------------ |
| Bubble Sort                   | **O(n²)**            | O(1)     | n = elements                               |
| Insertion Sort                | **O(n²)**            | O(1)     | ""                                         |
| Selection Sort                | **O(n²)**            | O(1)     | ""                                         |
| Count Sort                    | **O(n + k) -> O(n)** | O(k)     | n = elements<br>k = range of input, k = 10 |
| Radix Sort<br>(Using Bucket)  | **O(dn)**            | O(n)     | n = elements<br>d = digits (max number)    |
| Radix Sort<br>(Using Counter) | **O(dn)**            | O(n)     | ""                                         |
| DFS & BFS (Using List)        | **O(V + E)**         | O(V + E) | V = Vertex, Edge                           |
| DFS & BFS (Using Matrix)      | **O(V²)**            | O(V²)    | ""                                         |
| Dijkstra                      | **O((V + E) log V)** | O(V + E) | ""                                         |
| Bellman Ford                  | **O(V * E)**         | O(V + E) | ""                                         |
| Floyd Warshall                | **O(V³)**            | O(V³)    | ""                                         |
| Prim's                        | **O((V + E) log V)** | O(V + E) | ""                                         |
| Kruskal's                     | **O(E log E)**       | O(V + E) | ""                                         |
| Fibonacci (No DP)             | **O(2^n)**           | O(n)     | n = nth Fibonacci Number                   |
| Fibonacci (DP)                | **O(n)**             | O(n)     | ""                                         |

---


## Important Notes:


#### Radix Sort Using Counter vs Bucket:

| Feature             | Radix Sort using **Buckets**              | Radix Sort using **Counter (Counting Sort)** |
| ------------------- | ----------------------------------------- | -------------------------------------------- |
| Sorting subroutine  | Manual bucket distribution                | Counting Sort (stable version)               |
| Stability           | Must be manually maintained               | Automatically stable                         |
| Speed (in practice) | Slightly slower (due to copying)          | Faster for large arrays                      |
| Space complexity    | More memory usage (10 buckets of vectors) | Lower, uses fixed-size count/output arrays   |
| Preferred when      | Learning conceptually / visualization     | Performance matters (competitive/production) |

---
#### Adjacency List vs Adjacency Matrix 

| Situation                                | Best Choice      |
| ---------------------------------------- | ---------------- |
| Sparse Graph (E << V²)                   | **Adjacency List**   |
| Dense Graph (E ≈ V²)                     | **Adjacency Matrix** |
| Need fast edge existence check           | **Adjacency Matrix** |
| Need memory efficiency                   | **Adjacency List**   |
| Weighted Graph with many nodes           | **Adjacency List**   |
| All-pairs shortest path (Floyd-Warshall) | **Adjacency Matrix** |

| Feature              | List              | Matrix         |
| -------------------- | ----------------- | -------------- |
| Sparse Graphs    | ✅ Best        | ❌ Wasteful |
| Dense Graphs     | ⚠️ Ok         | ✅ Best     |
| Fast edge lookup | ❌ (O(degree)) | ✅ (O(1))   |
| Space Efficiency | ✅             | ❌          |
| Weighted Graph   | ✅             | ✅          |

| Operation                  | Adjacency List | Adjacency Matrix |
| -------------------------- | -------------- | ---------------- |
| Add Edge               | O(1)       | O(1)         |
| Remove Edge            | O(degree)  | O(1)         |
| Check if edge exists   | O(degree)  | O(1)         |
| Space                  | O(V + E)   | O(V²)        |
| Iterate over neighbors | O(degree)  | O(V)         |

---

#### Dijkstra vs Bellman Ford vs Floyd Warshall

| Feature                       | **Dijkstra’s Algorithm**                 | **Bellman-Ford Algorithm**         | **Floyd-Warshall Algorithm**         |
| ----------------------------- | ---------------------------------------- | ---------------------------------- | ------------------------------------ |
| Purpose                       | Single Source Shortest Path (SSSP)       | Single Source Shortest Path (SSSP) | All Pairs Shortest Path (APSP)       |
| Edge Weights                  | Only non-negative weights                | Can handle negative weights        | Can handle negative weights          |
| Negative Cycle Detection      | ❌ Not supported                          | ✅ Detects negative cycles          | ✅ Detects negative cycles            |
| Time Complexity (Adj. List)   | **O((V + E) log V) with Min Heap**           | **O(V × E)**                           | **O(V³)**                                |
| Time Complexity (Adj. Matrix) | **O(V²)**                                    | **O(V × E)**                           | **O(V³)**                                |
| Space Complexity              | **O(V + E)**                                 | **O(V + E)**                           | **O(V²)**                                |
| Shortest Path Output          | Distances from single source             | Distances from single source       | Distances between all pairs          |
| Path Reconstruction           | Via `parent[]` or `prev[]` array         | Via `parent[]` or `prev[]` array   | Via `next[][]` matrix (optional)     |
| Best Use Case                 | Fast shortest paths with non-neg weights | Graphs with negative edges         | Dense graphs, all-pairs computation  |
| Ease of Implementation        | Moderate                                 | Easy to Moderate                   | Complex (Nested loops, Matrix based) |
| Edge Relaxation               | Once per edge (priority-driven)          | Up to V−1 times per edge           | Updates every pair via every node    |

---

#### Prim's vs Kruskal's

| **Aspect**                      | **Prim’s Algorithm**                                                      | **Kruskal’s Algorithm**                                                |
| ------------------------------- | ------------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| Approach                        | Greedy + Growing a tree from a single node                                | Greedy + Building MST by picking edges                                 |
| Works on                        | Connected, undirected, weighted graphs                                    | Connected, undirected, weighted graphs                                 |
| Type of algorithm               | Greedy                                                                    | Greedy                                                                 |
| Starting point                  | Starts with a single node                                                 | Starts with an empty forest (no edges)                                 |
| Core operation                  | Selects the minimum-weight edge from the visited set to an unvisited node | Selects the minimum-weight edge that connects two different components |
| Data structures used            | Priority queue (Min Heap)                                                 | Disjoint Set Union (Union-Find)                                        |
| Edge selection criteria         | From current MST to a new vertex with least weight                        | Edge with smallest weight that doesn’t form a cycle                    |
| Cycle handling                  | Avoids cycles by not revisiting visited nodes                             | Explicitly checks and avoids cycles using Union-Find                   |
| Graph representation        | **Adjacency List / Matrix efficient**                                     | **Edge List preferred**                                                |
| Time Complexity (Optimized) | **O((V + E) log V) using Min Heap**                                       | **O(E log E) with efficient DSU**                                      |
| Space Complexity            | **O(V + E)**                                                              | **O(V + E)**                                                           |
| Best for                        | Dense graphs (more edges)                                                 | Sparse graphs (fewer edges)                                            |
| Edge cases                      | Doesn’t work on disconnected graphs                                       | Can handle disconnected graphs (gives forest)                          |
| Multiple Components Support     | ❌ Not directly (for disconnected graphs)                                  | ✅ Can form minimum spanning forest                                     |

--- 

