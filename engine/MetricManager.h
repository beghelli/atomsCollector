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

			static MetricManager* Get();
			static int unitToPixelsX(double units);
			static int unitToPixelsY(double units);
			void debugPrint();
	};
}
