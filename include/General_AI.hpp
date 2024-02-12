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

enum searching_algorithm
{
    BFS,
    DFS
};

template <typename T>
class General_AI
{
public:
    // Precondition: If the get_successors and is_goal function pointers are not passed in, the T class must have the methods implemented.
    // Postcondition: It creates a valid General_AI object that uses the passed in searching alghorithm to solve the problem. Default is breadth first search.
    General_AI(T initial_state, bool (*is_goal)(T) = NULL, std::vector<T> (*get_successors)(T) = NULL, searching_algorithm algorithm = BFS);
    // Precondition: The calling object is a valid General_AI object
    // Postcondition: It will return a vector of the states that lead from the initial state to the goal state.
    std::vector<T> solve();

private:
    T initial_state;
    bool (*is_goal)(T);
    std::vector<T> (*get_successors)(T);
    searching_algorithm algorithm;
    std::vector<T> solve_BFS();
    std::vector<T> solve_DFS();
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
std::vector<T> General_AI<T>::solve()
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
        break;
    }
}

template <typename T>
std::vector<T> General_AI<T>::solve_BFS()
{
    return std::vector<T>();
}

template <typename T>
std::vector<T> General_AI<T>::solve_DFS()
{
    return std::vector<T>();
}

#endif // GENERAL_AI_HPP