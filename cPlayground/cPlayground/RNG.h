
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

	//Default random functions
	template <typename ReturnType, typename DistributionType = std::conditional<std::is_floating_point<ReturnType>::value, Distribution::UniformReal<ReturnType>, Distribution::UniformInt<ReturnType>>::type>
	typename std::enable_if<sizeof(ReturnType) != 1, ReturnType>::type random()
	{
		static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
		DistributionType dist;
		return dist(engine);
	}

	template <typename ReturnType, typename DistributionType = Distribution::UniformInt<int>>
	typename std::enable_if<sizeof(ReturnType) == 1, ReturnType>::type random()
	{
		return (ReturnType) random<int>(std::numeric_limits<ReturnType>::min(), std::numeric_limits<ReturnType>::max());
	}

	template <typename ReturnType, typename DistributionType = std::conditional<std::is_floating_point<ReturnType>::value, Distribution::UniformReal<ReturnType>, Distribution::UniformInt<ReturnType>>::type>
	ReturnType random(const ReturnType _min, const ReturnType _max)
	{
		static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
		DistributionType dist;
		return dist(engine, {_min, _max});
	}

	//Functions for certain distirbutions
	template <typename ReturnType, typename DistributionType = Distribution::Bernoulli>
	ReturnType random(const double _probability)
	{
		static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
		DistributionType dist(_probability);
		return dist(engine);
	}

	template <typename ReturnType, typename DistributionType = Distribution::Binomial<ReturnType>>
	ReturnType random(const double _probability, const ReturnType _min, const ReturnType _max)
	{
		static_assert(std::is_arithmetic<ReturnType>::value, "ReturnType needs to be an arithmetic value!");
		DistributionType dist(double(_max - _min), _probability);
		return _min + dist(engine);
	}

	//Special functions
	/*
	circle
	square
	coin
	unit
	dice
	*/


private:
	SeedType randomSeed;
	MTEngine engine;
};