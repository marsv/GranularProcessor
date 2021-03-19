#pragma once

#include <type_traits>
#include <cmath>

namespace StrongTypes
{
    // ============================================================================================

    // ============================================================================================

    template <typename T, typename PhantomParameter>
    class NamedArgument
    {
    public:
        constexpr explicit NamedArgument(T const& value) :
            value_(value) {}

        template <typename T_ = T>
        constexpr explicit NamedArgument(T&& value,
                                         typename std::enable_if<!std::is_reference<T_> {},
                                                                 std::nullptr_t>::type = nullptr) :
            value_(std::move(value))
        {
        }

        constexpr T& get() { return value_; }
        constexpr T const& get() const { return value_; }

    private:
        T value_;
    };

    // ============================================================================================

    // ============================================================================================

    template <typename FloatType>
    class TimeValue
    {
    public:
        constexpr TimeValue(const TimeValue& other) :
            valueInS_(other.valueInS_)
        {
        }
        template <typename OtherFloatType>
        constexpr TimeValue(const TimeValue<OtherFloatType>& other) :
            valueInS_(FloatType(other.getSeconds()))
        {
        }

        /**
         * Returns a TimeValue from a raw floating point value in seconds.
         * For improved readability, please use the literals defined in the Literals namespace.
         */
        static constexpr TimeValue fromSeconds(FloatType seconds)
        {
            return TimeValue(seconds);
        }

        constexpr TimeValue operator+(const TimeValue& b) const { return TimeValue(valueInS_ + b.valueInS_); }
        constexpr TimeValue operator-(const TimeValue& b) const { return TimeValue(valueInS_ - b.valueInS_); }
        constexpr TimeValue operator*(const FloatType& b) const { return TimeValue(valueInS_ * b); }
        constexpr TimeValue operator/(const FloatType& b) const { return TimeValue(valueInS_ / b); }

        inline constexpr bool operator<(const TimeValue& rhs) { return valueInS_ < rhs.valueInS_; }
        inline constexpr bool operator>(const TimeValue& rhs) { return rhs < *this; }
        inline constexpr bool operator<=(const TimeValue& rhs) { return !(*this > rhs); }
        inline constexpr bool operator>=(const TimeValue& rhs) { return !(*this < rhs); }
        inline constexpr bool operator==(const TimeValue& rhs) { return valueInS_ == rhs.valueInS_; }
        inline constexpr bool operator!=(const TimeValue& rhs) { return !(*this == rhs); }

        constexpr FloatType getSeconds() const { return valueInS_; }
        constexpr FloatType getMilliSeconds() const { return valueInS_ * FloatType(1000); }
        constexpr FloatType getMicroSeconds() const { return valueInS_ * FloatType(1000000); }

    private:
        constexpr TimeValue(FloatType seconds) :
            valueInS_(seconds)
        {
        }
        FloatType valueInS_;
    };

    // ============================================================================================

    // ============================================================================================

    template <typename FloatType>
    class FrequencyValue
    {
    public:
        constexpr FrequencyValue(const FrequencyValue& other) :
            valueInHz_(other.valueInHz_)
        {
        }
        template <typename OtherFloatType>
        constexpr FrequencyValue(const FrequencyValue<OtherFloatType>& other) :
            valueInHz_(FloatType(other.getHz()))
        {
        }

        /**
         * Returns a FrequencyValue from a raw floating point value in Hz.
         * For improved readability, please use the literals defined in the Literals namespace.
         */
        static constexpr FrequencyValue fromHertz(FloatType hz)
        {
            return FrequencyValue(hz);
        }

        constexpr FrequencyValue operator+(const FrequencyValue& b) const { return FrequencyValue(valueInHz_ + b.valueInHz_); }
        constexpr FrequencyValue operator-(const FrequencyValue& b) const { return FrequencyValue(valueInHz_ - b.valueInHz_); }
        constexpr FrequencyValue operator*(const FloatType& b) const { return FrequencyValue(valueInHz_ * b); }
        constexpr FrequencyValue operator/(const FloatType& b) const { return FrequencyValue(valueInHz_ / b); }

        inline constexpr bool operator<(const FrequencyValue& rhs) { return valueInHz_ < rhs.valueInHz_; }
        inline constexpr bool operator>(const FrequencyValue& rhs) { return rhs < *this; }
        inline constexpr bool operator<=(const FrequencyValue& rhs) { return !(*this > rhs); }
        inline constexpr bool operator>=(const FrequencyValue& rhs) { return !(*this < rhs); }
        inline constexpr bool operator==(const FrequencyValue& rhs) { return valueInHz_ == rhs.valueInHz_; }
        inline constexpr bool operator!=(const FrequencyValue& rhs) { return !(*this == rhs); }

        constexpr FloatType getHz() const { return valueInHz_; }
        constexpr FloatType getMilliHz() const { return valueInHz_ * FloatType(1000); }
        constexpr FloatType getKiloHz() const { return valueInHz_ / FloatType(1000); }

    private:
        constexpr FrequencyValue(FloatType hz) :
            valueInHz_(hz)
        {
        }
        FloatType valueInHz_;
    };

    // ============================================================================================

    // ============================================================================================

    template <typename FloatType>
    class DecibelValue
    {
    public:
        constexpr DecibelValue(const DecibelValue& other) :
            valueIndB_(other.valueIndB_)
        {
        }
        template <typename OtherFloatType>
        constexpr DecibelValue(const DecibelValue<OtherFloatType>& other) :
            valueIndB_(FloatType(other))
        {
        }

        /**
         * Returns a DecibelValue from a raw floating point value in dB.
         * For improved readability, please use the literals defined in the Literals namespace.
         */
        static constexpr DecibelValue fromDecibels(FloatType dB)
        {
            return DecibelValue(dB);
        }

        constexpr DecibelValue operator+(const DecibelValue& b) const { return DecibelValue(valueIndB_ + b.valueIndB_); }
        constexpr DecibelValue operator-(const DecibelValue& b) const { return DecibelValue(valueIndB_ - b.valueIndB_); }
        constexpr DecibelValue operator*(const FloatType& b) const { return DecibelValue(valueIndB_ * b); }
        constexpr DecibelValue operator/(const FloatType& b) const { return DecibelValue(valueIndB_ / b); }

        inline constexpr bool operator<(const DecibelValue& rhs) { return valueIndB_ < rhs.valueIndB_; }
        inline constexpr bool operator>(const DecibelValue& rhs) { return rhs < *this; }
        inline constexpr bool operator<=(const DecibelValue& rhs) { return !(*this > rhs); }
        inline constexpr bool operator>=(const DecibelValue& rhs) { return !(*this < rhs); }
        inline constexpr bool operator==(const DecibelValue& rhs) { return valueIndB_ == rhs.valueIndB_; }
        inline constexpr bool operator!=(const DecibelValue& rhs) { return !(*this == rhs); }

        constexpr operator FloatType() const { return valueIndB_; }

        FloatType getAsGain() const
        {
            static constexpr auto tenPow1Div20 = 1.12201845430196343559;
            return std::pow(tenPow1Div20, valueIndB_);
        }

    private:
        constexpr DecibelValue(FloatType dB) :
            valueIndB_(dB)
        {
        }
        FloatType valueIndB_;
    };

    // ============================================================================================

    // ============================================================================================

    namespace Literals
    {
        constexpr TimeValue<long double> operator"" _sec(long double seconds) { return TimeValue<long double>::fromSeconds(seconds); }
        constexpr TimeValue<long double> operator"" _msec(long double milliSeconds) { return TimeValue<long double>::fromSeconds(milliSeconds / 1000.0); }
        constexpr TimeValue<long double> operator"" _usec(long double microSeconds) { return TimeValue<long double>::fromSeconds(microSeconds / 1000000.0); }

        constexpr FrequencyValue<long double> operator"" _Hz(long double hertz) { return FrequencyValue<long double>::fromHertz(hertz); }
        constexpr FrequencyValue<long double> operator"" _kHz(long double kiloHz) { return FrequencyValue<long double>::fromHertz(kiloHz * 1000.0); }
        constexpr FrequencyValue<long double> operator"" _mHz(long double milliHz) { return FrequencyValue<long double>::fromHertz(milliHz / 1000.0); }

        constexpr DecibelValue<long double> operator"" _dB(long double decibels) { return DecibelValue<long double>::fromDecibels(decibels); }
    } // namespace Literals

} // namespace StrongTypes
