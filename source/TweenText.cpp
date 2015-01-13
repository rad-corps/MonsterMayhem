#include "TweenText.h"
#include "FrameworkHelpers.h"


//predicate function
bool IsTextInactive(const TweenText& text_)
{
	cout << !(text_.IsActive()) << endl; 
	return !(text_.IsActive());
}

TweenText::TweenText(int score_, Vector2 startPos_, float maxTime_)
{
	timer = 0.0f;
	textPos = startPos_;	
	textSize = 0.5f;
	score = score_;
	maxTime = maxTime_;
	//targetPos = startPos_;
	//targetPos.y += 40;

	//2 random numbers between 50 and 150
	int vx = rand() % 100 + 50;   
	int vy = rand() % 100 + 50;

	//we want to invert the x or y 50% of the time
	int invx=rand()%2;
	int invy=rand()%2;
	if ( invx ) vx -= vx * 2;
	if ( invy ) vy -= vy * 2;

	velocity = Vector2(vx, vy);
	active = true;
}


TweenText::~TweenText(void)
{
}

void TweenText::Update(float delta_)
{
 	if ( timer > maxTime )
	{
		active = false;
		return;
	}
	
	timer += delta_;
	textPos += velocity * delta_;
	textSize += score * delta_ * 0.015;
	velocity -= velocity * delta_;
}

void TweenText::Draw()
{
	if ( active ) 
		DrawString(to_string(score).c_str(), textPos.x, textPos.y, textSize);
}
