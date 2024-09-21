using System;
using System.Windows;
using Hardcodet.Wpf.TaskbarNotification;

namespace MonitorLightController
{
    public partial class App : Application
    {
        private TaskbarIcon _trayIcon = new TaskbarIcon();

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            _trayIcon.TrayLeftMouseDown += TrayIcon_TrayMouseDoubleClick;
        }

        private void TrayIcon_TrayMouseDoubleClick(object sender, RoutedEventArgs e)
        {
            ShowSettingsWindow();
        }

        private void ShowSettingsWindow()
        {
            if (Current.MainWindow == null)
            {
                MainWindow = new SettingsWindow();
                MainWindow.Show();
            }
            else
            {
                if (MainWindow.IsVisible)
                {
                    MainWindow.Hide();
                }
                else
                {
                    MainWindow.Show();
                }
            }
        }

        private void Settings_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
