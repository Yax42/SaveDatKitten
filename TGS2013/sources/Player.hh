
enum EDirection
{
	LEFT,
	TOP,
	RIGHT,
	BOT,
	NONE
};

class Player
{
public:
    Player(int x, int y);
    ~Player();
    void	move(const EDirection &dir);

private:
    int		_x;
    int		_y;

    bool	clampPosition();
};