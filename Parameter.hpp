#ifndef PARAMETER_H
#define PARAMETER_H 1

// Other module includes

// Library includes
#include <type_traits>


enum class IgnoreParameter { YES };


template<typename BaseType>
class Parameter {
public:
    /**
     * Constructor for non-ignored parameters.
     * @param value [in] Value of the parameter
     */
    Parameter(const BaseType &value) : m_value(&value), m_isIgnored(false) {}

    /**
     * Constructor for ignored parameters.
     *
     * The actual value of the passed parameter is ignored.
     */
    Parameter(IgnoreParameter) : m_value(nullptr),  m_isIgnored(true) {}

    /**
     * Returns the parameter value.
     * @return Parameter value
     */
    const BaseType& getValue()
    {
        return *m_value;
    }

    /**
     * Returns the parameter value.
     * @return Parameter value
     */
    const BaseType& getPointerValue()
    {
        return m_value;
    }

    /**
     * Indicates if the parameter is ignored.
     * @return @c true if the parameter is ignored, @c false otherwise
     */
    bool isIgnored()
    {
        return m_isIgnored;
    }


private:
    typename std::remove_reference<const BaseType>::type *m_value;
    bool m_isIgnored;
};

#endif //PARAMETER_H
