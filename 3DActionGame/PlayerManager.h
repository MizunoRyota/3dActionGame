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
	int PlayerHandle;
	static constexpr int StatusNum = 4;
	PlayerBase* player[StatusNum];
};