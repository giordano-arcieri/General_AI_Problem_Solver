#ifndef GENERAL_AI_HPP
#define GENERAL_AI_HPP

/*

SMALL DESCRIPTION:
The General_AI class is an object that is used to solve any problem that can be represented as a state space search problem.
You can use this class to solve any problem, as long as you know what the initial state is, what the goal state is, and what the possible actions/operators are to go from one state to another.

WHAT THE CLASS NEEDS TO WORK:
The rappresentation of the initial state and final state will just be another class object, any object you choose to implement, as long as it has the following methods:

    Precondition: The calling object is a valid object of the class
    Postcondition: Return true if the calling object is the goal state, false otherwise
    bool is_goal() const;

    Precondition: The calling object is a valid object of the class
    Postcondition: Returns a vector of all the possible states that can be reached from the calling object. All possible next states.
    std::vector<T> get_successors() const;

If you do not want to implement those methods as member functions of the class, you can pass them as function pointers to the General_AI constructor. If none are passed in, or NULL is passed it assumes those methods are implemented as member functions of the class.

ADT:

Precondition: If the get_successors and is_goal function pointers are not passed in, the T class must have the methods implemented.
Postcondition: It creates a valid General_AI object that uses the passed in searching alghorithm to solve the problem. Default is breadth first search.
General_AI(T initial_state, bool (*is_goal)(T) = NULL, std::vector<T> (*get_successors)(T) = NULL, searching_algorithm = BFS);

Precondition: The calling object is a valid General_AI object
Postcondition: It will return a vector of the states that lead from the initial state to the goal state.
std::vector<T> solve();

Precondition: The passed in argument is a vector of T objects where T has the << operator overloaded to be used with cout.
Postcondition: It will print the vector one item at a time to the cout stream. // This is a non member function so it should not have a calling object. ai.print_solution() is not valid.
void print_solution(std::vector<T> solution);

MORE ON CONSTRUCTOR:
This is what the constructer takes in:
    - (initial state): This is required. It is the initial state of the problem.
    - (is_goal): This is optional. It is a function pointer that returns true if the passed in state is the goal state, false otherwise. If not passed in, it assumes the T class has a is_goal method.
    - (get_successors): This is optional. It is a function pointer that returns a vector of all the possible states that can be reached from the passed in state. If not passed in, it assumes the T class has a get_successors method.
    - (searching_algorithm): This is the searching algorithm that will be used to solve the problem. Which based on the specific problem this is what has the biggest effect on space and time complexity. The default is breadth first search. but here are the constats it could take in:
        BFS: Breadth First Search
        DFS: Depth First Search

*/

#include <vector>
#include <ostream>
#include <queue>
#include <algorithm>
#include "Node.hpp"

enum searching_algorithm
{
    BFS,
    DFS
};

template <typename T>
class General_AI
{
private:
    T initial_state;
    bool (*is_goal)(T);
    std::vector<T> (*get_successors)(T);
    searching_algorithm algorithm;

public:
    // Precondition: If the get_successors and is_goal function pointers are not passed in, the T class must have the methods implemented.
    // Postcondition: It creates a valid General_AI object that uses the passed in searching alghorithm to solve the problem. Default is breadth first search.
    General_AI(T initial_state, bool (*is_goal)(T) = NULL, std::vector<T> (*get_successors)(T) = NULL, searching_algorithm algorithm = BFS);

    // Precondition: The calling object is a valid General_AI object
    // Postcondition: It will return a vector of the states that lead from the initial state to the goal state.
    std::vector<T> solve() const;

    friend std::ostream &operator<<(std::ostream &os, const General_AI<T> &ai)
    {
        os << "IS: " << ai.initial_state;
        os << "\nGoal: " << ai.is_goal;
        os << "\nGet Suc: " << ai.get_successors;
        os << "\nAlgo: " << ai.algorithm;

        return os;
    }

private:
    std::vector<T> solve_BFS() const;
    std::vector<T> solve_DFS() const;
};

template <typename T>
General_AI<T>::General_AI(T initial_state, bool (*is_goal)(T), std::vector<T> (*get_successors)(T), searching_algorithm algorithm)
{
    this->initial_state = initial_state;
    this->is_goal = is_goal;
    this->get_successors = get_successors;
    this->algorithm = algorithm;
}

template <typename T>
std::vector<T> General_AI<T>::solve() const
{
    switch (this->algorithm)
    {
    case BFS:
        return solve_BFS();
        break;

    case DFS:
        return solve_DFS();
        break;

    default:
        throw std::logic_error("Unsupported algorithm type. Check the searching_algorithm enum passed in the General_AI constructor.");
    }
}

// Precondition: The passed in argument is a vector of T objects where T has the << operator overloaded to be used with cout.
// Postcondition: It will print the vector one item at a time to the cout stream.
template <typename T>
void print_solution(const std::vector<T> &solution)
{
    std::cout << "Printing solution:\n\n";
    int step = 1;
    for (T item : solution)
    {
        std::cout << "Step " << step++ << ":\n";
        std::cout << item << std::endl;
    }
}

template <typename T>
std::vector<T> General_AI<T>::solve_BFS() const
{
    std::cout << "Solving with BFS..." << std::endl;

    std::vector<T> solution; // This will keep track of the states to go from initial state to solution state
    std::vector<T> viseted;  // This will keep track of the states we have already visited

    // Check if the initial state is the solution state and if it is return solution
    if (this->is_goal(this->initial_state))
    {
        std::cout << "Solution Found!\n";
        return std::vector<T>{this->initial_state};
    }
    viseted.push_back(this->initial_state);

    // Create an OPEN queue with the initial node, I, (initial-state)
    std::queue<Node<T>> bsf_queue;
    bsf_queue.push(this->initial_state);

    // 2 OUTCOME=False
    bool outcome = false; // This rappresents weather or not we found a solution

    // 3 Repeat while OPEN list is empty and OUTCOME is true
    while (!(bsf_queue.empty() || outcome))
    {
        // Remove the first node from OPEN list, N
        Node<T> N = bsf_queue.front();
        bsf_queue.pop();

        // If N has successors then Generate the successors of N
        std::vector<T> successors = this->get_successors(N.value);
        if (!successors.empty())
        {
            for (auto successor : successors)
            {
                // Check if state has already been visited if it has continue
                if (std::find(viseted.begin(), viseted.end(), successor) != viseted.end())
                {
                    continue;
                }

                // Visit node
                viseted.push_back(successor);

                // Create pointers from the successors to N
                Node<T> nodeSuccessor(successor);
                nodeSuccessor.next = std::make_shared<Node<T>>(N);

                // If a successor is a goal node then OUTCOME=True
                if (this->is_goal(successor))
                {
                    std::cout << "Solution Found!\n";

                    // Create a path from I to N through the pointers

                    // Get size of solution
                    size_t size = 1;
                    Node<T> temp = nodeSuccessor;
                    while (temp.next != nullptr)
                    {
                        size++;
                        temp = *temp.next;
                    }

                    temp = nodeSuccessor;

                    solution.resize(size);
            
                    // Fill the vector in reverse order
                    for (int i = size - 1; i > 0; i--)
                    {
                        solution[i] = temp.value;
                        temp = *temp.next;
                    }

                    solution[0] = this->initial_state;

                    outcome = true;
                }

                // Else add successors at end of OPEN list
                else
                {
                    bsf_queue.push(nodeSuccessor);
                }
            }
        }
    }

    // 4 If OUTCOME Then Solution = path from I to N through the pointers
    if (outcome)
    {
        return solution;
    }
    // Else Solution = False
    else
    {
        // This will happen if there is no solution.
        std::cout << "Solution Not Found!\n";
        return solution;
    }
}

template <typename T>
std::vector<T> General_AI<T>::solve_DFS() const
{
    std::cout << "SOLVED WITH DFS" << std::endl;
    return std::vector<T>();
}

#endif // GENERAL_AI_HPP