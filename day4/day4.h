template<typename T>
bool vectorContains(std::vector<T>& vec, T item)
{
    for (T& elem : vec)
    {
        if(elem == item)
        {
            return true;
        }
    }

    return false;
}

struct coord 
{
    int x; int y;
    bool operator==(const coord& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    UP_LEFT = 4,
    UP_RIGHT = 5,
    DOWN_LEFT = 6,
    DOWN_RIGHT = 7
};