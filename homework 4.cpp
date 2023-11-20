#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
// Constants for grid size and initial critter counts
const int GRID_SIZE = 20;
const int INITIAL_DOODLEBUGS = 5;
const int INITIAL_ANTS = 100;

// Directions for movement
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
// Critter types
enum class CritterType {
    ANT,
    DOODLEBUG
};
class Organism {
protected:
    int row;
    int column;
    int timeSteps;
public:
    Organism(int row, int column) : row(row), column(column), timeSteps(0) {}
    int getRow() const { return row; }
    int getColumn() const { return column; }
    int getTimeSteps() const { return timeSteps; }
    virtual void move(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) = 0;
    virtual CritterType getType() const = 0;
    virtual void breed(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) = 0;
    virtual void starve(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) {}
    virtual ~Organism() {}
};

class Ant : public Organism {
public:
    Ant(int r, int c) : Organism(r,c) {}
    CritterType getType() const override { return CritterType::ANT; }
    void move(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) override {
         int newRow = getRow();
         int newCol = getColumn();
         Direction direction = static_cast<Direction>(rand() % 4);
         switch (direction) {
             case Direction::UP:
                 newRow--;
                 break;
             case Direction::DOWN:
                 newRow++;
                 break;
             case Direction::LEFT:
                 newCol--;
                 break;
             case Direction::RIGHT:
                 newCol++;
                 break;
         }
         if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE &&
             grid[newRow][newCol] == nullptr) {
             grid[newRow][newCol] = this;
             grid[getRow()][getColumn()] = nullptr;
             row = newRow;
             column = newCol;
             timeSteps++;
             movedCritters.push_back(this);
         }
     }
     void breed(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) {
         if (timeSteps >= 3) {
             Direction direction = static_cast<Direction>(std::rand() % 4);
             int newRow = row;
             int newCol = column;

             switch (direction) {
                 case Direction::UP:
                     newRow--;
                     break;
                 case Direction::DOWN:
                     newRow++;
                     break;
                 case Direction::LEFT:
                     newCol--;
                     break;
                 case Direction::RIGHT:
                     newCol++;
                     break;
             }
             if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) {
                 Ant* newAnt = new Ant(newRow, newCol);
                 grid[newRow][newCol] = newAnt;
                 movedCritters.push_back(newAnt);
             }
             timeSteps = 0;
         }
    }
};
class Doodlebug : public Organism {
private:
    int timeSinceLastMeal;

public:
    Doodlebug(int r, int c) : Organism(r, c), timeSinceLastMeal(0) {}

    CritterType getType() const override { return CritterType::DOODLEBUG; }

    void move(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) override {
        // Check for nearby ants
        vector<pair<int, int>> possibleMoves;
        if (row > 0 && grid[row - 1][column] != nullptr && grid[row - 1][column]->getType() == CritterType::ANT) {
            possibleMoves.push_back(make_pair(row - 1, column));
        }
        if (row < GRID_SIZE - 1 && grid[row + 1][column] != nullptr && grid[row + 1][column]->getType() == CritterType::ANT) {
            possibleMoves.push_back(make_pair(row + 1, column));
        }
        if (column > 0 && grid[row][column - 1] != nullptr && grid[row][column - 1]->getType() == CritterType::ANT) {
            possibleMoves.push_back(make_pair(row, column - 1));
        }
        if (column < GRID_SIZE - 1 && grid[row][column + 1] != nullptr && grid[row][column + 1]->getType() == CritterType::ANT) {
            possibleMoves.push_back(make_pair(row, column + 1));
        }
        if (!possibleMoves.empty()) {
            // Move to a cell with an ant and eat it
            pair<int, int> move = possibleMoves[rand() % possibleMoves.size()];
            int newRow = move.first;
            int newCol = move.second;
            delete grid[newRow][newCol]; // Delete the eaten ant
            grid[newRow][newCol] = this;
            grid[row][column] = nullptr;
            row = newRow;
            column = newCol;
            timeSteps++;
            timeSinceLastMeal = 0;
            movedCritters.push_back(this);
        } else {
            // No nearby ants, move like an ant
            Direction direction = static_cast<Direction>(rand() % 4);
            int newRow = row;
            int newCol = column;

            switch (direction) {
                case Direction::UP:
                    newRow--;
                    break;
                case Direction::DOWN:
                    newRow++;
                    break;
                case Direction::LEFT:
                    newCol--;
                    break;
                case Direction::RIGHT:
                    newCol++;
                    break;
            }

            if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) {
                grid[newRow][newCol] = this;
                grid[row][column] = nullptr;
                row = newRow;
                column = newCol;
                timeSteps++;
                timeSinceLastMeal++;
                movedCritters.push_back(this);
            }
        }
    }
    void breed(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) override {
        if (timeSteps >= 8) {
            // Find an empty adjacent cell to breed
            vector<Direction> possibleDirections;
            if (row > 0 && grid[row - 1][column] == nullptr) {
                possibleDirections.push_back(Direction::UP);
            }
            if (row < GRID_SIZE - 1 && grid[row + 1][column] == nullptr) {
                possibleDirections.push_back(Direction::DOWN);
            }
            if (column > 0 && grid[row][column - 1] == nullptr) {
                possibleDirections.push_back(Direction::LEFT);
            }
            if (column < GRID_SIZE - 1 && grid[row][column + 1] == nullptr) {
                possibleDirections.push_back(Direction::RIGHT);
            }
            if (!possibleDirections.empty()) {
                Direction direction = possibleDirections[rand() % possibleDirections.size()];
                int newRow = row;
                int newCol = column;
                switch (direction) {
                    case Direction::UP:
                        newRow--;
                        break;
                    case Direction::DOWN:
                        newRow++;
                        break;
                    case Direction::LEFT:
                        newCol--;
                        break;
                    case Direction::RIGHT:
                        newCol++;
                        break;
                }
                Doodlebug* newDoodlebug = new Doodlebug(newRow, newCol);
                grid[newRow][newCol] = newDoodlebug;
                movedCritters.push_back(newDoodlebug);
            }
            timeSteps = 0;
        }
    }
    void starve(vector<vector<Organism*>>& grid, vector<Organism*>& movedCritters) {
        if (timeSinceLastMeal >= 3) {
            grid[row][column] = nullptr;
            for (size_t i = 0; i < movedCritters.size(); ++i) {
                if (movedCritters[i] == this) {
                    for (size_t j = i; j < movedCritters.size() -
                    1; ++j) {
                        swap(movedCritters[j], movedCritters[j+1]);
                    }
                    movedCritters.pop_back();
                }
            }
            delete this;
        }
    }
};
// Function to print the grid
void printGrid(const vector<vector<Organism*>>& grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == nullptr) {
                cout << "-";
            } else if (grid[i][j]->getType() == CritterType::ANT) {
                cout << "o";
            } else {
                cout << "X";
            }
        }
        cout << endl;
    }
}
int main() {
    srand(time(0));
    vector<vector<Organism*>> grid(GRID_SIZE, vector<Organism*>(GRID_SIZE, nullptr));
    vector<Organism*> movedCritters;

    // Create initial ants
    for (int i = 0; i < INITIAL_ANTS; i++) {
        int row = rand() % GRID_SIZE;
        int column = rand() % GRID_SIZE;

        if (grid[row][column] == nullptr) {
            grid[row][column] = new Ant(row, column);
            movedCritters.push_back(grid[row][column]);
        } else {
            i--;
        }
    }
    // Create initial doodlebugs
    for (int i = 0; i < INITIAL_DOODLEBUGS; i++) {
        int row = rand() % GRID_SIZE;
        int column = rand() % GRID_SIZE;

        if (grid[row][column] == nullptr) {
            grid[row][column] = new Doodlebug(row, column);
            movedCritters.push_back(grid[row][column]);
        } else {
            i--;
        }
    }
    int timeSteps = 0;
    while (true) {
        cout << "Time Step: " << timeSteps << endl;
        printGrid(grid);
        cout << "Press Enter to move to the next time step (or q to quit)..." << endl;
        string input;
        getline(cin, input);
        if (input == "q") {
            break;
        }
        // Move doodlebugs first
        for (Organism* critter : movedCritters) {
            if (critter->getType() == CritterType::DOODLEBUG) {
                critter->move(grid, movedCritters);
            }
        }
        // Move ants
        for (Organism* critter : movedCritters) {
            if (critter->getType() == CritterType::ANT) {
                critter->move(grid, movedCritters);
            }
        }
        // Breed and starve
        for (Organism* critter : movedCritters) {
            critter->breed(grid, movedCritters);
            if (critter->getType() == CritterType::DOODLEBUG) {
                critter->starve(grid, movedCritters);
            }
        }
        timeSteps++;
    }
    // Clean up memory
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            delete grid[i][j];
        }
    }
}

