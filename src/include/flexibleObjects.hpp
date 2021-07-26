#pragma once

#include "flexibleObjects.h"

namespace flexiobjects {
namespace properties {

using namespace logging;

template<typename TPropertyType>
iProperty<TPropertyType>::~iProperty() {}

template<typename TPropertyType>
tPropertyImpl<TPropertyType>::tPropertyImpl() : propertyPtr(new PropertyType()) {
    traceStart();
    traceEnd();
}

template<typename TPropertyType>
tPropertyImpl<TPropertyType>::~tPropertyImpl() {
    traceStart();
    delete propertyPtr;
    traceEnd();
}

template<typename TPropertyType>
TPropertyType* tPropertyImpl<TPropertyType>:: get() { return propertyPtr; }

template<typename TPropertyType>
void tPropertyImpl<TPropertyType>::set(TPropertyType* value) { propertyPtr = value; }

template<typename TPropertyType>
TPropertyType tPropertyImpl<TPropertyType>::getValue() { return *propertyPtr; }

template<typename TPropertyType>
void tPropertyImpl<TPropertyType>::setValue(TPropertyType value) { *propertyPtr = value; }

//template<typename ...TPropertyTypes>
//constexpr size_t iPropertyContainer<TPropertyTypes...>::NumberOfProperties = sizeof...(TPropertyTypes);

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
tSimilarPropertyContainerImpl()
{
        traceStart();
        traceEnd();
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
void tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
addProperty(Property* property)
{
    this->properties.push_back(property);
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
typename tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property*
tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
get(size_t index) {
    return properties[index];
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
void tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
set(size_t index, Property* property)
{
    properties[index] = property;
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
typename tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::PropertyType
tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
getValue(size_t index) {
    return properties[index]->getValue();
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
void tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
setValue(size_t index, PropertyType value)
{
    properties[index]->setValue(value);
}


template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
void NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
addProperty(std::string& propertyName) {
    traceStart();
    propertyNames.push_back(propertyName);
    auto empty = new TPropertyImpl();
    Base::addProperty(empty);
    traceEnd();
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
typename NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property*
NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
getProperty(std::string& propertyName) {
    traceStart();
    auto idx = getIndexOf(propertyName);
    if (idx >= 0 && idx < this->properties.size()) {
        return this->properties[idx];
    }
    // should we add new property or just throw exception?
    // for now throwing excpetion.
    throw new std::exception();
    traceEnd();
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
size_t NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::
getIndexOf(std::string& name) {
    for(size_t index = 0; index < propertyNames.size(); index++) {
        if(propertyNames[index] == name) {
            return index;
        }
    }
    return -1;
}

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl>
NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::NamedPropertyContainer()
{
    traceStart();
    traceEnd();
}


template<typename TCommonPropertyType, int TNumOfProperties, typename PropertyImpl>
NamedProperties<TCommonPropertyType, TNumOfProperties, PropertyImpl>::
NamedProperties()
{
    traceStart();
    traceEnd();
}

}
}
