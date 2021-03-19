#include <algorithm>
#include <gtest/gtest.h>
#include "DSP/util/ExponentialSmoother.h"
#include "util/StrongTypes.h"
using namespace StrongTypes::Literals;

struct ExponentialSmootherParams
{
    StrongTypes::FrequencyValue<float> sampleRate;
    StrongTypes::TimeValue<float> riseTime;

    /* For prettier printing in the gtest log */
    friend std::ostream& operator<<(std::ostream& os, const ExponentialSmootherParams& values)
    {
        return os << "SampleRate: " << values.sampleRate.getHz() << "Hz, "
                  << "RiseTime: " << values.riseTime.getSeconds() << "s";
    }
};

static std::string generateTestCaseName(const ::testing::TestParamInfo<ExponentialSmootherParams>& info)
{
    std::stringstream ss;
    ss << "SR" << info.param.sampleRate.getHz() << "Hz_";
    ss << "Rise" << info.param.riseTime.getSeconds() << "s";
    auto s = ss.str();
    std::replace(s.begin(), s.end(), ',', 'p'); // replace all ',' to 'p'
    std::replace(s.begin(), s.end(), '.', 'p'); // replace all '.' to 'p'
    return s;
}

class DSP_ExponentialSmoother_Fixture : public ::testing::TestWithParam<ExponentialSmootherParams>
{
protected:
    DSP_ExponentialSmoother_Fixture() :
        timeConstant_(ExponentialSmoother::TimeConstant::SampleRate(GetParam().sampleRate),
                      ExponentialSmoother::TimeConstant::RiseTime(GetParam().riseTime))
    {
    }

    ExponentialSmoother smoother_;
    ExponentialSmoother::TimeConstant timeConstant_;
};

TEST_P(DSP_ExponentialSmoother_Fixture, a_riseTime)
{
    // Checks that the smoother reaches 88.8% of the target value
    // after the rise time has passed.

    smoother_.reset(0.0f);

    int numSamplesToProcess = int(std::round(GetParam().riseTime.getSeconds() * GetParam().sampleRate.getHz()));
    while (numSamplesToProcess--)
        smoother_.getNextValue(1.0f, timeConstant_);

    EXPECT_NEAR(smoother_.getCurrentValue(), 0.8888f, 0.001f);
}

TEST_P(DSP_ExponentialSmoother_Fixture, b_fallTime)
{
    // Checks that the smoother reaches 88.8% of the target value
    // after the fall time has passed.

    smoother_.reset(1.0f);

    int numSamplesToProcess = int(std::round(GetParam().riseTime.getSeconds() * GetParam().sampleRate.getHz()));
    while (numSamplesToProcess--)
        smoother_.getNextValue(0.0f, timeConstant_);

    EXPECT_NEAR(smoother_.getCurrentValue(), 0.1111f, 0.001f);
}

INSTANTIATE_TEST_SUITE_P(
    DSP_ExponentialSmoother,
    DSP_ExponentialSmoother_Fixture,
    ::testing::Values<ExponentialSmootherParams>(
        ExponentialSmootherParams { 44100.0_Hz, 1.0_sec },
        ExponentialSmootherParams { 44100.0_Hz, 0.5_sec },
        ExponentialSmootherParams { 88200.0_Hz, 1.0_sec },
        ExponentialSmootherParams { 88200.0_Hz, 0.5_sec }),
    generateTestCaseName);

TEST(DSP_ExponentialSmoother_Constexpr, precomputedTimeConstant)
{
    // If this compiles, we know that the time constant can be pre-computed as a constexpr

    static constexpr ExponentialSmoother::TimeConstant timeConstant(ExponentialSmoother::TimeConstant::SampleRate(44100.0_Hz),
                                                                    ExponentialSmoother::TimeConstant::RiseTime(0.5_sec));

    ExponentialSmoother smoother;
    smoother.reset();
    const auto result = smoother.getNextValue(1.0f, timeConstant);
    EXPECT_GT(result, 0.0f);
}
