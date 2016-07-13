//
//  ofxRange.h
//  ofxRange
//
//  Created by Elias Zananiri on 2016-03-30.
//
//

#pragma once
#define GLM_FORCE_SIZE_FUNC
#include "glm/glm.hpp"

//--------------------------------------------------------------
template <typename T>
class ofxRange__
{
public:
    ofxRange__();
    virtual ~ofxRange__();

    virtual void add(const T& e) = 0;
    virtual void clear();
    virtual bool contains(const T& e) const = 0;

	void include(ofxRange__<T>& range);

	const T& getMin() const;
	const T& getMax() const;
	const T& getSpan() const;
	const T& getCenter() const;

protected:
    void setDirty();

    T m_min;
    T m_max;
	mutable T m_span;
	mutable T m_center;

	mutable bool m_bDirtySpan;
	mutable bool m_bDirtyCenter;
};

//--------------------------------------------------------------
template <typename T>
class ofxRange1_
: public ofxRange__<T>
{
public:
	~ofxRange1_();

    void add(const T& e) override;
    void clear() override;
	bool contains(const T& e) const override;

	using ofxRange__<T>::include;

protected:
    using ofxRange__<T>::m_min;
    using ofxRange__<T>::m_max;
};

//--------------------------------------------------------------
template <typename T, typename U>
class ofxRangeX_
: public ofxRange__<T>
{
public:
	~ofxRangeX_();

    void add(const T& e) override;
    void clear() override;
	bool contains(const T& e) const override;

	using ofxRange__<T>::include;

protected:
    using ofxRange__<T>::m_min;
    using ofxRange__<T>::m_max;
};

#include "ofxRange.inl"

using ofxRange1f = ofxRange1_<float>;
using ofxRange2f = ofxRangeX_<glm::vec2, float>;
using ofxRange3f = ofxRangeX_<glm::vec3, float>;
using ofxRange4f = ofxRangeX_<glm::vec4, float>;

using ofxRange1i = ofxRange1_<int>;
using ofxRange2i = ofxRangeX_<glm::tvec2<int>, int>;
using ofxRange3i = ofxRangeX_<glm::tvec3<int>, int>;
using ofxRange4i = ofxRangeX_<glm::tvec4<int>, int>;
