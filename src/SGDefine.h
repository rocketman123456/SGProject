#pragma once

#define SGMain main
#define Interface class
#define implements public

#include "Eigen/Eigen"
namespace SG
{
	using Vector4h = Eigen::Matrix<Eigen::half, 4, 1>;
	using Vector4f = Eigen::Matrix<float, 4, 1>;
	using Vector4d = Eigen::Matrix<double, 4, 1>;
	using Vector4fru = Eigen::Matrix<float, 4, 1, Eigen::RowMajor | Eigen::DontAlign>;
	using RowVector4f = Eigen::Matrix<float, 1, 4>;
	using Matrix4f = Eigen::Matrix<float, 4, 4>;
	using Matrix3x4f = Eigen::Matrix<float, 3, 4>;
	// for opengl
	using double4 = SG::Vector4d;
	using float4 = SG::Vector4f;
	using half4 = SG::Vector4h;
}
