#pragma once

#include <chrono>
#include <cstdint>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include <cmath>

// 可配任意频率的周期定时器（C++11 header-only）
// 使用方法示例（注释形式）:
// Timer t;
// t.start(10.0, []{ /* 每秒 10 次的任务 */ });
// ...
// t.stop();

class Timer
{
public:
    Timer() = default;

    ~Timer()
    {
        stop();
    }

    // Start the periodic timer with frequency in Hz (> 0).
    // The callback will be invoked repeatedly on a background thread.
    void start(double frequency_hz, std::function<void()> cb)
    {
        if (frequency_hz <= 0.0 || !std::isfinite(frequency_hz))
        {
            throw std::invalid_argument("frequency_hz must be positive finite");
        } 
        if (!cb)
        {
            throw std::invalid_argument("callback must be valid");
        }
            

        std::lock_guard<std::mutex> lock(mutex_);
        callback_ = std::move(cb);
        frequency_hz_.store(frequency_hz);

        if (running_.load())
        {
            cv_.notify_one(); // update frequency/callback on-the-fly
            return;
        }

        running_.store(true);
        worker_ = std::thread([this]() { this->threadFunc(); });
    }

    // Stop the timer and join the worker thread.
    void stop()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!running_.load()) return;
            running_.store(false);
        }
        cv_.notify_one();
        if (worker_.joinable()) worker_.join();
    }

    // Change frequency while running (Hz > 0).
    void setFrequency(double frequency_hz)
    {
        if (frequency_hz <= 0.0 || !std::isfinite(frequency_hz))
        {
            throw std::invalid_argument("frequency_hz must be positive finite");
        }
        frequency_hz_.store(frequency_hz);
        cv_.notify_one();
    }

    bool isRunning() const { return running_.load(); }

private:
    void threadFunc()
    {
        using clock = std::chrono::steady_clock;
        auto next = clock::now();

        while (running_.load())
        {
            double freq = frequency_hz_.load();
            if (!(freq > 0.0)) break;
            auto period = std::chrono::duration<double>(1.0 / freq);
            next += std::chrono::duration_cast<std::chrono::steady_clock::duration>(period);

            // wait until next tick or until frequency/stop change
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait_until(lock, next, [this]() { return !running_.load(); });
            if (!running_.load()) break;

            // copy callback under lock to avoid race with stop()/start()
            auto cb = callback_;
            lock.unlock();

            if (cb) cb();
        }
    }

    std::thread worker_;
    std::atomic<bool> running_{false};
    std::atomic<double> frequency_hz_{0.0};
    std::function<void()> callback_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
};