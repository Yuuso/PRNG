
#pragma once

#include <random>
#include <stdint.h>
#include <type_traits>
#include <string>
#include <assert.h>


namespace Distribution
{
	//Uniform Distributions
	template<typename type>
	using UniformInt = std::uniform_int_distribution<type>;

	template<typename type>
	using UniformReal = std::uniform_real_distribution<type>;


	//Bernoulli Distributions
	using Bernoulli = std::bernoulli_distribution;

	template<typename type>
	using Geometric = std::geometric_distribution<type>;

	template<typename type>
	using Binomial = std::binomial_distribution<type>;

	template<typename type>
	using Pascal = std::negative_binomial_distribution<type>;


	//Poisson Distirbutions
	template<typename type>
	using Poisson = std::poisson_distribution<type>;

	template<typename type>
	using Exponential = std::exponential_distribution<type>;

	template<typename type>
	using Gamma = std::gamma_distribution<type>;

	template<typename type>
	using Weibull = std::weibull_distribution<type>;

	template<typename type>
	using ExtremeValue = std::extreme_value_distribution<type>;


	//Normal Distributions
	template<typename type>
	using Normal = std::normal_distribution<type>;

	template<typename type>
	using LogNormal = std::lognormal_distribution<type>;

	template<typename type>
	using ChiSquared = std::chi_squared_distribution<type>;

	template<typename type>
	using Cauchy = std::cauchy_distribution<type>;

	template<typename type>
	using FisherF = std::fisher_f_distribution<type>;

	template<typename type>
	using StudentT = std::student_t_distribution<type>;


	//Sampling Distributions
	template<typename type>
	using Discrete = std::discrete_distribution<type>;

	template<typename type>
	using PiecewiseConstant = std::piecewise_constant_distribution<type>;

	template<typename type>
	using PiecewiseLinear = std::piecewise_linear_distribution<type>;
}

template <typename SeedType>
class PRNG
{
	static_assert(std::is_unsigned<SeedType>::value && (sizeof(SeedType) == 4 || sizeof(SeedType) == 8), "SeedType needs to be either 32bit or 64bit unsigned integer value!");
	typedef typename std::conditional<sizeof(SeedType) == 4, std::mt19937, std::mt19937_64>::type MTEngine;

public:
	PRNG(const SeedType _seed = std::mt19937::default_seed)
	{
		randomSeed = _seed;
		engine.seed(randomSeed);
	}

	void seed(const SeedType _seed)
	{
		randomSeed = _seed;
		engine.seed(randomSeed);
	}
	SeedType seed()
	{
		return randomSeed;
	}
	void reset()
	{
		engine.seed(randomSeed);
	}
	void discard(const unsigned _amount = 1)
	{
		engine.discard(_amount);
	}

	template <typename ReturnType, typename DistributionType = std::conditional<std::is_integral<ReturnType>::value, Distribution::UniformInt<ReturnType>, Distribution::UniformReal<ReturnType>>::type>
	ReturnType random()
	{
		DistributionType dist;
		return dist(engine);
	}



	/*{
		static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
		DistributionType dist;
		return dist()
	}*/

	//template <typename ReturnType, typename DistributionType>
	//ReturnType random(const ReturnType _min, const ReturnType _max, const RandomDistribution _distribution = Uniform)
	//{
	//	static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
	//	switch (_distribution)
	//	{
	//	case Uniform:
	//	{
	//		typedef std::conditional<std::is_integral<ReturnType>::value, std::uniform_int_distribution<ReturnType>, std::uniform_real_distribution<ReturnType>>::type _uniform_distribution;
	//		_uniform_distribution dist;
	//		return dist(engine, { _min, _max });
	//	}
	//	case Binomial:
	//	{
	//		return random<ReturnType>(std::numeric_limits<ReturnType>::min(), std::numeric_limits<ReturnType>::max(), 0.5, _distribution);
	//	}

	//	case Geometric:
	//	{

	//	}
	//	case Pascal:
	//	{

	//	}
	//	case Poisson:
	//	{

	//	}
	//	case Exponential:
	//	{

	//	}
	//	case Gamma:
	//	{

	//	}
	//	case Weibull:
	//	{

	//	}
	//	case ExtremeValue:
	//	{

	//	}
	//	case Normal:
	//	{

	//	}
	//	case Lognormal:
	//	{

	//	}
	//	case ChiSquared:
	//	{

	//	}
	//	case Cauchy:
	//	{

	//	}
	//	case FisherF:
	//	{

	//	}
	//	case StudentT:
	//	{

	//	}
	//	case Discrete:
	//	{

	//	}
	//	case PiecewiseConstant:
	//	{

	//	}
	//	case PiecewiseLinear:
	//	{

	//	}

	//	case Bernoulli:
	//	default:
	//		assert(false);
	//		break;
	//	}
	//	return 0;
	//}

	//template <typename ReturnType>
	//ReturnType random(const double _probability, const RandomDistribution _distribution)
	//{
	//	static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
	//	switch (_distribution)
	//	{
	//	case Bernoulli:
	//	{
	//		std::bernoulli_distribution dist(_probability);
	//		return dist(engine);
	//	}
	//	case Binomial:
	//	{
	//		return random<ReturnType>(std::numeric_limits<ReturnType>::min(), std::numeric_limits<ReturnType>::max(), _probability, _distribution);
	//	}

	//	case Geometric:
	//	{

	//	}
	//	case Pascal:
	//	{

	//	}
	//	case Poisson:
	//	{

	//	}
	//	case Exponential:
	//	{

	//	}
	//	case Gamma:
	//	{

	//	}
	//	case Weibull:
	//	{

	//	}
	//	case ExtremeValue:
	//	{

	//	}
	//	case Normal:
	//	{

	//	}
	//	case Lognormal:
	//	{

	//	}
	//	case ChiSquared:
	//	{

	//	}
	//	case Cauchy:
	//	{

	//	}
	//	case FisherF:
	//	{

	//	}
	//	case StudentT:
	//	{

	//	}
	//	case Discrete:
	//	{

	//	}
	//	case PiecewiseConstant:
	//	{

	//	}
	//	case PiecewiseLinear:
	//	{

	//	}

	//	case Uniform:
	//	default:
	//		assert(false);
	//		break;
	//	}
	//	return 0;
	//}

	//template <typename ReturnType>
	//ReturnType random(const ReturnType _min, const ReturnType _max, const double _probability, const RandomDistribution _distribution)
	//{
	//	static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
	//	switch (_distribution)
	//	{
	//	case Binomial:
	//	{
	//		std::binomial_distribution<ReturnType> dist(_probability, double(_max - _min));
	//		return _min + dist(engine);
	//	}

	//	case Geometric:
	//	{

	//	}
	//	case Pascal:
	//	{

	//	}
	//	case Poisson:
	//	{

	//	}
	//	case Exponential:
	//	{

	//	}
	//	case Gamma:
	//	{

	//	}
	//	case Weibull:
	//	{

	//	}
	//	case ExtremeValue:
	//	{

	//	}
	//	case Normal:
	//	{

	//	}
	//	case Lognormal:
	//	{

	//	}
	//	case ChiSquared:
	//	{

	//	}
	//	case Cauchy:
	//	{

	//	}
	//	case FisherF:
	//	{

	//	}
	//	case StudentT:
	//	{

	//	}
	//	case Discrete:
	//	{

	//	}
	//	case PiecewiseConstant:
	//	{

	//	}
	//	case PiecewiseLinear:
	//	{

	//	}

	//	case Uniform:
	//	case Bernoulli:
	//	default:
	//		assert(false);
	//		break;
	//	}
	//	return 0;
	//}

private:
	SeedType randomSeed;
	MTEngine engine;
};