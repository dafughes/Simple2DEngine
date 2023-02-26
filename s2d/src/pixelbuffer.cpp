#include "pixelbuffer.h"

#include <cstdlib>
#include <cstring>

namespace s2d
{
	Pixelbuffer::Pixelbuffer() : Pixelbuffer(0,0) {}

	Pixelbuffer::Pixelbuffer(size_t width, size_t height) :
		m_width(width),
		m_height(height),
		m_data(nullptr)
	{
		size_t size = m_width * m_height;

		if (size > 0)
		{
			m_data = (u32*)malloc(size * sizeof(u32));
		}
	}

	Pixelbuffer::~Pixelbuffer()
	{
		if (m_data)
		{
			free(m_data);
		}
	}

	size_t Pixelbuffer::width() const
	{
		return m_width;
	}

	size_t Pixelbuffer::height() const
	{
		return m_height;
	}

	const u32* Pixelbuffer::data() const
	{
		return m_data;
	}

	u32* Pixelbuffer::data()
	{
		return m_data;
	}

	void Pixelbuffer::clear(u32 color)
	{
		memset(m_data, color, m_width * m_height * sizeof(*m_data));
	}

	void Pixelbuffer::resize(size_t width, size_t height)
	{
		if (m_data)
		{
			free(m_data);
		}
		m_width = width;
		m_height = height;

		auto size = m_width * m_height;
		if (size > 0)
		{
			m_data = (u32*)malloc(size * sizeof(u32));
		}
	}

	u32 Pixelbuffer::get_pixel(size_t x, size_t y) const
	{
		if (x < m_width && y < m_height)
		{
			return m_data[x + y * m_width];
		}
		return 0;
	}

	void Pixelbuffer::set_pixel(size_t x, size_t y, u32 color)
	{
		if (x < m_width && y < m_height)
		{
			m_data[x + y * m_width] = color;
		}
	}
}