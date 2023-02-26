#pragma once

#include "defines.h"

namespace s2d
{
	
	class Pixelbuffer final
	{
	public:
		Pixelbuffer();
		Pixelbuffer(size_t width, size_t height);
		~Pixelbuffer();

		Pixelbuffer(const Pixelbuffer& other);
		
		Pixelbuffer& operator=(const Pixelbuffer& other);



		size_t width() const;
		size_t height() const;
		size_t size() const;

		const u32* data() const;
		u32* data();

		void clear(u32 color);
		void resize(size_t width, size_t height);

		u32 get_pixel(size_t x, size_t y) const;
		void set_pixel(size_t x, size_t y, u32 color);

	private:
		size_t m_width, m_height;
		u32* m_data;
	};

}