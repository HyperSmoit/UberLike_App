#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include "./Graph.h"
void go_offline(std::ifstream& fin, std::vector<Cabs>Drivers, int nr_drivers) {
	std::string driver;
	fin >> driver;
	for (int i = 0; i < nr_drivers; ++i) {
		if(driver.compare(Drivers[i].Driver) == 0) {
			Drivers[i].status = 0;
			break;
		}
	}
}

void print_info(std::ifstream& fin, std::vector<Cabs>&Drivers, int nr_drivers) {
	std::string driver, info;
	fin >> info >> driver;
	for (int i = 0; i < nr_drivers; ++i) {
		if (driver.compare(Drivers[i].Driver) == 0) {
			std::cout << Drivers[i].Driver << ": " << Drivers[i].location <<
			' ';
			if (Drivers[i].top_rating == 0) {
				std::cout << "0.00" << ' ';
			} else {
				std::cout << Drivers[i].top_rating / Drivers[i].top_rides << ' ';
			}
			std::cout << Drivers[i].top_rides << ' ' << Drivers[i].top_dist <<
			' ';
			if (Drivers[i].status == 0) {
				std::cout << "offline\n";
			} else {
				std::cout << "online\n";
			}
		}
	}
}
void add_Driver(std::ifstream& fin, std::vector<Cabs>&Drivers,
	int &nr_drivers) {
	std::string driver, location;
    fin >> driver >> location;
    int ok = 0;
    for (int i = 0; i < nr_drivers; ++i) {
       	if (driver.compare(Drivers[i].Driver) == 0) {
       		Drivers[i].location = location;
       		Drivers[i].status = 1;
       		ok = 1;
            break;
        }
    }
    if (ok == 0) {
       	Drivers[nr_drivers].Driver = driver;
       	Drivers[nr_drivers].location = location;
       	nr_drivers++;
    }
}

void print_top_rides(std::vector<Cabs>&Drivers, int nr_drivers) {
	for (int i = 0; i < nr_drivers - 1; ++i) {
		for (int j = i; j < nr_drivers; ++j) {
			if (Drivers[i].top_rides < Drivers[j].top_rides ||
				(Drivers[i].top_rides == Drivers[j].top_rides &&
				Drivers[i].Driver.compare(Drivers[j].Driver) > 0)) {
				Cabs aux;
				aux = Drivers[i];
				Drivers[i] = Drivers[j];
				Drivers[j] = aux;
			}
		}
	}
}
void print_top_dist(std::vector<Cabs>&Drivers, int nr_drivers) {
	for (int i = 0; i < nr_drivers - 1; ++i) {
		for (int j = i; j < nr_drivers; ++j) {
			if (Drivers[i].top_dist < Drivers[j].top_dist ||
				(Drivers[i].top_dist == Drivers[j].top_dist &&
				Drivers[i].Driver.compare(Drivers[j].Driver) > 0)) {
				Cabs aux;
				aux = Drivers[i];
				Drivers[i] = Drivers[j];
				Drivers[j] = aux;
			}
		}
	}
}
void print_top_rating(std::vector<Cabs>&Drivers, int nr_drivers) {
	for (int i = 0; i < nr_drivers - 1; ++i) {
		for (int j = i; j < nr_drivers; ++j) {
			if (Drivers[i].top_rating < Drivers[j].top_rating ||
				(Drivers[i].top_rating == Drivers[j].top_rating &&
				Drivers[i].Driver.compare(Drivers[j].Driver) > 0)) {
				Cabs aux;
				aux = Drivers[i];
				Drivers[i] = Drivers[j];
				Drivers[j] = aux;
			}
		}
	}
}
void top_calls(std::ifstream& fin, std::vector<Cabs>&Drivers,
	int nr_drivers) {
	std::string str;
	int n;
	fin >> str >> n;
	getline(fin, str);
	if (n > nr_drivers) {
		n = nr_drivers;
	}
	if (str[3] == 'r' && str[4] == 'i') {
        print_top_rides(Drivers, nr_drivers);
        for (int i = 0; i < n; ++i) {
			std::cout << Drivers[i].Driver << ':' << Drivers[i].top_rides << ' ';
		}
		std::cout << '\n';
    }
    if (str[3] == 'r' && str[4] == 'a') {
        print_top_rating(Drivers, nr_drivers);
        for (int i = 0; i < n; ++i) {
            std::cout << Drivers[i].Driver << ':' << Drivers[i].top_rating
            << ' ';
        }
        std::cout << '\n';
    }
    if (str[3] == 'd') {
        print_top_dist(Drivers, nr_drivers);
        for (int i = 0; i < n; ++i) {
        	std::cout << Drivers[i].Driver << ':' << Drivers[i].top_dist << ' ';
        }
        std::cout << '\n';
    }

class solver {
    int n;
    Graph *G;
    Hashtable<std::string, int> *Hash;

 public:
        void task1_solver(std::ifstream& fin, std::ofstream& fout) {
            int m;
            std::string str;
            fin >> n >> m;
            G = new Graph(n);
            // Creating a Hashtable for nodes
            Hash = new Hashtable<std::string, int>(n, &char_hash);
            for (int i = 0; i < n; ++i) {
                fin >> str;
                Hash->put(str, i);
            }
            for (int i = 0; i < m; ++i) {
                std::string start, end;
                fin >> start >> end;
                // Adding a road for a node start to a node end
                G->AddRoad(Hash->get(start), Hash->get(end));
                }
            fin >> m;
            for (int i = 0; i < m; ++i) {
                std::string start, end;
                fin >> start >> end;
                // Checking if there's a road between node start and node end
                if (G->hasRoad(Hash->get(start), Hash->get(end)) == true) {
                    fout << 'y' << std::endl;
                } else {
                    fout << 'n' << std::endl;
                }
            }
        }

        void task2_solver(std::ifstream& fin, std::ofstream& fout) {
            int m;
            std::string str;
            fin >> m;
            for (int i = 0; i < m; ++i) {
                std::string start, end;
                fin >> start >> end;
                // In case there's a road between node start and node end
                // we find the distance between those two, otherwise, we print
                // -1
                if (G->hasRoad(Hash->get(start), Hash->get(end)) == true) {
                    fout << G->distance(Hash->get(start), Hash->get(end)) <<
                '\n';
                } else {
                    fout << "-1" << std::endl;
                }
            }
        }

        void task3_solver(std::ifstream& fin, std::ofstream& fout) {
            int m;
            fin >> m;
            for (int i = 0; i < m; ++i) {
                char c_or_q, decision;
                std::string start, end;
                fin >> c_or_q >> start >> end >> decision;
                if (c_or_q == 'c') {
                    if (decision == '0') {
                    	// Adding a road
                        G->AddRoad(Hash->get(start), Hash->get(end));
                    }
                    if (decision == '1') {
                    	// Removing a road, wheter is bidirectional or not
                            G->RemoveRoad(Hash->get(start), Hash->get(end));
                            G->RemoveRoad(Hash->get(end), Hash->get(start));
                    }
                    if (decision == '2') {
                    	// Making bidirectional roads
                        if (!G->hasDirectRoad(Hash->get(start),
                            Hash->get(end))) {
                            G->AddRoad(Hash->get(start), Hash->get(end));
                        }
                        if (!G->hasDirectRoad(Hash->get(end),
                            Hash->get(start))) {
                            G->AddRoad(Hash->get(end), Hash->get(start));
                        }
                    }
                    if (decision == '3') {
                    	// Reversing the way
                        if (!G->hasDirectRoad(Hash->get(start),
                            Hash->get(end)) &&
                            G->hasDirectRoad(Hash->get(end),
                                Hash->get(start))) {
                            G->RemoveRoad(Hash->get(end), Hash->get(start));
                            G->AddRoad(Hash->get(start), Hash->get(end));
                        } else if (!G->hasDirectRoad(Hash->get(end),
                            Hash->get(start)) &&
                            G->hasDirectRoad(Hash->get(start),
                                Hash->get(end))) {
                            G->RemoveRoad(Hash->get(start), Hash->get(end));
                            G->AddRoad(Hash->get(end), Hash->get(start));
                        }
                    }
                } else {
                    if (decision == '0') {
                    	// Checking if there's a road
                        if (G->hasRoad(Hash->get(start), Hash->get(end))) {
                            fout << 'y' << std::endl;
                        } else {
                            fout << 'n' << std::endl;
                        }
                    }
                    if (decision == '1') {
                    	// If there's a road, find the distance and display it
                    	// Otherwise, display -1
                        if (G->hasRoad(Hash->get(start), Hash->get(end))) {
                            fout << G->distance(Hash->get(start),
                                Hash->get(end)) << std::endl;
                        } else {
                            fout << "-1" << std::endl;
                        }
                    }
                    if (decision == '2') {
                    	// Checking if there's a road from a node to another
                    	// Through an adjacent node and display distance
                        std::string adj;
                        fin >> adj;
                        if (G->hasRoad(Hash->get(start), Hash->get(adj)) &&
                            G->hasRoad(Hash->get(adj), Hash->get(end))) {
                            fout << G->distance(Hash->get(start),
                                Hash->get(adj)) +
                                G->distance(Hash->get(adj), Hash->get(end))
                                << '\n';
                        } else {
                            fout << "-1" << std::endl;
                        }
                    }
                }
            }
            delete G;
            delete Hash;
        }
};

#endif  // SOLVER_H_
