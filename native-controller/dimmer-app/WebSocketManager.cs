using System;
using System.Diagnostics;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace MonitorLightController
{
    public class WebSocketManager
    {
        private ClientWebSocket _client;

        private int _brightness;
        private int _colorTemp;

        public WebSocketManager()
        {
            _client = new ClientWebSocket();
            ConnectAsync().ConfigureAwait(false);
        }

        private async Task ConnectAsync()
        {
            try
            {
                await _client.ConnectAsync(new Uri("ws://m5stamp.local:443"), CancellationToken.None);
                await ReceiveParameterAsync();

            }
            catch (Exception ex)
            {
                Debug.Print("Error: " + ex.Message);
            }
        }

        public int Brightness
        {
            get { return _brightness; }
            set { _brightness = value; }
        }

        public int ColorTemp
        {
            get { return _colorTemp; }
            set { _colorTemp = value; }
        }


        /// <summary>
        /// パラメーター送信リクエスト ("w [brightness] [colorTemp]") -> ("OK" or "NG")
        /// </summary>
        /// <param name="brightness"></param>
        /// <returns></returns>
        public async Task SendParameterAsync()
        {
            if (_client.State == WebSocketState.Open)
            {
                var message = "w " + _brightness + " " + _colorTemp;
                var bytes = Encoding.UTF8.GetBytes(message);
                await _client.SendAsync(new ArraySegment<byte>(bytes), WebSocketMessageType.Text, true, CancellationToken.None);
                if (await ReceiveAsync() == "NG")
                {
                    Debug.Print("Error: SendBrightnessAsync");
                }
            }
        }


        /// <summary>
        /// パラメーター受信リクエスト ("r") -> ("[brightness] [colorTemp]" or "NG")
        /// </summary>
        /// <returns></returns>
        public async Task ReceiveParameterAsync()
        {
            if (_client.State == WebSocketState.Open)
            {
                var message = "r";
                var bytes = Encoding.UTF8.GetBytes(message);
                await _client.SendAsync(new ArraySegment<byte>(bytes), WebSocketMessageType.Text, true, CancellationToken.None);
                var result = await ReceiveAsync();
                if (result == "NG")
                {
                    Debug.Print("Error: ReceiveBrightnessAsync");
                }
                else
                {
                    var values = result.Split(' ');
                    _brightness = int.Parse(values[0]);
                    _colorTemp = int.Parse(values[1]);
                }
            }
        }


        /// <summary>
        /// パラメーター保存リクエスト ("s") -> ("OK" or "NG")
        /// </summary>
        /// <returns></returns>
        public async Task SaveParameterAsync()
        {
            if (_client.State == WebSocketState.Open)
            {
                var message = "s";
                var bytes = Encoding.UTF8.GetBytes(message);
                await _client.SendAsync(new ArraySegment<byte>(bytes), WebSocketMessageType.Text, true, CancellationToken.None);
                if (await ReceiveAsync() == "NG")
                {
                    Debug.Print("Error: SaveParameterAsync");
                }
            }
        }


        private async Task<string> ReceiveAsync()
        {
            var buffer = new byte[1024];
            var result = await _client.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);
            return Encoding.UTF8.GetString(buffer, 0, result.Count);
        }

    }
}
