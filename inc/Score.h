#pragma once

class Score
{
private:
	int score;
	int killTime;
	float multiple;
	int spree;

public:
	Score(void);
	~Score(void);

public:
	void reset() { score = 0; killTime = 0; multiple = 0; spree = 0; }
	int getScore() { return score; }

	void addToScore(int x) { if(x>0) score += x; killTime = 0; spree++; }
	int calculate(float weapon, float h, int base = 1000);

	void calculateMultiple();
};

