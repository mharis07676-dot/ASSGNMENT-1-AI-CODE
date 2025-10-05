#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Route {
    int from, to;
    double probability;
};

class Network {
private:
    vector<Route> routes;

public:
    // Add a new route
    void addRoute(int from, int to, double probability) {
        routes.push_back({from, to, probability});
    }

    // Display all routes
    void displayRoutes() {
        cout << "\nAvailable Routes:\n";
        for (auto &r : routes) {
            cout << "Node " << r.from << " → Node " << r.to
                 << " | Success Probability: "
                 << fixed << setprecision(2) << r.probability << endl;
        }
    }

    // Find the most reliable route (direct or 2-hop)
    double mostReliableRoute(int start, int end, bool show = true) {
        double maxProb = 0.0;
        string bestPath = "None";

        for (auto &r1 : routes) {
            if (r1.from == start) {
                // Direct route
                if (r1.to == end && r1.probability > maxProb) {
                    maxProb = r1.probability;
                    bestPath = "Node " + to_string(start) + " → Node " + to_string(end);
                }

                // Two-step route
                for (auto &r2 : routes) {
                    if (r2.from == r1.to && r2.to == end) {
                        double total = r1.probability * r2.probability;
                        if (total > maxProb) {
                            maxProb = total;
                            bestPath = "Node " + to_string(start) + " → Node " +
                                       to_string(r1.to) + " → Node " + to_string(end);
                        }
                    }
                }
            }
        }

        if (show) {
            cout << "\nMost Reliable Route from " << start << " to " << end << ":\n";
            if (maxProb > 0)
                cout << bestPath << "\nTotal Probability: "
                     << fixed << setprecision(4) << maxProb << endl;
            else
                cout << "No valid route found.\n";
        }

        return maxProb;
    }

    // Clear all routes
    void clear() {
        routes.clear();
    }
};

int main() {
    srand(time(0));
    cout << "===Maximizing Probability in Route Selection ===\n";

    Network network;
    double maxProb[10];

    // ---------- 10 Random Networks ----------
    for (int i = 0; i < 10; i++) {
        cout << "\n--- Network " << i + 1 << " ---\n";
        network.clear();

        int numRoutes = rand() % 6 + 5; // 5–10 routes
        for (int r = 0; r < numRoutes; r++) {
            int from = rand() % 10 + 1;
            int to = rand() % 10 + 1;
            if (from != to) {
                double prob = (rand() % 50 + 50) / 100.0; // 0.5–1.0
                network.addRoute(from, to, prob);
            }
        }

        network.displayRoutes();

        int start = rand() % 10 + 1;
        int end = rand() % 10 + 1;
        while (end == start)
            end = rand() % 10 + 1;

        maxProb[i] = network.mostReliableRoute(start, end);
    }

    // ---------- Histogram ----------
    cout << "\n=== Histogram of Maximum Probabilities ===\n";
    for (int i = 0; i < 10; i++) {
        cout << "Network " << setw(2) << i + 1 << ": ";
        int stars = int(maxProb[i] * 20);
        for (int s = 0; s < stars; s++) cout << "*";
        cout << " (" << fixed << setprecision(3) << maxProb[i] << ")\n";
    }

    return 0;
}
