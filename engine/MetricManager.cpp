#include "iostream"
#include "MetricManager.h"
#include "constants.h"

Engine::MetricManager* Engine::MetricManager::metricManager{nullptr};

Engine::MetricManager::MetricManager()
{
	this->heightUnits = 10;
	this->widthUnits = 17.7;

	this->unitInPixelsX = SCREEN_WIDTH / widthUnits;
	this->unitInPixelsY = SCREEN_HEIGHT / heightUnits;
}

Engine::MetricManager* Engine::MetricManager::Get()
{
	if (metricManager == nullptr)
	{
		metricManager = new Engine::MetricManager();
	}

	return metricManager;
}

void Engine::MetricManager::debugPrint()
{
	cout << "Height units: " << heightUnits << endl;
	cout << "Width units: " << widthUnits << endl;
	cout << "Unit pixels: " << unitInPixelsX << " , " << unitInPixelsY << endl;
}

int Engine::MetricManager::unitToPixelsX(double units)
{
	auto mgr = Engine::MetricManager::Get();
	return units * mgr->unitInPixelsX;
}

int Engine::MetricManager::unitToPixelsY(double units)
{
	auto mgr = Engine::MetricManager::Get();
	return units * mgr->unitInPixelsY;
}
