#include <iostream>
#include "../include/General_AI.hpp"
#include <vector>

bool g(int m)
{
    return m == 9;
}

std::vector<int> get(int m)
{
    std::vector<int> v;
    v.push_back(m+1);
    v.push_back(m-1);
    return v;
}
int main()
{
    int x = 5;
    int y = 9;

    General_AI<int> ai(x, g, get, BFS);
    //std::cout << ai << std::endl;
    std::vector<int> solution = ai.solve();
    print_solution(solution);
    
    return 0;
}