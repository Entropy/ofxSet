//
//  ofxSet.inl
//  ofxSet
//
//  Created by Elias Zananiri on 2016-03-31.
//
//

#include "ofxSet.h"

//--------------------------------------------------------------
// Base Class
// ofxSet__

//--------------------------------------------------------------
template <typename T>
ofxSet__<T>::ofxSet__()
{
    setDirty();
}

//--------------------------------------------------------------
template <typename T>
ofxSet__<T>::~ofxSet__()
{
    clear();
}

//--------------------------------------------------------------
template <typename T>
void ofxSet__<T>::add(const T& e)
{
    m_elements.push_back(e);

    setDirty();
}

//--------------------------------------------------------------
template <typename T>
bool ofxSet__<T>::remove(const T& e)
{
    auto it = std::find(m_elements.begin(), m_elements.end(), e);
    if (it == m_elements.end())
    {
        return false;
    }

    m_elements.erase(it);

    setDirty();

    return true;
}

//--------------------------------------------------------------
template <typename T>
void ofxSet__<T>::clear()
{
    m_elements.clear();

    setDirty();
}

//--------------------------------------------------------------
template <typename T>
void ofxSet__<T>::toggle(T& e)
{
    if (contains(e))
    {
        remove(e);
    }
    else
    {
        add(e);
    }
}

//--------------------------------------------------------------
template <typename T>
bool ofxSet__<T>::contains(T& e) const
{
    return (std::find(m_elements.begin(), m_elements.end(), e) != m_elements.end());
}

//--------------------------------------------------------------
template <typename T>
size_t ofxSet__<T>::size() const
{
    return m_elements.size();
}

//--------------------------------------------------------------
template <typename T>
const std::vector<T>& ofxSet__<T>::getElements() const
{
    return m_elements;
}

//--------------------------------------------------------------
template <typename T>
void ofxSet__<T>::setDirty()
{
    m_bDirtyMin = true;
    m_bDirtyMax = true;
    m_bDirtyMean = true;
    m_bDirtyMedian = true;
    m_bDirtyCenter = true;
    m_bDirtySpan = true;
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet__<T>::getCenter()
{
    if (m_bDirtyCenter)
    {
        m_center = getMin() + getSpan() * 0.5f;

        m_bDirtyCenter = false;
    }

    return m_center;
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet__<T>::getSpan()
{
    if (m_bDirtySpan)
    {
        m_span = getMax() - getMin();

        m_bDirtySpan = false;
    }

    return m_span;
}

//--------------------------------------------------------------
// Single Component Subclass
// ofxSet1_

//--------------------------------------------------------------
template <typename T>
void ofxSet1_<T>::add(const T& e)
{
    ofxSet__<T>::add(e);

    m_ordered.insert(e);
}

//--------------------------------------------------------------
template <typename T>
bool ofxSet1_<T>::remove(const T& e)
{
    if (ofxSet__<T>::remove(e))
    {
        auto it = m_ordered.find(e);
        m_ordered.erase(it);

        return true;
    }

    return false;
}

//--------------------------------------------------------------
template <typename T>
void ofxSet1_<T>::clear()
{
    ofxSet__<T>::clear();

    m_ordered.clear();
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet1_<T>::getMin()
{
    if (m_bDirtyMin)
    {
        if (size())
        {
            m_min = *m_ordered.begin();
        }
        else
        {
            m_min = 0;
        }

        m_bDirtyMin = false;
    }

    return m_min;
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet1_<T>::getMax()
{
    if (m_bDirtyMax)
    {
        if (size())
        {
            m_max = *m_ordered.rbegin();
        }
        else
        {
            m_max = 0;
        }

        m_bDirtyMax = false;
    }

    return m_max;
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet1_<T>::getMean()
{
    if (m_bDirtyMean)
    {
        m_mean = 0;

        if (size())
        {
            for (T e : m_ordered)
            {
                m_mean += e;
            }
            m_mean /= m_ordered.size();
        }

        m_bDirtyMean = false;
    }

    return m_mean;
}

//--------------------------------------------------------------
template <typename T>
T& ofxSet1_<T>::getMedian()
{
    if (m_bDirtyMedian)
    {
        if (size())
        {
            size_t offset = m_ordered.size() / 2;
            auto it = m_ordered.begin();
            std::advance(it, offset);
            m_median = *it;
        }
        else
        {
            m_median = 0;
        }

        m_bDirtyMedian = false;
    }

    return m_median;
}

//--------------------------------------------------------------
// Multi Component Subclass
// ofxSetX_

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSetX_<T, U, D>::add(const T& e)
{
    ofxSet__<T>::add(e);

    for (int i = 0; i < D; ++i)
    {
        m_components[i].add(e[i]);
    }
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
bool ofxSetX_<T, U, D>::remove(const T& e)
{
    if (ofxSet__<T>::remove(e))
    {
        for (int i = 0; i < D; ++i)
        {
            m_components[i].remove(e[i]);
        }

        return true;
    }

    return false;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSetX_<T, U, D>::clear()
{
    ofxSet__<T>::clear();

    for (int i = 0; i < D; ++i)
    {
        m_components[i].clear();
    }
}


//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSetX_<T, U, D>::getMin()
{
    if (m_bDirtyMin)
    {
        for (int i = 0; i < D; ++i)
        {
            m_min[i] = m_components[i].getMin();
        }

        m_bDirtyMin = false;
    }

    return m_min;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSetX_<T, U, D>::getMax()
{
    if (m_bDirtyMax)
    {
        for (int i = 0; i < D; ++i)
        {
            m_max[i] = m_components[i].getMax();
        }

        m_bDirtyMax = false;
    }

    return m_max;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSetX_<T, U, D>::getMean()
{
    if (m_bDirtyMean)
    {
        for (int i = 0; i < D; ++i)
        {
            m_mean[i] = m_components[i].getMean();
        }

        m_bDirtyMean = false;
    }

    return m_mean;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSetX_<T, U, D>::getMedian()
{
    if (m_bDirtyMedian)
    {
        for (int i = 0; i < D; ++i)
        {
            m_median[i] = m_components[i].getMedian();
        }

        m_bDirtyMedian = false;
    }

    return m_median;
}
