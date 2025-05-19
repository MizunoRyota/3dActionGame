#pragma once
class PlayerBase;

class PlayerManager final
{
public:
	PlayerManager();
	~PlayerManager();

	void Initialize();
	void Update();
	void Draw();

private:
	static constexpr int StatusNum = 2;
	PlayerBase* player[StatusNum];
};