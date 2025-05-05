#pragma once

class PlayerBase 
{
public:

	PlayerBase();
	virtual ~PlayerBase();

	virtual void Update() ;					// �X�V.
	virtual void Draw();					// �`��.

	// ���f���n���h���̎擾.
	int GetModelHandle() { return PlayerHandle; }

	// �|�W�V������getter/setter.
	const VECTOR& Getposition() const { return position; }
	void Setposition(const VECTOR set) { position = set; }

protected:
	int PlayerHandle;
	VECTOR position;
};
