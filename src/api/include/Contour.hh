#ifndef CONTOUR_HH
#define CONTOUR_HH

#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <stb_truetype.h>

#include "LinearAlgebra.hh"

namespace SuperSDF
{
	class Contour
	{
	public:
		Contour();
		~Contour();

		size_t AddSurface(stbtt_vertex* vertex, size_t size, size_t start);
		void PrintContour() const;
		
		const std::vector<Point>& GetPoints() const;

		const bool PointBelongs(const Eigen::Vector2f& point, const DrawBox& drawBox) const;
		const bool IsClockwise() const;
		void Flip();
	private:		

		void SetClockwise();
		void SetCorners();
		size_t PushPoints(stbtt_vertex* vertex, size_t size, size_t start);
		bool CheckCorner(size_t point, float toleranceAngle);

		std::vector<Point> m_Contour;
		bool m_Clockwise = true;
	};

}

#endif // CONTOUR_HH