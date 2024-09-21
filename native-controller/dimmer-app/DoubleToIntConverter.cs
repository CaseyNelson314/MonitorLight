// https://gootara.org/library/2016/06/wpf-sdc2.html

using System;
using System.Globalization;
using System.Windows.Data;

namespace WpfCustomSlider
{
    class DoubleToIntConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return System.Convert.ToInt32(value);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            double d;
            return double.TryParse(value.ToString(), out d) ? d : 0;
        }

    }
}