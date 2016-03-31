//
//  ofxSet.h
//  ofxSet
//
//  Created by Elias Zananiri on 2016-03-30.
//
//

#pragma once

#include <glm/glm.hpp>

template <typename T, typename U, size_t D>
class ofxSet_
{
public:
    ofxSet_();
    ~ofxSet_();

    void add(T& e);
    void add(U c);

    void remove(T& e);
    void toggle(T& e);

    bool contains(T& e);
    void clear();

    T& getMin();
    T& getMax();
    T& getMean();
    T& getMedian();
    T& getCenter();
    T& getSpan();

    size_t size();

    const std::vector<T>& getElements();

protected:
    void setDirty();

    std::vector<T> m_elements;
    std::vector<std::multiset<U>> m_components;

    T m_min;
    T m_max;
    T m_mean;
    T m_median;
    T m_center;
    T m_span;

    bool m_bDirtyMin;
    bool m_bDirtyMax;
    bool m_bDirtyMean;
    bool m_bDirtyMedian;
    bool m_bDirtyCenter;
    bool m_bDirtySpan;
};

typedef ofxSet_<glm::tvec1<float>, float, 1> ofxSet1f;
typedef ofxSet_<glm::vec2, float, 2> ofxSet2f;
typedef ofxSet_<glm::vec3, float, 3> ofxSet3f;
typedef ofxSet_<glm::vec4, float, 4> ofxSet4f;

typedef ofxSet_<glm::tvec1<int>, int, 1> ofxSet1i;
typedef ofxSet_<glm::tvec2<int>, int, 2> ofxSet12;
typedef ofxSet_<glm::tvec3<int>, int, 3> ofxSet13;
typedef ofxSet_<glm::tvec4<int>, int, 4> ofxSet14;

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
ofxSet_<T, U, D>::ofxSet_()
{
    m_components.resize(D);
    setDirty();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
ofxSet_<T, U, D>::~ofxSet_()
{
    clear();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::setDirty()
{
    m_bDirtyMin = true;
    m_bDirtyMax = true;
    m_bDirtyMean = true;
    m_bDirtyMedian = true;
    m_bDirtyCenter = true;
    m_bDirtySpan = true;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::add(T& e)
{
    m_elements.push_back(e);

    for (int i = 0; i < D; ++i)
    {
        m_components[i].insert(e[i]);
    }

    setDirty();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::add(U c)
{
    T e(c);
    add(e);
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::remove(T& e)
{
    auto it = m_elements.find(e);
    if (it == m_elements.end()) return;

    m_elements.erase(it);

    for (int i = 0; i < D; ++i)
    {
        auto it = m_components[i].find(e[i]);
        m_components[i].erase(it);
    }

    setDirty();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::toggle(T& e)
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
template <typename T, typename U, size_t D>
bool ofxSet_<T, U, D>::contains(T& e)
{
    return (m_elements.find(e) != m_elements.end());
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
void ofxSet_<T, U, D>::clear()
{
    m_elements.clear();

    for (auto& it : m_components)
    {
        it.clear();
    }
    m_components.clear();

    setDirty();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getMin()
{
    if (m_bDirtyMin)
    {
        if (size())
        {
            for (int i = 0; i < D; ++i)
            {
                m_min[i] = *m_components[i].begin();
            }
        }
        else
        {
            m_min = T(0);
        }

        m_bDirtyMin = false;
    }

    return m_min;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getMax()
{
    if (m_bDirtyMax)
    {
        if (size())
        {
            for (int i = 0; i < D; ++i)
            {
                m_max[i] = *m_components[i].rbegin();
            }
        }
        else
        {
            m_max = T(0);
        }

        m_bDirtyMax = false;
    }

    return m_max;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getMean()
{
    if (m_bDirtyMean)
    {
        m_mean = T(0);

        if (size())
        {
            for (int i = 0; i < D; ++i)
            {
                for (auto& it : m_components[i])
                {
                    m_mean[i] += it;
                }
                m_mean[i] /= m_components[i].size();
            }
        }

        m_bDirtyMean = false;
    }

    return m_mean;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getMedian()
{
    if (m_bDirtyMedian)
    {
        if (size())
        {
            for (int i = 0; i < D; ++i)
            {
                size_t offset = m_components[i].size() / 2;
                auto it = m_components[i].begin();
                std::advance(it, offset);
                m_median[i] = *it;
            }
        }
        else
        {
            m_median = T(0);
        }

        m_bDirtyMedian = false;
    }

    return m_median;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getCenter()
{
    if (m_bDirtyCenter)
    {
        m_center = getMin() + getSpan() * 0.5f;

        m_bDirtyCenter = false;
    }

    return m_center;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
T& ofxSet_<T, U, D>::getSpan()
{
    if (m_bDirtySpan)
    {
        m_span = getMax() - getMin();

        m_bDirtySpan = false;
    }

    return m_span;
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
size_t ofxSet_<T, U, D>::size()
{
    return m_elements.size();
}

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
const std::vector<T>& ofxSet_<T, U, D>::getElements()
{
    return m_elements;
}
