#include "pch.h"
#include "Timer.h"

Timer::Timer() noexcept
{
	mLast = std::chrono::steady_clock::now();
	return;
}

float Timer::Mark() noexcept
{
	const auto old = mLast;
	mLast = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = mLast - old;
	return frameTime.count();
}

float Timer::Peek() const noexcept
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mLast).count();
}
