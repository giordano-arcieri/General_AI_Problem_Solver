# General_AI_Problem_Solver
This repo takes any problem: an initial state, solution state, and a set of operators to go from one state to another. It uses any search algorithm to find a path from the initial state to the solution state.

This project is able to solve any problem that can be represented as a path from the initial state to the final state.

Artificial Intelligence can be divided into two steps: Representation and Search.

For any problem you need to represent it. To represent a problem you need to define:
  An Initial State(IS) - In this case I will represent it as a C++ object.
  A Solution State(SS) - In this case I will also represent it as a C++ object.
  A set of operands - This can vary based on what problem you are trying to solve. I have a function called get_successors(T state1) which returns a vector of T objects representing all the possible states you can go to from state1. Or all successors of state1.

After you represent a problem you can search it using any searching algorithm. They all have their pros and cons so you need to pick the best algorithm based on your case. A list of searching algorithms are:
  breadth-first-search(BFS)
  depth-first-search(DFS)
  best-first-search(BestFS)
  
To search the problem you start at the initial state, then all the successors of the initial state, which you get through the get_successors function explained above, are connected to that state. This creates a graph where you can perform your searching algorithm on until you find the solution state. You want to keep track of the paths in order to know what steps to take from the IS to the SS.

Here is the pseudo code using BFS:

    Check if the initial state is the solution state and if it is solution is trivial return anything (e.g. throw an exception)
    
    Create an OPEN queue with the initial node = (IS)
  
    OUTCOME=False
   
    While OPEN list is not empty or OUTCOME is false
    
        Remove the first node from OPEN list, N
       
        If N has successors then Generate the successors of N

        For every successor
                
                Check if successor/state has already been visited if it has continue
                
                Visit successor/state
                
                Create pointers from the successors/state to N
              
                If a successor is a goal state then OUTCOME=True
               
                Else add successors at end of OPEN list
               
    If OUTCOME = True then return the path from IS to successor
   
    Else there is no solution return anything (e.g. throw an exception)



## Using the Code

This program includes a main function which tests the header file with various objects. However to use this General AI for your specific problem you can just steal the include folder and include it in your specific project.

To run the tests:

```
g++ src/*.cpp -o program && ./program
```
### Small Description of the class:

The General_AI class is an object that is used to solve any problem that can be represented as a state space search problem.
You can use this class to solve any problem, as long as you know what the initial state is, what the goal state is, and what the possible actions/operators are to go from one state to another.

### What the Class Needs to Work:
The representation of the initial state and final state will just be another class object, any object you choose to implement, as long as it has the following methods:

    Precondition: The calling object is a valid object of the class
    Postcondition: Return true if the calling object is the goal state, false otherwise
    bool is_goal() const;

    Precondition: The calling object is a valid object of the class
    Postcondition: Returns a vector of all the possible states that can be reached from the calling object. All possible next states.
    std::vector<T> get_successors() const;

If you do not want to implement those methods as member functions of the class, you can pass them as function pointers to the General_AI constructor. If none are passed in, or NULL is passed it assumes those methods are implemented as member functions of the class.

### Here is the ADT for the GeneralAI object:

Precondition: If the get_successors and is_goal function pointers are not passed in, the T class must have the methods implemented.
Postcondition: It creates a valid General_AI object that uses the passed in searching algorithm to solve the problem. Default is breadth first search.
General_AI(T initial_state, bool (*is_goal)(T) = NULL, std::vector<T> (*get_successors)(T) = NULL, searching_algorithm = BFS);

Precondition: The calling object is a valid General_AI object
Postcondition: It will return a vector of the states that lead from the initial state to the goal state.
std::vector<T> solve();

Precondition: The passed in argument is a vector of T objects where T has the << operator overloaded to be used with cout.
Postcondition: It will print the vector one item at a time to the cout stream. // This is a non member function so it should not have a calling object. ai.print_solution() is not valid.
void print_solution(std::vector<T> solution);


make sure you are in the cloned directory as the above command is a relative path.

## Moving Forward

Moving forward I want to implement more and more searching algorithms as the ones implemented so far have their downsides. So far the only implemented searching algorithm are:
  breadth-first-search(BFS)

Searching algorithms I want to implement:
  depth-first-search(DFS)
  best-first-search(BestFS) - this will require a heuristics

Other things needed to be implemented:
  - multiple constructors and more error handling. I want to use only std errors.

## Prerequisites

g++ is the only prerequisite. You can also use gcc. Or any compiler.


## Contributing

Please submit any PRs you want


## License

This project is licensed under GNU

## Additional Resources

For more information on how this AI technique works and guarantees and optimal solution visit in (BFS):
https://www.cs.us.es/~fsancho/Blog/posts/BFS_Solver_NetLogo.md.html


