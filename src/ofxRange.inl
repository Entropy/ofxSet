//
//  ofxRange.inl
//  ofxRange
//
//  Created by Elias Zananiri on 2016-03-31.
//
//


//--------------------------------------------------------------
// Base Class
// ofxRange__

#include "ofxRange.h"
#include <algorithm>

//--------------------------------------------------------------
template <typename T>
ofxRange__<T>::ofxRange__()
{
    setDirty();
}

//--------------------------------------------------------------
template <typename T>
ofxRange__<T>::~ofxRange__()
{

}

//--------------------------------------------------------------
template <typename T>
void ofxRange__<T>::clear()
{
	setDirty();
}

//--------------------------------------------------------------
template <typename T>
void ofxRange__<T>::setDirty()
{
    m_bDirtyCenter = true;
    m_bDirtySpan = true;
}

//--------------------------------------------------------------
template <typename T>
void ofxRange__<T>::include(ofxRange__<T>& range)
{
	add(range.getMin());
	add(range.getMax());
}

//--------------------------------------------------------------
template <typename T>
T& ofxRange__<T>::getMin()
{
	return m_min;
}

//--------------------------------------------------------------
template <typename T>
T& ofxRange__<T>::getMax()
{
	return m_max;
}

//--------------------------------------------------------------
template <typename T>
T& ofxRange__<T>::getSpan()
{
	if (m_bDirtySpan)
	{
		m_span = getMax() - getMin();

		m_bDirtySpan = false;
	}

	return m_span;
}

//--------------------------------------------------------------
template <typename T>
T& ofxRange__<T>::getCenter()
{
    if (m_bDirtyCenter)
    {
        m_center = getMin() + getSpan() * 0.5f;

        m_bDirtyCenter = false;
    }

    return m_center;
}

//--------------------------------------------------------------
// Single Component Subclass
// ofxRange1_

//--------------------------------------------------------------
template <typename T>
ofxRange1_<T>::~ofxRange1_()
{
	clear();
}

//--------------------------------------------------------------
template <typename T>
void ofxRange1_<T>::add(const T& e)
{
	m_min = std::min(m_min, e);
	m_max = std::max(m_max, e);

	ofxRange__<T>::setDirty();
}

//--------------------------------------------------------------
template <typename T>
void ofxRange1_<T>::clear()
{
	ofxRange__<T>::clear();
		
	m_min = std::numeric_limits<T>::max();
	m_max = std::numeric_limits<T>::min();
}

//--------------------------------------------------------------
template <typename T>
bool ofxRange1_<T>::contains(const T& e) const
{
	return (m_min <= e && e <= m_max);
}

//--------------------------------------------------------------
// Multi Component Subclass
// ofxRangeX_

//--------------------------------------------------------------
template <typename T, typename U>
ofxRangeX_<T, U>::~ofxRangeX_()
{
	clear();
}

//--------------------------------------------------------------
template <typename T, typename U>
void ofxRangeX_<T, U>::add(const T& e)
{
	for (int i = 0; i < e.size(); ++i)
    {
		m_min[i] = std::min(m_min[i], e[i]);
		m_max[i] = std::max(m_max[i], e[i]);
    }

	ofxRange__<T>::setDirty();
}

//--------------------------------------------------------------
template <typename T, typename U>
void ofxRangeX_<T, U>::clear()
{
	ofxRange__<T>::clear();
	
	for (int i = 0; i < m_min.size(); ++i)
	{
		m_min[i] = std::numeric_limits<U>::max();
		m_max[i] = std::numeric_limits<U>::min();
	}
}

//--------------------------------------------------------------
template <typename T, typename U>
bool ofxRangeX_<T, U>::contains(const T& e) const
{
	for (int i = 0; i < e.size(); ++i)
	{
		if (m_min[i] > e[i] || e[i] > m_max[i])
		{
			return false;
		}
	}
	return true;
}
