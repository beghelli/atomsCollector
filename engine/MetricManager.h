#pragma once

namespace Engine
{
	class MetricManager
	{
		private:
			static MetricManager* metricManager;
			double widthUnits;
			double heightUnits;

		public:
			MetricManager();
			double unitInPixelsX;
			double unitInPixelsY;
			double unitInPixels;

			static MetricManager* Get();
			static double unitToPixelsX(double units);
			static double unitToPixelsY(double units);
			static double unitToPixels(double units);
			static void debugPrint();
	};
}
