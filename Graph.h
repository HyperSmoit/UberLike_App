#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <list>
#include <iterator>
#include <queue>

template <typename Tkey, typename Tvalue> struct info {
    Tkey key;
    Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 private:
    std::list<struct info<Tkey, Tvalue>> *H;
    int capacity;
    int (*hash)(Tkey);

 public:
    Hashtable(int capacity, int (*h)(Tkey)) {
        this->capacity = capacity;
        hash = h;
        H = new std::list<struct info<Tkey, Tvalue>>[capacity];
    }

    ~Hashtable() {
        delete[] H;
    }

    void put(Tkey key, Tvalue value) {
        int hkey = hash(key) % capacity;
        auto p = H[hkey].begin();
        while (p != H[hkey].end()) {
            if (p->key == key) {
                break;
            }
            ++p;
        }
        if (p != H[hkey].end()) {
            p->value = value;
        } else {
            struct info <Tkey, Tvalue> i;
            i.key = key;
            i.value = value;
            H[hkey].push_back(i);
        }
    }
    void print_hashtable() {
        for (int i = 0; i < capacity; i++) {
            std::cout << "HASH = " << i << ": ";
            typename std::list<struct info<Tkey, Tvalue>>::iterator it;
            for (it = H[i].begin(); it != H[i].end(); it++) {
                std::cout << it->value << " | ";
            }
            std::cout << "\n";
        }
    }
    void remove(Tkey key) {
        int hkey = hash(key) % capacity;
        auto p = H[hkey].begin();
        for (auto& it = p.begin(); it != p.end(); ++it) {
            if (p->key == key) {
                H[hkey].erase(it);
            }
        }
    }
    Tvalue get(Tkey key) {
        int hkey = hash(key) % capacity;
        auto p = H[hkey].begin();
        while (p != H[hkey].end()) {
            if (p->key == key) {
                break;
            }
            ++p;
        }
        if (p != H[hkey].end()) {
            return p->value;
        } else {
            // std::cout << "The key does not exist\n";
            return Tvalue();
        }
    }
    bool has_key(Tkey key) {
        int hkey = hash(key) % capacity;
        auto p = H[hkey].begin();
        while (p != H[hkey].end()) {
            if (p->key == key) {
                break;
            }
            ++p;
        }
        if (p != H[hkey].end()) {
            return true;
        } else {
            return false;
        }
    }

  std::list<struct info<Tkey, Tvalue>>* getHashtable() {
    return H;
  }
};

class Cabs {
 public:
    std::string Driver, location;
    int ID, top_dist = 0, top_rides = 0, status = 1;
    double top_rating = 0.0;
    ~Cabs() {}
};

struct Node {
    std::vector<int> neighbors;
};

class Graph {
 private:
    std::vector<Node> nodes;
    int size;

 public:
    // Constructor
    explicit Graph(int size) {
        this->size = size;
        for (int i = 0; i < size; ++i) {
            struct Node elem;
            nodes.push_back(elem);
        }
    }

    // Destructor
    ~Graph() {
    }
    void AddRoad(int src, int dest) {
        nodes[src].neighbors.push_back(dest);
    }

    int distance(int src, int dest) {
    std::vector<bool> visited(size, 0);
    std::vector<int> distance(size, 0);
    std::queue<int> Q;

    distance[src] = 0;
    Q.push(src);
    visited[src] = true;
    while (!Q.empty()) {
         int x = Q.front();
         Q.pop();
         for (unsigned int i = 0; i < nodes[x].neighbors.size(); ++i) {
             if (visited[nodes[x].neighbors[i]]) {
                 continue;
             }
             distance[nodes[x].neighbors[i]] = distance[x] + 1;
             Q.push(nodes[x].neighbors[i]);
             visited[nodes[x].neighbors[i]] = 1;
         }
     }
     return distance[dest];
    }
    bool hasDirectRoad(int src, int dest) {
        for (auto i = nodes[src].neighbors.begin(); i !=
            nodes[src].neighbors.end(); ++i) {
            if (*i == dest) {
                return true;
            }
        }
        return false;
    }

    bool hasRoad(int src, int dest) {
        if (src == dest) {
            return 1;
        }
        std::vector<bool> visited(size, 0);
        for (int i = 0; i < size; ++i) {
            visited[i] = false;
        }
        std::queue <int> Q;
        Q.push(src);
        visited[src] = true;
        while (!Q.empty()) {
            src = Q.front();
            Q.pop();
            for (auto i = nodes[src].neighbors.begin(); i !=
                nodes[src].neighbors.end(); ++i) {
                if (*i == dest) {
                    return true;
                }
                if (!visited[*i]) {
                    visited[*i] = 1;
                    Q.push(*i);
                }
            }
        }
        return 0;
    }

    void RemoveRoad(int src, int dest) {
        for (auto it = nodes[src].neighbors.begin(); it !=
            nodes[src].neighbors.end(); ++it) {
            if (*it == dest) {
                nodes[src].neighbors.erase(it);
                break;
            }
        }
    }
};
int char_hash(std::string str) {
    int S = 0;
    for (unsigned i = 0; i < str.length(); ++i) {
        S += str[i];
    }
    return S;
}


#endif  // GRAPH_H_
