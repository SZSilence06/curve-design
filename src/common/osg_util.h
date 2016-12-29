#ifndef HJ_OSG_UTIL_H_
#define HJ_OSG_UTIL_H_

#include <osg/Drawable>
#include <boost/shared_ptr.hpp>
/*
class drawable {
public:
	void bounding_box(float min_max[2][3]) const;
	void render(void) const;
};
*/
template <typename T>
class osg_drawable : public ::osg::Drawable
{
public:
	osg_drawable(){}
	osg_drawable(T* imp){
		drawable_.reset(imp);
	}
    /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
    osg_drawable(const osg_drawable& a,const ::osg::CopyOp& copyop=::osg::CopyOp::SHALLOW_COPY):
		Drawable(a,copyop) {}

    META_Object(osg, osg_drawable)	// RTTI

    // the draw immediate mode method is where the OSG wraps up the drawing of
    // of OpenGL primitives.
	virtual void drawImplementation(osg::RenderInfo&) const { drawable_->render(); }
	boost::shared_ptr<T> drawable_;
protected:
	virtual ::osg::BoundingBox computeBoundingBox() const {
		_boundingBox.init();
		float min_max[2][3];
		drawable_->bounding_box(min_max);
		_boundingBox.set(
			min_max[0][0], min_max[0][1], min_max[0][2],
			min_max[1][0], min_max[1][1], min_max[1][2]);
		_boundingBoxComputed = true;
		return _boundingBox;
	}
};

template <typename T>
osg_drawable<T> *create_osg_drawable(T *imp) {
	return new osg_drawable<T>(imp);
}

#include <zjucad/matrix/matrix.h>
using namespace zjucad::matrix;
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Viewport>
#include <osg/Drawable>
//#include <Producer/Math>

template <int LEN, typename E, typename VEC>
static inline void convert2osgVec(const matrix_expression<E> &v, VEC &osg_v) {
	for(int i = 0; i < LEN; ++i) osg_v[i] = v()[i];
}

template <typename E>
static inline void convert(const matrix_expression<E> &v, osg::Vec3d &v3) {
	convert2osgVec<3>(v, v3);
}

template <typename E>
static inline void convert(const matrix_expression<E> &v, osg::Vec4d &v4) {
	convert2osgVec<4>(v, v4);
}

template <typename E>
static inline void convert(const matrix_expression<E> &v, osg::Vec3f &v3) {
	convert2osgVec<3>(v, v3);
}

template <typename E>
static inline void convert(const matrix_expression<E> &v, osg::Vec4f &v4) {
	convert2osgVec<4>(v, v4);
}

template <typename E>
static inline void convert(const osg::Vec3 &v3, matrix_expression<E> &v) {
	v()(0) = v3[0]; v()(1) = v3[1]; v()(2) = v3[2];
}

template <typename E>
static inline void convert(const osg::Vec4 &v4, matrix_expression<E> &v) {
	v()(0) = v4[0]; v()(1) = v4[1]; v()(2) = v4[2]; v()(3) = v4[3];
}

template <typename E, typename OSG_M>
const OSG_M &convert2osgMatrix(const matrix_expression<E> &src, OSG_M &dst) {
  std::copy(src().begin(), src().end(), dst.ptr());
	return dst;
}

template <typename E>
const osg::Matrixf &convert(const matrix_expression<E> &src, osg::Matrixf &dst) {
	return convert2osgMatrix(src, dst);
}

template <typename E>
const osg::Matrixd &convert(const matrix_expression<E> &src, osg::Matrixd &dst) {
	return convert2osgMatrix(src, dst);
}

template <typename E>
const matrix_expression<E> &convert(const osg::Matrixf &src, matrix_expression<E> &dst)
{
	const float *p = src.ptr();
	dst() = zeros<typename E::value_type>(4);
  std::copy(p, p+16, dst().begin());
	return dst;
}

template <typename OS>
OS &operator << (OS &os, const osg::Vec3 &v3) {
  std::copy(v3._v, v3._v+3, std::ostream_iterator<float>(os, " "));
	return os;
}

template <typename OS>
OS &operator << (OS &os, const osg::Vec4 &v4) {
  std::copy(v4._v, v4._v+4, std::ostream_iterator<float>(os, " "));
	return os;
}

template <typename OS, typename T>
OS &insert_osg_Matrix_to_stream(OS &os, T &m)
{
	os << '{';
	for(int i = 0; i < 4; ++i) {
		os << '\n';
		for(int j = 0; j < 4; ++j)
			os << " " << m(i, j);
	}
	os << "\n}\n";
	return os;
}

template <typename OS>
OS &operator << (OS &os, const osg::Matrixd &m)
{
	return insert_osg_Matrix_to_stream(os, m);
}

template <typename OS>
OS &operator << (OS &os, const osg::Matrixf &m)
{
	return insert_osg_Matrix_to_stream(os, m);
}

template <typename IS, typename T>
IS &extract_osg_Matrix_from_stream(IS &is, T &m)
{
	char c;
	is >> c;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j)
			is >> m(i, j);
	}
	is >> c;
	return is;
}

template <typename IS>
IS &operator >> (IS &is, osg::Matrixd &m)
{
	return extract_osg_Matrix_from_stream(is, m);
}

template <typename IS>
IS &operator >> (IS &is, osg::Matrixf &m)
{
	return extract_osg_Matrix_from_stream(is, m);
}

#endif
