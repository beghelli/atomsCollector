#pragma once
#include <string>

using namespace std;

namespace Support
{
	class Message
	{
		private:
			string text;
			int fontSize;
			int fontId;
			int positionX;
			int positionY;
			int width;
			int height;

		public:
			Message(string text, int fontSize, int fontId, int positionX, int positionY, int width, int height);
			string getText();
			int getFontSize();
			int getFontId();
			int getPositionX();
			int getPositionY();
			int getWidth();
			int getHeight();
	};
}
