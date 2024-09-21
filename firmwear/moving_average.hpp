//
//   moving average
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once

namespace casey
{

    /**
     * @brief moving average
     */
    template <size_t N>
    class moving_average
    {
    public:
        moving_average()
            : data{}
            , write_index{}
            , sum{}
        {
        }

        double operator()(int value) noexcept
        {
            sum -= data[write_index];
            data[write_index++] = value;
            sum += value;

            if (write_index >= N)
                write_index = 0;

            return static_cast<double>(sum) / N;
        }

    private:
        int data[N];
        size_t write_index;
        long sum;
    };

}    // namespace casey
