#pragma once

#include <vector>
#include <cstdarg>
#include <map>
#include <iostream>
#include "logging.h"

#if BUILDING_LIBFLEXI && HAVE_VISIBILITY
#define LIBFLEXI_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_LIBFLEXI && defined _MSC_VER
#define LIBFLEXI_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LIBFLEXI_DLL_EXPORTED __declspec(dllimport)
#else
#define LIBFLEXI_DLL_EXPORTED
#endif


namespace flexiobjects {
namespace properties {

using namespace logging;

template<typename TPropertyType>
LIBFLEXI_DLL_EXPORTED struct iProperty {
public:
    virtual ~iProperty() {}
    typedef TPropertyType PropertyType;
    typedef TPropertyType* PropertyTypePtr;
    virtual PropertyType* get() = 0 ;
    virtual void set(PropertyType* value) = 0 ;
    virtual PropertyType getValue() = 0 ;
    virtual void setValue(PropertyType value) = 0 ;

};


template<typename TPropertyType>
LIBFLEXI_DLL_EXPORTED struct tPropertyImpl : public iProperty<TPropertyType> {
public:
    typedef TPropertyType PropertyType;
    typedef TPropertyType* PropertyTypePtr;

    tPropertyImpl();

    ~tPropertyImpl();

    virtual PropertyType* get();
    virtual void set(PropertyType* value);

    virtual PropertyType getValue();
    virtual void setValue(PropertyType value);

protected:
    typename iProperty<TPropertyType>::PropertyTypePtr propertyPtr;
};

namespace traits {
    template<typename T>
    LIBFLEXI_DLL_EXPORTED struct bind {};

#define DECLARE_BIND_TYPE(_type) \
    template<> \
    LIBFLEXI_DLL_EXPORTED struct bind<_type> { \
        typedef tPropertyImpl<_type> PropertyImpl; \
    }; \

DECLARE_BIND_TYPE(char)
DECLARE_BIND_TYPE(unsigned char)
DECLARE_BIND_TYPE(short)
DECLARE_BIND_TYPE(unsigned short)
DECLARE_BIND_TYPE(int)
DECLARE_BIND_TYPE(unsigned int)
DECLARE_BIND_TYPE(long)
DECLARE_BIND_TYPE(unsigned long)
DECLARE_BIND_TYPE(float)
DECLARE_BIND_TYPE(double)

DECLARE_BIND_TYPE(std::string)

}

template<typename ...TPropertyTypes>
LIBFLEXI_DLL_EXPORTED struct iPropertyContainer {
public:
    static constexpr size_t NumberOfProperties = sizeof...(TPropertyTypes);
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
LIBFLEXI_DLL_EXPORTED struct iSimilarPropertyContainer {
public:
    static constexpr size_t NumberOfProperties = TNumOfProperties;
    typedef TPropertyImpl PropertyImpl;
    typedef typename TPropertyImpl::PropertyType PropertyType;
    typedef iProperty<TCommonPropertyType> Property;

    virtual void addProperty(Property* property) = 0;
    virtual Property* get(size_t index) = 0;
    virtual void set(size_t index, Property* property) = 0;
    virtual PropertyType getValue(size_t index) = 0;
    virtual void setValue(size_t index, PropertyType value) = 0;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
LIBFLEXI_DLL_EXPORTED struct tSimilarPropertyContainerImpl : public iSimilarPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl> {
    typedef typename iSimilarPropertyContainer<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property Property;
    static constexpr size_t numProperties = TNumOfProperties;
    typedef typename TPropertyImpl::PropertyType PropertyType;

    tSimilarPropertyContainerImpl();

    virtual void addProperty(Property* property);
    virtual Property* get(size_t index);
    virtual void set(size_t index, Property* property);
    virtual PropertyType getValue(size_t index);
    virtual void setValue(size_t index, PropertyType value);

    protected:
        std::vector<Property*> properties;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename TPropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
LIBFLEXI_DLL_EXPORTED struct NamedPropertyContainer : public tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl> {
public:
    typedef tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl> Base;
    typedef typename tSimilarPropertyContainerImpl<TCommonPropertyType, TNumOfProperties, TPropertyImpl>::Property Property;
    typedef typename TPropertyImpl::PropertyType PropertyType;

    NamedPropertyContainer();

    void addProperty(std::string& propertyName);

    Property* getProperty(std::string& propertyName);

protected:
    size_t getIndexOf(std::string& name);
    std::vector<std::string> propertyNames;
};

template<typename TPropertyContainer>
struct ValidatedPropertyContainer : public TPropertyContainer {
protected:
    std::map<std::string, void*> validators;
};

template<typename TCommonPropertyType, int TNumOfProperties, typename PropertyImpl=typename traits::bind<TCommonPropertyType>::PropertyImpl>
LIBFLEXI_DLL_EXPORTED class NamedProperties: public NamedPropertyContainer<TCommonPropertyType, TNumOfProperties, PropertyImpl> {
public:
    NamedProperties();
};

}
}

#include <flexibleObjects.hpp>
