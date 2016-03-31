//
//  ofxSet.h
//  ofxSet
//
//  Created by Elias Zananiri on 2016-03-30.
//
//

#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
template <typename T>
class ofxSet__
{
public:
    ofxSet__();
    virtual ~ofxSet__();

    virtual void add(const T& e);
    virtual bool remove(const T& e);
    virtual void clear();

    void toggle(T& e);

    bool contains(T& e) const;

    size_t size() const;
    const std::vector<T>& getElements() const;

    virtual T& getMin() = 0;
    virtual T& getMax() = 0;
    virtual T& getMean() = 0;
    virtual T& getMedian() = 0;
    T& getCenter();
    T& getSpan();

protected:
    void setDirty();

    std::vector<T> m_elements;

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

//--------------------------------------------------------------
template <typename T>
class ofxSet1_
: public ofxSet__<T>
{
public:
    void add(const T& e) override;
    bool remove(const T& e) override;

    void clear() override;

    using ofxSet__<T>::size;

    T& getMin() override;
    T& getMax() override;
    T& getMean() override;
    T& getMedian() override;

protected:
    std::multiset<T> m_ordered;

    using ofxSet__<T>::m_min;
    using ofxSet__<T>::m_max;
    using ofxSet__<T>::m_mean;
    using ofxSet__<T>::m_median;

    using ofxSet__<T>::m_bDirtyMin;
    using ofxSet__<T>::m_bDirtyMax;
    using ofxSet__<T>::m_bDirtyMean;
    using ofxSet__<T>::m_bDirtyMedian;
};

//--------------------------------------------------------------
template <typename T, typename U, size_t D>
class ofxSetX_
: public ofxSet__<T>
{
public:
    void add(const T& e) override;
    bool remove(const T& e) override;

    void clear() override;

    using ofxSet__<T>::size;

    T& getMin() override;
    T& getMax() override;
    T& getMean() override;
    T& getMedian() override;

protected:
    ofxSet1_<U> m_components[D];

    using ofxSet__<T>::m_min;
    using ofxSet__<T>::m_max;
    using ofxSet__<T>::m_mean;
    using ofxSet__<T>::m_median;

    using ofxSet__<T>::m_bDirtyMin;
    using ofxSet__<T>::m_bDirtyMax;
    using ofxSet__<T>::m_bDirtyMean;
    using ofxSet__<T>::m_bDirtyMedian;
};

#include "ofxSet.inl"

using ofxSet1f = ofxSet1_<float>;
using ofxSet2f = ofxSetX_<ofDefaultVec2, float, 2>;
using ofxSet3f = ofxSetX_<ofDefaultVec3, float, 3>;
using ofxSet4f = ofxSetX_<ofDefaultVec4, float, 4>;

using ofxSet1i = ofxSet1_<int>;
using ofxSet2i = ofxSetX_<glm::tvec2<int>, int, 2>;
using ofxSet3i = ofxSetX_<glm::tvec3<int>, int, 3>;
using ofxSet4i = ofxSetX_<glm::tvec4<int>, int, 4>;
