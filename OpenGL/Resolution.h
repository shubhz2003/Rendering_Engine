#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	// members are public with default in a struct
	int m_width;
	int m_height;

	Resolution(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}
};
#endif // !RESOLUTION_H
