#include "PSGameOver.h"
#include "AIE.h"
#include "PSMainMenu.h"

PSGameOver::PSGameOver(void)
{
}


PSGameOver::~PSGameOver(void)
{
}


ProgramState* PSGameOver::Update(float delta_)
{
	if ( IsKeyDown(KEY_ESCAPE) )
	{
		return new PSMainMenu();
	}
	return nullptr;
}

void PSGameOver::Draw()
{
	DrawString("GAME OVER, PRESS ESC TO RESET", 100, 100);
}