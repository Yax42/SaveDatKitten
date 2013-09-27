enum EDirection
{
	BOT,
	RIGHT,
	TOP,
	LEFT
};

class Player
{
public:
    Player(int x, int y, int currentCubeID, int otherCubeID);
    ~Player();
    void	connection(unsigned int cube1ID, unsigned int side1, unsigned int cube2ID, unsigned int side2);
    void	x() const { return _x; }
    void	y() const { return _y; }
    void	cubeID() const { return _currentCubeID; }

private:
    int		_x;
    int		_y;
    int		_currentCubeID;
    int		_otherCubeID;

    void	move(const EDirection &dir);
    void	swapCubes();
    bool	clampPosition();
};