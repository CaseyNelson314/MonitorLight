//
//   移動平均
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once

namespace casey
{

    /// @brief 移動平均クラス
    template <size_t N>
    class moving_average
    {

        int data[N];           // 平均を取るデータ
        size_t write_index;    // 次の値のdataへの書き込み場所
        long sum;              // dataに保存されているデータの合計値

    public:
        /// @brief コンストラクタ
        /// @param N [in]移動平均するデータの個数
        moving_average()
            : data{}
            , write_index{}
            , sum{}
        {
        }

        /// @brief 値の更新と平均値の取得
        /// @param value [in]移動平均するデータ
        /// @return 平均値
        double operator()(double value) noexcept
        {
            sum -= data[write_index];       // 取り除くデータの値分だけ合計から取り除く
            data[write_index++] = value;    // データを更新する
            sum += value;                   // 合計値に更新した値を追加する

            if (write_index >= N)
                write_index = 0;

            return static_cast<double>(sum) / N;
        }
    };

}    // namespace casey
