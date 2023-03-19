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
	this->unitInPixels = (this->unitInPixelsX + this->unitInPixelsY) / 2;
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
	auto mgr = Engine::MetricManager::Get();
	cout << "Height units: " << mgr->heightUnits << endl;
	cout << "Width units: " << mgr->widthUnits << endl;
	cout << "Unit pixels: " << mgr->unitInPixelsX << " , " << mgr->unitInPixelsY << endl;
}

double Engine::MetricManager::unitToPixelsX(double units)
{
	auto mgr = Engine::MetricManager::Get();
	return units * mgr->unitInPixelsX;
}

double Engine::MetricManager::unitToPixelsY(double units)
{
	auto mgr = Engine::MetricManager::Get();
	return units * mgr->unitInPixelsY;
}

double Engine::MetricManager::unitToPixels(double units)
{
	auto mgr = Engine::MetricManager::Get();
	return units * mgr->unitInPixels;
}
