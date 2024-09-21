using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System;
using System.Windows;
using System.Windows.Input;

namespace MonitorLightController
{
    public partial class SettingsWindow : Window
    {
        private WebSocketManager webSocketManager = new WebSocketManager();

        public SettingsWindow()
        {
            InitializeComponent();
            // ウィンドウをトレイアイコンの近くに表示するロジックを追加できます
            this.Loaded += SettingsWindow_Loaded;
        }

        private void SettingsWindow_Loaded(object sender, RoutedEventArgs e)
        {
            // システムトレイの位置を取得してウィンドウを配置
            // ここでは簡単のため画面の右下に表示
            var workingArea = SystemParameters.WorkArea;
            this.Left = workingArea.Right - this.Width - 350;
            this.Top = workingArea.Bottom - this.Height - 60;
        }

        private async void ColorTemperatureSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            webSocketManager.ColorTemp = (int)e.NewValue;
            await webSocketManager.SendParameterAsync();
        }

        private async void BrightnessSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            webSocketManager.Brightness = (int)e.NewValue;
            await webSocketManager.SendParameterAsync();
        }

        protected override void OnDeactivated(EventArgs e)
        {
            base.OnDeactivated(e);
            this.Hide();
        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            await webSocketManager.SaveParameterAsync();
        }
    }
}
