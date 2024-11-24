#include "Rage.h"

class Sage : public Rage::Application
{
public:
	Sage()
	{
	}

	~Sage()
	{
	}

private:

};


Rage::Application* Rage::CreateApplication()
{
	return new Sage();
}