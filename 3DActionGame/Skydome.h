#pragma once

class Skydome
{
public:
	Skydome();
	~Skydome();
	void Update();
	void Draw();
private:
	int SkydomeHandle;		//���f���n���h��
	VECTOR pos;				//�|�W�V����
	// �ÓI�萔.
	static constexpr float Scale = 0.10f;		//�傫��
};
