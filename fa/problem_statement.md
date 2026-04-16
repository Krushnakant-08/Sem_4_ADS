# Problem Statement
## Train Management System Using B+ Tree and Dijkstra's Algorithm

---

### Background

Railway systems handle thousands of trains daily across hundreds of stations. Two
fundamental challenges in any railway management system are:

1. **Efficiently storing and retrieving train schedule data** as trains are added.
2. **Finding the shortest travel route** between any two stations for passengers.

Traditional linear data structures become too slow as the number of trains and
stations grows. This project addresses both challenges using advanced data
structures and algorithms.

---

### Problem Statement

Design and implement a **Train Management System** for a regional railway network
covering the following 8 stations:

| Index | Station  |
|-------|----------|
| 0     | CSMT     |
| 1     | Dadar    |
| 2     | Kalyan   |
| 3     | Karjat   |
| 4     | Lonavala |
| 5     | Daund    |
| 6     | Nashik   |
| 7     | Sinnar   |

The system must solve **two sub-problems**:

---

### Sub-Problem 1 – Train Schedule Management using B+ Tree (`tree.cpp`)

**Problem:**
The railway authority needs to maintain a dynamic database of train schedules.
Each train record contains:
- **Train ID** (unique identifier)
- **Source Station** (starting point)
- **Destination Station** (ending point)
- **Arrival Time**

As new trains are added, the system must:
- Store records in sorted order by Train ID.
- Support fast search by Train ID.
- Display all schedules in ascending order of Train ID at any time.

**Solution — B+ Tree (Order 4):**

A **B+ Tree** is used as the underlying data structure because:
- It provides **O(log n)** time for both insertion and search.
- All actual records are stored only in **leaf nodes**, keeping internal nodes
  lightweight (index-only).
- Leaf nodes are connected as a **doubly-linked list**, enabling efficient
  **in-order (sorted) traversal** without any recursive tree walk.
- It is the industry-standard structure used in database engines (MySQL, Oracle)
  for exactly this purpose.

**Train Records Stored:**

| Train ID | From     | To       | Arrival Time |
|----------|----------|----------|--------------|
| 30       | CSMT     | Dadar    | 5.00 PM      |
| 40       | CSMT     | Karjat   | 10.30 PM     |
| 45       | Kalyan   | Daund    | 10.00 AM     |
| 50       | Dadar    | Lonavala | 9.00 AM      |
| 65       | Kalyan   | Sinnar   | 12.30 PM     |
| 70       | Dadar    | Nashik   | 8.00 PM      |
| 85       | Lonavala | Dadar    | 7.45 AM      |
| 90       | CSMT     | Kalyan   | 1.15 PM      |

**Expected Output:**
- B+ Tree structure showing internal index nodes and leaf data nodes.
- All records printed in sorted order via leaf linked-list traversal.
- Search result showing Source → Destination and arrival time for a given Train ID.

---

### Sub-Problem 2 – Shortest Route Finding using Dijkstra's Algorithm (`graph.cpp`)

**Problem:**
A passenger at any station wants to travel to another station. Given a network of
stations connected by direct train routes with known distances (in km), find:
- The **minimum total distance** between the source and destination station.
- The **exact sequence of intermediate stations** (route) to take.

**Solution — Weighted Graph + Dijkstra's Algorithm:**

The station network is modelled as a **weighted undirected graph** where:
- **Vertices** = Train stations
- **Edges** = Direct train routes
- **Weights** = Distance in km

**Dijkstra's Algorithm** is used because:
- It finds the **shortest path from a single source** to all other vertices.
- It works correctly for graphs with **non-negative weights** (distances).
- A **parent array** is maintained alongside distances to reconstruct the
  exact route taken.

**Railway Network (Direct Routes):**

| From     | To       | Distance |
|----------|----------|----------|
| CSMT     | Dadar    | 8 km     |
| CSMT     | Kalyan   | 60 km    |
| Dadar    | Kalyan   | 54 km    |
| Dadar    | Nashik   | 160 km   |
| Kalyan   | Karjat   | 45 km    |
| Kalyan   | Nashik   | 120 km   |
| Karjat   | Lonavala | 60 km    |
| Lonavala | Daund    | 75 km    |
| Daund    | Sinnar   | 90 km    |
| Nashik   | Sinnar   | 30 km    |

**Expected Output:**
- All shortest distances from the chosen source station to every other station.
- The exact route displayed for each destination.
- Specific shortest distance and route for the user-chosen destination.

---

### Combined System Overview

```
              TRAIN MANAGEMENT SYSTEM
              ========================

  +-------------------------+    +---------------------------+
  |       tree.cpp          |    |       graph.cpp           |
  |   B+ Tree (Order 4)     |    |  Adjacency Matrix Graph   |
  |-------------------------|    |---------------------------|
  | - Store train schedules |    | - Model station network   |
  | - Source & Destination  |    | - 8 stations, 10 routes   |
  | - Fast search by ID     |    | - Dijkstra's shortest path|
  | - Sorted display        |    | - Route reconstruction    |
  +-------------------------+    +---------------------------+
             |                              |
             +----------+  +---------------+
                        |  |
             [ Efficient Railway Information System ]
```

---

### Data Structures & Algorithms Used

| Concept                            | File         |
|------------------------------------|--------------|
| B+ Tree — Insert with node split   | `tree.cpp`   |
| B+ Tree — Leaf linked-list search  | `tree.cpp`   |
| Weighted Graph (Adjacency Matrix)  | `graph.cpp`  |
| Dijkstra's Shortest Path           | `graph.cpp`  |
| Path Reconstruction (Parent Array) | `graph.cpp`  |

---

### Complexity Analysis

| Operation           | Data Structure | Time Complexity |
|---------------------|----------------|-----------------|
| Insert train record | B+ Tree        | O(log n)        |
| Search by Train ID  | B+ Tree        | O(log n)        |
| Display all records | B+ Tree (leaf) | O(n)            |
| Shortest path       | Dijkstra's     | O(V²)           |
| Route reconstruction| Parent Array   | O(V)            |
